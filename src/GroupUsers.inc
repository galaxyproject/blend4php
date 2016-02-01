<?php 
include_once "GalaxyRequest.inc";


class GroupRoles extends GalaxyRequest{

	
/**
 * Default constructor
 * @param GalaxyInstance $galaxy
*/ 
 public function __construct($galaxy) {
	parent ::__construct($galaxy);
 }
 
 
 /**
  *GET /api/groups/{encoded_group_id}/users
   
   Displays a collection (list) of groups.
  * 
  * @param string $group_id
  */
 public function index($group_id){
 	$URL = $this->galaxy->getURL() . '/api/groups/'
 			.$group_id. '/users/?key=' . $this->galaxy->getAPIKey(); 
 	return $this->rest->GET($URL);
 }
 
 /**
    GET /api/groups/{encoded_group_id}/users/{encoded_user_id}
    
    Displays information about a group user.

  * @param string $group_id
  * @param string $user_id
  */
 public function show($group_id, $user_id){
 	$URL = $this->galaxy->getURL() . '/api/groups/'
 			.$group_id. '/users/'. $user_id .'/?key=' . $this->galaxy->getAPIKey();
 	return $this->rest->GET($URL);
 	
 }
 
 /**
   PUT /api/groups/{encoded_group_id}/users/{encoded_user_id}
   Adds a user to a group  
  * 
  * @param string $group_id
  * @param string $user_id
  */
 public function update($group_id, $user_id){
 	$URL = $this->galaxy->getURL() . '/api/groups/'
 			.$group_id. '/users/'. $user_id .'/?key=' . $this->galaxy->getAPIKey(); 
 	return $this->PUT($URL);
 }
 
 /**
    DELETE /api/groups/{encoded_group_id}/users/{encoded_user_id}
    Removes a user from a group   
  * @param string $group_id
  * @param string $user_id
  */
 public function delete($group_id,$user_id){
 	$URL = $this->galaxy->getURL() . '/api/groups/'
 			.$group_id. '/users/'. $user_id .'/?key=' . $this->galaxy->getAPIKey(); 	
 	return $this->delete($URL);
 }
 
 
}





 ?>
