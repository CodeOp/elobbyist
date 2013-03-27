<?php

/**
 * @file
 * Contact group entity pages callbacks
 */

/*
 * forms callback
 */
function elobbyist_contact_group_form($form, &$form_state, $entity) {
  // Set the id to identify this as a contact edit form.
  $form['#id'] = 'elobbyist_contact_group-form';
  
  // Save the contact for later, in case we need it.
  $form['#elobbyist_contact_group'] = $entity;
  $form_state['elobbyist_contact_group'] = $entity;
  
  $new_record = empty($entity->grpid);
  
  // Set fields
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Group Name'),
    '#default_value' => $entity->name,
    '#weight' => -5,
    '#maxlength' => 100,
    '#size' => 50,
    '#required' => TRUE,
  );
  
  //Add the buttons
  $form['buttons'] = array();
  $form['buttons']['#weight'] = 100;
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
    '#submit' => array('elobbyist_contact_group_form_submit'),
  );
  
  if (!$new_record) {
    $form['buttons']['delete'] = array(
      '#access' => user_access('delete email lobbyist contact groups'),
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 120,
      '#submit' => array('elobbyist_contact_group_form_delete_submit'),
    );
  }
  
  $form['#validate'][] = 'elobbyist_contact_group_form_validate';
  
  field_attach_form('elobbyist_contact_group', $entity, $form, $form_state);
  
  return $form;
}

/*
 * Add record page callback
 */
function elobbyist_contact_group_add($type) {
  $types = elobbyist_contact_group_types();
  $type  = (isset($type) ? str_replace('-', '_', $type) : NULL);
  if (empty($types[$type])) {
    return MENU_NOT_FOUND;
  }
  
  $entity = entity_get_controller('elobbyist_contact_group')->create($type);
      
  drupal_set_title(t('New @name', array('@name' => $types[$type]->name)),
    PASS_THROUGH);
  
  return drupal_get_form('elobbyist_contact_group_form', $entity);
}

/*
 * Edit record page callback
 */
function elobbyist_contact_group_page_edit($entity) {
  $types = elobbyist_contact_group_types();
  drupal_set_title(t('@type: @title', array(
    '@type' => $types[$entity->type]->name,
    '@title' => $entity->name, )), PASS_THROUGH);
  
  return drupal_get_form('elobbyist_contact_group_form', $entity);
}

/*
 * Validate function
 */
function elobbyist_contact_group_form_validate($form, &$form_state) {
  $entity = $form_state['elobbyist_contact_group'];
    
  //Field validation
  field_attach_form_validate('elobbyist_contact_group', $entity, $form, $form_state);
}

/*
 * Save functions
 */
function elobbyist_contact_group_form_submit($form, &$form_state) {
  global $user;
  
  $entity = $form_state['elobbyist_contact_group'];
  
  $entity->name = $form_state['values']['name'];
        
  // Notify field widgets.
  field_attach_submit('elobbyist_contact_group', $entity, $form, $form_state);
  
  $new_record = empty($entity->grpid);
  
  // Save the contact.
  $entity = elobbyist_contact_group_save($entity);
  
  $types = elobbyist_contact_group_types();
  
  // Notify the user.
  if ($entity) {
    drupal_set_message(t('@name saved.',array( '@name' => $types[$entity->type]->name)));
    
    if ($new_record) {
      $form_state['redirect'] = 'elobbyist/contact-group/' . $entity->grpid . '/edit';
    }
  }
}

function elobbyist_contact_group_save($entity) {
  //invoke hook_elobbyist_contact_save_alter
  $cloned = clone $entity;
  $continue = TRUE;
    
  drupal_alter('elobbyist_contact_group_save', $cloned, $continue);
  
  if ($continue)
    return entity_get_controller('elobbyist_contact_group')->save($entity);
  
  //allow to modify grpid for new records
  if (empty($entity->grpid))
    $entity->grpid = check_url($cloned->grpid);
  
  return $entity;
}


