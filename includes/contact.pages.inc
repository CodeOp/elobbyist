<?php

/**
 * @file
 * Contact entity pages callbacks
 */

/*
 * forms callback
 */
function elobbyist_contact_form($form, &$form_state, $contact) {
  // Set the id to identify this as a contact edit form.
  $form['#id'] = 'elobbyist_contact-form';
  
  // Save the contact for later, in case we need it.
  $form['#elobbyist_contact'] = $contact;
  $form_state['elobbyist_contact'] = $contact;
  
  //save hidden/disabled values for this form
  $form_state['values']['stype'] = $contact->stype;
  $form_state['values']['form'] = $contact->form;
  
  $new_record = empty($contact->cid);
  
  // Set fields
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Full Name'),
    '#default_value' => $contact->name,
    '#weight' => -5,
    '#maxlength' => 100,
    '#size' => 50,
    '#required' => TRUE,
  );
  
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => $contact->email,
    '#weight' => 3,
    '#maxlength' => 254,
    '#size' => 50,
    '#required' => TRUE,
    '#rules' => array('email'),
  );
    
  if ($contact->type == 'subscriber') {
    //subscriber specific fields
    
    //password
    $form['pass'] = array(
      '#type' => 'password',
      '#title' => t('Password'),
      //never send back the password, so no default_value
      '#default_value' => '',
      '#weight' => 4,
      '#maxlength' => 64,
      '#size' => 50,
      '#description' => t('Email account password.'),
      '#required' => $new_record,
      );
    
    //provider
    $form['providerid'] = array(
      '#type' => 'select',
      '#key_type' => 'associative',
      '#title' => t('Email Provider'),
      '#options' => elobbyist_get_email_providers(),
      '#default_value' => $contact->providerid,
      '#weight' => 20,
      '#description' => t('Select the Email provider for the email account.'),
      '#required' => TRUE,
    );
    
    $form['notify'] = array(
      '#type' => 'checkbox',
      '#title' => t('Notify'),
      '#default_value' => $contact->notify,
      '#weight' => 30,
      '#description' => t('Notify the contact on each email sent.'),
    );
  }
  
  $form['elobbyist_contact_groups'] = array(
      '#type' => 'elobbyist_contact_groups',
      '#relation_type' => 'elobbyist_' . $contact->type,
      '#title' => t('Groups'),
      '#weight' => 40,
      '#description' => t('Emails are sent only between groups.'),
  );
  
  //Add the buttons
  $form['buttons'] = array();
  $form['buttons']['#weight'] = 100;
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
    '#submit' => array('elobbyist_contact_form_submit'),
  );
  
  if (!$new_record) {
    $form['buttons']['delete'] = array(
      '#access' => user_access('delete email lobbyist contacts'),
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 120,
      '#submit' => array('elobbyist_contact_form_delete_submit'),
      '#limit_validation_errors' => array(),       // No validation.
    );
  }
  
  $form['#validate'][] = 'elobbyist_contact_form_validate';
  
  field_attach_form('elobbyist_contact', $contact, $form, $form_state);
  
  return $form;
}

/*
 * Validate function
 */
function elobbyist_contact_form_validate($form, &$form_state) {
  $contact = $form_state['elobbyist_contact'];
  
  //encrypt password
  if (isset($form_state['values']['pass'])) {
    $contact->pass = encrypt($form_state['values']['pass'], array('base64' => TRUE));
    //do not store plain password from now on
    unset($form_state['values']['pass']);
  }
  
  //verify that email is unique
  elobbyist_contact_unique_email($contact->cid, $form_state['values']['email']);
      
  //Field API validation
  field_attach_form_validate('elobbyist_contact', $contact, $form, $form_state);
}

/*
 * Save functions
 */
