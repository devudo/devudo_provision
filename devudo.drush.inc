<?php
function devudo_drush_command() {
  $items['devudo-create-server'] = array(
    'callback' => 'devudo_drush_create_server', 
    'description' => dt('Create a new server for devudo.'), 
    'aliases' => array('dcs'), 
    'examples' => array(
    ), 
    'arguments' => array(
    ),
   'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.

  );
  return $items;
}

/**
 * Attempt to create server.
 * Stolen from https://github.com/rackspace/php-opencloud/blob/master/samples/compute/create.php
 */
function devudo_drush_create_server(){
  drush_log('[DEVUDO] Hello, devudo-create-server.');

  

  require_once('opencloud/rackspace.inc');
  require_once('opencloud/compute.inc');
  
  // RACKSPACE
  define('AUTHURL', 'https://identity.api.rackspacecloud.com/v2.0/');
  define('USERNAME', 'careernerd');
  define('TENANT', 'devudo');
  define('APIKEY', 'e93596076f1a3bd404d6a8b790b8a96b');

  // establish our credentials
  $connection = new OpenCloud\Rackspace(AUTHURL,
    array( 'username' => USERNAME,
      'tenantName' => TENANT,
      'apiKey' => APIKEY ));

  // now, connect to the compute service
  $compute = $connection->Compute('cloudServersOpenStack', 'DFW');

  // first, find the image
  $ilist = $compute->ImageList();
  $found = FALSE;
  $distro = "org.openstack__1__os_distro";
  $version = "org.openstack__1__os_version";
  while (!$found && $image = $ilist->Next()) {
   printf("Checking image %s...", $image->name);
  }
}



