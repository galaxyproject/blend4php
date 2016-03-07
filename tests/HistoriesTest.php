<?php
require_once '../src/Histories.inc';
require_once '../src/GalaxyInstance.inc';
require_once 'testConfig.inc';

class HistoriesTest extends PHPUnit_Framework_TestCase {

  /**
   *
   */
  public function testCreate() {

    global $config;

    $galaxy = new GalaxyInstance($config['host'], $config['port']);
    $galaxy->authenticate($config['email'], $config['pass']);
    $hist = new Histories($galaxy);

   $hist->create('testhistorycreate');

    $response = $hist->httpGET($config['host'] . ':' . $config['port'] . '/api/histories/?key=' . $config['api_key']);

    $i = 0;
    while (array_key_exists('name', $response[$i])) {

      if ("testhistorycreate" == $response[$i]['name']) {
        break;
      }
      $i++ ;
    }

    $this->assertEquals('testhistorycreate', $response[$i]['name']);
  }

  /**
   *
   * @return Json
   */
  public function testIndex() {

    global $config;

    $galaxy = new GalaxyInstance($config['host'], $config['port']);
    $galaxy->authenticate($config['email'], $config['pass']);
    $hist = new Histories($galaxy);

    $response = $hist->index();

    // Now we check again to make sure the response is valid and we can
    // find 'testhistorycreate'
    $i = 0;
    while (array_key_exists('name', $response[$i])) {

      if ("testhistorycreate" == $response[$i]['name']) {
        break;
      }
      $i++ ;
    }

    $this->assertEquals('testhistorycreate', $response[$i]['name']);

    return $response[$i];
  }

  /**
   * @depends testIndex
   *
   * @param json $response
   */
  public function testShow($response) {

    global $config;

    $galaxy = new GalaxyInstance($config['host'], $config['port']);
    $galaxy->authenticate($config['email'], $config['pass']);
    $hist = new Histories($galaxy);

    $result = $hist->show($response['id']);

    $this->assertEquals('testhistorycreate', $result['name']);

    return $result;
  }

  /**
   * This function prepares a downloadable file a selected history.
   *
   * This test calls two functions from the Histories.inc:
   * 1. archiveDownload
   * 2. archiveExport
   *
   * @depends testShow
   */
  public function testArchiveDownload($result) {
    global $config;
    $galaxy = new GalaxyInstance($config['host'], $config['port']);
    $galaxy->authenticate($config['email'], $config['pass']);
    $hist = new Histories($galaxy);

    // We place it in /tmp as it's a temporary holding directory that any
    // entity may place files
    $response = $hist->archiveDownload($result['id'], "/tmp/phpUnitTestHistory.tar.gz");

    $this->assertTrue($response);
    $this->assertTrue(file_exists("/tmp/phpUnitTestHistory.tar.gz"));

    return $result;
  }

  /**
   * This function will 'delete' a history, hiding the history from the users.
   *
   * This action can be undone by undelete, this history can still be found by
   * invoking the index() function
   *
   * @depends testArchiveDownload
   */
  public function testDeleteHistory($result){
    global $config;
    $galaxy = new GalaxyInstance($config['host'], $config['port']);
    $galaxy->authenticate($config['user'], $config['pass']);
    $hist = new Histories($galaxy);

    $hist->deleteHistory($result['id']);

    // Invoke the index() function, this will indirectly test the deleted parameter
    // as well and if the particular id and whether the parameter of said id is
    // deleted [as it's supposed to be from the call from the above call].
    $hist->index();

    $response = $hist->index();

    // Now we check again to make sure the response is valid and we can
    // find 'testhistorycreate'
    $i = 0;
    while (array_key_exists('id', $response[$i]) && array_key_exists('deleted',  $response[$i])) {

      if ( $result['id'] == $response[$i]['id'] && $response[$i]['deleted'] == TRUE) {
        break;
      }
      $i++ ;
    }

    // Once we break out we have found our candidate
    $this->assertEquals($result['id'] ,$response[$i]['id']);
    $this->assertTrue($response[$i]['deleted']);
  }

/**
 *
 *
 * @depends testDeleteHistory
 */
  public function testUndelete($result){
    global $config;
    $galaxy = new GalaxyInstance($config['host'], $config['port']);
    $galaxy->authenticate($config['email'], $config['pass']);
    $hist = new Histories($galaxy);

    var_dump($hist->undelete($result['id']));

    // We run the index function again looking for two parameters again
    // that the id we have undeletetd is back AND that the parameter
    // deleted will be set to false
    $response = $hist->index();

   // var_dump($response);
    $i = 0;
    while (array_key_exists('id', $response[$i]) && array_key_exists('deleted',  $response[$i])) {

      if ( $result['id'] == $response[$i]['id'] && $response[$i]['deleted'] == FALSE) {
        break;
      }
      $i++ ;
    }

    // Once we break out we have found our candidate
    $this->assertEquals($result['id'] ,$response[$i]['id']);
    $this->assertFalse($response[$i]['deleted']);
  }
}