function elobbyist_contact_form_submit($form, &$form_state) {
  global $user;
  
  $contact = $form_state['elobbyist_contact'];
  
  $contact->name = $form_state['values']['name'];
  $contact->email = $form_state['values']['email'];
  
  if (isset($form_state['values']['providerid'])) {
    $contact->providerid = $form_state['values']['providerid'];
  }
  
  if (isset($form_state['values']['notify'])) {
    $contact->notify = $form_state['values']['notify'];
  }
      
  // Notify field widgets.
  field_attach_submit('elobbyist_contact', $contact, $form, $form_state);
  
  $new_record = empty($entity->cid);
  
  // Save the contact.
  $contact = elobbyist_contact_save($contact);
  
  //if new record, call submit groups manually, because it needs the entity id
  if ($new_record) {
    elobbyist_field_attach_submit('elobbyist_contact', $contact, $form, $form_state);
  }
  
  $types = elobbyist_contact_types();
  
  // Notify the user.
  if ($contact) {
    drupal_set_message(t('@name saved.',array( '@name' => $types[$contact->type]->name)));
    
    if ($new_record) {
      $form_state['redirect'] = 'elobbyist/contact/' . $contact->cid . '/edit';
    }
  }
}

function elobbyist_contact_save($contact) {
  //invoke hook_elobbyist_contact_save_alter
  $cloned = clone $contact;
  $continue = TRUE;
    
  drupal_alter('elobbyist_contact_save', $cloned, $continue);
  
  if ($continue)
    return entity_get_controller('elobbyist_contact')->save($contact);
  
  //allow to modify cid for new records
  if (empty($contact->cid))
    $contact->cid = check_url($cloned->cid);
  
  return $contact;
}


/*
 * Delete functions
 */
function elobbyist_contact_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  
  $contact = $form['#elobbyist_contact'];
  $form_state['redirect'] = array('elobbyist/contact/' . $contact->cid . '/delete',
    array('query' => $destination));
}
function elobbyist_contact_delete_confirm($form, &$form_state, $contact) {
  $form['#elobbyist_contact'] = $contact;
    
  $path = 'elobbyist/' . $contact->type . 's';

  // Always provide entity id in the same form key as in the entity edit form.
  $form['cid'] = array('#type' => 'value', '#value' => $contact->cid);
  return confirm_form($form, 
    t('Are you sure you want to delete %title?',
      array('%title' => $contact->name)),
    $path,
    t('This action cannot be undone'),
    t('Delete'), 
    t('Cancel')
  );
}
function elobbyist_contact_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $contact = elobbyist_contact_load($form_state['values']['cid']);
    
    $path = 'elobbyist/' . $contact->type . 's';
    
    elobbyist_contact_delete($form_state['values']['cid']);
    
    watchdog('elobbyist_contact', '@type: deleted %title.' , array('@type' => 
      $contact->type, '%title' => $contact->name) );
    
    $types = elobbyist_contact_types();
    drupal_set_message(t('@type %title has been deleted.', array(
      '@type' => $types[$contact->type]->name,
      '%title' => $contact->name)
      )
    );
    
    $form_state['redirect'] = $path;
  }
}

/*
 * Validate that email is unique
 */
function elobbyist_contact_unique_email($cid, $email) {
  //Execute a count query to see if there's other similar values.
  
  $query = db_select('elobbyist_contact', 'c');
  
  $query->addExpression('COUNT(cid)', 'contact_count');
  
  $query->condition('email', $email);
    
  if (!empty($cid))
        $query = $query->condition('cid', $cid, '<>');

  $query = $query->execute();
  
  $col =  $query->fetchColumn();

  if ($col > 0) {
    form_set_error('email', t('Email address must be unique in the contacts table. @email is already in use for another contact.',
      array('@email' => $email)));
  }
}

