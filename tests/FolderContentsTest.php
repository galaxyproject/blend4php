<?php
require_once '../galaxy.inc';
require_once 'testConfig.inc';


class FolderContentsTest extends PHPUnit_Framework_TestCase {
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

  // /**
  //  * Tests the index() function.
  //  *
  //  * @depends testInitGalaxy
  //  */
  // function testIndex($galaxy) {
  //   $folder_contents = new GalaxyFolderContents($galaxy);
  //   // A history is technically a folder.
  //   $histories = new GalaxyHistories($galaxy);
  //   $folders = new GalaxyFolders($galaxy);
  //
  //   // Create a history specifcally for this test
  //   $inputs = array(
  //     'name' => 'History for FolderContentsTest',
  //   );
  //   $history = $histories->create($inputs);
  //
  //   // Create a folder within the above history
  //   $folder_inputs = array(
  //     'name' => 'Folder for FolderContentsTest',
  //     'parent_folder_id' => $history['id'],
  //   );
  //   $folder = $folders->create();
  //   print_r($history[0]['id']);
  //   $folder_content = $folder_contents->index(array('folder_id' => $folder[0]['id']));
  //   print_r($folder_content);
  //   $this->assertTrue(is_array($folder_content), $galaxy->getErrorMessage());
  // }

  /**
   * Tests the create() function.
   *
   * There will be one test case where we make two histories, one history that
   * will be the 'hda' source to draw from (copy the test case from
   * HistoryContentsTest). For the history is where we will create a folder in
   * said history and place this particular folder content there.
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy) {

    // Create the necessary obejcts for this function:
    $histories = new GalaxyHistories($galaxy);
    $history_content = new GalaxyHistoryContents($galaxy);
    $tools = new GalaxyTools($galaxy);

    // Create our very own history for this test
    $inputs = array(
      'name' => "FolderContentsTest 'from' history",
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

    // Now we have the source history to draw the 'hda' from.

    $folder_contents = new GalaxyFolderContents($galaxy);
    $folders = new GalaxyFolders($galaxy);

    $history = $histories->create(array('name' => 'History for Folder Contents'));

    $folder_inputs = array(
      'parent_folder_id' => $history['id'],
      'name' => 'Folder for Folder Contents',
      'description' => 'Making sure that we are able to add a Folder Content
      to a given folder.'
    );

    $folder = $folders->create($folder_inputs);
    $hda = $history_content->index(array('history_id' => $history_list[0]['id']));

    $folder_contents_inputs = array(
      'parent_folder_id' => $folder['id'],
      'create_type' => 'dataset',
      'from_hda_id' =>  $hda
    );

    $folder_content = $folder_contents->create($folder_contents_inputs);
    $this->assertTrue(is_array($folder_content), $galaxy->getErrorMessage());
  }
}
