
<?php
/**
 * @file
 *
 * The GalaxyVisualizations class.
 *
 * The GalaxyVisualizations class interacts with Galaxy to manage contents of a Galaxy
 * visualizaiton. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

/**
 * @defgroup visualizations_class Visualizations Class
 * @{
 *   The Visualization class interacts with Galaxy to manage contents of a Galaxy
 *   visualization. The functions in this class correspond to the Galaxy API
 *   functions and are named similarly to their Python counterparts.
 * @}
 */

class GalaxyVisualizations {
  private $galaxy;

  /**
   * The visualizations constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object
   *
   * @return
   *   An instance of a Visualizations object
   *
   *
   */
  function __construct($galaxy) {
    $this->galaxy = $galaxy;
    parent::__construct();
  }

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
    return $this->expectArray($response);
  }

  /**
   * Retreive detailed information about a specific visualization.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/visualizations/<viz_id>
   *
   * @param viz_id
   *   The visualization id whos details to display.
   *
   *
   */
  function show($viz_id){
    $URL = $this->galaxy->getURL() . '/api/visualizations/'. $viz_id . '?/key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->expectArray($response);
  }

  /**
   * Imports copy of existing visualizatiion into the  workplace.
   *
   * Corresponds to the Galaxy API/paths at
   *  POST /api/visualizations
   *  or
   *  POST /api/visualizations?import_id={encoded_visualization_id}
   *
   * @param type
   *   The visualization type for the new visualization.
   * @param title
   *   The title for the visualization.
   * @param import_id
   *   (optional)The id of the visualization to import, if the user
   *   desires to import a visualization.
   *
   * @return
   *   An array containing the created visualization.
   *
   *
   */
  function create($type, $title, $dbkey, $import_id = NULL){
    if($import_id != NULL) {
      $URL = $this->galaxy->getURL() . '/api/visualizations?import_id=' . $import_id . '&key=' . $this->galaxy->getAPIKey();
      $response = $this->galaxy->httpPOST($URL);
      return $this->expectArray($response);
    }

    $URL = $this->galaxy->getURL() . '/api/visualizations?key=' . $this->galaxy->getAPIKey();
    $elements = array(
      'type' => $type,
      'title' => $title,
      'dbkey' => $dbkey,
    );
    $response = $this->galaxy->httpPOST($URL, $elements);
    return $this->expectArray($response);
  }


  /**
   * Update a specific visualization
   *
   * Corresponds to the Galaxy API/path at
   *   PUT /api/visualizations/<visualizations id>
   *
   * @param viz_id
   *   visualization id of the visualization to update. To obtain this id
   *   please use this class's index method.
   * @param title
   *   If the user is changing the title, include the new title.
   * @param $dbkey
   *   If the user is changing the new db key, include the new dbkey.
   * @param $config
   *   The configuration of the visualization.
   *
   * @return
   *   An array containing the updated visualizaiton.
   *
   *
   */
  function update($viz_id, $title=null, $dbkey=null, $config=null){
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
    return $this->expectArray($response);

  }
}
