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
require_once 'GalaxyRequest.inc';


class HistoryContents extends GalaxyRequest {
	
 /**
   * The HistoryContents constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a HistoryContents object.
   *
   * @ingroup history_content_class
   */	
  public function __construct($galaxy) {
    parent::__construct($galaxy);
  }

  /**
   * Create a new HistoryContents component to a given history
   * 
   * Corresponds to the Galaxy API method at: 
   *  POST /api/histories/{history_id}/contents/datasets
   *
   * create a new History Dataset Association by copying an
   *  accessible LibraryDataset or History Dataset Association, and assigning it to the given history_id
   *  NOTE, currently, only creating new 'datasets' is supported,
   *  as opposed to creating dataset Collections
   *
   * @param history_id
   *   history id of the history to update. To find, please refer to 
   *   'Histories' class. 
   * @param source 
   *   The source of the new dataset, either hda or library
   * @param content_id 
   *   the content to add (dataset id's work)
   *   to find dataset id's go to:
   *   /api/histories/<history_id>/content only 'ok' state datasets work 
   *   Or refer to the Datasets class 
   * 
   * @return 
   * Json array containing information about the new History content component.
   *
   * @ingroup history_content_class
   */
  public function create($history_id, $content_id, $source = 'hda') {
    $URL = $this->galaxy->getURL() .'/api/histories/' . $history_id .'/contents/dataset/?key=' . $this->galaxy->getAPIKey();
    $elements = array('source' => $source,'content' => $content_id,'collection_type' => $collection_type,'element_identifiers' => $element_identifiers,'collection_type' => $collection_type);
    $notNullInputs = array();
    foreach ($elements as $element => $value) {
      if ($value !=NULL) {
        $notNullInputs[$element] = $value;
      }
    }
    return $this->rest->POST($URL, $notNullInputs);
  }

  /**
   * Retrieve detailed information about a specific historycontent. 
   * 
   * Corresponds to the Galaxy API method and path: 
   *   GET /api/histories/{history_id}/contents/{id}
   *
   * @param content_id 
   *   the encoded history content id of the HDA to return (History data association)
   *   please use the index() function for a list of content_id's. 
   * @param $history_id
   *   history id of the history to update. To find, please refer to 
   *   'Histories' class. 
   *   
   * @return 
   *   Json array containing detailed HDA (history dataset association) information.
   *   
   * @ingroup history_content_class
   */
  public function show($history_id, $content_id) {
    $URL = $this->galaxy->getURL() .'/api/histories/' .$history_id .'/contents/' .$content_id .'/?key=' .$this->galaxy->getAPIKey();
    return $this->rest->GET($URL);
  }

  /**
   * Updates the values for the History content with the given id.
   * 
   * Corresponds to the Galaxy API method and path:
   *   PUT /api/histories/{history_id}/contents/{id}
   * 
   *  Some functionality from original python function is not available.
   *
   * @param history_id
   *   history id of the history to update. To find, please refer to 
   *   'Histories' class. 
   * @param content_id
   *   content id of the content to update the history with, can be a dataset
   *   to find dataset id's go to:
   *   /api/histories/<history_id>/content, only 'ok' state datasets work
   * @param $annotation
   *   annotation for the hda
   *   
   * @return 
   *   Json array containing detailed HDA (history dataset association) information.
   *   
   * @ingroup history_content_class  
   */
  public function update($history_id, $content_id, $annotation = '') {
    $URL = $this->galaxy->getURL() .'/api/histories/' .$history_id .'/contents/' .$content_id .'/?key=' .$this->galaxy->getAPIKey();
    $elements = array('annotation' => $annotation);
    return $this->rest->PUT($URL, $elements);
  }

  /**
   * Delete the History content with the given id.
   *  
   * Corresponds to the galaxy API path at: 
   *   DELETE /api/histories/{history_id}/contents/{id}
   *
   *
   * @param history_id
   *   history id of the history to update. To find, please refer to 
   *  'Histories' class. 
   * @param content_id
   *   content id of the content to update the history with, can be a dataset
   *   to find dataset id's go to:
   *   /api/histories/<history_id>/content, only 'ok' state datasets work
   *   Or use this classe's index() function.
   * @param purge
   *   A value of TRUE will remove this history content from the deleted
   *   page as well.
   *   
   * @return 
   *   Json array containing detailed HDA (history dataset association) information.
   *   
   * @ingroup history_content_class    
   */
  public function delete($history_id, $content_id, $purge = false) {
    $URL = $this->galaxy->getURL() .'/api/histories/' .$history_id .'/contents/' .$content_id .'/?key=' .$this->galaxy->getAPIKey();
    if ($purge) {
      $URL .= '&purge=true';
    }
    return $this->rest->delete($URL);
  }

  /**
   * Displays a collection of history content components. 
   * 
   * Corresponds to th Galaxy API path at: 
   *   GET /api/histories/{history_id}/contents
   *
   * @param history_id
   *   history id of the history to update. To find, please refer to 
   *  'Histories' class. 
   * @param ids 
   *   A comma separated string of encoded historyContent ids to narrow 
   *   The return JSON. 
   *
   * @return 
   *   JSON information containing summary or 
   *   detailed HDA(history dataset association) of all the history contents. 
   *   
   * @ingroup history_content_class    
   */
  public function index($history_id, $ids = NULL) {
    $URL = $this->galaxy->getURL() .'/api/histories/' .$history_id .'/contents';
    $URL .= '/?key=' .$this->galaxy->getAPIKey();
    if ($ids !==NULL) {
      $URL .= '/&ids=' .$ids;
    }
    return $this->rest->GET($URL);
  }
}
