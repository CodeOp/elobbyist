<?php

class elobbyist_views_handler_list_field extends views_handler_field {
    
  function render($values) {    
    $value = $this->get_value($values);
    return $this->definition['list'][$value];
  }
}