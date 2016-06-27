<?php

require_once('GalaxyAPIService.inc');

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

class GalaxyGroups extends GalaxyAPIService {

  /**
   * Displays a collection (list) of groups.
   *
   * Corresponds to the Galaxy API method and path: GET /api/groups.
   *
   * @return
   *   An array of all groups.
   */
  public function index() {
    $URL = $this->galaxy->getURL() . '/api/groups/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Create a new group.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/groups.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - name: Name of the group.
   *   - user_ids: (Optional) An array of user_ids, if any, to associate user id's to the
   *       group. Use the Users::index() to retrieve a list of users.
   *   - role_ids: (Optional) An array of role_ids to associate any new roles to the
   *       group. Use the Roles::index() to retreive a list of existing role IDs.
   *
   * @return
   *   An array of the group that contains the users and roles.
   */
  public function create($params){

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('name'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('name', 'user_ids', 'role_ids'))) {
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
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/groups/{encoded_group_id}
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - group_id: The ID of the specific group to show.  Group IDs can be
   *     found using Groups::index().
   *
   * @return
   *   An array containing details about the group.
   */
  public function show($params) {
    
      // Check for required fields.
    if (!$this->checkRequiredParams($params, array('group_id'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('group_id'))) {
      return FALSE;
    }
    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Supports changes to a group including the name, users and roles.
   *
   * Corresponds to an HTTP PUT on the Galaxy API path
   *   /api/groups/{encoded_group_id}.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *     - group_id: The ID of the group to modify.  Group IDs can be found
   *         using Groups::index().
   *     - name: (Optional) A new name to call the group.
   *     - user_ids: An array of user_ids, if any, to associate user id's to
   *         the group. Use Users::index() to retrieve a list of users.
   *     - role_ids: An array of role_ids to associate any new roles to the
   *         group. Use the Roles::index() class to retreive a list of existing role IDs.
   *
   * @return
   *   An array of the group that contains the users and roles.
   *
   *
   */
  public function update($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('group_id'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('group_id', 'name', 'user_ids', 'role_ids'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/?key=' . $this->galaxy->getAPIKey();

    if (array_key_exists('user_ids', $params))
      $params['user_ids'] = json_encode($user_ids);

    if (array_key_exists('role_ids', $params))
      $params['role_ids'] = json_encode($role_ids);

    $response = $this->galaxy->httpPUT($URL, $params);
    return $response;
  }
}
