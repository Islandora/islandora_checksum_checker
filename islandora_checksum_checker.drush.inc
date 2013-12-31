<?php

/**
 * @file
 * Drush integration file for the Islandora Checksum Checker module.
 *
 * Drupal 7's cron can only be run as an anonymous user. The Islandora
 * Checksum Checker module uses Fedora's API-M to retrieve information
 * about datastreams and to update objects. Anonymous Drupal users may
 * not have sufficient privileges to perform these tasks. This drush
 * script offers an alternative to having Drupal 7 cron populate and
 * process the Islandora Checksum Checker job queue. 
 * 
 * This script should be run with the drush --user parameter indicating
 * an Islandora user with sufficient privileges to access all objects in
 * your Fedora repository. It uses configuration options defined at the
 * Islandora Checksum Checker module's admin settings, 
 * admin/islandora/checksum_checker. 
 */

/**
 * Implements hook_drush_help().
 */
function islandora_checksum_checker_drush_help($command) {
  switch ($command) {
    case 'drush:run-islandora-checksum-queue':
      return dt('Populate and process items in the Islandora checksum validation queue.');
  }
}

/**
 * Implements hook_drush_command().
 */
function islandora_checksum_checker_drush_command() {
  $items = array();
  $items['run-islandora-checksum-queue'] = array(
    'description' => dt('Populate and process items in the Islandora checksum validation queue.'),
    'examples' => array(
      'Standard example' => 'drush --user=fedoraAdmin run-islandora-checksum-queue',
      'Alias example' => 'drush --user=fedoraAdmin ricq',
    ),
    'aliases' => array('ricq'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );
  return $items;
}

/**
 * Callback function for drush run-islandora-checksum-queue.
 */
function drush_islandora_checksum_checker_run_islandora_checksum_queue() {
  if (variable_get('islandora_checksum_checker_queue_cron_method', 'drupal') != 'drush') {
    return;
  }

  // Populate the queue with the next $objects_to_check object PIDs.
  $queue = DrupalQueue::get('validateIslandoraChecksums');
  $items_still_in_queue = $queue->numberOfItems();
  $objects_to_check = islandora_checksum_checker_get_objects($items_still_in_queue);
  foreach($objects_to_check as $object) {
    $queue->createItem($object);
  }

  // Process the items just added to the queue.
  while ($item = $queue->claimItem()) {
    // $item->data will be an Islandora object's PID.
    if (islandora_checksum_checker_validate_checksum($item->data)) {
      // If success, remove the item from queue.
      $queue->deleteItem($item);
    }
    else {
      // @todo: Log failure to watchdog.
      // Release, not delete the item so it remains in the queue.
      $queue->releaseItem($item);
    }
  }
}
