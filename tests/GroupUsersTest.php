<?php
require_once  '../galaxy.inc';
require_once './testConfig.inc';


class GroupUsersTest extends PHPUnit_Framework_TestCase {

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
   * Prepares a group with users for further testing.
   *
   * This function does not correspond to a function in the GroupUsers Class.
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy) {

    global $config;

    // Add the user from the config file..
    $users = new GalaxyUsers($galaxy);
    $user_id = $users->getUserID($config['user']);
    $user_ids = array($user_id);

    // Create a new group to be used for testing by this class, and
    // add users to it.
    $groups = new GalaxyGroups($galaxy);
    $group_name = uniqid('galaxy-php-test-group_users-');
    $group = $groups->create($group_name, $user_ids);
    $this->assertTrue(is_array($group), $galaxy->getErrorMessage());

    return $group;
  }

  /**
  * Tests the index() function.
  *
  * The index function retrieves a list of groups.
  *
  * @depends testInitGalaxy
  * @depends testCreate
  */
  function testIndex($galaxy, $group) {

    $group_users = new GalaxyGroupUsers($galaxy);

    // Case 1:  Are we getting an array, and are we getting only 1 users.
    $users_list = $group_users->index($group['id']);
    $this->assertTrue(is_array($users_list), $galaxy->getErrorMessage());
    $this->assertTrue(count($users_list) == 1, "The GroupUsers::index() function does not return a single user: " . print_r($users_list, TRUE));
    return $users_list;
  }

  /**
  * Test the show() function of the Groups class.
  *
  * @depends testInitGalaxy
  * @depends testCreate
  */
  public function testShow($galaxy, $group) {
    global $config;

    $group_users = new GalaxyGroupUsers($galaxy);

    $users = new GalaxyUsers($galaxy);
    $user_id = $users->getUserID($config['user']);

    $group_id = $group['id'];

    // Case 1:  Are we getting an array for the user.
    $user = $group_users->show($group_id, $user_id);
    $this->assertTrue(is_array($user), $galaxy->getErrorMessage());

    // Case 2: Wrong group id entered. We should get a FALSE value instead
    // of an error.
    $user = $group_users->show('not-a-real-group-id', $user_id);
    $this->assertTrue($user === FALSE, "GroupUsers::show should have failed when a bogus group_id was provided: " . print_r($user, TRUE));

    // Case 3: Wrong user id entered. We should get a FALSE value instead.
    $user = $group_users->show($group_id, 'not-a-real-role-id');
    $this->assertTrue($user === FALSE, "GroupUsers::show should have failed when a bogus user_id was provided: " . print_r($user, TRUE));

  }

  /**
   * Test the update() function of the Groups class.
   *
   * @depends testInitGalaxy
   *
   */
  public function testUpdate($galaxy) {
    global $config;

    $group_users = new GalaxyGroupUsers($galaxy);

    $users = new GalaxyUsers($galaxy);
    $user_id = $users->getUserID($config['user']);

    // Case 1: First add a new group for testing of an update. We need to
    // gaurantee that the user we add isn't already in the group so
    // the way to make sure this is true is to add a new group.
    $groups = new GalaxyGroups($galaxy);
    $group_name = uniqid('galaxy-php-test-group_users2-');
    $group = $groups->create($group_name);
    $this->assertTrue(is_array($group), $galaxy->getErrorMessage());

    // Case 2: Test that this group has no users.
    $group_users = new GalaxyGroupUsers($galaxy);
    $users_list = $group_users->index($group['id']);
    $this->assertTrue(is_array($users_list), $galaxy->getErrorMessage());
    $this->assertTrue(count($users_list) == 0, "The group should have no users, but it does: " . print_r($users_list, TRUE));

    // Case 3:  Add the user and make sure we get a group array back.
    $user = $group_users->update($group['id'], $user_id);
    $this->assertTrue(is_array($user), $galaxy->getErrorMessage());

    // Case 4:  Make sure the user is added to the group.
    $users_list = $group_users->index($group['id']);
    $this->assertTrue(is_array($users_list), $galaxy->getErrorMessage());
    $this->assertTrue(count($users_list) == 1, "The group should have a single users, but does not: " . print_r($users_list, TRUE));

    return $group;
  }

  /**
   * Test the delete() function of the Groups class.
   *
   * @depends testInitGalaxy
   * @depends testUpdate
   *
   */
  public function testDelete($galaxy, $group) {
    global $config;

    $group_users = new GalaxyGroupUsers($galaxy);

    $users = new GalaxyUsers($galaxy);
    $user_id = $users->getUserID($config['user']);
    $group_id = $group['id'];

    // Case 1: The delete function should return an array of the group.
    $deleted_group = $group_users->delete($group_id, $user_id);
    $this->assertTrue(is_array($deleted_group), $galaxy->getErrorMessage());

    // Case 2: There should be no users left in the group
    $users_list = $group_users->index($group['id']);
    $this->assertTrue(is_array($users_list), $galaxy->getErrorMessage());
    $this->assertTrue(count($users_list) == 0, "The group should have no users, but it does: " . print_r($users_list, TRUE));

  }
}
