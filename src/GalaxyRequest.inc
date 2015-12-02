<?php
require_once 'RESTManager.php';
/**
 *
 */

class GalaxyRequest {

  protected $galaxy = NULL;
  protected $debug = True;
  protected $rest = NULL;
  

/**
 * public constructor
 * 
 * @param GalaxyInstance $galaxy
 * @param string $debug
 * @param string $REST
 * @param RequestError $requestError
 */
 public function __construct($galaxy, $debug=False, $REST = NULL, $requestError = NULL ) {
 	$this-> galaxy = $galaxy; 
 	$this->debug = $debug;
 	
 	if($REST!==NULL) { $this->rest = $REST; } 
 	else{ $this->rest = new RESTManager(); }

 }
 
 /**
  * @return string error message 
  */
 public function getErrorMessage(){
 	return $this->rest->getError();
 }

 /**
  * @return string error type, either 'HTTP' or 'Galaxy' 
  */
 public function getErrorType(){
 	return $this->rest->getErrorType();
 }
 
 
 
}

?>