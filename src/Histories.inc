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

class GalaxyHistories  {

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
   *
   */
   public function __construct($galaxy) {
     $this->galaxy = $galaxy;
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
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - name: The new history's name
   *   - history_id: The id of the history to copy (will copy contents to new
   *       history). To obtain history_id's, please use this classes' index()
   *       function.
   *   - archive_source: The url that will generate the archive to import.
   *   - archive_type: 'url' (default).
   *   - bool all_datasets: Copy deleted hdas/hdcas 'True' or 'False',
   *     defaults to True.
   *
   * @return
   *    An array containing information about the new History component.
   */
   public function create($params){

     $URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();

     if(array_key_exists('name', $params)){

       $response = $this->galaxy->httpPOST($URL, $params);
       return $this->galaxy->expectArray($response);

//        $inputs = array(
//          'name' => $params['name']
//        );

//        (array_key_exists('archive_source', $params)) ? $input['tool_version'] = $params['archive_source'] : 0;
//        (array_key_exists('archive_type', $params)) ? $input['archive_type'] = $params['archive_type'] : 0;
//        (array_key_exists('history_id', $params)) ? $input['history_id'] = $params['history_id'] : 0;
//        (array_key_exists('all_datasets', $params)) ? $input['all_datasets'] = $params['all_datasets'] : $input['all_datasets'] = TRUE;
     }

     else{
       $this->galaxy->setError("API", "A 'name' for the history is required in order to invoke this call");
       return FALSE;
     }
   }

  /**
   *  Displays a collection of history components in Galaxy.
   *
   *  GET /api/histories and  GET /api/histories/deleted
   *
   *  This function combines the list of active and deleted histories and
   *  therefore, corresponds to both of the Galaxy API methods and paths:
   *
   *  @param $params
   *    An associative array of parameters that can contain the following elements
   *
   *      - deleted: If set true this will show deleted histories only.
   *
   * @return
   *    An array containing list of histories in galaxy instance.
   *
   *
   */
   public function index($params = array()){

     // Get the deleted histories.
     if(array_key_exists('deleted', $params) and $params['deleted'] == TRUE){
       $URL = $this->galaxy->getURL() . '/api/histories/deleted/?key=' . $this->galaxy->getAPIKey();
       $response = $this->galaxy->httpGET($URL);
     }

     // Get the active histories.
     else{
       $URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();
       $response = $this->galaxy->httpGET($URL);

     }

     return $response;
   }

  /**
   *  Retreive detailed information about a particular history component.
   *
   *  Corresponds to the Galaxy API method and path:
   *  POST /api/histories/{encoded_history_id}:
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - history_id: The id of the history to retreive.
   *       To obtain history_id's, please use this classes' index() function.
   *
   * @return
   *    Json array containing information about the specified history
   *
   */
   public function show($params){
     if(array_key_exists('history_id', $params)){

       $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/?key=' . $this->galaxy->getAPIKey();
     }

     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
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
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - history_id: The id of the history to download
   *       To obtain history_id's, use this classes' index() function.
   *   - file_path: The full path (including the file name) on the file system
   *       where the file should be written. Ideally, the file name should
   *       have a .tar.gz extension as the downloaded file will be
   *       gzip compressed.
   *
   * @return
   *    TRUE if the download was successful and FALSE otherwise.
   *
   */
   public function archiveDownload($params) {

    // Obtain download URL, with the necessary jeha_id
    if(array_key_exists('history_id', $params))
      $download_url = $this->archiveExport($params);
    else{
      $this->galaxy->setError("API", "This function requires a history to download, please provide a 'history_id'");
      return FALSE;
    }
    $URL = $this->galaxy->getURL() . '/' . $download_url['download_url'] . '?key=' . $this->galaxy->getAPIKey();
    if(array_key_exists('file_path', $params)){
      $file_contents = $this->galaxy->getRemoteFile($URL, $params['file_path']);
      return $file_contents;
    }
    else{
      $this->galaxy->setError("API", "This function requires a location to download history, please provide a 'file_path'");
      return FALSE;
    }
  }

  /**
   * Start Job to create history export for corresponding history.
   *
   * Corresponds to the Galaxy API method and path:
   *  PUT /api/histories/{id}/exports:
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - history_id: The encoded id of the history to export.
   *
   * @return
   *   A URL of where to download the export.
   *
   *
   */
   public function archiveExport($params){

     if(array_key_exists('history_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/exports/?key=' . $this->galaxy->getAPIKey();
       $input = array('id' => $params['history_id']);
       return $this->galaxy->httpPUT($URL, $input);
     }
     else{
       $this->galaxy->setError("API", "A 'history_id' is required in order to export");
       return FALSE;
     }

   }

  /**
   * Delete a specified history.
   *
   * Corresponds to the Galaxy API method and path:
   *  DELETE /api/histories/{encoded_history_id}
   *
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *  - history_id: The encoded id of the history to delete. To obtain
   *      history_id's, please use this classes' index() function.
   *
   * @return
   *   An array of deleted histories.
   *
   *
   */
   public function deleteHistory($params){
     if(array_key_exists('history_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/histories/'. $params['history_id'] . '/?key=' . $this->galaxy->getAPIKey();
       $response =  $this->galaxy->httpDELETE($URL);
       return $this->galaxy->expectArray($response);
     }
     else{
       $this->galaxy->setError("API", "A 'history_id' is required in order to delete the history");
       return FALSE;
     }

   }

  /**
   * Undelete a specified history.
   *
   * Corresponds to the Galaxy API method and path:
   *   POST /api/histories/deleted/{encoded_history_id}
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - history_id: The encoded id of the history to undelete.
   *       To obtain history_id's, please use this classes' index() function.
   *
   * @return
   *   An array of undeleted histories.
   *
   *
   */
   public function undelete($params){
     if(array_key_exists('history_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/histories/deleted/'. $params['history_id'] . '/undelete?key=' . $this->galaxy->getAPIKey();
       $response = $this->galaxy->httpPOST($URL);
       return $this->galaxy->expectArray($response);
     }
     else{
       $this->galaxy->setError("API", "A 'history_id' is required in order to UNdelete the history");
       return FALSE;
     }
   }

  /**
   * Retreive information of the citations of a specified history.
   *
   * Corresponds to the Galaxy API method and path:
   *   GET /api/histories/{encoded_history_id}/citations
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - history_id: The encoded id of the history to undelete.
   *       To obtain history_id's, please use this classes' index() function.
   *
   * @return
   *   An array of citations.
   *
   *
   */
   public function citations($params){
     if(array_key_exists('history_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/histories/'. $params['history_id'] . '/citations?key=' . $this->galaxy->getAPIKey();
       $response = $this->galaxy->httpGET($URL);
       return $this->galaxy->expectArray($response);
     }
     else{
       $this->galaxy->setError("API", "A 'history_id' is required in order to see the citations of the history");
       return FALSE;
     }

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
   *
   */
   public function published(){
     $URL = $this->galaxy->getURL() . '/api/histories/published/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
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
  *
  */
  public function sharedWithMe(){
    $URL = $this->galaxy->getURL() . '/api/histories/shared_with_me/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }
}
