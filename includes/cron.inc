<?php

/*
  * @file
  * Encapsulates the main cron job task for elobbyist 
 * 
  * See the Run() method
  */

require_once "Mail.php";

class ElobbyistCronTask {
  
  protected $Mailings = null;
  
   /*
    * Processes active mailings that have already started
    */
  public function Run() {
    try {
      $Sent = 0;
      $MaxSend = variable_get('elobbyist_max_emails_per_batch', ELOBBYIST_DEFAULT_MAX_EMAILS_PER_BATCH);
      
      $this->LoadMailings();
      
      foreach($this->Mailings as $mailing) {
        $mail_obj = new ElobbyistCronTaskMailing($mailing, $MaxSend);
        $mail_obj->Process($Sent);
        unset($mail_obj);
        if ($Sent >= $MaxSend && $MaxSend > 0)
          break;
      }
    }
    catch(Exception $ex) {
      watchdog('elobbyist cron', $ex->getMessage() . ' Trace: ' . $ex->getTraceAsString(), array(), WATCHDOG_ERROR);
    }
  }
  
  protected function LoadMailings() {
    $query = db_select('elobbyist_mailing', 'm');
    $query->join('elobbyist_template', 't', 'm.tid = t.tid');    
    
    $this->Mailings = $query->condition('m.status', ELOBBYIST_MAILING_STATUS_ACTIVE)
          ->condition('start', REQUEST_TIME, '<=')
          ->fields ('m', array (
                  'mid',
                  'schedule',
                  'end',
                  'addtogrpid',
                )
            )
          ->fields ('t', array (
                  'tid',
                  'subject',
                  'body',
                )
            )
          ->execute();
  }
}

class ElobbyistCronTaskMailing {
  
  protected $Mailing = null;
  protected $FromGroups = array();
  protected $ToGroups = array();
  protected $FromIds = array();
  protected $CollectedSendersIds = array();
  protected $ToIds = array();
  protected $From = null;
  protected $CollectedSenders = null;
  protected $To = null;
  
  protected $NotificationSenderReady = FALSE;
  protected $NotificationSenderEmail = null;
  protected $NotificationSenderSmtpHost = null;
  protected $NotificationSenderSmtpPort = null;
  protected $NotificationSenderPass = null;
  protected $NotificationSubject = null;
  protected $MaxBounces = 0;
  
  protected $Sent = 0;
  protected $MaxSend = 0;
  
  protected $ProcessFrom = TRUE; //used by NextSender()
  
  protected $Activities = array();

  public function __construct($row, $max_send) {
    $this->Mailing = $row;
    $this->MaxSend = $max_send;
  }

   /*
    * Process emails for each mailing
    */
  public function Process(&$total_sent) {
    if (!$this->LoadContacts()) {
      return; //exit (skip this mailing) if there are no recipients/senders
    }
    
    $this->PrepareNotifications();
    
    //load already processed activities
    $this->LoadActivities();

    $Recipient = null;
    $bMaxSendTest = FALSE;
    $Sender = $this->FirstSender();
    do {
      $bNotify = FALSE;
      reset($this->To);
      $Recipient = current($this->To);
      $Body = NULL;
      $Pass = elobbyist_decrypt($Sender->pass);
      $RecipientEmailList = array();
      $RecipientNameList = array();
      
      do {
        //skip processed mails
        if (!$this->HasActivity($Sender->cid, $Recipient->cid)) {
          //create the activity and send email
          if ($this->ProcessEmail($Sender, $Recipient, $Body, $Pass)) {
            //collect recipient emails for notifications
            if ($Sender->notify && $this->NotificationSenderReady) {
              $bNotify = TRUE;
              $RecipientEmailList[] = $Recipient->email;
              $RecipientNameList[]  = $Recipient->name;
            }
            $total_sent++;
            $bMaxSendTest = ($total_sent >= $this->MaxSend && $this->MaxSend > 0);
          }
          elseif ($Sender->bounce == ELOBBYIST_CONTACT_EMAIL_BOUNCING_IGNORED) {
            break;
          }
        }
      } while(!$bMaxSendTest && $Recipient = next($this->To));
      if ($bNotify) {
        $this->NotifySender($Sender, $Body, $RecipientEmailList, $RecipientNameList);
      }
    } while (!$bMaxSendTest && $Sender = $this->NextSender());

    if (!$bMaxSendTest) {
      $this->Close();
    }
  }
  