function elobbyist_contact_page_view($entity, $view_mode = 'full') {
  
  elobbyist_contact_page_title($entity);
  
  // Remove previously built content, if exists.
  $entity->content = array();
  
  $entity->content['#attached']['css'] = array(
    drupal_get_path('module', 'elobbyist') . '/includes/elobbyist.css',
  );
      
  $entity->content['email'] = array(
    '#markup' => 
      theme('elobbyist_field',
        array(
          'title' => t('Email'),
          'item' => filter_xss($entity->email),
        )
     ),
    '#weight' => -50,
  );
  
  if ($entity->type == 'subscriber') {
    if (!empty($entity->providerid)) {
      $provider = entity_load('elobbyist_email_provider', array($entity->providerid));
      
      if ($provider != null && is_array($provider)) {
        $entity->content['providerid'] = array(
          '#markup' => theme('elobbyist_field',
              array(
                'title' => t('Provider'),
                'item' => filter_xss(current($provider)->name),
              )
           ),
          '#weight' => -45,
        );
      }
    }
  
    $entity->content['notify'] = array(
      '#markup' => theme('elobbyist_field',
          array(
            'title' => t('Notify on each mail'),
            'item' => $entity->notify ? t('Yes') : t('No'),
          )
       ),
      '#weight' => -35,
    );

    if (!empty($entity->form)) {
      $form_types = elobbyist_form_types();
      $entity->content['form'] = array(
        '#markup' => theme('elobbyist_field',
            array(
              'title' => t('Created through'),
              'item' => $form_types[$entity->form],
            )
         ),
        '#weight' => -30,
      );
    }
  }
  
  $format_short_date = variable_get('date_format_short', 'Y-n-j - H:i');
  
  $entity->content['created'] = array(
    '#markup' => theme('elobbyist_field',
          array(
            'title' => t('Created on'),
            'item' => format_date($entity->created, 'custom', $format_short_date),
          )
       ),
      '#weight' => -16,
  );
  
  $entity->content['changed'] = array(
    '#markup' => theme('elobbyist_field',
          array(
            'title' => t('Modified on'),
            'item' => format_date($entity->changed, 'custom', $format_short_date),
          )
       ),
      '#weight' => -15,
  );
  
  // Build fields content.
  field_attach_prepare_view('elobbyist_contact', 
    array($entity->cid => $entity), $view_mode);
  
  entity_prepare_view('elobbyist_contact', array($entity->cid => $entity));
  
  $entity->content += field_attach_view('elobbyist_contact', $entity, $view_mode);
  
  return $entity->content;
}

/*
 * Add record page callback
 */
function elobbyist_contact_add($type) {
  $types = elobbyist_contact_types();
  $type  = (isset($type) ? str_replace('-', '_', $type) : NULL);
  if (empty($types[$type])) {
    return MENU_NOT_FOUND;
  }
  
  $contact = entity_get_controller('elobbyist_contact')->create($type);
  
  //set subscription type to persistent for subscribers
  if ($type == 'subscriber') {
    $contact->stype = ELOBBYIST_SUBSCRIBER_TYPE_PERSISTENT;
    $contact->form = ELOBBYIST_FORM_ADMIN;
  }
  
  $contact->form = ELOBBYIST_FORM_ADMIN;
  
  drupal_set_title(t('New @name', array('@name' => $types[$type]->name)),
    PASS_THROUGH);
  
  return drupal_get_form('elobbyist_contact_form', $contact);
}

/*
 * Edit record page callback
 */
function elobbyist_contact_page_edit($contact) {
  elobbyist_contact_page_title($contact);
  
  return drupal_get_form('elobbyist_contact_form', $contact);
}

function elobbyist_contact_page_title($contact) {
  $types = elobbyist_contact_types();
  drupal_set_title(t('@type: @title', array(
    '@type' => $types[$contact->type]->name,
    '@title' => $contact->name, )), PASS_THROUGH);
}

/**
 * Gets subscriber built in types
 */
function elobbyist_subscriber_types() {
  return array(
    ELOBBYIST_SUBSCRIBER_TYPE_ONE_TIME => t('One-Time'),
    ELOBBYIST_SUBSCRIBER_TYPE_PERSISTENT => t('Persistent'),
  );
}

/*
 * Get form types
 */
function elobbyist_form_types() {
  return array(
    ELOBBYIST_FORM_ADMIN => t('admin form'),
    ELOBBYIST_FORM_PUBLIC => t('public form'),
  );
}

/*
 * Pull a list of Email providers from the database
 */
function elobbyist_get_email_providers() {
  //get values from cache if exist there
  $providers = &drupal_static(__FUNCTION__);
  
  if (!empty($providers)) 
    return $providers;
  
  $result = db_select('elobbyist_email_provider', 'ep')
          ->fields('ep', array('providerid', 'name'))
          ->orderBy('ep.name', 'ASC')
          ->execute();

  return $result->fetchAllKeyed();
}

/*
 * Display list of subscribers
 */
