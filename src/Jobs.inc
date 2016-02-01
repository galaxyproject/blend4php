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
 * 
 * NOTE: Creating/submitting a job is actually run under tools.py in the
 * Galaxy api

 */
public function create(){
	return null;
}


/**
 * POST /api/jobs/search
 * 
   This method is designed to scan the list of previously run jobs and find 
   records of jobs that had
   the exact some input parameters and datasets. This can be used to minimize 
   the amount of repeated work, and simplyrecycle the old results.
   
  * @param action - string optional 'rerun' to rerun the tool and not execute
  * @param tool_id - string  (tool_id to execute)
  * @param tool_version - string  OPTIONAL, specify specific tool version
  * @param history_id - string history_id where tool is located
  * @param region - string optional (information on the region of the genome being rerun)
  * @param input_dataset_ds - array of dataset id's where the tool should grab the inputs from
  * similar to workflow_invoke  
 
 */
public function search($tool_id=NULL,  $input_dataset_ids=array(), $history_id = NULL,$tool_version=NULL,
 		$region = NULL,  $action = NULL){
 	$URL = $this->galaxy->getURL() . '/api/jobs/search/?key=' . $this->galaxy->getAPIKey();
 			
 	$input_ids = array();
 	$i =0;
 	
 	foreach($input_dataset_ids as &$input_dataset_id){
 		$input_ids[$i] = array('id'=> $input_dataset_id, 'src'=>'hda');
 		$i++;
 	}
 			
 	$elements = array(
		'tool_id' => $tool_id,
		'tool_version' => $tool_version,
 		'inputs' => json_encode($input_ids,JSON_FORCE_OBJECT),
 		'history_id'=>$history_id,
 		'region' => $region,
 		'action' => $action,
	);
 	//create a list of input items that is not null
 	$notNullInputs = array();
 	foreach($elements as $element=>$value) {
 		if($value != NULL) {
 			$notNullInputs[$element] = $value;
 		}
 	}
 			
 	return $this->rest->POST($URL, $notNullInputs);
 			
}

}


?>
