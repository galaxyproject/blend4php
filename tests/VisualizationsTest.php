<?php
require_once '../src/Visualizations.inc';

require_once '../src/GalaxyInstance.inc';

require_once './testConfig.inc';



class VisualizationsTest extends PHPUnit_Framework_TestCase {


  /**
   * Test the create()
   *
   *
   */
  function testCreate(){
    global $config;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
    $response = $galaxy->authenticate($config['email'], $config['pass']);
    $vizs = new Visualizations($galaxy);

    // Case 1: Successful creation of a new visualization
    $response = $vizs->create("A type", "A Title", "a db_key" , 'password');
    $this->assertTrue(is_array($response), $vizs->getErrorMessage());

    // Case 2: Failed creation of a visuzalization
    $response = $visz->create("@@",  "@@!@@", '@@' );
    $this->assertTrue($response === FALSE, "Creation should fail but didn't:" . print_r($response, TRUE));
  }



  /**
   * Tests the index() function.
   *
   * The index function retrieves a list of visualization
   *
   *@depends testCreate
   */
  function testIndex() {
    global $config;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
    $response = $galaxy->authenticate($config['email'], $config['pass']);

    // Create  Visualization object.
    $vizs = new Visualizations($galaxy);

    // Case 1:  Are we getting an array?
    $response = $vizs->index();
    $this->assertTrue(is_array($response), $vizs->getErrorMessage());

  }

  /**
   * Tests the show() function.
   *
   * The show function retreives detailed information on a given visuzlization
   *
   *@depends testIndex
   */
  function testShow(){
    global $config;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
    $response = $galaxy->authenticate($config['email'], $config['pass']);

    $vizs = new Visualizations($galaxy);

    // Get the ID of our config .
    $response = $vizs->index();
    $viz_id = NULL;
    foreach($response as $viz){
      $viz_id = $viz['id'];
      break;
    }

    // Case 1:  Get the visualization information for the config user.
    $response = $vizs->show($viz_id);
    $this->assertTrue(is_array($response), $vizs->getErrorMessage());

    // Case 2: Wrong visualization id entered. We should get a FALSE value instead
    // of an error.
    $response = $vizs->show("123456");
    $this->assertTrue($response === FALSE, "Showing user should have failed: " . print_r($response, TRUE));

  }

}
