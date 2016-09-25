<?php

# Include the blend4php library.
require_once('../galaxy.inc');

# Get the incoming arguments.
$hostname  = $argv[1];
$port      = $argv[2];
$use_https = $argv[3];
$api_key   = $argv[4];
$username  = $argv[5];
$email     = $argv[6];
$password  = $argv[7];

# Instantiate the Galaxy object.
$galaxy = new GalaxyInstance($hostname, $port, $use_https);
$galaxy->setAPIKey($api_key);

# Test the connection to Galaxy.
$version = $galaxy->getVersion();
if (!$version) {
  print "Cannot connect to the Galaxy server. Exiting.\n";
}

# Instantiate the User's API object.
$usersAPI = new GalaxyUsers($galaxy);

# Create the new User
$user = $usersAPI->create(array(
  'username' => $username,
  'email' => $email,
  'password' => $password,
));

# Set the API Key for this user. It is the
# current API associated with the galaxy object.
$usersAPI->apiKey(array(
  'user_id' => $user['id'],
));

