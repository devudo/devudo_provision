<?php


/**
 * Implementation of hook_drush_command().
 *
 * A total rip off of hostmaster-install.
 *
 * This is because 'profile' => 'hostmaster' is hard coded!
 */
function devudo_provision_drush_command() {
  
  // Ensure provision is installed before using its functions
  if (function_exists('provision_command')){
    $items['devmaster-install'] = array(
      'description' => dt('Install and verify the Devmaster frontend.'),
      'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
      'arguments' => array(
        'example.com' => dt('The URL of the site to install, optional (default: %host).', array('%host' => provision_fqdn())),
      ),
      'options' => array(
       'http_service_type' => dt('Webserver type to configure (default: %webserver)', array('%webserver' => 'apache')),
       'drush_make_version' => dt('Drush make version to install, if not present (default: %drush_make', array('%drush_make' => '6.x-2.3')),
       'aegir_db_host' => dt('Database host to connect to (default: %host)', array('%host' => 'localhost')),
       'aegir_db_user' => dt('Database user to connect as (default: %user)', array('%user' => 'root')),
       'aegir_db_pass' => dt('Database password to use'),
       'client_email' => dt('Email of the first client to create in the frontend'),
       'client_name' => dt('Name of the first client to create in the frontend (default: %user)', array('%user' => 'admin')),
       'aegir_host' => dt('Fully qualified domain name of the local server (default: %fqdn)', array('%fqdn' => provision_fqdn())),
       'script_user' => dt('User to run the backend as (default: %user)', array('%user' => provision_current_user())),
       'web_group' => dt('Group the webserver is running as (default: %group)', array('%group' => _provision_default_web_group())),
       'version' => dt('The version of this released. (default: %version)', array('%version' => provision_version())),
       'aegir_root' => dt('Install aegir in this home directory (default: %home). Do not change unless you know what you are doing.', array('%home' => drush_server_home())),
       'makefile' => dt('The Drupal installation profile to use for installing the front-end (default: hostmaster)'),
      ),
    );

    return $items;
  }
}