<?php
function devudo_drush_command() {
  $items['devudo-create-server'] = array(
    'callback' => 'devudo_drush_create_server', 
    'description' => dt('Create a new server for devudo.'), 
    'aliases' => array('dcs'), 
    'examples' => array(
    ), 
    'arguments' => array(
      'server-name' => dt('The name of the new server.'),
    ),
   'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );
  return $items;
}

/**
 * Attempt to create server.
 * Stolen from https://github.com/rackspace/php-opencloud/blob/master/samples/compute/create.php
 */
function devudo_drush_create_server($name = 'My New Server'){
  drush_log('[DEVUDO] Hello, devudo-create-server.');

  ini_set('include_path', '/usr/share/php-opencloud/lib:'.ini_get('include_path'));

  require_once('rackspace.inc');
  require_once('compute.inc');
  require_once('network.inc');
  
  // @TODO: make these drush options
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

  $options = array();

  // @TODO: options
  //  os_distro, os_version

  // STEP 1: Choose Image
  $list = $compute->ImageList();
  while ($image = $list->Next()) {
    $images[$image->id] = $image;
    $options['images'][$image->id] = $image->name;
  }
  
  // Look for drush option
  $image_id = drush_get_option('image_id');

  // If no option set, ask.
  if (empty($image_id)){
    asort($options['images']);
    $image_id = drush_choice($options['images'], 'Choose an OS');
  }
  
  // Save for later.
  $chosen_image = $images[$image_id];
  print_r($chosen_image);

  // STEP 2: Choose Flavor
  $list = $compute->FlavorList();
  while ($flavor = $list->Next()) {
    $flavors[$flavor->id] = $flavor;
    $options['flavors'][$flavor->id] = $flavor->name;
  }
  
  // Look for drush option
  $flavor_id = drush_get_option('flavor_id');

  // If no option set, ask.
  if (empty($flavor_id)){
    asort($options['flavors']);
    $flavor_id = drush_choice($options['flavors'], 'Choose an Flavor');
  }

  // Save for later
  $chosen_flavor = $flavors[$flavor_id];

  // STEP 3: Request Server
  $server = $compute->Server();

  // Set server properties
  $server->name = $name;
  $server->Create(array(
		'image' => $chosen_image,
		'flavor' => $chosen_flavor,
  ));
  
  // Let the user know we are waiting on it.
  drush_log("Server Requested, Now waiting on Server: " . $server->id, 'ok');
  
  //@TODO: Active doesn't mean ready!
  $server->WaitFor("ACTIVE", 1200, 'devudo_drush_create_server_complete');
 
}

function devudo_drush_create_server_complete($server) {
  if ($server->status == 'ACTIVE'){
    drush_log("Server Build Complete!");
    drush_log("Your server is now available at ". $server->ip());
    drush_log("Your root password is ". $server->adminPass);
  } else {
    drush_log('Server is being built...');
    
    if ($server->adminPass){
      drush_log("Your root password is ". $server->adminPass);    
    }
    
    if ($server->ip()){
      drush_log("Your IP is ". $server->ip());    
    }
  }
}
