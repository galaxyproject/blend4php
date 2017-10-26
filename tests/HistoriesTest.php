<?php
require_once '../galaxy.inc';
require_once 'testConfig.inc';

/**
 * Unit test for the Histories class.
 */
class HistoriesTest extends phpunit56Class {

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
   * Tests the create() function of the Histories class.
   *
   * @depends testInitGalaxy
   */
  public function testCreate($galaxy) {

    $histories = new GalaxyHistories($galaxy);

    // Case 1: Create a history with only a single name.
    $inputs = array(
      'name' => 'testhistorycreate',
    );

    $history = $histories->create($inputs);
    $this->assertTrue(is_array($history), $galaxy->getErrorMessage());

    return $history['id'];
  }

  /**
   * Tests the index() function of the Hisories class.
   *
   * @depends testInitGalaxy
   */
  public function testIndex($galaxy) {

    $histories = new GalaxyHistories($galaxy);

    $inputs = array();

    // Case 1: Include the the deleted param
    $inputs['deleted'] = TRUE;
    $history_list = $histories->index($inputs);
    $this->assertTrue(is_array($history_list), $galaxy->getErrorMessage());

    // Case 2:  Are we getting an array?  If so, that's all we need to.
    unset($inputs['deleted']);
    $history_list = $histories->index($inputs);
    $this->assertTrue(is_array($history_list), $galaxy->getErrorMessage());

    return $history_list;
  }

  /**
   * Tests the create() function of the Histories class.
   *
   * This instantiation is different in that we want to copy an existing
   * history into a new container, and to do that we need to have at least
   * one existing history to copy from.
   *
   * @depends testInitGalaxy
   * @depends testIndex
   */
  public function testCreateOptions($galaxy, $history_list) {

    $histories = new GalaxyHistories($galaxy);

    // Case 2: Create a history with a name, and an existing history,
    // This form will be copying an existing history (as we have made at least
    // one in the above create() call).
    $inputs = array(
      'name' => 'test-history-copy-existing',
      'history_id' => $history_list[0]['id']
    );
    $history = $histories->create($inputs);
    $this->assertTrue(is_array($history), $galaxy->getErrorMessage());

    // Case 3: Create a copy history from an imported archive.
    // This case will invoke the archiveExport() function.
    // We will Export a previously created history utilizing the index() again.

    // NOTE** You cannot copy from a local history id AND import a history as
    // well, that would be a conflict of which history object to copy
    unset($inputs['history_id']);
    $inputs = array(
      'name' => 'test-history-from-archive',
      'archive_source' => $histories->archiveExport(array('history_id' => $history_list[0]['id'])),
    );
    $history = $histories->create($inputs);
    $this->assertTrue(is_array($history), $galaxy->getErrorMessage());


    // Case 4: Change the hdas param from default to False.
    unset($inputs['archive_source']);
    $inputs = array(
      'name' => 'test-history-hdas-false',
      'all_datasets' => FALSE
    );
    $history = $histories->create($inputs);
    $this->assertTrue(is_array($history), $galaxy->getErrorMessage());

    // Case 5: hdas param is False and we are importing from archive.
    $inputs = array(
      'name' => 'test-history-hdas-false-from-archive',
      'archive_source' => $histories->archiveExport(array('history_id' => $history_list[0]['id'])),
      'all_datasets' => FALSE
    );
    $history = $histories->create($inputs);
    $this->assertTrue(is_array($history), $galaxy->getErrorMessage());


    // Case 6: hdas param is False and we are copying an existing history.
    $inputs = array(
      'name' => 'test-history-hdas-false-copy-existing',
      'archive_source' => $history_list[0]['id'],
      'all_datasets' => FALSE
    );
    $history = $histories->create($inputs);
    $this->assertTrue(is_array($history), $galaxy->getErrorMessage());

    // TODO: Deal with the archive_type parameter, I do not know of another
    // type of archive type supported by Galaxy:
    // URL is default
    // What about file upload maybe that's the other type?
  }

