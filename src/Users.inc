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

/**
 * @defgroup users_class Users Class
 * @{
 *   The Users class interacts with Galaxy to manage contents of a Galaxy
 *   user. The functions in this class correspond to the Galaxy API
 *   functions and are named similarly to their Python counterparts.
 * @}
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
    * @param deleted
    *   (optional) If true, show deleted users.
    * @param email
    *   (optional) An email address to filter results based on.
    * @param name
    *   (optional) A username to filter results based on.
    * @param any
    *   (optional) If true, Filter on username OR email.
    *
    * @return
    *   An array containing information on the the users the  API function
    *   retreived
    *
    *
    */
   function index($deleted = false, $email = NULL, $username = NULL, $any = false) {
     $endURL = "&key=" . $this->galaxy->getAPIKey();
     $URL = $this->galaxy->getURL() .'/api/users';
     $URL .= '/?deleted=' . $deleted;
     if ($username !=NULL) {
       $URL .= '&f_name=' . $username;
     }

     if ($email !=NULL) {
       $URL .= '&f_email=' . $email;
     }

     if ($any !=false) {
       $URL .= '&f_any=' . $any;
     }
     $URL .= $endURL;
     // $URL2 = $this->galaxy->getURL() . '/api/users/deleted'. $user_id ."/api_key/?key=" . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Retreive detailed information on a specific user.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/users/{encoded_user_id}
   *
   * @param user_id
   *   The id of the user whos details to retreive. To obtain a user id
   *   please use this class's index() function.
   *
   * @return
   *   An array containing the details of the user.
   *
   *
   */
  function show($user_id) {
    $URL = $this->galaxy->getURL() .'/api/users/' .$user_id .'/?key=' .$this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Creates a new API key for specified user.
   *
   * Corresponds to the Galaxy API/path
   *   POST /api/users/{encoded_user_id}/api_key
   *
   * @param user_id
   *   The id of the specified user. To obtain a user id, please use this
   *   class's index function.
   *
   * @return
   *   The API key of the user.
   *
   *
   */
  function apiKey($user_id) {
    $URL = $this->galaxy->getURL() . '/api/users/' . $user_id . '/api_key/?key=' . $this->galaxy->getAPIKey();
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
   * @param username
   *   The username of the new user.
   * @param user_email
   *   The email of the new user.
   * @param password
   *   The password of the new user.
   *
   * @return
   *   An array containing details of the new user. On failure FALSE is
   *   returned.
   *
   *
   */
  function create($username, $user_email, $password) {
    $URL = $this->galaxy->getURL() . '/api/users/' . '?key=' . $this->galaxy->getAPIKey();

    $input = array(
      'username' => $username,
      'email' => $user_email,
      'password' => $password
    );

    $response = $this->galaxy->httpPOST($URL, $input);
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
   * @param user_id
   *   The id of the user to delete. To obtain a user id, please use
   *   this class's index function.
   * @param purge
   *   (Optional) if true, the user will be completely erased from Galaxy.
   *
   * @return
   *   An array containing details of the deleted user, or FALSE on failure.
   *
   *
   */
  function delete($user_id, $purge = FALSE) {

    $URL = $this->galaxy->getURL() . '/api/users/' . $user_id . '?key=' . $this->galaxy->getAPIKey();
    if ($purge) {
      $URL .= '&purge=True';
    }
    $response =  $this->galaxy->httpDELETE($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retrieves the ID of a Galaxy user.
   *
   * @param $username
   *   The name of the user.
   * @return
   *   A string containing the user ID or FALSE if the user could not be found.
   */
  function getUserID($username) {
    // Get the index and iterate through until we find our user.
    $users = $this->index();

    foreach($users as $user){
      if($user['username'] == $username){
        return $user['id'];
      }
    }
    return FALSE;
  }
}

?>
