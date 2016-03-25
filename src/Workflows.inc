<?php
include_once 'HTTPRequest.inc';

/**
 * @file
 *
 * The Workflows class.
 *
 * The Workflows class interacts with Galaxy to manage contents of a Galaxy
 * Workflow. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

/**
 * @defgroup workflowa_class Workflows Class
 * @{
 *   The Workflows class interacts with Galaxy to manage contents of a Galaxy
 *   workflow. The functions in this class correspond to the Galaxy API
 *   functions and are named similarly to their Python counterparts.
 * @}
 */


class Workflows extends HTTPRequest{

  private $galaxy;

  /**
  * The Workflows constructor.
  *
  * @param GalaxyInstance $galaxy
  *   A GalaxyInstance object.
  *
  * @return
  *   An instance of a workflows object.
  *
  * @ingroup workflows_class
  */
  function __construct($galaxy) {
    $this->galaxy = $galaxy;

    parent::__construct();
  }


   /**
    * Retreive a list of all the workflows.
    *
    * Corresponds to the Galaxy API/path at
    *   GET /api/workflows
    *
    * @param is_published
    *   Optional, if true, published workflows will be displayed.
    *
    * @return
    *   An array containing all of the workflows in Galaxy.
    *
    * @ingroup workflows_class
    */
  public function index($is_published = FALSE){
    $URL = $this->galaxy->getURL() . '/api/workflows/?is_published=' . $is_published .'/&key=' . $this->galaxy->getAPIKey(); ;
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }

