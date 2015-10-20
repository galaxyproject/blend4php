<?php 
require_once "GalaxyInstance.inc";


class HistoryClient{
private $galaxy = NULL; 
private $debug = True;
	
	

 public function __construct($galaxy) {
	$this->galaxy = $galaxy;
 }
 
 
 
 /*TODO: Test this 
  * Creates a new  history in a galaxy instance 
  * returns REST restuls
  * calls upon
  * POST /api/histories:
  * 
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
 	$url = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();
 	//print $url;
 	$ch = curl_init();
 		
 	curl_setopt($ch, CURLOPT_URL, $url);
 	curl_setopt($ch, CURLOPT_POST, 1);
 	curl_setopt($ch, CURLOPT_POSTFIELDS,
 			http_build_query(array(
 					'name' => $name,
 					'tool_version' => $archive_source,
 					'archive_type' => $archive_type,
 					'history_id'=>$history_id,
 					'all_datasets' => $all_datasets,
 			)));
 	$message = '';
 	// receive server response ...
 	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
 	$message = curl_exec($ch);
 	curl_close($ch);
 	if($message === FALSE) {
 		print "I have failed";
 		return 'Error ' . curl_error($ch);
 	}
 	
 	return $message;
 	 	
 }
 
 /* What is a immutable id??
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
 	$ch = curl_init();
 	$URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/exports/' . $jeha_id .'/?key=' . $this->galaxy->getAPIKey();
 	
 	
 	curl_setopt($ch,CURLOPT_URL,$URL);
 	curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
 	
 	$output = curl_exec($ch);
 	if($output === FALSE) {
 		return 'Curl error: ' . curl_error($ch);
 	}
 	
 	curl_close($ch);
 	return $output;	
 }
 
 
 
 
 public function archive_export(){
 		
 }
 
 
 public function create_content(){
 	
 }
 
 
 
}
 
 ?>