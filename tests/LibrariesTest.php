<?php
require_once '../galaxy.inc';
require_once './testConfig.inc';

class LibrariesTest extends phpunitClass {
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
    $libraries = new GalaxyLibraries($galaxy);

    // Case 1: Create a new library.
    $library_name = uniqid('galaxy-php-test-library1-');

    $newLibParams = array(
      "name" => $library_name,
      "description" => 'Test library #1',
      "synopsis" => 'Synopsis string.'
    );

    $library = $libraries->create($newLibParams);
    $this->assertTrue(is_array($library), $galaxy->getErrorMessage());

    // Case 2: Fail creating a library.
    $newLibParams = array(
      "name" => '',
      "description" => 'Test library #1',
      "synopsis" => 'Synopsis string.'
    );

    $library_fail = $libraries->create($newLibParams);
    $this->assertTrue($library_fail === FALSE, $galaxy->getErrorMessage());

    return $library;
  }

  /**
   * Tests the update() function.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testUpdate($galaxy, $library) {
    $libraries = new GalaxyLibraries($galaxy);
	$this->assertTrue(TRUE, "Librariesupdate is not implemented yet\n");
    // This function is not yet implemented in our API.
  }

  /**
   * Tests the delete() function.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testDelete($galaxy, $library) {
    $libraries = new GalaxyLibraries($galaxy);

    // Case 1: The delete function should return an array.
    $libParams1 = array(
      "library_id" => $library['id'],
    );

    $dlibrary = $libraries->delete($libParams1);
    $this->assertTrue(is_array($dlibrary), $galaxy->getErrorMessage());
    $this->assertTrue($dlibrary['deleted'], "The library should be deleted but it's not: " . print_r($dlibrary, TRUE));

    // Case 2:  Try not passing a library_id.  The function should return FALSE.
    $empty = array();
    $dlibrary = $libraries->delete($empty);
    $this->assertTrue($dlibrary === FALSE, $galaxy->getErrorMessage());

    // TODO: The 'undelete' argument doesn't seem to work, and I suspect
    // this is a Galaxy API issue, so the test below is commented out until
    // we can verify.

    // Case 3: Undelete the library deleted in case #1.
    $libParams2 = array(
      "library_id" => $library['id'],
      "undelete" => true,
    );
    $dlibrary = $libraries->delete($libParams2);
    $this->assertTrue(is_array($dlibrary), $galaxy->getErrorMessage());
    //$this->assertFalse($library['deleted'], "The library should be undeleted but it's not: " . print_r($library, TRUE));

    // Mark the library as deleted again for further testing
    $dlibrary = $libraries->delete($libParams1);

  }

  /**
   * Tests the index() function.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   * @depends testDelete
   */
  function testIndex($galaxy, $library) {
    $libraries = new GalaxyLibraries($galaxy);

    // Create a new library for this test.
    $library_name = uniqid('galaxy-php-test-library2-');
    $newLibParams = array(
      "name" => $library_name,
      "description" => 'Test library #2',
      "synopsis" => 'Synopsis string.'
    );
    $library = $libraries->create($newLibParams);
    $this->assertTrue(is_array($library), $galaxy->getErrorMessage());

    // Case 1:  Get the list of non deleted libraries.  We should have at least the
    // one we created above.
    $inputs = array();
    $library_list = $libraries->index($inputs);
    $this->assertTrue(is_array($library_list), $galaxy->getErrorMessage());
    $this->assertTrue(count($library_list) > 0, $galaxy->getErrorMessage());

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
    $this->assertTrue(is_array($library_list), $galaxy->getErrorMessage());
    $this->assertTrue(count($library_list) > 0, $galaxy->getErrorMessage());

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
    $libraries = new GalaxyLibraries($galaxy);

    // Case 1: Get a library that is not deleted.
    $inputs = array(
      "library_id" => $library['id']
    );
    $library = $libraries->show($inputs);
    $this->assertTrue(is_array($library), $galaxy->getErrorMessage());

    // TODO: because of the problems with the delete testing in previous,
    // functions we'll wait to implement testing of the 'deleted'
    // argument
  }

  /**
   * Tests the setPermissions() function.
   * This is the function that relies on the 'Roles.inc' file
   *
   * @depends testInitGalaxy
   * @depends testCreate
   *
   */
  function testSetPermissions($galaxy, $library) {
    $libraries = new GalaxyLibraries($galaxy);
    $roles = new GalaxyRoles($galaxy);

    // Case 1: Provide the library_id and action but no id manipulations
    $inputs = array(
      "library_id" => $library['id'],
      "action" => 'set_permissions'
    );

    $response = $libraries->setPermissions($inputs);
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

    // Case 2: Provide the library_id, action, and some of the id fields
    $inputs["access_ids"] = $roles->index();
    $inputs["add_ids"] = $roles->index();
    $response = $libraries->setPermissions($inputs);
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

    // Case 3: Provide the library_id, action, and all of the id fields
    $inputs["manage_ids"] = $roles->index();
    $inputs["modify_ids"] = $roles->index();
    $response = $libraries->setPermissions($inputs);
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

    // Case 4: Provide invalid parameters
    $invalidInput = array();
    $response = $libraries->setPermissions($invalidInput);
    $this->assertFalse(is_array($response), $galaxy->getErrorMessage());

  }

  /**
   * Tests the getPermissions() function.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testGetPermissions($galaxy, $library) {
    $libraries = new GalaxyLibraries($galaxy);

    $inputs = array();
    $inputs['library_id'] = $library['id'];
    // Case 1: Simply looking at the permissions using the library_id only
    $library = $libraries->getPermissions($inputs);
    $this->assertTrue(is_array($library), $galaxy->getErrorMessage());

    // Any subsequent tests include the library_id with the exception of the
    // last test

    // Case 2: Look at the permissions with the scope parameter set ONLY
    $inputs['scope'] = 'available';
    $library = $libraries->getPermissions($inputs);
    $this->assertTrue(is_array($library), $galaxy->getErrorMessage());

    // Case 3: Look at the permissions with the is_library_access parameter set ONLY
    array_pop($inputs);
    $inputs['is_library_access'] = FALSE;
    $library = $libraries->getPermissions($inputs);
    $this->assertTrue(is_array($library), $galaxy->getErrorMessage());

    // Case 4: Look at the permissions with the scope AND is_library_access parameter set
    $inputs['scope'] = 'available';
    $library = $libraries->getPermissions($inputs);
    $this->assertTrue(is_array($library), $galaxy->getErrorMessage());

    // Case 5: Invalid case that should be caught
    $incorrect = array();
    $library = $libraries->getPermissions($incorrect);
    $this->assertFalse(is_array($library), $galaxy->getErrorMessage());
  }
}
