<?php

/**
 * @file
 * Contains the linked name field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a record.
 * Definition terms:
 * - link_to_record default: Should this field have the checkbox "link to record" enabled by default.
 * - id field: the id (primary key) field name
 * - url: url with % for id place holder
 *
 * @ingroup views_field_handlers
 */
class elobbyist_views_handler_linked_name extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);
    // Don't add the additional fields to groupby
    if (!empty($this->options['link_to_record'])) {
      $this->additional_fields[$this->definition['id field']] = array(
        'field' => $this->definition['id field']
      );
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_record'] = array('default' => isset($this->definition['link_to_record default']) ? $this->definition['link_to_record default'] : FALSE, 'bool' => TRUE);
    return $options;
  }

  /**
   * Provide link to node option
   */
  function options_form(&$form, &$form_state) {
    $form['link_to_record'] = array(
      '#title' => t('Link this field to the record edit form'),
      '#description' => t("Enable to override this field's links."),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_record']),
    );

    parent::options_form($form, $form_state);
  }

  /**
   * Render whatever the data is as a link to the record.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_record']) && !empty($this->additional_fields[$this->definition['id field']])) {
      if ($data !== NULL && $data !== '') {
        $this->options['alter']['make_link'] = TRUE;
        $this->options['alter']['path'] = str_replace('%', $this->get_value($values, $this->definition['id field']), 
          $this->definition['url']);
      }
      else {
        $this->options['alter']['make_link'] = FALSE;
      }
    }
    return $data;
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }
}
