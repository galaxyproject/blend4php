<?php

require_once('GalaxyAPIService.inc');

/**
 * @file
 *
 * The GalaxyUsers class.
 *
 * The Users class interacts with Galaxy to manage contents of a Galaxy
 * User. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

class GalaxyUsers extends GalaxyAPIService {

  /**
   * Displays a collection of Galaxy users.
   *
   * Corresponds to an HTTP GET on the Galaxy API paths
   *   /api/users 
   *   and
   *   /api/users/deleted
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - deleted: (Optional) If true, show deleted users.
   *   - f_email: (Optional) An email address to filter results based on.
   *   - f_name: (Optional) A username to filter results based on.
   *   - f_any: (Optional) If true, Filter on username OR email.
   *
   * @return
   *   An array containing information on the the users.
   */
  function index($params) {
    $URL = $this->galaxy->getURL() .'/api/users' . '/?key=' . $this->galaxy->getAPIKey();

    if(array_key_exists('deleted', $params))
      $URL .= '/?deleted=' . $params['deleted'];

    if (array_key_exists('f_name', $params))
      $URL .= '&f_name=' . $params['f_name'];

    if (array_key_exists('f_email', $params))
      $URL .= '&f_email=' . $params['f_email'];

    if (array_key_exists('f_any', $params))
      $URL .= '&f_any=' . $params['f_any'];

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive detailed information on a specific user.
   *
   * Corresponds to an HTTP GET on the Galaxy API paths
   *   /api/users/{encoded_user_id}
   *   /api/users/current
   *   /api/users/deleted/{encoded_user_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - user_id: (Optional) The ID of the user whos details to retreive. To obtain a user
   *       ID use Users::index().
   *   - deleted: (Optional) If set to TRUE, will show deleted users.
   *   - current: (Default) If neither of the above parameters are set then
   *       present details of current user.
   *       
   * @return
   *   An array containing the details of the user.
   */
  function show($params) {

    if(array_key_exists('deleted', $params) and $params['deleted'] == TRUE)
      $URL = $this->galaxy->getURL() . '/api/users/deleted/';

    else if(array_key_exists('user_id', $params))
      $URL = $this->galaxy->getURL() . '/api/users/' . $params['user_id'];

    else
      $URL = $this->galaxy->getURL() . '/api/users/current';

    $URL .= '/?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Creates a new API key for specified user.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/users/{encoded_user_id}/api_key
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - user_id: The ID of the specified user. To obtain a user ID, use
   *       Users::index().
   *
   * @return
   *   The API key of the user.
   */
  function apiKey($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('user_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('user_id'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/users/' . $params['user_id'] . '/api_key/?key=' . $this->galaxy->getAPIKey();
    return $this->galaxy->httpPOST($URL);
  }

  /**
   * Creates new galaxy user.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/users
   *   
   * For this method to work, the Galaxy instance must have the allow_user_creation
   * option set to True and use_remote_user option set to False in the
   * config/galaxy.ini configuration file.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - username: The username of the new user.
   *   - email: The email of the new user.
   *   - password: The password of the new user.
   *
   * @return
   *   An array containing details of the new user. On failure FALSE is
   *   returned.
   */
  function create($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('username', 'email', 'password'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('username', 'email', 'password'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/users/' . '?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  /**
   * The actual python implementation is not complete
   */
  function update() {
  }

  /**
   * The actual python implementation is not complete
   */
  function undelete() {
  }

  /**
   * Mark a given user as deleted
   *
   * Corresponds to an HTTP DELETE on the Galaxy API path
   *   /api/users/{id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - user_id: The ID of the user to delete. To obtain a user id, use
   *       Users::index().
   *   - purge: (Optional) If true, the user will be completely erased from Galaxy.
   *
   * @return
   *   An array containing details of the deleted user, or FALSE on failure.
   */
  function delete($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('user_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('username', 'user_id', 'purge'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/users/' . $params['user_id'] . '?key=' . $this->galaxy->getAPIKey();

    if (array_key_exists('purge', $params) and $params['purge'] == TRUE)
      $URL .= '&purge=True';

    $response =  $this->galaxy->httpDELETE($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retrieves the ID of a Galaxy user.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - username: The name of the user.
   *
   * @return
   *   A string containing the user ID or FALSE if the user could not be found.
   */
  function getUserID($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('username'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('username'))) {
      return FALSE;
    }

    // Get the index and iterate through until we find our user.
    $users = $this->index(array());

    foreach($users as $user){
      if($user['username'] == $params['username']){
        return $user['id'];
      }
    }
    return FALSE;
  }
  
}