  /*
   * Create the activity and send the email
   */
  protected function ProcessEmail($Sender, $Recipient, &$Body, &$Pass) {   
    //send email
    try
    {
      //load sender email provider
      $eps = entity_load('elobbyist_email_provider', array($Sender->providerid));
      if (!isset($eps) || count($eps) == 0)
        return FALSE;
      $ep = current($eps);
      
      $Body = elobbyist_template_to_email_body($this->Mailing->body, $Sender->name,
              $Recipient->name);
      
      // Build the default headers
      $message = array();
      $message['headers'] = array(
        'MIME-Version'              => '1.0',
        'Content-Type'              => 'text/html; charset=UTF-8; format=flowed; delsp=yes',
        'Content-Transfer-Encoding' => '8Bit',
      );

      //subject is in the headers in this mail function, so copy it
      $message['headers']['Subject'] = elobbyist_template_to_email_subject(
        $this->Mailing->subject, $Sender->name, $Recipient->name );

      
      $message['headers']['From'] = $message['headers']['Sender'] = $message['headers']['Return-Path'] = $Sender->email;
      $message['headers']['To'] = $Recipient->email;
      
      $message['body'] = $Body;
      
      $smtp = Mail::factory('smtp',
        array ('host' => $ep->smtphost,
          'port' => $ep->smtpport,
          'auth' => true,
          'username' => $Sender->email,
          'password' => $Pass));

      $result = $smtp->send($Recipient->email, $message['headers'], $message['body']);

      if (PEAR::isError($result)) {
        $this->SetBouncing($result->getCode(), $Sender);
        $this->LogMailError(NULL, $result, $Sender, $Recipient);
        return FALSE;
      }
      else if ($result) {
        if ($Sender->bounce != ELOBBYIST_CONTACT_EMAIL_VERIFIED) {
          $Sender->bounce = ELOBBYIST_CONTACT_EMAIL_VERIFIED;
          $Sender = entity_get_controller('elobbyist_contact')->save($Sender);
        }
        return $this->CreateActivity($Sender, $Recipient);
      }
    }
    catch(Exception $ex) {
      $this->LogMailError($ex, NULL, $Sender, $Recipient);
    }
    
    return FALSE;
  }

  /*
   * Gets the next sender or FALSE if there aren't any - from either the From array or the CollectedSenders one
   * If the next sender is from the From array and is confined to a mailing - it is skipped
   */
  protected function NextSender() {    
    if ($this->ProcessFrom) {
      $Sender = next($this->From);
      if (!$Sender) {
        $this->ProcessFrom = FALSE;
        if (!isset($this->CollectedSenders) || count($this->CollectedSenders) == 0) {
          return FALSE;
        }
        return $this->NextSender();
      }
      //If the sender is from the From field and is confined to a mailing - it is skipped
      if ($Sender->bounce == ELOBBYIST_CONTACT_EMAIL_BOUNCING_IGNORED || $Sender->stype == ELOBBYIST_SUBSCRIBER_TYPE_MAILING) {
        return $this->NextSender();
      }
      return $Sender;
    }
    else {
      $Sender = next($this->CollectedSenders);
      if (!$Sender)
        return FALSE;
      //if the sender is from the collector group and is confined to a mailing, but not to this mailing - it is skipped
      if ($Sender->bounce == ELOBBYIST_CONTACT_EMAIL_BOUNCING_IGNORED || 
        ($Sender->stype == ELOBBYIST_SUBSCRIBER_TYPE_MAILING && $Sender->mid != $this->Mailing->mid)) {
        return $this->NextSender();
      }
      return $Sender;
    }
  }
  
