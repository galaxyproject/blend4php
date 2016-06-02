<?php

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

/**
 * @defgroup history_contents_class HistoryContents class
 * @{
 *   The Histories Class interacts with Galaxy to manage history data.
 *   The functions in this class correspond to the Galaxy API functions and
 *   are named similarly to their Python counterpart.
 * @}
 */

class GalaxyHistoryContents {

  private $galaxy;
 /**
   * The HistoryContents constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a HistoryContents object.
   *
   *
   */
  public function __construct($galaxy) {
    parent::__construct();
  }

  /**
   * Create a new HistoryContents component to a given history
   *
   * Corresponds to the Galaxy API method at:
   *  POST /api/histories/{history_id}/contents/{type}
   *  Types will be "datasets" by default. The other option "dataset_collection"
   *  is currently not supported.
   *
   * @param $params
   *   A dictionary (associative array) containing the input parameters that
   *   are required to run this function.
   *
   *   - history_id: The id of the history to add contents to. To obtain
   *       history id's, please refer to the index() function of the history
   *       class.
   *   - source: Can be any one of the following source types:
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
   *   - type(Optional): Type of history content, defaults to 'dataset', alternative is
   *       'dataset_collection'
   *
   *   - content: The id of the content associated to the selected source to
   *       add to the history. To obtian content (id's) please refer to this
   *       class's index() function.
   *
   * @return
   *   An array containing information about the new History content component.
   *
   *
   */
  public function create($params) {
    if(array_key_exists('source', $params)){
      if(array_key_exists('history_id', $params)){
        $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents/datasets/?key=' . $this->galaxy->getAPIKey();
        $response = $this->galaxy->httpPOST($URL, $params);
        return $this->expectArray($response);
      }
      $this->setError("API", "This API call needs a 'history_id' to create a history content");
      return FALSE;
    }

    $this->setError("API", "This API call needs a 'source' to create a history content");
    return FALSE;
  }

  /**
   * Retrieve detailed information about a specific hda.
   *
   * Corresponds to the Galaxy API method and path:
   *   GET /api/histories/{history_id}/contents/{id}
   *
   *
   * @param $params
   *   A dictionary (associative array) containing the input parameters that
   *   are required to run this function.
   *
   *   - id: The encoded history content id of the HDA to return please
   *       use the index() function for a list of content_id's.
   *   - history_id: The id of the history to update. To find, please refer to
   *     'Histories' class index() funciton.
   *
   * @return
   *   An array containing detailed HDA (history dataset association) information.
   *
   *
   */
  public function show($params) {
    if(array_key_exists('history_id', $params)){
      if(array_key_exists('id', $params)){
        $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents/' . $params['id'] .'/?key=' . $this->galaxy->getAPIKey();
        $response = $this->galaxy->httpGET($URL);
        return $this->expectArray($response);
      }
      $this->setError("API", "This API call needs an 'id' to be present the correct history content");
      return FALSE;
    }
    $this->setError("API", "This API call needs a 'history_id' to acquire a history");
    return FALSE;
  }

  /**
   * Updates the values for the History content with the given id.
   *
   * Corresponds to the Galaxy API method and path:
   *   PUT /api/histories/{history_id}/contents/{id}
   *
   *  Some functionality from original python function is not available.
   *
   * @param $params
   *   A dictionary (associative array) containing the input parameters that
   *   are required to run this function.
   *
   *   - history_id: The id of the history to update. To find, please refer to
   *     'Histories' class index() function.
   *   - id: The id of the content to update the selected hda in the
   *       history, this can be a dataset. To find dataset id's go to:
   *       ./api/histories/<history_id>/content, only 'ok' state datasets work
   *   - annotation: The new annotation for the hda.
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
   * @return
   *   An array containing detailed HDA (history dataset association)
   *   information.
   *
   *
   */
  public function update($params) {
    if (array_key_exists('history_id', $params)){
      if(array_key_exists('id', $params)){
        $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents/' . $params['id'] . '/?key=' . $this->galaxy->getAPIKey();

        unset($params['history_id']);
        unset($params['id']);

        $response = $this->galaxy->httpPUT($URL, $params);
        return $this->expectArray($response);
      }
      $this->setError("API", "HistoryContents update requires an 'id' parameter to update the appropriate hda");
      return FALSE;
    }
    $this->setError("API", "HistoryContents update requires a 'history_id' parameter to update the appropriate hda");
    return FALSE;

  }


  /**
   * Delete the History content with the given id.
   *
   * Corresponds to the galaxy API path at:
   *   DELETE /api/histories/{history_id}/contents/{id}
   *
   *
   * @param $params
   *   A dictionary (associative array) containing the input parameters that
   *   are required to run this function.
   *
   *   - history_id: The id of the history content to delete.
   *   - id: The id of the content to delete from the history, to find
   *       the (dataset) id's go to:
   *       /api/histories/<history_id>/content, only 'ok' state datasets work
   *       Or use this classe's index() function.
   *   - purge: A value of TRUE will remove this history content from the
   *       deleted page as well.
   *
   * @return
   *   An array containing detailed HDA (history dataset association)
   *   information.
   *
   *
   */
  public function delete($params) {
    if (array_key_exists('history_id', $params)){
      if(array_key_exists('id', $params)){
        $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents/' . $params['id'] . '/?key=' . $this->galaxy->getAPIKey();

        if(array_key_exists('purge', $params) and $params['purge'] == TRUE)
          $URL .= '&purge=true';

        $response =  $this->galaxy->httpDELETE($URL);
        return $this->expectArray($response);
      }
      $this->setError("API", "HistoryContents delete requires an 'id' parameter to delete the appropriate hda");
      return FALSE;
    }
    $this->setError("API", "HistoryContents delete requires a 'history_id' parameter to delete the appropriate hda");
    return FALSE;
  }

  /**
   * Displays a collection of history content components.
   *
   * Corresponds to th Galaxy API path at:
   *   GET /api/histories/{history_id}/contents
   *
   * @param $params
   *   A dictionary (associative array) containing the input parameters that
   *   are required to run this function.
   *
   *   - history_id: The id of the history in order to view the contents.
   *   - ids: A comma separated string of encoded history content ids to narrow
   *       The return JSON. If this does not exits then all contents of the
   *       history will be returned.
   *
   * @return
   *   An array containing a summary or detailed HDA(history dataset
   *   association) of all the history contents.
   *
   *
   */
  public function index($params) {
    if(array_key_exists('history_id', $params)){
      $URL = $this->galaxy->getURL() . '/api/histories/' . $params['history_id'] . '/contents' . '/?key=' . $this->galaxy->getAPIKey();
      if(array_key_exists('ids', $params)){
        $URL .= '/&ids=' . json_encode($params['ids']);
      }
      $response = $this->galaxy->httpGET($URL);
      return $this->expectArray($response);
    }
    $this->setError("API", "HistoryContents index requires a 'history_id' parameter to view the contents of the history");
    return FALSE;

  }
}
