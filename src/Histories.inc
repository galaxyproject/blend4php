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



   /**TODO: Test this
    * Creates a new  history in a galaxy instance
    * returns rest restuls
    * calls upon
    * POST /api/histories:
    *
    *
    * @param string name: the new history’s name
    * @param string history_id: the id of the history to copy
    * @param bool all_datasets: copy deleted hdas/hdcas?  ‘True’ or ‘False’, defaults to True
    * @param string archive_source: the url that will generate the archive to import
      @param string archive_type: ‘url’ (default)

      @param string keys – same as the use of keys in the index function above
      @param string view – same as the use of view in the index function above
      
      @return string/Json from server response 

    *
    */
   public function create($name, $archive_source=NULL,  $archive_type=NULL,
   		$all_datasets= True, $history_id = NULL) {
     $URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();

     $inputs = array(
       'name' => $name,
       'tool_version' => $archive_source,
       'archive_type' => $archive_type,
       'history_id'=>$history_id,
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
   

   /** What is a immutable id??
    *
    * GET /api/histories/{id}/exports/{jeha_id}:

      If ready and available, return raw contents of
      exported history.
      Use/poll “PUT /api/histories/{id}/exports” to initiate the

      
      @param string history_id
      @param string jeha_id 
      
      @return string/Json from the server response
    *
    */
   public function archive_download($history_id, $jeha_id){
    $initialURL = '/api/histories/' . $history_id . '/exports/?key=' . $this->galaxy->getAPIKey();
   	$this->rest->PUT($URL);
    $URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/exports/' . $jeha_id .'/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->GET($URL);
  }

  /**
   * PUT /api/histories/{id}/exports:
   *
   * start job (if needed) to create history export for corresponding history.
   * @param  id:     the encoded id of the history to export
   *
   * @return url of download site
   *
   */
   public function archive_export($history_id){
     $URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/exports/?key=' . $this->galaxy->getAPIKey();
     $input = array('id' => $history_id);
     $output = $this->rest->PUT($URL, $input);
  

     return $output;
   }

   /**
    *	DELETE /api/histories/id
    *
    *	deletes the history with the given id
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
    * @param str $history_id
    */
   public function undelete($history_id){
   	$URL = $this->galaxy->getURL() . '/api/histories/deleted/'. $history_id . '/undelete/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->POST($URL);
   }

   
   //TODO: The parameters this web service requires are the same
   // for func:`galaxy.model.History.to_dict
   // public function update($history_id)
   
   

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