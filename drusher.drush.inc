<?php

/**
 * Implements hook_drush_help().
 */
function drusher_drush_help($command) {
  switch ($command) {
    case 'drush:my-command':
      return dt('Run my command');
  }
}

/**
 * Implements hook_drush_command().
 */
function drusher_drush_command() {
  $items = array();
  $items['drusher-set-env'] = array(
    'description' => dt('To set enviroment.'),
    'arguments'   => array(
      'dev'    => dt('Set enviroment to develepment.'),
      'prod'    => dt('Set enviroment to production.')
    ),
    'examples' => array(
      'Standard use' => 'drush drusher-set-env(env)',
      'Set to dev enviroment' => 'drush drusher-set-env(env) dev',
      'Set to prod enviroment' => 'drush drusher-set-env(env) prod',
    ),
    'aliases' => array('env'),
    'callback' => '_set_env'
  );
  $items['drusher-users-get'] = array(
    'description' => dt('To get users.'),
    'aliases' => array('admins'),
    'callback' => '_get_admins'
  );
  return $items;
}


/**
 * Callback: Set Enviroment
 */
function _set_env($arg = '') {
  if ($arg == '') {
    drupal_set_message('Arguments must be dev or prod.', 'error');
    return;
  }
  if ($arg === 'prod') {
    variable_set('preprocess_css', 1);
    variable_set('preprocess_js', 1);
    variable_set('cache', 1);
    variable_set('block_cache', 1);
    variable_set('page_compression', 1);
    variable_set('error_level', 0);
    module_disable(array(
      'devel',
      'devel_generate',
      'views_ui',
      'update',
      'syslog',
      'dblog',
      'field_ui'
    ));
  }
  else {
    variable_set('preprocess_css', 0);
    variable_set('preprocess_js', 0);
    variable_set('cache', 0);
    variable_set('block_cache', 0);
    variable_set('page_compression', 0);
    variable_set('error_level', 1);
    module_enable(array(
      'devel',
      'devel_generate',
      'views_ui',
      'update',
      'syslog',
      'dblog',
      'field_ui'
    ));
  }
  // clear cache
  drupal_flush_all_caches();
  drupal_set_message('Env: ' . $arg, 'success');
}

/**
 * Callback: Get users
 */
function _get_admins() {
  $query = db_select('users', 'u');
  $query->innerJoin('users_roles', 'r', 'r.uid = u.uid');
  $query->condition('r.rid', 3);
  $query->condition('u.uid', 0, '<>');
  $query->fields('u', array('name'));
  $result = $query->execute();
  drush_print('-------------');
  drush_print('Get admin users:');
  while($record = $result->fetchAssoc()) {
    drush_print('* '.$record['name'], '2');
  }
  drush_print('-------------');
}

