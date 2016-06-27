<?php

require_once('GalaxyAPIService.inc');

/**
 * @file
 *
 * The Roles class.
 *
 * The Roles class interacts with Galaxy to manage contents of a Galaxy
 * Role. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

class GalaxyRoles extends GalaxyAPIService {


  /**
   * Retreive a list of all of Galaxy's roles.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/roles
   *
   * @return
   *   An array containing details of all the roles in Galaxy.
   */
  public function index() {
    
    $URL = $this->galaxy->getURL() . '/api/roles/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive details about a specific Galaxy role.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/roles/{encoded_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - role_id: The ID of a role to retreive information. Use Roles::index()
   *       to retreive a list of role ID's.
   *
   * @return
   *   An array containing details about the specified role.
   */
  public function show($params){
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('role_id'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('role_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/roles/' . $params['role_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }


  /**
   * Creates a new role.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/roles
   *
   * NOTE: Only an admin can create new roles
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - name: The name of the new role.
   *   - description: The description of the new role.
   *   - user_ids: (Optional) An array of user ids to associate the new role with.
   *       To obtain a user id, please use the index() function of
   *       the users class.
   *   - group_ids: (Optional) An array of group id's to associate the new role with.
   *       To obtain a group id, please use the index() function of the
   *       groups class.
   *
   * @return
   *   An array containing informaiton about the new role.
   */
  public function create($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('name', 'description'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('name', 'description', 'user_ids', 'group_ids'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/roles/?key=' . $this->galaxy->getAPIKey();

    if(array_key_exists('name', $params) and array_key_exists('description', $params)){
      if(array_key_exists('user_ids', $params))
        $params['user_ids'] = json_encode($params['user_ids']);

      if(array_key_exists('group_ids', $params))
        $params['group_ids'] = json_encode($params['group_ids']);

      $response = $this->galaxy->httpPOST($URL, $params);
      $response = $this->galaxy->expectArray($response);

      return $response;
    }

    $this->galaxy->setError('API', 'Please provide at least a \'name\' AND \'description\' as inputs to this funciton.');
    return FALSE;

    $response = $this->galaxy->httpPOST($URL, $params);
    $response = $this->galaxy->expectArray($response);

    return $response;
  }
}
