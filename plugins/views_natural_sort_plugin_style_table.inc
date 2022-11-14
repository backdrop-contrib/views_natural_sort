<?php

class views_natural_sort_plugin_style_table extends views_plugin_style_table {
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $handlers = $this->display->handler->get_handlers('field');

    $form['#theme'] = 'views_natural_sort_style_plugin_table';

    $columns = $this->sanitize_columns($this->options['columns']);

    foreach ($columns as $field => $column) {
      $safe = str_replace(array('][', '_', ' '), '-', $field);
      // the $id of the column for dependency checking.
      $id = 'edit-style-options-columns-' . $safe;

      if ($handlers[$field]->click_sortable()) {
        $form['info'][$field]['natural_sort'] = array(
          '#type' => 'checkbox',
          '#default_value' => !empty($this->options['info'][$field]['natural_sort']),
          '#dependency' => array($id => array($field)),
        );
      }
    }
  }
}
