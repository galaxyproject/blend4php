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
    $success = $galaxy->authenticate($config['email'], $config['pass']);
    $this->assertTrue($success, $galaxy->getErrorMessage());

    return $galaxy;
  }

  /**
   * Will test if index() within the Tools class that it presents tools
   * as specified by the filters
   *
   * @depends testInitGalaxy
   */
  public function testindex($galaxy){
    $tools = new GalaxyTools($galaxy);

    // Case 1: View all tools, no filtering out.

    $inputs = array();

    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $galaxy->getErrorMessage());

    // Case 2: Specify a tool id to see if there are different versions of
    // it installed on the given instance.
    // This particular id is found in the default instances of galaxy.
    $inputs['tool_id'] = 'upload1';
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $galaxy->getErrorMessage());

    // Case 3: Specify a given text query on whether the name of a tool exists.
    // The return will be the list of the tool id('s) that contain the query's
    // contents.
    array_pop($inputs);
    $inputs['q'] = urlencode("UCSC Test");
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $galaxy->getErrorMessage());

    // Case 4: List the available tools that are visualization enabled.
    array_pop($inputs);
    $inputs['trackster'] = TRUE;
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $galaxy->getErrorMessage());

    // Case 5: Lists the tools in a 'panel' structure
    array_pop($inputs);
    $inputs['in_panel'] = TRUE;
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $galaxy->getErrorMessage());

    // Case 6:
    $inputs['trackster'] = TRUE;
    $inputs['q'] = urlencode('UCSC Test');
    $inputs['tool_id'] = 'ucsc_table_direct_test1';
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $galaxy->getErrorMessage());

  }

  /**
   * Will test if show() within the Tools class that it presents a specific
   * tool as specified by the tool_id
   *
   * @depends testInitGalaxy
   */
  public function testShow($galaxy){
    $tools = new GalaxyTools($galaxy);

    // Acquire the first tool entry
    $inputs = array();

    $tools_list = $tools->index($inputs);

    // Case 1: View all tools, no filtering out.
    $input['tool_id'] = $tools_list[0]['elems'][0]['id'];
    $tool = $tools->show($input);
    $this->assertTrue(is_array($tool), $galaxy->getErrorMessage());
  }

  /**
   * Will test if Diagnostics within the Tools class that it presents a details
   * about a tool specified by the tool_id, information to debug the tool in
   * the event of a fault to the tool.
   *
   * @depends testInitGalaxy
   */
  public function testDiagnostics($galaxy){
    $tools = new GalaxyTools ($galaxy);

    // Acquire the first tool entry
    $inputs = array();

    $tools_list = $tools->index($inputs);

    $input['tool_id'] = $tools_list[0]['elems'][0]['id'];
    $tool = $tools->diagnostics($input);
    $this->assertTrue(is_array($tool), $galaxy->getErrorMessage());
  }

  /**
   * Will reload if specified tool and return default configuration of data.
   * Similar to hitting the refresh button on a web page you've been altering.
   *
   * @depends testInitGalaxy
   */
  public function testReload($galaxy){
    $tools = new GalaxyTools($galaxy);

    $inputs = array();

    $tools_list = $tools->index($inputs);

    $input['tool_id'] = $tools_list[0]['elems'][0]['id'];
    $tool = $tools->reload($input);
    $this->assertTrue(is_array($tool), $galaxy->getErrorMessage());
  }

  /**
   * Will download a tool specified by the tool_id into the '/tmp/' directory.
   *
   * @depends testInitGalaxy
   */
  public function testDownload($galaxy){
    $tools = new GalaxyTools($galaxy);

    $inputs = array();

    $tools_list = $tools->index($inputs);

    $inputs['tool_id'] = $tools_list[0]['elems'][0]['id'];
    $inputs['file_path'] = "/tmp/" . $tools_list[0]['elems'][0]['id'] . ".tar.gz";
    $tool_file = $tools->download($inputs);
    $this->assertTrue(file_exists("/tmp/" . $tools_list[0]['elems'][0]['id'] . ".tar.gz"));

  }

  /**
   * This funciton executes the specified tool given the inputs.
   *
   * In a way this function 'creates' a unique instantiation of this tool.
   *
   * AttributeError: 'UploadDataset' object has no attribute 'value_to_display_text'
   *
   * @depends testInitGalaxy
   */
  public function testCreate($galaxy){
    $tools = new GalaxyTools($galaxy);

    // We need a history object in which to place uploaded files for the tool.
    $histories = new GalaxyHistories($galaxy);
    $history_list = $histories->index(array());

    // Case 1: Upload a file usinng the upload1 tool

// upload1 can only upload ONE file at a time
    // This extra element is to demonstrate how to further populate the array
    // in the event of using a tool that uses multiple files
    $inputs['files'] = array(
      0 => array(
        'name' => 'Galaxy-Workflow-UnitTest_Workflow.ga',
        'path' => getcwd(). '/files/Galaxy-Workflow-UnitTest_Workflow.ga',
      ),
      1 => array(
        'name' => 'test.bed',
        'path' => getcwd() . '/files/test.bed',
      ),

    );

    $inputs['tool_id'] = 'upload1';
    $inputs['history_id'] = $history_list[0]['id'];
    $tool = $tools->create($inputs);
    $this->assertTrue(is_array($tool), $galaxy->getErrorMessage());


    // Case 2:  Check that a job was actually added.
    $this->assertTrue(array_key_exists('jobs', $tool), "File uploaded to upload1 tool, but job was not created: " . print_r($tool, TRUE));


  }

  /**
   * Will return a tool model that includes its parameters, 'building'
   * the tool into a specified history.
   *
   * @depends testInitGalaxy
   * AttributeError: 'Tool' object has no attribute 'tool'
   */
  public function testBuild($galaxy){
    $tools = new GalaxyTools($galaxy);

    $histories = new GalaxyHistories($galaxy);

    $history_list = $histories->index(array());

    // Case 1: Present just the tool model and place it in the selected history
    // denoted by its id.

    // We are not using the tool_id upload requires further paramaters

    $inputs = array(
      'tool_id' => 'sort1',
      'history_id' => $history_list[0]['id'],

    );
    $build = $tools->build($inputs);
    $this->assertTrue(is_array($build), $galaxy->getErrorMessage());

    // Case 2: Include the version of the tool as specified as newer tools may
    // or may not be compatible with other workflows/datasets etc.
    $inputs['tool_version'] = $tools->show(array('tool_id' => 'sort1'))['version'];
    $build = $tools->build($inputs);
    $this->assertTrue(is_array($build), $galaxy->getErrorMessage());
  }
}


