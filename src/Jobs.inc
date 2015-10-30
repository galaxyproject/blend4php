<?php 
require_once 'GalaxyRequest.inc';


class Jobs extends GalaxyRequest{


/**
 * public constructor 
 * @param GalaxyInstance $galaxy
 */
public function __construct($galaxy){
	parent::__construct($galaxy);
}


/**
 * Calls upon GET/api/jobs/id/build_for_rerun
 * @param string/int $job_id 
 **/
public function build($job_id){
	$URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/?key=' . $this->galaxy->getAPIKey();
	return $this->REST->GET($URL);
}


public function create(){

	
}


public function inputs(){
	
}


}


?>
