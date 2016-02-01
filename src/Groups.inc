<?php 
include_once "GalaxyRequest.inc";


class Groups extends GalaxyRequest{

	
/**
 * Default constructor
 * @param GalaxyInstance $galaxy
*/ 
 public function __construct($galaxy) {
	parent ::__construct($galaxy);
 }

 
 /**
  * GET /api/groups
  * 
    Displays a collection (list) of groups.
  */
 public function index(){
 	
 }
 
 /**
    POST /api/groups
    
    Creates a new group.
    
  * @param string $name name of the group
  * @param string array $user_ids array of user id's to associate group with
  * @param string array $role_ids array of role ids to associate group with
  */
 public function create($name, $user_ids=array(), $role_ids=array()){
 	$URL = $this->galaxy->getURL() . '/api/groups/?key=' . $this->galaxy->getAPIKey();
 	$elements = array(
 		'name'=> $name,
 		'user_ids'=>$user_ids,
 		'role_ids'=>$role_ids,	
 	);
 	return $this->rest->POST($URL,$elements);
 }
 
 /**
  *  GET /api/groups/{encoded_group_id}   
     
     Displays information about a group.
  *  
  *  @param string $group_id
  */
 public function show($group_id){
 	$URL = $this->galaxy->getURL() . '/api/groups/' . $group_id . 
 	'/?key='. $this->galaxy->getAPIKey();
 	return $this->rest->GET($URL);
 	
 }
 
 
 /**
  * PUT /api/groups/{encoded_group_id}
    
    Modifies a group.
  * 
  * @param string $group_id, the id of the group to modify
  * @param string $name, a new name, if any, to call the group
  * @param string array $user_ids an array of user_ids, if any, to associate user id's to the group
  * @param string array $role_ids an array of role_ids to associate any new roles to the group
  */
 public function update($group_id,$name = NULL, $user_ids = array(), $role_ids = array()){
 	$URL = $this->galaxy->getURL() . '/api/groups/' . $group_id .
 	'/?key='. $this->galaxy->getAPIKey(); 	
 
 	$elements = array(
 		'user_ids'=>$user_ids,
 		'role_ids'=>$role_ids,
 	);
 	
 	if($name!=null){$elements['name'] = $name;}
 	return $this->rest->PUT($URL,$elements);
 }
 
}