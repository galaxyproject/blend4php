<?php
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';
require_once '../src/Histories.inc';
require_once '../src/HistoryContents.inc';
require_once '../src/Tools.inc';

require_once '../src/DataSets.inc';




class DataSetsTest extends phpunit_5.6_Class {


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
    $datasets = new GalaxyDatasets($galaxy);

    // Case 1: Are we getting an array? We shouldn't because apparently the
    // python counterpart has not been implemented
    $dataset_list = $datasets->index();
    $this->assertFalse(is_array($dataset_list), $galaxy->getErrorMessage());

  }

/**
 * Tests the converted function
 *
 * Retreives a list of all the datasets that have been
 * converted within the given datset id
 *
 * @depends testInitGalaxy
 * @depends testIndex
 */
  public function testConverted($galaxy){
    global $config;

    // Create the necessary obejcts for this function:
    $histories = new GalaxyHistories($galaxy);
    $history_content = new GalaxyHistoryContents($galaxy);
    $tools = new GalaxyTools($galaxy);

    // Create our very own history for this test!
    $ourHistory = $histories->create(array('name' => "Testing HistoryContentsCreate!"));
    $this->assertTrue(is_array($ourHistory), $galaxy->getErrorMessage());

    $history_list = $histories->index();
    $history_id = $history_list[0]['id'];

    // Now we need some content!
    $files = array(
      0=> array(
        'name'=> 'test.bed',
        'path'=> getcwd() . '/files/test.bed',
      ),
    );
    $tool = $tools->create(array(
      'tool_id' => 'upload1',
      'history_id' => $history_id,
      'files' => $files
    ));

    // Now history_list[0] should have some content to it
    $content_list = $history_content->index(array('history_id' => $history_id));

    // Make sure the count of this list is greater than 0
    $this->assertTrue((count($content_list) > 0) , "Content was not added to history.");
    $content_id = $content_list[0]['id'];

    //Declare a new datasets
    $datasets = new GalaxyDatasets($galaxy);

    // Case 1: Correctly obtain the converted datasets
    $converted = $datasets->converted(array('dataset_id' => $content_id));
    $this->assertTrue(is_array($converted), $galaxy->getErrorMessage());

    // Case 2: If an incorrect id is entered, the function should return false
    $converted = $datasets->converted(array('dataset_id' => "123"));
    $this->assertFalse(is_array($converted), "Datasets should not have returned an array");



  }

  /**
   * Tests the Display function on datasets
   *
   * Retreives a list of dataset id's associated with a given history and content
   *
   * @depends testInitGalaxy
   * @depends testIndex
   * @depends testConverted
   */
  public function testDisplay($galaxy) {
    global $config;

    // Create the necessary obejcts for this function:
    $histories = new GalaxyHistories($galaxy);
    $history_content = new GalaxyHistoryContents($galaxy);
    $tools = new GalaxyTools($galaxy);

    // Create our very own history for this test!
    $ourHistory = $histories->create(array('name' => "Testing HistoryContentsCreate!"));
    $this->assertTrue(is_array($ourHistory), $galaxy->getErrorMessage());

    $history_list = $histories->index();
    $history_id = $history_list[0]['id'];

    // Now we need some content!
    $files = array(
      0=> array(
        'name'=> 'test.bed',
        'path'=> getcwd() . '/files/test.bed',
      ),
    );
    $tool = $tools->create(array(
      'tool_id' => 'upload1',
      'history_id' => $history_id,
      'files' => $files
    ));

    // Now history_list[0] should have some content to it
    $content_list = $history_content->index(array('history_id' => $history_id));

    // Make sure the count of this list is greater than 0
    $this->assertTrue((count($content_list) > 0) , "Content was not added to history.");
    $content_id = $content_list[0]['id'];

    $history_id = $histories->index();
    $history_id = $history_id[0]['id'];

    //Declare a new datasets
    $datasets = new GalaxyDatasets($galaxy);

    // Case 1: correctly retreive a datasets display
    $display = $datasets->display(array(
      'hist_id' => $history_id,
      'hist_content_id' => $content_id,
    ));
    $this->assertTrue(is_array($display), $galaxy->getError());

    // Case 2: Return false given incorrect informaiton
    $display = $datasets->display(array(
      'hist_id' => "123",
      'hist_content_id' => "456"
    ));
    $this->assertFalse(is_array($display), "Datasets function did not return false on incorrect input.");
  }

  /**
   * Tests the Display function on datasets
   *
   * Retreives a list of dataset id's associated with a given history and content
   *
   * @depends testInitGalaxy
   * @depends testIndex
   * @depends testConverted
   */
  function testShow($galaxy){
    global $config;

    // Obtain a content_id
    // Create the necessary obejcts for this function:
    $histories = new GalaxyHistories($galaxy);
    $history_content = new GalaxyHistoryContents($galaxy);
    $tools = new GalaxyTools($galaxy);

    // Create our very own history for this test!
    $ourHistory = $histories->create(array('name' => "Testing HistoryContentsCreate!"));
    $this->assertTrue(is_array($ourHistory), $galaxy->getErrorMessage());

    $history_list = $histories->index();
    $history_id = $history_list[0]['id'];

    // Now we need some content!
    $files = array(
      0=> array(
        'name'=> 'test.bed',
        'path'=> getcwd() . '/files/test.bed',
      ),
    );
    $tool = $tools->create(array(
      'tool_id' => 'upload1',
      'history_id' => $history_id,
      'files' => $files,
    ));

    // Now history_list[0] should have some content to it
    $content_list = $history_content->index(array('history_id' => $history_id));

    // Make sure the count of this list is greater than 0
    $this->assertTrue((count($content_list) > 0) , "Content was not added to history.");
    $content_id = $content_list[0]['id'];

    // Declare a new datasets
    $datasets = new GalaxyDatasets($galaxy);

    // Case 1: We successfully obtain an array given correct inputs.
    $details = $datasets->show(array('dataset_id' => $content_id));
    $this->assertTrue(is_array($details), $galaxy->getErrorMessage());

    // Case 2: We successfully obtain 'FALSE' given incorrect inputs.
    $details = $datasets->show(array('dataset_id' => "@@"));
    $this->assertFalse(is_array($details), "Datasets did not successfully return false given incorrect inputs.");
  }

}
