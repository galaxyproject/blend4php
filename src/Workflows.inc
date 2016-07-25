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
   * Corresponds to the Galaxy API/path at
   *   GET /api/workflows
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * @param $is_published
   *   Optional, if true, published workflows will be displayed.
   *
   * @return
   *   An array containing all of the workflows in Galaxy.
   *
   *
   */
  public function index($params){
    if(array_key_exists('is_published', $params)){
      $URL = $this->galaxy->getURL() . '/api/workflows/?is_published=' . $params['is_published'] .'/&key=' . $this->galaxy->getAPIKey(); ;
      $response = $this->galaxy->httpGET($URL);
      return $this->galaxy->expectArray($response);
    }
    $URL = $this->galaxy->getURL() . '/api/workflows/?' . '/&key=' . $this->galaxy->getAPIKey(); ;
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);

  }

  /**
   * Retreive detailed information about a specific workflow.
   *
   * Corresponds to the Galaxy API/path at
   *   GET /api/workflows/{encoded_workflow_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id
   *  - show_published
   *   If true, show published workflows.
   *
   * @return
   *   An array containing the details of a workflow.
   *
   *
   */
  public function show($params){
    if(!array_key_exists('workflow_id', $params)){
      $this->galaxy->setError("API", "A 'workflow_id' is required to show a workflow.");
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
   * Corresponds to the Galaxy API/method at
   *   DELETE /api/workflows/{encoded_workflow_id}
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - workflow_id
   *     The id of the workflow to delete. To obtain a workflow id
   *     please use this class's index function.
   *
   *
   */
  public function delete($params) {
    if(!array_key_exists('workflow_id', $params)){
      $this->galaxy->setError("API", "A 'workflow_id' is needed in order to delete a workflow.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '?key=' . $this->galaxy->getAPIKey();

    return $this->rest->delete($URL);
   }

  /**
   * Exports a workflow
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id
   *    Encoded workflow ID.
   *
   * @return
   *   An array representing the workflow requested.
   *
   *
   */
   public function export($params) {
     if(!array_key_exists('workflow_id', $params)){
       $this->galaxy->setError("API", "A 'workflow_id' is needed in order to export a workflow.");
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '?key=' . $this->galaxy->getAPIKey();

     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Returns a selected workflow (using a filepath) to download.
   *
   * It is similar to the export function except the returned array does not
   * include a 'inputs' field.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/workflows/{encoded_workflow_id}/download
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id
   *    Id of the Workflow to retreive To obtain a workflow id, please
   *    use this class index() function.
   *
   * @return
   *   An array of the selected workflow.
   *
   */
  public function download($params) {

    if(!array_key_exists('workflow_id', $params)){
      $this->galaxy->setError("API", "A 'workflow_id' is needed in order to download a workflow.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/download/?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);

  }


  /**
   * Updates an existing workflow using a pre-built JSON object.
   *
   * Corresponds to the Galaxy API method and path
   *   PUT /api/workflows/{encoded_workflow_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id
   *    The id of the workflow to update. You can obtain a workflow id through
   *    this class's index() function.
   *  - workflow
   *    The JSON representation of what the final workflow should look like,
   *    including the updates.
   *
   * @return
   *   An array containing the updated workflow.
   *
   *
   */
   public function update($params){

     if(!array_key_exists('workflow_id', $params)){
       $this->galaxy->setError("API", "A 'workflow_id' is needed in order to update a workflow.");
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
    $i =0;
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

    $this->galaxy->setError('API', "The PHP implementation of this is not yet complete. Please see our 'issues' page on github for more informaiton");
    return FALSE;
  }

  /**
   * Retreive a list of the workflow invocations for a given workflow.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/workflows/{workflow_id}/invocations
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id
   *    The id of the workflow whos invocations to retreive.
   *
   * @return
   *   An array containing the invocations of a workflow.
   *
   *
   */
   public function indexInvocations($params){

     if(!array_key_exists('workflow_id', $params)){
       $this->galaxy->setError("API", "A 'workflow_id' is needed in order to view the invocations of a workflow.");
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/invocations/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Retreive a detailed specific workflow invocation
   *
   * Corresponds to the Galaxy API/path at
   *   GET /api/workflows/{workflow_id}/invocation/{invocation_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id
   *    The specified workflow of the invocation to show.
   *    To obtain a workflow id please use this class index function.
   * - invocation_id
   *    The id of the invocaiton.
   *    To obtain an invocation id, please use this class's index invocation
   *    function.
   *
   * @return
   *   An array containing details of the specified invocation.
   *
   */
   public function showInvocations($params) {

     if(!array_key_exists('workflow_id', $params)){
       $this->galaxy->setError("API", "A 'workflow_id' is needed in order to view an invocation step of a workflow.");
       return FALSE;
     }

     if(!array_key_exists('invocation_id', $params)){
       $this->galaxy->setError("API", "An 'invocation_id' is needed in order to view an ivocation step of a workflow.");
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/invocations/' . $params['invocation_id'] . '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Cancel an invocation request.
   *
   * Corresponds to the Galaxy API/path at
   *   DELETE /api/workflows/{workflow_id}/invocation/{invocation_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id
   *    The id of the workflow that the invocation belongs to. To obtain
   *    a workflow invocation, please use this class's index() function.
   *  - invocation_id
   *    The id of the invocation to invoke.
   *
   * @return
   *   An array containing details of the specified invocation.
   *
   */
   public function cancelInvocation($params){
     $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . 'invocations/'. $params['invocation_id'] . '/?key=' . $this->galaxy->getAPIKey();
      $this->galaxy->setError("API", "This function has not yet been implemented by PHP. Please see our issues thread on github to learn more.");
      return FALSE;
   }

  /**
   * Returns the invocation steps for a workflow.
   *
   * Corresponds to the Galaxy API/path at
   *   GET /api/workflows/{workflow_id}/invocation/{invocation_id}/steps/{step_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - workflow_id
   *    The id of the workflow whos invocation steps to retreive. To obtain
   *    a workflow id, please use this class's index function.
   *  - invocation_id
   *    The id of the invocation the step belongs to. To obtain an invocaiton id
   *    please use this class's indexInvocation function.
   *  - step_id
   *    The id of the step to retreive.
   *
   * @return
   *   An array containing information for all the invocation steps of
   *   the given workflow invocation.
   *
   */
   public function invocationSteps($params){
     $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/invocations/'. $params['invocation_id'].'/?key=' . $this->galaxy->getAPIKey();

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
   * Corresponds to the Galaxy API method/path at
   *   POST /api/workflows/{encoded_workflow_id}/invocations
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
   *  - input_dataset_ids
   *    The list of id's of the datasets to enter into the workflow.
   *    These id's can be found using the dataset class's index() function.
   *    The dataset must be present in a history, and the dataset 'state' must
   *    be 'ok' and 'deleted' must be set to FALSE.
   *  - parameters
   *    A mapping of tool parameters that are non-datasets parameters. The map
   *    must be in the following format:
   *    @code
   *    'parameters' = array(
   *      [step_id_or_UUID] => array([param_name] => [value]),
   *      [step_id_or_UUID] => array([param_name] => [value])
   *    );
   *    @endcode
   *  - hist_id
   *    Optional. The id of the history to export the results to.
   *    If a new history is not created. Leave this ommitted if a new history
   *    is to be created.
   *
   * @return
   *   An array containing information on the workflow invoked.
   *
   *
   */
  public function invoke($params) {

    $URL = $this->galaxy->getURL() . '/api/workflows/' . $params['workflow_id'] . '/invocations/?key=' . $this->galaxy->getAPIKey();

    $input_ids = array();
    $i = 0;

    foreach($params['input_dataset_ids'] as &$input_dataset_id){
      $input_ids[$i] = array(
        'id' => $input_dataset_id,
        'src'=>'hda'
      );
      $i++;
    }

    $history_input = '';

    if (array_key_exists('hist_id', $params)) {
      $history_input = 'hist_id=' . $params['hist_id'];
    }

    $elements = array(
      'inputs' => json_encode($input_ids, JSON_FORCE_OBJECT),
      'dataset_map' => json_encode($input_ids, JSON_FORCE_OBJECT),
      'history' => $history_input,
    );

    // If the user provided parameters we want to add them to the elements
    // that get passed to the POST.
    if (array_key_exists('parameters', $params)) {
      $elements['parameters'] = json_encode($params['parameters'], JSON_FORCE_OBJECT);
    }

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
    *   - workflow_id:  An existing workflow id. Either workflow_id,
    *       installed_repository_file or from_history_id must be specified.
    *       To obtain a workflow id, please see this class's index() function.
    *   - parameters: If workflow_id is set, specify the parameters for the
    *       workflow. See this class's invoke() for more details.
    *   - ds_map: If workflow_id is set - a dictionary mapping each input step
    *       id to a dictionary with 2 keys: ‘src’ (which can be ‘ldda’,
    *       ‘ld’ or ‘hda’) and ‘id’ (which should be the id of a
    *       LibraryDatasetDatasetAssociation, LibraryDataset or
    *       HistoryDatasetAssociation respectively).
    *   - no_add_to_history: If workflow_id is set; if present in the payload
    *       with any value, the input datasets will not be added to the
    *       selected history.
    *   - replacement_params:  If workflow_id is set  an optional dictionary
    *       used when renaming datasets.
    *   - history:  If workflow_id is set  optional history where to run the
    *       workflow, either the name of a new history or “hist_id=HIST_ID”
    *       where HIST_ID is the id of an existing history. If not specified,
    *       the workflow will be run a new unnamed history.  To obtain a history
    *       ID Please refer to the index() function in the histories class.
    *
    *   If Creating / Running workflows from a History
    *   - from_history_id:  Id of history to extract a workflow from. Either
    *       workflow_id, installed_repository_file or from_history_id must be
    *       specified.
    *   - job_ids:  If from_history_id is set, optional list of jobs to include
    *       when extracting a workflow from history.
    *   - dataset_collection_ids: If from_history_id is set - optional list of
    *       HDCA hid`s corresponding to workflow inputs when extracting a
    *       workflow from history.
    *   - workflow_name: If from_history_id is set; name of the workflow to
    *       create when extracting a workflow from history.
    *   - allow_tool_state_corrections: if set to True, any Tool parameter
    *       changes will not prevent running workflow, defaults to False.
    *
    *  @return
    *   An array containing the created workflow.
    *
    *
    **/
   public function create($params) {

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
