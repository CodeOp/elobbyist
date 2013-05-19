<?php

/*
 * Settings page
 * 
 * To add a new setting:
 * 1. Add it as a form element to elobbyist_settings_form
 * 2. Add a line to elobbyist_settings_restore
 * 3. Don't forget to implement the use of the setting in the relavant places
 * 
 * The rest should work automatically!
 */

function elobbyist_settings_form() {  
  
  $form['notifications'] = array(
    '#type' => 'fieldset',
    '#title' => t('Notifications'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => -20,
    '#description' => t('Notifications sent to subscribers by the site\'s cron job on each email sent on their behalf. Subscription to notifications is controlled by the subscriber\'s Notify field.'),
  );
  
  $form['notifications']['elobbyist_sender_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Sender Email'),
    '#default_value' => variable_get('elobbyist_sender_email'),
    '#weight' => 0,
    '#maxlength' => 254,
    '#size' => 50,
    '#required' => FALSE,
    '#rules' => array('email'),
    '#description' => t('The email account the notifications will be sent from.'),
  );
  
  $form['notifications']['elobbyist_sender_pass'] = array(
      '#type' => 'password',
      '#title' => t('Sender Password'),
      //never send back the password, so no default_value
      '#default_value' => '',
      '#weight' => 4,
      '#maxlength' => 64,
      '#size' => 50,
      '#description' => t('Email account password.'),
      );
  
  $form['notifications']['elobbyist_sender_providerid'] = array(
      '#type' => 'select',
      '#key_type' => 'associative',
      '#title' => t('Email Provider'),
      '#options' => array('' => '') + elobbyist_get_email_providers(),
      '#default_value' => variable_get('elobbyist_sender_providerid'),
      '#weight' => 5,
      '#description' => t('Email provider for the sender.'),
      '#required' => FALSE,
    );
  
  $form['notifications']['elobbyist_notify_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Notification Subject'),
    '#size' => 100,
    '#max_length' => 255,
    '#default_value' => elobbyist_get_notify_subject(),
    '#description' => t('The subject of the notification email that is sent to a sender that is to be notified on each mail sent. Use [elobbyist:subject] to include the subject of the sent email.'),
    '#weight' => 10,
  );
  
  $form['notifications']['elobbyist_notify_body'] = array(
    '#type' => 'text_format',
    '#title' => t('Notification Body'),
    '#default_value' => elobbyist_get_notify_body(),
    '#weight' => 20,
    '#description' => t('The body of the notification email that is sent to a sender that is to be notified on each mail sent. <br/>
     Allowed tokens: <br/>[elobbyist:body] - original message body <br/>
     [elobbyist:recipients] - recipients names <br/>
     [elobbyist:recipients emails] - recipients email addresses <br/>
     [elobbyist:unsubscribe] - link to stop notifications <br/>
     [elobbyist:subscribe] - link to subscribe to notifications <br/>
     [elobbyist:signup] - link to sign up to all mailings <br/>
     [elobbyist:remove] - link to remove subscription/participation in all mailings <br/>
     Note: these links will only work if the appropriate permissions were granted to the anonymous user role (by default they are granted).'),
    '#required' => TRUE,
  );

  $form['defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default form values'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => 0,
    '#tree' => TRUE,
  );

  $form['defaults']['elobbyist_smtp_port_default'] = array(
    '#type' => 'textfield',
    '#title' => t('SMTP port'),
    '#size' => 5,
    '#max_length' => 5,
    '#default_value' => variable_get('elobbyist_smtp_port_default', ELOBBYIST_DEFAULT_SMTP_PORT),
    '#description' => t('Email Provider form'),
    '#weight' => 0,
    '#rules' => array(
      array(
        'rule' => 'regexp[/^[1-9]\d{0,4}$/]',
        'error' => t('Enter an up to 5-digit positive number for %field.')
        ),
    ),
  );

  $form['defaults']['elobbyist_notify_default_public'] = array(
    '#type' => 'checkbox',
    '#title' => t('Notify on Emails Sent'),
    '#default_value' => variable_get('elobbyist_notify_default_public', ELOBBYIST_DEFAULT_NOTIFY_ON_EMAILS_SENT_FOR_PUBLIC_FORM),
    '#description' => t('Subscriber\'s public form'),
    '#weight' => 5,
  );
  
  
  $form['defaults']['elobbyist_notify_default_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Notify on Emails Sent'),
    '#default_value' => variable_get('elobbyist_notify_default_admin', ELOBBYIST_DEFAULT_NOTIFY_ON_EMAILS_SENT_FOR_ADMIN_FORM),
    '#description' => t('Subscriber\'s admin form'),
    '#weight' => 5,
  );
  
  $form['elobbyist_max_emails_per_batch'] = array(
    '#type' => 'textfield',
    '#title' => t('Max emails per batch'),
    '#size' => 7,
    '#max_length' => 7,
    '#default_value' => variable_get('elobbyist_max_emails_per_batch', ELOBBYIST_DEFAULT_MAX_EMAILS_PER_BATCH),
    '#description' => t('After this number of emails the cron job stops, even if a mailing wasn\'t completely processed. The next cron job run proceeds from the same place the previous one has stopped. Zero means all mailings are always processed in whole.'),
    '#required' => TRUE,
    '#weight' => 3,
    '#rules' => array(
      array(
        'rule' => 'regexp[/^\d{0,7}$/]',
        'error' => t('Enter an up to 7-digit number for %field.')
        ),
    ),
  );
  
  $form['elobbyist_max_bounces'] = array(
    '#type' => 'textfield',
    '#title' => t('Max Bounces'),
    '#size' => 4,
    '#max_length' => 4,
    '#default_value' => variable_get('elobbyist_max_bounces', ELOBBYIST_DEFAULT_MAX_BOUNCES),
    '#description' => t('After this number of sends an email account will be ignored, unless the contact\'s Email Status is changed manually to \'Unverified\' - in which case the count will be reset. Set to zero to never ignore bouncing email accounts.'),
    '#required' => TRUE,
    '#weight' => 5,
    '#rules' => array(
      array(
        'rule' => 'regexp[/^\d{1,3}$/]',
        'error' => t('Enter an up to 3-digit number for %field.')
        ),
    ),
  );
  
  $form['elobbyist_records_per_page'] = array(
    '#type' => 'select',
    '#title' => t('Records per page'),
    '#default_value' => variable_get('elobbyist_records_per_page', ELOBBYIST_DEFAULT_RECORDS_PER_PAGE),
    '#options' => elobbyist_config_records_per_page_options(),
    '#description' => t('Records per page to display on grids/tables.'),
    '#required' => TRUE,
    '#weight' => 10,
  );

  $form['elobbyist_main_menu_weight'] = array(
    '#type' => 'textfield',
    '#title' => t('Main menu weight'),
    '#default_value' => variable_get('elobbyist_main_menu_weight', ELOBBYIST_DEFAULT_MAIN_MENU_WEIGHT),
    '#size' => 4,
    '#max_length' => 4,
    '#description' => t('Sets the location of the Email Lobbyist main menu inside Drupal\'s menu toolbar. 
      Clearing Drupal\'s cache after save is required for the setting to take effect.'),
    '#required' => TRUE,
    '#weight' => 50,
    '#rules' => array(
      array(
        'rule' => 'regexp[/^-?\d{1,3}$/]',
        'error' => t('Enter an up to 3-digit number for %field.')
        ),
    ),
  );

  $form['actions'] = array();
  $form['actions']['#type'] = 'actions';

  $form['actions']['submit'] = array(
    '#type' => 'submit', 
    '#submit' => array('elobbyist_settings_form_submit'),
    '#value' => t('Save configuration')
  );

  $form['actions']['restore'] = array(
    '#type' => 'submit', 
    '#submit' => array('elobbyist_settings_form_restore_submit'),
    '#value' => t('Restore defaults'),
    '#limit_validation_errors' => array(),       // No validation.
  );

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }

  //render the form using theme_system_settings_form().
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }

  return $form;
}



