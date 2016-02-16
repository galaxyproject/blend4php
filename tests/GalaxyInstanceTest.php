<?php
require_once '../src/GalaxyInstance.inc';;

/**
 * Testing to make sure the galaxy instance file will authenticate
 * and connect correctly
 */

class GalaxyInstanceTest extends PHPUnit_Framework_TestCase {

  /**
   * Tests the getURL function.
   *
   * This test ensures that the URLs used by those library are properly
   * constructed for both HTTP and HTTPs.
   *
   * @param $host
   *   The hostname of the server running Galaxy.
   * @param $port
   *   The port where galaxy is running on the remote server.
   * @param $use_https
   *   Set to TRUE if the remote galaxy instance uses HTTPS and FALSE otherwise.
   */
  public function testGetURL() {

    // Test HTTP URL construction.
    $galaxy = new GalaxyInstance('localhost', '8080', FALSE);
    $this->assertEquals($galaxy->getURL(), 'http://localhost:8080');

    // Test HTTPS URL construction.
    $galaxy = new GalaxyInstance('localhost', '8080', TRUE);
    $this->assertEquals($galaxy->getURL(), 'https://localhost:8080');
  }

  /**
   * Tests checkConnection.
   *
   * This test ensure that a galaxy instance can be connected to.  If not
   * then all other tests will naturally fail.
   *
   * @depends testGetURL
   */
  public function testCheckConnection() {
    // Test a connection to an instances that is improperly instantiated.
    $galaxy = new GalaxyInstance('8080', 'localhost', FALSE);
    $this->assertFalse($galaxy->checkConnection());

    // Test a connection to an instance that is properly instantiated.
    $galaxy = new GalaxyInstance('localhost', '8080', FALSE);
    $this->assertTrue($galaxy->checkConnection());

    // Set the private galaxy class member object.
    $this->galaxy = $galaxy;
  }

  /**
   * Test the getAPIKey and setAPIKey functions.
   *
   * @depends testCheckConnection
   */
  public function testGetSetAPIKey() {
     $galaxy = new GalaxyInstance('localhost', '8080', FALSE);
     $galaxy->setAPIKey('XYZPDQ');
     $this->assertEquals($galaxy->getAPIKey(), 'XYZPDQ');
  }

  /**
   * Tests the authenticate function.
   *
   * Tests that we can get an API Key during authentication.  Also tests that
   * if the username/password is not correct that a proper error is set.
   *
   * @depends testGetSetAPIKey
   */
  public function testAuthenticate () {
    $galaxy = new GalaxyInstance('localhost', '8080', FALSE);

    // Test a proper user authentcation. First check that the function
    // will return true.
    $retval = $galaxy->authenticate('cgpwytko@gmail.com', 'potato15');
    $this->assertTRUE($retval);

    // Next, test an incorrect username/password.
    $retval = $galaxy->authenticate('cgpwytko@gmail.com', 'potato5');
    $this->assertTRUE($retval);

  }

}