<?php
require_once '../src/Histories.inc';
require_once '../src/GalaxyInstance.inc';
require_once 'testConfig.inc';


class HistoriesTest extends PHPUnit_Framework_TestCase {

  public function testcreate(){
  	global $config;
  	$galaxy = new GalaxyInstance($config['host'], $config['port']);
  	$galaxy->authenticate($config['user'], $config['pass']);
  	$hist = new Histories($galaxy);

  	//$hist->create('testhistorycreate');

  	$response = $hist->GET($config['host'] . ':' . $config['port'] .  '/api/histories/?key=' . $config['api_key']);

  	$i = 0;
  	while (array_key_exists('name', $response[$i])){

  		if("testhistorycreate" == $response[$i]['name']){
  			break;
  		}
  		$i++;
  	}

  	$this->assertEquals('testhistorycreate', $response[$i]['name']);
  }

  public function testindex(){
   global $config;
   $galaxy = new GalaxyInstance($config['host'], $config['port']);
   $galaxy->authenticate($config['user'], $config['pass']);
   $hist = new Histories($galaxy);

   $response = $hist->index();
   // Now we check again to make sure the response is valid and we can
   // find 'testhistorycreate'
   $i = 0;
   while (array_key_exists('name', $response[$i])){

   if("testhistorycreate" == $response[$i]['name']){
     break;
   }
    $i++;
   }

   $this->assertEquals('testhistorycreate', $response[$i]['name']);

   return $response[$i];
  }
  /**
   * @depends testindex
   * @param json $response
   */
  public function testshow($response){
  	global $config;
  	$galaxy = new GalaxyInstance($config['host'], $config['port']);
  	$galaxy->authenticate($config['user'], $config['pass']);
  	$hist = new Histories($galaxy);

  	$result = $hist->show($response['id']);

  	$this->assertEquals('testhistorycreate', $result['name']);

  	return $result;
  }

  /**
   * @depends testshow
   */
  public function testarchive_download($result){
   global $config;
   $galaxy = new GalaxyInstance($config['host'], $config['port']);
   $galaxy->authenticate($config['user'], $config['pass']);
   $hist = new Histories($galaxy);

   $response = $hist->archive_download($result['id']);

   var_dump($response);
  }
}
