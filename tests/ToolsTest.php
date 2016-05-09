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
    
    $inputs = array();
    
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 2: Specify a tool id to see if there are different versions of
    // it installed on the given instance.
    // This particular id is found in the default instances of galaxy.
    $inputs['tool_id'] = 'upload1';
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 3: Specify a given text query on whether the name of a tool exists.
    // The return will be the list of the tool id('s) that contain the query's
    // contents.
    array_pop($inputs);
    $inputs['q'] = 'UCSC Test';
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 4: List the available tools that are visualization enabled.
    array_pop($inputs);
    $inputs['trackster'] = TRUE;
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 5: Lists the tools in a 'panel' structure
    array_pop($inputs);
    $inputs['in_panel'] = TRUE;
    $tools_list = $tools->index($inputs);
    $this->assertTrue(is_array($tools_list), $tools->getErrorMessage());

    // Case 6:
    $inputs['trackster'] = TRUE;
    $inputs['q'] = 'UCSC Test';
    $inputs['tool_id'] = 'ucsc_table_direct_test1';
    $tools_list = $tools->index($inputs);
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
    $inputs = array();
    
    $tools_list = $tools->index($inputs);

    // Case 1: View all tools, no filtering out.
    $input['tool_id'] = $tools_list[0]['elems'][0]['id'];
    $tool = $tools->show($input);
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
    $inputs = array();
    
    $tools_list = $tools->index($inputs);

    $input['tool_id'] = $tools_list[0]['elems'][0]['id'];
    $tool = $tools->diagnostics($input);
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

    $inputs = array();
    
    $tools_list = $tools->index($inputs);
    
    $input['tool_id'] = $tools_list[0]['elems'][0]['id'];
    $tool = $tools->reload($input);
    $this->assertTrue(is_array($tool), $tools->getErrorMessage());
  }

  /**
   * Will download a tool specified by the tool_id into the '/tmp/' directory.
   *
   * @depends testInitGalaxy
   */
  public function testDownload($galaxy){
    $tools = new Tools($galaxy);

    $inputs = array();
    
    $tools_list = $tools->index($inputs);

    $inputs['tool_id'] = $tools_list[0]['elems'][0]['id'];
    $inputs['file_path'] = "/tmp/" . $tools_list[0]['elems'][0]['id'] . ".tar.gz";
    $tool_file = $tools->download($inputs);
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
    //  we don't know
    // how to use any one of the given tools properly
    
    // TODO: Working on it now
/*     $tools = new Tools($galaxy);

    $histories = new Histories($galaxy);

    $history_list = $histories->index();

    $tools_list = $tools->index();

    print(" \n This is the tools list in build tools: \n");
    //print_r($tools_list);
    //print("\n This is the history list object: \n");
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
   * AttributeError: 'UploadDataset' object has no attribute 'value_to_display_text'
   * 
   * @depends testInitGalaxy
   */
  public function testCreate($galaxy){
    $tools = new Tools($galaxy);

    // We need a history object in which to place uploaded files for the tool.
    $histories = new Histories($galaxy);
    $history_list = $histories->index();

    // Case 1: Upload a file usinng the upload1 tool
    $inputs['files'] = array(
      0 => array(
        'name' => 'test.bed',
        'path' => getcwd() . '/files/test.bed',
      ),
    );

    $inputs['tool_id'] = 'upload1';
    $inputs['history_id'] = $history_list[0]['id'];
    $tool = $tools->create($inputs);
    $this->assertTrue(is_array($tool), $tools->getErrorMessage());


    // Case 2:  Check that a job was actually added.
    $this->assertTrue(array_key_exists('jobs', $tool), "File uploaded to upload1 tool, but job was not created: " . print_r($tool, TRUE));


  }
}
