<?php


class ELobbyistMailingController extends DrupalDefaultEntityController {
  public function create() {
    return (object)array(
      'mid' => '',
      'name' => '',
      'tid' => '',
      'schedule' => '',
      'status' => '',
      'start' => '',
      'end' => '',
      'time_part1' => '',
      'time_part2' => '',
    );
  }
  
  public function save($entity) {
    $transaction = db_transaction();
    
    try {
      global $user;
      
      // Determine if we will be inserting a new record
      $entity->is_new = empty($entity->mid);
            
      $update = TRUE;
            
      // Give modules the opportunity to prepare field data for
      // saving.
      field_attach_presave('elobbyist_mailing', $entity);
            
      // If this is a new record...
      if ($entity->is_new) {
        // Save the new record.
        drupal_write_record('elobbyist_mailing', $entity);
                
        $op = 'insert';
      }
      else {
        // Save the updated record
        drupal_write_record('elobbyist_mailing', $entity, 'mid');
        
        $op = 'update';
      }
            
      // Save fields.
      $function = 'field_attach_' . $op;
      $function('elobbyist_mailing', $entity);
      
      module_invoke_all('entity_' . $op, $entity, 'elobbyist_mailing');
     
      //clear internal properties
      unset($entity->is_new);
      
      // Ignore slave server temporarily to give time for the saved
      // order to be propagated to the slave.
      db_ignore_slave();

      return $entity;
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('elobbyist_mailing', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }
  
  public function delete($ids) {
    if (empty($ids)) {
      return TRUE;
    }
      
    $entities = $this->load($ids, array());
    $transaction = db_transaction();
    
    try
    {
      db_delete('elobbyist_mailing')
        ->condition('mid', $ids, 'IN')
        ->execute();

      foreach($entities as $entity) {        
        field_attach_delete('elobbyist_mailing', $entity);

        module_invoke_all('entity_delete', $entity, 'elobbyist_mailing');
      }

      db_ignore_slave();
    }
    catch(Exception $e) {
      $transaction->rollback();
      watchdog_exception('elobbyist_mailing', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
    
    return TRUE;
  }
}