<?php

require_once('GalaxyAPIService.inc');


/**
 * @file
 *
 * The Workflows class.
 *
 * The Workflows class interacts with Galaxy to manage contents of a Galaxy
 * Workflow. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

class GalaxyWorkflows extends GalaxyAPIService {


  /**
   * Retreive a list of all the workflows.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/workflows
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * - is_published: (Optional) If true, published workflows will be displayed.
   *
   * @return
   *   An array containing all of the workflows in Galaxy.
   */
  public function index($params = array()) {

    if(array_key_exists('is_published', $params)){
      $URL = $this->galaxy->getURL() . '/api/workflows/?is_published=' . $params['is_published'] .'/&key=' . $this->galaxy->getAPIKey(); ;
      $response = $this->galaxy->httpGET($URL);
      return $this->galaxy->expectArray($response);
    }


    $URL = $this->galaxy->getURL() . '/api/workflows/?' . 'key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive detailed information about a specific workflow.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/workflows/{encoded_workflow_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id: The particular workflow that the user wants to see.
   *  - show_published: (Optional) If true, show published workflows.
   *
   * @return
   *   An array containing the details of a workflow.
   */
  public function show($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('workflow_id'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('workflow_id', 'show_published'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/?key=' . $this->galaxy->getAPIKey();

    if(array_key_exists('show_published', $params))
      $URL .= '&show_published=' . $params['show_published'];

    $response = $this->galaxy->httpGET($URL);

    return $this->galaxy->expectArray($response);
   }

  /**
   * Delete a specified workflow.
   *
   * Corresponds to an HTTP DELETE on the Galaxy API path
   *   /api/workflows/{encoded_workflow_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * - workflow_id: The ID of the workflow to delete. To obtain a workflow ID
   *     use Workflows::index().
   *
   * @return
   *
   */
  public function delete($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('workflow_id'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('workflow_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '?key=' . $this->galaxy->getAPIKey();

    return $this->galaxy->httpDELETE($URL);
   }

  /**
   * Returns a selected workflow (using a filepath) to download.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/workflows/{encoded_workflow_id}/download
   *
   * It is similar to the export function except the returned array does not
   * include a 'inputs' field.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * - workflow_id: ID of the workflow to retreive. To obtain a workflow ID,
   *     use Workflows::index().
   *
   * @return
   *   An array of the selected workflow.
   */
  public function download($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('workflow_id'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('workflow_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/download/?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);

  }

  /**
   * Updates an existing workflow using a pre-built JSON object.
   *
   * Corresponds to an HTTP PUT on the Galaxy API path
   *   /api/workflows/{encoded_workflow_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * - workflow_id: The ID of the workflow to update. Obtain a workflow ID
   *     using Workflows::index().
   * - workflow: The JSON representation of what the final workflow should
   *     look like, including the updates.
   *
   * @return
   *   An array containing the updated workflow.
   */
  public function update($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('workflow_id'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('workflow_id', 'workflow'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/workflows/'. $params['workflow_id'] . '/?key=' . $this->galaxy->getAPIKey();

    unset($params['workflow_id']);

    $response = $this->galaxy->httpPUT($URL, $params);
    return $this->galaxy->expectArray($response);
  }


  /**
    *  TODO incomplete
    *
    */
   public function buildModule($tool_id, $tool_input_ids = NULL,
       $tool_version = NULL, $annotation=NULL) {

    $URL = $this->galaxy->getURL() . '/api/workflows/build_module/?key=' . $this->galaxy->getAPIKey();
    $i = 0;
    // Follow same formating at imputting ids as invoke
    $input_ids = array();
    if ($tool_input_ids != NULL) {
      foreach ($tool_input_ids as &$tool_input_id) {
        $input_ids[$i] = array('id'=> $tool_input_id, 'src'=>'hda');
        $i++;
      }
    }

    $elements = array(
      'tool_id' => $tool_id,
      'tool_version' => $tool_version,
      'tool_inputs' => $input_ids,
      'annotation' => $annotation,
     );

     // Use only the elements that are not null
    $notNullInputs = array();
    foreach($elements as $element=>$value) {
      if($value != NULL ) {
        $notNullInputs[$element] = $value;
      }
    }

    $this->galaxy->setError('API', "The PHP implementation of this is not yet complete. Please see our 'issues' page on github for more information");
    return FALSE;
  }

  /**
   * Retreive a list of the workflow invocations for a given workflow.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   api/workflows/{workflow_id}/invocations
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * - workflow_id: The ID of the workflow's invocations to retreive.
   *
   * @return
   *   An array containing the invocations of a workflow.
   */
   public function indexInvocations($params) {

     // Check for required fields.
     if (!$this->checkRequiredParams($params, array('workflow_id'))) {
       return FALSE;
     }

     // Check for allowed fields.
     if (!$this->checkAllowedParams($params, array('workflow_id'))) {
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/invocations/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Retreive a detailed specific workflow invocation
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/workflows/{workflow_id}/invocations/{invocation_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * - workflow_id: The specified workflow of the invocation to show. To obtain
   *     a workflow ID use Workflows::index().
   * - invocation_id: The ID of the invocaiton. To obtain an invocation ID,
   *     use Workflows::index().
   *
   * @return
   *   An array containing details of the specified invocation.
   */
   public function showInvocations($params) {

     // Check for required fields.
     if (!$this->checkRequiredParams($params, array('workflow_id', 'invocation_id'))) {
       return FALSE;
     }

     // Check for allowed fields.
     if (!$this->checkAllowedParams($params, array('workflow_id', 'invocation_id'))) {
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/invocations/' . $params['invocation_id'] . '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Cancel an invocation request.
   *
   * Corresponds to an HTTP DELETE on the Galaxy API path
   *   /api/workflows/{workflow_id}/invocations/{invocation_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * - workflow_id: The ID of the workflow that the invocation belongs to. To
   *     obtain a workflow invocation, use Workflows::index().
   * - invocation_id: The ID of the invocation to delete.
   *
   * @return
   *   An array containing details of the specified invocation.
   */
   public function cancelInvocation($params) {
     // Check for required fields.
     if (!$this->checkRequiredParams($params, array('workflow_id', 'invocation_id'))) {
       return FALSE;
     }

     // Check for allowed fields.
     if (!$this->checkAllowedParams($params, array('workflow_id', 'invocation_id'))) {
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/invocations/'. $params['invocation_id'] . '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpDELETE($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Returns the invocation steps for a workflow.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/workflows/{workflow_id}/invocation/{invocation_id}/steps/{step_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * - workflow_id: The ID of the workflow's invocation steps to retreive. To
   *     obtain a workflow ID, use Workflows::index().
   *  - invocation_id: The ID of the invocation the step belongs to. To obtain
   *      an invocaiton ID, use Workflows::indexInvocation().
   *  - step_id: The ID of the step to retreive.
   *
   * @return
   *   An array containing information for the invocation step of
   *   the given workflow invocation.
   */
   public function invocationSteps($params) {

     // Check for required fields.
     if (!$this->checkRequiredParams($params, array('workflow_id', 'invocation_id' , 'step_id'))) {
       return FALSE;
     }

     // Check for allowed fields.
     if (!$this->checkAllowedParams($params, array('workflow_id', 'invocation_id', 'step_id'))) {
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/invocations/'. $params['invocation_id'] . '/steps/' . $params['step_id'] .'/?key=' . $this->galaxy->getAPIKey();

     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
    * Update state of running workflow step invocations.
    *
    * Corresponds to the Galaxy API/path at
    *   PUT /api/workflows/{workflow_id}/invocation/{invocation_id}/steps/{step_id}
    *
    * @param $workflow_id
    *   The id of the workflow whos invocation steps to update. To obtain
    *   a workflow id, please use this class's index function.
    * @param $invocation_id
    *   The id of the invocation the step belongs to. To obtain an invocaiton id
    *   please use this class's indexInvocation function.
    * @param $step_id
    *   The id of the step to update.
    * @param $payload
    *   The workflow as a JSON object (in an array), containing any or all update fields for
    *   the workflow.
    * @return
    *   An array containing information of the updated invocation step.
    *
    *
    */
   public function updateInvocationSteps($workflow_id, $invocation_id, $step_id, $payload = array()){
     $URL = $this->galaxy->getURL() . '/api/workflows/' .
       $workflow_id . '/invocations/' . $invocation_id . '/steps/' .
       $step_id . '?key=' . $this->galaxy->getAPIKey();

     $response = $this->galaxy->httpPUT($URL, $payload);
     // TODO: It is unclear how this function should operate
     $this->galaxy->setError("API", "It is unclear how this function should operate, and is therefore incomplete,
         please see our issues page on github for more information");
     return FALSE;
   }

  /**
   * Invokes (runs) a specified workflow.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/workflows/{encoded_workflow_id}/invocations
   *
   * If a $hist_id or $hist_name are not provided then a new history is
   * created.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id
   *    The ID of the workflow to invoke.
   *
   *  - inputs
   *    A mapping of workflow inputs to datasets and dataset collections.
   *    The datasets source can be a LibraryDatasetDatasetAssociation (ldda),
   *    LibraryDataset (ld), HistoryDatasetAssociation (hda), or
   *    HistoryDatasetCollectionAssociation (hdca). The map must be in the
   *    following format
   *    @code
   *    array(
   *      <input_index> => array(
   *        'id' => <encoded dataset ID>,
   *        'src' => '[ldda, ld, hda, hdca]'
   *      )
   *    );
   *    @endcode
   *    The id's are dataset IDs and can be found using the dataset class's
   *    index() function. The dataset must be present in a history, and the
   *    dataset 'state' must be 'ok' and 'deleted' must be set to FALSE.
   *
   *  - parameters
   *    A mapping of tool parameters that are non-datasets parameters. The map
   *    must be in the following format:
   *    @code
   *    'parameters' = array(
   *      [step_id_or_UUID] => array([param_name] => [value]),
   *      [step_id_or_UUID] => array([param_name] => [value])
   *    );
   *    @endcode
   *
   *  - history_id
   *    Optional. The id of the history to export the results to.
   *    Leave this ommitted if a new history is to be created.
   *
   * @return
   *   An array containing information on the workflow invoked.
   */
  public function invoke($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('workflow_id', 'inputs'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('workflow_id', 'inputs' ,
        'parameters', 'history_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/invocations/?key=' . $this->galaxy->getAPIKey();

    $elements = array(
      'inputs' => json_encode($params['inputs'], JSON_FORCE_OBJECT),
      'dataset_map' => json_encode($params['inputs'], JSON_FORCE_OBJECT),
      'history_id' => $params['history_id'],
    );

    //print_r($elements);

    // If the user provided parameters we want to add them to the elements
    // that get passed to the POST.
    if (array_key_exists('parameters', $params)) {
      $elements['parameters'] = json_encode($params['parameters'], JSON_FORCE_OBJECT);
    }
    //print_r($params['parameters']);

    $response = $this->galaxy->httpPOST($URL, $elements);
    return $this->galaxy->expectArray($response);
  }


  /**
   * Creates or edits a workflow with the given parameters.
   *
   * Corresponds to the Galaxy api/path at
   *   POST /api/workflows
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   If importing a JSON workflow:
   *   - workflow: A JSON representation of a workflow to be inserted into
   *       the database.
   *
   *   If running workflow from pre-existing workflow:
   *   - workflow_id: An existing workflow id. Either workflow_id,
   *       installed_repository_file or from_history_id must be specified.
   *       To obtain a workflow id, please see this class's index() function.
   *   - parameters: If workflow_id is set, specify the parameters for the
   *       workflow. See  Workflows::invoke() for more details.
   *   - ds_map: If workflow_id is set - a dictionary mapping each input step
   *       id to a dictionary with 2 keys: ‘src’ (which can be ‘ldda’,
   *       ‘ld’ or ‘hda’) and ‘id’ (which should be the id of a
   *       LibraryDatasetDatasetAssociation, LibraryDataset or
   *       HistoryDatasetAssociation respectively).
   *   - no_add_to_history: If workflow_id is set; if present in the payload
   *       with any value, the input datasets will not be added to the
   *       selected history.
   *   - replacement_params: (Optional) If workflow_id is set an dictionary
   *       used when renaming datasets.
   *   - history: (Optional) If workflow_id is sethistory where to run the
   *       workflow, either the name of a new history or “hist_id=HIST_ID”
   *       where HIST_ID is the id of an existing history. If not specified,
   *       the workflow will be run a new unnamed history.  To obtain a history
   *       ID Please refer to the index() function in the histories class.
   *
   *   If Creating/Running workflows from a History
   *   - from_history_id: ID of history to extract a workflow from. Either
   *       workflow_id, installed_repository_file or from_history_id must be
   *       specified.
   *   - job_ids: (Optional) If from_history_id is set, list of jobs to include
   *       when extracting a workflow from history.
   *   - dataset_collection_ids: (Optional) If from_history_id is set - list of
   *       HDCA hid`s corresponding to workflow inputs when extracting a
   *       workflow from history.
   *   - workflow_name: If from_history_id is set; name of the workflow to
   *       create when extracting a workflow from history.
   *   - allow_tool_state_corrections: (Optional) If set to True, any Tool parameter
   *       changes will not prevent running workflow, defaults to False.
   *
   *  @return
   *   An array containing the created workflow.
   */
  public function create($params) {

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('workflow', 'workflow_id', 'parameters', 'ds_map', 'no_add_to_history', 'replacement_params',
      'history', 'from_history_id', 'job_ids', 'dataset_collection_ids', 'workflow_name', 'allow_tool_state_corrections'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/workflows/?key=' . $this->galaxy->getAPIKey();


    $arguement = array();
    $error = NULL;

    // If the user is attempting to create a workflow from json
    if(array_key_exists('workflow', $params)){
      if(count($params) > 1){
        $this->galaxy->setError("API", "When creating a workflow from a pre-existing JSON workflow,
            the only parameter needed in this function is /'workflow/'");
        return FALSE;
      }
    }

    // If user is attempting to create workflow from pre-existing workflow:
    if(array_key_exists('workflow_id', $params)){
      if(array_key_exists('from_history_id', $params)){
        $arguement[] = "from_history_id";
        $error = "workflow_id";
      }
      if(array_key_exists('job_ids', $params)){
        $arguement[] = "job_ids";
        $error = "workflow_id";
      }
      if(array_key_exists('dataset_collection_ids', $params)){
        $arguement[] = 'dataset_collection_ids';
        $error = "workflow_id";
      }
      if(array_key_exists('workflow_name', $params)){
        $arguement[] = 'workflow_name';
        $error = "workflow_id";
      }
    }

    // If user attempting to create workfllow from history:
    else if(array_key_exists('from_history_id', $params)){
      if(array_key_exists('workflow_id', $params)){
        $arguement[] = "workflow_d";
        $error = "from_history";
      }
      if(array_key_exists('parameters', $params)){
        $arguement[] = "parameters";
        $error = "from_history";
      }
      if(array_key_exists('ds_map', $params)){
        $arguement[] = "ds_map";
        $error = "from_history";
      }
      if(array_key_exists('no_add_to_history', $params)){
        $arguement[] = "no_add_to_history";
        $error = "from_history";
      }
      if(array_key_exists('replacement_params', $params)){
        $arguement[] = "replacement_params";
        $error = "from_history";
      }
      if(array_key_exists('history', $params)){
        $arguement[] = "history";
        $error = "from_history";
      }
    }
    // Obtain any incorrect parameters
    if($error == "workflow_id"){
      $errors = "";
      foreach($arguement as $arg){
        $errors .= " " .$arg;
      }
      $this->galaxy->setError('API'," The following arguements you entered
          are not neccesary when executing workflow specified by workflow id: ". $errors);

      return FALSE;
    }

    if($error == "from_history"){
      $errors = "";
      foreach($arguement as $arg){
        $errors .= " " .$arg;
      }
      $this->galaxy->setError('API', "".$arguement." The following arguements you entered
          are not neccesary when executing workflow specified by from_workflow_id: ". $errors);
      return FALSE;
    }

    // Use only the elements that are not null
    $notNullInputs = array();
    foreach($params as $param => $value) {
      if($value != NULL ) {
        $notNullInputs[$param] = $value;
      }
    }

    $response = $this->galaxy->httpPOST($URL, $notNullInputs);
    return $this->galaxy->expectArray($response);
  }


}
