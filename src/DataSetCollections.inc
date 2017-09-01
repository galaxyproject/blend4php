<?php

require_once('GalaxyAPIService.inc');


class GalaxyDatasetCollections extends GalaxyAPIService{

  // POST /api/datasetcollections
  public function create($params){
    // Required params
    if(!$this->checkRequiredParams($params, array('collection_type', 'element_identifiers', 'history_id'))){
      return FALSE;
    }
    // XXX: element_identifiers is also an array and CAN BE recursive, check this
    // Allowed params
    if(!$this->checkAllowedParams($params, array('name', 'collection_type', 'element_identifiers', 'history_id'))){
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . 'api/dataset_collections' . '/?key=' . $this->galaxy->getAPIKey();
    json_encode($params);
    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);

  }

  public function show($params){

  }
}
