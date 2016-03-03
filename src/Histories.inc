<?php

/**
 * @file
 *
 * Implements the Histories class.
 *
 * The Histories Class interacts with Galaxy to manage history information.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

/**
 * @defgroup histories_class Histories class
 * @{
 *   The Histories Class interacts with Galaxy to manage history data.
 *   The functions in this class correspond to the Galaxy API functions and
 *   are named similarly to their Python counterpart.
 * @}
 */
require_once 'HTTPRequest.inc';

class Histories extends HTTPRequest {

  private $galaxy;
	/**
	 * The Histories constructor.
	 *
	 * @param GalaxyInstance $galaxy
	 *   A GalaxyInstance object.
	 *
	 * @return
	 *   An instance of a Histories object.
	 *
	 * @ingroup histories_class
	 */
   public function __construct($galaxy) {
     $this->galaxy = galaxy;
     parent::__construct();
   }

   /**
    *  Create a new History component in Galaxy.
    *
    *  Corresponds to the Galaxy API method and path:
    *    POST /api/histories:
    *
    *  Creates a new  history in a galaxy instance
    *    Note the option to pass 'keys' and 'views' is currently not supported
    *
    * @param name
    *   the new history’s name
    * @param history_id
    *   The id of the history to copy (will copy contents to new history)
    *   To obtain history_id's, please use this classes' index() function.
    * @param bool all_datasets
    *   Copy deleted hdas/hdcas?  ‘True’ or ‘False’, defaults to True.
    * @param archive_source
    *   The url that will generate the archive to import.
    * @param archive_type
    *   ‘url’ (default)
    *
    * @return
    *    Json array containing information about the new History component.
    *
    * @ingroup histories_class
    */
   public function create($name, $history_id = NULL, $annotation = NULL, $archive_source = NULL,  $archive_type = NULL,
   $all_datasets = TRUE) {
     $URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();

     $inputs = array(
       'name' => $name,
       'annotation' => $annotation,
       'tool_version' => $archive_source,
       'archive_type' => $archive_type,
       'history_id' => $history_id,
       'all_datasets' => $all_datasets
     );

     //Assure we are not inputting null values into the python dictionary
     $notNullInputs = array();
     foreach ($inputs as $inputName => $input){
      if($input !== NULL){
       $notNullInputs[$inputName] = $input;
      }
     }

     return $this->rest->POST($URL, $notNullInputs);
   }

   /**
    *  Displays a collection of history components in Galaxy.
    *
    *  Corresponds to the Galaxy API method and path:
    *  GET /api/histories and  GET /api/histories/deleted
    *
    * @return
    *    Json array containing list of histories in galaxy instance.
    *
    * @ingroup histories_class
    */
   public function index(){
     $URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();
     $URLDeleted = $this->galaxy->getURL() . '/api/histories/deleted/?key=' . $this->galaxy->getAPIKey();
     $result = $this->rest->GET($URL) . $this->rest->GET($URLDeleted);
     $result = json_encode($result);
     return  $result;
   }

   /**
    *  Retreive detailed information about a particular history component.
    *
    *  Corresponds to the Galaxy API method and path:
    *  POST /api/histories/{encoded_history_id}:
    *
    * @param history_id
    *   The id of the history to retreive.
    *   To obtain history_id's, please use this classes' index() function.
    *
    * @return
    *    Json array containing information about the specified history
    *
    * @ingroup histories_class
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
    * Download a given history with indicated history id.
    *
    * Corresponds to the Galaxy API method and path::
    *  PUT /api/histories/{id}/exports”
    *  and:
    *  GET /api/histories/{id}/exports/{jeha_id}
    *
    * @param history_id
    *   The id of the history to download
    *   To obtain history_id's, please use this classes' index() function.
    * @return
    *    Binary format of the history specified, error message if error.
    *
    * @ingroup histories_class
    */
   public function archive_download($history_id){
    $error_message = "Error, unrecognized server response.";
    // Obtain download URL, with the necessary jeha_id
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
   * Start Job to create history export for corresponding history.
   *
   * Corresponds to the Galaxy API method and path:
   *  PUT /api/histories/{id}/exports:
   *
   * @param history_id:
   *   the encoded id of the history to export.
   *
   * @return
   *   Json url of where to download the export.
   *
   * @ingroup histories_class
   */
   public function archive_export($history_id){
     $URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/exports/?key=' . $this->galaxy->getAPIKey();
     $input = array('id' => $history_id);
     $output = $this->rest->PUT($URL, $input);


     return $output;
   }

   /**
    * Delete a specified history.
    *
    * Corresponds to the Galaxy API method and path:
    *  DELETE /api/histories/{encoded_history_id}
    *
    * @param  history_id:
    *   The encoded id of the history to delete.
    *   To obtain history_id's, please use this classes' index() function.
    *
    * @return
    *   Json information of history deleted.
    *
    * @ingroup histories_class
    */
   public function deleteHistory($history_id){
     $URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->DELETE($URL);
   }

   /**
    * Undelete a specified history.
    *
    * Corresponds to the Galaxy API method and path:
    *   DELETE /api/histories/deleted/{encoded_history_id}
    *
    * @param  history_id:
    *   The encoded id of the history to undelete.
    *   To obtain history_id's, please use this classes' index() function.
    *
    * @return
    *   Json information of history undeleted.
    *
    * @ingroup histories_class
    */
   public function undelete($history_id){
   	$URL = $this->galaxy->getURL() . '/api/histories/deleted/'. $history_id . '/undelete/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->POST($URL);
   }

   /**
    * Retreive information of the citations of a specified history.
    *
    * Corresponds to the Galaxy API method and path:
    *   GET /api/histories/{encoded_history_id}/citations
    *
    * @param  history_id:
    *   The encoded id of the history to undelete.
    *   To obtain history_id's, please use this classes' index() function.
    *
    * @return
    *   Json information of history undeleted.
    *
    * @ingroup histories_class
    */
   public function citations($hist_id){
   	$URL = $this->galaxy->getURL() . '/api/histories/'. $hist_id . '/citations/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }

   /**
    * Retreive all histories that have been published.
    *
    * Corresponds to the Galaxy API method and path:
    *   GET /api/histories/published:
    *
    * @return
    *   Json information of published histories.
    *
    * @ingroup histories_class
    */
   public function published(){
   	$URL = $this->galaxy->getURL() . '/api/histories/published/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }

   /**
    * Retreive all histories that are shared with the current user.
    *
    * Corresponds to the Galaxy API method and path:
    *   GET /api/histories/shared_with_me:
    *
    * @return
    *   Json information of histories shared with the user.
    *
    * @ingroup histories_class
    */
   public function shared_with_me(){
   	$URL = $this->galaxy->getURL() . '/api/histories/shared_with_me/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }


}

 ?>