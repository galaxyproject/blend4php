<?php 
require_once "GalaxyInstance.inc";


class ToolClient{
private $galaxy = NULL; 
private $debug = True;
	
	
	
	
 public function __construct($galaxy) {
	$this->galaxy = $galaxy;
 }
 
 
 /*
  returns information about a tool specified, or all tools if no
  tool id is specified
  *uses GET /api/tools: returns a list of tools defined by parameters::
  */
 public function get_tools($tool_id = NULL) {
 	$ch = curl_init();
 	if($tool_id === NULL) {
 		$URL = $this->galaxy->getURL() . '/api/tools/?key=' . $this->galaxy->getAPIKey();
 	}else {
 		$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/?key=' . $this->galaxy->getAPIKey();
 	}
 	
 	curl_setopt($ch,CURLOPT_URL,$URL);
 	curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
 	
 	$output = curl_exec($ch);
 	if($output === FALSE) {
 		return 'Curl error: ' . curl_error($ch);
 	}
 	curl_close($ch);
 	 
 	return $output;
 	
 	
 }
 
 
 /*
  * Utilizises python's 'create' method through Rest command
  * POST /api/tools 
  *       Executes tool using specified inputs and returns tool's outputs.
  *       
  * 
  * there is little docuementation on the parameters however these are the ones
  * I've found through parsing the python code 
  * 
  * action - string optional (indicat3es whther to rerun or not)
  * tool_id - string  (tool_id to execute)
  * tool_version - string  (I'm not entirely sure if this is optional but
  * 						it is the tool version of the given tool id)
  * history_id - string optional (Somehow this is optional )
  * region - string optional (I'm not entirely sure what this does)
  * inputs - string optional (I believe you can specify the inputs as files_ )
  * 	It is still unclear the parameters of this file. I.e. where the file needs to be in order for the functino to
  * 	call it. 
  */
 
 public function executeTool($tool_id, $tool_version, $inputs=NULL,  $history_id = NULL, $region = NULL,  $action = NULL ) {
 	$url = $this->galaxy->getURL() . '/api/tools/?key=' . $this->galaxy->getAPIKey();
 	//print $url;
 	$ch = curl_init();
 	 
 	curl_setopt($ch, CURLOPT_URL, $url);
 	curl_setopt($ch, CURLOPT_POST, 1);
 	curl_setopt($ch, CURLOPT_POSTFIELDS,
 			http_build_query(array(
 					'tool_id' => $tool_id,
 					'tool_version' => $tool_version,
 					'inputs' => $inputs,
 					'history_id'=>$history_id,
 					'region' => $region,
 					'action' => $action,
 			)));
 	$message = '';
 	// receive server response ...
 	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
 	$message = curl_exec($ch);
 	 
 	if($message === FALSE) {
 		print "I have failed";
 		return 'Error ' . curl_error($ch);
 	}
 	
 	return $message;
 }
 

 
 
 
 /* Incomplete 
  * Custom Function
  * Obtains a tool id baswed ona a given tool name/annotation
  *
  * returns tool_id if successful
  * returns False otherwise
  *
  *
  */
 public function obtainTool_id($name) {
 	 
 	$tool_id = "Nothing happened";
 	$ch = curl_init();
 	curl_setopt_array($ch, array(
 			CURLOPT_RETURNTRANSFER => 1,
 			CURLOPT_URL => $this->galaxy->getURL(). '/api/tools/?key='. $this->galaxy->getAPIKey(),
 	));
 	$message = curl_exec($ch);
 
 	if($ch === FALSE){
 		print 'Curl error: ' . curl_error($ch);
 		return FALSE ;
 	}
 	curl_close ($ch);
 	$message = str_replace(array('[',']', " "), "", $message);
 	$message = str_replace(array('"version":""'), '', $message);
 	$message = str_replace(array ('-1'), '"-1"', $message);
 	$message = str_replace(array('{
"elems":
'), '', $message);
 	$len = strlen($message);
 	$good = FALSE;
 	$current_string = "";
 	// Break all the users intp json arrays, find the appropriate id
 	for($i = 0; $i<= $len; $i++) {
 		$char = substr($message, $i, 1);
 		$current_string .= $char;
 		 
 		// If we have reached the end of the tool, time to evaluate it
 		if($char == '}') {
 			//print $current_string;
 			$current_string = json_decode($current_string, true);
 			var_dump($current_string);
 			if($current_string !== NULL and in_array("name", $current_string) and $current_string["name"] == $name) {
 				$good = TRUE;
 				$tool_id = $current_string["id"];
 				break;
 			}
 			$i++;
 			$current_string = "";
 		} 		 
 	}

 	if(!$good) {
 		print "NOOO!";
 		return FALSE;
 	}
 	 print $tool_id;
 	return $tool_id;
 }
	
	
	
	
	
	
	
	
	
	
	
	
}// End tool class 










?>
