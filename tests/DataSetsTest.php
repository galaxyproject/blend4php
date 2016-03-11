<?php
require_once '../src/GalaxyInstance.inc';
require_once '../src/Histories.inc';
require_once '../src/DataSets.inc';
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
   *
   *  @depends testInitGalaxy
   */
  public function testIndex($galaxy) {
    global $config;

    // Create Visualization object.
    $datasets = new Datasets($galaxy);

    // Case 1: Are we getting an array? We shouldn't because apparently the
    // python counterpart has not been implemented
    $response = $datasets->index();
    $this->assertFalse(is_array($response), $datasets->getErrorMessage());

  }

/**
 * Tests the converted function
 *
 * Retreives a list of all the datasets that have been
 * converted
 *
 * @depends testInitGalaxy
 */
  public function testConverted($galaxy){
    global $config;

    // Create Datasets object.
    $datasets = new Datasets($galaxy);

    // We must create a histories object to obtain datasets
    $histories = new Histories($galaxy);

    $history_list = $histories->index();
    print_r($history_list);
  }
}
