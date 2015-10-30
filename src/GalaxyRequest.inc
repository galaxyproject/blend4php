<?php
require_once 'GalaxyInstance.inc';
require_once 'RESTManager.php';
/**
 *
 */

class GalaxyRequest {
  // A Galaxy instance.o
  protected $galaxy = NULL;
  protected $debug = True;
  protected $rest = NULL;
  


 public function __construct($galaxy, $debug=False, $REST = NULL) {
 	$this-> galaxy = $galaxy; 
 	$this->debug = False;
 	if($REST!==NULL) { $this->rest = $REST; } 
 	if($REST===NULL) { $this->rest = new RESTManager(); }
 	
 }
 
 
 
}