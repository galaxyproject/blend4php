<?php
require_once '../galaxy.inc';
require_once './testConfig.inc';


class FolderContentsTest extends PHPUnit_Framework_TestCase {
  /**
   * Intializes the Galaxy object for all of the tests.
   *
   * This function provides the $galaxy object to all other tests as they
   * are dependent on this one.
   */
  function testInitGalaxy() {
    global $config;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
    $success = $galaxy->authenticate($config['email'], $config['pass']);
    $this->assertTrue($success, $galaxy->getErrorMessage());

    return $galaxy;
  }

  /**
   * Tests the index() function.
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy) {
    $folder_contents = new FolderContents($galaxy);
    $folders = new Folders($galaxy);

  }
}
