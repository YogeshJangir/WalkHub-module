<?php

class WalkhubWalkthroughSet implements WalkhubObject {

  /**
   * @filter check_plain
   */
  public $uuid;

  /**
   * @filter check_plain
   */
  public $title;

  /**
   * @filter check_plain
   */
  public $description;

  /**
   * @filter check_plain
   */
  public $parameters;

  /**
   * @filter check_plain
   */
  public $references;

  /**
   * @filter none
   */
  public $logo;

  /**
   * @filter none
   */
  public $icon;

  /**
   * @filter none
   */
  public $detail_image;

  public function __construct(stdClass $node = NULL) {
    if ($node) {
      module_load_include('inc', 'walkhub');
      $this->uuid = $node->uuid;
      $this->title = $node->title;
      $this->description = walkhub_field_get_value($node, 'body');
      $this->parameters = _walkhub_get_parameters($node);
      $this->references = array_map(function ($item) {
        $item['walkthrough'] = $item['walkthrough']->uuid;
        return $item;
      }, _walkthrough_sets_get_references($node));
      $this->logo = walkhub_image_field_get_url($node, 'field_logo');
      $this->icon = walkhub_image_field_get_url($node, 'field_icon');
      $this->detail_image = walkhub_image_field_get_url($node, 'field_detail_image');
    }
  }

  /**
   * Applies the contents of this container object to an existing entity.
   *
   * @param stdClass $entity
   */
  public function applyOnEntity($entity) {
    // TODO: Implement applyOnEntity() method.
  }
}

function _walkthrough_set_resource_retrieve($uuid) {
  module_load_include('inc', 'walkhub');
  $node = _walkhub_node_retrieve($uuid, 'walkthrough_set');
  return $node ? walkhub_serialize_safely(new WalkhubWalkthroughSet($node)) : $node;
}

/**
 * Export PHPUnit test from a walkthrough_set.
 *
 * @param string $uuid
 *  Walkthrough set uuid.
 *
 * @return string
 *  PHPUnit test case.
 */
function _walkthrough_set_phpunit_resource_retrieve($uuid) {
  $output = NULL;

  module_load_include('inc', 'walkhub', 'walkhub.export');
  $walkthrough_set = _walkhub_node_retrieve($uuid, 'walkthrough_set');
  if (!empty($walkthrough_set)) {
    module_load_include('inc', 'walkthrough_sets', 'walkthrough_sets.export');
    $output = _walkthrough_set_get_phpunit_export_output($walkthrough_set);
  }

  return $output;
}

function _walkthrough_set_resource_access($op = 'view', $args = array()) {
  module_load_include('inc', 'walkhub');
  return _walkhub_node_resource_access('walkthrough_set', $op, $args);
}
