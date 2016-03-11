<?php
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';
require_once '../src/Histories.inc';
require_once '../src/HistoryContents.inc';


class HistoryContentsTest extends PHPUnit_Framework_TestCase {


  /**
   * Intializes the Galaxy object for all of the tests.
   *
   * This function provides the $galaxy object to all other tests as they
   * are  on this one.
   */
  function testInitGalaxy() {
    global $config;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);

    $response = $galaxy->authenticate($config['email'], $config['pass']);

    return $galaxy;
  }

  /**
   *
   * @depends testInitGalaxy
   */
//   function testSetUp($galaxy){
//     global $config;

//     //Create a tool for uploading files
//     $tool = new Tools($galaxy, array('1'), '500665cb113baad6' );
//     $uploadTool = $tool->create('upload1');
//     print(" \t \n This is the contents of the tool!!!! \n");
//     print_r($uploadTool);
//     //print($uploadTool->getErrorMessage());
//   }


  /**
   * Tests the history content index function
   *
   * @depends testInitGalaxy
   */
  function testIndex($galaxy){
    global $config;

    // First we need a history id, grab the first history we see
    $histories = new Histories($galaxy);
    $history_content = new HistoryContents($galaxy);
    $history_list = $histories->index();
    $history_id = $history_list[0]['id'];

    $response = $history_content->index('f597429621d6eb2b');
    print_r($response);
    $this->assertTrue(is_array($response), $history_content->getErrorMessage());

    // Case 2, user inputs a bad id
    $response2 = $history_content->index("123");
    $this->assertFalse(is_array($response2), $history_content->getErrorMessage());

    //return $response;
  }


  /**
   * Test the create function
   *
   * Creates a new history content
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy){
    global $config;

    // Create history content and history objects
    $histories = new Histories($galaxy);
    $history_content = new HistoryContents($galaxy);
    $history_list = $histories->index();
    $history_id = $history_list[0]['id'];
    print("! ! ! ! The history id is: " . $history_id);
    $content_list = $history_content->index($history_id);
    print("This is the contents of the history contents list: ");
    print_r($content_list);
    $content_id = $content_list['id'];

    //Case 1, correctly create a history_content
    $response = $history_content->create($history_id, $content_id);
    $this->assertTrue(is_array($response), $history_content->getErrorMessage());
  }


}
