<?php
/**
 * @file
 *
 * API operations on a history.
 *
 * Functions correspond to the Galaxy API file at:
 * https://github.com/galaxyproject/galaxy/blob/dev/lib/galaxy/webapps/galaxy/api/histories.py
 *
 */
require_once 'GalaxyRequest.inc';


/**
 *
 *
 */
class Histories extends GalaxyRequest {


  /**
   *
   * @param unknown $galaxy
   */
   public function __construct($galaxy) {
   	parent::__construct($galaxy);
   }



   /**
    * POST /api/histories:
    *
    *  Creates a new  history in a galaxy instance
    *  Note the option to pass 'keys' and 'views' is currently not supported
    *
    * @param string name: the new history’s name
    * @param string history_id: the id of the history to copy (will copy contents to new history)
    * @param bool all_datasets: copy deleted hdas/hdcas?  ‘True’ or ‘False’, defaults to True
    * @param string archive_source: the url that will generate the archive to import
      @param string archive_type: ‘url’ (default)

      
      @return string/Json from server response 

    *
    */
   public function create($name, $history_id = NULL,$annotation = NULL, $archive_source=NULL,  $archive_type=NULL,
   		$all_datasets= True ) {
     $URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();

     $inputs = array(
       'name' => $name,
     	'annotation'=>$annotation,	
       'tool_version' => $archive_source,
       'archive_type' => $archive_type,
       'history_id'=>	$history_id,
       'all_datasets' => $all_datasets,
     );
     
     //Assure we are not inputting null values into the python dictionary
     $notNullInputs = array();
     foreach ($inputs as $inputName=>$input){
     	if($input !== NULL){
     		$notNullInputs[$inputName] = $input; 
     	}
     }

     return $this->rest->POST($URL, $notNullInputs);
   }
   
   /**
    * GET /api/histories:
    * 
      return undeleted histories for the current user
      
      GET /api/histories/deleted:
      
      return deleted histories for the current user
        .. note:: Anonymous users are allowed to get their current history
    */
   public function index(){
   	$URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();
   	$URLDeleted = $this->galaxy->getURL() . '/api/histories/deleted/?key=' . $this->galaxy->getAPIKey();
   	$result = $this->rest->GET($URL) . $this->rest->GET($URLDeleted);
    $result = json_encode($result);
   	return  $result;
   }

   /**
    * GET /api/histories/{id}:
    * 
      return the history with ``id``
      
      GET /api/histories/deleted/{id}:
      
      return the deleted history with ``id``
      
      GET /api/histories/most_recently_used:
      
      return the most recently used history
      
    * @param str $history_id
    * 
    * @return str/json 

    */
   public function show($history_id){
   	
   	$URL = $this->galaxy->getURL() . '/api/histories/'.$history_id .'/?key=' . $this->galaxy->getAPIKey();
   	$URL2 = $this->galaxy->getURL() . '/api/histories/deleted/'.$history_id .'/?key=' . $this->galaxy->getAPIKey();
   	$URL3 = $this->galaxy->getURL() . '/api/histories/most_recently_used/?key=' . $this->galaxy->getAPIKey();
   	$result = $this->rest->GET($URL) . $this->rest->GET($URL2) . $this->rest->GET($URL3);
   	$result = json_encode($result);
   	return $result; 
   }
   

   /** 
    * Download a given history with indicated history id 
    * 
    * Calls to requests: 
      PUT /api/histories/{id}/exports” 
      Initiates the download, summons the download url path 
      ** (SAME AS archive_export() function) **
      
      GET /api/histories/{id}/exports/{jeha_id}
      If ready and available, return raw contents of
      exported history.
     
      @param string history_id the id of the history to download
      
      @return returns the physical history downloaded
    *
    */
   public function archive_download($history_id){
    $error_message = "Error, unrecognized server response.";
    // Obtain download URL 

    $jeha_id = $this->archive_export($history_id);
    //convert jeha_id into an array
    $jeha_id = json_decode($jeha_id,true);
    if($jeha_id == NULL) {
    	return $error_message;
    }
    if(!array_key_exists('download_url', $jeha_id)) {
    	return $error_message;
    }
    // download_url should be in the form of /api/histories/{id}/exports/{jeha_id}
    $URL = $this->galaxy->getURL() . $jeha_id['download_url'] .'/?key=' . $this->galaxy->getAPIKey();;
    return $this->rest->GET($URL);
  }
  


  /**
   * PUT /api/histories/{id}/exports:
   *
   * start job (if needed) to create history export for corresponding history.
   * 
   * @param  history_id:     the encoded id of the history to export
   *
   * @return string/json url of where to download the export
   *
   */
   public function archive_export($history_id){
     $URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/exports/?key=' . $this->galaxy->getAPIKey();
     $input = array('id' => $history_id);
     $output = $this->rest->PUT($URL, $input);
  

     return $output;
   }

   /**
    * DELETE /api/histories/id
    *
    * deletes the history with the given id
    *
    * @param $history_id
    *
    * @return curl
    */
   public function deleteHistory($history_id){
     $URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->Delete($URL);
   }
   
   /**
    *	POST /api/histories/deleted/{id}/undelete:
        undelete history (that hasn't been purged) with the given ``id`
    *   @param str $history_id
    */
   public function undelete($history_id){
   	$URL = $this->galaxy->getURL() . '/api/histories/deleted/'. $history_id . '/undelete/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->POST($URL);
   }

   

   /**
    * GET /api/histories/{encoded history_id}/citations 
    * 
    * @param str $hist_id
    */
   public function citations($hist_id){
   	$URL = $this->galaxy->getURL() . '/api/histories/'. $hist_id . '/citations/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }
   
   /**
    * GET /api/histories/published:
            return all histories that are published
    */
   public function published(){
   	$URL = $this->galaxy->getURL() . '/api/histories/published/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }
   
   /**
      GET /api/histories/shared_with_me:
          return all histories that are shared with the current 
          user
    */
   public function shared_with_me(){
   	$URL = $this->galaxy->getURL() . '/api/histories/shared_with_me/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }
   
   

}

 ?>