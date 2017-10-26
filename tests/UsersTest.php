<?php
require_once '../galaxy.inc';
require_once './testConfig.inc';


class UsersTest extends phpunit56Class {

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
   * The index function retrieves a list of users.
   *
   * @depends testInitGalaxy
   */
  function testIndex($galaxy) {
    global $config;

    // Create  Users object.
    $users = new GalaxyUsers($galaxy);

    // Case 1:  Are we getting an array?
    $users_list = $users->index(array());
    $this->assertTrue(is_array($users_list), $galaxy->getErrorMessage());

    // Case 2: Is the array properly formatted such that it contains the user
    // that is running this test.
    $contains_user = FALSE;
    foreach($users_list as $user){
      $this->assertTrue(array_key_exists('username', $user), "Malformed users array: missing username: " . print_r($users_list, TRUE));
      $this->assertTrue(array_key_exists('id', $user), "Malformed users array: missing id: " . print_r($users_list, TRUE));
      if($user['username'] == $config['user']){
        $contains_user = TRUE;
        break;
      }
    }
    $this->assertTrue($contains_user, "index() function works but user is missiing: " . print_r($users_list, TRUE));

    // TODO: test all of the arugments of the index() function.

    return $users_list;
  }

  /**
   * Test the show() function.
   *
   * The show function retreives information on a specific user
   *
   * @depends testInitGalaxy
   * @depends testIndex
   */
  function testShow($galaxy, $users_list){
    global $config;

    $users = new GalaxyUsers($galaxy);

    // Use the user ID of the first user in the list to test the
    // show() function.
    $user_id = $users_list[0]['id'];

    // Case 1:  Get the user information for the config user.
    $response = $users->show(array( 'user_id' => $user_id));
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

    // Case 2: Wrong user id entered. We should get a FALSE value instead
    // of an error.
    $response = $users->show(array('user_id' => "123456"));
    $this->assertTrue($response === FALSE, "Showing user should have failed: " . print_r($response, TRUE));

  }

  /**
   * Test the getUserID() function.
   *
   * @depends testInitGalaxy
   */
  function testGetUserID($galaxy) {
    global $config;

    $users = new GalaxyUsers($galaxy);

    // Case 1:  Test for a false user.
    $user_id = $users->getUserID(array('username' => 'asdjasldfjasldfjaslfjaslfjaslfjasdf'));
    $this->assertFalse($user_id, "Retreiving the user should have failed: " . print_r($user_id, TRUE));

    // Case 2: Test for a real user id.
    $user_id = $users->getUserID(array('username' => $config['user']));
    $this->assertTrue($user_id !== FALSE, $galaxy->getErrorMessage());
  }


  /**
   * Test the create()
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy){
    global $config;

    $users = new GalaxyUsers($galaxy);

    // Case 1: Successful creation of a new user.
    $inputs = array();
    $inputs['username'] = uniqid('galaxy-php-test-create-');
    $inputs['email'] = $inputs['username'] . '@test.com';
    $inputs['password'] = 'password';
    $response = $users->create($inputs);
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

    unset($inputs);
    // Case 2: Failed creation of a user.
    $inputs['username'] = uniqid('galaxy-php-test-create-');
    $inputs['email'] = $inputs['username'] . '@@@@test.com';
    $inputs['password'] = 'password';
    $response = $users->create($inputs);
    $this->assertTrue($response === FALSE, "Creation should fail but didn't:" . print_r($response, TRUE));
  }



  /**
   * Test the create()
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testDelete($galaxy){
    global $config;

    $users = new GalaxyUsers($galaxy);

    // Create a new user for testing of delete.
    $inputs = array();
    $inputs['username'] = uniqid('galaxy-php-test-delete-');
    $inputs['email'] = $inputs['username'] . '@test.com';
    $inputs['password'] = 'password';
    $user = $users->create($inputs);

    // Case 1: Make sure we get a proper response.
    $response = $users->delete(array('user_id' => $user['id']));
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

    // Case 2: Make sure the user is marked as deleted
    $this->assertTrue(array_key_exists('deleted', $response), "Missing 'deleted' in response array." . print_r($response, TRUE));
    $this->assertTrue($response['deleted'], 'User not marked as deleted: ' . print_r($response, TRUE));

    // Case 3: Make sure the user is marked as purged
    // The purge option has not yet been formally implemented.  So this
    // test must be commented out for now.
    /*
    $response = $users->delete($user['id'], TRUE);
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());
    $this->assertTrue(array_key_exists('deleted', $response), "Missing 'deleted' in response array." . print_r($response, TRUE));
    $this->assertTrue($response['purged'], 'User not marked as purged: ' . print_r($response, TRUE));
    */
  }

   /**
    * Test the api key function
    *
    * generates a new api key for a user
    *
    * @depends testInitGalaxy
    * @depends testCreate
    */
   function testAPIKey($galaxy){
     global $config;

     $users = new GalaxyUsers($galaxy);

     // First create a new user for testing the change of API Key.
     $inputs = array();
     $inputs['username'] = uniqid('galaxy-php-test-apikey-');
     $inputs['email'] = $inputs['username'] . '@test.com';
     $inputs['password'] = 'password';
     $user = $users->create($inputs);

     // Case 1: Test the return of false.
     $api_key = $users->apiKey(array('user_id' => ''));
     $this->assertTrue($api_key === FALSE, "Creating API Key should have failed:" . print_r($api_key, TRUE));

     // Case 2: Test creation of an API key
     $api_key = $users->apiKey(array('user_id' => $user['id']));
     $this->assertTrue($api_key !== FALSE, $galaxy->getErrorMessage());
   }
}
