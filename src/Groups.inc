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

include_once "HTTPRequest.inc";


class Groups extends HTTPRequest {
  private $galaxy;

  /**
   * The Groups constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Groups object.
   *
   * 
   */
  public function __construct($galaxy) {
    $this->galaxy = $galaxy;
    parent::__construct();
  }

  /**
   * Displays a collection (list) of groups.
   *
   * Corresponds to the Galaxy API method and path: GET /api/groups.
   *
   * @return
   *   An array of all groups.
   *
   * 
   */
  public function index() {
    $URL = $this->galaxy->getURL() . '/api/groups/?key=' . $this->galaxy->getAPIKey();
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
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
   *   An array of the group that contains the users and roles.
   *
   * 
   */
  public function create($name, $user_ids = array(), $role_ids = array()) {

    $URL = $this->galaxy->getURL() . '/api/groups/?key=' . $this->galaxy->getAPIKey();

    $inputs = array(
      'name' => $name,
    );

    if (count($user_ids) > 0) {
      $inputs['user_ids'] = json_encode($user_ids);
    }
    if (count($role_ids) > 0) {
      $inputs['role_ids'] = json_encode($role_ids);
    }

    $response = $this->httpPOST($URL, $inputs);
    $response = $this->expectArray($response);

    // For some reason we get an array containing the associative array with
    // the role details.  So, we'll just return the associative array.
    // TODO: find out if this is a bug in Galaxy API or if if its intended.
    if (is_array($response)) {
      return $response[0];
    }
    else {
      return $response;
    }
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
   *   An array containing details about the group.
   *
   * 
   */
  public function show($group_id) {
    $URL = $this->galaxy->getURL() . '/api/groups/' . $group_id . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
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
   *   An array of the group that contains the users and roles.
   *
   * 
   */
  public function update($group_id, $name = NULL, $user_ids = array(), $role_ids = array()) {

/*     $URL = $this->galaxy->getURL() . '/api/groups/' . $group_id . '/?key=' . $this->galaxy->getAPIKey();

    $inputs = array();

    if ($name) {
      $inputs['name'] = $name;
    }
    if (count($user_ids) > 0) {
      $inputs['user_ids'] = json_encode($user_ids);
    }
    if (count($role_ids) > 0) {
      $inputs['role_ids'] = json_encode($role_ids);
    } */

/*     if (count($inputs) == 0) {
      $this->setError('API', "At least one optional argument must be provided to the Groups::update() function.");
      return FALSE;
    } */

    $response = False;
    $this->setError('API', "This funciton has not been implemented by Galaxy. You can view our discussion on the issue here: https://github.com/galaxyproject/galaxy/issues/1987");
    return $this->expectArray($response);
  }
}