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
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/visualizations
   *
   * @return
   *   An array containing all of galaxy's visualizations.
   */
  function index() {
    
    $URL = $this->galaxy->getURL() . '/api/visualizations/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreive detailed information about a specific visualization.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/visualizations/{viz_id}
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
  function show($params) {
    
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('viz_id'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('viz_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/visualizations/'. $params['viz_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Imports copy of existing visualizatiion into the  workplace.
   *
   * Corresponds to an HTTP POST on the Galaxy API paths
   *  /api/visualizations
   *  or
   *  /api/visualizations?import_id={encoded_visualization_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - type: The visualization type for the new visualization.
   *   - title: The title for the visualization.
   *   - dbkey: The db key.
   *   - import_id: (Optional) The id of the visualization to import, if the
   *     user desires to import a visualization.
   *
   * @return
   *   An array containing information about the created visualization.
   */
  function create($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('type', 'title', 'dbkey'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('type', 'title', 'dbkey', 'import_id'))) {
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
   * Corresponds to an HTTP PUT on the Galaxy API path
   *   /api/visualizations/{visualizations id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   * - viz_id: Visualization ID of the visualization to update. To obtain this 
   *     ID use Visualizations::index().
   * - title: (Optional) If the user is changing the title, include the new title.
   * - dbkey: (Optional) If the user is changing the new db key, include the new dbkey.
   * - config: The configuration of the visualization.
   *
   * @return
   *   An array containing the updated visualizaiton.
   */
  function update($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('viz_id', 'config'))) {
      return FALSE;
    }
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('viz_id', 'config', 'title', 'dbkey'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/visualizations/' . $params['viz_id'] . '/?key=' . $this->galaxy->getAPIKey();
    
    unset($params['viz_id']);

    $response = $this->galaxy->httpPUT($URL, $params);
    return $this->galaxy->expectArray($response);

  }
  
}
