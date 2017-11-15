<?php

require_once '../src/Visualizations.inc';
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';

class VisualizationsTest extends phpunitClass {


  /**
   * Intializes the Galaxy object for all of the tests.
   *
   * This function provides the $galaxy object to all other tests as they
   * are dependent on this one.
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
   * Test the create()
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy){
    global $config;

    $vizs = new GalaxyVisualizations($galaxy);

    // Case 1: Successful creation of a new visualization
    $response = $vizs->create(array(
      'type' => "A type",
      'title' => "A Title",
      'dbkey' => "a db_key" ,
    ));
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

    // Case 2: Failed creation of a visuzalization
    $response = $vizs->create(array(
      'title' => "@@!@@",
      'dbkey' => '@@'
    ));
    $this->assertFalse($response, "Creation should fail but didn't: " . print_r($galaxy->getErrorMessage(), TRUE));
  }



  /**
   * Tests the index() function.
   *
   * The index function retrieves a list of visualization
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testIndex($galaxy) {
    global $config;

    // Create  Visualization object.
    $vizs = new GalaxyVisualizations($galaxy);

    // Case 1:  Are we getting an array?
    $response = $vizs->index();
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

  }

  /**
   * Tests the show() function.
   *
   * The show function retreives detailed information on a given visuzlization
   *
   * @depends testInitGalaxy
   * @depends testIndex
   */
  function testShow($galaxy){
    global $config;

    $vizs = new GalaxyVisualizations($galaxy);

    // Get the ID of our config.
    $response = $vizs->index();
    $viz_id = NULL;
    foreach($response as $viz){
      $viz_id = $viz['id'];
      break;
    }

    // Case 1:  Get the visualization information for the config user.
    $response = $vizs->show(array('viz_id' => $viz_id));
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

    // Case 2: Wrong visualization id entered. We should get a FALSE value instead
    // of an error.
    $response = $vizs->show(array('viz_id' => "123456"));
    $this->assertFalse($response, "Showing user should have failed: " . print_r($galaxy->getErrorMessage(), TRUE));

  }

}