  /*
   * Gets the first sender or FALSE if there aren't any - from either the From array or the CollectedSenders one
   */
  protected function FirstSender() {   
    if (!isset($this->From) || count($this->From) == 0) {
      $this->ProcessFrom = FALSE;
    }
      
    if ($this->ProcessFrom) {
      $Sender = current($this->From);
      //If the sender is from the From field and is confined to a mailing - it is skipped
      if ($Sender->bounce == ELOBBYIST_CONTACT_EMAIL_BOUNCING_IGNORED || $Sender->stype == ELOBBYIST_SUBSCRIBER_TYPE_MAILING) {
        return $this->NextSender();
      }
      return $Sender;
    }
    else {
      if (!isset($this->CollectedSenders) || count($this->CollectedSenders) == 0) {
        return FALSE;
      }
      $Sender = current($this->CollectedSenders);
      //if the sender is from the collector group and is confined to a mailing, but not to this mailing - it is skipped
      if ($Sender->bounce == ELOBBYIST_CONTACT_EMAIL_BOUNCING_IGNORED || 
          ($Sender->stype == ELOBBYIST_SUBSCRIBER_TYPE_MAILING && $Sender->mid != $this->Mailing->mid)) {
        return $this->NextSender();
      }
      return $Sender;
    }
  }
  
  protected function SetBouncing($nCode, $Sender) {
    $bSave = FALSE;
    switch($nCode) {
      case PEAR_MAIL_SMTP_ERROR_AUTH:
      case PEAR_MAIL_SMTP_ERROR_SENDER:
      case PEAR_MAIL_SMTP_ERROR_CONNECT:
        $Sender->bounces++;
        if ($Sender->bounces >= $this->MaxBounces && $this->MaxBounces > 0) {
          if ($Sender->bounce != ELOBBYIST_CONTACT_EMAIL_BOUNCING_IGNORED) {
            $Sender->bounce = ELOBBYIST_CONTACT_EMAIL_BOUNCING_IGNORED;
            $bSave = TRUE;
          }
        }
        elseif ($Sender->bounce != ELOBBYIST_CONTACT_EMAIL_BOUNCING) {
          $Sender->bounce = ELOBBYIST_CONTACT_EMAIL_BOUNCING;
          $bSave = TRUE;
        }
        elseif ($Sender->bounces < $this->MaxBounces) {
          $bSave = TRUE; //just save the count
        }
        if ($bSave) {
          $Sender = entity_get_controller('elobbyist_contact')->save($Sender);
        }
        break;
   }
 }
  
  protected function LoadContacts() {
    //prepare for contact loading
    $this->ProcessRelations();
    //exit (skip this mailing) if there are no recipients
    if (count($this->ToIds) == 0) {
      return FALSE;
    }

    $Collected = count($this->CollectedSendersIds);

    if (count($this->FromIds) > 0) {
      $this->From = entity_load('elobbyist_contact', $this->FromIds);
    }
    elseif ($Collected == 0) {
      //exit (skip this mailing) if there are no senders
      return FALSE;
    }

    if ($Collected > 0) {
      $this->CollectedSenders = entity_load('elobbyist_contact', $this->CollectedSendersIds);
    }

    $this->To = entity_load('elobbyist_contact', $this->ToIds);

    //get max bouncing variable value
    $this->MaxBounces = variable_get('elobbyist_max_bounces', ELOBBYIST_DEFAULT_MAX_BOUNCES);

    return TRUE;
  }
  
  protected function CreateActivity($Sender, $Recipient) {
    //create the activity
    $ctl = entity_get_controller('elobbyist_activity');
    $activity = $ctl->create();

    $activity->mid = $this->Mailing->mid;
    $activity->tid = $this->Mailing->tid;
    $activity->fromcid = $Sender->cid;
    $activity->tocid = $Recipient->cid;

    $activity = $ctl->save($activity);

    if (!$activity)
      return FALSE;

    //save the activity as processed for this run
    $this->Activities[$activity->fromcid . ':' . $activity->tocid] = $activity->aid;

    return TRUE;
  }

  protected function LoadActivities() {
    $results = db_select('elobbyist_activity', 'ac')
             ->condition('mid', $this->Mailing->mid)
             ->condition('fromcid', $this->FromIds + $this->CollectedSendersIds, 'IN')
             ->condition('tocid', $this->ToIds, 'IN')
             ->fields ('ac', array (
                    'aid',
                    'fromcid',
                    'tocid',
                  )
              )
             ->execute();
    
    foreach($results as $row) {
      $this->Activities[$row->fromcid . ':' . $row->tocid] = $row->aid;
    }
  }
  
