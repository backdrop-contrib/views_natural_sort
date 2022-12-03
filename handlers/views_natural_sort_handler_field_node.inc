<?php

class views_natural_sort_handler_field_node extends views_handler_field_node {
  /**
   * Called to determine what to tell the clicksorter.
   */
  public function click_sort($order) {
    // Determine if this field has natural sort enabled.
    $natural_sort = 0;
    $id = $this->options['id'];
    if (isset($this->view->style_options['info'][$id]['natural_sort'])) {
      $natural_sort = $this->view->style_options['info'][$id]['natural_sort'];
    }

    // If this field isn't being used as a Natural Sort Field, move along
    // nothing to see here.
    if (!$natural_sort) {
      parent::click_sort($order);
      return;
    }

    // Add the Views Natural Sort table for this field.
    $vns_alias = 'vns_' . $this->table_alias;
    if (empty($this->query->relationships[$vns_alias])) {
      $this->ensure_my_table();
      $vns_alias = $this->query->add_relationship('vns_' . $this->table_alias, $this->natural_sort_join(), $this->table, $this->relationship);
    }
    $this->query->add_orderby($vns_alias, 'content', $order);
  }

  /**
   * Helper function that creates a join to the views natural sort table.
   */
  public function natural_sort_join() {
    $join = new views_join();
    $table_data = views_fetch_data($this->table);
    $join->definition = array(
      'table' => 'views_natural_sort',
      'field' => 'eid',
      'left_field' => $table_data['table']['base']['field'],
      'left_table' => $this->table,
      'extra' => array(
        array(
          'field' => 'entity_type',
          'value' => $table_data['table']['entity type'],
        ),
        array(
          'field' => 'field',
          'value' => $this->real_field,
        ),
      ),
    );
    $join->construct();
    $join->adjusted = TRUE;
    return $join;
  }
}
