<?php

/*
 * Implements hook_rules_action_info
 */
function elobbyist_rules_action_info() {
  return array(
    'elobbyist_rule_remove_contacts_add_var' => array(
      'label' => t('Add group variable from url'),
      'provides' => array(
        'grpid' => array(
          'type' => 'integer',
          'label' => t('Group ID'),
        ),
      ),
      'group' => t('Email Lobbyist'),
    ),
    'elobbyist_rule_remove_contacts' => array(
      'label' => t('Remove Contacts from Group'),
      'parameter' => array(
        //must have first parameter as entity, to integrate with VBO
        'contacts' => array('type' => 'list<entity>', 'label' => t('Contacts')),
        'grpid' => array('type' => 'integer', 'label' => t('Group ID')),
      ),
      'group' => t('Email Lobbyist'),
      'access callback' => 'elobbyist_rule_remove_contacts_access',
    ),
    'elobbyist_rule_add_contacts' => array(
      'label' => t('Add Contacts to Group'),
      'parameter' => array(
        //must have first parameter as entity, to integrate with VBO
        'contacts' => array('type' => 'list<entity>', 'label' => t('Contacts')),
        'grpid' => array('type' => 'integer', 'label' => t('Group Id')),
      ),
      'group' => t('Email Lobbyist'),
      'access callback' => 'elobbyist_rule_add_contacts_access',
    ),
  );
}

function elobbyist_rule_remove_contacts_add_var($args, $element) {
  //return the group id for group member paths
  return array('grpid' => arg(2));
}

/*
 * Callback for elobbyist_rule_remove_contact
 * 
 */
function elobbyist_rule_remove_contacts($contacts, $grpid) {
  //get relations for contact-group combinatios
  $query = relation_query('elobbyist_group', $grpid);
  $query->fieldCondition('endpoints', 'entity_type', 'elobbyist_contact', '=');
  $query->fieldCondition('endpoints', 'entity_id', array_keys($contacts), 'IN');

  $relations = array_keys($query->execute());
  
  foreach($relations as $rid) {
    relation_delete($rid);
  }
}

/**
 * access callback for elobbyist_rule_remove_contact
 */
function elobbyist_rule_remove_contacts_access($type, $name) {
  return entity_access('update', 'elobbyist_contact');
}

function elobbyist_rule_add_contacts($contacts, $grpid) {  
  foreach($contacts as $cid => $contact) {
    if ($contact->type == 'subscriber') {
      elobbyist_relations_create('elobbyist_contact', $cid, 'elobbyist_group', $grpid,
            'elobbyist_subscriber');
    }
    else {
      elobbyist_relations_create('elobbyist_contact', $cid, 'elobbyist_group', $grpid,
            'elobbyist_recipient');
    }
  }
}

function elobbyist_rule_add_contacts_access($type, $name) {
  return entity_access('update', 'elobbyist_contact');
}