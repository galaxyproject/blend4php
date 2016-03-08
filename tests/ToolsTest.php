<?php
require_once '../src/Tools.inc';
require_once '../src/GalaxyInstance.inc';
require_once 'testConfig.inc';


class ToolsTest extends PHPUnit_Framework_TestCase {
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
    $response = $galaxy->authenticate($config['email'], $config['pass']);

    return $galaxy;
  }

  /**
   * Will test if index() within the Tools class that it presents tools
   * as specified by the filters
   *
   * @depends testInitGalaxy
   */
  public function testindex($galaxy){
    $tools = new Tools($galaxy);

    // Case 1: View all tools, no filtering out.
    $tools_list = $tools->index();
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 2: Specify a tool id to see if there are different versions of
    // it installed on the given instance.
    // This particular id is found in the default instances of galaxy.
    $tools_list = $tools->index('upload1');
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 3: Specify a given text query on whether the name of a tool exists.
    // The return will be the list of the tool id's that contain the query's
    // contents.
    $tools_list = $tools->index(NULL, 'table browser');
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

  }

}
