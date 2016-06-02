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

class GalaxyJobs {
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

    // The 'tool_id' is required.
    if (!array_key_exists('job_id', $params)) {
      $this->setError("API", "A 'job_id' is required in order to invoke this call");
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/'. $params['job_id'] . '/build_for_rerun/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
//     $this->setError("API", "This function is not complete, the corresponding Galaxy API
//         function wants a history_id, why or how is still uknown. Please see our issues page on Github for more information");
    return $this->expectArray($response);
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

    // The 'tool_id' is required.
    if (!array_key_exists('job_id', $params)) {
      $this->setError("API", "A 'job_id' is required to see a job's inputs");
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/'. $params['job_id'] . '/inputs/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->expectArray($response);
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

    // The 'tool_id' is required.
    if (!array_key_exists('job_id', $params)) {
      $this->setError("API", "A 'job_id' is required to see a job's outputs");
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/'. $params['job_id'] . '/outputs/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->expectArray($response);
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

    // The 'tool_id' is required.
    if (!array_key_exists('job_id', $params)) {
      $this->setError("API", "A 'job_id' is required to see a job's metadata");
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/'. $params['job_id'] . '/inputs/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->expectArray($response);
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

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/?key=' . $this->galaxy->getAPIKey();

    // If a state is specified chech to see if the user is looking for multiple
    // states or if the user is only specifiying one
    if(array_key_exists('state', $params)){
      // Is the parameter an array of states?
      if(!is_array($params['state'])){
        // Is there only one parameter?
        if (!is_string($params['state'])){
          $this->setError('User', 'Invalid state input scheme (string or array structure)');
          return FALSE;
        }

        $URL .= '&state=' . $params['state'];
      }

      else{
        foreach($params['state'] as &$states) {
          $URL .= '&state=' . $states;
        }
      }
      unset($params['state']);
    }


    // If a state is specified chech to see if the user is looking for multiple
    // tool_ids or if the user is only specifiying one
    if(array_key_exists('tool_ids', $params)){
      // Is the parameter an array of tool_ids?
      if(!is_array($params['tool_ids'])){
        // Is there only one parameter?
        if (!is_string($params['tool_ids'])){
          return $this->setError('User', 'Invalid tool_id input scheme (string or array structure)');
        }
        $URL .= '&tool_id=' . $params['tool_ids'];
      }

      else{
        foreach($params['tool_ids'] as &$tool_id) {
          $URL .= '&tool_id=' . $tool_id;
        }
      }
      unset($params['tool_ids']);
    }


    // Add all other parameters to the URL.
    foreach ($params as $key => $value) {
      $URL .= '&' . $key . '=' . $value;
    }

    $response = $this->galaxy->httpGET($URL);

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
      $this->setError('API', 'The \'tool_id\' parameter is required');
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


    $response = $this->galaxy->httpPOST($URL, $params);

    print "\nResponse:";

    return $response;

    $this->setError("API", "This function is incomplete, please see our issues page on GitHub for
        more information");
    return FALSE;

  }
}


?>
