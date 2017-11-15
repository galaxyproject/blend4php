<?php
require_once "../src/Error.inc";

/**
 * @file
 *
 * Testing to be sure the program discerns whether the fault lies with galaxy
 * or if the fault lies with our program bindings
 */


class ErrorTest extends phpunitClass {

  /**
   * Tests the setError() and getError() functions.
   */
  function testGetSet() {
    // We simply need to make sure that the setter works.
    $error = new GalaxyError();
    $error->setError('HTTP', 'test_message');
    $error = $error->getError();

    // Case 1:  The return value should always be an array.
    $this->assertTrue(is_array($error) , 'The RequestError return value is not an array: ' . print_r($error, TRUE));

    // Case 2:  Make sure the array is formatted properly:
    $this->assertTrue(array_key_exists('type', $error), 'The RequestError is missing the "type" key: '. print_r($error, TRUE));
    $this->assertTrue(array_key_exists('message', $error), 'The RequestError is missing the "message" key: '. print_r($error, TRUE));

    // Case 3:  The type should match the type provided.
    $this->assertEquals($error['type'], 'HTTP', 'The RequestError type does not match what was provided: '. print_r($error, TRUE));

    // Case 3:  The message should be teh message provided.
    $this->assertEquals($error['message'], 'test_message', 'The RequestError message does not match what was provided: '. print_r($error, TRUE));

  }

}