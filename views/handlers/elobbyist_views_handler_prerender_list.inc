<?php

class elobbyist_views_handler_prerender_list extends views_handler_field_prerender_list {
    
  function pre_render(&$values) {
    $property = $this->field_alias;
    
    foreach ($values as $row) {
      $value = $row->$property;
      if (isset($value) && (!empty($value) || isset($this->definition['list'][0]))) {
        $this->items[$value] = array();
        $this->items[$value][] = array('option' => $this->definition['list'][$value]);
      }
    }
  }
  
  function render_item($count, $item) {
    return $item['option'];
  }
}