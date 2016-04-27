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

require_once 'HTTPRequest.inc';

class Jobs extends HTTPRequest{
  private $galaxy;
 /**
  * The Jobs constructor.
  *
  * @param GalaxyInstance $galaxy
  *   A GalaxyInstance object.
  *
  * @return
  *   An instance of a Jobs object.
  *
  * 
  */
  public function __construct($galaxy){
    $this->galaxy = $galaxy;
    parent::__construct();
  }

  /**
   * Retreive a tool input template populated with this job's information.
   *
   * Corresponds to the Galaxy Api/path at:
   *   GET /api/jobs/{encoded_job_id}/build_for_rerun
   *   This function is suitable for rerunning or rendering parameters of
   *   the job.
   *   
   * @param $params
   *    A key value (associative array) where the keys can be the following:
   *
   *    - job_id: The job id of the job whose information to retreive.
   *        The job id can be ontained from this class's index() function.
   *
   * @return
   *   An array containing ouput informaiton of the tool that has been
   *   built.
   *
   * 
   */
  public function buildForRerun($params){
    if(array_key_exists('job_id', $params)){
      $URL = $this->galaxy->getURL() . '/api/jobs/' . $params['job_id'] . '/build_for_rerun/?key=' . $this->galaxy->getAPIKey();
      $response = $this->httpGET($URL);
      $this->setError("API", "This function is not complete, the corresponding Galaxy API
        function wants a history_id, why or how is still uknown. Please see our issues page on Github for more information");
      return FALSE;
    }
    $this->setError("API", "This function expects at least the associative parameter 'job_id' in order to run");
    return FALSE;
   
  }

 /**
  * Retreive the input datasets created from the specified job.
  *
  * Corresponds to the Galaxy Api/path at:
  *   GET/api/jobs/{encoded_job_id}/inputs
  *
  * @param $params
  *    A key value (associative array) where the keys can be the following:
  *
  *    - job_id: The job id of the job whose information to retreive.
  *        The job id can be ontained from this class's index() function.
  *        
  * @return
  *   An array containing ouput informaiton of the job input.
  *
  * 
  */
  public function inputs($params){
    if(array_key_exists('job_id', $params)){
      $URL = $this->galaxy->getURL() . '/api/jobs/' . $params['job_id'] . '/inputs/?key=' . $this->galaxy->getAPIKey();
      $response = $this->httpGET($URL);
      return $this->expectArray($response);
    }
    
    $this->setError("API", "This function expects the associative parameter 'job_id' in order to run");
    return FALSE;

  }

 /**
  * Retreive the output datasets created from the specified job.
  *
  * Corresponds to the Galaxy Api/path at:
  *   GET/api/jobs/{encoded_job_id}/inputs.
  *   
  *   
  * @param $params
  *    A key value (associative array) where the keys can be the following:
  *
  *    - job_id: The job id of the job whose information to retreive.
  *        The job id can be ontained from this class's index() function.
  *
  * @return
  *   An array containing ouput informaiton of the job outputs.
  *
  * 
  */
  public function outputs($params){
    if(array_key_exists('job_id', $params)){
      $URL = $this->galaxy->getURL() . '/api/jobs/' . $params['job_id'] . '/outputs/?key=' . $this->galaxy->getAPIKey();
      $response = $this->httpGET($URL);
      return $this->expectArray($response);
    }
    $this->setError("API", "This function expects the associative parameter 'job_id' in order to run");
    return FALSE;
  }

 /**
  * Retreive information about a specific job
  *
  * Corresponds to the Galaxy API function/path:
  *   GET /api/jobs/{job_id}
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *
  *   - job_id: The job that you would like to see. Please see the 
  *       index() function in this class to obtain job ids.
  *
  * @return
  *   JSON array containing information about the specified job.
  *
  * 
  */
  public function show($params){
    if(array_key_exists('job_id', $params)){
      $URL = $this->galaxy->getURL() . '/api/jobs/' . $params['job_id'] . '/?key=' . $this->galaxy->getAPIKey();
      $response = $this->httpGET($URL);
      return $this->expectArray($response);
    }
    $this->setError("API", "This function expects the associative parameter 'folder_id' in order to run");
    return FALSE;
  }

 /**
  * Retreive a list of jobs for current user.
  *
  * Corresponds to the Galaxy Api method/path:
  *   GET /api/jobs
  *
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *   
  *   - state: filter job search by any one of these conditions:
  *     (i)    'new'
  *     (ii)   'upload'
  *     (iii)  'waiting'
  *     (iv)   'queued'
  *     (v)    'running'
  *     (vi)   'ok'
  *     (vii)  'error'
  *     (viii) 'paused'
  *     (ix)   'deleted'
  *     (x)    'deleted_now'
  *   - tool_ids: A list of tool ids that limit  the  search to include only
  *       those with given tool_ids. To find tool id's, please refer to this 
  *       class's index() function.
  *   - date_range_min: Limit the search of jobs updated after this date.
  *   - date_range_max: Limit the search of jobs updated before this date.
  *   - history_id: Limit listing of jobs to those that match history_id.
  *       To find the history id, please refer to the history class.
  *
  * @return
  *   An array containing a list of all the jobs that matched
  *   the given parameters.
  *
  * 
  */
  public function index($params){
    $URL = $this->galaxy->getURL() . '/api/jobs/?';

    if(array_key_exists('state', $params)){
      if(!is_array($params['state'])){
        if (!is_string($params['state'])){
          return $this->setError('User', 'Invalid state input scheme (string or array structure)');
        }
        $URL .= 'state=' . $params['state'] . '&';
      }

      else{
        foreach($params['state'] as &$states) {
          $URL .= 'state=' . $states . '&';
        }
      }
    }

    if(array_key_exists('tool_ids', $params)){
      if(!is_array($params['tool_ids'])){
        if (!is_string($params['tool_ids'])){
          return $this->setError('User', 'Invalid tool_id input scheme (string or array structure)');
        }
        $URL .= 'tool_id=' . $params['tool_ids'] . '&';
      }

      else{
        foreach($params['tool_ids'] as &$tool_id) {
          $URL .= 'tool_id=' . $tool_id . '&';
        }
      }
    }

    if(array_key_exists('date_range_min', $params)){
      $URL .= 'date_range_min='. $params['date_range_min'] . '&';
    }
    if(array_key_exists('date_range_max', $params)){
      $URL .= 'date_range_max=' . $params['date_range_max'] . '&';
    }
    if(array_key_exists('history_id', $params)){
      $URL .= 'history_id=' . $params['history_id'] . '&';
    }

    $URL .= 'key=' . $this->galaxy->getAPIKey();

    $response = $this->httpGET($URL);

    return $this->expectArray($response);
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
  * 
  */
  public function create(){
     $this->setError('Galaxy', 'Not implemented: Creating/submitting a job is actually run under tools.py');
     return FALSE;
   }


  /**
    * Search for previously created jobs.
    *
    * Corresponds to the Galaxy api/path at:
    *   POST /api/jobs/search
    *
    * This method is designed to scan the list of previously run jobs and find
    *   records of jobs that had the exact some input parameters and datasets.
    *   This can be used to minimize, the amount of repeated work,
    *   and simplyrecycle the old results.
    *
    * @param $params
    *   A key value (associative array) where the keys can be the following:
    *   
    *   - tool_id:  Required. The tool id to execute. To find the tool id, use
    *     the index function of this class.
    *   - inputs:  Required. An associative array of key/value pairs where
    *     valid keys are 'id' and 'src' and 'id' is a tool_id (e.g. wc_gnu),
    *     and 'src' is is optional but defaults to 'hda'.  Alternatively, if
    *     multiple inputs are desired, this can be an array of associative
    *     arrays.
    *   - state: Optional. The state of the job: 'running', 'queued',
    *     'waiting', 'ok'.
    * @return
    *   An array of jobs matching the provided arguments.
    *
    * 
    */
  public function search($params) {

    $URL = $this->galaxy->getURL() . '/api/jobs/search/?key=' . $this->galaxy->getAPIKey();

    // Check that incoming arguments are appropriate.
    if (!array_key_exists('tool_id', $params)) {
      $this->setError('API', 'The \'tool_id\' paremeter is required');
      return FALSE;
    }

    // Make sure if the inputs argument exists then it's an associative array.
//     if (array_key_exists('inputs', $params)) {
//       $keys = array_keys($params['inputs']);
//       foreach ($keys as $key) {
//         if ($key !== 'src' and $key !== 'id') {
//           $this->setError('API', "The \"inputs\" parameter must be an associative array with keys either 'id' or 'src'.");
//           return FALSE;
//         }
//       }
//     }

    // We can't include arrays as POST arguemtns. They must strings,
    // so we'll convert to a JSON array which Galaxy likes.
    if (array_key_exists('inputs', $params)) {
      $params['inputs'] = json_encode($params['inputs']);
    }


    // Create a list of input items that is not NULL.
    $notNULLInputs = array();
    foreach($params as $element => $value) {
      if($value != NULL) {
        $notNULLInputs[$element] = $value;
      }
    }

    $response = $this->httpPOST($URL, $notNULLInputs);
    $this->setError("API", "This function is incomplete, please see our issues page on GitHub for
        more information");
    return FALSE;

  }
}


?>
