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
     $this->galaxy = $galaxy;
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
    *   the new history's name
    * @param history_id
    *   The id of the history to copy (will copy contents to new history)
    *   To obtain history_id's, please use this classes' index() function.
    * @param bool all_datasets
    *   Copy deleted hdas/hdcas  'True' or 'False', defaults to True.
    * @param archive_source
    *   The url that will generate the archive to import.
    * @param archive_type
    *   'url' (default)
    *
    * @return
    *    An array containing information about the new History component.
    *
    * @ingroup histories_class
    */
   public function create($name, $history_id = NULL, $archive_source = NULL,
       $archive_type = NULL, $all_datasets = TRUE){

     $URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();

     $inputs = array(
       'name' => $name,
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

     $response = $this->httpPOST($URL, $notNullInputs);
     return $this->expectArray($response);
   }

   /**
    *  Displays a collection of history components in Galaxy.
    *
    *  This function combines the list of active and deleted histories and
    *  therefore, corresponds to both of the Galaxy API methods and paths:
    *
    *  GET /api/histories and  GET /api/histories/deleted
    *
    * @return
    *    An array containing list of histories in galaxy instance.
    *
    * @ingroup histories_class
    */
   public function index(){

     // Get the active histories.
     $URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();
     $active = $this->httpGET($URL);

     // Get the deleted histories.
     $URLDeleted = $this->galaxy->getURL() . '/api/histories/deleted/?key=' . $this->galaxy->getAPIKey();
     $deleted = $this->httpGET($URLDeleted);

     // If we have deleted histories then merge those with the active histories.
     // Othwerwise, just return the active histories.
     if ($deleted) {
       return array_merge($active, $deleted);
     }
     return $active;
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
     $URL = $this->galaxy->getURL() . '/api/histories/' . $history_id . '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Download a given history with indicated history id.
    *
    * Corresponds to the Galaxy API method and path:
    *
    *  PUT /api/histories/{id}/exports'
    *    and:
    *  GET /api/histories/{id}/exports/{jeha_id}
    *
    * @param $history_id
    *   The id of the history to download
    *   To obtain history_id's, please use this classes' index() function.
    * @param $file_path
    *   The full path (including the file name) on the file systems where this
    *   file should be written.  Ideally, the file name should have a .tar.gz
    *   extension as the downloaded file is tar'ed and gzip compressed.
    *
    * @return
    *    TRUE if the download was successful and FALSE otherwise.
    *
    * @ingroup histories_class
    */
   public function archiveDownload($history_id, $file_path) {

    // Obtain download URL, with the necessary jeha_id
    $download_url = $this->archiveExport($history_id);

    $URL = $this->galaxy->getURL() . '/' . $download_url['download_url'] . '?key=' . $this->galaxy->getAPIKey();
    $file_contents = $this->getRemoteFile($URL, $file_path);
    return $file_contents;
  }

  /**
   * Start Job to create history export for corresponding history.
   *
   * Corresponds to the Galaxy API method and path:
   *  PUT /api/histories/{id}/exports:
   *
   * @param $history_id:
   *   the encoded id of the history to export.
   *
   * @return
   *   A URL of where to download the export.
   *
   * @ingroup histories_class
   */
   public function archiveExport($history_id){

     $URL = $this->galaxy->getURL() . '/api/histories/' . $history_id . '/exports/?key=' . $this->galaxy->getAPIKey();
     $input = array('id' => $history_id);
     return $this->httpPUT($URL, $input);
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
    *   An array of deleted histories.
    *
    * @ingroup histories_class
    */
   public function deleteHistory($history_id){
     $URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/?key=' . $this->galaxy->getAPIKey();
     $response =  $this->httpDELETE($URL);
     return $this->expectArray($response);
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
    *   An array of undeleted histories.
    *
    * @ingroup histories_class
    */
   public function undelete($history_id){
     $URL = $this->galaxy->getURL() . '/api/histories/deleted/'. $history_id . '/undelete?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpPOST($URL);
     return $this->expectArray($response);
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
    *   An array of citations.
    *
    * @ingroup histories_class
    */
   public function citations($history_id){
     $URL = $this->galaxy->getURL() . '/api/histories/'. $history_id . '/citations?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Retreive all histories that have been published.
    *
    * Corresponds to the Galaxy API method and path:
    *   GET /api/histories/published:
    *
    * @return
    *   An array of published histories.
    *
    * @ingroup histories_class
    */
   public function published(){
     $URL = $this->galaxy->getURL() . '/api/histories/published/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

  /**
  * Retreive all histories that are shared with the current user.
  *
  * Corresponds to the Galaxy API method and path:
  *   GET /api/histories/shared_with_me:
  *
  * @return
  *   An array histories shared with the current user.
  *
  * @ingroup histories_class
  */
  public function sharedWithMe(){
    $URL = $this->galaxy->getURL() . '/api/histories/shared_with_me/?key=' . $this->galaxy->getAPIKey();
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }
}
