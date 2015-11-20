<?php 
include_once "GalaxyRequest.inc";


class Libraries extends GalaxyRequest{

	
/**
 * public constructor
 * @param GalaxyInstance $galaxy
 */
 public function __construct($galaxy) {
	parent ::__construct($galaxy);
 }
 
 
 /**
 	 POST /api/libraries:
     Creates a new library. Only ``name`` parameter is required.
     @param string 'name':         the new library's name (required)
     @param 'description':  the new library's description (optional)
     @param 'synopsis':     the new library's synopsis (optional)
  *
  */
 public function create($name, $description=NULL, $synopsis=NULL) {
 	$URL = '/api/libraries/?key ='. $this->galaxy->getAPIKey();
 	$inputs = array(
 			'name' => $name,
 			'description'=> $description,
 			'synopsis' => $synopsis,
 	);
 	return $this->rest->POST($URL, $inputs);
 }
 
 
 public function get_permissions() {
 	
 }
 
 public function set_permissions(){
 	
 }
 
 
}// end libraries class