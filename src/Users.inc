<?php
/**
 * @file
 *
 * The GalaxyUsers class.
 *
 * The Users class interacts with Galaxy to manage contents of a Galaxy
 * User. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

class GalaxyUsers {

  private $galaxy;

  /**
   * The Users constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Users object.
   *
   *
   */
   function __construct($galaxy) {
     $this->galaxy = $galaxy;
   }

  /**
    * Displays a collection of Galaxy users.
    *
    * Corresponds to the Galaxy API/paths at
    *   GET /api/users and
    *   GET /api/users/deleted
    *
    * @param $params
    *   A key value (associative array) where the keys can be the following:
    *
    *   - deleted (Optional): If true, show deleted users.
    *   - f_email (Optional): An email address to filter results based on.
    *   - f_name (Optional): A username to filter results based on.
    *   - f_any (Optional): If true, Filter on username OR email.
    *
    * @return
    *   An array containing information on the the users.
    *
    *
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
   * Corresponds to the Galaxy API path
   *   GET /api/users/{encoded_user_id}
   *   GET /api/users/current
   *   GET /api/users/deleted/{encoded_user_id}
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - user_id (Optional): The id of the user whos details to retreive. To obtain a user
   *       id please use this class's index() function.
   *   - deleted (Optional): If set to TRUE, will show deleted users.
   *   - current (Default): If neither of the above parameters are set then
   *       present details of current user.
   * @return
   *   An array containing the details of the user.
   *
   *
   */
  function show($params) {
    if(array_key_exists('deleted', $params) and $params['deleted'] == TRUE and !array_key_exists('user_id', $params)){
      $this->setError("API", "Provide a 'user_id' along with the 'delete' parameter.");
      return FALSE;
    }

    if(array_key_exists('deleted', $params) and $params['deleted'] == TRUE)
      $URL = $this->galaxy->getURL() . '/api/users/deleted/' . $params['user_id'];

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
   * Corresponds to the Galaxy API/path
   *   POST /api/users/{encoded_user_id}/api_key
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - user_id: The id of the specified user. To obtain a user id, please use
   *       this class's index function.
   *
   * @return
   *   The API key of the user.
   *
   *
   */
  function apiKey($params) {
    if(!array_key_exists('user_id', $params)){
      $this->setError("API", "Specify a 'user_id' in order to generate a new API key.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/users/' . $params['user_id'] . '/api_key/?key=' . $this->galaxy->getAPIKey();
    return $this->galaxy->httpPOST($URL);
  }

  /**
   * Creates new galaxy user.
   *
   * Corresponds to the Galaxy API/path
   *   POST  /api/users
   * For this method to work, the Galaxy instance must have the allow_user_creation
   * option set to True and use_remote_user option set to False in the
   * config/galaxy.ini configuration file.
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - username: The username of the new user.
   *   - user_email: The email of the new user.
   *   - password: The password of the new user.
   *
   * @return
   *   An array containing details of the new user. On failure FALSE is
   *   returned.
   *
   *
   */
  function create($params) {
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
   * Corresponds to the Galaxy API/path
   *   DELETE /api/users/{id}
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - user_id: The id of the user to delete. To obtain a user id, please use
   *     this class's index function.
   *   - purge (Optional): If true, the user will be completely erased from Galaxy.
   *
   * @return
   *   An array containing details of the deleted user, or FALSE on failure.
   *
   *
   */
  function delete($params) {
    if(!array_key_exists('user_id', $params)){
      $this->setError("API", "To delete a user, you must specify a 'user_id'.");
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
   *   A key value (associative array) where the keys can be the following:
   *
   *   - username: The name of the user.
   *
   * @return
   *   A string containing the user ID or FALSE if the user could not be found.
   */
  function getUserID($params) {
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

?>
