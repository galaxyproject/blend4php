
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
		if($import_id != NULL) {
			$url = $this->galaxy->getURL() . '/api/visualizations/?import_id=' . $import_id . '&key=' . $this->galaxy->getAPIKey();
			return $this->rest->POST($url);
		}
		
		$url = $this->galaxy->getURL() . '/api/visualizations/?key=' . $this->galaxy->getAPIKey();
		$elements = array(
			'type'=> $type,
			'title'=>$title,
			'dbkey'=>$dbkey,
		);
		return $this->rest->POST($url, $elements);
	}
	
	
    /**
     * PUT /api/visualizations/<visualizations id>
     * @param string $viz_id visual;iization id of the visualization to update
     * @param string $title If we are changing the title, include the new title
     * @param string $dbkey If we are changing the new db key, include the new dbkey
     * @param string $config ??
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
		
		return $this->rest->PUT($url,$elements);
		
	}
}
