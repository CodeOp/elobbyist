<?php

/**
 * @file
 * Contact group entity pages callbacks
 */

/*
 * forms callback
 */
function elobbyist_group_form($form, &$form_state, $entity) {
  // Set the id to identify this as a contact edit form.
  $form['#id'] = 'elobbyist_group-form';
  
  // Save the contact for later, in case we need it.
  $form['#elobbyist_group'] = $entity;
  $form_state['elobbyist_group'] = $entity;
  
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
  
  $form['status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#default_value' => $entity->status,
    '#weight' => 5,
    '#options' => elobbyist_group_status_list(),
    '#required' => TRUE,
    '#description' => t('Incative groups do not send or receive emails and cannot be selected, but preserve their current relations'),
  );
  
  //Add the buttons
  $form['buttons'] = array();
  $form['buttons']['#weight'] = 100;
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
    '#submit' => array('elobbyist_group_form_submit'),
  );
  
  if (!$new_record) {
    $form['buttons']['delete'] = array(
      '#access' => user_access('delete email lobbyist contact groups'),
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 120,
      '#submit' => array('elobbyist_group_form_delete_submit'),
      '#limit_validation_errors' => array(),       // No validation.
    );
  }
  
  $form['#validate'][] = 'elobbyist_group_form_validate';
  
  field_attach_form('elobbyist_group', $entity, $form, $form_state);
  
  return $form;
}


/*
 * Add record page callback
 */
function elobbyist_group_add($type) {
  $types = elobbyist_group_types();
  $type  = (isset($type) ? str_replace('-', '_', $type) : NULL);
  if (empty($types[$type])) {
    return MENU_NOT_FOUND;
  }
  
  $entity = entity_get_controller('elobbyist_group')->create($type);
      
  drupal_set_title(t('New @name', array('@name' => $types[$type]->name)),
    PASS_THROUGH);
  
  return drupal_get_form('elobbyist_group_form', $entity);
}

/*
 * Edit record page callback
 */
function elobbyist_group_page_edit($entity) {
  elobbyist_group_page_title($entity);
  
  return drupal_get_form('elobbyist_group_form', $entity);
}

function elobbyist_group_page_view($entity, $view_mode = 'full') {
  elobbyist_group_page_title($entity);
  
  // Remove previously built content, if exists.
  $entity->content = array();
  
  $entity->content['#attached']['css'] = array(
    drupal_get_path('module', 'elobbyist') . '/includes/elobbyist.css',
  );
  
  if (!empty($entity->status)) {
    $statuses = elobbyist_group_status_list();
    $entity->content['status'] = array(
      '#markup' => theme('elobbyist_field',
          array(
            'title' => t('Status'),
            'item' => $statuses[$entity->status],
          )
       ),
      '#weight' => -30,
    );
  }

  // Build fields content.
  field_attach_prepare_view('elobbyist_group', 
    array($entity->grpid => $entity), $view_mode);
  
  entity_prepare_view('elobbyist_group', array($entity->grpid => $entity));
  
  $entity->content += field_attach_view('elobbyist_group', $entity, $view_mode);
  
  return $entity->content;
}

function elobbyist_group_page_title($entity) {
  $types = elobbyist_group_types();
  drupal_set_title(t('@type: @title', array(
    '@type' => $types[$entity->type]->name,
    '@title' => $entity->name, )), PASS_THROUGH);
}

/*
 * Validate function
 */
function elobbyist_group_form_validate($form, &$form_state) {
  $entity = $form_state['elobbyist_group'];
    
  //Field validation
  field_attach_form_validate('elobbyist_group', $entity, $form, $form_state);
}

/*
 * Save functions
 */
function elobbyist_group_form_submit($form, &$form_state) {
  global $user;
  
  $entity = $form_state['elobbyist_group'];
  
  $entity->name = $form_state['values']['name'];
  $entity->status = $form_state['values']['status'];

  // Notify field widgets.
  field_attach_submit('elobbyist_group', $entity, $form, $form_state);
  
  $new_record = empty($entity->grpid);
  
  // Save the contact.
  $entity = elobbyist_group_save($entity);
  
  $types = elobbyist_group_types();
  
  // Notify the user.
  if ($entity) {
    drupal_set_message(t('@name saved.',array( '@name' => $types[$entity->type]->name)));
    
    if ($new_record) {
      $form_state['redirect'] = 'elobbyist/contact-group/' . $entity->grpid . '/edit';
    }
  }
}

function elobbyist_group_save($entity) {
  //invoke hook_elobbyist_contact_save_alter
  $cloned = clone $entity;
  $continue = TRUE;
    
  drupal_alter('elobbyist_group_save', $cloned, $continue);
  
  if ($continue)
    return entity_get_controller('elobbyist_group')->save($entity);
  
  //allow to modify grpid for new records
  if (empty($entity->grpid))
    $entity->grpid = check_url($cloned->grpid);
  
  return $entity;
}


/*
 * Delete functions
 */
