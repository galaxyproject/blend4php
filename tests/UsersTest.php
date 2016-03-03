<?php

require_once '../src/GalaxyInstance.inc';
require_once '../src/Users.inc';
require_once './testConfig.inc';

class UsersTest extends PHPUnit_Framework_TestCase {
  /**
   *  Tests the index() function.
   *
   *  The index function retrieves a list of users.
   */
  function testIndex() {
    global $config;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
    $response = $galaxy->authenticate($config['user'], $config['pass']);

    // Create  Users object.
    $users = new Users($galaxy);

    // Case 1: Retrieve an array of all users
    $user_list = $users->index();
    print $users->getError();
    print_r($user_list);

  }
}
