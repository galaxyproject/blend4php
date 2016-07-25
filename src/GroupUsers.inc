<?php

require_once('GalaxyAPIService.inc');

/**
 * @file
 *
 * Implements the GroupUsers class.
 *
 * The GroupUsers Class interacts with Galaxy to manage groups of users.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

class GalaxyGroupUsers extends GalaxyAPIService {

   /**
    * Displays a collection (list) of users corresponding to a group..
    *
    * Corresponds to an HTTP GET on the Galaxy API path 
    *   /api/groups/{encoded_group_id}/users.
    *
    * @param $params
    *   An associative array containing the input parameters for this function.
    *   The following parameters are available:
    *
    *   - group_id:  The ID of a group's users to list.  Group IDs can
    *       be found using Groups::index().
    *
    * @return
    *   An array of all users of a given group.
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
    
    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/users/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive information about a specific group user.
   *
   * Corresponds to an HTTP GET on the Galaxy API path 
   *   /api/groups/{encoded_group_id}/users/{encoded_user_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - group_id: The ID of a group to show.  Group IDs can be
   *       found using Groups::index().
   *   - user_id: The ID of a specific user to show. User IDS can be found
   *       using Users::index().
   *
   * @return
   *   An array containing details about the user of a given group.
   */
  public function show($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('group_id', 'user_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('group_id', 'user_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/users/' . $params['user_id'] .'/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Adds a user to a given group.
   *
   * Corresponds to an HTTP PUT on the Galaxy API path 
   *   /api/groups/{encoded_group_id}/users/{encoded_user_id}.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - group_id: The ID of a group to modify. Group IDs can be found using
   *       Groups::index().
   *   - user_id: A user ID to associate any new users to the group. Use
   *       Users::index() to retreive a list of existing user IDs.
   *
   * @return
   *   An array of the user that has added to the group
   */
  public function update($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('group_id', 'user_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('group_id', 'user_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/users/' . $params['user_id'] .'/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpPUT($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Deletes a user from a given group.
   *
   * Corresponds to an HTTP DELETE on the Galaxy API path 
   *   /api/groups/{encoded_group_id}/users/{encoded_user_id}.
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - group_id:  The ID of the group to delete a user. Group IDs can be
   *       found using  Groups::index().
   *   - user_id: A user ID to deassociate user(s) from a group. Use
   *       Users::index() to retreive a list of user IDs.
   *
   * @return
   *   An array of the user that has been removed from the group.
   */
  public function delete($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('group_id', 'user_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('group_id', 'user_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/users/' . $params['user_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response =  $this->galaxy->httpDELETE($URL);
    return $this->galaxy->expectArray($response);
  }
}
