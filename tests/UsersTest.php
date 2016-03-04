<?php

require_once '../src/GalaxyInstance.inc';
require_once '../src/Users.inc';
require_once './testConfig.inc';


class UsersTest extends PHPUnit_Framework_TestCase {
	
  
  /**
   *  Tests the index() function.
   *
   *  The index function retrieves a list of users.
   */
  function testIndex() {
    global $config_brian;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config_brian['host'], $config_brian['port'], FALSE);
    $response = $galaxy->authenticate($config_brian['user'], $config_brian['pass']);

    // Create  Users object.
    $users = new Users($galaxy);
	
    $responses = $users->index();

    $contains_user = FALSE;
   	foreach($responses as $response){
   	  if(array_key_exists('username', $response)) {
   	  	if($response['username'] == $config_brian['username']){
   	  	  $contains_user = TRUE;
   	  	  break;
   	  	}
   	  }
   	}    
    // Case 1: Retrieve an array of all users	
    $this->assertTrue($contains_user);
  }
  
  /**
   * Test the show() function.
   * 
   * The show function retreives information on a specific user
   */
   function testShow(){
   	global $config_brian;
   	
   	// Connect to Galaxy.
   	$galaxy = new GalaxyInstance($config_brian['host'], $config_brian['port'], FALSE);
   	$response = $galaxy->authenticate($config_brian['user'], $config_brian['pass']);
   	
   	// Case 1: Retreive information about existing user 
   	$users = new Users($galaxy); 
   	
   	$response = $users->show($config_brian["user_id"]);

   	$this->assertTrue(($response!= FALSE && count($response) > 0));
   	
   	//Case2: Wrong user id entered
   	
   	$response = $users->show("123456");
   	$this->assertFalse(($response!= FALSE && count($response) > 0));   	
   	
   }
   
   /**
    * Test the create() function.
    * 
    * The create function creates a new user
    */
   function testCreate(){
   	global $config_brian;
   	
   	// Connect to Galaxy.
   	$galaxy = new GalaxyInstance($config_brian['host'], $config_brian['port'], FALSE);
   	$response = $galaxy->authenticate($config_brian['user'], $config_brian['pass']);
   	
   	//Case 1, create a new user correctly
   	$users = new Users($galaxy);
   	
   	$users->create("bimbo9000", "bimbo@yahoo.com", "password");
   	$responses = $users->index();
   	$contains_user = FALSE;
   	foreach($responses as $response){
   		if(array_key_exists('username', $response)) {
   			if($response['username'] == "bimbo9000"){
   				$contains_user = TRUE;
   				break;
   			}
   		}
   	}
   	
   	$this->assertTrue($contains_user);
   	
   	
   }
   
}
