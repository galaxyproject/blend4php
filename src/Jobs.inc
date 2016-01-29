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
 * GET /api/jobs/{id}/build_for_rerun
 *
 * returns a tool input template populated with this job's
 * information, suitable for rerunning or rendering parameters of the job
 *
 * @param str job id
 * @return dictionary containing ouput dataset association
 */
public function build_for_rerun($job_id){
	$URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/build_for_rerun/?key=' . $this->galaxy->getAPIKey();
	return $this->rest->GET($URL);
}


/**
 * GET/api/jobs/{id}/inputs
 * returns input datasets created by job
 * 
 * @param string job_id
 */
public function inputs($job_id){
	$URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/inputs/?key=' . $this->galaxy->getAPIKey();
	return $this->rest->GET($URL);
}

/**
 * GET/api/jobs/{id}/outputs
 * returns output datasets created by job 
 * 
 * @param string $job_id
 */
public function outputs($job_id){
	$URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/outputs/?key=' . $this->galaxy->getAPIKey();
	return $this->rest->GET($URL);	
}

/**
 *  GET /api/jobs/{id}
 */
public function show($job_id){
	$URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/?key=' . $this->galaxy->getAPIKey();	
}

/**
 * GET /api/jobs 
 * 
 * returns jobs for current user
 * 
 * @param string state, look for jobs with given state, 
 * 'new' 'upload' 'waiting' 'quued', 'running', 'ok', 'error', 'paused', 'deleted', 'deleted_now'
   @param array tool_ids. Limit search to include only those with given tool_id
   @param string date_range_min limit search of jobs updated after this date
   @param string date_range_max limit search of jobs updated before this date
   @param string history_id  limit listing of jobs to those that match history_id
   
   @return json array of matched jobs 
 */
public function index($state, $tool_ids = null, $date_range_min = null, $date_range_max=null,
		$history_id = null){
	$URL = $this->galaxy->getURL() . '/api/jobs/?';
	if($tool_ids !== null){
		if(!is_array($tool_id)) 
		{ return "tool_id must be an array of tool_id's, or null"; }
		
	   foreach($tool_ids as &$tool_id) {
	   	$URL .= 'tool_id=' . $tool_id . '&';
	   }
	}
	
	if($date_range_min !==null) {
		$URL .= 'date_range_min='. $date_range_min . '&'; 
	}
	if($date_range_max !== null) {
		$URL .='date_range_max='.$date_range_max . '&';
	}
	if($history_id !== null ){
		$URL .='history_id=' . $history_id . '&';
	}
	
	$URL .= 'key=' . $this->galaxy->getAPIKey();
	
	return $this->rest->GET($URL);
}





/**
 * POST /api/tools
 */
public function create(){
	
}


/**
 * POST /api/jobs/search
 *
 * @param request info
 */
public function search(){
	$elements = array(
			'inputs' => null,
			'tool_id'=> null,
				
	);
}

}


?>
