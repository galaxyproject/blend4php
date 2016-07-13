<?php

require_once('GalaxyAPIService.inc');


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

class GalaxyHistories  extends GalaxyAPIService {

  /**
   *  Create a new History component in Galaxy.
   *
   *  Corresponds to an HTTP POST on the Galaxy API path 
   *    /api/histories
   *
   *  Creates a new history in a galaxy instance
   *    Note the option to pass 'keys' and 'views' are currently not supported
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - name: The new history's name
   *   - history_id: (Optional) The ID of the history to copy (will copy contents to new
   *       history). To obtain history_id's, please use this classes' index()
   *       function.
   *   - archive_source: (Optional) The url that will generate the archive to import.
   *   - archive_type: (Optional) 'url' (default).
   *   - all_datasets: (Optional) Copy deleted hdas/hdcas 'TRUE' or 'FALSE'
   *     defaults to TRUE.
   *
   * @return
   *    An array containing information about the new History component.
   */
  public function create($params){
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('name'))) {
      return FALSE;
    }

    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('name', 'history_id', 'archive_source', 'archive_type', 'all_datasets'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/histories/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  /**
   *  Displays a collection of history components in Galaxy.
   *
   *  Corresponds to an HTTP GET on the Galaxy API paths
   *    GET /api/histories 
   *    GET /api/histories/deleted
   *
   *  This function can present the list of active and deleted histories.
   *
   *  @param $params
   *    An associative array containing the input parameters for this function.
   *    The following parameters are available:
   *
   *      - deleted: If set true this will show deleted histories only.
   *
   * @return
   *    An array containing list of histories in galaxy instance.
   */
  public function index($params = array()) {
     
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('deleted'))) {
      return FALSE;
    }

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

    return $this->galaxy->expectArray($response);
  }

  /**
   *  Retreive detailed information about a particular history component.
   *
   *  Corresponds to an HTTP POST on the Galaxy API path
   *    /api/histories/{encoded_history_id}:
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - history_id: The ID of the history to retreive.
   *       To obtain history_ids, use Histories::index() function.
   *
   * @return
   *    An array containing information about the specified history
   */
  public function show($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/?key=' . $this->galaxy->getAPIKey();
    
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Download a given history with indicated history id.
   *
   * Corresponds to an HTTP PUT on the Galaxy API path
   *   PUT /api/histories/{id}/exports'
   *     and
   *   GET /api/histories/{id}/exports/{jeha_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - history_id: The ID of the history to download
   *       To obtain history_ids, use Histories::index() function.
   *   - file_path: The full path (including the file name) on the file system
   *       where the file should be written. Ideally, the file name should
   *       have a .tar.gz extension as the downloaded file will be
   *       gzip compressed.
   *
   * @return
   *    TRUE if the download was successful and FALSE otherwise.
   */
  public function archiveDownload($params) {
     
     // Check for required fields.
     if (!$this->checkRequiredParams($params, array('history_id', 'file_path'))) {
       return FALSE;
     }

     // Check for allowed fields.
     if (!$this->checkAllowedParams($params, array('history_id', 'file_path'))) {
       return FALSE;
     }
     
    // Obtain download URL, with the necessary jeha_id
    $download_url = $this->archiveExport($params);
    
    // Generate the URL and download
    $URL = $this->galaxy->getURL() . '/' . $download_url['download_url'] . '?key=' . $this->galaxy->getAPIKey();
    $file_contents = $this->galaxy->getRemoteFile($URL, $params['file_path']);
    return $file_contents;
  }

  /**
   * Start Job to create history export for corresponding history.
   *
   * Corresponds to an HTTP PUT on the Galaxy API path
   *   /api/histories/{id}/exports:
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - history_id: The encoded ID of the history to export.
   *
   * @return
   *   A URL of where to download the export.
   */
  public function archiveExport($params) {
    
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/exports/?key=' . $this->galaxy->getAPIKey();
    $input = array('id' => $params['history_id']);
    return $this->galaxy->httpPUT($URL, $input);
  }

  /**
   * Delete a specified history.
   *
   *  Corresponds to an HTTP DELETE on the Galaxy API path
   *    /api/histories/{encoded_history_id}
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - history_id: The encoded ID of the history to delete. To obtain
   *      history_id, use Histories::index().
   *
   * @return
   *   An array of deleted histories.
   */
  public function deleteHistory($params) {
     
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id'))) {
      return FALSE;
    }
     
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id'))) {
      return FALSE;
    }
     
    $URL = $this->galaxy->getURL() . '/api/histories/'. $params['history_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response =  $this->galaxy->httpDELETE($URL);
    return $this->galaxy->expectArray($response);

  }

  /**
   * Undelete a specified history.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/histories/deleted/{encoded_history_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - history_id: The encoded ID of the history to undelete.
   *       To obtain history_ids, use Histories::index() function.
   *
   * @return
   *   An array of undeleted histories.
   */
  public function undelete($params) {
     
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id'))) {
      return FALSE;
    }
     
    $URL = $this->galaxy->getURL() . '/api/histories/deleted/'. $params['history_id'] . '/undelete?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpPOST($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive information of the citations of a specified history.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/histories/{encoded_history_id}/citations
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - history_id: The encoded ID of the history to undelete.
   *       To obtain history_ids, use Histories::index() function.
   *
   * @return
   *   An array of citations.
   */
  public function citations($params) {
     
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id'))) {
      return FALSE;
    }
     
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id'))) {
      return FALSE;
    }
     
    $URL = $this->galaxy->getURL() . '/api/histories/'. $params['history_id'] . '/citations?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive all histories that have been published.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/histories/published:
   *
   * @return
   *   An array of published histories.
   */
  public function published() {
     
    $URL = $this->galaxy->getURL() . '/api/histories/published/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive all histories that are shared with the current user.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/histories/shared_with_me:
   *
   * @return
   *   An array histories shared with the current user.
   */
  public function sharedWithMe() {
    
    $URL = $this->galaxy->getURL() . '/api/histories/shared_with_me/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }
  
  
  /**
   * Retreive the current history found in the right pane of the galaxy server
   *   gui.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /history/current_history_json:
   *
   * @return
   *   An array of the current history of the current user.
   */
  public function getCurrentHistory() {
    $URL = $this->galaxy->getURL() . '/history/current_history_json?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }
  
}
