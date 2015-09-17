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
    
  	$url = $this->galaxy->getURL() . '/api/workflows/' . $workflow_id . '?key=' . $api_key[api_key];
  	curl_setopt($i, CURLOPT_URL, $url);
    curl_setopt($i, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
  	 
  	$result = curl_exec($i);
  	$info = curl_getinfo($i);
  	print_r($result);
  	
  	if (!$result)
  	{
  		echo "Problem encountered\n";
  	}
  	else
  	{
  		//$result = json_decode($result);
  		print_r($info);
  		print_r($result);
  	}
  	curl_close($i);
//     // TODO: We should return something to the user saying that
//     // the delete was successful or not successful in
//     // deleting the workflow

//     // Set the POST data
//     $postdata = http_build_query(array(
//       'key' => $this->galaxy->getAPIKey()
//     ));

//     // Set the POST options
//     $opts = array(
//       'http' => array(
//         'method' => 'DELETE',
//         'content' => $postdata,
//       	'header' => "Content-type: application/x-www-form-urlencoded\r\n"
//       )
//     );

//     // Create the POST context
//     $context = stream_context_create($opts);

//     // POST the data to an api
//     $url = $this->galaxy->getURL() . '/api/workflows/' . base64_encode($workflow_id);
//     $result = file_get_contents($url, false, $context);
  }

  /**
   * Exports a workflow
   *
   * @param $workflow_id
   *   Encoded workflow ID.
   * @return
   *   Dict representing the workflow requested.
   */
  public function export_workflow_json($workflow_id) {
  	$postdata = http_build_query(
  			array(
  					'var1' => 'some content',
  					'var2' => 'doh'
  			)
  	);
  	
  	$opts = array('http' =>
  			array(
  					'method'  => 'POST',
  					'header'  => 'Content-type: application/x-www-form-urlencoded\r\n',
  					'content' => $postdata
  			)
  	);
  	
  	$context  = stream_context_create($opts);
  	$url = $this->galaxy->getURL();
  	$result = file_get_contents($url, false, $context, -1, 40000);
  	
  	print $result;
  }
  
  public function test ()
  {
  	echo "hello\n";
  	
  }

  /**
   * Exports a workflow in json format to a given local path.
   *
   * @param $workflow_id
   *   Encoded workflow ID
   * @param $file_local_path Local
   *   Path to which the exported file will be saved. (Should not contain
   *   filename if use_default_name=True).
   * @param $use_default_filename
   *   If the use_default_name parameter is True, the exported file will be saved
   *   as file_local_path/Galaxy-Workflow-%s.ga, where %s is the workflow name.
   *   If use_default_name is False, file_local_path is assumed to contain the
   *   full file path including filename.
   */
  public function export_workflow_to_local_path($workflow_id, $file_local_path,
    $use_default_filename = TRUE) {


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
  	$opts = array(
  			'http' => array(
  					'method'  => 'GET',
  					'content' => '',
  					'timeout' => 60
  			)
  	);
  	
  	$context  = stream_context_create($opts);
  	$url = $this->getURL() . '/api/workflows?';
  	$result = file_get_contents($url, false, $context, -1, 40000);
  	
  	//     if($debug)
  		//     print ($result);
  	
  		// TODO: make sure we get a correct result.
  		$this->api_key = $result;
  
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
  	$ch = curl_init();
  	curl_setopt($ch,CURLOPT_URL,$this->galaxy->getURL() . '/api/workflows/' );
  	curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
  	curl_setopt($ch, CURLOPT_SSLVERSION,3);
  	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 1);
  	$output = curl_exec($ch);
  	
  	if($output === FALSE) {
  		return 'Curl error: ' . curl_error($ch);
  	}
  	
  	return $output;
  	
  }
}
