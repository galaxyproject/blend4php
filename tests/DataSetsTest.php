<?php
require_once '../src/DataSets.inc';
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';
require_once './testConfig.inc';

class DataSetsTest extends PHPUnit_Framework_TestCase {

	/**
	 * Intializes the Galaxy object for all of the tests.
	 *
	 * This function provides the $galaxy object to all other tests as they
	 * are dependent on this one.
	 * 
	 * 
	 */
	function testInitGalaxy() {
		global $config;
	
		// Connect to Galaxy.
		$galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
		$success = $galaxy->authenticate($config['email'], $config['pass']);
		$this->assertTrue($success, $galaxy->getErrorMessage());
	
		return $galaxy;
	}	
	
  /**
   *  Tests the index() function.
   *
   *  The index function retrieves a list of data sets.
   */
  public function testIndex() {
    global $config;
    
    
    
    // Create  Visualization object.
    $Datasets = new Datasets($galaxy);
    
    // Case 1:  Are we getting an array?
    $response = $Datasets->index();
    $this->assertTrue(is_array($response), $Datasets->getErrorMessage());

  }
}
