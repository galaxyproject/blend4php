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
  }

  /**
   * Tests the authenticate function.
   *
   * Expects an example username and password are already set in the
   * remote Galaxy instance.
   *
   * @depends testCheckConnection
   */
  public function testAuthenticate () {
    $galaxy = new GalaxyInstance('localhost', '8080', FALSE);
    $galaxy->authenticate('cgpwytko@gmail.com', 'potato15');
  }
}