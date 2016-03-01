<?php 
/**
 * @file
 *
 * Implements the Jobs class.
 *
 * The Jobs Class interacts with Galaxy to manage contents of a Galaxy Job.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

/**
 * @defgroup jobs_class
 * @{
 *   The Jobs Class interacts with Galaxy to manage
 *   its folders. The functions in this class correspond to the Galaxy
 *   API functions and are named similarly to their Python counterpart.
 * @}
 */

require_once 'GalaxyRequest.inc';

class Jobs extends GalaxyRequest{

  /**
	* The Jobs constructor.
	*
	* @param GalaxyInstance $galaxy
	*   A GalaxyInstance object.
	*
	* @return
	*   An instance of a Jobs object.
	*
	* @ingroup jobs_class
	*/
   public function __construct($galaxy){
	 parent::__construct($galaxy);
    }

  /**
    * Retreive a tool input template populated with this job's information.
    * 
    * Corresponds to the Galaxy Api/path at:
    *   GET /api/jobs/{encoded_job_id}/build_for_rerun 
    *   This function is suitable for rerunning or rendering parameters of 
    *   the job.
    *
    * @param job id
    *   The job id of the job whose information to retreive.
    *   The job id can be ontained from this class's index() function.
    * 
    * @return 
    *   JSON object containing ouput informaiton of the tool that has been 
    *   built.
    *   
    * @ingroup jobs_class   
    */
   public function buildForRerun($job_id){
	 $URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/build_for_rerun/?key=' . $this->galaxy->getAPIKey();
	 return $this->rest->GET($URL);
   }

   /**
    * Retreive the input datasets created from the specified job.
    * 
    * Corresponds to the Galaxy Api/path at: 
    *   GET/api/jobs/{encoded_job_id}/inputs
    * 
    * @param job_id
    *   The job id of the job whose information to retreive.
    *   The job id can be ontained from this class's index() function.
    *   
    * @return 
    *   JSON object containing ouput informaiton of the job input.
    *   
    * @ingroup jobs_class 
    */
   public function inputs($job_id){
	 $URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/inputs/?key=' . $this->galaxy->getAPIKey();
	 return $this->rest->GET($URL);
   }

   /**
    * Retreive the output datasets created from the specified job.
    *
    * Corresponds to the Galaxy Api/path at:
    *   GET/api/jobs/{encoded_job_id}/inputs.
    *
    * @param job_id
    *   The job id of the job whose information to retreive.
    *   The job id can be ontained from this class's index() function.
    *
    * @return 
    *   JSON object containing ouput informaiton of the job outputs.
    *
    * @ingroup jobs_class
    */
   public function outputs($job_id){
	 $URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/outputs/?key=' . $this->galaxy->getAPIKey();
	 return $this->rest->GET($URL);	
   }

   /**
    * Retreive information about a specific job
    *
    * Corresponds to the Galaxy API function/path:
    *   GET /api/jobs/{folder_id}
    *
    * @param $folder_id
    *   The folder that you would like to see. Please see the index()
    *   function in this class to obtain folder ids.
    *
    * @return
    *   JSON array containing information about the specified job.
    *
    * @ingroup jobs_class
    */
   public function show($job_id){
	 $URL = $this->galaxy->getURL() . '/api/jobs/' . $job_id . '/?key=' . $this->galaxy->getAPIKey();	
   }

  /**
    * Retreive a list of jobs for current user.
    * 
    * Corresponds to the Galaxy Api method/path: 
    *   GET /api/jobs 
    * 
    * @param state: 
    *   filter job search by any one of these conditions:
    *   'new', 'upload', 'waiting', 'quued', 'running', 'ok', 'error', 
    *   'paused', 'deleted', 'deleted_now'
    * @param tool_ids. 
    *   A list of tool ids that limit  the  search to include only those with 
    *   given tool_ids. To find tool id's, please refer to this class's index()
    *   function.
    * @param date_range_min 
    *   Bool, Limit the search of jobs updated after this date.
    * @param date_range_max
    *   Bool, Limit the search of jobs updated before this date.
    * @param history_id 
    *   Limit listing of jobs to those that match history_id. 
    *   To find the history id, please refer to the history class.
    * 
    * @return 
    *   JSON array ocntaining a list of all the jobs that matched 
    *   the given parameters.
    *   
    * @ingroup jobs_class
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
    * This function is not implemented by its python counterpart
    * 
    * NOTE: Creating/submitting a job is actually run under tools.py in the
    * Galaxy api
    * 
    * @return 
    *   FALSE
    * 
    * @ingroup jobs_class
    */
   public function create(){
	 return null;
   }


  /**
    * Search for previously created jobs.
    * 
    * Corresponds to the Galaxy Api/path at:   
    *   POST /api/jobs/search
    * 
    * This method is designed to scan the list of previously run jobs and find 
    *   records of jobs that had the exact some input parameters and datasets. 
    *   This can be used to minimize, the amount of repeated work, 
    *   and simplyrecycle the old results.
    *
    * @param action 
    *   optional, 'rerun' to rerun the tool and not execute.
    * @param tool_id 
    *   The tool id to execute. To find the tool id, use the index function of
    *   this class.
    * @param tool_version 
    *   Optional, specify specific tool version to search for.
    * @param history_id 
    *   The history_id where tool is located. 
    * @param region 
    *   Optional information on the region of the genome being rerun.
    * @param input_dataset_ds
    *   Array of dataset id's where the tool should grab the inputs from,
    *   similar to workflow_invoke.  
    * 
    * @ingroup jobs_class 
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
