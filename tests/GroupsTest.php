<?php
require_once '../galaxy.inc';
require_once './testConfig.inc';

class GroupsTest extends PHPUnit_Framework_TestCase {
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
   * Tests the create() function of the Groups class.
   *
   * @depends testInitGalaxy
   */
  public function testCreate($galaxy) {

    $groups = new Groups($galaxy);
    $users = new Users($galaxy);

    // First get the list of users that we'll add to our test group.
    $user_list = $users->index();
    $user_ids = array();
    foreach ($user_list as $user) {
      $user_ids[] = $user['id'];
    }

    // Case 1: Create a group without any users.
    $inputs = array();
    $inputs['name'] = uniqid('galaxy-php-test-group1-');

    $group = $groups->create($inputs);
    $this->assertTrue(is_array($group), $groups->getErrorMessage());

    // Case 2: Try recreating the group with the same name. We should
    // recieve a FALSE return value.
    $group = $groups->create($inputs);
    $this->assertFalse($group, 'If the group already exists the create() function should return FALSE: ' . print_r($group, TRUE));

    // Case 3: Create another group and add all the users to it.
    $inputs['name'] = uniqid('galaxy-php-test-group2-');
    $inputs['user_ids'] = $user_ids;
    $group = $groups->create($inputs);
    $this->assertTrue(is_array($group), $groups->getErrorMessage());
    // TODO: need a way to determine if all of the users were added to the group?

    // Case 4: Create another group and add a set of roles to it.  But, both
    // the Roles and the Groups class create() functions can both
    // accept groups and roles respectively, we have to repeat some of the
    // unit testing for each here, because we can't add roles to a group
    // if we don't have any roles in the database and we can't add roles
    // if we don't first test they can be added.
    $role_ids = array();
    $roles = new Roles($galaxy);

    // Create two roles without any users then use their IDs for a new group
    $roleinputs = array();
    $roleinputs['name'] = uniqid('galaxy-php-test-group-role-');
    $roleinputs['description'] = 'Test group role #1';
    $role = $roles->create($roleinputs);
    $this->assertTrue(is_array($role), $roles->getErrorMessage());
    $role_ids[] = $role[0]['id'];

    $roleinputs['name'] = uniqid('galaxy-php-test-group-role-');
    $roleinputs['description'] = 'Test group role #2';
    $role = $roles->create($roleinputs);
    $this->assertTrue(is_array($role), $roles->getErrorMessage());


    $inputs['role_ids'] = $role_ids;
    $inputs['name'] = uniqid('galaxy-php-test-group3-');
    $group = $groups->create($inputs);
    $this->assertTrue(is_array($group), $groups->getErrorMessage());

    // Return the last group created.
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
  function testIndex($galaxy) {

    $groups = new Groups($galaxy);

    // Case 1:  Are we getting an array?
    $groups_list = $groups->index();
    $this->assertTrue(is_array($groups_list), $groups->getErrorMessage());

    return $groups_list;
  }

  /**
   * Test the show() function of the Groups class.
   *
   * @depends testInitGalaxy
   * @depends testIndex
   */
  public function testShow($galaxy, $groups_list) {

    $groups = new Groups($galaxy);

    // Use the history ID of the first history in the list to test the
    // show() function.
    $inputs = array();
    $inputs['group_id'] = $groups_list[0]['id'];

    // Case 1:  Are we getting an array?  If so, that's all we need to
    // test. We don't need to do unit testing for galaxy. We assume the
    // array is correct.
    $group = $groups->show($inputs);
    $this->assertTrue(is_array($group), $groups->getErrorMessage());
  }

  /**
   * Test the update() function of the Groups class.
   *
   * This function has not been implemented by galaxy
   * @depends testInitGalaxy
   * @depends testCreate
   *
   */
  public function testUpdate($galaxy, $group) {
    global $config;
    $groups = new Groups($galaxy);

    // Case 1:  Change the name.
    $inputs = array();
    $inputs['group_id'] = $group['id'];
    $inputs['name'] = $group['name'] . '-updated';
    $updated_group = $groups->update($inputs);

    // A different approach is needed in order to see if the group is updated.
    // The word 'updated' is added to the name of the group.
    $isupdated = $groups->show(array('group_id' => $group['id']));
    preg_match("/updated$/", $isupdated['name'], $matches);
    $this->assertTrue(!empty($matches), $groups->getErrorMessage());
  }
}
