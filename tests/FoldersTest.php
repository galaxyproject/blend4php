<?php
require_once '../src/Folders.inc';
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';


class FoldersTest extends PHPUnit_Framework_TestCase {
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
  function testIndex($galaxy) {
    $folders = new Folders($galaxy);

    // Currently, the 'index' function is implemented in the Galaxy API.
    // Therefore we skip this test.
    //$folder_list = $folders->index();
    //$this->assertTrue(is_array($folder_list), $folders->getErrorMessage());

  }
  /**
   * Tests the show() function.
   *
   * @depends testInitGalaxy
   */
  function testShow($galaxy) {
    $folders = new Folders($galaxy);

    // $folder_list = $folders->show($folder_id);
  }
  /**
   * Tests the create() function.
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy) {
    $folders = new Folders($galaxy);

    $parent_folder_id = 0;
    $folder_name = uniqid('galaxy-php-test-folder1-');
    $folders->create($parent_folder_id, $folder_name, 'Test folder #1');
    $this->assertTrue(is_array($folder_list), $folders->getErrorMessage());

  }

  /**
   * Tests the delete() function.
   *
   * @depends testInitGalaxy
   */
  function testDelete($galaxy) {
    $folders = new Folders($galaxy);
  }

  /**
   * Tests the update() function.
   *
   * @depends testInitGalaxy
   */
  function testUpdate($galaxy) {
    $folders = new Folders($galaxy);
  }
  /**
   * Tests the setPermissions() function.
   *
   * @depends testInitGalaxy
   */
  function testSetPermissions($galaxy) {
    $folders = new Folders($galaxy);
  }
  /**
   * Tests the getPermissions() function.
   *
   * @depends testInitGalaxy
   */
  function testGetPermissions($galaxy) {
    $folders = new Folders($galaxy);
  }
}
