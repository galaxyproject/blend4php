<?php
require_once '../src/Tools.inc';
require_once '../src/Histories.inc';
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
    // The return will be the list of the tool id('s) that contain the query's
    // contents.
    $tools_list = $tools->index(NULL, 'UCSC Test');
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 4: List the available tools that are visualization enabled.
    $tools_list = $tools->index(NULL, NULL, NULL, TRUE);
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 5: Lists the tools in a 'panel' structure
    $tools_list = $tools->index(NULL, NULL, TRUE, NULL);
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 6:
    $tools_list = $tools->index('ucsc_table_direct_test1', 'UCSC Test', TRUE, TRUE);
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

  }

  /**
   * Will test if show() within the Tools class that it presents a specific
   * tool as specified by the tool_id
   *
   * @depends testInitGalaxy
   */
  public function testShow($galaxy){
    $tools = new Tools($galaxy);

    // Acquire the first tool entry
    $tools_list = $tools->index();

    // Case 1: View all tools, no filtering out.
    $tool = $tools->show($tools_list[0]['elems'][0]['id']);
    $this->assertTrue(is_array($tool), $tools->getErrorMessage());
  }

  /**
   * Will test if Diagnostics within the Tools class that it presents a details
   * about a tool specified by the tool_id, information to debug the tool in
   * the event of a fault to the tool.
   *
   * @depends testInitGalaxy
   */
  public function testDiagnostics($galaxy){
    $tools = new Tools ($galaxy);

    // Acquire the first tool entry
    $tools_list = $tools->index();

    $tool = $tools->diagnostics($tools_list[0]['elems'][0]['id']);
    $this->assertTrue(is_array($tool), $tools->getErrorMessage());
  }

  /**
   * Will reload if specified tool and return default configuration of data.
   * Similar to hitting the refresh button on a web page you've been altering.
   *
   * @depends testInitGalaxy
   */
  public function testReload($galaxy){
    $tools = new Tools($galaxy);

    $tools_list = $tools->index();

    $tool = $tools->reload($tools_list[0]['elems'][0]['id']);
    $this->assertTrue(is_array($tool), $tools->getErrorMessage());
  }

  /**
   * Will download a tool specified by the tool_id into the '/tmp/' directory.
   *
   * TODO: This funciton has been seg faulting, this needs to be fixed.
   *
   * @depends testInitGalaxy
   */
  public function testDownload($galaxy){
    $tools = new Tools($galaxy);

    $tools_list = $tools->index();

    $tool_file = $tools->download($tools_list[0]['elems'][0]['id'], "/tmp/" . $tools_list[0]['elems'][0]['id'] . ".tar.gz");
    $this->assertTrue(file_exists("/tmp/" . $tools_list[0]['elems'][0]['id'] . ".tar.gz"));

  }


  /**
   * Will return a tool model that includes its parameters, 'building'
   * the tool into a specified history.
   *
   * @depends testInitGalaxy
   * AttributeError: 'Tool' object has no attribute 'tool'
   */
  public function testBuild($galaxy){
/*     $tools = new Tools($galaxy);

    $histories = new Histories($galaxy);

    $history_list = $histories->index();

    $tools_list = $tools->index();

    print(" \n This is the tools list in build tools: \n");
    //print_r($tools_list);
    //rint("\n This is the histopry list object: \n");
    print_r($history_list);

    // Case 1: Present just the tool model and place it in the selected history
    // denoted by its id.
    $build = $tools->build($tools_list[0]['elems'][0]['id'], $history_list[0]['id']);
    $this->assertTrue(is_array($build), $tools->getErrorMessage());

    // Case 2: Include the version of the tool as specified as newer tools may
    // or may not be compatible with other workflows/datasets etc.
    $build = $tools->build($tools_list[0]['elems'][0]['id'], $history_list[0]['id'], $tools_list[0]['elems'][0]['version']);
    $this->assertTrue(is_array($build), $tools->getErrorMessage()); */
   }

  /**
   * This funciton executes the specified tool given the inputs.
   *
   * In a way this function 'creates' a unique instantiation of this tool.
   *
   *AttributeError: 'UploadDataset' object has no attribute 'value_to_display_text'

   * @depends testInitGalaxy
   */
  public function testCreate($galaxy){
    $tools = new Tools($galaxy);

    // We need a history object in which to place uploaded files for the tool.
    $histories = new Histories($galaxy);
    $history_list = $histories->index();

    // Case 1: Upload a file usinng the upload1 tool
    $files = array(
      0=> array(
        'name'=> 'test.bed',
        'path'=> getcwd() . '/files/test.bed',
      ),
    );

    $tool = $tools->create('upload1', $history_list[0]['id'], $files);

    $this->assertTrue(is_array($tool), $tools->getErrorMessage());

    // Case 2:  Check that a job was actually added.
    $this->assertTrue(array_key_exists('jobs', $tool), "File uploaded to upload1 tool, but job was not created: " . print_r($tool, TRUE));
  }
}
