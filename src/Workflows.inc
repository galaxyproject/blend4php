<?php
include_once 'GalaxyRequest.inc';

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


class Workflows extends GalaxyRequest{

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
    parent::__construct($galaxy);
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
    *   A Json array containing all of the workflows in Galaxy.
    *   
  	* @ingroup workflows_class
    */
  public function index($is_published = NULL){
    $i = curl_init();
    $api_key = $this->galaxy->getAPIKey();

    $url = $this->galaxy->getURL() . '/api/workflows/' . '?key=' . $api_key;
    $result = $this->rest->GET($url);
    $array = json_decode($result, true);

    if (!empty($is_published)){
      $foundworkflows = array ();
       foreach ($array as &$temp){
           //print_r ($temp['published']);
           if (!empty($temp['published'])){
           array_push($foundworkflows , $temp);
         }
       }
       return $foundworkflows;
     }

    else{
      return $result;
    }

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
    *   A Json Array containing the details of a workflow.
    *   
  	* @ingroup workflows_class
    */
   public function show($workflow_id, $show_published=true){
     $URL = $this->galaxy->getURL() . '/api/workflows/' .$workflow_id. '/?key=' . $this->galaxy->getAPIKey();
     $URL .= '&show_published=' . $show_published;
     return $this->rest->GET($URL);
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
     $url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;
    return $this->rest->delete($url);
   }

   /**
    * Exports a workflow
    *
    * @param $workflow_id
    *   Encoded workflow ID.
    *
    * @return
    *   Dict representing the workflow requested.
    *   This "Dict" is synonymous with metadata
    *
    * @ingroup workflows_class
    */
   public function export($workflow_id) {
     $api_key = $this->galaxy->getAPIKey();

     $url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;

    return $this->rest->GET($url);
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
   *   A Json dictionary of the selected workflow.
   *   
   * @ingroup workflows_class
   */
  public function workflowDict($workflow_id, $file_local_path,
    $use_default_filename = TRUE) {

    $api_key = $this->galaxy->getAPIKey();

    $url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;

    $result = $this->rest->GET($url);
    
    return $result.

    $array = json_decode($result, true);

    if ($use_default_filename == TRUE){

      $success = file_put_contents($file_local_path . '/' . 'Galaxy-Workflow-' . $array['name'] . '.ga', $result);
    }
    else {
      $success = file_put_contents($file_local_path, $result);
    }

    //return $success; Not sure what return to place here, if this function even needs a return

  }


   /**
    * TODO: incomplete
    * 
    * Corresponds to the Galaxy API/path at
    *   PUT /api/workflows/{id}
    *
    * updates the workflow stored with workflow_id
    *
    */
   public function update($workflow_id, $parameters = NULL, $ds_map = NULL,
     $no_add_to_history = TRUE, $history =NULL, $replacement_params = NULL,
     $from_history_id=NULL, $job_ids = NULL, $dataset_ids = NULL, $dataset_collection_ids=NULL,
     $workflow_name = NULL, $allow_tool_state_corrections = NULL){

    $url = $this->galaxy->getURL() . '/api/workflows/'. $workflow_id . '/?key=' . $this->galaxy->getAPIKey();

    $elements = array(
        'workflow_id' => $workflow_id,
        'description' => 'bob',
        'workflow' => 'bob',
        'from_history_id' => $from_history_id,
        'parameters' => $parameters,
        'ds_map'=>$ds_map,
        'no_add_to_history'=>$no_add_to_history,
        'history' =>$history,
        'replacement_params' => $replacement_params,
        'from_history_id' => $from_history_id,
        'jobs_id'=>$job_ids,
        'dataset_ids'=>$dataset_ids,
        'dataset_collection_ids'=>$dataset_collection_ids,
        'workflow_name'=>$workflow_name,
        'allow_tool_state_corrections' => $allow_tool_state_corrections,
    );

    // Use only the elements that are not null
    $notNullInputs = array();
    foreach($elements as $element=>$value) {
      if($value != NULL ) {
        $notNullInputs[$element] = $value;
      }
    }
    return $this->rest->PUT($url, $notNullInputs);
  }


  /**
    *  TODO incomplete
    * POST /api/workflows/build_module
    * 
    *  Builds module details including a tool model for the workflow editor.
    *
    * @param string $tool_id, the tool id to
    * @param string $tool_version
    * @param string array $tool_inputs, inputs for the tool, can be dataset_id's.
    *   dataset_ids can be found at /api/histories/history_id/content
    * @param string $annotation, annotation for the module
    */
   public function buildModule($tool_id,$tool_input_ids=NULL, $tool_version=NULL,
      $annotation=NULL){

    $url = $this->galaxy->getURL() . '/api/workflows/build_module/?key=' . $this->galaxy->getAPIKey();
    $i =0;
    // Follow same formating at imputting ids as invoke
    $input_ids = array();
      if($tool_input_ids !=NULL){

        foreach($tool_input_ids as &$tool_input_id){
          $input_ids[$i] = array('id'=> $tool_input_id, 'src'=>'hda');
          $i++;
        }
      }

     $elements = array(
      'tool_id'=>$tool_id,
      'tool_version'=>$tool_version,
      'tool_inputs'=>$input_ids,
      'annotation'=>$annotation,

     );

    // Use only the elements that are not null
    $notNullInputs = array();
    foreach($elements as $element=>$value) {
      if($value != NULL ) {
        $notNullInputs[$element] = $value;
    }

    return $this->rest->POST($url, $notNullInputs);
  }

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
    *   A Json array containing the invocations of a workflow.
    *   
    * @ingroup workflows_class
    */
   public function indexInvocations($workflow_id){
     $url = $this->galaxy->getURL() . '/api/workflows/' .
     $workflow_id . 'invocations/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->GET($url);
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
    *   A Json array containing details of the specified invocation.
    *
    * @ingroup workflows_class
    */
   public function showInvocations($workflow_id, $invocation_id) {
     $url = $this->galaxy->getURL() . '/api/workflows/' .
        $workflow_id . 'invocations/'.$invocation_id.'/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->GET($url);
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
    *   A Json array containing details of the specified invocation.
    *    
    * @ingroup workflows_class
    */
   public function cancelInvocation($workflow_id, $invocation_id){
     $url = $this->galaxy->getURL() . '/api/workflows/' .
        $workflow_id . 'invocations/'.$invocation_id.'/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->delete($url);
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
    *   A Json array containing information for all the invocation steps of 
    *   the given workflow invocation.
    *   
    * @ingroup workflows_class
    */
   public function invocationSteps($workflow_id, $invocation_id, $step_id){
     $url = $this->galaxy->getURL() . '/api/workflows/' .
         $workflow_id . 'invocations/'.$invocation_id.'/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->delete($url);
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
    *   A Json array containing information of the updated invocation step.
    *   
    * @ingroup workflows_class
    */
   public function updateInvocationSteps($workflow_id, $invocation_id, $step_id){
    $url = $this->galaxy->getURL() . '/api/workflows/' .
       $workflow_id . '/invocations/'.$invocation_id.'/steps/'
           .$step_id . '/?key=' . $this->galaxy->getAPIKey();
    return $this->rest->PUT($url);
   }

 

  /**
   * Invokes (runs) a specified workflow.
   * 
   * Corresponds to the Galaxy API method/path at
   *   POST /api/workflows/{encoded_workflow_id}/invocations
   *
   * @param $input_dataset_ids: 
   *   The list of id's of the datasets to enter into the workflow.
   *   These id's can be found using the dataset class's index() function.
   *   For right now the dataset must come from a history. 
   *   Also The dataset 'state' must be 'ok and 'deleted' must be set to false.
   * @param $don't_add_to_history 
   *   Defaults to false. Id true, the function will add the results to a 
   *   specified history.
   * @param $hist_name 
   *   The name of the history to output the results to, 
   *   if a new history is being created
   * @param $hist_id 
   *   Optional. The id of the history to export the results to. 
   *   If a new history is not created. Leave this ommitted if a new history
   *   is to be created.
   *   
   * @return 
   *   A Json object containing information on the workflow invoked.
   *   
   * @ingroup workflows_class
   */
  public function invoke($workflow_id, $input_dataset_ids, $hist_name=NULL,$hist_id=NULL,
      $dont_add_to_history=FALSE) {

    $url = $this->galaxy->getURL() . '/api/workflows/' .$workflow_id. '/invocations/?key=' . $this->galaxy->getAPIKey();
    $input_ids = array();
    $i = 0;

    foreach($input_dataset_ids as &$input_dataset_id){
      $input_ids[$i] = array('id'=> $input_dataset_id, 'src'=>'hda');
      $i++;
    }
    $history_input='';
    if($hist_id !== NULL) {$history_input = 'hist_id='.$hist_id; }
    else {$history_input = $hist_name;}
    $elements = array(
      'inputs'=>json_encode($input_ids,JSON_FORCE_OBJECT),
      'dataset_map'=>json_encode($input_ids,JSON_FORCE_OBJECT),
      'no_add_to_history'=>$dont_add_to_history,
      'history'=>$history_input,
    );
    return  $this->rest->POST($url, $elements);
  }


  /***
   * Creates or edits a workflow with the given parameters.
   *
   * Corresponds to the Galaxy api/path at
   *   POST /api/workflows
   *
   *
   *
   * @param workflow_id 
   *   An existing workflow id. Either workflow_id,
   *   installed_repository_file or from_history_id must be specified.
   *   To obtain a workflow id, please see this class's index() function. 
   * @param parameters 
   *   If workflow_id is set, specify the parameters for the workflow. 
   *   See this class's invoke() for more details.
   *
   *  @param ds_map: If workflow_id is set - a dictionary mapping each input step id to a dictionary with 2 keys:
                 ‘src’ (which can be ‘ldda’, ‘ld’ or ‘hda’) and ‘id’ (which should be the id of a LibraryDatasetDatasetAssociation, LibraryDataset or HistoryDatasetAssociation respectively)

   @param   string no_add_to_history:  If workflow_id is set - if present in the payload with any value,
              the input datasets will not be added to the selected history

   @param  string history: If workflow_id is set - optional history where to run the workflow,
              either the name of a new history or “hist_id=HIST_ID” where HIST_ID is the id of an existing history.
              If not specified, the workflow will be run a new unnamed history

   @param  string array replacement_params: If workflow_id is set - an optional dictionary used when renaming datasets

   @param   string from_history_id: Id of history to extract a workflow from. Either workflow_id,
              installed_repository_file or from_history_id must be specified

   @param  string array job_ids: If from_history_id is set - optional list of jobs to include when extracting a workflow from history

   @param   string dataset_ids: If from_history_id is set - optional list of HDA `hid`s corresponding
              to workflow inputs when extracting a workflow from history

   @param   string dataset_collection_ids: If from_history_id is set - optional list of HDCA
              `hid`s corresponding to workflow inputs when extracting a workflow from history

   @param   string workflow_name: If from_history_id is set - name of the workflow to create when extracting a workflow from history

   @param   bool allow_tool_state_corrections: If set to True, any Tool parameter changes will not prevent running workflow, defaults to False


   **/
 public function create($workflow_id = NULL, $parameters = NULL, $ds_map = NULL,
      $no_add_to_history = True, $history =NULL, $replacement_params = NULL,
      $from_history_id=NULL, $job_ids = NULL, $dataset_ids = NULL, $dataset_collection_ids=NULL,
      $workflow_name = NULL, $allow_tool_state_corrections = NULL ) {

    $url = $this->galaxy->getURL() . '/api/workflows/?key=' . $this->galaxy->getAPIKey();

    $elements = array(
      'workflow_id' => $workflow_id,
      'from_history_id' => $from_history_id,
      'parameters' => $parameters,
      'ds_map'=>$ds_map,
      'no_add_to_history'=>$no_add_to_history,
      'history' =>$history,
      'replacement_params' => $replacement_params,
      'from_history_id' => $from_history_id,
      'jobs_id'=>$job_ids,
      'dataset_ids'=>$dataset_ids,
      'dataset_collection_ids'=>$dataset_collection_ids,
      'workflow_name'=>$workflow_name,
      'allow_tool_state_corrections' => $allow_tool_state_corrections,
      );

    // Use only the elements that are not null
    $notNullInputs = array();
    foreach($elements as $element=>$value) {
      if($value != NULL ) {
        $notNullInputs[$element] = $value;
      }
    }

    return $this->rest->POST($url, $notNullInputs);


  }


}// End CLass
