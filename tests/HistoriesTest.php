<?php
require_once '../src/Histories.inc';
require_once '../src/GalaxyInstance.inc';
require_once 'testConfig.inc';

/**
 * Unit test for the Histories class.
 */
class HistoriesTest extends PHPUnit_Framework_TestCase {

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

    $histories = new Histories($galaxy);

    // Case 1: Create a history with only a single name.
    $history = $histories->create('testhistorycreate');
    $this->assertTrue(is_array($history), $histories->getErrorMessage());

  }

  /**
   * Tests the index() function of the Hisories class.
   *
   * @depends testInitGalaxy
   */
  public function testIndex($galaxy) {

    $histories = new Histories($galaxy);

    // Case 1:  Are we getting an array?  If so, that's all we need to
    // test. We don't need to do unit testing for galaxy. We assume the
    // array is correct.
    $history_list = $histories->index();
    $this->assertTrue(is_array($history_list), $histories->getErrorMessage());


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

    $histories = new Histories($galaxy);

    // Case 2: Create a history with a name, and an existing history,
    // This form will be copying an existing history (as we have made at least
    // one in the above create() call).
    $history = $histories->create('test-history-copy-existing', $history_list[0]['id']);
    $this->assertTrue(is_array($history), $histories->getErrorMessage());

    // Case 3: Create a copy history from an imported archive.
    // This case will invoke the archiveExport() function.
    // We will Export a previously created history utilizing the index() again.

    // NOTE** You cannot copy from a local history id AND import a history as
    // well, that would be a conflict of which history object to copy
    $history = $histories->create('test-history-from-archive', NULL, $histories->archiveExport($history_list[0]['id']));
    $this->assertTrue(is_array($history), $histories->getErrorMessage());


    // Case 4: Change the hdas param from default to False.
    $history = $histories->create('test-history-hdas-false', NULL, NULL, NULL, FALSE);
    $this->assertTrue(is_array($history), $histories->getErrorMessage());

    // Case 5: hdas param is False and we are importing from archive.
    $history = $histories->create('test-history-hdas-false-from-archive', NULL, $histories->archiveExport($history_list[0]['id']), NULL, FALSE);
    $this->assertTrue(is_array($history), $histories->getErrorMessage());


    // Case 6: hdas param is False and we are copying an existing history.
    $history = $histories->create('test-history-hdas-false-copy-existing', $history_list[0]['id'], NULL, NULL, FALSE);
    $this->assertTrue(is_array($history), $histories->getErrorMessage());

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

    $histories = new Histories($galaxy);

    // Use the history ID of the first history in the list to test the
    // show() function.
    $hist_id = $history_list[0]['id'];

    // Case 1:  Are we getting an array?  If so, that's all we need to
    // test. We don't need to do unit testing for galaxy. We assume the
    // array is correct.
    $history = $histories->show($hist_id);
    $this->assertTrue(is_array($history), $histories->getErrorMessage());

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

    $histories = new Histories($galaxy);

    // We place it in /tmp as it's a temporary holding directory that any
    // entity may place files
    $success = $histories->archiveDownload($history['id'], "/tmp/phpUnitTestHistory.tar.gz");

    $this->assertTrue($success);
    $this->assertTrue(file_exists("/tmp/phpUnitTestHistory.tar.gz"));
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

    $histories = new Histories($galaxy);

    // Case 1: Test that we can mark the history as deleted.
    $del_history = $histories->deleteHistory($history['id']);
    $this->assertTrue(is_array($del_history), $histories->getErrorMessage());
    $this->assertTrue($del_history['deleted']);

    return $del_history;
  }

  /**
   * Tests the index() function of the Hisories class.
   *
   * This second test for index needs to check the merging of active and
   * deleted hitories.  We don't want to do this test until we are sure
   * that the create() and deleteHistory() functions are also test and that
   * should give us a combination of active and deleted histories.
   *
   * @depends testInitGalaxy
   * @depends testDeleteHistory
   */
  public function testIndex2($galaxy) {
    $histories = new Histories($galaxy);

    // Currently we know we ahve one deleted history, so now add another
    // this will be active.
    $history = $histories->create('testhistorycreate2');
    $this->assertTrue(is_array($history), $histories->getErrorMessage());

    // Case 2: Because our code merges active and deleted histories, we need
    // to check to make sure the merge is working.
    $history_list = $histories->index();
    $this->assertTrue(is_array($history_list), $histories->getErrorMessage());

    // Iterate through the histories list to find both deleted and undeleted
    // histories.
    $has_active = FALSE;
    $has_deleted = FALSE;
    foreach ($history_list as $history) {
      if (!$history['deleted']) {
        $has_active = TRUE;
        continue;
      }
      if ($history['deleted']) {
        $has_deleted = TRUE;
        continue;
      }
    }
    $this->assertTrue($has_active, "Histories index() fails to include the active histories: " . print_r($history_list, TRUE));
    $this->assertTrue($has_deleted, "Histories index() fails to include the deleted histories: " . print_r($history_list, TRUE));
  }

/**
 * Tests the undelete() function of the Histories class.
 *
 * @depends testInitGalaxy
 * @depends testDeleteHistory
 */
  public function testUndelete($galaxy, $del_history){

    $histories = new Histories($galaxy);

    // Case 1: Make sure that the deleted file created in the
    // testDeleteHistory() function can be undeleted.
    $undel_history = $histories->undelete($del_history['id']);
    $this->assertTrue(is_array($undel_history), $histories->getErrorMessage());
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
    $histories = new Histories($galaxy);

    // Case 1: Make sure that an array (whether empty or filled) will be
    // presented when the citations function is invoked.
    $citations = $histories->citations($undel_history['id']);
    $this->assertTrue(is_array($citations), $histories->getErrorMessage());
  }

  /**
   * Tests the published() member functions of the Histories class.
   *
   * @depends testInitGalaxy
   */
  public function testpublished($galaxy){
    $histories = new Histories($galaxy);

    // Case 1: Make sure that an array (whether empty or filled) will be
    // presented when the published function is invoked.
    // Meaning we return an array of all the histories published under the
    // the given user.
    $published = $histories->published();
    $this->assertTrue(is_array($published), $histories->getErrorMessage());
  }

  /**
   * Tests the sharedWithMe() member functions of the Histories class.
   *
   * @depends testInitGalaxy
   */
  public function testSharedWithMe($galaxy){
    $histories = new Histories($galaxy);

    // Case 1: Make sure that an array of histories shared with the given user
    // (whether empty or filled) will be presented when the sharedWithMe()
    // function is invoked.
    $shared_histories = $histories->sharedWithMe();
    $this->assertTrue(is_array($shared_histories), $histories->getErrorMessage());
  }
}
