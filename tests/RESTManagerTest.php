<?php
require_once '../src/RESTManager.inc';
require_once 'testConfig.inc';

/**
 * @file
 *
 * Testing to be sure the program processes POST, PUT, and DELETE requests.
 * GET will be tested in conjunction with the other calls to ensure the other
 * processes are working.
 *
 */

class RESTManagerTest extends PHPUnit_Framework_TestCase {

  /**
   * Uses the curl POST to place data on a server.
   *
   * In our case we will test the library api and make sure that we POST there
   * correctly.
   * A subsequent function will delete the library we create here.
   */
  public function testPOST_GET() {
    $curl = new RESTManager();
    global $config;

    $curl = new RESTManager();
    $host = $config['host'];
    $user = $config['user'];
    $pass = $config['pass'];
    $port = $config['port'];
    $apikey = $config['apikey'];

    $i = 0;
    $input = array ('name' => "phpunittestlibrary");
    $success = $curl->POST($host . ':' . $port . '/api/libraries/' . '?key=' . $apikey, $input);

    // Now we check to see if the library we just posted is in fact there.
    $response = $curl->GET($host . ':' . $port . '/api/libraries/?' . 'key=' . $apikey);

    while (array_key_exists('name', $response[$i])){

      if("phpunittestlibrary" == $response[$i]['name']){
        break;
      }
      $i++;
    }
    // When we break we either have found phpunittestuser or we have not and
    // our POST has failed and we are at the last user
    $this->assertEquals('phpunittestlibrary', $response[$i]['name']);

  }

  /**
   * Uses the curl PUT to place and/or modify existing data on a server.
   * 
   * The library API does not have PUT method so we will use a historycontent
   * manipulation. This will untilize the PUT method twice to test its ability
   * to act as it should (to add data and modify an existing piece of data) and
   * use the GET method to verify the proper use of both PUTs.
   */
  public function testPUT_GET(){
    $curl = new RESTManager();
    global $config;

    $curl = new RESTManager();
    $host = $config['host'];
    $user = $config['user'];
    $pass = $config['pass'];
    $port = $config['port'];
    $apikey = $config['apikey'];

    $input = array ('name' => "phpunittesthistoryput1test", 
       'annotation' => NULL,
       'tool_version' => NULL,
       'archive_type' => NULL,
       'history_id' => NULL,
       'all_datasets' => TRUE);

    $success = $curl->PUT($host . ':' . $port . '/api/histories/' . '?key=' . $apikey, $input);

    $i = 0;
    $response = $curl->GET($host . ':' . $port . '/api/histories/?' . 'key=' . $apikey);

    while (array_key_exists('name', $response[$i])){

      if("phpunittesthistoryput1test" == $response[$i]['name']){
        break;
      }
      $i++;
    }

    $this->assertEquals('phpunittesthistoryput1test',$response[$i]['name']);

    // Here we add a history content to the history we created above to then 
    // manipulate
  }

  /**
   * Uses the curl DELETE to remove data from a server.
   *
   * Removes the library created by this test case.
   */
  public function testDELETE_GET(){
    global $config;

    $curl = new RESTManager();
    $host = $config['host'];
    $user = $config['user'];
    $pass = $config['pass'];
    $port = $config['port'];
    $apikey = $config['apikey'];

    $i = 0;
    $response = $curl->GET($host . ':' . $port . '/api/libraries/?deleted=False&' . 'key=' . $apikey);

    while (array_key_exists('name', $response[$i])){

      if("phpunittestlibrary" == $response[$i]['name']){
        break;
      }
      $i++;
    }
    $parameters = array(
      'undelete' => FALSE,
    );
    $response = $curl->DELETE($host . ':' . $port . '/api/libraries/' . $response[$i]['id'] . '?key=' . $apikey, $parameters);

    $i = 0;
    $response = $curl->GET($host . ':' . $port . '/api/libraries/?deleted=True&' . 'key=' . $apikey);
    while (array_key_exists('name', $response[$i])){

      if("phpunittestlibrary" == $response[$i]['name']){
        break;
      }
      $i++;
    }
    $this->assertEquals(true, $response[$i]['deleted']);
  }

}