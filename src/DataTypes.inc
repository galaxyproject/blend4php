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
class Datatypes extends GalaxyRequest {


  /**
   *
   * @param unknown $galaxy
   */
   public function __construct($galaxy) {
   	parent::__construct($galaxy);
   }

   
   /**
    *   GET /api/datatypes/sniffers
        Return a list of sniffers.
    */
   public function sniffers(){
   	$URL = $this->galaxy->getURL() . '/api/datatypes/sniffers/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   	
   }
   
   /**
    * 	GET /api/datatypes/converters
        Return a list of converters.
    */
   public function converters(){
   	$URL = $this->galaxy->getURL() . '/api/datatypes/converters/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }
   
   /**
    * 	GET /api/datatypes/edam_formats
        Return a list of converters.
    */
   public function edam_formats(){
   	$URL = $this->galaxy->getURL() . '/api/datatypes/edam_formats/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }
   
   /**
        GET /api/datatypes/mapping
        Return a dictionary of class to class mappings.
    */
   public function mapping () {
   	$URL = $this->galaxy->getURL() . '/api/datatypes/mapping/?key=' . $this->galaxy->getAPIKey(); 	
   	return $this->rest->GET($URL);
   }
   
   
   
	/**
	 * GET /api/datatypes Lists datatypes.
	 */   
 	public function index(){
 	 $URL = $this->galaxy->getURL() . '/api/datatypes/?key=' . $this->galaxy->getAPIKey();
 	 return $this->rest->GET($URL); 		
 	}

}

