<?php

require_once('GalaxyAPIService.inc');

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

class GalaxyJobs extends GalaxyAPIService {

  /**
   * Retreive a tool input template populated with this job's information.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/jobs/{encoded_job_id}/build_for_rerun
   *
   *   This function is suitable for rerunning or rendering parameters of
   *   the job.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *    - id: The ID of the job to retreive.
   *        The job id can be obtained from Jobs::index().
   *
   * @return
   *   An array containing ouput informaiton of the tool that has been
   *   built.
   */
  public function buildForRerun($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('id'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('id'))) {
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/'. $params['id'] . '/build_for_rerun';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

 /**
  * Retreive the input datasets created from the specified job.
  *
  * Corresponds to an HTTP GET on the Galaxy API path
  *   /api/jobs/{encoded_job_id}/inputs
  *
  * @param $params
  *    An associative array containing the input parameters for this function.
  *    The following parameters are available:
  *
  *    - job_id: The ID of the job's inputs to retreive.
  *        The job id can be obtained from Jobs::index().
  *
  * @return
  *   An array containing ouput informaiton of the job input.
  */
  public function inputs($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('job_id'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('job_id'))) {
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/'. $params['job_id'] . '/inputs/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

 /**
  * Retreive the output datasets created from the specified job.
  *
  * Corresponds to an HTTP GET on the Galaxy API path
  *   /api/jobs/{encoded_job_id}/inputs.
  *
  *
  * @param $params
  *    An associative array containing the input parameters for this function.
  *   The following parameters are available:
  *
  *    - job_id: The ID of the job's outputs to retreive.
  *        The job id can be obtained from Jobs::index().
  *
  * @return
  *   An array containing ouput informaiton of the job outputs.
  */
  public function outputs($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('job_id'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('job_id'))) {
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/'. $params['job_id'] . '/outputs/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

 /**
  * Retreive information about a specific job
  *
  * Corresponds to an HTTP GET on the Galaxy API path
  *   /api/jobs/{job_id}
  *
  * @param $params
  *   An associative array containing the input parameters for this function.
  *   The following parameters are available:
  *
  *   - job_id: The job to present. See the Jobs::index() to obtain job IDs.
  *   - full:  Set to TRUE to retrieve the full information about a job.
  *
  * @return
  *   An array containing information about the specified job.
  */
  public function show($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('job_id'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('job_id', 'full'))) {
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/'. $params['job_id'];
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    if (array_key_exists('full', $params) and $params['full'] == TRUE){
      $URL .= '&full=True';
    }

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

 /**
  * Retreive a list of jobs for current user.
  *
  * Corresponds to an HTTP GET on the Galaxy API path
  *   /api/jobs
  *
  *
  * @param $params
  *   An associative array containing the input parameters for this function.
  *   The following parameters are available:
  *
  *   - state: filter job search by any of these conditions:
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
  *   - tool_ids: (Optional) A list of tool IDs that limit the search to
  *       include only those with given tool_ids. To find tool IDs, refer to
  *       Tools::index().
  *   - date_range_min: (Optional) Limit the search of jobs updated after this
  *       date.
  *   - date_range_max: (Optional) Limit the search of jobs updated before this
  *       date.
  *   - history_id: (Optional) Limit listing of jobs to those that match
  *       history_id. To find the history id, refer to Histories::index().
  *
  * @return
  *   An array containing a list of all the jobs that matched
  *   the given parameters.
  */
  public function index($params) {

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/jobs/?key=' . $this->galaxy->getAPIKey();

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('state', 'tool_ids', 'date_range_min', 'date_range_max', 'history_id'))) {
      return FALSE;
    }

    // If a state is specified check to see if the user is looking for multiple
    // states or if the user is only specifiying one
    if(array_key_exists('state', $params)){
      // Is the parameter an array of states?
      if(!is_array($params['state'])){
        // Is there only one parameter?
        if (!is_string($params['state'])){
          $this->galaxy->setError('API', 'Invalid state input scheme (string or array structure)');
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


    // If a state is specified check to see if the user is looking for multiple
    // tool_ids or if the user is only specifiying one
    if(array_key_exists('tool_ids', $params)){
      // Is the parameter an array of tool_ids?
      if(!is_array($params['tool_ids'])){
        // Is there only one parameter?
        if (!is_string($params['tool_ids'])){
          return $this->galaxy->setError('API', 'Invalid tool_id input scheme (string or array structure)');
        }
        $URL .= '&tool_id=' . $params['tool_ids'];
      }

      else{
        foreach($params['tool_ids'] as &$tool_id) {
          $URL .= '&tool_id=' . $tool_id;
        }
      }
      unset($params['tool_ids']);


    // Add all other parameters to the URL as key value pairs.
    foreach ($params as $key => $value) {
      $URL .= '&' . $key . '=' . $value;
    }

  }
    $response = $this->galaxy->httpGET($URL);

    return $this->galaxy->expectArray($response);
}


 /**
  * This function is not implemented by its python counterpart
  *
  * NOTE: Creating/submitting a job is actually run under tools.py in the
  * Galaxy api
  *
  * @return
  *   FALSE
  */
  public function create() {
     $this->galaxy->setError('Galaxy', 'Not implemented: Creating/submitting a job is actually run under tools.py');
     return FALSE;
   }


  /**
    * Search for previously created jobs.
    *
    * Corresponds to an HTTP POST on the Galaxy API path
    *   /api/jobs/search
    *
    * This method is designed to scan the list of previously run jobs and find
    *   records of jobs that had the exact some input parameters and datasets.
    *   This can be used to minimize, the amount of repeated work,
    *   and recycle old results.
    *
    * @param $params
    *   An associative array containing the input parameters for this function.
    *   The following parameters are available:
    *
    *   - tool_id: The tool ID to execute. To find a tool ID, use
    *     Tools::index().
    *   - inputs: An associative array of key value pairs where
    *     valid keys are 'id' and 'src' and 'id' is a tool_id (e.g. wc_gnu),
    *     and 'src' is is optional but defaults to 'hda'.  Alternatively, if
    *     multiple inputs are desired, this can be an array of associative
    *     arrays.
    *   - state: (Optional) The state of the job: 'running', 'queued',
    *     'waiting', 'ok'.
    * @return
    *   An array of jobs matching the provided arguments.
    */
  public function search($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('tool_id', 'inputs'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('tool_id', 'inputs', 'state'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/jobs/search/?key=' . $this->galaxy->getAPIKey();

    // Check that incoming arguments are appropriate.
    if (!array_key_exists('tool_id', $params)) {
      $this->galaxy->setError('API', 'The \'tool_id\' parameter is required');
      return FALSE;
    }

    // We can't include arrays as POST arguments. They must be strings,
    // so we'll convert to a JSON array which Galaxy likes.
    if (array_key_exists('inputs', $params)) {
      $params['inputs'] = json_encode($params['inputs']);
    }

    $response = $this->galaxy->httpPOST($URL, $params);

    return $response;

    $this->galaxy->setError("API", "This function is incomplete, please see our issues page on GitHub for
        more information");
    return FALSE;
  }

}
