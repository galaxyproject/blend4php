<?php 
include_once "GalaxyRequest.inc";


class Tools extends GalaxyRequest{

	
/**
 * Default constructor
 * @param GalaxyInstance $galaxy
*/ 
 public function __construct($galaxy) {
	parent ::__construct($galaxy);
 }
 
/**
 * 	GET /api/tools: returns a list of tools defined by parameters
 * @param string $tool_id
 * @param string $q
 * @param string $in_panel
 * @param string $trackster
 */
 public function index($tool_id = NULL, $q = NULL, $in_panel = FALSE, $trackster = FALSE ) {
 
 	$URL = $this->galaxy->getURL() . '/api/tools';	
 	if ($tool_id !==NULL){ $URL = $URL .'/'. $tool_id;}
 	if ($trackster != FALSE ) { $URL = $URL . '/?trackster=true'; }
 	if ($in_panel != FALSE ) {$URL = $URL . '/?in_panel=true';}
 	if ($q != NULL){$URL = $URL . '/?q=' . $q; }
	$URL = $URL . '/?key=' . $this->galaxy->getAPIKey();
	
 	return  $this->rest->GET($URL);
 		
 }

 /**
  * GET /api/tools/{tool_id}
	Returns tool information, including parameters and inputs.
  * 
  * @param string $tool_id
  */
 public function show($tool_id){
 	$URL = $this->galaxy->getURL() . '/api/tools/' . $tool_id .'/'. $this->galaxy->getAPIKey();
 }
 
 /**
  * GET /api/tools/{tool_id}/diagnostics 
  * Return diagnostic information to help debug panel and dependency related problems.
  *
  *@param str $tool_id
  */
 public function diagnostics($tool_id){
 	$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/diagnostics/?key=' . $this->galaxy->getAPIKey();	
	$this->rest->GET($URL);	
	
 	return $output; 		
 }
 
 /**
  * GET /api/tools/{tool_id}/reload 
  * Reload specified tool.
  * 
 	@param string $tool_id
  */
 public function reload($tool_id){
 	$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/reload/?key=' . $this->galaxy->getAPIKey();
 	return 	$this->rest->GET($URL);
 }
 
/**
 * It is unclear how inputs should be formated here. 

 *  GET /api/tools/{tool_id}/build
 *  
	Returns a tool model including dynamic parameters and updated values, repeats block etc.
 * 
 * @param string $tool_id, tool_id of the tool to perform action on
 * @param string history_id, history id of where to find the tool (I think?, in any case, it's needed to run)
 * @param string optional $tool_version
 
 */
 public function build($tool_id, $history_id, $tool_version=NULL){	
 	
 	$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/build';
 	if ($tool_version !=NULL){$URL = $URL . '/?tool_version='. $tool_version;}
 	$URL = $URL . '/?key=' . $this->galaxy->getAPIKey();	
 	$URL .= '&history_id=' . $history_id;
 	
 	return 	$this->rest->GET($URL);
 }
 
 /**
  * GET /api/tools/{tool_id}/citations
  * 
  * Obtains citations for a given tool
  * 
  * @param string $tool_id
  */
 public function citations($tool_id){
 	$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/citations/?key=' . $this->galaxy->getAPIKey();
 	return $this->rest->GET($URL);
 }
 
 
 /**
  *  GET /api/tools/{tool_id}/download
  *  
  *  by default this will give us a file in binary, to assure this is outputted in its correct form, simply
  *  input the download to a .gz file 
  *  Prompts user to download information on specified tool
  *  
  * @param string $tool_id
  */
 public function download($tool_id){
 	$URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/download/?key=' . $this->galaxy->getAPIKey();
 	return $this->rest->GET($URL);
 }
 
 
 /**

  * POST /api/tools 
  * 
  * Executes tool using specified inputs and returns tool's outputs.    
  *  
  * @param action - string optional 'rerun' to rerun the tool and not execute
  * @param tool_id - string  (tool_id to execute)
  * @param tool_version - string  OPTIONAL, specify specific tool version
  * @param history_id - string history_id where tool is located
  * @param region - string optional (information on the region of the genome being rerun)
  * @param input_dataset_ds - array of dataset id's where the tool should grab the inputs from
  * similar to workflow_invoke
  */
 public function create($tool_id,  $input_dataset_ids, $history_id = NULL,$tool_version=NULL,
 		$region = NULL,  $action = NULL ) {
 	$URL = $this->galaxy->getURL() . '/api/tools/?key=' . $this->galaxy->getAPIKey();
	
 	$input_ids = array();
 	$i=0;
 	foreach($input_dataset_ids as &$input_dataset_id){
 		$input_ids[$i] = array('id'=> $input_dataset_id, 'src'=>'hda');
 		$i++;
 	}
 	
 	$elements = array(
				'tool_id' => $tool_id,
				'tool_version' => $tool_version,
				'inputs' => json_encode($input_ids,JSON_FORCE_OBJECT),
				'history_id'=>$history_id,
				'region' => $region,
				'action' => $action,
				);
 	//create a list of input items that is not null
 	$notNullInputs = array();
 	foreach($elements as $element=>$value) {
 		if($value != NULL) {
 			$notNullInputs[$element] = $value;
 		}
 	}
 	
 	return $this->rest->POST($URL, $notNullInputs);
 }
 	
}// End tool class 

?>