/**
* Implements validation from the Form API.
*
* @param $form
*   A structured array containing the elements and properties of the form.
* @param $form_state
*   An array that stores information about the form's current state
*   during processing.
*/
function elobbyist_settings_form_validate($form, &$form_state){
  
}

/**
 * Submits the settings form.
 *
 */
function elobbyist_settings_form_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  form_state_values_clean($form_state);

  elobbyist_settings_form_set_values($form_state['values']);

  drupal_set_message(t('The configuration options have been saved.'));
}

/*
 * Handles settings save, including inside fieldsets (by recurse)
 * 
 * Since this is an admin form, it's ok to pass arrays by value as is the PHP default behaviour
 */
function elobbyist_settings_form_set_values($values) {
  foreach ($values as $key => $value) {
    switch($key) {
      case 'elobbyist_notify_body':
        variable_set($key, $value['value']);
        break;
      case 'elobbyist_sender_pass':
        if (empty($value))
          continue; //don't delete password when not entered
        else { 
          ////encrypt password
          variable_set($key, encrypt($value, array('base64' => TRUE)));
        }
        break;
      default:
        if (is_array($value)) {
          elobbyist_settings_form_set_values($value);
        }
        //make sure only intended values are saved
        else if (strpos($key, 'elobbyist_') === 0) {
          variable_set($key, $value);
        }
        break;
    }
  }
}

/*
 * Restore functions
 */
function elobbyist_settings_form_restore_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  
  $form_state['redirect'] = array('admin/config/administration/elobbyist/restore',
    array('query' => $destination));
}

function elobbyist_settings_restore_confirm($form, &$form_state) {
  return confirm_form($form, 
    t('Are you sure you want to restore default settings for the module Email Lobbyist?'),
    'admin/config/administration/elobbyist',
    t('This action cannot be undone'),
    t('Restore'),
    t('Cancel')
  );
}

function elobbyist_settings_restore_confirm_submit($form, &$form_state) {

  elobbyist_settings_restore();
  
  drupal_set_message(t('The configuration options have been restored.'));
  
  $form_state['redirect'] = array('admin/config/administration/elobbyist');
}

function elobbyist_config_records_per_page_options() {
  return array( 
      5 => 5,
      10 => 10,
      ELOBBYIST_DEFAULT_RECORDS_PER_PAGE => ELOBBYIST_DEFAULT_RECORDS_PER_PAGE,
      50 => 50,
      100 => 100,
      150 => 150,
      200 => 200,
      250 => 250,
      500 => 500,
  );
}