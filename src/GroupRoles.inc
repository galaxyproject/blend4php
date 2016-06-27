<?php

require_once('GalaxyAPIService.inc');

/**
 * @file
 *
 * Implements the GroupsRoles class.
 *
 * The GroupRoles Class interacts with Galaxy to manage user groups and roles.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */
class GalaxyGroupRoles extends GalaxyAPIService {
  
  /**
   * Displays a collection (list) of roles corresponding to a group..
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/groups/{encoded_group_id}/roles.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - group_id: The ID of the group to list roles. Group IDs can be
   *       found using Groups::index().
   *
   * @return
   *   An array of all group roles for a given group.
   */
  public function index($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('group_id'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('group_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/roles/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive information about a specific group role.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/groups/{encoded_group_id}/roles/{encoded_role_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - group_id: The ID of the group to list roles. Group IDs can be
   *       found using Groups::index().
   *   - role_id: The ID of a specific role to show. Role IDS can be found
   *       using Roles::index().
   *
   * @return
   *   An array containing details about the role of a given gorup.
   */
  public function show($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('group_id', 'role_id'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('group_id', 'role_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/roles/' . $params['role_id']. '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Supports adding a role to a given group.
   *
   * Corresponds to an HTTP PUT on the Galaxy API path
   *   /api/groups/{encoded_group_id}/roles/{encoded_role_id}.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - group_id: The ID of the group to list roles. Group IDs can be
   *       found using Groups::index().
   *   - role_id: The ID of a specific role to add. Role IDS can be found
   *       using Roles::index().
   *
   * @return
   *   An array of the role that was added to the group
   */
  public function update($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('group_id', 'role_id'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('group_id', 'role_id'))) {
      return FALSE;
    }
    
     $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/roles/' . $params['role_id'] . '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpPUT($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Supports deleting a role from a given group.
   *
   * Corresponds to an HTTP DELETE on the Galaxy API path
   *   /api/groups/{encoded_group_id}/roles/{encoded_role_id}.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - group_id: The ID of the group to list roles. Group IDs can be
   *       found using Groups::index().
   *   - role_id: The ID of a specific role to delete. Role IDS can be found
   *       using Roles::index().
   *
   * @return
   *   An array of the role that was removed from the group.
   */
  public function delete($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('group_id', 'role_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('group_id', 'role_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/roles/' . $params['role_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpDELETE($URL);
    return $this->galaxy->expectArray($response);
  }
  
}