  /**
    * Retreive detailed information about a specific workflow.
    *
    * Corresponds to the Galaxy API/path at
    *   GET /api/workflows/{encoded_workflow_id}
    *
    * @param $workflow_id
    * @param show $show_published
    *   If true, show published workflows.
    *
    * @return
    *   An array containing the details of a workflow.
    *
    * @ingroup workflows_class
    */
   public function show($workflow_id, $show_published=true){
     $URL = $this->galaxy->getURL() . '/api/workflows/' .$workflow_id. '/?key=' . $this->galaxy->getAPIKey();
     $URL .= '&show_published=' . $show_published;
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Delete a specified workflow.
    *
    * Corresponds to the Galaxy API/method at
    *   DELETE /api/workflows/{encoded_workflow_id}
    *
    * @param $workflow_id
    *   The id of the workflow to delete. To obtain a workflow id
    *   please use this class's index function.
    *
    * @ingroup workflows_class
    */
   public function delete($workflow_id) {
     $api_key = $this->galaxy->getAPIKey();
     $URL = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;
    return $this->rest->delete($URL);
   }

   /**
    * Exports a workflow
    *
    * @param $workflow_id
    *   Encoded workflow ID.
    *
    * @return
    *   An array representing the workflow requested.
    *
    * @ingroup workflows_class
    */
   public function export($workflow_id) {
     $api_key = $this->galaxy->getAPIKey();

     $URL = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;

     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

  /**
   * Returns a selected workflow as a json dictionary.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/workflows/{encoded_workflow_id}/download
   *
   * @param $workflow_id
   *   Id of the Workflow to retreive To obtain a workflow id, please
   *   use this class index() function.
   * @param $file_local_path Local
   *   Path to which the exported file will be saved. (Should not contain
   *   filename if use_default_name=True). It must be the full path to which
   *   the object is to be saved
   * @param $use_default_filename
   *   If the use_default_name parameter is True, the exported file will be saved
   *   as file_local_path/Galaxy-Workflow-%s.ga, where %s is the workflow name.
   *   If use_default_name is False, file_local_path is assumed to contain the
   *   full file path including filename.
   *
   * @return
   *   An array of the selected workflow.
   *
   * @ingroup workflows_class
   */
  public function workflowDict($workflow_id, $file_local_path,
    $use_default_filename = TRUE) {

    $api_key = $this->galaxy->getAPIKey();

    $URL = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;

    $response = $this->httpGET($URL);
    return $this->expectArray($response);

  }


   /**
    * TODO: incomplete
    *
    */
   public function update($workflow_id, $parameters = NULL, $ds_map = NULL,
     $no_add_to_history = TRUE, $history =NULL, $replacement_params = NULL,
     $from_history_id=NULL, $job_ids = NULL, $dataset_ids = NULL, $dataset_collection_ids=NULL,
     $workflow_name = NULL, $allow_tool_state_corrections = NULL){

    $URL = $this->galaxy->getURL() . '/api/workflows/'. $workflow_id . '/?key=' . $this->galaxy->getAPIKey();

    $elements = array(
        'workflow_id' => $workflow_id,
        'description' => 'bob',
        'workflow' => 'bob',
        'from_history_id' => $from_history_id,
        'parameters' => $parameters,
        'ds_map' => $ds_map,
        'no_add_to_history' =>$no_add_to_history,
        'history'  => $history,
        'replacement_params' => $replacement_params,
        'from_history_id' => $from_history_id,
        'jobs_id' => $job_ids,
        'dataset_ids'  => $dataset_ids,
        'dataset_collection_ids'=> $dataset_collection_ids,
        'workflow_name'=> $workflow_name,
        'allow_tool_state_corrections' => $allow_tool_state_corrections,
    );

    // Use only the elements that are not null
    $notNullInputs = array();
    foreach($elements as $element=>$value) {
      if($value != NULL ) {
        $notNullInputs[$element] = $value;
      }
    }

    $response = $this->httpPUT($URL, $notNullInputs);
    return $this->expectArray($response);
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

    $response = $this->httpPOST($URL, $notNullInputs);
    return $this->expectArray($response);
  }

   /**
    * Retreive a list of the workflow invocations for a given workflow.
    *
    * Corresponds to the Galaxy API/path
    *   GET /api/workflows/{workflow_id}/invocations
    *
    * @param workflow_id
    *   The id of the workflow whos invocations to retreive.
    *
    * @return
    *   An array containing the invocations of a workflow.
    *
    * @ingroup workflows_class
    */
   public function indexInvocations($workflow_id){
     $URL = $this->galaxy->getURL() . '/api/workflows/' .
     $workflow_id . 'invocations/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Retreive a detailed specific workflow invocation
    *
    * Corresponds to the Galaxy API/path at
    *   GET /api/workflows/{workflow_id}/invocation/{invocation_id}
    *
    * @param $workflow_id
    *   The specified workflow of the invocation to show.
    *   To obtain a workflow id please use this class index function.
    * @param $invocation_id
    *   The id of the invocaiton.
    *   To obtain an invocation id, please use this class's index invocation
    *   function.
    *
    * @return
    *   An array containing details of the specified invocation.
    *
    * @ingroup workflows_class
    */
   public function showInvocations($workflow_id, $invocation_id) {
     $URL = $this->galaxy->getURL() . '/api/workflows/' .
        $workflow_id . '/invocations/' . $invocation_id . '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }


   /**
    * Cancel an invocation request.
    *
    * Corresponds to the Galaxy API/path at
    *   DELETE /api/workflows/{workflow_id}/invocation/{invocation_id}
    *
    * @param workflow_id
    *   The id of the workflow that the invocation belongs to. To obtain
    *   a workflow invocation, please use this class's index() function.
    * @param invocation_id
    *   The id of the invocation to invoke.
    *
    * @return
    *   An array containing details of the specified invocation.
    *
    * @ingroup workflows_class
    */
   public function cancelInvocation($workflow_id, $invocation_id){
     $URL = $this->galaxy->getURL() . '/api/workflows/' .
        $workflow_id . 'invocations/'.$invocation_id.'/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->delete($URL);
   }


   /**
    * Returns the invocation steps for a workflow.
    *
    * Corresponds to the Galaxy API/path at
    *   GET /api/workflows/{workflow_id}/invocation/{invocation_id}/steps/{step_id}
    *
    * @param workflow_id
    *   The id of the workflow whos invocation steps to retreive. To obtain
    *   a workflow id, please use this class's index function.
    * @param invocation_id
    *   The id of the invocation the step belongs to. To obtain an invocaiton id
    *   please use this class's indexInvocation function.
    * @param step_id
    *   The id of the step to retreive.
    *
    * @return
    *   An array containing information for all the invocation steps of
    *   the given workflow invocation.
    *
    * @ingroup workflows_class
    */
   public function invocationSteps($workflow_id, $invocation_id, $step_id){
     $URL = $this->galaxy->getURL() . '/api/workflows/' .
         $workflow_id . 'invocations/'.$invocation_id.'/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->delete($URL);
   }


  /**
    * Update state of running workflow step invocations.
    *
    * Corresponds to the Galaxy API/path at
    *   PUT /api/workflows/{workflow_id}/invocation/{invocation_id}/steps/{step_id}
    *
    * @param workflow_id
    *   The id of the workflow whos invocation steps to update. To obtain
    *   a workflow id, please use this class's index function.
    * @param invocation_id
    *   The id of the invocation the step belongs to. To obtain an invocaiton id
    *   please use this class's indexInvocation function.
    * @param step_id
    *   The id of the step to update.
    *
    * @return
    *   An array containing information of the updated invocation step.
    *
    * @ingroup workflows_class
    */
   public function updateInvocationSteps($workflow_id, $invocation_id, $step_id){
     $URL = $this->galaxy->getURL() . '/api/workflows/' .
       $workflow_id . '/invocations/' . $invocation_id . '/steps/' .
       $step_id . '?key=' . $this->galaxy->getAPIKey();

     $response = $this->httpPUT($URL);
     return $this->expectArray($response);;
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
   * @param $workflow_id
   *   The ID of the workflow to invoke.
   * @param $input_dataset_ids:
   *   The list of id's of the datasets to enter into the workflow.
   *   These id's can be found using the dataset class's index() function.
   *   For right now the dataset must come from a history.
   *   Also The dataset 'state' must be 'ok and 'deleted' must be set to false.
   * @param $parameters
   *   Workflow tool parameters.
   * @param $hist_id
   *   Optional. The id of the history to export the results to.
   *   If a new history is not created. Leave this ommitted if a new history
   *   is to be created.
   *
   * @return
   *   An array containing information on the workflow invoked.
   *
   * @ingroup workflows_class
   */
  public function invoke($workflow_id, $input_dataset_ids, $parameters = NULL, $hist_id = NULL) {

    $URL = $this->galaxy->getURL() . '/api/workflows/' .
           $workflow_id . '/invocations/?key=' . $this->galaxy->getAPIKey();
    $input_ids = array();
    $i = 0;

    foreach($input_dataset_ids as &$input_dataset_id){
      $input_ids[$i] = array(
        'id' => $input_dataset_id,
        'src'=>'hda'
      );
      $i++;
    }
    $history_input='';
    if ($hist_id !== NULL) {
      $history_input = 'hist_id=' . $hist_id;
    }
    $elements = array(
      'inputs' => json_encode($input_ids,JSON_FORCE_OBJECT),
      'dataset_map' => json_encode($input_ids,JSON_FORCE_OBJECT),
      'history' => $history_input,
    );

    $response = $this->httpPOST($URL, $elements);
    return $this->expectArray($response);
  }


   /***
    * Creates or edits a workflow with the given parameters.
    *
    * Corresponds to the Galaxy api/path at
    *   POST /api/workflows
    *
    * @param $params
    *   A key value (associative array) where the keys can be the following:
    *
    *   If importing a Json workflow:
    *   - workflow:  A json representation of a workflow to be inserted into
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
    * @ingroup workflows_class
    **/
   public function create($params) {

    $URL = $this->galaxy->getURL() . '/api/workflows/?key=' . $this->galaxy->getAPIKey();


    $arguement = array();
    $error = NULL;

    // If the user is attempting to create a workflow from json
    if(array_key_exists('workflow', $params)){
      if(count($params) > 1){
        $this->setError("API", "When creating a workflow from a pre-existing JSON workflow,
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
      $this->setError('API'," The following arguements you entered
          are not neccesary when executing workflow specified by workflow id: ". $errors);

      return FALSE;
    }

    if($error == "from_history"){
      $errors = "";
      foreach($arguement as $arg){
        $errors .= " " .$arg;
      }
      $this->setError('API', "".$arguement." The following arguements you entered
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

    $response = $this->httpPOST($URL, $notNullInputs);
    return $this->expectArray($response);
  }


}
