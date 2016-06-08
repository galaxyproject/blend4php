<?php
require_once '../galaxy.inc';
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
    $folders = new GalaxyFolders($galaxy);

    // Case 1: The index function is currently not implemented.
    // Gracefully return false.
   $folder_list = $folders->index();
   $this->assertFalse(is_array($folder_list), $galaxy->getErrorMessage());

  }


  /**
   * Tests the show() function.
   *
   * @depends testInitGalaxy
   */
  function testShow($galaxy) {
    $folders = new GalaxyFolders($galaxy);

    // Any library is treated as a folder
    $libraries = new GalaxyLibraries($galaxy);


    $inputs['folder_id'] = "987";
    $folder = $folders->show($inputs);
    $this->assertFalse(is_array($folder), $galaxy->getErrorMessage());

    $inputs['folder_id'] = $libraries->index(array())[0]['id'];
    $folder = $folders->show($inputs);
    $this->assertTrue(is_array($folder), $galaxy->getErrorMessage());

    return $inputs;
  }


  /**
   * Tests the create() function.
   *
   * @depends testInitGalaxy
   * @depends testShow
   */
  function testCreate($galaxy, $inputs) {
    $folders = new GalaxyFolders($galaxy);

    // Create a folder to retain as
    $inputs['parent_folder_id'] = $inputs['folder_id'];
    unset($inputs['folder_id']);
    $inputs['name'] = uniqid('galaxy-php-test-folder1-');
    $inputs['description'] = 'Folder Unit Test 1';
    $folder = $folders->create($inputs);
    $this->assertTrue(is_array($folder), $galaxy->getErrorMessage());


    $inputs['parent_folder_id'] = $inputs['folder_id'];
    unset($inputs['folder_id']);
    $inputs['name'] = uniqid('galaxy-php-test-folder-toBeDeleted-');
    $inputs['description'] = 'Folder Unit Test Which will be \'deleted\' by the subsequent unit test delete function';
    $folder = $folders->create($inputs);
    $this->assertTrue(is_array($folder), $galaxy->getErrorMessage());

    return $folder;

  }

  /**
   * Tests the delete() function.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testDelete($galaxy, $folder) {
    $folders = new GalaxyFolders($galaxy);

    $inputs['folder_id'] = $folder['id'];
    $response = $folders->delete($inputs);
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

  }

//   /**
//    * Tests the update() function.
//    *
//    * @depends testInitGalaxy
//    */
//   function testUpdate($galaxy) {
//     $folders = new GalaxyFolders($galaxy);
//   }
//   /**
//    * Tests the setPermissions() function.
//    *
//    * @depends testInitGalaxy
//    */
//   function testSetPermissions($galaxy) {
//     $folders = new GalaxyFolders($galaxy);
//   }
//   /**
//    * Tests the getPermissions() function.
//    *
//    * @depends testInitGalaxy
//    */
//   function testGetPermissions($galaxy) {
//     $folders = new GalaxyFolders($galaxy);
//   }
}
