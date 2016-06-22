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

class GalaxyRoles {

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
  public function __construct(GalaxyInstance $galaxy) {
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
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive details about a specific Galaxy role.
   *
   * Corresponds to the Galaxy API/path:
   *   GET /api/roles/{encoded_id}
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - role_id: The id of the role whos informaiton to retreive. Please use
   *       this class's index function to retreive a list of role id's.
   *
   * @return
   *   An array containing details about the specified role.
   *
   *
   */
  public function show($params){
    if(!array_key_exists('role_id', $params)){
      $this->galaxy->setError('API', 'Please provide a value for the \'role_id\' argument.');
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/roles/' . $params['role_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);

  }


  /**
   * Creates a new role.
   *
   * Corresponds to the Galaxy Api/path:
   *   POST /api/roles
   *
   * NOTE: only type admin can be applied for new roles
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - name: The name of the new role.
   *   - description: The description of the new role.
   *   - user_ids: An array of user ids to associate the new role with.
   *       To obtain a user id, please use the index() function of
   *       the users class.
   *   - group_ids: An array of group id's to associate the new role with.
   *       To obtain a group id, please use the index() function of the
   *       groups class.
   *
   * @return
   *   An array containing informaiton about the new role.
   *
   *
   */
  public function create($params) {

    if(!array_key_exists('name', $params)){
      $this->galaxy->setError('API', "Please provide a 'name'  as an input to this function.");
      return FALSE;
    }
    if(!array_key_exists('description', $params)){
      $this->galaxy->setError('API', "Please provide a 'description' as an input to this function.");
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
