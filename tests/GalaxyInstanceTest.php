<?php
require_once '../src/GalaxyInstance.inc';;

/**
 * Testing to make sure the galaxy instance file will authenticate
 * and connect correctly
 */

class GalaxyInstanceTest extends PHPUnit_Framework_TestCase {

  private $galaxy;

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
  public function testGetURL($host, $port, $use_https) {
    // Test HTTP URL construction.
    $galaxy = new GalaxyInstance('localhost', '8080', FALSE);
    $this->assertEquals($galaxy->getURL() == 'http://localhost:8080');

    // Test HTTPS URL construction.
    $galaxy = new GalaxyInstance('localhost', '8080', TRUE);
    $this->assertEquals($galaxy->getURL() == 'https://localhost:8080');
  }

  /**
   * Tests the checkConnection() function.
   *
   * This performs two tests, one to check that a connection can be established
   * and one to check what happens when a connection fails.
   */
  public function initializeCheckConnection() {
    return array(
      // These tests are purposusly supposed to fail
      'Host/Port parameter switch' => array ('8080', 'localhost', FALSE, FALSE),
      'Galaxy Test Instance' => array('localhost', '8080', FALSE, TRUE)
    );
  }

  /**
   * By default the user should have localhost selected and the port 8080
   * opened w/no https for the a trial instance
   *
   * I should have a prompt to ask if the information should be tested otherwise
   * because how am I to elsewise know the connectivity?
   *
   * @dataProvider initializeCheckConnection
   * @depends testGetURL
   */
  public function testCheckConnection($host, $port, $use_https, $expected) {
    $galaxy = new GalaxyInstance($host, $port, $use_https);
    if ($expected == FALSE) {
      $this->assertFalse($galaxy->checkConnection());
    }
    if ($expected == TRUE) {
      $this->assertTrue($galaxy->checkConnection());
    }
  }

  /**
   * @depends testCheckConnection
   */
  public function initializeAuthenticate() {
    return array(
        'Default' => array ('localhost', '8080', FALSE),
        'Host/Port parameter switch' => array ('8080', 'localhost', FALSE),
        'Enabling HTTPS with default' => array ('localhost', '8080', TRUE),
        'Custom Hostname' => array ('ExampleHostName.com', '80', TRUE)
    );
  }

  /**
   * Test
   *
   * I should have a prompt to ask if the information should be tested otherwise
   * because how am I to elsewise know the connectivity?
   *
   * @dataProvider initializeAuthenticate
   */
  public function testAuthenticate ($hostname, $port) {
    $galaxy = new GalaxyInstance('localhost', '8080', FALSE);
    $galaxy->authenticate('cgpwytko@gmail.com', 'potato15');
  }
}