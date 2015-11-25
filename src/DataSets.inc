<?php
/**
 * @file
 *
 * API operations on a history.
 *
 * Functions correspond to the Galaxy API file at:
 * https://github.com/galaxyproject/galaxy/blob/dev/lib/galaxy/webapps/galaxy/api/histories.py
 *
 */
require_once 'GalaxyRequest.inc';


/**
 *
 *
 */
class Datasets extends GalaxyRequest {


  /**
   *
   * @param unknown $galaxy
   */
   public function __construct($galaxy) {
   	parent::__construct($galaxy);
   }

   /**
    * GET /api/datasets/{dataset_id}/converted/{ext}
    * return information about datasets made by 
    * converting this dataset to a new format
    * 
    * @param str $dataset_id
    * @param str $extension
    */
   public function converted ($dataset_id, $extension) {
   	$URL = $this->galaxy->getURL() . '/api/datasets/' .$dataset_id .'/converted/'. $extension. '/?key=' . $this->galaxy->getAPIKey(); 	
   	return $this->rest->GET($URL);
   }
   
   
   /**
    * GET /api/histories/{encoded_history_id}/contents/{encoded_content_id}/display Displays 
    * history content (dataset).
    * @param unknown $hist_id
    * @param unknown $hist_content_id
    */
   public function display($hist_id, $hist_content_id){
   	$URL = $this->galaxy->getURL() . '/api/histories/' .$hist_id .'/contents/'. $hist_content_id. '/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }
   
	/**
	 * GET /api/datasets Lists datasets.
	 */   
 	public function index(){
 	 $URL = $this->galaxy->getURL() . '/api/datasets/?key=' . $this->galaxy->getAPIKey();
 	 return $this->rest->GET($URL); 		
 	}
   
 	
 	/**
 	 * GET /api/datasets/{encoded_dataset_id} 
 	 * Displays information about and/or content of a dataset.
 	 * @param str $dataset_id
 	 */
 	public function show($dataset_id){
 	 $URL = $this->galaxy->getURL().'/api/datasets/'.$dataset_id.'/?key=' . $this->galaxy->getAPIKey();
 	 return $this->rest->GET($URL); 		
 	}
}
