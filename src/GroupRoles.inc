<?php
include_once "GalaxyRequest.inc";

class GroupRoles extends GalaxyRequest {


  /**
   * Default constructor
   * @param GalaxyInstance $galaxy
   */
   public function __construct($galaxy) {
     parent ::__construct($galaxy);
   }

  /**
   * GET /api/groups/{encoded_group_id}/roles
   *
   * Displays a collection (list) of groups.
   *
   * @param string $group_id
   */
  public function index($group_id) {
    $URL = $this->galaxy->getURL() . '/api/groups/'
        . $group_id. '/roles/?key=' . $this->galaxy->getAPIKey();
    return $this->rest->GET($URL);
  }

  /**
   *GET /api/groups/{encoded_group_id}/roles/{encoded_role_id}

    Displays information about a group role.

     @param group_id str group id
     @param role_id str role id
   */
  public function show($group_id, $role_id) {
    $URL = $this->galaxy->getURL() . '/api/groups/'
        . $group_id. '/roles/' . $role_id. '/?key=' . $this->galaxy->getAPIKey();
    return $this->rest->GET($URL);
  }


  /**
   * PUT /api/groups/{encoded_group_id}/roles/{encoded_role_id}
   *
   *  Adds a role to a group
   *
   * @param string $group_id
   * @param string $role_id
   */
  public function update($group_id,$role_id) {
    $URL = $this->galaxy->getURL() . '/api/groups/'
        . $group_id . '/roles/' . $role_id. '/?key=' . $this->galaxy->getAPIKey();
    return $this->PUT($URL);
  }

  /**
   * DELETE /api/groups/{encoded_group_id}/roles/{encoded_role_id}
   *
   * Removes a role from a group
   *
   * @param string $group_id
   * @param string $role_id
   */
  public function delete($group_id,$role_id) {
    $URL = $this->galaxy->getURL() . '/api/groups/'
        . $group_id . '/roles/' . $role_id . '/?key=' . $this->galaxy->getAPIKey();
    return $this->rest->delete($URL);
  }

}
