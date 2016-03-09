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

/**
 * @defgroup group_roles_class GroupsRoles Class
 * @{
 *   The GroupRoles Class interacts with Galaxy to manage user groups and roles.
 *   The functions in this class correspond to the Galaxy API functions and
 *   are named similarly to their Python counterpart.
 * @}
 */

include_once "HTTPRequest.inc";

class GroupRoles extends HTTPRequest {
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
   * @ingroup group_roles_class
   */
    public function __construct($galaxy) {
      $this->galaxy = $galaxy;
      parent ::__construct();
    }

   /**
    * Displays a collection (list) of roles corresponding to a group..
    *
    * Corresponds to the Galaxy API method and path: GET /api/groups/
    * {encoded_group_id}/roles.
    *
    * @param $group_id
    *   The id of the group whose roles to list.  Group IDs can be found using the
    *   index() function of the Groups class.
    * @return
    *   An array of all group roles for a given group.
    *
    * @ingroup group_roles_class
    */
   public function index($group_id) {
     $URL = $this->galaxy->getURL() . '/api/groups/' . $group_id. '/roles/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Retreive information about a specific group role.
    *
    * Corresponds to the Galaxy API method and path:
    * GET /api/groups/{encoded_group_id}/roles/{encoded_role_id}
    *
    * @param $group_id
    *   The id of the group whose roles to list.  Group IDs can be found using the
    *   index() function of the Groups class.
    * @param $role_id
    *   The id of the specific role to show. Role IDS can be found using the index()
    *   function of the Roles class
    * @return
    *   An array containing details about the role of a given gorup.
    *
    * @ingroup group_roles_class
    */
   public function show($group_id, $role_id) {
     $URL = $this->galaxy->getURL() . '/api/groups/' . $group_id. '/roles/' . $role_id. '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Supports adding a role to a given group.
    *
    * Corresponds to the Galaxy API method and path:
    * PUT /api/groups/{encoded_group_id}/roles/{encoded_role_id}.
    *
    * @param $group_id,
    *   The id of the group to modify.  Group IDs can be found using the
    *   index() function of this class.
    * @param $role_id
    *   A role id to associate any new roles to the group. Use the
    *   Roles class to retreive a list of existing role IDs.
    * @return
    *   An array of the role that was added to the group
    *
    * @ingroup group_roles_class
    */
   public function update($group_id, $role_id) {
     $URL = $this->galaxy->getURL() . '/api/groups/' . $group_id . '/roles/' . $role_id. '/?key=' . $this->galaxy->getAPIKey();

     $response = $this->httpPUT($URL);
     return $this->expectArray($response);
   }

   /**
    * Supports deleting a role from a given group.
    *
    * Corresponds to the Galaxy API method and path:
    * DELETE /api/groups/{encoded_group_id}/roles/{encoded_role_id}.
    *
    * @param $group_id,
    *   The id of the group to modify.  Group IDs can be found using the
    *   index() function of this class.
    * @param $role_id
    *   A role id to deassociate any roles from the group. Use the
    *   Roles class to retreive a list of role IDs.
    * @return
    *   An array of the role that was removed from the group.
    *
    * @ingroup group_roles_class
    */
   public function delete($group_id,$role_id) {
     $URL = $this->galaxy->getURL() . '/api/groups/' . $group_id . '/roles/' . $role_id . '/?key=' . $this->galaxy->getAPIKey();

     $response = $this->httpDELETE($URL);
     return $this->expectArray($response);
   }

}
