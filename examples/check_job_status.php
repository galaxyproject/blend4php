<?php

// Include the blend4php library.
require_once('../galaxy.inc');

// The domain name of the host to connect to.
$hostname  = 'usegalaxy.org';
// Port 443 is the typical port for HTTPS.
$port      = '443';
// The remote server uses HTTPS for secure connections.
$use_https = TRUE;
// The API key to use for connections will be provided on the command-line
// by the user calling this script.
$api_key   = $argv[1];

// Instantiate the Galaxy object.
$galaxy = new GalaxyInstance($hostname, $port, $use_https);
$galaxy->setAPIKey($api_key);

// Check the version of Galaxy.
$version = $galaxy->getVersion();
if (!$version) {
  print $galaxy->getErrorMessage() . "\n";
  exit -1;
}
print "Found Galaxy version: " . $version['version_major'] . "\n";

// Instantiate a GalaxyWorkflows object.
$gwf = new GalaxyWorkflows($galaxy);

// Get the list of workflows that the user currently has on the remote Galaxy
// server.
$workflows = $gwf->index();
print "You have the following workflows:\n";
foreach ($workflows as $index => $workflow) {
  print ($index + 1) . ". " . $workflow['name'] . "\n";
}

