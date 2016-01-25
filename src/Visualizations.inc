
<?php
include_once 'GalaxyRequest.inc';

/**
 * 
 * Currently this file cannot be completed for we do not have any visualization objects nor the knowledge
 * of how to create them 
 *
 */



class Visualizations extends GalaxyRequest{
	/**
	 * Implements the constructor.
	 *
	 * @param GalaxyInstance $galaxy
	 */
	function __construct($galaxy) {
		parent::__construct($galaxy);
	}
	
	/**
	 * GET /api/visualizations 
	 */
	function index(){
		$url = $this->galaxy->getURL() . '/api/visualizations/?key=' . $this->galaxy->getAPIKey();
		return $this->rest->GET($url);
	}
	
	/**
	 * GET /api/visualizations/<viz_id>
	 * 
	 * @param string viz_id
	 */
	function show($viz_id){
		$url = $this->galaxy->getURL() . '/api/visualizations/'. $viz_id . '?/key=' . $this->galaxy->getAPIKey();
		return $this->rest->GET($url);
	}
	
	/**
	 * POST /api/visualizations
	 * or 
	 * POST /api/visualizations?import_id={encoded_visualization_id}
	 * imports copy of existing visualizatiion into workplace
	 * 
	 * @param string type visualization type
	 * @param string title the title for the visualization
	 * @param int import_id the id of the visualization to import, if the user
	 * desires to import a visualization
	 */
	function create($type, $title, $dbkey, $import_id = NULL){
		$url = $this->galaxy->getURL() . '/api/visualizations/?key=' . $this->galaxy->getAPIKey();
		$elements = array(
			'type'=> $type,
			'title'=>$title,
			'dbkey'=>$dbkey,
		);
		$this->rest->POST($url, $elements);
	}
	 /**
	  * TODO: import existing visualization
	  */
}
