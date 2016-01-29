<?php
require_once '.././src/GalaxyInstance.inc';
require_once '.././src/Workflows.inc';

$galaxy = new GalaxyInstance('localhost','8080', FALSE);
$galaxy->authenticate('cgpwytko@gmail.com', 'potato15');

$wfc = new Workflows($galaxy);

// I want to get a popular workflow or a list of work flows automatically
// imported to the user's base website.

/**
 * Ask to place the dummy workflow/workflows to gather and place in a directory
 * that will be created from the current directory
 */

print getcwd() . "\n";
chdir("$HOME");
print getcwd() . "\n";