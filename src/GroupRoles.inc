<?php

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
class GalaxyGroupRoles {
  private $galaxy;


  /**
   * The Group Roles constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Group Roles object.
   *
   *
   */
    public function __construct(GalaxyInstance $galaxy) {
      $this->galaxy = $galaxy;
    }

   /**
    * Displays a collection (list) of roles corresponding to a group..
    *
    * Corresponds to the Galaxy API method and path: GET /api/groups/
    * {encoded_group_id}/roles.
    *
    * @param $params
    *   A key value (associative array) where the keys can be the following:
    *
    *   - group_id: The id of the group whose roles to list. Group IDs can be
    *       found using the index() function of the Groups class.
    *
    * @return
    *   An array of all group roles for a given group.
    *
    *
    */
   public function index($params) {
     if(!array_key_exists('group_id', $params)){
       $this->galaxy->setError("API", "A 'group_id' is required in order to invoke this call");
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/roles/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

   /**
    * Retreive information about a specific group role.
    *
    * Corresponds to the Galaxy API method and path:
    * GET /api/groups/{encoded_group_id}/roles/{encoded_role_id}
    *
    * @param $params
    *   A key value (associative array) where the keys can be the following:
    *
    *   - group_id: The id of the group whose roles to list. Group IDs can be
    *       found using the index() function of the Groups class.
    *   - role_id: The id of the specific role to show. Role IDS can be found
    *       using the index() function of the Roles class
    *
    * @return
    *   An array containing details about the role of a given gorup.
    *
    *
    */
   public function show($params) {
     if(!array_key_exists('group_id', $params)){
       $this->galaxy->setError("API", "A 'group_id' is required in order to invoke this call");
       return FALSE;
     }
     if(!array_key_exists('role_id', $params)){
       $this->galaxy->setError("API", "A 'role_id' is required in order to invoke this call");
       return FALSE;
     }
     $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/roles/' . $params['role_id']. '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

   /**
    * Supports adding a role to a given group.
    *
    * Corresponds to the Galaxy API method and path:
    * PUT /api/groups/{encoded_group_id}/roles/{encoded_role_id}.
    *
    * @param $params
    *   A key value (associative array) where the keys can be the following:
    *
    *   - group_id: The id of the group whose roles to list. Group IDs can be
    *       found using the index() function of the Groups class.
    *   - role_id: The id of the specific role to show. Role IDS can be found
    *       using the index() function of the Roles class.
    *
    * @return
    *   An array of the role that was added to the group
    *
    *
    */
   public function update($params) {
     if(!array_key_exists('group_id', $params)){
       $this->galaxy->setError("API", "A 'group_id' is required in order to invoke this call");
       return FALSE;
     }
     if(!array_key_exists('role_id', $params)){
       $this->galaxy->setError("API", "A 'role_id' is required in order to invoke this call");
       return FALSE;
     }
     $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/roles/' . $params['role_id'] . '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpPUT($URL);
     return $this->galaxy->expectArray($response);
   }

   /**
    * Supports deleting a role from a given group.
    *
    * Corresponds to the Galaxy API method and path:
    * DELETE /api/groups/{encoded_group_id}/roles/{encoded_role_id}.
    *
    * @param $params
    *   A key value (associative array) where the keys can be the following:
    *
    *   - group_id: The id of the group whose roles to list. Group IDs can be
    *       found using the index() function of the Groups class.
    *   - role_id: The id of the specific role to show. Role IDS can be found
    *       using the index() function of the Roles class.
    *
    * @return
    *   An array of the role that was removed from the group.
    *
    *
    */
   public function delete($params) {
     if(!array_key_exists('group_id', $params)){
       $this->galaxy->setError("API", "A 'group_id' is required in order to invoke this call");
       return FALSE;
     }
     if(!array_key_exists('role_id', $params)){
       $this->galaxy->setError("API", "A 'role_id' is required in order to invoke this call");
       return FALSE;
     }
     $URL = $this->galaxy->getURL() . '/api/groups/' . $params['group_id'] . '/roles/' . $params['role_id'] . '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpDELETE($URL);
     return $this->galaxy->expectArray($response);
   }
}