/*
 * Delete functions
 */
function elobbyist_contact_group_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  
  $entity = $form['#elobbyist_contact_group'];
  $form_state['redirect'] = array('elobbyist/contact-group/' . $entity->grpid . '/delete',
    array('query' => $destination));
}
function elobbyist_contact_group_delete_confirm($form, &$form_state, $entity) {
  $form['#elobbyist_contact_group'] = $entity;
  
  $path = 'elobbyist/' . $entity->type . '/groups';

  // Always provide entity id in the same form key as in the entity edit form.
  $form['grpid'] = array('#type' => 'value', '#value' => $entity->grpid);
  return confirm_form($form, 
    t('Are you sure you want to delete %title?',
      array('%title' => $entity->name)),
    $path,
    t('This action cannot be undone'),
    t('Delete'), 
    t('Cancel')
  );
}
function elobbyist_contact_group_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $entity = elobbyist_contact_group_load($form_state['values']['grpid']);
    
    $path = 'elobbyist/' . $entity->type . '/groups';
    
    elobbyist_contact_group_delete($form_state['values']['grpid']);
    
    watchdog('elobbyist_contact_group', '@type: deleted %title.' , array('@type' => 
      $entity->type, '%title' => $entity->name) );
    
    $types = elobbyist_contact_group_types();
    drupal_set_message(t('@type %title has been deleted.', array(
      '@type' => $types[$entity->type]->name,
      '%title' => $entity->name)
      )
    );
    
    $form_state['redirect'] = $path;
  }
}

function elobbyist_contact_group_delete($grpid) {
  elobbyist_contact_group_delete_multiple(array($grpid));
}

function elobbyist_contact_group_delete_multiple($ids) {

  //invoke hook_elobbyist_contact_delete
  $continue = module_invoke_all('elobbyist_contact_group_delete', $ids);
  
  if ($continue !== FALSE)
    return entity_get_controller('elobbyist_contact_group')->delete($ids);
  
  return FALSE; //return false when delete was not made by entity_get_controller
}

/*
 * Display list of subscribers
 */
function elobbyist_contacts_groups_grid($type) {
 
  //Create a list of headers for sorting
	$header = array( array('data' => t('Group Name'), 'field' => 'name', 'sort' => 'asc')	);
  
  $types = elobbyist_contact_group_types();
  
  //change default "Groups" title provided by menu
  drupal_set_title($types[$type]->plural);
  
	//Create the Sql query
	$results = elobbyist_contacts_groups_grid_data($type, $header);

  //go through resultset
	$rows = array();
  if ($results) {
    foreach ($results as $row) {
      $rows[] = array(
            'data' => array(
                l($row->name, 'elobbyist/contact-group/'. $row->grpid .'/edit'),
                l(t('Edit'), 'elobbyist/contact-group/'. $row->grpid .'/edit') . '&nbsp;&nbsp;' .
                l(t('Delete'), 'elobbyist/contact-group/'. $row->grpid .'/delete'),
            )
      );
    }
  }
  
  //Complete list of headers for theming
  $header[] = array('data' => '');
	
	//Theme the html table
	$html = l(t('Add new group'), 'elobbyist/' . $type . '/groups/add') .
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

function elobbyist_contacts_groups_grid_data($type, &$header) {  
  //invoke hook_elobbyist_contact_grid to allow a different data source
  $results = module_invoke_all('elobbyist_contact_group_rows', $header, array('type' => $type));

  if ($results)
    return $results;
  
  //Create the Sql query
	$query = db_select('elobbyist_contact_group', 'cg');
  
	$query = $query->condition('type', $type)
				->extend('PagerDefault') 	//Pager Extender
					->limit(25)				//results per page
				->extend('TableSort')		//Sorting Extender
					->orderByHeader($header);//Field to sort on is picked from $header
  
  $query = $query->fields ('cg', array (
                'grpid',
                'name',
              )
          );
  	
	return $query->execute();
}