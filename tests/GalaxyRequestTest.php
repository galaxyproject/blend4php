<?php
require_once '../src/HTTPRequest.inc';
require_once 'testConfig.inc';
require_once '../src/GalaxyInstance.inc';

/**
 * 
 * The purpose of GalaxyRequest is to allow the visibility of errors
 *
 * This testing file will see if the visiblity of errors are possible
 * on simple request statements
 *
 */

class GalaxyRequestTest extends PHPUnit_Framework_TestCase {

  public function testgetErrorMessage(){
    global $config;
    $galaxy = new GalaxyInstance('localhost', '8080');
    $debug = new HTTPRequest($galaxy);
    
    var_dump($debug);
    
    $galaxy->checkConnection();
    //$debug->getErrorMessage();
    print "\n";
    var_dump($galaxy->checkConnection());
    print "\n";
	}
	
}
