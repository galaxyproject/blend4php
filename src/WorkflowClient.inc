<?php
require_once "GalaxyInstance.inc";



class WorkflowClient {
  private $galaxy = NULL;

  /**
   * Implements the constructor.
   *
   * @param GalaxyInstance $galaxy
   */
  function __construct(GalaxyInstance $galaxy) {
    $this->galaxy = $galaxy;
  }

  /**
   * Delete a workflow identified by workflow_id.
   *
   * @param $workflow_id
   */
  public function delete_workflow($workflow_id) {

  	$i = curl_init();
    $api_key = $this->galaxy->getAPIKey();
    
    
  	$url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;
  	curl_setopt($i, CURLOPT_URL, $url);
    curl_setopt($i, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
  	 
  	$result = curl_exec($i);
  	$info = curl_getinfo($i);
  	// print_r ($info);
  	print_r($result);

  	curl_close($i);
  }

  /**
   * Exports a workflow
   * Reference Material: 
   * http://bioblend.readthedocs.org/en/latest/api_docs/galaxy/docs.html#export-or-import-a-workflow
   * 
   * @param $workflow_id
   *   Encoded workflow ID.
   * @return
   *   Dict representing the workflow requested.
   *   This "Dict" is synonymous with metadata
   */
  public function export_workflow_json($workflow_id) {
  	
  	// I'm not sure if this is properly exported 
  	// I need to know how the exporting aspect works
  	// I have a feeling I'm close, the metadata is in json form 
  	// but is this information enough to "export" it somewhere
  	// I need to ask Stephen about this 
  	$i = curl_init();
  	$api_key = $this->galaxy->getAPIKey();
  	
  	$url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;
  	
  	curl_setopt($i, CURLOPT_URL, $url);
  	curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
  	curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
 
  	$result = curl_exec($i);
  	
  	$info = curl_getinfo($i);
  	//print "\n\nResult\n\n";
  	//print_r($result);
  	
  	
  	//print "\n\nInfo\n\n";
  	//print_r ($info);
  	 
  	curl_close($i);

  }
  
  /**
   * Exports a workflow in json format to a given local path.
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
   */
  public function export_workflow_to_local_path($workflow_id, $file_local_path,
    $use_default_filename = TRUE) {
  	$i = curl_init();
  	$api_key = $this->galaxy->getAPIKey();
  	 
  	$url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;
  	 
  	curl_setopt($i, CURLOPT_URL, $url);
  	curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
  	curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
  	
  	$result = curl_exec($i);
  	 
  	$info = curl_getinfo($i);
  	//print "\n\nResult\n\n";
  	//print_r($result);
  	 
  	//print "\n\nInfo\n\n";
  	//print_r ($info);
  	$array = json_decode($result, true);
  	 
  	if ($use_default_filename == TRUE){
  		
  	  $success = file_put_contents($file_local_path . '/' . 'Galaxy-Workflow-' . $array['name'] . '.ga', $result);
  	}
  	else {
  		$success = file_put_contents($file_local_path, $result);
  	}
  	curl_close($i);


  }
  /**
   *
   * @param $workflow_id Encoded
   *   workflow ID
   * @param $label
   */
  public function get_workflow_inputs($workflow_id, $label) {
  }

  /**
   *
   * @param
   *          $workflow_id
   * @param
   *          $name
   * @param
   *          $published
   */
  public function get_workflows($workflow_id = NULL, $name = NULL, $published = FALSE) {
  
  }

  /**
   *
   * @param $workflow_id Encoded
   *          workflow ID
   */
  public function import_shared_workflow($workflow_id) {
  }

  /**
   *
   * @param
   *          $file_local_path
   */
  public function import_workflow_from_local_path($file_local_path) {
  }
  /**
   *
   * @param
   *          $workflow_json
   */
  public function import_workflow_json($workflow_json) {
  }
  /**
   *
   * @param $workflow_id
   *   Encoded workflow ID
   * @param $dataset_map
   * @param $params
   * @param $history_id
   * @param $history_name
   * @param $import_inputs_to_history
   * @param $replacement_params
   */
  public function run_workflow($workflow_id, $dataset_map = None, $params = NULL, $history_id = NULL,
    $history_name = NULL, $import_inputs_to_history = FALSE, $replacement_params = NULL) {
  }
  /**
   * Display information needed to run a workflow.
   *
   * @param $workflow_id
   *   Encoded workflow ID.
   * @return
   *   A description of the workflow and its inputs as a JSON object. For example:
   *    {
   *      u'id': u'92c56938c2f9b315',
   *      u'inputs': {u'23': {u'label': u'Input Dataset', u'value': u''}},
   *      u'name': u'Simple',
   *      u'url': u'/api/workflows/92c56938c2f9b315'
   *    }
   */
  public function show_workflow($workflow_id) {
  }
}
