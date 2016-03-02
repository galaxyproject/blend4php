<?php
require_once '../src/Histories.inc';
require_once '../src/GalaxyInstance.inc';
require_once 'testConfig.inc';


class HistoriesTest extends PHPUnit_Framework_TestCase {

  public function testcreate(){
  	global $config;
  	$galaxy = new GalaxyInstance($config['host'], $config['port']);
  	$galaxy->authenticate($config['email'], $config['pass']);
  	$hist = new Histories($galaxy);
  	
  	$hist->create('testhistorycreate');
  
  	
  }
}
