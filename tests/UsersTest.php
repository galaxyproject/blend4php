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
    global $config;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
    $response = $galaxy->authenticate($config['user'], $config['pass']);

    // Create  Users object.
    $users = new Users($galaxy);
	
    $responses = $users->index();
	printf("\n \n THIS IS THE RESPONSE FROM USERS INDEX" );
    $contains_user = FALSE;
   	foreach($responses as $response){
   	  if(array_key_exists('username', $response)) {
   	  	if($response['username'] == $config['username']){
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
   	global $config;
   	
   	
   	// Connect to Galaxy.
   	$galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
   	$response = $galaxy->authenticate($config['user'], $config['pass']);
   	
   	// Case 1: Retreive information about existing user 
   	$users = new Users($galaxy); 
   	$user_list = $users->index();
   	
   	foreach($user_list as $person){
   		if(array_key_exists('username', $person) && ($person['username'] ))
   	}
   	
   	$response = $users->show($config["user_id"]);

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
   	global $config;
   	
   	// Connect to Galaxy.
   	$galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
   	$response = $galaxy->authenticate($config['user'], $config['pass']);
   	
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
   	
   	//Case 2: make sure server does not create user if bad emailed entered
   	$responses = $users->create("bimbo8000", "bimbo@nothing", "password");
   	$contains_user = FALSE;
   	if($responses != FALSE){	
   	  foreach($responses as $response){
   	    if(array_key_exists('username', $response)) {
   	      if($response['username'] == "bimbo8000"){
   		    $contains_user = TRUE;
   		      break;
   		  }
   		}
   	  }
   	}
   	$this->assertFalse($contains_user);
   	
   }
   
   /**
    * Test the delete function 
    * 
    * Deletes a user
    */
  // function testDelete(){
 /**
   	global $config;
   	
   	// Connect to Galaxy.
   	$galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
   	$response = $galaxy->authenticate($config['user'], $config['pass']);
   	
   	//Case 1, successfully delete a user
   	$users = new Users($galaxy);
   	
   	$response = $user->delete();
   	*/
  // }
   
   /**
    * Test the api key function 
    * 
    * generates a new api key for a user
    */
   function testAPIKEY(){
   	global $config;
   	// Connect to Galaxy.
   	$galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
   	$response = $galaxy->authenticate($config['user'], $config['pass']);
   	
   	//Case 1, enter an api key for a user
   	$users = new Users($galaxy);
   	
   	$id = $user->
   	
   	$response = $users->api_key($config['user_id'] );
   	print($users->getError);
   	print("This is a response \n");
   	var_dump($response);
   	
   	
   }
    

}
