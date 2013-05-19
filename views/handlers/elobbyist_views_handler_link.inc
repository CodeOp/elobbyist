<?php

class elobbyist_views_handler_link extends views_handler_field_url {
      
  function render($values) {
    $value = $this->get_value($values);
    if (isset($this->definition['url'])) {
      $value = str_replace('%', $value, $this->definition['url']);
    }
    if (!empty($this->options['display_as_link'])) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = $value;
      $text = !empty($this->definition['link_text']) ? $this->sanitize_value($this->definition['link_text']) : $this->sanitize_value($value, 'url');

      return $text;
    }
    else {
      return $this->sanitize_value($value, 'url');
    }
  }
}