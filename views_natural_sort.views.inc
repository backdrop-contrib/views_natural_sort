<?php

/**
 * @file
 * Views related hooks for the Views Natural Sort module.
 */

/**
 * Implements hook_views_data_alter().
().
 */
function views_natural_sort_views_data_alter(&$views_data) {
  $supported_entity_properties = views_natural_sort_get_supported_entity_properties();
  $schema_fields = array();
  foreach ($supported_entity_properties as $entity => $properties) {
    foreach ($properties as $property => $schema_info) {
      if (empty($schema_fields[$schema_info['base_table']])) {
        $schema_fields[$schema_info['base_table']] = array();
      }
      $schema_fields[$schema_info['base_table']][] = $schema_info['schema_field'];
    }
  }
  foreach ($views_data as $table => &$data) {
    if (empty($schema_fields[$table])) {
      continue;
    }
    foreach ($data as $view_field => &$view_field_data) {
      if (isset($view_field_data['field']) && 
        isset($view_field_data['sort']) && 
        $view_field_data['sort']['handler'] == 'views_handler_sort' && 
        ((isset($view_field_data['field']['field']) && in_array($view_field_data['field']['field'], $schema_fields[$table])) ||
          in_array($view_field, $schema_fields[$table]))) {
        // We've verified that this is a perfect candidate to add our sort
        // handler to.
        $view_field_data['sort']['handler'] = 'views_natural_sort_handler_sort';

        switch ($view_field_data['field']['handler']) {
          case 'views_handler_field_node':
            $view_field_data['field']['handler'] = 'views_natural_sort_handler_field_node';
            break;
            // @todo: Add support for other field handlers.
        }
      }
    }
  }
}

/** 
 * Implements hook_views_data().
 */
function views_natural_sort_views_data() {
  // Include the natural title argument in Node views. 
  $data['views_natural_sort']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'eid',
      // We only support this for node titles.
      'extra' => array(
        array(
          'field' => 'field',
          'value' => 'title',
          'operator' => '=',
        ),
        array(
          'field' => 'entity_type',
          'value' => 'node',
          'operator' => '=',
        ),
      )
    ),
  );
  $data['views_natural_sort']['content'] = array(
    'title' => 'Title - Natural',
    'group' => t('Node'),
    'help' => t('The natural title of a node.'),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_plugins_alter().
().
 */
function views_natural_sort_views_plugins_alter(&$plugins) {
  $plugins['style']['table']['handler'] = 'views_natural_sort_plugin_style_table';
  $plugins['style']['table']['path'] = backdrop_get_path('module', 'views_natural_sort') . '/plugins';
  $plugins['style']['table']['file'] = 'views_natural_sort_plugin_style_table.inc';
}
