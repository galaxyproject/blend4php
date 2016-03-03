<?php
require_once "../src/RequestError.inc";

/**
 * @file
 *
 * Testing to be sure the program discerns whether the fault lies with galaxy
 * or if the fault lies with our program bindings
 */


class RequestErrorTest extends PHPUnit_Framework_TestCase {

	/**
	 * Tests the parseCURLResponse function to see if it can catch all of the errors.
	 *
	 * Compose a dummy json like object for this function to play with, one with
	 * the right pieces and one without to make sure that this error handler does
	 * what it's supposed to.
	 *
	 * @param $message
	 * 	The json object to parse to then be interpreted and presented to the user
	 *
	 */
  public function testparseCURLResponse(){
	// Construct Dummy object

	  // Test 1: test case #1 with message not in JSON format.
  	$dummy = 'asdaljfa;lskjfaf';
  	$handler = new RequestError();
  	$response = $handler->parseCURLResponse($dummy);
  	$this->assertFalse($response);
  	$this->assertEquals('Galaxy', $handler->getErrorType());
  	$this->assertEquals('Unknown CURL response: not json compatible.' ,$handler->getErrorMessage());

  	// Test 2a:  tests case #2 with python failure with an error message.
	  $dummy = '{"traceback": "No traceback available.", "err_msg": "API authentication required for this request", "err_code": 403001}';
	  $handler = new RequestError();
	  $response = $handler->parseCURLResponse($dummy);
	  $this->assertFalse($response);
	  $this->assertEquals('Galaxy', $handler->getErrorType());
	  $this->assertEquals('API authentication required for this request' ,$handler->getErrorMessage());

	  // Test 2b:  test case #3 with a python failure but no error message.
	  $dummy = '{"traceback": "No traceback available.", "err_code": 403001}';
	  $response = $handler->parseCURLResponse($dummy);
	  $this->assertFalse($response);
	  $this->assertEquals('Galaxy', $handler->getErrorType());
	  $this->assertEquals('A galaxy error was detected, though its contents are unkown', $handler->getErrorMessage());

	  // Test 3:  tests case # where galaxy generated the error.
	  // TODO: Find example to use for this test


	  // Test 4:  on a successful message do we get the proper array format
	  // with the correct keys.
	  $dummy = '[{ "id": "f2db41e1fa331b3e", "model_class": "Role", "name": "testuser@mail.com", "url": "/api/roles/f2db41e1fa331b3e"},  {"id": "f597429621d6eb2b", "model_class": "Role", "name": "blah@mail.com", "url": "/api/roles/f597429621d6eb2b"}]';
	  $response = $handler->parseCURLResponse($dummy);
	  $this->assertTrue(array_key_exists('id', $response[0]));
	  $this->assertEquals('f2db41e1fa331b3e', $response[0]['id']);


  }
}