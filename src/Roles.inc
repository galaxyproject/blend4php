<?php  
include_once "GalaxyRequest.inc";


class Roles extends GalaxyRequest{


	/**
	 * Default constructor
	 * @param GalaxyInstance $galaxy
	 */
	public function __construct($galaxy) {
		parent ::__construct($galaxy);
	}
	
	/**
	 * GET /api/roles
	 * Display a collection (list of roles)
	 */
	public function index(){
		$URL = $this->galaxy->getURL() . '/api/roles/?key=' . $this->galaxy->getAPIKey();
		return $this->rest->GET($URL);
	}
	
	/**
	 * 
	 *  GET /api/roles/{encoded_id}
	 *  Displays informatin about a role 
	 *  
	 * @param string $role_id
	 */
	public function show($role_id){
		$URL = $this->galaxy->getURL() . '/api/roles/'. $role_id.'/?key=' . $this->galaxy->getAPIKey();
		return $this->rest->GET($URL);
	}
	
	
	/**
	 * POST /api/roles
	 * Create a new role
	 * NOTE: only type admin can be applied for new roles
	 * 
	 * 
	 * @param string $name
	 * @param string $description
	 * @param string array $user_ids (array of user id's)
	 * @param string array $group_ids (array of group_id's)
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
			if($input != NULL) {
				$notNullInputs[$input] = $value;
			}
		}
		
		return $this->rest->POST($URL, $notNullInputs);
	}




}

?>