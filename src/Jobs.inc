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
 * 
 * @param string/int $job_id 
 **/
public function build($job_id){
	$URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/?key=' . $this->galaxy->getAPIKey();
	return $this->rest->GET($URL);
}



/**
 * GET/api/jobs/{id}/inputs
 * returns input datasets created by job
 * 
 * @param string job_id
 */
public function inputs($job_id){
	$URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . 'inputs/?key=' . $this->galaxy->getAPIKey();
	return $this->rest->GET($URL);
}

/**
 * GET/api/jobs/{id}/outputs
 * returns output datasets created by job 
 * 
 * @param string $job_id
 */
public function outputs($job_id){
	$URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . 'outputs/?key=' . $this->galaxy->getAPIKey();
	return $this->rest->GET($URL);	
}

public function search(){
	
}


}


?>
