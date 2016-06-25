<?php

require_once('GalaxyAPIService.inc');

/**
 * @file
 *
 * Implements the FolderContents class.
 *
 * The FolderContents Class interacts with Galaxy to manage contents of a folder.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

class GalaxyFolderContents extends GalaxyAPIService {

  /**
   * Displays all the contents of a folder.
   *
   * Corresponds to the Galaxy API/path:
   *  GET /api/folders/F{folder_id}/contents.
   *
   * @param $params
   *  An associative array containing the input parameters for this function.
   *  The following parameters are available:
   *
   *  - folder_id: Id of the folder's contents to display. To obtain an id
   *     see the index() function in the Folder class.
   *
   * @return
   *  An array of The specified folder's contents
   *
   *
   */
  public function index($params) {
    if(!array_key_exists('folder_id', $params)){
      $this->galaxy->setError("API", "A 'folder_id' is required in order to invoke this call");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/folders/'  . $params['folder_id'] . '/contents' . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Create a new dataset inside of a folder.
   *
   * Corresponds to an HTTP POST to the Galaxy API path
   *  /api/folders/{folder_id}/contents
   *
   * @param $params
   *  An associative array containing the input parameters for this function.
   *  The following parameters are available:
   *
   *  - folder_id: The ID of the folder into which the dataset should be added.
   *  - from_hda_id (Optional): The id of an accessible HDA to into the
   *     library. To obtain this id, see index() in HistoryContents class.
   *  - ldda_messge (Optional): Any message to send along with the
   *     LibraryDatasetAssociation.
   *  - extented_metadata (Optional): associative array containing any extended
   *     metadata to associate with the item.
   *
   * @return
   *  An array containing the newly created folder content.
   *
   *
   */
  public function create($params){
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('folder_id'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('folder_id', 'from_hda_id',
         'ldda_messge', 'extented_metadata'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/folders/' . $params['folder_id'] . '/contents/?key=' . $this->galaxy->getAPIKey();
    unset($params['folder_id']);

    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  /**
  * Retreive details of for a specified folder.
  *
  * Corresponds to the Galaxy API/path:
  *  GET /api/folders/{folder_id}/
  *
  * @param $params
  *  An associative array containing the input parameters for this function.
  *  The following parameters are available:
  *
  * @return
  *  False.
  *
  *
  */
  public function show($params){
   //Not implemented in the python counterpart
    return FALSE;
  }

  /**
   * Update the contents to a specific folder
   *
   * Corresponds to the Galaxy API/PATH
   *  PUT /api/folders/{folder_id}/
   *
   * @return
   *  False.
   *
   *
   */
  public function update($params){
   //Not implemented by the python counterpart.
   return FALSE;
  }
}
