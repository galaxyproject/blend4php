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

class GalaxyGroups  {
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
  public function __construct(GalaxyInstance $galaxy) {
    $this->galaxy = $galaxy;
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
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Create a new group.
   *
   * Corresponds to the Galaxy API method and path: POST /api/groups.
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - name: Name of the group.
   *   - user_ids: An array of user_ids, if any, to associate user id's to the
   *       group. Use the Users class to retrieve a list of users.
   *   - role_ids: An array of role_ids to associate any new roles to the
   *       group. Use the Roles class to retreive a list of existing role IDs.
   *
   * @return
   *   An array of the group that contains the users and roles.
   *
   *
   */
  public function create($params){

    if(!array_key_exists('name', $params)){
      $this->galaxy->setError('API', "Please provide a 'name'  as an input to this function.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/groups/?key=' . $this->galaxy->getAPIKey();

    if (array_key_exists('user_ids', $params))
      $params['user_ids'] = json_encode($params['user_ids']);

    if (array_key_exists('role_ids', $params))
      $params['role_ids'] = json_encode($params['role_ids']);

    $response = $this->galaxy->httpPOST($URL, $params);
    $response = $this->galaxy->expectArray($response);

    // For some reason we get an array containing the associative array with
    // the role details.  So, we'll just return the associative array.
    // TODO: find out if this is a bug in Galaxy API or if if its intended.
    // https://github.com/tripal/blend4php/issues/14
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
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *     - group_id: The id of the specific group to show.  Group IDs can be
   *         found using the index() function of this class.
   *
   * @return
   *   An array containing details about the group.
   *
   *
   */
  public function show($params) {
    if(!array_key_exists('group_id', $params)){
      $this->galaxy->setError("API", "A 'group_id' is required to show metadata about a group");
      return FALSE;
    }
    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Supports changes to a group including the name, users and roles.
   *
   * Corresponds to the Galaxy API method and path:
   * PUT /api/groups/{encoded_group_id}.
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *     - group_id: The id of the group to modify.  Group IDs can be found
   *         using the index() function of this class.
   *     - name: A new name, if any, to call the group.
   *     - user_ids: An array of user_ids, if any, to associate user id's to
   *         the group. Use the Users class to retrieve a list of users.
   *     - role_ids: An array of role_ids to associate any new roles to the
   *         group. Use the Roles class to retreive a list of existing role IDs.
   *
   * @return
   *   An array of the group that contains the users and roles.
   *
   *
   */
  public function update($params) {
    // If the user does not include an update to the name, group_ids, role_ids
    // then reject the update
    if (array_key_exists('user_ids', $params) or array_key_exists('role_ids', $params) or array_key_exists('name', $params)){
     $this->galaxy->setError('API', "At least one optional argument (name, user_ids, role_ids) must be provided to the Groups::update() function.");
     return FALSE;
   }
    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/?key=' . $this->galaxy->getAPIKey();
    //$params['key'] = $this->galaxy->getAPIKey();
    if (array_key_exists('user_ids', $params))
      $params['user_ids'] = json_encode($user_ids);

    if (array_key_exists('role_ids', $params))
      $params['role_ids'] = json_encode($role_ids);

    $response = $this->galaxy->httpPUT($URL, $params);
    return $response;// $this->galaxy->expectArray($response);
  }
}
