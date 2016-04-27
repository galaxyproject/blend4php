<?php
/**
 * @file
 *
 * The Roles class.
 *
 * The Roles class interacts with Galaxy to manage contents of a Galaxy
 * Role. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

include_once "HTTPRequest.inc";

class Roles extends HTTPRequest{

  private $galaxy;

  /**
   * The Roles constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a roles object.
   *
   * 
   */
  public function __construct($galaxy) {
    parent ::__construct();
    $this->galaxy = $galaxy;
  }

  /**
   * Retreive a list of all of Galaxy's roles.
   *
   * Corresponds to the Galaxy API/path:
   *   GET /api/roles
   *
   * @return
   *   An array containing details of all the roles in Galaxy.
   *
   * 
   */
  public function index(){
    $URL = $this->galaxy->getURL() . '/api/roles/?key=' . $this->galaxy->getAPIKey();
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }

  /**
   * Retreive details about a specific Galaxy role.
   *
   * Corresponds to the Galaxy API/path:
   *   GET /api/roles/{encoded_id}
     *
   * @param $role_id
   *   The id of the role whos informaiton to retreive. Please use
   *   this class's index function to retreive a list of role id's.
   *
   * @return
   *   An array containing details about the specified role.
   *
   * 
   */
  public function show($role_id){
    $URL = $this->galaxy->getURL() . '/api/roles/' . $role_id . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }


  /**
   * Creates a new role.
   *
   * Corresponds to the Galaxy Api/path:
   *   POST /api/roles
   * NOTE: only type admin can be applied for new roles
   *
   * @param $name
   *   The name of the new role.
   * @param $description
   *   The description of the new role.
   * @param $user_ids
   *   An array of user ids to associate the new role with.
   *   To obtain a user id, please use the index() function of
   *   the users class.
   * @param $group_ids
   *   An array of group id's to associate the new role with.
   *   To obtain a group id, please use the index() function of the
   *   groups class.
   *
   * @return
   *   An array containing informaiton about the new role.
   *
   * 
   */
  public function create($name, $description, $user_ids = array(), $group_ids = array()) {

    $URL = $this->galaxy->getURL() . '/api/roles/?key=' . $this->galaxy->getAPIKey();

    $inputs = array(
      'name' => $name,
      'description' => $description,
    );

    if (count($user_ids) > 0) {
      $inputs['user_ids'] = json_encode($user_ids);
    }
    if (count($group_ids) > 0) {
      $inputs['group_ids'] = json_encode($group_ids);
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
}