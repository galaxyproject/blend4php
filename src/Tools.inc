<?php 
include "GalaxyRequest.inc";


class Tools extends GalaxyRequest{

	

 public function __construct($galaxy) {
	parent ::__construct($galaxy);
 }
 
 
 /**
  returns information about a tool specified, or all tools if no
  tool id is specified
  *uses GET /api/tools: returns a list of tools defined by parameters::
  
  *@param str $rool_id 
  */
 public function get_tools($tool_id = NULL) {
 	if($tool_id === NULL) {
 		$URL = $this->galaxy->getURL() . '/api/tools/?key=' . $this->galaxy->getAPIKey();
 	}else {
 		$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/?key=' . $this->galaxy->getAPIKey();
 	}
	
	$output = $this->rest->GET($URL);
 	 
 	return $output;
 		
 }
 /**        
  *  Detect whether the tool with the given id is installed.

     @param tool_id: exact id of the tool
     @param type tool_id:  str

     @return list with available versions
        
  */
 
 public function detect($tool_id){
 
 }
 
 
 /**Functional! 
  * Calls upon 
  * GET /api/tools/{tool_id}/diagnostics 
  * Return diagnostic information to help debug panel and dependency related problems.
  *@param str $tool_id
  */
 
 public function diagnostics($tool_id){
 	$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/diagnostics/?key=' . $this->galaxy->getAPIKey();	
	$this->rest->GET($URL);	
	
 	return $output; 		
 }
 
 
 /**
  * calls upon 
  * GET /api/tools/{tool_id}/reload 
  * Reload specified tool.
 	@param string #tool_id
  */
 public function reload($tool_id){
 	$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/reload/?key=' . $this->galaxy->getAPIKey();
 	return 	$this->rest->GET($URL);
 }
 
 
 
 
 
 /** !!WARNING!!: Currently not functional. when called it asks for a history id, though it shouldn't need one.
  *  
  * Utilizes Python's 'build' method through Rest command 
  * GET /api/tools/{tool_id}/build 
  * Returns a tool model including dynamic parameters and updated values, repeats block etc.
  * 
  * Not completely certain of its practical use but it seems simple enough to implement so I will do so
  * @param str $tool_id
  */
 public function build_tool($tool_id){	
 	$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/build/?key=' . $this->galaxy->getAPIKey();
 	return $this->rest->GET($URL); 	
 }
 
 
 /**
  * Utilizises python's 'create' method through Rest command
  * POST /api/tools 
  *       Executes tool using specified inputs and returns tool's outputs.
  *       
  * 
  * there is little docuementation on the parameters however these are the ones
  * I've found through parsing the python code 
  * 
  * @param action - string optional (indicat3es whther to rerun or not)
  * @param tool_id - string  (tool_id to execute)
  * @param tool_version - string  (I'm not entirely sure if this is optional but
  * 						it is the tool version of the given tool id)
  * @param history_id - string optional (Somehow this is optional )
  * @param region - string optional (I'm not entirely sure what this does)
  * @param inputs - string optional (I believe you can specify the inputs as files_ )
  */
 
 public function executeTool($tool_id, $tool_version, $inputs=NULL,  $history_id = NULL, $region = NULL,  $action = NULL ) {
 	$URL = $this->galaxy->getURL() . '/api/tools/?key=' . $this->galaxy->getAPIKey();

 	$input = array(
						'tool_id' => $tool_id,
						'tool_version' => $tool_version,
						'inputs' => $inputs,
						'history_id'=>$history_id,
						'region' => $region,
						'action' => $action,
				);
 	
 	
 	return $this->rest->POST($URL, $input);
 }
 	
}// End tool class 

?>
