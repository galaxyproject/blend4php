
<?php
/**
 * @file
 *
 * The Visualizations class.
 *
 * The Visualiations class interacts with Galaxy to manage contents of a Galaxy
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

include_once 'HTTPRequest.inc';


class Visualizations extends HTTPRequest{
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
   * @ingroup visualizations_class
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
   *   A Json array containing all of galaxy's visualizations.
   *
   * @ingroup visualizations_class
   */
  function index(){
    $url = $this->galaxy->getURL() . '/api/visualizations/?key=' . $this->galaxy->getAPIKey();
    return $this->httpGET($url);
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
   * @ingroup visualizations_class
   */
  function show($viz_id){
    $url = $this->galaxy->getURL() . '/api/visualizations/'. $viz_id . '?/key=' . $this->galaxy->getAPIKey();
    return $this->rest->httpGET($url);
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
   *   A Json array containing the created visualization.
   *
   * @ingroup visualizations_class
   */
  function create($type, $title, $dbkey, $import_id = NULL){
    if($import_id != NULL) {
      $url = $this->galaxy->getURL() . '/api/visualizations/?import_id=' . $import_id . '&key=' . $this->galaxy->getAPIKey();
      return $this->httpPOST($url);
    }

    $url = $this->galaxy->getURL() . '/api/visualizations/?key=' . $this->galaxy->getAPIKey();
    $elements = array(
      'type'=> $type,
      'title'=>$title,
      'dbkey'=>$dbkey,
    );
    return $this->httpPOST($url, $elements);
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
   *   A Json object containing the updated visualizaiton.
   *
   * @ingroup visualizations_class
   */
  function update($viz_id, $title=null, $dbkey=null, $config=null){
    $url = $this->galaxy->getURL() . '/api/visualizations/' .$viz_id. '/?key=' . $this->galaxy->getAPIKey();
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

    return $this->rest->httpPUT($url,$elements);

  }
}
