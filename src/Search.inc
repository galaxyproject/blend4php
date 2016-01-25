<?php
include_once 'GalaxyRequest.inc';





class Search extends GalaxyRequest{

	/**
	 * Implements the constructor.
	 *
	 * @param GalaxyInstance $galaxy
	 */
	function __construct($galaxy) {
		parent::__construct($galaxy);
	}
	
	
	/**
	 * Post /api/search
	 * Do a search oif the various elements in Galaxy

	 * @param string $query, must be a valid SQL expression, lowercase example: 
	 * 
	 * @return json string results
	 */
   function create($query) { 
   	$url = $this->galaxy->getURL() . '/api/search/?key=' . $this->galaxy->getAPIKey();
   	$elements = array (
   		'query'=>$query,
   	);
   	return  $this->rest->POST($url, $elements);
   }
	
	

	
	
	
}
