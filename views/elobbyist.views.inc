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
        'title' => 'Elobbyist Activity',
        'help' => 'Email Lobbyist email activity',
        'weight' => 540,
       ),
      'group' => 'Elobbyist Activity',
    ),
    'aid' => array(
      'title' => 'Activity id',
      'help' => 'The primary identifier for an email activity.',
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
      'title' => 'Mailing id',
      'help' => 'mailing id.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => 'Mailing',
          'lable' => 'Mailing',
          'base' => 'elobbyist_mailing',
          'base field' => 'mid',
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
    'tid' => array(
      'title' => 'Template id',
      'help' => 'template id.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => 'Template',
          'lable' => 'Template',
          'base' => 'elobbyist_template',
          'base field' => 'tid',
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
    'fromcid' => array(
      'title' => 'From Contact id',
      'help' => 'Contact id.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => 'From',
          'lable' => 'From',
          'base' => 'elobbyist_contact',
          'base field' => 'cid',
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
    'tocid' => array(
      'title' => 'To Contact id',
      'help' => 'Contact id.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => 'To',
          'lable' => 'To',
          'base' => 'elobbyist_contact',
          'base field' => 'cid',
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
      'title' => 'Created',
      'help' => 'The Unix timestamp when the record was created.',
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
  $data['elobbyist_contact'] = array(
    'table' => array(
      'base' => array(
        'field' => 'cid',
        'title' => 'Elobbyist Contact',
        'help' => 'Email Lobbyist contacts - subscribers and recipients',
        'weight' => 500,
        'defaults' => array(
          'field' => 'name',
        ),
      ),
      'group' => 'Elobbyist Contact',
      'entity type' => 'elobbyist_contact',
    ),
    'cid' => array(
      'title' => 'Contact id',
      'help' => 'The primary identifier for a contact.',
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
      'title' => 'Edit',
      'help' => 'An edit link for the contact',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/contact/%/edit',
        'link_text' => t('Edit'),
      ),
    ),
    'delete_link' => array(
      'real field' => 'cid',
      'title' => 'Delete',
      'help' => 'A delete link for the contact',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/contact/%/delete',
        'link_text' => t('Delete'),
      ),
    ),
    'type' => array(
      'title' => 'Type',
      'help' => 'The contact_type of this contact.',
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
      'title' => 'Name',
      'help' => 'The contact full name.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/contact/%/edit',
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
      'title' => 'Email',
      'help' => 'The contact email address.',
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
      'title' => 'Form',
      'help' => 'for subscriber - creating form',
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => elobbyist_form_types(),
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
    'stype' => array(
      'title' => 'Subscriber Type',
      'help' => 'for subscriber - subscription type: persistent or specific-mailing subscriber?',
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => elobbyist_subscriber_types(),
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
    'providerid' => array(
      'title' => 'Provider id',
      'help' => 'The email provider identifier.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => 'Email Provider',
          'lable' => 'Email Provider',
          'base' => 'elobbyist_email_provider',
          'base field' => 'providerid',
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
    'mid' => array(
      'title' => 'Restricted to Mailing id',
      'help' => 'Restrict to specific mailing.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => 'Restricted to Mailing',
          'lable' => 'Restricted to Mailing',
          'base' => 'elobbyist_mailing',
          'base field' => 'mid',
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
    'notify' => array(
      'title' => 'Notify',
      'help' => 'Notify on emails sent.',
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
      'title' => 'Bounce',
      'help' => 'bouncing status',
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => elobbyist_email_statuses(),
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
    'bounces' => array(
      'title' => 'Bounces',
      'help' => 'bouncing count',
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
      'title' => 'Created',
      'help' => 'The Unix timestamp when the contact was created.',
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
      'title' => 'Changed',
      'help' => 'The Unix timestamp when the contact was most recently saved.',
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
        'title' => 'Elobbyist Email Provider',
        'help' => 'Email Lobbyist email provider',
        'weight' => 570,
      ),
      'group' => 'Elobbyist Email Provider',
    ),
    'providerid' => array(
      'title' => 'Provider id',
      'help' => 'The email provider identifier id.',
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
      'title' => 'Name',
      'help' => 'The provider name.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/email-provider/%/edit',
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
      'title' => 'Smtp host',
      'help' => 'The provider smtp server address.',
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
      'title' => 'Smtp port',
      'help' => 'The provider smtp server port',
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
      'title' => 'Edit',
      'help' => 'An edit page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/email-provider/%/edit',
        'link_text' => t('Edit'),
      ),
    ),
    'delete_link' => array(
      'real field' => 'providerid',
      'title' => 'Delete',
      'help' => 'A delete page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/email-provider/%/delete',
        'link_text' => t('Delete'),
      ),
    ),
  );
  $data['elobbyist_group'] = array(
    'table' => array(
      'base' => array(
        'field' => 'grpid',
        'title' => 'Elobbyist Group',
        'help' => 'Email Lobbyist contact group',
        'weight' => 510,
      ),
      'group' => 'Elobbyist Group',
    ),
    'grpid' => array(
      'title' => 'Group id',
      'help' => 'The group id.',
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
      'title' => 'Name',
      'help' => 'The group name.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/contact-group/%/edit',
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
      'title' => 'Type',
      'help' => 'The contact_type this group is confined to.',
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
      'title' => 'Status',
      'help' => 'group status: Active, Inactive.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => elobbyist_group_status_list(),
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
    'edit_link' => array(
      'real field' => 'grpid',
      'title' => 'Edit',
      'help' => 'An edit page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/contact-group/%/edit',
        'link_text' => t('Edit'),
      ),
    ),
    'delete_link' => array(
      'real field' => 'grpid',
      'title' => 'Delete',
      'help' => 'A delete page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/contact-group/%/delete',
        'link_text' => t('Delete'),
      ),
    ),
  );
  $data['elobbyist_mailing'] = array(
    'table' => array(
      'base' => array(
        'field' => 'mid',
        'title' => 'Elobbyist Mailing',
        'help' => 'Email Lobbyist mailing',
        'weight' => 520,
      ),
      'group' => 'Elobbyist Mailing',
    ),
    'mid' => array(
      'title' => 'Mailing id',
      'help' => 'The primary identifier for a mailing.',
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
      'title' => 'Name',
      'help' => 'The mailing name.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/mailing/%/edit',
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
      'title' => 'Template id',
      'help' => 'The mailing template.',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
          'title' => 'Template',
          'lable' => 'Template',
          'base' => 'elobbyist_template',
          'base field' => 'tid',
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
    'schedule' => array(
      'title' => 'Schedule',
      'help' => 'schedule type.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => elobbyist_mailing_schedule_type_list(),
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
    'status' => array(
      'title' => 'Status',
      'help' => 'mailing status: Draft, Scheduled, Cancelled, Closed.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => elobbyist_mailing_status_list(),
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
    'page' => array(
      'title' => 'Page',
      'help' => 'content of the call to action page',
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    ),
    'successurl' => array(
      'title' => 'Success URL',
      'help' => 'URL to redirect to after a successful public subscription',
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
      'title' => 'Start',
      'help' => 'The Unix timestamp for scheduling start time.',
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
      'title' => 'End',
      'help' => 'The Unix timestamp for scheduling end time.',
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
      'title' => 'Collector Group id',
      'help' => 'Collects subscribers of on-going schedule type',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => FALSE,
      ),
      'relationship' => array(
          'title' => 'Collector Group',
          'lable' => 'Collector Group',
          'base' => 'elobbyist_group',
          'base field' => 'grpid',
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
      'title' => 'Created',
      'help' => 'The Unix timestamp when the record was created.',
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
      'title' => 'Changed',
      'help' => 'The Unix timestamp when the record was most recently saved.',
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
      'title' => 'Edit',
      'help' => 'An edit page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/mailing/%/edit',
        'link_text' => t('Edit'),
      ),
    ),
    'delete_link' => array(
      'real field' => 'mid',
      'title' => 'Delete',
      'help' => 'A delete page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/mailing/%/delete',
        'link_text' => t('Delete'),
      ),
    ),
  );
  $data['elobbyist_template'] = array(
    'table' => array(
      'base' => array(
        'field' => 'tid',
        'title' => 'Elobbyist Template',
        'help' => 'Email Lobbyist template',
        'weight' => 560,
      ),
      'group' => 'Elobbyist Template',
    ),
    'tid' => array(
      'title' => 'Template id',
      'help' => 'The primary identifier for a template.',
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
      'title' => 'Name',
      'help' => 'The template name.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_linked_name',
        'click sortable' => TRUE,
        'link_to_record default' => TRUE,
        'url' => 'elobbyist/template/%/edit',
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
      'title' => 'Subject',
      'help' => 'The email subject.',
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
    'body' => array(
      'title' => 'Body',
      'help' => 'The email body.',
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => FALSE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    ),
    'status' => array(
      'title' => 'Status',
      'help' => 'template status: Draft, Sent, Closed, Cancelled.',
      'field' => array(
        'handler' => 'elobbyist_views_handler_list_field',
        'list' => elobbyist_template_status_list(),
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
    'edit_link' => array(
      'real field' => 'tid',
      'title' => 'Edit',
      'help' => 'An edit page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/template/%/edit',
        'link_text' => t('Edit'),
      ),
    ),
    'delete_link' => array(
      'real field' => 'tid',
      'title' => 'Delete',
      'help' => 'A delete page link',
      'field' => array(
        'handler' => 'elobbyist_views_handler_link',
        'click sortable' => FALSE,
        'url' => 'elobbyist/template/%/delete',
        'link_text' => t('Delete'),
      ),
    ),
  );

  return $data;
}