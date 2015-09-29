<?php 
require_once "GalaxyInstance.inc";


class ToolClient{
private $galaxy = NULL; 
private $debug = True;
	
	
	
	
 function __construct($galaxy) {
	$this->galaxy = $galaxy;
 }
 
 
 /*
  returns information about a tool specified, or all tools if no
  tool id is specified
  *uses GET /api/tools: returns a list of tools defined by parameters::
  */
 function get_tools($tool_id = NULL) {
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
