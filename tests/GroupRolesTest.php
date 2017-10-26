<?php

require_once './testConfig.inc';
require_once '../galaxy.inc';

class GroupRolesTest extends phpunit_5.6_Class {

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
   * Prepares a group with roles for further testing.
   *
   * This function does not correspond to a function in the GroupUsers Class.
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy) {

    global $config;

    // Add a new role for this test.
    $roles = new GalaxyRoles($galaxy);
    $role = $roles->create(array(
      'name' => uniqid('galaxy-php-test-group-role1-'),
      'description' => 'Group Role Test Role #1'
    ));
    $this->assertTrue(is_array($role), $galaxy->getErrorMessage());

    // Create a new group to be used for testing by this class, and
    // add users to it.
    $groups = new GalaxyGroups($galaxy);
    $group = $groups->create(array(
      'role_ids' => array($role[0]['id']),
      'name' => uniqid('galaxy-php-test-group_role1-')
    ));
    $this->assertTrue(is_array($group), $galaxy->getErrorMessage());

    return $group;
  }

  /**
   * Tests the index() function.
   *
   * The index function retrieves a list of users.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testIndex($galaxy, $group) {

    // Create  Users object.
    $group_roles = new GalaxyGroupRoles($galaxy);

    // Case 1:  Are we getting an array.
    $roles_list = $group_roles->index(array('group_id' => $group['id']));
    $this->assertTrue(is_array($roles_list), $galaxy->getErrorMessage());

    // Case 2:  The index() function failes. We should get false.
    $roles_list2 = $group_roles->index('not-a-real-group-id');
    $this->assertTrue($roles_list2 === FALSE);

    return $roles_list;
  }

  /**
   * Test the show() function.
   *
   * The show function retreives information on a specific user
   *
   * @depends testInitGalaxy
   * @depends testCreate
   * @depends testIndex
   */
  function testShow($galaxy, $group, $roles_list){

    $group_roles = new GalaxyGroupRoles($galaxy);

    // Use the user ID of the first user in the list to test the
    // show() function.
    $role_id = $roles_list[0]['id'];
    $group_id = $group['id'];

    // Case 1:  Get the user information for the config user.
    $roles_list = $group_roles->show(array(
      'group_id' => $group_id,
      'role_id' => $role_id
    ));
    $this->assertTrue(is_array($roles_list), $galaxy->getErrorMessage());

    // Case 2: Wrong group id entered. We should get a FALSE value instead
    // of an error.
    $role = $group_roles->show('not-a-real-group-id', $role_id);
    $this->assertTrue($role === FALSE, "GroupRoles::show should have failed when a bogus group_id was provided: " . print_r($role, TRUE));

    // Case 3: Wrong Role id entered. We should get a FALSE value instead.
    $role = $group_roles->show($group_id, 'not-a-real-role-id');
    $this->assertTrue($role === FALSE, "GroupRoles::show should have failed when a bogus role_id was provided: " . print_r($role, TRUE));
  }

  /**
   * Test the update() function of the GroupRoles class.
   *
   * @depends testInitGalaxy
   *
   */
  public function testUpdate($galaxy) {
    global $config;

    $group_roles = new GalaxyGroupRoles($galaxy);

    $users = new GalaxyUsers($galaxy);
    $user_id = $users->getUserID($config['user']);

    // Case 1: First add a new group for testing of an update. We need to
    // gaurantee that the user we add isn't already in the group so
    // the way to make sure this is true is to add a new group.
    $groups = new GalaxyGroups($galaxy);
    $group_name = uniqid('galaxy-php-test-group_roles2-');
    $group = $groups->create(array('name' => $group_name));
    $this->assertTrue(is_array($group), $galaxy->getErrorMessage());

    // Case 2: Test that this group has no roles.
    $roles_list = $group_roles->index(array('group_id' => $group['id']));
    $this->assertTrue(is_array($roles_list), $galaxy->getErrorMessage());
    $this->assertTrue(count($roles_list) == 0, "The group should have no users, but it does: " . print_r($roles_list, TRUE));

    // Case 3:  Add the role and make sure we get a group array back.
    $roles = new GalaxyRoles($galaxy);
    $role_name = uniqid('galaxy-php-test-group-role2-');
    $role = $roles->create(array(
      'name' => $role_name,
      'description' => 'Group Role Test Role #2'
    ));
    $this->assertTrue(is_array($role), $galaxy->getErrorMessage());

    $role = $group_roles->update(array(
      'group_id' => $group['id'],
      'role_id' => $role[0]['id']
    ));
    $this->assertTrue(is_array($role), $galaxy->getErrorMessage());

    // Case 4:  Make sure the role is added to the group.
    $roles_list = $group_roles->index(array('group_id' => $group['id']));
    $this->assertTrue(is_array($roles_list), $galaxy->getErrorMessage());
    $this->assertTrue(count($roles_list) == 1, "The group should have a single users, but does not: " . print_r($roles_list, TRUE));

    return $group;
  }

  /**
   * Test the create()
   *
   * @depends testInitGalaxy
   * @depends testUpdate
   */
  function testDelete($galaxy, $group){

    $group_roles = new GalaxyGroupRoles($galaxy);

    $group_id = $group['id'];
    $roles_list = $group_roles->index(array('group_id' => $group_id));

    $this->assertTrue(is_array($roles_list), $galaxy->getErrorMessage());
    $role_id = $roles_list[0]['id'];

    // Case 1: The delete function should return an array of the group.
    $role = $group_roles->delete(array(
      'group_id' => $group_id,
      'role_id' => $role_id
    ));
    $this->assertTrue(is_array($role), $galaxy->getErrorMessage());

    // Case 2: There should be no users left in the group
    $roles_list = $group_roles->index(array('group_id' => $group['id']));
    $this->assertTrue(is_array($roles_list), $galaxy->getErrorMessage());
    $this->assertTrue(count($roles_list) == 0, "The group should have no roles, but it does: " . print_r($roles_list, TRUE));

  }
}
