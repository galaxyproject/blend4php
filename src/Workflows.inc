<?php
include_once 'GalaxyRequest.inc';



class Workflows extends GalaxyRequest{

  /**
   * Implements the constructor.
   *
   * @param GalaxyInstance $galaxy
   */
  function __construct($galaxy) {
  parent::__construct($galaxy);
  }


  /**
   * GET /api/workflows
   *
   * (display collection of workflows can show published)
   *
   * @param bool is_published
   */
  public function index ($is_published = NULL){
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
 *   GET /api/workflows/{encoded_workflow_id}

     Displays information needed to run a workflow from the command line.
   *
   * @param string $workflow_id
   * @param show $show_published, if true, show published workflows
   */
  public function show($workflow_id, $show_published=true){
    $URL = $this->galaxy->getURL() . '/api/workflows/' .$workflow_id. '/?key=' . $this->galaxy->getAPIKey();
    $URL .= '&show_published=' . $show_published;
    return $this->rest->GET($URL);
  }


  /**
   * DELETE /api/workflows/{encoded_workflow_id}
   *
   * Delete a workflow identified by workflow_id.
   *
   * @param $workflow_id the id of the workflow to delete
   */
  public function delete($workflow_id) {
    $api_key = $this->galaxy->getAPIKey();
    $url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;
  return $this->rest->delete($url);
  }

  /**
   * TODO: what workflow function does this map to?
   * Exports a workflow
   *
   * @param $workflow_id
   *   Encoded workflow ID.
   *
   * @return
   *   Dict representing the workflow requested.
   *   This "Dict" is synonymous with metadata
   *
   *   This function designed for simply seeing the entities of the Workflow
   *   without seeing it through the browser
   */
  public function export_workflow_json($workflow_id) {
    $api_key = $this->galaxy->getAPIKey();

    $url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;

  return $this->rest->GET($url);
  }

  /**
   * GET /api/workflows/{encoded_workflow_id}/download
        Returns a selected workflow as a json dictionary.
   *
   * @param $workflow_id
   *   Encoded workflow ID
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
   *   This is an what the newest code says
   *   workflow_dict GET /api/workflows/{encoded_workflow_id}/download
   *   Returns a selected workflow as a json dictionary
   *   input param workflow_id
   */
  public function workflow_dict($workflow_id, $file_local_path,
    $use_default_filename = TRUE) {

    $api_key = $this->galaxy->getAPIKey();

    $url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;

    $result = $this->rest->GET($url);

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
   * TODO
   * PUT /api/workflows/{id}

     updates the workflow stored with workflow_id
   *
   * @param string $workflow_id
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
    var_dump($notNullInputs);
    return $this->rest->PUT($url, $notNullInputs);
  }


  /**
      TODO
   * POST /api/workflows/build_module

      Builds module details including a tool model for the workflow editor.

   * @param string $tool_id, the tool id to
   * @param string $tool_version
   * @param string array $tool_inputs, inputs for the tool, can be dataset_id's.
   *   dataset_ids can be found at /api/histories/history_id/content
   * @param string $annotation, annotation for the module
   */
  public function build_module($tool_id,$tool_input_ids=NULL, $tool_version=NULL,
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
    var_dump($input_ids);
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
   * GET /api/workflows/{workflow_id}/invocations

     Get the list of the workflow invocations

   * @param string $workflow_id
   */
  public function index_invocations($workflow_id){
    $url = $this->galaxy->getURL() . '/api/workflows/' .
    $workflow_id . 'invocations/?key=' . $this->galaxy->getAPIKey();
    return $this->rest->GET($url);
  }


  /**
   * GET /api/workflows/{workflow_id}/invocation/{invocation_id}

     Get detailed description of workflow invocation
   *
   * @param string $workflow_id
   * @param string $invocation_id
   */
 public function show_invocations($workflow_id, $invocation_id) {
   $url = $this->galaxy->getURL() . '/api/workflows/' .
       $workflow_id . 'invocations/'.$invocation_id.'/?key=' . $this->galaxy->getAPIKey();
   return $this->rest->GET($url);
 }


 /**
  * DELETE /api/workflows/{workflow_id}/invocation/{invocation_id}

   Cancel the specified workflow invocation.
  *
  * @param string $workflow_id
  * @param string $invocation_id
  */
 public function cancel_invocation($workflow_id, $invocation_id){
   $url = $this->galaxy->getURL() . '/api/workflows/' .
       $workflow_id . 'invocations/'.$invocation_id.'/?key=' . $this->galaxy->getAPIKey();
   return $this->rest->delete($url);
 }


 /**
  * GET /api/workflows/{workflow_id}/invocation/{invocation_id}/steps/{step_id}
  *
  * Returns the invocation steps for the url provided...
  *
  * @param string $workflow_id
  * @param string $invocation_id
  * @param string $step_id
  */
 public function invocation_steps($workflow_id, $invocation_id, $step_id){
   $url = $this->galaxy->getURL() . '/api/workflows/' .
       $workflow_id . 'invocations/'.$invocation_id.'/?key=' . $this->galaxy->getAPIKey();
   return $this->rest->delete($url);
 }


 /**
  * TODO
  * PUT /api/workflows/{workflow_id}/invocation/{invocation_id}/steps/{step_id}

   Update state of running workflow step invocation - still very nebulous
   but this would be for stuff like confirming paused steps can proceed
   etc....
  *
  * @param string $workflow_id
  * @param string $invocation_id
  * @param string $step_id
  */
 public function update_invocation_steps($workflow_id, $invocation_id, $step_id){
   $url = $this->galaxy->getURL() . '/api/workflows/' .
       $workflow_id . '/invocations/'.$invocation_id.'/steps/'
           .$step_id . '/?key=' . $this->galaxy->getAPIKey();
   return $this->rest->PUT($url);
 }


  /**
   * Deprecated to...
   * @param string $workflow_id Encoded
   * @param string  $label
   */
  public function get_workflow_inputs($workflow_id, $label) {
    $api_key = $this->galaxy->getAPIKey();

    $url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '/?key=' . $api_key;

    $result = $this->rest->GET($url);

    $array = json_decode($result, true);

    $inputs = $array['inputs'];

    $found = 0;
    foreach ($inputs as &$templabel){
      $labelArray = $templabel;
      if ($labelArray['label'] == $label){
        print ($labelArray['label']) . " is a workflow input\n";
        $found = 1;
      }
    }

    if ($found == 0){
      print "No workflow inputs of this label found\n";
    }


  }


  /**
   * TODO: What function does this map to in worklow.py ???
   *
   * @param
   */
  public function import_workflow_from_local_path($file_local_path) {


    // we are going to assume that the file that you wish to upload is of *.ga
    // type (we will check) if it is not we will display an error and not upload
    // the file

    if (!preg_match("!\.ga$!", $file_local_path)){
      return "Cannot upload a workflow that does not have the '.ga' extension\n";
    }

    else{
      print_r ($file_local_path);
      print "\n";
    }

    // I do not know how to generate an encoded Id so I'll ask for help when
    // Stephen is available

    // here is where a base64 encoded string would be created for this workflow
    // it will need 16 characters (so the first 16 characters of the name? and
    // then encode that? and if there's not 16 generate the rest of the letters
    // randomly)

//     $target_url = 'http://127.0.0.1:8080/workflow/imp?id=' . $workflow_id;


//     $ch = curl_init();
//     curl_setopt($ch, CURLOPT_URL,$target_url);
//     curl_setopt($i, CURLOPT_CUSTOMREQUEST, "POST");
//     curl_setopt($ch, CURLOPT_POST,1);
//     curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
//     $result=curl_exec ($ch);
//     echo $result;
//     curl_close ($ch);

  }


  /**
   *      POST /api/workflows/{encoded_workflow_id}/invocations
   *
   *      There are a few more features supported by the galaxy invoke function not present in thid
   *     But this function should allow for basic invokation of a workflow
   *     Galaxy parameters not currently supported by this function include:
   *        - replacement_dict: Workflow level parameters used for renaming post
             job actions.
   *         - copy_inputs_to_history: Should input data parameters be copied to
               target_history. (Defaults to False)
             - param_map: Override step parameters - should be dict with step id keys and
                tool param name-value dicts as values..
   *
   *    @param $input_dataset_ids (str array): the id's of the datasets to enter into the workflow
   *           These id's can be found under /api/histories/<history_id>/contents. For right now the dataset must
   *           come from a history. Also The dataset 'state' must be 'ok and 'deleted' must be set to false
   *
   *    @param $don't_add_to_history bool: defaults to false. Option to add inputs to the history
   *
   *    @param $hist_name: the name of the history, if a new one is being created
   *
   *    @param $hist_id : the id to export the results to. If a new history is not created
   *
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
   * TODO
   * Build a new workflow or edit an existing workflow
   *
   * POST /api/workflows
   *
     Build a new workflow or edit an existing workflow
   *

   *
   @param  string workflow_id: An existing workflow id. Either workflow_id,
              installed_repository_file or from_history_id must be specified

   @param   string array parameters: If workflow_id is set - see _update_step_parameters()

   @param   string array ds_map: If workflow_id is set - a dictionary mapping each input step id to a dictionary with 2 keys:
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
