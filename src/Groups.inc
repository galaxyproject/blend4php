<?php

/**
 * @file
 *
 * Implements the Groups class.
 *
 * The Group Class interacts with Galaxy to manage user groups and roles.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

/**
 * @defgroup group_class Groups Class
 * @{
 *   The Group Class interacts with Galaxy to manage user groups and roles.
 *   The functions in this class correspond to the Galaxy API functions and
 *   are named similarly to their Python counterpart.
 * @}
 */

include_once "GalaxyRequest.inc";


class Groups extends GalaxyRequest {

  /**
   * The Groups constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Groups object.
   *
   * @ingroup group_class
   */
  public function __construct($galaxy) {
    parent::__construct($galaxy);
  }

  /**
   * Displays a collection (list) of groups.
   *
   * Corresponds to the Galaxy API method and path: GET /api/groups.
   *
   * @return
   *   A JSON array of all groups.
   *
   * @ingroup group_class
   */
  public function index() {
    $URL = $this->galaxy->getURL() . '/api/groups/?key=' . $this->galaxy->getAPIKey();
    return $this->rest->GET($URL);
  }

  /**
   * Create a new group.
   *
   * Corresponds to the Galaxy API method and path: POST /api/groups.
   *
   * @param $name
   *   Name of the group.
   * @param $user_ids
   *   An array of user_ids, if any, to associate user id's to the group. Use
   *   the Users class to retrieve a list of users.
   * @param $role_ids
   *   An array of role_ids to associate any new roles to the group. Use the
   *   Roles class to retreive a list of existing role IDs.
   *
   * @return
   *   A JSON array of the group that contains the users and roles.
   *
   * @ingroup group_class
   */
  public function create($name, $user_ids = array(), $role_ids = array()) {

    $URL = $this->galaxy->getURL() . '/api/groups/?key=' . $this->galaxy->getAPIKey();
    $elements = array(
      'name' => $name,
      'user_ids' => $user_ids,
      'role_ids' => $role_ids
    );
    return $this->rest->POST($URL, $elements);
  }

  /**
   * Retreive information about a group.
   *
   * Corresponds to the Galaxy API method and path:
   * GET /api/groups/{encoded_group_id}
   *
   * @param $group_id
   *   The id of the specific group to show.  Group IDs can be found using the
   *   index() function of this class.
   * @return
   *   A JSON array containing details about the group.
   *
   * @ingroup group_class
   */
  public function show($group_id) {
    $URL = $this->galaxy->getURL() . '/api/groups/' . $group_id . '/?key=' . $this->galaxy->getAPIKey();
    return $this->rest->GET($URL);
  }

  /**
   * Supports changes to a group including the name, users and roles.
   *
   * Corresponds to the Galaxy API method and path:
   * POST /api/groups/{encoded_group_id}.
   *
   * @param $group_id,
   *   The id of the group to modify.  Group IDs can be found using the
   *   index() function of this class.
   * @param $name,
   *   A new name, if any, to call the group.
   * @param $user_ids
   *   An array of user_ids, if any, to associate user id's to the group. Use
   *   the Users class to retrieve a list of users.
   * @param $role_ids
   *   An array of role_ids to associate any new roles to the group. Use the
   *   Roles class to retreive a list of existing role IDs.
   *
   * @return
   *   A JSON array of the group that contains the users and roles.
   *
   * @ingroup group_class
   */
  public function update($group_id, $name = NULL, $user_ids = array(), $role_ids = array()) {
    $URL = $this->galaxy->getURL() . '/api/groups/' . $group_id . '/?key=' . $this->galaxy->getAPIKey();

    $elements = array(
      'user_ids' => $user_ids,
      'role_ids' => $role_ids
    );

    if ($name !=null) {
      $elements['name'] = $name;
    }

    return $this->rest->PUT($URL, $elements);
  }
}