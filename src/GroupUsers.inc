<?php

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

/**
 * @defgroup group_users_class GroupUsers Class
 * @{
 *   The GroupUsers Class interacts with Galaxy to manage users of groups.
 *   The functions in this class correspond to the Galaxy API functions and
 *   are named similarly to their Python counterpart.
 * @}
 */
include_once "GalaxyRequest.inc";

class GroupUsers extends GalaxyRequest {

	/**
	 * The GroupUsers constructor.
	 *
	 * @param GalaxyInstance $galaxy
	 *   A GalaxyInstance object.
	 *
	 * @return
	 *   An instance of a Groups Users object.
	 *
	 * @ingroup group_users_class
	 */
   public function __construct($galaxy) {
     parent::__construct($galaxy);
   }

   /**
    * Displays a collection (list) of users corresponding to a group..
    *
    * Corresponds to the Galaxy API method and path: GET /api/groups/
    * {encoded_group_id}/users.
    *
    * @param $group_id
    *   The id of the group whose users to list.  Group IDs can be found using the
    *   index() function of the Groups class.
    * @return
    *   A JSON array of all users of a given group.
    *
    * @ingroup group_users_class
    */
  public function index($group_id) {
    $URL = $this->galaxy->getURL() .'/api/groups/' .$group_id .'/users/?key=' .$this->galaxy->getAPIKey();
    return $this->rest->GET($URL);
  }

  /**
   * Retreive information about a specific group user.
   *
   * Corresponds to the Galaxy API method and path:
   * GET /api/groups/{encoded_group_id}/users/{encoded_user_id}
   *
   * @param $group_id
   *   The id of the group whose users to list.  Group IDs can be found using the
   *   index() function of the Groups class.
   * @param $user_id
   *   The id of the specific user to show. User IDS can be found using the index()
   *   function of the Users class
   * @return
   *   A JSON array containing details about the user of a given group.
   *
   * @ingroup group_users_class
   */
  public function show($group_id, $user_id) {
    $URL = $this->galaxy->getURL() .'/api/groups/' .$group_id .'/users/' .$user_id .'/?key=' .$this->galaxy->getAPIKey();
    return $this->rest->GET($URL);
  }

  /**
   * Supports adding a user to a given group.
   *
   * Corresponds to the Galaxy API method and path:
   * PUT /api/groups/{encoded_group_id}/users/{encoded_user_id}.
   *
   * @param $group_id,
   *   The id of the group to modify.  Group IDs can be found using the
   *   index() function of this class.
   * @param $user_id
   *   A user id to associate any new users to the group. Use the
   *   Users class to retreive a list of existing user IDs.
   * @return
   *   A JSON array of the group that has been modified
   *
   * @ingroup group_users_class
   */
  public function update($group_id, $user_id) {
    $URL = $this->galaxy->getURL() .'/api/groups/' .$group_id .'/users/' .$user_id .'/?key=' .$this->galaxy->getAPIKey();
    return $this->PUT($URL);
  }

  /**
   * Supports deleting a user from a given group.
   *
   * Corresponds to the Galaxy API method and path:
   * DELETE /api/groups/{encoded_group_id}/users/{encoded_user_id}.
   *
   * @param $group_id,
   *   The id of the group to modify.  Group IDs can be found using the
   *   index() function of this class.
   * @param $user_id
   *   A user id to deassociate any users from the group. Use the
   *   Users class to retreive a list of user IDs.
   * @return
   *   A JSON array of the group that has been modified
   *
   * @ingroup group_users_class
   */
  public function delete($group_id, $user_id) {
    $URL = $this->galaxy->getURL() .'/api/groups/' .$group_id .'/users/' .$user_id .'/?key=' .$this->galaxy->getAPIKey();
    return $this->delete($URL);
  }
}
