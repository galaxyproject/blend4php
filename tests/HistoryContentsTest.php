<?php
require_once './testConfig.inc';
require_once '../galaxy.inc';

class HistoryContentsTest extends phpunit56Class {

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
   * Tests the history content index function
   *
   * @depends testInitGalaxy
   */
  function testIndex($galaxy){

    // First we need a history id, grab the first history we see
    $histories = new GalaxyHistories($galaxy);
    $tools = new GalaxyTools($galaxy);
    $history_content = new GalaxyHistoryContents($galaxy);


    // Create our very own history!
    //
    $inputs = array(
      'name' => "Testing HistoryContentsIndex1",
    );
    $ourHistory = $histories->create($inputs);
    unset($inputs['name']);
    $history_list = $histories->index($inputs);
    $inputs['history_id'] = $history_list[0]['id'];


    $response = $history_content->index($inputs);
    $this->assertTrue(is_array($response), $galaxy->getErrorMessage());

    // Case 2, user inputs a bad id
    $inputs['history_id'] = "123";
    $response2 = $history_content->index($inputs);
    $this->assertFalse(is_array($response2), $galaxy->getErrorMessage());
  }

  /**
   * Test the create function
   *
   * Creates a new GalaxyHistory content
   *
   * @depends testInitGalaxy
   * @depends testIndex
   */
  function testCreate($galaxy){

    // Create the necessary obejcts for this function:
    $histories = new GalaxyHistories($galaxy);
    $history_content = new GalaxyHistoryContents($galaxy);
    $tools = new GalaxyTools($galaxy);

    // Create our very own history for this test
    $inputs = array(
      'name' => "Testing HistoryContentsIndex2",
    );
    $ourHistory = $histories->create($inputs);
    unset($inputs['name']);
    $history_list = $histories->index($inputs);

    // Now we need some content
    $inputs['files'] = array(
      0 => array(
        'name'=> 'test.bed',
        'path'=> getcwd() . '/files/test.bed',
      ),
    );
    $inputs['history_id'] = $history_list[0]['id'];
    $inputs['tool_id'] = 'upload1';
    $tool = $tools->create($inputs);

    unset($inputs['files']);
    unset($inputs['tool_id']);
    // Now history_list[0] should have some content to it
    $content_list = $history_content->index($inputs);

    // Make sure the count of this list is greater than 0
    $this->assertTrue((count($content_list) > 0) , "Content was not added to history.");
    $inputs['source'] = 'hda';
    $inputs['content'] = $content_list[0]['id'];

    // Case 1, correctly create a history_content
    $content= $history_content->create($inputs);
    $this->assertTrue(is_array($content), $galaxy->getErrorMessage());

    // Case 2, given incorrect history, our function will return FALSE
    // gracefully.
    $inputs['history_id'] = "123";
    $content = $history_content->create($inputs);
    $this->assertFalse(is_array($content), $galaxy->getErrorMessage());

    // Case 3. given an incorrect content_id, our function will still return false
    $inputs['content'] = "123";
    $content = $history_content->create($inputs);
    $this->assertFalse(is_array($content), $galaxy->getErrorMessage());

    // Reset the parameters to proper values to be manipulated by the next test
    // function.

    unset($inputs['source']);

    $inputs['id'] = $content_list[0]['id'];

    unset($inputs['content']);

    $inputs['history_id'] = $history_list[0]['id'];


    return $inputs;
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
  function testShow($galaxy, $inputs){

    $histories = new GalaxyHistories($galaxy);
    $history_content = new GalaxyHistoryContents($galaxy);

    $history_list = $histories->index(array());

    // Case 1 successfully display history contents
    $content = $history_content->show($inputs);
    $this->assertTrue(is_array($content), $galaxy->getErrorMessage());

    // Case 2 given an incorrect history id, make sure it still returns an array
    // containing info9rmation abot the content.
    $inputs['history_id'] = "@@";
    $content2 = $history_content->show($inputs);
    $this->assertTrue(is_array($content2), $galaxy->getErrorMessage());

    //print_r($content2);

    // Case 3 given an incorect content_id, make sure it returns false.
    $inputs['history_id'] = $history_list[0]['id'];
    $inputs['id'] = "@@";
    $content2 = $history_content->show($inputs);
    $this->assertFalse(is_array($content2), $galaxy->getErrorMessage());
  }

  /**
   * Tests the update function of history content
   *
   * Updates an existing history content, (places a pre-existing dataset into a
   *   given history)
   *
   * @depends testInitGalaxy
   * @depends testCreate
   * @depends testIndex
   */
  function testUpdate($galaxy, $inputs){

   // Declare history content and history objects
   $histories = new GalaxyHistories($galaxy);
   $history_content = new GalaxyHistoryContents($galaxy);

   // Case 1, update successfully
   $inputs['annotation'] = 'This History content has been updated';
   $updated = $history_content->update($inputs);
   $this->assertTrue(is_array($updated), $galaxy->getErrorMessage());

   // Case 2, incorrect history_id provided, make sure it still returns an array
   $inputs['history_id'] = "123";
   $updated = $history_content->update($inputs);
   $this->assertTrue(is_array($updated), $galaxy->getErrorMessage());


   $inputs['history_id'] = $histories->index(array())[0]['id'];

   // Case 3, incorrect content _id provided, make sure it returns false
   $inputs['id'] = "123";
   $updated = $history_content->update($inputs);
   $this->assertFalse(is_array($updated), $galaxy->getErrorMessage());
 }

 /**
  * Tests the delete function of the history content.
  *
  * Deletes a given history content from a history.
  *
  * @depends testInitGalaxy
  * @depends testCreate
  * @depends testIndex
  * @depends testShow
  * @depends testUpdate
  */
 function testDelete($galaxy, $inputs){

   // Declare history content and history objects
   $histories = new GalaxyHistories($galaxy);
   $history_content = new GalaxyHistoryContents($galaxy);

   $deleted = $history_content->delete($inputs);
   unset($inputs['id']);
   // Obtan the content_id of the content in the 0'th index
   $content_list = $history_content->index($inputs);

   // Case 1 make sure the history content is marked as deleted.
   $this->assertTrue($content_list[0]['deleted']  == 'true');
 }
 
}