  protected function HasActivity($from, $to) {
    $sKey = $from . ':' . $to;
    return isset($this->Activities[$sKey]);
  }
  
  
  /*
   * Mailing processing finalization
   */
  protected function Close()
  {
    //Once a mailing is completely processed and its end date has passed - change its status to 'closed'
    if ($this->Mailing->schedule == ELOBBYIST_MAILING_SCHEDULE_SIMPLE || $this->Mailing->end < REQUEST_TIME) {
      $this->Mailing->status = ELOBBYIST_MAILING_STATUS_CLOSED;
      entity_get_controller('elobbyist_mailing')->save($this->Mailing);
    }
  }
  
  
  protected function PrepareNotifications() {
    $this->NotificationSenderEmail = variable_get('elobbyist_sender_email');
    if (empty($this->NotificationSenderEmail)) {
      return;
    }
    
    $this->NotificationSenderPass= variable_get('elobbyist_sender_pass');
    if (empty($this->NotificationSenderPass)) {
      return;
    }
    $this->NotificationSenderPass=elobbyist_decrypt($this->NotificationSenderPass);
    
    $providerid = variable_get('elobbyist_sender_providerid');
    if (empty($providerid)) {
      return;
    }
    $providers = entity_load('elobbyist_email_provider', array($providerid));
    if (!isset($providers) || count($providers) == 0) {
      return;
    }
    $provider = current($providers);
    $this->NotificationSenderSmtpHost = $provider->smtphost;
    $this->NotificationSenderSmtpPort = $provider->smtpport;
    
    $this->NotificationSubject = str_replace('[elobbyist:subject]', $this->Mailing->subject,
      elobbyist_get_notify_subject());
    
    $this->NotificationSenderReady = TRUE;
  }
  
  protected function NotifySender($Sender, &$Body, &$RecipientEmailList, &$RecipientNameList) {
    //send notification email
    try
    {
      global $base_url;
      // Build the default headers
      $message = array();
      $message['headers'] = array(
        'MIME-Version'              => '1.0',
        'Content-Type'              => 'text/html; charset=UTF-8; format=flowed; delsp=yes',
        'Content-Transfer-Encoding' => '8Bit',
      );

      //subject is in the headers in this mail function, so copy it
      $message['headers']['Subject'] = $this->NotificationSubject;
      $message['headers']['From'] = $message['headers']['Sender'] = $message['headers']['Return-Path'] = $this->NotificationSenderEmail;
      $message['headers']['To'] = $Sender->email;
      
      $message['body'] = str_replace(
        array(
          '[elobbyist:recipients emails]',
          '[elobbyist:recipients]',
          '[elobbyist:body]',
          '[elobbyist:unsubscribe]',
          '[elobbyist:subscribe]',
          '[elobbyist:signup]',
          '[elobbyist:remove]',
        ),
        array(
          join(', ', $RecipientEmailList),
          join(', ', $RecipientNameList),
          $Body,
          l(t('Unsubscribe'), $base_url . '/elobbyist/contact/unsubscribe/' . $Sender->handle, 
            array('attributes' => array('target' => '_blank'))),
          l(t('Subscribe'), $base_url .  '/elobbyist/contact/subscribe/' . $Sender->handle, 
            array('attributes' => array('target' => '_blank'))),
          l(t('Sign up'), $base_url . '/elobbyist/contact/signup/' . $Sender->handle, 
            array('attributes' => array('target' => '_blank'))),
          l(t('Remove'),$base_url . '/elobbyist/contact/remove/' . $Sender->handle, 
            array('attributes' => array('target' => '_blank'))),
        ),
        elobbyist_get_notify_body()
      );
      
      $smtp = Mail::factory('smtp',
        array ('host' => $this->NotificationSenderSmtpHost,
          'port' => $this->NotificationSenderSmtpPort,
          'auth' => true,
          'username' => $this->NotificationSenderEmail,
          'password' => $this->NotificationSenderPass));

      $smtp->send($Sender->email, $message['headers'], $message['body']);
    }
    catch(Exception $ex) {
      watchdog('elobbyist cron', $ex->getMessage() . ' Trace: ' . $ex->getTraceAsString(), array(), WATCHDOG_ERROR);
    }
  }


