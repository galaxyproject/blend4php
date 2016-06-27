<?php

require_once('GalaxyAPIService.inc');


/**
 * @file
 *
 * Implements the HistoryContents class.
 *
 * The HistoryContents Class interacts with Galaxy to manage history information.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */


class GalaxyHistoryContents extends GalaxyAPIService {

  /**
   * Create a new HistoryContents component to a given history
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/histories/{history_id}/contents/{type}
   *  
   *  Types will be "datasets" by default. The other option "dataset_collection"
   *  is currently not supported.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - history_id: The id of the history to add contents to. To obtain
   *       history id's, please refer to the index() function of the history
   *       class.
   *   - source: Can be any ONE of the following source types:
   *     (i)   library: Copy from library, would contain the id of the library dataset
   *     (ii)  library_folder: Copy from library folder, conains the id of the
   *       library folder.
   *     (iii) hda: Copy from history dataset, would contain the id of the HDA
   *     (iv)  hdca: Copy from history dataset collection, contains the HDCA.
   *     (v)   new_collection: A list that contains the following parameters:
   *            - collection_type: Can be list, paired, list:paired
   *            - name: Name of the the new dataset collection
   *            - element_identifiers: List defining collection (the actual data
   *                for this new collection).
   *   - type: (Optional) Type of history content, defaults to 'dataset', alternative is
   *       'dataset_collection'
   *   - content: (Optional) The id of the content associated to the selected source to
   *       add to the history. To obtain content IDs refer to 
   *       HistoryContents::index().
   *
   * @return
   *   An array containing information about the new History content component.
   */
  public function create($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id', 'source'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id', 'source', 'type', 'content'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents/datasets/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retrieve detailed information about a specific hda.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/histories/{history_id}/contents/{id}
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - id: The encoded history content ID of the HDA to return, use
   *       HistoryContents::index() for a list of content_ids.
   *   - history_id: The ID of the history to present. To find, refer to
   *     Histories::index().
   *
   * @return
   *   An array containing detailed HDA (history dataset association) information.
   */
  public function show($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id', 'id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id', 'id'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents/' . $params['id'] .'/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Updates the values for the History content with the given id.
   *
   * Corresponds to an HTTP PUT on the Galaxy API path
   *   /api/histories/{history_id}/contents/{id}
   *
   *  Some functionality from original python function is not available.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - history_id: The ID of the history to update. To find, refer to
   *       Histories::index().
   *   - id: The ID of the content to update (the selected hda) in the
   *       history, this can be a dataset. To find dataset IDs use
   *       HistoryContents::index(), only 'ok' state datasets work.
   *   - annotation: (Optional) The new annotation for the hda.
   *
   *    **This was in the api docs but it does not seem to work.
   *    TODO: Figure out what this payload does during the update.
   *   - payload: An associative array that contains hda fields, to update
   *       the specified hda within the history. Can contain:
   *       (i)    name: The new dataset name.
   *       (ii)   history_id: An id to a history whose contents are to be
   *                manipulated.
   *       (iii)  datset_id: A dataset to add to the provided history (giving
   *                content to the specified history.
   *       (iv)   genome_build: The new genome build (a data base key).
   *       (v)    annotation: The new genome annotation for the hda.
   *       (vi)   deleted: A boolean value if the hda is deleted or not.
   *       (vii)  visible: A boolean value if the hda is visible or not.
   *       
   * @return
   *   An array containing detailed HDA (history dataset association)
   *   information.
   */
  public function update($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id', 'id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id', 'id', 'annotation', 'payload'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents/' . $params['id'] . '/?key=' . $this->galaxy->getAPIKey();

    // Clear these params to prevent them from being put in the request.
    unset($params['history_id']);
    unset($params['id']);

    $response = $this->galaxy->httpPUT($URL, $params);
    return $this->galaxy->expectArray($response);
  }


  /**
   * Delete the History content with the given id.
   *
   * Corresponds to an HTTP DELETE on the Galaxy API path
   *   /api/histories/{history_id}/contents/{id}
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - history_id: The ID of the history to delete a history content.
   *   - id: The ID of the content to delete from the history to find
   *       the (dataset) ID(s) use HistoryContent::index(), only 'ok' state
   *       datasets work.
   *   - purge: (Optional) A value of TRUE will remove this history content from the
   *       deleted page as well.
   *
   * @return
   *   An array containing detailed HDA (history dataset association)
   *   information.
   */
  public function delete($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id', 'id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id', 'id', 'purge'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents/' . $params['id'] . '/?key=' . $this->galaxy->getAPIKey();

    if(array_key_exists('purge', $params) and $params['purge'] == TRUE)
      $URL .= '&purge=true';

    $response =  $this->galaxy->httpDELETE($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Displays a collection of history content components.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/histories/{history_id}/contents
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - history_id: The ID of the history in order to view the contents.
   *   - ids: A comma separated string of encoded history content IDs. If
   *       the specified content does not exist then all contents of the 
   *       history will be included.
   *
   * @return
   *   An array containing a summary or detailed HDA(history dataset
   *   association) of all the history contents.
   */
  public function index($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('history_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('history_id', 'ids'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents' . '/?key=' . $this->galaxy->getAPIKey();
    
    // Check if the user asks for any specific content ids
    if(array_key_exists('ids', $params)){
      $URL .= '/&ids=' . json_encode($params['ids']);
    }
    
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }
  
}