  /**
   * Test the show() function of the Histories class.
   *
   * @depends testInitGalaxy
   * @depends testIndex
   *
   */
  public function testShow($galaxy, $history_list) {

    $histories = new GalaxyHistories($galaxy);

    // Case 1:  Are we getting an array?  If so, that's all we need to
    // test. We don't need to do unit testing for galaxy. We assume the
    // array is correct.
    $inputs = array(
      'history_id' => $history_list[0]['id'],
    );
    
    $history = $histories->show($inputs);
    $this->assertTrue(is_array($history), $galaxy->getErrorMessage());

    return $history;
  }

  /**
   * This function prepares a downloadable file a selected history.
   *
   * This test calls two functions from the Histories.inc:
   * 1. archiveDownload
   * 2. archiveExport
   *
   * @depends testInitGalaxy
   * @depends testShow
   */
  public function testArchiveDownload($galaxy, $history) {

    $histories = new GalaxyHistories($galaxy);

    // We place it in /tmp as it's a temporary holding directory that any
    // entity may place files
    $inputs = array(
      'history_id' => $history['id'],
      'file_path' => "/tmp/phpUnitTestHistory.tar.gz",
    );
    $success = $histories->archiveDownload($inputs);

    $this->assertTrue($success);
    $this->assertTrue(file_exists($inputs['file_path']));
  }

  /**
   * Tests the deleteHistory() function of the Histories calss.
   *
   * This function will 'delete' a history which hides the history from the
   * users. This action can be undone by undelete, this history can still be
   * found by invoking the index() function
   *
   * @depends testInitGalaxy
   * @depends testShow
   * @depends testArchiveDownload
   */
  public function testDeleteHistory($galaxy, $history){

    $histories = new GalaxyHistories($galaxy);

    // Case 1: Test that we can mark the history as deleted.
    $del_history = $histories->deleteHistory(array('history_id' => $history['id']));
    $this->assertTrue(is_array($del_history), $galaxy->getErrorMessage());
    $this->assertTrue($del_history['deleted']);

    return $del_history;
  }

/**
 * Tests the undelete() function of the Histories class.
 *
 * @depends testInitGalaxy
 * @depends testDeleteHistory
 */
  public function testUndelete($galaxy, $del_history){

    $histories = new GalaxyHistories($galaxy);

    // Case 1: Make sure that the deleted file created in the
    // testDeleteHistory() function can be undeleted.
    $inputs = array(
      'history_id' => $del_history['id'],
    );
    $undel_history = $histories->undelete($inputs);
    $this->assertTrue(is_array($undel_history), $galaxy->getErrorMessage());
    $this->assertFalse($undel_history['deleted']);

    return $undel_history;
  }



  /**
   * Tests the citations() member functions of the Histories class.
   *
   * @depends testInitGalaxy
   * @depends testUndelete
   */
  public function testCitations($galaxy, $undel_history){
    $histories = new GalaxyHistories($galaxy);

    // Case 1: Make sure that an array (whether empty or filled) will be
    // presented when the citations function is invoked.
    $inputs = array(
      'history_id' => $undel_history['id'],
    );
    $citations = $histories->citations($inputs);
    $this->assertTrue(is_array($citations), $galaxy->getErrorMessage());
  }

  /**
   * Tests the published() member functions of the Histories class.
   *
   * @depends testInitGalaxy
   */
  public function testpublished($galaxy){
    $histories = new GalaxyHistories($galaxy);

    // Case 1: Make sure that an array (whether empty or filled) will be
    // presented when the published function is invoked.
    // Meaning we return an array of all the histories published under the
    // the given user.
    $published = $histories->published();
    $this->assertTrue(is_array($published), $galaxy->getErrorMessage());
  }

  /**
   * Tests the sharedWithMe() member functions of the Histories class.
   *
   * @depends testInitGalaxy
   */
  public function testSharedWithMe($galaxy){
    $histories = new GalaxyHistories($galaxy);

    // Case 1: Make sure that an array of histories shared with the given user
    // (whether empty or filled) will be presented when the sharedWithMe()
    // function is invoked.
    $shared_histories = $histories->sharedWithMe();
    $this->assertTrue(is_array($shared_histories), $galaxy->getErrorMessage());
  }
}
