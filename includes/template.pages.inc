<?php

/**
 * @file
 * Template entity pages callbacks
 */

/**
 * form prepare callback
 */
function elobbyist_template_form($form, &$form_state, $entity) {
  // Set the id to identify this as a record edit form.
  $form['#id'] = 'elobbyist_template-form';
  
  // Save the record for later, in case we need it.
  $form['#elobbyist_template'] = $entity;
  $form_state['elobbyist_template'] = $entity;
  
  // Set fields
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Template Name'),
    '#default_value' => $entity->name,
    '#weight' => -5,
    '#maxlength' => 100,
    '#size' => 83,
    '#required' => TRUE,
  );
  
  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Subject'),
    '#default_value' => $entity->subject,
    '#weight' => 5,
    '#maxlength' => 500,
    '#size' => 83,
    '#required' => TRUE,
  );
    
  $form['body'] = array(
    '#type' => 'text_format',
    '#title' => t('Email Body'),
    '#default_value' => $entity->body,
    '#weight' => 20,
    '#cols' => 80,
    '#rows' => 10,
    '#required' => TRUE,
  );
  
  $form['status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#default_value' => $entity->status,
    '#weight' => 25,
    '#options' => elobbyist_template_status_list(),
    '#required' => TRUE,
  );
  
  //Add the buttons
  $form['buttons'] = array();
  $form['buttons']['#weight'] = 100;
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
    '#submit' => array('elobbyist_template_form_submit'),
  );
  
  if (!empty($entity->tid)) {
    $form['buttons']['delete'] = array(
      '#access' => user_access('delete email lobbyist templates'),
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 120,
      '#submit' => array('elobbyist_template_form_delete_submit'),
      '#limit_validation_errors' => array(),       // No validation.
    );
  }
  
  $form['#validate'][] = 'elobbyist_template_form_validate';
  
  field_attach_form('elobbyist_template', $entity, $form, $form_state);
  
  return $form;
}

function elobbyist_template_status_list() {
  return array(
    ELOBBYIST_TEMPLATE_STATUS_DRAFT => t('Draft'),
    ELOBBYIST_TEMPLATE_STATUS_ACTIVE => t('Active'),
    ELOBBYIST_TEMPLATE_STATUS_CLOSED => t('Closed'),
    ELOBBYIST_TEMPLATE_STATUS_CANCELLED => t('Cancelled'),
  );
}

/**
 * Validate form
 */
function elobbyist_template_form_validate($form, &$form_state) {
  $entity = $form_state['elobbyist_template']; 
  
  //Field validation
  field_attach_form_validate('elobbyist_template', $entity, $form, $form_state);
}

/**
 * Save functions
 */
function elobbyist_template_form_submit($form, &$form_state) {
  global $user;
  
  $entity = $form_state['elobbyist_template'];
  
  $entity->name = $form_state['values']['name'];
  $entity->subject = $form_state['values']['subject'];
  $entity->body = $form_state['values']['body']['value'];
  $entity->status = $form_state['values']['status'];
    
  // Notify field widgets.
  field_attach_submit('elobbyist_template', $entity, $form, $form_state);
  
  $new_record = empty($entity->tid);
  
  // Save the record.
  $entity = elobbyist_template_save($entity);
  
  // Notify the user.
  if ($entity) {
    drupal_set_message(t('Template saved.'));
    
    if ($new_record) {
      $form_state['redirect'] = 'elobbyist/template/' . $entity->tid . '/edit';
    }
  }
}

function elobbyist_template_save($entity) {
  return entity_get_controller('elobbyist_template')->save($entity);
}

/*
 * Delete functions
 */
function elobbyist_template_delete_confirm($form, &$form_state, $entity) {
  $form['#elobbyist_template'] = $entity;
  
  $form['tid'] = array('#type' => 'value', '#value' => $entity->tid);
  return confirm_form($form, 
    t('Are you sure you want to delete %title?',
      array('%title' => $entity->name)),
    'elobbyist/templates',
    t('This action cannot be undone'),
    t('Delete'), 
    t('Cancel')
  );
}
function elobbyist_template_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  
  $entity = $form['#elobbyist_template'];
  $form_state['redirect'] = array('elobbyist/template/' . $entity->tid . '/delete',
    array('query' => $destination));
}

function elobbyist_template_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $entity = elobbyist_template_load($form_state['values']['tid']);
    elobbyist_template_delete($form_state['values']['tid']);
    watchdog('elobbyist_template', 'template deleted %title.' , 
      array('%title' => $entity->name) );
    
    drupal_set_message(t('Template %title has been deleted.', array(
      '%title' => $entity->name)
      )
    );
  }
  
  $form_state['redirect'] = 'elobbyist/templates';
}


/*
 * list templates
 */
function elobbyist_template_grid() {
  //Create a list of headers for sorting
	$header = array( 
    array('data' => t('Template Name'), 'field' => 'name', 'sort' => 'asc'),
    array('data' => t('Subject'), 'field' => 'subject', 'sort' => 'asc'),
    array('data' => t('Status'), 'field' => 'status', 'sort' => 'asc'),
    array('data' => ''),
  );
  
  $statuses = elobbyist_template_status_list();

	//Create the Sql query
	$query = db_select('elobbyist_template', 'p')
				->extend('PagerDefault') 	//Pager Extender
					->limit(variable_get('elobbyist_records_per_page', ELOBBYIST_DEFAULT_RECORDS_PER_PAGE))				//results per page
				->extend('TableSort')		//Sorting Extender
					->orderByHeader($header)//Field to sort on is picked from $header
				->fields ('p', array (
                'tid',
                'name',
                'subject',
                'status',
              )
          );
	
	$results = $query->execute();

  //go through resultset
	$rows = array();	
	foreach ($results as $row) {
		$rows[] = array(
					'data' => array(
						  l($row->name, 'elobbyist/template/'. $row->tid .'/edit'),
						  $row->subject,
						  $statuses[$row->status],
              l(t('Edit'), 'elobbyist/template/'. $row->tid .'/edit'). '&nbsp;&nbsp;' .
              l(t('Delete'), 'elobbyist/template/'. $row->tid .'/delete'),
					)
		);
	}
	
	//Theme the html table
	$html = l(t('Add new template'), 'elobbyist/templates/add') .
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
 * Add record page callback
 */
function elobbyist_template_add() { 
  $entity = entity_get_controller('elobbyist_template')->create();
  
  drupal_set_title(t('New Template'), PASS_THROUGH);
  
  return drupal_get_form('elobbyist_template_form', $entity);
}

/*
 * Edit record page callback
 */
function elobbyist_template_page_edit($entity) {
  drupal_set_title(t('Template: @title', array(
    '@title' => $entity->name, )), PASS_THROUGH);
  
  return drupal_get_form('elobbyist_template_form', $entity);
}

