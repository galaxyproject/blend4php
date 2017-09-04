<?php

require_once('GalaxyAPIService.inc');


class GalaxyDatasetCollections extends GalaxyAPIService{

  /**
   * Creates a dataset collection.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/dataset_collections
   *
   * @param $params
   *    An associative array containing the input parameters for this function.
   *    The following parameters are available:
   *
   *    - collection_type:  the dataset collection type to create, can be one
   *       of 'list', 'paired' or 'list:paired'.
   *    - instance_type: can be one of 'history' or 'library'.
   *    - name: the new dataset collection name.
   *    - element_identifiers:  an array describing the datasets in the collection.
   *    - history_id: if instance_type is history then this is the history_id
   *        within which the files are found.
   *    - folder_id:  if instance_type is 'library' then this is the folder_id
   *        within which the files are found.
   *
   * @return
   *   An array containing information about the dataset collection.
   */
  public function create($params){


    // Required params
    if(!$this->checkRequiredParams($params, array('collection_type', 'instance_type', 'element_identifiers', 'name'))){
      return FALSE;
    }

    // Allowed params
    if(!$this->checkAllowedParams($params, array('name', 'collection_type', 'instance_type', 'history_id', 'folder_id', 'element_identifiers'))){
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/dataset_collections' . '/?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  public function show($params){

  }
}
