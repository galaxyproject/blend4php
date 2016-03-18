<?php
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';
require_once '../src/Histories.inc';
require_once '../src/HistoryContents.inc';
require_once '../src/Tools.inc';

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
    $tools = new Tools($galaxy);
    $history_content = new HistoryContents($galaxy);


    // Create our very own history!
    // This history should appear as the first item on the histories list!?
    $ourHistory = $histories->create("Testing HistoryContentsIndex!");
    $history_list = $histories->index();
    $history_id = $history_list[0]['id'];


    $response = $history_content->index($history_id);
    //print_r($response);
    $this->assertTrue(is_array($response), $history_content->getErrorMessage());

    // Case 2, user inputs a bad id
    $response2 = $history_content->index("123");
    $this->assertFalse(is_array($response2), $history_content->getErrorMessage());

    // return the history_id.
    return $history_id;
  }


  /**
   * Test the create function
   *
   * Creates a new history content
   *
   * @depends testInitGalaxy
   * @depends testIndex
   */
  function testCreate($galaxy){
    global $config;

    // Create the necessary obejcts for this function:
    $histories = new Histories($galaxy);
    $history_content = new HistoryContents($galaxy);
    $tools = new Tools($galaxy);

    // Create our very own history for this test!
    $ourHistory = $histories->create("Testing HistoryContentsCreate!");
    $history_list = $histories->index();
    $history_id = $history_list[0]['id'];

    // Now we need some content!
    $files = array(
      0=> array(
        'name'=> 'test.bed',
        'path'=> getcwd() . '/files/test.bed',
      ),
    );
    $tool = $tools->create('upload1', $history_id, $files);

    // Now history_list[0] should have some content to it
    $content_list = $history_content->index($history_id);

    // Make sure the count of this list is greater than 0
    $this->assertTrue((count($content_list) > 0) , "Content was not added to history.");
    $content_id = $content_list[0]['id'];

    // Case 1, correctly create a history_content
    $content= $history_content->create($history_list[1]['id'], $content_id);
    $this->assertTrue(is_array($content), $history_content->getErrorMessage());

    // Case 2, given incorrect history, our function will return FALSE
    // gracefully.
    $content = $history_content->create('123', $content_id);
    $this->assertFalse(is_array($content), $history_content->getErrorMessage());

    // Case 3. given an incorrect conten_id, our function will still return false
    $content = $history_content->create('123', '123');
    $this->assertFalse(is_array($content), $history_content->getErrorMessage());

    return $content_id;
  }

  /**
   * Test the show function
   *
   * Retreives details about a history content.
   *
   * @depends testInitGalaxy
   * @depends testCreate
   * @depends testIndex
   */
  function testShow($galaxy, $content_id){
    global $config;

    $histories = new Histories($galaxy);
    $history_content = new HistoryContents($galaxy);


    $history_list = $histories->index();
    $history_id = $history_list[0]['id'];

    // Case 1 successfully display history contents
    $content = $history_content->show($history_id, $content_id);
    $this->assertTrue(is_array($content), $history_content->getErrorMessage());

  }

  function test


}
