<?php
/**
 * @file
 * elobbyist.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function elobbyist_user_default_roles() {
  $roles = array();

  $roles['elobbyist admin'] = array(
    'name' => 'elobbyist admin',
  );

  return $roles;
}
