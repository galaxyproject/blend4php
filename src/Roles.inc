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

/**
 * @defgroup roles_class roels Class
 * @{
 *   The Roles class interacts with Galaxy to manage contents of a Galaxy
 *   role. The functions in this class correspond to the Galaxy API
 *   functions and are named similarly to their Python counterparts.
 * @}
 */

include_once "GalaxyRequest.inc";


class Roles extends GalaxyRequest{


	/**
	 * The Roles constructor.
	 *
	 * @param GalaxyInstance $galaxy
	 *   A GalaxyInstance object.
	 *
	 * @return
	 *   An instance of a roles object.
	 *
	 * @ingroup roles_class
	 */
	public function __construct($galaxy) {
		parent ::__construct($galaxy);
	}
	
	/**
	 * Retreive a list of all of Galaxy's roles.
	 * 
	 * Corresponds to the Galaxy API/path:
	 *   GET /api/roles
	 *
	 * @return
	 *   JSON array containing details of all the roles in Galaxy. 
	 *
	 * @ingroup roles_class
	 */
	public function index(){
		$URL = $this->galaxy->getURL() . '/api/roles/?key=' . $this->galaxy->getAPIKey();
		return $this->rest->GET($URL);
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
	 *   JSON object containing details about the specified role.
	 *   
	 * @ingroup roles_class
	 */
	public function show($role_id){
		$URL = $this->galaxy->getURL() . '/api/roles/'. $role_id.'/?key=' . $this->galaxy->getAPIKey();
		return $this->rest->GET($URL);
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
	 *   A JSON object containing informaiton about the new role.
	 *   
	 * @ingroup roles_class
	 */
	public function create($name, $description, $user_ids, $group_ids=NULL) {
		$URL = $this->galaxy->getURL() . '/api/roles/?key=' . $this->galaxy->getAPIKey();
		$inputs = array(
				'name' => $name,
				'description' => $description,
				'user_ids' => json_encode($user_ids),
				'group_ids' => json_encode($group_ids),
		);
		//create a list of input items that is not null
		$notNullInputs = array();
		foreach($inputs as $input=>$value) {
			if($value != NULL && $value != "null") {
				$notNullInputs[$input] = $value;
			}
		}
		
		return $this->rest->POST($URL, $notNullInputs);
	}


}

?>