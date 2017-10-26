<?php

require_once '../galaxy.inc';
require_once './testConfig.inc';

class RolesTest extends phpunit_5.6_Class {

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
   * The index function retrieves a list of roles.
   *
   * @depends testInitGalaxy
   */
  function testIndex($galaxy) {

    $roles = new GalaxyRoles($galaxy);

    // Case 1:  Are we getting an array?
    $roles_list = $roles->index();
    $this->assertTrue(is_array($roles_list), $galaxy->getErrorMessage());

    return $roles_list;
  }

  /**
   * Test the show() function of the Histories class.
   *
   * @depends testInitGalaxy
   * @depends testIndex
   *
   */
  public function testShow($galaxy, $roles_list) {

    $roles = new GalaxyRoles($galaxy);

    // Use the history ID of the first history in the list to test the
    // show() function.
    $inputs = array(
      "role_id" => $roles_list[0]['id']
    );

    // Case 1:  Are we getting an array?  If so, that's all we need to
    // test. We don't need to do unit testing for galaxy. We assume the
    // array is correct.
    $role = $roles->show($inputs);
    $this->assertTrue(is_array($role), $galaxy->getErrorMessage());
  }

  /**
   * Tests the create() function of the Histories class.
   *
   * @depends testInitGalaxy
   * @depends testShow
   */
  public function testCreate($galaxy) {

    $roles = new GalaxyRoles($galaxy);
    $users = new GalaxyUsers($galaxy);

    // First get the list of users that we'll add to our test role.
    $user_list = $users->index(array());
    $user_ids = array();
    foreach ($user_list as $user) {
      $user_ids[] = $user['id'];
    }

    // Case 1: Create a role without any users.
    $inputOne = array(
      "name" => uniqid('galaxy-php-test-create1-'),
      "description" => 'Test role #1'
    );

    $role = $roles->create($inputOne);
    $this->assertTrue(is_array($role), $galaxy->getErrorMessage());

    // Case 2: Try recreating the role with the same name. We should
    // recieve a FALSE return value.
    $role = $roles->create($inputOne);
    $this->assertFalse($role, 'If the role already exists the create() function should return FALSE: ' . print_r($role, TRUE));

    // Case 3: Create another role and add all the users to it.

    $inputTwo = array(
      "name" => uniqid('galaxy-php-test-create2-'),
      "description" => 'Test role #2',
      "user_ids" => $user_ids
    );
    $role = $roles->create($inputTwo);
    $this->assertTrue(is_array($role), $galaxy->getErrorMessage());
    // TODO: need a way to determine if all of the users were added to the role?

    // Case 4: Create another role and add a set of groups to it.  But, both
    // the Roles and the Groups class create() functions can both
    // accept groups and roles respectively, we have to repeat some of the
    // unit testing for each here, because we can't add groups to a role
    // if we don't have any groups in the database and we can't add groups
    // if we don't first test they can be added.
    $groups = new GalaxyGroups($galaxy);
    $group_ids = array();

    // Create two groups without any users then use their IDs for a new role
    $groupInput = array();
    $groupInput['name'] = uniqid('galaxy-php-test-role-group1-');
    $group = $groups->create($groupInput);
    $this->assertTrue(is_array($group), $galaxy->getErrorMessage());
    $group_ids[] = $group['id'];

    $groupInput['name'] = uniqid('galaxy-php-test-role-group2-');
    $group = $groups->create($groupInput);
    $this->assertTrue(is_array($group), $galaxy->getErrorMessage());
    $group_ids[] = $group['id'];

    $inputThree = array(
      "name" => uniqid('galaxy-php-test-create3-'),
      "description" => 'Test role #3',
      "group_ids" => $group_ids
    );
    $role = $roles->create($inputThree);
    $this->assertTrue(is_array($role), $galaxy->getErrorMessage());
    // TODO: need a way to determine if the groups were added to the role?

    // Case 5: Create another user and add both users and groups.
    $inputFour = array(
      "name" => uniqid('galaxy-php-test-create4-'),
      "description" => 'Test role #4',
      "user_ids" => $user_ids,
      "group_ids" => $group_ids
    );
    $role = $roles->create($inputFour);
    $this->assertTrue(is_array($role), $galaxy->getErrorMessage());
    // TODO: need a way to determine if the users and groups were added to the role?
  }
}