function elobbyist_group_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  
  $entity = $form['#elobbyist_group'];
  $form_state['redirect'] = array('elobbyist/contact-group/' . $entity->grpid . '/delete',
    array('query' => $destination));
}
function elobbyist_group_delete_confirm($form, &$form_state, $entity) {
  $form['#elobbyist_group'] = $entity;
  
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
function elobbyist_group_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $entity = elobbyist_group_load($form_state['values']['grpid']);
    
    $path = 'elobbyist/' . $entity->type . '/groups';
    
    elobbyist_group_delete($form_state['values']['grpid']);
    
    watchdog('elobbyist_group', '@type: deleted %title.' , array('@type' => 
      $entity->type, '%title' => $entity->name) );
    
    $types = elobbyist_group_types();
    drupal_set_message(t('@type %title has been deleted.', array(
      '@type' => $types[$entity->type]->name,
      '%title' => $entity->name)
      )
    );
    
    $form_state['redirect'] = $path;
  }
}

/*
 * Display list of groups
 */
function elobbyist_contacts_groups_grid($type) {
 
  //Create a list of headers for sorting
	$header = array( 
    array('data' => t('Group Name'), 'field' => 'name', 'sort' => 'asc'),
    array('data' => t('Status'), 'field' => 'status', 'sort' => 'asc'),
    array('data' => ''),
  );
  
  $types = elobbyist_group_types();
  
  $statuses = elobbyist_group_status_list();
  
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
                $statuses[$row->status],
                l(t('Edit'), 'elobbyist/contact-group/'. $row->grpid .'/edit') . '&nbsp;&nbsp;' .
                l(t('Delete'), 'elobbyist/contact-group/'. $row->grpid .'/delete'),
            )
      );
    }
  }
	
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


/*
 * Display list of a group members
 */
function elobbyist_group_contacts_grid($entity) {
 
  //Create a list of headers for sorting
	$header = array( 
              array('data' => t('Full Name'), 'field' => 'name', 'sort' => 'asc')	,
              array('data' => t('Email'), 'field' => 'email', 'sort' => 'asc'),
  );
      
  $subscriber_types = null;
  $email_statuses = null;
  if ($entity->type == 'subscribers') {
    $header[] = array('data' => t('Status'), 'field' => 'bounce', 'sort' => 'asc');
    $header[] = array('data' => t('Subscription'), 'field' => 'stype', 'sort' => 'asc');
    
    $subscriber_types = elobbyist_subscriber_types();
    $email_statuses = elobbyist_email_statuses();
  }
  
  $header[] = array('data' => '');
  
  
  elobbyist_group_page_title($entity);

	//Create the Sql query
	$results = elobbyist_group_contacts_grid_data($entity->grpid);

  $rows = array();
  if ($results) {
    //subscribers
    if (isset($subscriber_types)) {
      foreach ($results as $row) {
        $rows[] = array(
              'data' => array(
                  l($row->name, 'elobbyist/contact/'. $row->cid .'/edit'),
                  $row->email,
                  !isset($row->bounce) ? '' : $email_statuses[$row->bounce],
                  empty($row->stype) ? '' : $subscriber_types[$row->stype],
                  l(t('Edit'), 'elobbyist/contact/'. $row->cid .'/edit'),
              )
        );
      }
    }
    //recipients
    else {
      foreach ($results as $row) {
        $rows[] = array(
              'data' => array(
                  l($row->name, 'elobbyist/contact/'. $row->cid .'/edit'),
                  $row->email,
                  l(t('Edit'), 'elobbyist/contact/'. $row->cid .'/edit'),
              )
        );
      }
    }
  }
	
	//Theme the html table
	$html = theme('table', 
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

function elobbyist_contacts_groups_grid_data($type, &$header) {  
  //invoke hook_elobbyist_contact_grid to allow a different data source
  //example of how the module could be extended to use CRM modules
  /*$results = module_invoke_all('elobbyist_group_rows', $header, array('type' => $type));

  if ($results)
    return $results;*/
  
  //Create the Sql query
	$query = db_select('elobbyist_group', 'cg');
  
	$query = $query->condition('type', $type)
				->extend('PagerDefault') 	//Pager Extender
					->limit(variable_get('elobbyist_records_per_page', ELOBBYIST_DEFAULT_RECORDS_PER_PAGE))				//results per page
				->extend('TableSort')		//Sorting Extender
					->orderByHeader($header);//Field to sort on is picked from $header
  
  $query = $query->fields ('cg', array (
                'grpid',
                'name',
                'status',
              )
          );
  	
	return $query->execute();
}

/*
 * Get contacts by group
 */
function elobbyist_group_contacts_grid_data($grpid) {
  $relations = elobbyist_relations_get_data('elobbyist_group', $grpid);
    
  $cids = array();
    
  foreach($relations as $relation) {
    foreach($relation->endpoints as $endpoints) {
      foreach($endpoints as $endpoint) {
        //add each group endpoint
        if ($endpoint['entity_type'] == 'elobbyist_contact') {
          //load contact
          $cids[] = $endpoint['entity_id'];
        }
      }
    }
  }
  
  return entity_load('elobbyist_contact', $cids);
}