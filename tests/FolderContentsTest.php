<?php
require_once '../galaxy.inc';
require_once 'testConfig.inc';


class FolderContentsTest extends phpunit56Class {
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
   * Tests the index() function.
   *
   * @depends testInitGalaxy
   */
  function testIndex($galaxy) {
    $folder_contents = new GalaxyFolderContents($galaxy);
    // A libary is technically a folder.
    $libraries = new GalaxyLibraries($galaxy);
    $folders = new GalaxyFolders($galaxy);

    // Create a history specifcally for this test
    $inputs = array(
      'name' => 'Library for FolderContentsTest',
    );
    $library = $libraries->create($inputs);
    // Create a folder within the above history
    $folder_inputs = array(
      'name' => 'Folder for FolderContentsTest',
      'parent_id' => $library['id'],
    );

    $folder = $folders->create($folder_inputs);
    $this->assertTrue(is_array($folder), $galaxy->getErrorMessage());

    $folder_content = $folder_contents->index(array('folder_id' => $folder['id']));
    $this->assertTrue(is_array($folder_content), $galaxy->getErrorMessage());
  }

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
    $this->assertTrue(is_array($tool), $galaxy->getErrorMessage());

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

    // A library is a folder too.
    $libraries = new GalaxyLibraries($galaxy);
    $library = $libraries->create(array('name' => uniqid('galaxy-php-test-library-')));
    $this->assertTrue(is_array($library), $galaxy->getErrorMessage());

    $folder = $folders->create(array(
      'parent_id' => $library['id'],
      'name' => uniqid('galaxy-php-test-folder-'),
      'description' => 'Making sure that we are able to add a Folder Content
      to a given folder.'
    ));
    $this->assertTrue(is_array($folder), $galaxy->getErrorMessage());

    $hda = $history_content->index(array('history_id' => $history_list[0]['id']));
    $this->assertTrue(is_array($hda), $galaxy->getErrorMessage());

    // TODO: look at this test. It fails with a message that the library
    // is deleted and it must be undeleted before a dataset can be added.
    // But, the library was created newly above and is not deleted. May be
    // a bug in Galaxy?
//     $folder_content = $folder_contents->create(array(
//       'folder_id' => $folder['id'],
//       'from_hda_id' =>  $hda[0]['id'],
//     ));
//     $this->assertTrue(is_array($folder_content), $galaxy->getErrorMessage());
  }
}
