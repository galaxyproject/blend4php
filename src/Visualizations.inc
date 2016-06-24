<?php

require_once ("GalaxyAPIService.inc");

/**
 * @file
 *
 * The GalaxyVisualizations class.
 *
 * The GalaxyVisualizations class interacts with Galaxy to manage contents of a Galaxy
 * visualizaiton. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

class GalaxyVisualizations extends GalaxyAPIService {

  /**
   * Retreive a list of all visualizations.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/visualizations
   *
   * @return
   *   An array containing all of galaxy's visualizations.
   *
   *
   */
  function index(){
    $URL = $this->galaxy->getURL() . '/api/visualizations/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive detailed information about a specific visualization.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/visualizations/{viz_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - viz_id: The ID of the visualization to retrieve.
   *
   * @return
   *   An array containing information about the matching visualization.
   */
  function show($params){
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('viz_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/visualizations/'. $params['viz_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Imports copy of existing visualizatiion into the  workplace.
   *
   * Corresponds to the Galaxy API/paths at
   *  POST /api/visualizations
   *  or
   *  POST /api/visualizations?import_id={encoded_visualization_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - type: The visualization type for the new visualization.
   *   - title: The title for the visualization.
   *   - dbkey: The db key.
   *   - import_id: (optional) The id of the visualization to import, if the
   *     user desires to import a visualization.
   *
   * @return
   *   An array containing information about the created visualization.
   *
   */
  function create($params){

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('type', 'title', 'dbkey'))) {
      return FALSE;
    }

    if (array_key_exists('import_id', $params)) {
      $URL = $this->galaxy->getURL() . '/api/visualizations?import_id=' . $params['import_id'] . '&key=' . $this->galaxy->getAPIKey();
      $response = $this->galaxy->httpPOST($URL);
      return $this->galaxy->expectArray($response);
    }
    else {
      $URL = $this->galaxy->getURL() . '/api/visualizations?key=' . $this->galaxy->getAPIKey();
      $response = $this->galaxy->httpPOST($URL, $params);
      return $this->galaxy->expectArray($response);
    }
  }


  /**
   * Update a specific visualization
   *
   * Corresponds to the Galaxy API/path at
   *   PUT /api/visualizations/{visualizations id}
   *
   * @param $viz_id
   *   visualization id of the visualization to update. To obtain this id
   *   please use this class's index method.
   * @param $title
   *   If the user is changing the title, include the new title.
   * @param $dbkey
   *   If the user is changing the new db key, include the new dbkey.
   * @param $config
   *   The configuration of the visualization.
   *
   * @return
   *   An array containing the updated visualizaiton.
   *
   */
  function update($viz_id, $title = NULL, $dbkey = NULL, $config = NULL){
    $URL = $this->galaxy->getURL() . '/api/visualizations/' .$viz_id. '/?key=' . $this->galaxy->getAPIKey();
    $inputs = array(
      'title'=>$title,
      'dbkey'=>$dbkey,
      'config'=>$config,
    );
    //collect non-null inputs
    $elements = array();
    foreach($inputs as $input=>$value){
      if($input !==null) {
        $elements[$input]=$value;
      }
    }

    $response = $this->galaxy->httpPUT($URL, $elements);
    return $this->galaxy->expectArray($response);

  }
}
