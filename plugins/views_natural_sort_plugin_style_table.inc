<?php
class views_natural_sort_plugin_style_table extends views_plugin_style_table {
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['#theme'] = 'views_natural_sort_style_plugin_table';
    $form['vns_test'] = array(
      '#markup' => "<h1>VNS TEST</h1>",
    );
  }
}
