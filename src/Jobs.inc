<?php 
require_once "GalaxyInstance.inc";
require_once "RESTManager.php";


class Jobs{
private $galaxy = NULL; 
private $debug = True;
private $REST;


public function __construct($galaxy){
	$this-> galaxy = $galaxy; 
	$this-> REST = new RESTManager();
}


/**
 * Calls upon GET/api/jobs/id/build_for_rerun
 *
 **/
public function build($job_id){
	$URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/?key=' . $this->galaxy->getAPIKey();
	return $this->REST->GET($URL);
}


public function create(){



	
}


?>
