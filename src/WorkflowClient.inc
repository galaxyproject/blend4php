<?php
require_once "GalaxyInstance.inc";



class WorkflowClient {
  private $galaxy = NULL;

  /**
   * Implements the constructor.
   *
   * @param GalaxyInstance $galaxy
   */
  function __construct($galaxy) {
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
  	$i = curl_init();
  	$api_key = $this->galaxy->getAPIKey();
  	
  	$url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;
  	
  	curl_setopt($i, CURLOPT_URL, $url);
  	curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
  	curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
 
  	$result = curl_exec($i);
  	
  	$info = curl_getinfo($i);
  	print "\n\nResult\n\n";
  	print_r($result);
  	
  	 
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
  	
  	$i = curl_init();
  	$api_key = $this->galaxy->getAPIKey();
  	
  	$url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key;
  	
  	curl_setopt($i, CURLOPT_URL, $url);
  	curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
  	curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
  	 
  	$result = curl_exec($i);
  	
  	$info = curl_getinfo($i);
  	
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
  	 
  	curl_close($i);
  	 
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
   *	COMPLETE
   * @param $workflow_id
   *   Encoded workflow ID
   * @param $dataset_map
   * @param $params
   * @param $history_id
   * @param $history_name
   * @param $import_inputs_to_history
   * @param $replacement_params
   *   	// POST /api/workflows/{encoded_workflow_id}/invocations
   */
  public function run_workflow($workflow_id, $dataset_map = NULL, $params = NULL, $history_id = NULL,
    $history_name = NULL, $import_inputs_to_history = FALSE, $replacement_params = NULL) {
  	
  	$url = $this->galaxy->getURL() . '/api/workflows/' .$workflow_id. '/invocations/?key=' . $this->galaxy->getAPIKey(); 
  	$ch = curl_init();
  	
  	curl_setopt($ch, CURLOPT_URL, $url);
  	curl_setopt($ch, CURLOPT_POST, 1);
  	curl_setopt($ch, CURLOPT_POSTFIELDS,
  			http_build_query(array(
  					'dataset_map' => $dataset_map,
  					'params' => $params,
  					'history_id' => $history_id,
  					'history_name'=>$history_name,
  					'import_inputs_to_history' => $import_inputs_to_history,
  					'replacement_params' => $replacement_params, 
  			)));
  	$message = '';
  	// receive server response ...
  	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  	$message = curl_exec($ch);
  	
  	if($message === FALSE) {
  		return 'Error ' . curl_error($ch);
  	}

  	return $message;
  	
  	
  }
  
  
  /* COMPLETE 
   * Custom Function 
   * Obtains a workflow baswed ona a given workflow name/annotation  
   * 
   * returns workflow_id if successful
   * returns False otherwise 
   * 
   * 
   */
  public function obtainWorkflow_id($name) {
  	
  	$workflow_id = "Nothing happened";
  	$ch = curl_init();
  	curl_setopt_array($ch, array(
  			CURLOPT_RETURNTRANSFER => 1,
  			CURLOPT_URL => $this->galaxy->getURL(). '/api/workflows/?key='. $this->galaxy->getAPIKey(),
  	));
  	$message = curl_exec($ch);

  	if($ch === FALSE){
  		print 'Curl error: ' . curl_error($ch);
  		return FALSE ;
  	}
  	curl_close ($ch);
  	//print 'I am on line 258'; 
  	$message = str_replace(array('[',']', " "), "", $message);
  	$message = str_replace(array('false'), '"false"', $message);
  	$message = str_replace('"tags":,', '', $message);
  	$len = strlen($message);
  	$good = FALSE;
  	$current_string = "";
  	// Break all the users intp json arrays, find the appropriate id
  	for($i = 0; $i<= $len; $i++) {
  		$char = substr($message, $i, 1);
  		$current_string .= $char;
  	
  		// If we have reached the end of the workflow, time to evaluate it
  		if($char == '}') {	
  			//print (json_decode($current_string,true));
  			//print("I am on line 270, current string is: ". $current_string);
  			$current_string = json_decode($current_string, true);
  			//print ($blah);
  			if($current_string['name'] == $name) {
  				$good = TRUE;
  				$workflow_id = $current_string["id"];
  				break;
  			}
  			// i++ to escape the comma
  			$i++;
  			$current_string = "";
  		}
  	
  	}
  	
  	//print ('And the workflow is' . $workflow_id);
  	
  	if(!$good) {
  		return FALSE;
  	}
  	
  	return $workflow_id;
  }
  
  
  /**
   * COMPLETE
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
  	$ch = curl_init();
  	$URL = $this->galaxy->getURL() . '/api/workflows/' .$workflow_id. '/?key=' . $this->galaxy->getAPIKey(); 
  	curl_setopt($ch,CURLOPT_URL,$URL);
  	curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);

  	$output = curl_exec($ch);
  	if($output === FALSE) {
  		return 'Curl error: ' . curl_error($ch);
  	}
  	curl_close($ch);
  	
  	return $output;
  	
  }
}