function elobbyist_subscribers_grid() {
 
  //Create a list of headers for sorting
	$header = array( 
    array('data' => t('Full Name'), 'field' => 'name', 'sort' => 'asc'),
    array('data' => t('Email'), 'field' => 'email', 'sort' => 'asc'),
    array('data' => t('Provider'), 'field' => 'provider_name', 'sort' => 'asc'),
    array('data' => t('Subscription'), 'field' => 'stype', 'sort' => 'asc'),
    array('data' => ''),
  );
  
  $subscriber_types = elobbyist_subscriber_types();

	//Create the Sql query
	$results = elobbyist_contacts_grid_data('subscriber', $header);

  //go through resultset
	$rows = array();
  if ($results) {
    foreach ($results as $row) {
      $rows[] = array(
            'data' => array(
                l($row->name, 'elobbyist/contact/'. $row->cid .'/edit'),
                $row->email,
                $row->provider_name,
                empty($row->stype) ? '' : $subscriber_types[$row->stype],
                l(t('Edit'), 'elobbyist/contact/'. $row->cid .'/edit') . '&nbsp;&nbsp;' .
                l(t('Delete'), 'elobbyist/contact/'. $row->cid .'/delete'),
            )
      );
    }
  }
	
	//Theme the html table
	$html = l(t('Add new subscriber'), 'elobbyist/subscribers/add/subscriber') .
    theme('table', 
				array(
					'header' => $header,
					'rows'=>$rows,
					'sticky' => TRUE,
					'empty' => t('No records.'),
				)
			);
	
	//Append pager
	$html .= theme('pager',
				array(
					'tags' => array()
				)
			);
			
	return ($html);
}

/*
 * Display list of recipients
 */
function elobbyist_recipients_grid() {
  //Create a list of headers for sorting
	$header = array( 
    array('data' => t('Full Name'), 'field' => 'name', 'sort' => 'asc'),
    array('data' => t('Email'), 'field' => 'email', 'sort' => 'asc'),
    array('data' => ''),
  );
  
	$results = elobbyist_contacts_grid_data('recipient', $header);

  //go through resultset
	$rows = array();
  if ($results) {
    foreach ($results as $row) {
      $rows[] = array(
            'data' => array(
                l($row->name, 'elobbyist/contact/'. $row->cid .'/edit'),
                $row->email,
                l(t('Edit'), 'elobbyist/contact/'. $row->cid .'/edit'). '&nbsp;&nbsp;' .
                l(t('Delete'), 'elobbyist/contact/'. $row->cid .'/delete'),
            )
      );
    }
  }
  	
	//Theme the html table
	$html = l(t('Add new recipient'), 'elobbyist/recipients/add/recipient') .
    theme('table', 
				array(
					'header' => $header,
					'rows'=>$rows,
					'sticky' => TRUE,
					'empty' => t('No records.'),
				)
			);
	
	//Append pager
	$html .= theme('pager',
				array(
					'tags' => array()
				)
			);
			
	return $html;
  
}

function elobbyist_contacts_grid_data($type, &$header) {  
  //invoke hook_elobbyist_contact_grid to allow a different data source
  //example of how the module could be extended to use CRM modules
  /*$results = module_invoke_all('elobbyist_contact_rows', $header, array('type' => $type));

  if ($results)
    return $results;*/
  
  //Create the Sql query
	$query = db_select('elobbyist_contact', 'c');
  
  $provider_alias = 'p';
  
  if ($type == 'subscriber') {
    $provider_alias = $query->leftJoin('elobbyist_email_provider' ,$provider_alias, '%alias.providerid = c.providerid');
  }

	$query = $query->condition('type', $type)
				->extend('PagerDefault') 	//Pager Extender
					->limit(variable_get('elobbyist_records_per_page', ELOBBYIST_DEFAULT_RECORDS_PER_PAGE))				//results per page
				->extend('TableSort')		//Sorting Extender
					->orderByHeader($header);//Field to sort on is picked from $header
  
  $query = $query->fields ('c', array (
                'cid',
                'name',
                'email',
              )
          );
  
  if ($type == 'subscriber') {    
    $query->addField('c', 'stype');
    $query->addField($provider_alias, 'name', 'provider_name');
  }
	
	return $query->execute();
}