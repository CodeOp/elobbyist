<?php

/*
 * Implements hook_views_data()
 */
function elobbyist_views_data() {
  $data = array();
  $data['elobbyist_activity'] = array(
    'table' => array(
      'base' => array(
        'field' => 'aid',
        'title' => t('Elobbyist Activity'),
        'help' => t('Email Lobbyist email activity'),
        'weight' => 540,
       ),
      'group' => t('Elobbyist Activity'),
    ),
    'aid' => array(
      'title' => t('Activity id'),
      'help' => t('The primary identifier for an email activity.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
        'validate type' => 'aid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'mid' => array(
      'title' => t('Mailing id'),
      'help' => t('mailing id.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => t('Mailing'),
          'lable' => t('Mailing'),
          'base' => 'elobbyist_mailing',
          'base field' => 'mid',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_many_to_one',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'elobbyist_views_handler_filter_mailing',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'tid' => array(
      'title' => t('Template id'),
      'help' => t('template id.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => t('Template'),
          'lable' => t('Template'),
          'base' => 'elobbyist_template',
          'base field' => 'tid',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_many_to_one',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'elobbyist_views_handler_filter_template',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'fromcid' => array(
      'title' => t('From Contact id'),
      'help' => t('Contact id.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => t('From'),
          'lable' => t('From'),
          'base' => 'elobbyist_contact',
          'base field' => 'cid',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_many_to_one',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'elobbyist_views_handler_filter_contact',
        'contact type' => 'subscriber',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'tocid' => array(
      'title' => t('To Contact id'),
      'help' => t('Contact id.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => t('To'),
          'lable' => t('To'),
          'base' => 'elobbyist_contact',
          'base field' => 'cid',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_many_to_one',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'elobbyist_views_handler_filter_contact',
        'contact type' => 'recipient',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'created' => array(
      'title' => t('Created'),
      'help' => t('The Unix timestamp when the record was created.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_date',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort_date',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_date',
     ),
    ),
    'view_link' => array(
      'real field' => 'aid',
      'title' => t('View'),
      'help' => t('A view link for the sent email'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/activity/%',
        'link_text' => t('View'),
      ),
    ),
  );
  
  $lstContactFormTypes = elobbyist_form_types();
  $lstContactSubscriberTypes = elobbyist_subscriber_types();
  $lstContactEmailStatuses = elobbyist_email_statuses();
  
  $data['elobbyist_contact'] = array(
    'table' => array(
      'base' => array(
        'field' => 'cid',
        'title' => t('Elobbyist Contact'),
        'help' => t('Email Lobbyist contacts - subscribers and recipients'),
        'weight' => 500,
      ),
      'group' => t('Elobbyist Contact'),
    ),
    'cid' => array(
      'title' => t('Contact id'),
      'help' => t('The primary identifier for a contact.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name field' => 'name', 
        'numeric' => TRUE,
        'validate type' => 'cid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'edit_link' => array(
      'real field' => 'cid',
      'title' => t('Edit'),
      'help' => t('An edit link for the contact'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/contact/%/edit',
        'link_text' => t('Edit'),
        'entity access' => 'update',
      ),
    ),
    'delete_link' => array(
      'real field' => 'cid',
      'title' => t('Delete'),
      'help' => t('A delete link for the contact'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/contact/%/delete',
        'link_text' => t('Delete'),
        'entity access' => 'delete',
      ),
    ),
    'type' => array(
      'title' => t('Type'),
      'help' => t('The contact_type of this contact.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'name' => array(
      'title' => t('Name'),
      'help' => t('The contact full name.'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'id field' => 'cid',
        'url' => 'elobbyist/contact/%/edit',
        'readonly url' => 'elobbyist/contact/%/view',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'email' => array(
      'title' => t('Email'),
      'help' => t('The contact email address.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'form' => array(
      'title' => t('Form'),
      'help' => t('for subscriber - creating form'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => $lstContactFormTypes,
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_in_operator',
        'options callback' => 'elobbyist_views_in_operator_callback',
        'options arguments' => array($lstContactFormTypes),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    
    'stype' => array(
      'title' => t('Subscriber Type'),
      'help' => t('for subscriber - subscription type: persistent or specific-mailing subscriber?'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => $lstContactSubscriberTypes,
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_in_operator',
        'options callback' => 'elobbyist_views_in_operator_callback',
        'options arguments' => array($lstContactSubscriberTypes),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'providerid' => array(
      'title' => t('Provider id'),
      'help' => t('The email provider identifier.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => t('Email Provider'),
          'lable' => t('Email Provider'),
          'base' => 'elobbyist_email_provider',
          'base field' => 'providerid',
        ),
      'argument' => array(
        'handler' => 'views_handler_argument_many_to_one',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'elobbyist_views_handler_filter_email_provider',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'mid' => array(
      'title' => t('Restricted to Mailing id'),
      'help' => t('Restrict to specific mailing.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => t('Restricted to Mailing'),
          'lable' => t('Restricted to Mailing'),
          'base' => 'elobbyist_mailing',
          'base field' => 'mid',
        ),
      'argument' => array(
        'handler' => 'views_handler_argument_many_to_one',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'elobbyist_views_handler_filter_mailing',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'notify' => array(
      'title' => t('Notify'),
      'help' => t('Notify on emails sent.'),
      'field' => array(
        'handler' => 'views_handler_field_boolean',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_boolean_operator',
        'label' => t('Notify on emails'),
        'type' => 'yes-no',
        'use equal' => TRUE, // Use status = 1 instead of status <> 0 in WHERE statment
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    
    'bounce' => array(
      'title' => t('Bounce'),
      'help' => t('bouncing status'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => $lstContactEmailStatuses,
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_in_operator',
        'options callback' => 'elobbyist_views_in_operator_callback',
        'options arguments' => array($lstContactEmailStatuses),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'bounces' => array(
      'title' => t('Bounces'),
      'help' => t('bouncing count'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'created' => array(
      'title' => t('Created'),
      'help' => t('The Unix timestamp when the contact was created.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'argument' => array(
         'handler' => 'views_handler_argument_date',
       ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
    ),
    'changed' => array(
      'title' => t('Changed'),
      'help' => t('The Unix timestamp when the contact was most recently saved.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'argument' => array(
         'handler' => 'views_handler_argument_date',
       ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    ),
  );
  $data['elobbyist_email_provider'] = array(
    'table' => array(
      'base' => array(
        'field' => 'providerid',
        'title' => t('Elobbyist Email Provider'),
        'help' => t('Email Lobbyist email provider'),
        'weight' => 570,
      ),
      'group' => t('Elobbyist Email Provider'),
    ),
    'providerid' => array(
      'title' => t('Provider id'),
      'help' => t('The email provider identifier id.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name field' => 'name', 
        'numeric' => TRUE,
        'validate type' => 'providerid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'name' => array(
      'title' => t('Name'),
      'help' => t('The provider name.'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'click sortable' => TRUE,
        'id field' => 'providerid',
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/email-provider/%/edit',
        'readonly url' => 'elobbyist/email-provider/%/view',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'smtphost' => array(
      'title' => t('Smtp host'),
      'help' => t('The provider smtp server address.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'smtpport' => array(
      'title' => t('Smtp port'),
      'help' => t('The provider smtp server port'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'edit_link' => array(
      'real field' => 'providerid',
      'title' => t('Edit'),
      'help' => t('An edit page link'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/email-provider/%/edit',
        'link_text' => t('Edit'),
        'entity access' => 'update',
      ),
    ),
    'delete_link' => array(
      'real field' => 'providerid',
      'title' => t('Delete'),
      'help' => t('A delete page link'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/email-provider/%/delete',
        'link_text' => t('Delete'),
        'entity access' => 'delete',
      ),
    ),
  );
  
  $lstGroupStatuses = elobbyist_group_status_list();
  
  $data['elobbyist_group'] = array(
    'table' => array(
      'base' => array(
        'field' => 'grpid',
        'title' => t('Elobbyist Group'),
        'help' => t('Email Lobbyist contact group'),
        'weight' => 510,
      ),
      'group' => t('Elobbyist Group'),
    ),
    'grpid' => array(
      'title' => t('Group id'),
      'help' => t('The group id.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name field' => 'name', 
        'numeric' => TRUE,
        'validate type' => 'grpid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'name' => array(
      'title' => t('Name'),
      'help' => t('The group name.'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'id field' => 'grpid',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/contact-group/%/edit',
        'readonly url' => 'elobbyist/contact-group/%/view',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'type' => array(
      'title' => t('Type'),
      'help' => t('The contact_type this group is confined to.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    
    'status' => array(
      'title' => t('Status'),
      'help' => t('group status: Active, Inactive.'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => $lstGroupStatuses,
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_in_operator',
        'options callback' => 'elobbyist_views_in_operator_callback',
        'options arguments' => array($lstGroupStatuses),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'edit_link' => array(
      'real field' => 'grpid',
      'title' => t('Edit'),
      'help' => t('An edit page link'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/contact-group/%/edit',
        'link_text' => t('Edit'),
        'entity access' => 'update',
      ),
    ),
    'delete_link' => array(
      'real field' => 'grpid',
      'title' => t('Delete'),
      'help' => t('A delete page link'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/contact-group/%/delete',
        'link_text' => t('Delete'),
        'entity access' => 'delete',
      ),
    ),
  );
  
  //get array once for both field and filter handlers
  $lstMailingStatuses = elobbyist_mailing_status_list();
  $lstMailingScheduleTypes = elobbyist_mailing_schedule_type_list();
  
  $data['elobbyist_mailing'] = array(
    'table' => array(
      'base' => array(
        'field' => 'mid',
        'title' => t('Elobbyist Mailing'),
        'help' => t('Email Lobbyist mailing'),
        'weight' => 520,
      ),
      'group' => t('Elobbyist Mailing'),
    ),
    'mid' => array(
      'title' => t('Mailing id'),
      'help' => t('The primary identifier for a mailing.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name field' => 'name', 
        'numeric' => TRUE,
        'validate type' => 'mid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'name' => array(
      'title' => t('Name'),
      'help' => t('The mailing name.'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'id field' => 'mid',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/mailing/%/edit',
        'readonly url' => 'elobbyist/mailing/%/view',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'tid' => array(
      'title' => t('Template id'),
      'help' => t('The mailing template.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => t('Template'),
          'lable' => t('Template'),
          'base' => 'elobbyist_template',
          'base field' => 'tid',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_many_to_one',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'elobbyist_views_handler_filter_template',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'schedule' => array(
      'title' => t('Schedule'),
      'help' => t('schedule type.'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => $lstMailingScheduleTypes,
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_in_operator',
        'options callback' => 'elobbyist_views_in_operator_callback',
        'options arguments' => array($lstMailingScheduleTypes),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'status' => array(
      'title' => t('Status'),
      'help' => t('mailing status: Draft, Scheduled, Cancelled, Closed.'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => $lstMailingStatuses,
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_in_operator',
        'options callback' => 'elobbyist_views_in_operator_callback',
        'options arguments' => array($lstMailingStatuses),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'page' => array(
      'title' => t('Page'),
      'help' => t('content of the call to action page'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    ),
    'successurl' => array(
      'title' => t('Success URL'),
      'help' => t('URL to redirect to after a successful public subscription'),
      'field' => array(
        'handler' => 'views_handler_field_url',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'start' => array(
      'title' => t('Start'),
      'help' => t('The Unix timestamp for scheduling start time.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'argument' => array(
         'handler' => 'views_handler_argument_date',
       ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    ),
    'end' => array(
      'title' => t('End'),
      'help' => t('The Unix timestamp for scheduling end time.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'argument' => array(
         'handler' => 'views_handler_argument_date',
       ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    ),
    'addtogrpid' => array(
      'title' => t('Collector Group id'),
      'help' => t('Collects subscribers of on-going schedule type'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => FALSE,
      ),
      'relationship' => array(
          'title' => t('Collector Group'),
          'lable' => t('Collector Group'),
          'base' => 'elobbyist_group',
          'base field' => 'grpid',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_many_to_one',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'elobbyist_views_handler_filter_group',
        'group type' => 'subscribers',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'created' => array(
      'title' => t('Created'),
      'help' => t('The Unix timestamp when the record was created.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'argument' => array(
         'handler' => 'views_handler_argument_date',
       ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
    ),
    'changed' => array(
      'title' => t('Changed'),
      'help' => t('The Unix timestamp when the record was most recently saved.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'argument' => array(
         'handler' => 'views_handler_argument_date',
       ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    ),
    'edit_link' => array(
      'real field' => 'mid',
      'title' => t('Edit'),
      'help' => t('An edit page link'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/mailing/%/edit',
        'link_text' => t('Edit'),
        'entity access' => 'update',
      ),
    ),
    'delete_link' => array(
      'real field' => 'mid',
      'title' => t('Delete'),
      'help' => t('A delete page link'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/mailing/%/delete',
        'link_text' => t('Delete'),
        'entity access' => 'delete',
      ),
    ),
  );
  
  $lstTemplateStatuses = elobbyist_template_status_list();
  
  $data['elobbyist_template'] = array(
    'table' => array(
      'base' => array(
        'field' => 'tid',
        'title' => t('Elobbyist Template'),
        'help' => t('Email Lobbyist template'),
        'weight' => 560,
      ),
      'group' => t('Elobbyist Template'),
    ),
    'tid' => array(
      'title' => t('Template id'),
      'help' => t('The primary identifier for a template.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name field' => 'name', 
        'numeric' => TRUE,
        'validate type' => 'tid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'name' => array(
      'title' => t('Name'),
      'help' => t('The template name.'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'id field' => 'tid',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/template/%/edit',
        'readonly url' => 'elobbyist/template/%/view',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'subject' => array(
      'title' => t('Subject'),
      'help' => t('The email subject.'),
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'id field' => 'tid',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/template/%/edit',
        'readonly url' => 'elobbyist/template/%/view',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'body' => array(
      'title' => t('Body'),
      'help' => t('The email body.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    ),
    'status' => array(
      'title' => t('Status'),
      'help' => 'template status: Draft, Sent, Closed, Cancelled.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => $lstTemplateStatuses,
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_in_operator',
        'options callback' => 'elobbyist_views_in_operator_callback',
        'options arguments' => array($lstTemplateStatuses),
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'edit_link' => array(
      'real field' => 'tid',
      'title' => t('Edit'),
      'help' => 'An edit page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/template/%/edit',
        'link_text' => t('Edit'),
        'entity access' => 'update',
      ),
    ),
    'delete_link' => array(
      'real field' => 'tid',
      'title' => t('Delete'),
      'help' => 'A delete page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/template/%/delete',
        'link_text' => t('Delete'),
        'entity access' => 'delete',
      ),
    ),
  );

  return $data;
}

/*
 * Implements hook_views_default_views
 */
function elobbyist_views_default_views() {
  $views = array();
  
  $items_per_page = variable_get('elobbyist_records_per_page', ELOBBYIST_DEFAULT_RECORDS_PER_PAGE);
  
  //-----------------------
  //----------------------- Subscribers
  //-----------------------
  
  $view = new view();
  $view->name = 'elobbyist_subscribers';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_contact';
  $view->human_name = t('Email Lobbyist Subscribers');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contacts';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'email' => 'email',
    'bounce' => 'bounce',
    'stype' => 'stype',
    'edit_link' => 'edit_link',
//    'delete_link' => 'delete_link',
    'provider_name' => 'provider_name',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'bounce' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'stype' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
   /* 'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),*/
    'provider_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  
  
  /* Field: Bulk operations: Elobbyist Contact */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => t('Delete'),
    ),
    'rules_component::elobbyist_add_contacts_to_group' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
  );
  
  /* Relationship: Elobbyist Contact: Email Provider */
  $handler->display->display_options['relationships']['providerid']['id'] = 'providerid';
  $handler->display->display_options['relationships']['providerid']['table'] = 'elobbyist_contact';
  $handler->display->display_options['relationships']['providerid']['field'] = 'providerid';
  /* Field: Elobbyist Contact: Contact Id */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['exclude'] = TRUE;
  
  /* Field: Elobbyist Contact: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = t('Full Name');
  /* Field: Elobbyist Contact: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  
  /* Field: Elobbyist Email Provider: Provider Id */
  $handler->display->display_options['fields']['providerid']['id'] = 'providerid';
  $handler->display->display_options['fields']['providerid']['table'] = 'elobbyist_email_provider';
  $handler->display->display_options['fields']['providerid']['field'] = 'providerid';
  $handler->display->display_options['fields']['providerid']['relationship'] = 'providerid';
  $handler->display->display_options['fields']['providerid']['exclude'] = TRUE;
  
  /* Field: Elobbyist Email Provider: Name */
  $handler->display->display_options['fields']['provider_name']['id'] = 'provider_name';
  $handler->display->display_options['fields']['provider_name']['table'] = 'elobbyist_email_provider';
  $handler->display->display_options['fields']['provider_name']['field'] = 'name';
  $handler->display->display_options['fields']['provider_name']['relationship'] = 'providerid';
  $handler->display->display_options['fields']['provider_name']['label'] = t('Provider');
  /* Field: Elobbyist Contact: Bounce */
  $handler->display->display_options['fields']['bounce']['id'] = 'bounce';
  $handler->display->display_options['fields']['bounce']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['bounce']['field'] = 'bounce';
  $handler->display->display_options['fields']['bounce']['label'] = t('Status');
  /* Field: Elobbyist Contact: Subscriber Type */
  $handler->display->display_options['fields']['stype']['id'] = 'stype';
  $handler->display->display_options['fields']['stype']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['stype']['field'] = 'stype';
  $handler->display->display_options['fields']['stype']['label'] = t('Subscription');
  /* Field: Elobbyist Contact: Edit */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Field: Elobbyist Contact: Delete */
 /* $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';*/
  /* Filter criterion: Elobbyist Contact: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'elobbyist_contact';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = 'subscriber';
  
  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contacts';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%view_%timestamp-yyyy_%timestamp-mm_%timestamp-dd.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'elobbyist/subscribers/download';

  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Recipients
  //-----------------------
  
  $view = new view();
  $view->name = 'elobbyist_recipients';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_contact';
  $view->human_name = t('Email Lobbyist Recipients');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contacts';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'email' => 'email',
    'edit_link' => 'edit_link',
 //   'delete_link' => 'delete_link',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
   /* 'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),*/
  );
  
  /* Field: Bulk operations: Elobbyist Contact */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => t('Delete'),
    ),
    'rules_component::elobbyist_add_contacts_to_group' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
  );
  
  /* Field: Elobbyist Contact: Contact id */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['exclude'] = TRUE;
  /* Field: Elobbyist Contact: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = t('Full Name');
  /* Field: Elobbyist Contact: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['label'] = t('Email');
  /* Field: Elobbyist Contact: Edit */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Field: Elobbyist Contact: Delete */
 /* $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';*/
  /* Filter criterion: Elobbyist Contact: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'elobbyist_contact';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = 'recipient';
  
  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contacts';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%view_%timestamp-yyyy_%timestamp-mm_%timestamp-dd.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'elobbyist/recipients/download';

  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Subscribers Groups
  //-----------------------
  
  $view = new view();
  $view->name = 'elobbyist_subscribers_groups';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_group';
  $view->human_name = t('Email Lobbyist Subscribers Groups');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contact groups';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'grpid' => 'grpid',
 //   'delete_link' => 'delete_link',
    'edit_link' => 'edit_link',
    'name' => 'name',
    'status' => 'status',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'grpid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
 /*   'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),*/
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  
  
  /* Field: Bulk operations */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => t('Delete'),
    ),
  );
  
  /* Field: Elobbyist Group: Group id */
  $handler->display->display_options['fields']['grpid']['id'] = 'grpid';
  $handler->display->display_options['fields']['grpid']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['grpid']['field'] = 'grpid';
  $handler->display->display_options['fields']['grpid']['exclude'] = TRUE;
  /* Field: Elobbyist Group: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = t('Group Name');
  /* Field: Elobbyist Group: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Elobbyist Group: Edit */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Field: Elobbyist Group: Delete */
 /* $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';*/
  /* Filter criterion: Elobbyist Group: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'elobbyist_group';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = 'subscribers';
  
  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contact groups';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%view_%timestamp-yyyy_%timestamp-mm_%timestamp-dd.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'elobbyist/subscribers/groups/download';

  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Recipients Groups
  //-----------------------
  
  $view = new view();
  $view->name = 'elobbyist_recipients_groups';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_group';
  $view->human_name = t('Email Lobbyist Recipients Groups');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contact groups';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'grpid' => 'grpid',
 //   'delete_link' => 'delete_link',
    'edit_link' => 'edit_link',
    'name' => 'name',
    'status' => 'status',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'grpid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  /*  'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),*/
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  
  /* Field: Bulk operations */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => t('Delete'),
    ),
  );
  
  /* Field: Elobbyist Group: Group id */
  $handler->display->display_options['fields']['grpid']['id'] = 'grpid';
  $handler->display->display_options['fields']['grpid']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['grpid']['field'] = 'grpid';
  $handler->display->display_options['fields']['grpid']['exclude'] = TRUE;
  /* Field: Elobbyist Group: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = t('Group Name');
  /* Field: Elobbyist Group: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Elobbyist Group: Edit */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Field: Elobbyist Group: Delete */
 /* $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'elobbyist_group';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';*/
  /* Filter criterion: Elobbyist Group: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'elobbyist_group';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = 'recipients';
  
  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contact groups';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%view_%timestamp-yyyy_%timestamp-mm_%timestamp-dd.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'elobbyist/recipients/groups/download';

  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Templates
  //-----------------------
  
  $view = new view();
  $view->name = 'elobbyist_templates';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_template';
  $view->human_name = t('Email Lobbyist Templates');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist templates';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'tid' => 'tid',
    'name' => 'name',
    'subject' => 'subject',
    'status' => 'status',
    'edit_link' => 'edit_link',
   // 'delete_link' => 'delete_link',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'tid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'subject' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  /*  'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),*/
  );
  
  /* Field: Bulk operations */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => t('Delete'),
    ),
  );
  
  /* Field: Elobbyist Template: Template id */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  /* Field: Elobbyist Template: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = t('Template Name');
  /* Field: Elobbyist Template: Subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  /* Field: Elobbyist Template: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Elobbyist Template: Edit */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Field: Elobbyist Template: Delete */
 /* $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';*/
  
  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist templates';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%view_%timestamp-yyyy_%timestamp-mm_%timestamp-dd.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'elobbyist/templates/download';

  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Mailings
  //-----------------------  
  
  $view = new view();
  $view->name = 'elobbyist_mailings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_mailing';
  $view->human_name = t('Email Lobbyist Mailings');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist mailings';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'mid' => 'mid',
    'name' => 'name',
    'template_name' => 'template_name',
    'status' => 'status',
    'schedule' => 'schedule',
    'start' => 'start',
    'end' => 'end',
    'edit_link' => 'edit_link',
 //   'delete_link' => 'delete_link',
    'tid' => 'tid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'mid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'template_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'schedule' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'start' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'end' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
 /*   'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),*/
    'tid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  
  /* Field: Bulk operations */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => t('Delete'),
    ),
  );
  
  /* Relationship: Elobbyist Mailing: Template */
  $handler->display->display_options['relationships']['tid']['id'] = 'tid';
  $handler->display->display_options['relationships']['tid']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['relationships']['tid']['field'] = 'tid';
  /* Field: Elobbyist Mailing: Mailing id */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Elobbyist Mailing: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = t('Mailing Name');
  /* Field: Elobbyist Template: Name */
  $handler->display->display_options['fields']['template_name']['id'] = 'template_name';
  $handler->display->display_options['fields']['template_name']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['template_name']['field'] = 'name';
  $handler->display->display_options['fields']['template_name']['relationship'] = 'tid';
  $handler->display->display_options['fields']['template_name']['label'] = t('Template');
  /* Field: Elobbyist Mailing: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Elobbyist Mailing: Schedule */
  $handler->display->display_options['fields']['schedule']['id'] = 'schedule';
  $handler->display->display_options['fields']['schedule']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['schedule']['field'] = 'schedule';
  /* Field: Elobbyist Mailing: Start */
  $handler->display->display_options['fields']['start']['id'] = 'start';
  $handler->display->display_options['fields']['start']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['start']['field'] = 'start';
  $handler->display->display_options['fields']['start']['date_format'] = 'custom';
  $handler->display->display_options['fields']['start']['custom_date_format'] = 'Y-m-d G:i';
  /* Field: Elobbyist Mailing: End */
  $handler->display->display_options['fields']['end']['id'] = 'end';
  $handler->display->display_options['fields']['end']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['end']['field'] = 'end';
  $handler->display->display_options['fields']['end']['date_format'] = 'custom';
  $handler->display->display_options['fields']['end']['custom_date_format'] = 'Y-m-d G:i';
  /* Field: Elobbyist Mailing: Edit */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Field: Elobbyist Mailing: Delete */
 /* $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';*/
  /* Field: Elobbyist Template: Template id */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['relationship'] = 'tid';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  /* Sort criterion: Elobbyist Mailing: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  
  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist mailings';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%view_%timestamp-yyyy_%timestamp-mm_%timestamp-dd.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'elobbyist/mailings/download';

  $views[$view->name] = $view;
  

  //-----------------------
  //----------------------- Email Providers
  //-----------------------  
  
  $view = new view();
  $view->name = 'elobbyist_providers';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_email_provider';
  $view->human_name = t('Email Lobbyist Providers');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist email providers';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'providerid' => 'providerid',
   // 'delete_link' => 'delete_link',
    'edit_link' => 'edit_link',
    'name' => 'name',
    'smtphost' => 'smtphost',
    'smtpport' => 'smtpport',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'providerid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  /*  'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),*/
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'smtphost' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'smtpport' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  
  
  /* Field: Bulk operations */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'elobbyist_email_provider';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => t('Delete'),
    ),
  );
  
  /* Field: Elobbyist Email Provider: Provider id */
  $handler->display->display_options['fields']['providerid']['id'] = 'providerid';
  $handler->display->display_options['fields']['providerid']['table'] = 'elobbyist_email_provider';
  $handler->display->display_options['fields']['providerid']['field'] = 'providerid';
  $handler->display->display_options['fields']['providerid']['exclude'] = TRUE;
  /* Field: Elobbyist Email Provider: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_email_provider';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = t('Provider Name');
  /* Field: Elobbyist Email Provider: Smtp host */
  $handler->display->display_options['fields']['smtphost']['id'] = 'smtphost';
  $handler->display->display_options['fields']['smtphost']['table'] = 'elobbyist_email_provider';
  $handler->display->display_options['fields']['smtphost']['field'] = 'smtphost';
  $handler->display->display_options['fields']['smtphost']['label'] = t('SMTP Server');
  /* Field: Elobbyist Email Provider: Smtp port */
  $handler->display->display_options['fields']['smtpport']['id'] = 'smtpport';
  $handler->display->display_options['fields']['smtpport']['table'] = 'elobbyist_email_provider';
  $handler->display->display_options['fields']['smtpport']['field'] = 'smtpport';
  $handler->display->display_options['fields']['smtpport']['label'] = t('Port');
  /* Field: Email Lobbyist Email Provider: Domain Name */
  $handler->display->display_options['fields']['elobbyist_domain']['id'] = 'elobbyist_domain';
  $handler->display->display_options['fields']['elobbyist_domain']['table'] = 'field_data_elobbyist_domain';
  $handler->display->display_options['fields']['elobbyist_domain']['field'] = 'elobbyist_domain';
  $handler->display->display_options['fields']['elobbyist_domain']['label'] = 'Domain Names';
  /* Field: Elobbyist Email Provider: Edit */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'elobbyist_email_provider';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Field: Elobbyist Email Provider: Delete */
 /* $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'elobbyist_email_provider';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';*/

  
  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist email providers';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%view_%timestamp-yyyy_%timestamp-mm_%timestamp-dd.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'elobbyist/email-providers/download';

  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Subscribers By Group
  //-----------------------  
  
  $view = new view();
  $view->name = 'elobbyist_subscribers_by_group';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_contact';
  $view->human_name = t('Email Lobbyist Subscribers By Group');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contacts';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'email' => 'email',
    'bounce' => 'bounce',
    'stype' => 'stype',
    'edit_link' => 'edit_link',
   // 'delete_link' => 'delete_link',
    'provider_name' => 'provider_name',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'bounce' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'stype' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    /*'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),*/
    'provider_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  
  /* Field: Bulk operations */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => t('Delete'),
    ),
    'rules_component::elobbyist_remove_contacts_from_group' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  
  /* Relationship: Elobbyist Contact: Relation: Subscriber Member (elobbyist_contact ↔ elobbyist_group) */
  $handler->display->display_options['relationships']['relation_elobbyist_subscriber_elobbyist_group']['id'] = 'relation_elobbyist_subscriber_elobbyist_group';
  $handler->display->display_options['relationships']['relation_elobbyist_subscriber_elobbyist_group']['table'] = 'elobbyist_contact';
  $handler->display->display_options['relationships']['relation_elobbyist_subscriber_elobbyist_group']['field'] = 'relation_elobbyist_subscriber_elobbyist_group';
  $handler->display->display_options['relationships']['relation_elobbyist_subscriber_elobbyist_group']['required'] = TRUE;
  $handler->display->display_options['relationships']['relation_elobbyist_subscriber_elobbyist_group']['entity_deduplication_left'] = 0;
  $handler->display->display_options['relationships']['relation_elobbyist_subscriber_elobbyist_group']['entity_deduplication_right'] = 0;
  /* Relationship: Elobbyist Contact: Relation: Group Subscribers (elobbyist_contact → relation) */
  $handler->display->display_options['relationships']['relation_base_left_elobbyist_subscriber']['id'] = 'relation_base_left_elobbyist_subscriber';
  $handler->display->display_options['relationships']['relation_base_left_elobbyist_subscriber']['table'] = 'elobbyist_contact';
  $handler->display->display_options['relationships']['relation_base_left_elobbyist_subscriber']['field'] = 'relation_base_left_elobbyist_subscriber';
  $handler->display->display_options['relationships']['relation_base_left_elobbyist_subscriber']['label'] = 'Group Subscribers Relation';
  $handler->display->display_options['relationships']['relation_base_left_elobbyist_subscriber']['required'] = TRUE;
  $handler->display->display_options['relationships']['relation_base_left_elobbyist_subscriber']['entity_deduplication_left'] = 0;
  
  /* Field: Elobbyist Contact: Contact id */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['exclude'] = TRUE;
  /* Field: Elobbyist Contact: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = t('Full Name');
  /* Field: Elobbyist Contact: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  /* Field: Elobbyist Contact: Bounce */
  $handler->display->display_options['fields']['bounce']['id'] = 'bounce';
  $handler->display->display_options['fields']['bounce']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['bounce']['field'] = 'bounce';
  $handler->display->display_options['fields']['bounce']['label'] = t('Status');
  /* Field: Elobbyist Contact: Subscriber Type */
  $handler->display->display_options['fields']['stype']['id'] = 'stype';
  $handler->display->display_options['fields']['stype']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['stype']['field'] = 'stype';
  $handler->display->display_options['fields']['stype']['label'] = t('Subscription');
  /* Field: Elobbyist Contact: Edit */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Field: Relation: Rid */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'relation';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['relationship'] = 'relation_base_left_elobbyist_subscriber';
  $handler->display->display_options['fields']['rid']['exclude'] = TRUE;
  
  /* Filter criterion: Elobbyist Group: Group id */
  $handler->display->display_options['filters']['grpid']['id'] = 'grpid';
  $handler->display->display_options['filters']['grpid']['table'] = 'elobbyist_group';
  $handler->display->display_options['filters']['grpid']['field'] = 'grpid';
  $handler->display->display_options['filters']['grpid']['relationship'] = 'relation_elobbyist_subscriber_elobbyist_group';
  $handler->display->display_options['filters']['grpid']['value']['value'] = 0;
  $handler->display->display_options['filters']['grpid']['group'] = 1;
  $handler->display->display_options['filters']['grpid']['expose']['operator_id'] = 'grpid_op';
  $handler->display->display_options['filters']['grpid']['expose']['label'] = t('Group id');
  $handler->display->display_options['filters']['grpid']['expose']['operator'] = 'grpid_op';
  $handler->display->display_options['filters']['grpid']['expose']['identifier'] = 'grpid';
  
  /* Filter criterion: Elobbyist Contact: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'elobbyist_contact';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = 'subscriber';
  $handler->display->display_options['filters']['type']['group'] = 1;
  
  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Recipients By Group
  //-----------------------  
  
  $view = new view();
  $view->name = 'elobbyist_recipients_by_group';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_contact';
  $view->human_name = t('Email Lobbyist Recipients By Group');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist contacts';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'email' => 'email',
    'edit_link' => 'edit_link',
   // 'delete_link' => 'delete_link',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  /*  'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),*/
  );
  
  /* Field: Bulk operations */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => t('Delete'),
    ),
    'rules_component::elobbyist_remove_contacts_from_group' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  
  /* Relationship: Elobbyist Contact: Relation: Recipient Member (elobbyist_contact ↔ elobbyist_group) */
  $handler->display->display_options['relationships']['relation_elobbyist_recipient_elobbyist_group']['id'] = 'relation_elobbyist_recipient_elobbyist_group';
  $handler->display->display_options['relationships']['relation_elobbyist_recipient_elobbyist_group']['table'] = 'elobbyist_contact';
  $handler->display->display_options['relationships']['relation_elobbyist_recipient_elobbyist_group']['field'] = 'relation_elobbyist_recipient_elobbyist_group';
  $handler->display->display_options['relationships']['relation_elobbyist_recipient_elobbyist_group']['required'] = TRUE;
  $handler->display->display_options['relationships']['relation_elobbyist_recipient_elobbyist_group']['entity_deduplication_left'] = 0;
  $handler->display->display_options['relationships']['relation_elobbyist_recipient_elobbyist_group']['entity_deduplication_right'] = 0;
  /* Field: Elobbyist Contact: Contact id */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['exclude'] = TRUE;
  /* Field: Elobbyist Contact: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = t('Full Name');
  /* Field: Elobbyist Contact: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  /* Field: Elobbyist Contact: Edit */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Filter criterion: Elobbyist Group: Group id */
  $handler->display->display_options['filters']['grpid']['id'] = 'grpid';
  $handler->display->display_options['filters']['grpid']['table'] = 'elobbyist_group';
  $handler->display->display_options['filters']['grpid']['field'] = 'grpid';
  $handler->display->display_options['filters']['grpid']['relationship'] = 'relation_elobbyist_recipient_elobbyist_group';
  $handler->display->display_options['filters']['grpid']['value']['value'] = '0';
  $handler->display->display_options['filters']['grpid']['group'] = 1;
  /* Filter criterion: Elobbyist Contact: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'elobbyist_contact';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = 'recipient';
  $handler->display->display_options['filters']['type']['group'] = 1;
 
  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Activities By Subscriber
  //-----------------------  
  
  $view = new view();
  $view->name = 'elobbyist_activities_by_subscriber';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_activity';
  $view->human_name = t('Email Lobbyist Activities By Subscriber');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist activities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'aid' => 'aid',
    'name' => 'name',
    'email' => 'email',
    'subject' => 'subject',
    'mailing_name' => 'mailing_name',
    'mid' => 'mid',
    'tid' => 'tid',
    'view_link' => 'view_link',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'aid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'subject' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mailing_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Elobbyist Activity: Mailing */
  $handler->display->display_options['relationships']['mid']['id'] = 'mid';
  $handler->display->display_options['relationships']['mid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['mid']['field'] = 'mid';
  $handler->display->display_options['relationships']['mid']['required'] = TRUE;
  /* Relationship: Elobbyist Activity: Template */
  $handler->display->display_options['relationships']['tid']['id'] = 'tid';
  $handler->display->display_options['relationships']['tid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['tid']['field'] = 'tid';
  /* Relationship: Elobbyist Activity: To */
  $handler->display->display_options['relationships']['tocid']['id'] = 'tocid';
  $handler->display->display_options['relationships']['tocid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['tocid']['field'] = 'tocid';
  $handler->display->display_options['relationships']['tocid']['label'] = 'tocid';
  $handler->display->display_options['relationships']['tocid']['required'] = TRUE;
  /* Field: Elobbyist Activity: Activity id */
  $handler->display->display_options['fields']['aid']['id'] = 'aid';
  $handler->display->display_options['fields']['aid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['aid']['field'] = 'aid';
  $handler->display->display_options['fields']['aid']['exclude'] = TRUE;
  /* Field: Elobbyist Contact: Contact id */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['relationship'] = 'tocid';
  $handler->display->display_options['fields']['cid']['exclude'] = TRUE;
  
  /* Field: Elobbyist Contact: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'tocid';
  $handler->display->display_options['fields']['name']['label'] = t('Recipient');
  /* Field: Elobbyist Contact: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['relationship'] = 'tocid';
  /* Field: Elobbyist Template: Subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  /* Field: Elobbyist Mailing: Name */
  $handler->display->display_options['fields']['mailing_name']['id'] = 'mailing_name';
  $handler->display->display_options['fields']['mailing_name']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['mailing_name']['field'] = 'name';
  $handler->display->display_options['fields']['mailing_name']['relationship'] = 'mid';
  $handler->display->display_options['fields']['mailing_name']['label'] = t('Mailing');
  
  /* Field: Elobbyist Activity: View */
  $handler->display->display_options['fields']['view_link']['id'] = 'view_link';
  $handler->display->display_options['fields']['view_link']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['view_link']['field'] = 'view_link';
  $handler->display->display_options['fields']['view_link']['label'] = t('View Email');
  /* Field: Elobbyist Activity: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = t('Sent');
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y-m-d G:i';
  /* Field: Elobbyist Activity: Mailing id */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Elobbyist Activity: Template id */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  /* Filter criterion: Elobbyist Activity: From Contact id */
  $handler->display->display_options['filters']['fromcid']['id'] = 'fromcid';
  $handler->display->display_options['filters']['fromcid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['filters']['fromcid']['field'] = 'fromcid';
  $handler->display->display_options['filters']['fromcid']['value']['value'] = '0';
  
  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Activities By Recipient
  //-----------------------  
  
  $view = new view();
  $view->name = 'elobbyist_activities_by_recipient';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_activity';
  $view->human_name = t('Email Lobbyist Activities By Recipient');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist activities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'aid' => 'aid',
    'name' => 'name',
    'email' => 'email',
    'subject' => 'subject',
    'mailing_name' => 'mailing_name',
    'view_link' => 'view_link',
    'created' => 'created',
    'mid' => 'mid',
    'tid' => 'tid',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'aid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'subject' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mailing_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Elobbyist Activity: Mailing */
  $handler->display->display_options['relationships']['mid']['id'] = 'mid';
  $handler->display->display_options['relationships']['mid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['mid']['field'] = 'mid';
  $handler->display->display_options['relationships']['mid']['required'] = TRUE;
  /* Relationship: Elobbyist Activity: Template */
  $handler->display->display_options['relationships']['tid']['id'] = 'tid';
  $handler->display->display_options['relationships']['tid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['tid']['field'] = 'tid';
  /* Relationship: Elobbyist Activity: From */
  $handler->display->display_options['relationships']['fromcid']['id'] = 'fromcid';
  $handler->display->display_options['relationships']['fromcid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['fromcid']['field'] = 'fromcid';
  $handler->display->display_options['relationships']['fromcid']['label'] = 'fromcid';
  $handler->display->display_options['relationships']['fromcid']['required'] = TRUE;
  /* Field: Elobbyist Activity: Activity id */
  $handler->display->display_options['fields']['aid']['id'] = 'aid';
  $handler->display->display_options['fields']['aid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['aid']['field'] = 'aid';
  $handler->display->display_options['fields']['aid']['exclude'] = TRUE;
  /* Field: Elobbyist Contact: Contact id */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['relationship'] = 'fromcid';
  $handler->display->display_options['fields']['cid']['exclude'] = TRUE;
  
  /* Field: Elobbyist Contact: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'fromcid';
  $handler->display->display_options['fields']['name']['label'] = t('Sender');
  /* Field: Elobbyist Contact: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['relationship'] = 'fromcid';
  /* Field: Elobbyist Template: Subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  /* Field: Elobbyist Mailing: Name */
  $handler->display->display_options['fields']['mailing_name']['id'] = 'mailing_name';
  $handler->display->display_options['fields']['mailing_name']['table'] = 'elobbyist_mailing';
  $handler->display->display_options['fields']['mailing_name']['field'] = 'name';
  $handler->display->display_options['fields']['mailing_name']['relationship'] = 'mid';
  $handler->display->display_options['fields']['mailing_name']['label'] = t('Mailing');
  
  /* Field: Elobbyist Activity: View */
  $handler->display->display_options['fields']['view_link']['id'] = 'view_link';
  $handler->display->display_options['fields']['view_link']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['view_link']['field'] = 'view_link';
  $handler->display->display_options['fields']['view_link']['label'] = t('View Email');
  /* Field: Elobbyist Activity: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = t('Sent');
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y-m-d G:i';
  /* Field: Elobbyist Activity: Mailing id */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Elobbyist Activity: Template id */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  /* Filter criterion: Elobbyist Activity: To Contact id */
  $handler->display->display_options['filters']['tocid']['id'] = 'tocid';
  $handler->display->display_options['filters']['tocid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['filters']['tocid']['field'] = 'tocid';
  $handler->display->display_options['filters']['tocid']['value']['value'] = '0';

  $views[$view->name] = $view;
  
  //-----------------------
  //----------------------- Activities By Mailing
  //-----------------------  
  
  $view = new view();
  $view->name = 'elobbyist_activities_by_mailing';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'elobbyist_activity';
  $view->human_name = t('Email Lobbyist Activities By Mailing');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view email lobbyist activities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = $items_per_page;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'aid' => 'aid',
    'name' => 'name',
    'email' => 'email',
    'recipient_name' => 'recipient_name',
    'recipient_email' => 'recipient_email',
    'subject' => 'subject',
    'view_link' => 'view_link',
    'created' => 'created',
    'mid' => 'mid',
    'tid' => 'tid',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'aid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'recipient_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'recipient_email' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'subject' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Elobbyist Activity: Mailing */
  $handler->display->display_options['relationships']['mid']['id'] = 'mid';
  $handler->display->display_options['relationships']['mid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['mid']['field'] = 'mid';
  $handler->display->display_options['relationships']['mid']['required'] = TRUE;
  /* Relationship: Elobbyist Activity: Template */
  $handler->display->display_options['relationships']['tid']['id'] = 'tid';
  $handler->display->display_options['relationships']['tid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['tid']['field'] = 'tid';
  /* Relationship: Elobbyist Activity: From */
  $handler->display->display_options['relationships']['fromcid']['id'] = 'fromcid';
  $handler->display->display_options['relationships']['fromcid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['fromcid']['field'] = 'fromcid';
  $handler->display->display_options['relationships']['fromcid']['label'] = 'fromcid';
  $handler->display->display_options['relationships']['fromcid']['required'] = TRUE;
  /* Relationship: Elobbyist Activity: To */
  $handler->display->display_options['relationships']['tocid']['id'] = 'tocid';
  $handler->display->display_options['relationships']['tocid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['relationships']['tocid']['field'] = 'tocid';
  $handler->display->display_options['relationships']['tocid']['label'] = 'tocid';
  $handler->display->display_options['relationships']['tocid']['required'] = TRUE;
  /* Field: Elobbyist Activity: Activity id */
  $handler->display->display_options['fields']['aid']['id'] = 'aid';
  $handler->display->display_options['fields']['aid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['aid']['field'] = 'aid';
  $handler->display->display_options['fields']['aid']['exclude'] = TRUE;
  /* Field: Elobbyist Contact: Contact id */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['relationship'] = 'fromcid';
  $handler->display->display_options['fields']['cid']['exclude'] = TRUE;
  /* Field: Elobbyist Contact: Contact id */
  $handler->display->display_options['fields']['cid_1']['id'] = 'cid_1';
  $handler->display->display_options['fields']['cid_1']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['cid_1']['field'] = 'cid';
  $handler->display->display_options['fields']['cid_1']['relationship'] = 'tocid';
  $handler->display->display_options['fields']['cid_1']['exclude'] = TRUE;
  
  /* Field: Elobbyist Contact: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'fromcid';
  $handler->display->display_options['fields']['name']['label'] = t('Sender');
  /* Field: Elobbyist Contact: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['relationship'] = 'fromcid';
  $handler->display->display_options['fields']['email']['label'] = t('From');
  /* Field: Elobbyist Contact: Name */
  $handler->display->display_options['fields']['recipient_name']['id'] = 'recipient_name';
  $handler->display->display_options['fields']['recipient_name']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['recipient_name']['field'] = 'name';
  $handler->display->display_options['fields']['recipient_name']['relationship'] = 'tocid';
  $handler->display->display_options['fields']['recipient_name']['label'] = t('Recipient');
  /* Field: Elobbyist Contact: Email */
  $handler->display->display_options['fields']['recipient_email']['id'] = 'recipient_email';
  $handler->display->display_options['fields']['recipient_email']['table'] = 'elobbyist_contact';
  $handler->display->display_options['fields']['recipient_email']['field'] = 'email';
  $handler->display->display_options['fields']['recipient_email']['relationship'] = 'tocid';
  $handler->display->display_options['fields']['recipient_email']['label'] = t('To');
  /* Field: Elobbyist Template: Subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'elobbyist_template';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  
  /* Field: Elobbyist Activity: View */
  $handler->display->display_options['fields']['view_link']['id'] = 'view_link';
  $handler->display->display_options['fields']['view_link']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['view_link']['field'] = 'view_link';
  $handler->display->display_options['fields']['view_link']['label'] = t('View Email');
  /* Field: Elobbyist Activity: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = t('Sent');
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y-m-d G:i';

  /* Field: Elobbyist Activity: Mailing id */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Elobbyist Activity: Template id */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  /* Filter criterion: Elobbyist Activity: Mailing id */
  $handler->display->display_options['filters']['mid']['id'] = 'mid';
  $handler->display->display_options['filters']['mid']['table'] = 'elobbyist_activity';
  $handler->display->display_options['filters']['mid']['field'] = 'mid';
  $handler->display->display_options['filters']['mid']['value']['value'] = '0';
  
  $views[$view->name] = $view;


  return $views;
}

function elobbyist_views_in_operator_callback($vals) {
  return $vals;
}