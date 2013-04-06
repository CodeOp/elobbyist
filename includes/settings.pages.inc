<?php

function elobbyist_settings_form() {
  $form['elobbyist_records_per_page'] = array(
    '#type' => 'select',
    '#title' => t('Records per page'),
    '#default_value' => variable_get('elobbyist_records_per_page', ELOBBYIST_DEFAULT_RECORDS_PER_PAGE),
    '#options' => elobbyist_config_records_per_page_options(),
    '#description' => t('Records per page to display on grids/tables.'),
    '#required' => TRUE,
    '#weight' => -50,
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
  
  $form['defaults']['elobbyist_notify_default_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Notify on Emails Sent'),
    '#default_value' => variable_get('elobbyist_notify_default_admin', ELOBBYIST_DEFAULT_NOTIFY_ON_EMAILS_SENT_FOR_ADMIN_FORM),
    '#description' => t('Subscriber\'s admin form'),
    '#weight' => 5,
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

/*
 * Restores default settings (by deleting saved ones)
 * 
 * This function is placed higher than other restore functions, because it should be
 * modified for each added setting
 */
function elobbyist_settings_restore() {
  variable_del('elobbyist_records_per_page');
  variable_del('elobbyist_smtp_port_default');
  variable_del('elobbyist_notify_default_admin');
  variable_del('elobbyist_main_menu_weight');
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
    if (is_array($value)) {
      elobbyist_settings_form_set_values($value);
    }
    //make sure only intended values are saved
    else if (strpos($key, 'elobbyist_') === 0) {
      variable_set($key, $value);
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