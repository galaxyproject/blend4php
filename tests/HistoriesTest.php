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
    $response = $galaxy->authenticate($config['email'], $config['pass']);

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

    // TODO: test each of the additional arguments to the create() function
    // to make sure they work.
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
  }
}
