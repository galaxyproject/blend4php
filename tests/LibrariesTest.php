<?php
require_once '../src/Libraries.inc';
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';

class LibrariesTest extends PHPUnit_Framework_TestCase {
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
   * Tests the create() function.
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy) {
    $libraries = new Libraries($galaxy);

    // Case 1: Create a new library.
    $library_name = uniqid('galaxy-php-test-library1-');
    $library = $libraries->create($library_name, 'Test library #1', 'Synopsis string.');
    $this->assertTrue(is_array($library), $libraries->getErrorMessage());

    // Case 2: Fail creating a library.
    $library_fail = $libraries->create('', 'Test library #1', 'Synopsis string.');
    $this->assertTrue($library_fail === FALSE, $libraries->getErrorMessage());

    return $library;
  }

  /**
   * Tests the update() function.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testUpdate($galaxy, $library) {
    $libraries = new Libraries($galaxy);

    // This function is not yet implemented in our API.
  }

  /**
   * Tests the delete() function.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testDelete($galaxy, $library) {
    $libraries = new Libraries($galaxy);

    // Case 1: The delete function should return an array.
    $library_id = $library['id'];
    $library = $libraries->delete($library_id);
    $this->assertTrue(is_array($library), $libraries->getErrorMessage());
    $this->assertTrue($library['deleted'], "The library should be deleted but it's not: " . print_r($library, TRUE));

    // Case 2:  Try not passing a library_id.  The function should return FALSE.
    $library = $libraries->delete('');
    $this->assertTrue($library === FALSE, $libraries->getErrorMessage());

    // TODO: The 'undelete' argument doesn't seem to work, and I suspect
    // this is a Galaxy API issue, so the test below is commented out until
    // we can verify.
 /*
    // Case 3: Undelete the library deleted in case #1.
    $library = $libraries->delete($library_id, TRUE);
    $this->assertTrue(is_array($library), $libraries->getErrorMessage());
    $this->assertFalse($library['deleted'], "The library should be undeleted but it's not: " . print_r($library, TRUE));

    // Mark the library as deleted again for further testing
    $library = $libraries->delete($library_id); */

  }

  /**
   * Tests the index() function.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   * @depends testDelete
   */
  function testIndex($galaxy, $library) {
    $libraries = new Libraries($galaxy);

    // Create a new library for this test.
    $library_name = uniqid('galaxy-php-test-library2-');
    $library = $libraries->create($library_name, 'Test library #2', 'Synopsis string.');
    $this->assertTrue(is_array($library), $libraries->getErrorMessage());

    // Case 1:  Get the list of non deleted libraries.  We should have at least the
    // one we created above.
    $library_list = $libraries->index();
    $this->assertTrue(is_array($library_list), $libraries->getErrorMessage());
    $this->assertTrue(count($library_list) > 0, $libraries->getErrorMessage());

    // TODO: The 'delete' argument doesn't seem to work. I think this is
    // a Galaxy API problem, so the tests below are commented out until
    // we can verify.
/*
    // Case 2: Make sure all of the libraries are not deleted.
    $all_undeleted = TRUE;
    foreach ($library_list as $library) {
      if ($library['deleted']) {
        $all_undeleted = FALSE;
      }
    }
    $this->assertTrue($all_undeleted, "The index() should only return non-deleted libraries: " . print_r($library_list, TRUE));


    // Case 3:  Get the list of deleted libraries. We should have at least the
    // one we deleted in the testDelete() function above.
    $library_list = $libraries->index(TRUE);
    $this->assertTrue(is_array($library_list), $libraries->getErrorMessage());
    $this->assertTrue(count($library_list) > 0, $libraries->getErrorMessage());

    // Case 4: Make sure all of the libraries are deleted.
    $all_deleted = TRUE;
    foreach ($library_list as $library) {
      if (!$library['deleted']) {
        $all_deleted = FALSE;
      }
    }
    $this->assertTrue($all_deleted, "The index(TRUE) should only return deleted libraries: " . print_r($library_list, TRUE));
 */
  }
  /**
   * Tests the show() function.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testShow($galaxy, $library) {
    $libraries = new Libraries($galaxy);

    // Case 1: Get a library that is not deleted.
    $library_id = $library['id'];
    $library = $libraries->show($library_id);
    $this->assertTrue(is_array($library), $libraries->getErrorMessage());

    // TODO: because of the problems with the delete testing in previous,
    // functions we'll wait to implement testing of the 'deleted'
    // argument
  }


  /**
   * Tests the setPermissions() function.
   *
   * @depends testInitGalaxy
   */
  function testSetPermissions($galaxy) {
    $libraries = new Libraries($galaxy);
  }
  /**
   * Tests the getPermissions() function.
   *
   * @depends testInitGalaxy
   */
  function testGetPermissions($galaxy) {
    $libraries = new Libraries($galaxy);
  }
}
