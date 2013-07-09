<?php

class WalkhubWalkthroughSet implements WalkhubObject {

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
  public $tokens;

  /**
   * @filter check_plain
   */
  public $references;

  /**
   * @filter none
   */
  public $logo;

  public function __construct(stdClass $node = NULL) {
    if ($node) {
      module_load_include('inc', 'walkhub');
      $this->title = $node->title;
      $this->description = walkhub_field_get_value($node, 'description');
      $this->tokens = _walkhub_get_tokens($node);
      $this->references = array_map(function ($item) {
        $item['walkthrough'] = $item['walkthrough']->uuid;
        return $item;
      }, _walkthrough_sets_get_references($node));
      $this->logo = walkhub_image_field_get_url($node, 'field_logo');
    }
  }

  /**
   * Applies the contents of this container object to an existing entity.
   *
   * @param stdClass $entity
   */
  public function applyOnEntity(stdClass $entity) {
    // TODO: Implement applyOnEntity() method.
  }
}

function _walkthrough_set_resource_retrieve($uuid) {
  module_load_include('inc', 'walkhub');
  $node = _walkhub_node_retrieve($uuid, 'walkthrough_set');
  return $node ? walkhub_serialize_safely(new WalkhubWalkthroughSet($node)) : $node;
}

function _walkthrough_set_resource_access($op = 'view', $args = array()) {
  module_load_include('inc', 'walkhub');
  return _walkhub_node_resource_access('walkthrough_set', $op, $args);
}