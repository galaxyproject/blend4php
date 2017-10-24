<?php

/**
 * @file
 *
 * Testing to make sure the galaxy instance file will authenticate
 * and connect correctly
 */

require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';
require_once 'PHPUnit/Autoload.php';


class GalaxyInstanceTest extends PHPUnit_Framework_TestCase {

  /**
   * Tests the getURL function.
   *
   * This test ensures that the URLs used by those library are properly
   * constructed for both HTTP and HTTPs.
   */
  public function testGetURL() {

    global $config;

    // Test HTTP URL construction.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
    $this->assertEquals($galaxy->getURL(), 'http://' . $config['host'] . ':' . $config['port']);

    // Test HTTPS URL construction.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], TRUE);
    $this->assertEquals($galaxy->getURL(), 'https://' . $config['host'] . ':' . $config['port']);
  }

  /**
   * Tests checkVersion.
   *
   * This test ensure that a galaxy instance can be connected to.  If not
   * then all other tests will naturally fail.
   *
   * @depends testGetURL
   */
  public function testGetVersion() {
    global $config;

    // Test a connection to an instances that is improperly instantiated.
    $galaxy = new GalaxyInstance($config['port'], $config['host'], FALSE);
    $version = $galaxy->getVersion();
    $this->assertFalse($version);

    // Test a connection to an instance that is properly instantiated.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
    $version = $galaxy->getVersion();
    $this->assertTrue(is_array($version), $galaxy->getErrorMessage() . " Please ensure Galaxy is running and the connection details are correct.");
    $this->assertTrue(array_key_exists('version_major', $version),  "The version array is missing the 'version_major' index. Please ensure Galaxy is running and the connection details are correct.");

  }

  /**
   * Test the getAPIKey and setAPIKey functions.
   *
   * @depends testGetVersion
   */
  public function testGetSetAPIKey() {
    global $config;

    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
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
    global $config;

    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);

    // Test a proper user authentcation. First check that the function
    // will return our API key after authentication.
    $success = $galaxy->authenticate($config['email'], $config['pass']);
    $this->assertTrue($success);

    // Next, test an incorrect username/password.
    $success = $galaxy->authenticate($config['pass'], $config['email']);
    $this->assertFalse($success);

  }

}