  protected function LogMailError($e, $result, $Sender, $Recipient) {
    $str = 'Sender:' . $Sender->email . ' Recipient: ' . $Recipient->email . ' ';
    if (isset($e)) {
      $str .= $ex->getMessage() . ' Trace: ' . $ex->getTraceAsString();
    }
    
    if (isset($result)) {
      $str .= ' PEAR message: ' . $result->getMessage();
    }
    
    watchdog('elobbyist cron', $str, array(), WATCHDOG_ERROR);
  }
  
  /*
   * Prepare all entity ids for the main process
   */
  protected function ProcessRelations() {
    $this->ProcessMailingRelations();
    $this->ProcessGroupsToContactsRelations($this->FromGroups, $this->FromIds, 'elobbyist_subscriber');
    $this->ProcessGroupsToContactsRelations($this->ToGroups, $this->ToIds, 'elobbyist_recipient');
    if ($this->Mailing->schedule == ELOBBYIST_MAILING_SCHEDULE_ON_GOING && !empty($this->Mailing->addtogrpid)) {
      $this->ProcessCollectedSendersRelations();
    }
  }
  
  protected function ProcessGroupsToContactsRelations(&$groups, &$target, $relation_type) {
    //from groups can be empty
    if (count($groups) == 0) {
      return;
    }
    $query = new RelationQuery();
    $query->fieldCondition('endpoints', 'entity_type', 'elobbyist_group', '=');
    $query->fieldCondition('endpoints', 'entity_id', $groups, 'IN');
    $relations = entity_load('relation', array_keys($query->execute()));

    foreach($relations as $relation) {
      if ($relation->relation_type != $relation_type) {
        continue;
      }
      foreach($relation->endpoints as $endpoints) {
        foreach($endpoints as $endpoint) {
          if ($endpoint['entity_type'] == 'elobbyist_contact') {
            $target[] = $endpoint['entity_id'];
          }
        }
      }
    }
  }
  
  protected function ProcessCollectedSendersRelations() {
    $groups = entity_load('elobbyist_group', array($this->Mailing->addtogrpid));
    if (!isset($groups) || count($groups) == 0) {
      return;
    }
    $group = current($groups);
    if ($group->status == ELOBBYIST_GROUP_STATUS_INACTIVE) {
      return;
    }
    
    $relations = elobbyist_relations_get_data('elobbyist_group', $this->Mailing->addtogrpid);
    
    foreach($relations as $relation) {
      if ($relation->relation_type != 'elobbyist_subscriber') {
        continue;
      }
      foreach($relation->endpoints as $endpoints) {
        foreach($endpoints as $endpoint) {
          if ($endpoint['entity_type'] == 'elobbyist_contact') {
            $this->CollectedSendersIds[] = $endpoint['entity_id'];
          }
        }
      }
    }
  }
  
  /*
   * Fill from and to arrays with group ids
   */
  protected function ProcessMailingRelations() {
    $bFrom = FALSE;
    $bTo = FALSE;
      
    $relations = elobbyist_relations_get_data('elobbyist_mailing', $this->Mailing->mid);
    foreach($relations as $relation) {
      $bFrom = FALSE;
      $bTo = FALSE;
      if ($relation->relation_type == 'elobbyist_from') {
        $bFrom = TRUE;
      }
      elseif ($relation->relation_type == 'elobbyist_to') {
        $bTo = TRUE;
      }
      foreach($relation->endpoints as $endpoints) {
        foreach($endpoints as $endpoint) {
          //add each group endpoint
          if ($endpoint['entity_type'] == 'elobbyist_group') {
            if ($bFrom) {
              $this->FromGroups[$endpoint['entity_id']] = $endpoint['entity_id'];
            }
            elseif ($bTo) {
              $this->ToGroups[$endpoint['entity_id']] = $endpoint['entity_id'];
            }
          }
        }
      }
    }
    
    //remove inactive groups
    $this->RemoveInactiveGroups($this->FromGroups);
    $this->RemoveInactiveGroups($this->ToGroups);
    
  }
  
  /*
   * Remove groups with inactive status
   */
  protected function RemoveInactiveGroups(&$grparr) {
    if (count($grparr) == 0) {
      return;
    }
    
    $groups = entity_load('elobbyist_group', $grparr);
    foreach($groups as $grpid => $group) {
      if ($group->status == ELOBBYIST_GROUP_STATUS_INACTIVE) {
        unset($grparr[$grpid]);
      }
    }
  }
}

?>
