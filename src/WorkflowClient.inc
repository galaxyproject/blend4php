<?php
require_once "GalaxyInstance.inc";



class WorkflowClient {
  private $galaxy = NULL;
  
  // A variable to set to true if debugging, Toggles print statements 
  private $debug = True;

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
  	//print_r($result);

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
  	$i = curl_init();
  	$api_key = $this->galaxy->getAPIKey();
  	
  	if (!empty($workflow_id) && !empty($name)){
  		print "Cannot filter results by both input parameters\nPlease select only one filter\n";
  	}
  	
  	if ($workflow_id == NULL){
  		$url = $this->galaxy->getURL() . '/api/workflows/' . '?key=' . $api_key;
  	}
  	else{
  		$url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id .'?key=' . $api_key;
  	}

  	curl_setopt($i, CURLOPT_URL, $url);
  	curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
  	curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
  	 
  	$result = curl_exec($i);
  	
  	$info = curl_getinfo($i);
  	
  	$array = json_decode($result, true);
  	
  	if (!empty($name)){
   		foreach ($array as &$temp){
   			  if ($temp['name'] == $name){
   			  $foundworkflow = $temp;
   	    }
 		  }
   		print_r ($foundworkflow);
   	}
  	
  	else{
  		print_r ($result);
  	}
  	
  	curl_close($i);
  }

  /**
   *
   * @param $workflow_id Encoded
   *          workflow ID
   *          
   *         !! The Online docuementation for this function says its deprecated !!
   *         	We will have to look at the sourcecode from github if we want to find
   *         	the most recent version.  
   */
  public function import_shared_workflow($workflow_id) {
  	$target_url = 'http://127.0.0.1:8080/workflow/imp?id=' . $workflow_id;
  	
  	
  	$ch = curl_init();
  	curl_setopt($ch, CURLOPT_URL,$target_url);
  	curl_setopt($i, CURLOPT_CUSTOMREQUEST, "POST");
  	curl_setopt($ch, CURLOPT_POST,1);
  	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  	$result=curl_exec ($ch);
  	echo $result;
  	curl_close ($ch);
  	
  	
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
  	//print $url;
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
  	if($this->debug) {
  	print $this->galaxy->getURL(). '/api/workflows/?key='. $this->galaxy->getAPIKey();
  	}
  	
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
  
  
  /***
   * Build a new workflow or edit an existing workflow
   * 
   * POST /api/workflows
   * 
   * Parameters: 
   * 
            -	workflow_id (str): An existing workflow id. Either workflow_id, 
            	installed_repository_file or from_history_id must be specified
            
            -	parameters (python dictionary): If workflow_id is set - see _update_step_parameters()
            
            -	ds_map (python dictionary dict): If workflow_id is set - a dictionary mapping each input step id to a dictionary with 2 keys: 
           	    ‘src’ (which can be ‘ldda’, ‘ld’ or ‘hda’) and ‘id’ (which should be the id of a LibraryDatasetDatasetAssociation, LibraryDataset or HistoryDatasetAssociation respectively)
            
            -	no_add_to_history (str):  If workflow_id is set - if present in the payload with any value, 
            	the input datasets will not be added to the selected history
            
            -	history (str): If workflow_id is set - optional history where to run the workflow, 
            	either the name of a new history or “hist_id=HIST_ID” where HIST_ID is the id of an existing history. 
            	If not specified, the workflow will be run a new unnamed history
            
            -	replacement_params (python dictionary): If workflow_id is set - an optional dictionary used when renaming datasets
            
            -	from_history_id (str): Id of history to extract a workflow from. Either workflow_id, 
            	installed_repository_file or from_history_id must be specified
            
            -	job_ids (str): If from_history_id is set - optional list of jobs to include when extracting a workflow from history
            
            -	dataset_ids (str): If from_history_id is set - optional list of HDA `hid`s corresponding 
            	to workflow inputs when extracting a workflow from history
            
            -	dataset_collection_ids (str): If from_history_id is set - optional list of HDCA 
            	`hid`s corresponding to workflow inputs when extracting a workflow from history
            
            -	workflow_name (str): If from_history_id is set - name of the workflow to create when extracting a workflow from history
            
            -	allow_tool_state_corrections (bool): If set to True, any Tool parameter changes will not prevent running workflow, defaults to False

    
How the Galaxy Python code looks at this:

        ways_to_create = set( [
            'workflow_id',
            'installed_repository_file',
            'from_history_id',
            'shared_workflow_id',
            'workflow',
        ] )

   
   **/
   
 public function create_workflow($workflow_id = NULL, $parameters = NULL, $ds_map = NULL,
  		$no_add_to_history = True, $history =NULL, $replacement_params = NULL, 
  		$from_history_id=NULL, $job_ids = NULL, $dataset_ids = NULL, $dataset_collection_ids=NULL,
  		$workflow_name = NULL, $allow_tool_state_corrections = NULL ) {
  	
  	$url = $this->galaxy->getURL() . '/api/workflows/?key=' . $this->galaxy->getAPIKey();
  	//print $url;
  	$ch = curl_init();
  	 
  	curl_setopt($ch, CURLOPT_URL, $url);
  	curl_setopt($ch, CURLOPT_POST, 1);
  	curl_setopt($ch, CURLOPT_POSTFIELDS,
  			http_build_query(array(
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
  
  
}// End CLass 
