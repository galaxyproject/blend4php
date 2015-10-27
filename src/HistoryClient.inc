<?php 
require_once "GalaxyInstance.inc";
require_once "RESTManager.php";


class HistoryClient{
private $galaxy = NULL; 
private $debug = True;
private $REST;
	
	

 public function __construct($galaxy) {
	$this->galaxy = $galaxy;
	$this->REST= new RESTManager();
 }
 
 
 
 /**TODO: Test this 
  * Creates a new  history in a galaxy instance 
  * returns REST restuls
  * calls upon
  * POST /api/histories:
  *  
  * 
  * Parameters:	(converted from a python dictionary)
    * name: the new history’s name 
    * history_id: the id of the history to copy 
    * all_datasets: copy deleted hdas/hdcas?  ‘True’ or ‘False’, defaults to True 
    * archive_source: the url that will generate the archive to import 
   	* archive_type: ‘url’ (default)
    
    keys – same as the use of keys in the index function above
    view – same as the use of view in the index function above
  
  * 
  */
 public function create($name, $archive_source,  $archive_type='url', $all_datasets= True, $history_id = NULL) {
 	$URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();

 	$input = array(
 		'name' => $name,
 		'tool_version' => $archive_source,
 		'archive_type' => $archive_type,
 		'history_id'=>$history_id,
 		'all_datasets' => $all_datasets,
 	);
	
 	return $this->REST->POST($URL, $input);
 }
 
 /** What is a immutable id??
  * 
  * GET /api/histories/{id}/exports/{jeha_id}:

    If ready and available, return raw contents of 
    exported history. 
    Use/poll “PUT /api/histories/{id}/exports” to initiate the 
    creation of such an export 
    - when ready that route will return 200 status code 
    (instead of 202) with a JSON dictionary containing a 
    download_url.
  * 
  */
 public function archive_download($history_id, $jeha_id){
 	$URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/exports/' . $jeha_id .'/?key=' . $this->galaxy->getAPIKey(); 		
 	return $this->REST->GET($URL); 	
}
 
/**
 * PUT /api/histories/{id}/exports:
  start job (if needed) to create history export for corresponding history.
@param  id:     the encoded id of the history to export

@return url of download site

*/
 public function archive_export($history_id){
 $URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/exports/?key=' . $this->galaxy->getAPIKey();
 $input = array('id' => $history_id); 
 $output = $this->REST->PUT($URL, $input); 
 $jsonArray = json_decode($output, true);
 if($jsonArray != NULL) {
 	return $jsonArray["download_url"];
 } 
 
 return $output; 
 	
 }
 
 /**
  * calls DELETE /api/histories/id
  * deletes the history with the given id
  */
 public function deleteHistory($history_id){
 	$URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/?key=' . $this->galaxy->getAPIKey();
 	return $this->REST->Delete($URL);
 }
 
 
 public function create_content(){
 	
 }
 
 
 
}
 
 ?>