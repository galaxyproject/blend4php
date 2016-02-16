<?php
require_once '.././src/GalaxyInstance.inc';
require_once '.././src/Users.inc';

/**
 * Testing to make sure the galaxy instance file will authenticate
 * and connect correctly
 *
 *
 * @author cwytko
 *         Jan 28, 2016 4:30:21 PM
 */
print "\nIf your hostname is not localhost, and/or your port is not 8080 please change the parameters within the function Test_GalaxyInstance.inc\n\n";

print "\n******BE SURE TO CHANGE THE FOLLOWING FUNCTIONS ACCORDINGLY******\n******initializeConnection()******\n******initializeAuthenticate()******\n******IF YOU DO NOT MOST TESTS WILL FAIL******";

class Test_GalaxyInstance extends PHPUnit_Framework_TestCase {
	
	public function initializeConnection() {
		return array(
			'Default' => array ('localhost', '8080', FALSE),
			'Host/Port parameter switch' => array ('8080', 'localhost', FALSE),
			'Enabling HTTPS with default' => array ('localhost', '8080', TRUE ),
			'Custom Hostname' => array ('ExampleHostName.com', '80', TRUE)
		);
		
	}
	
	public function initializeAuthenticate() {
		return array(
				'Default' => array ('localhost', '8080', FALSE),
				'Host/Port parameter switch' => array ('8080', 'localhost', FALSE),
				'Enabling HTTPS with default' => array ('localhost', '8080', TRUE ),
				'Custom Hostname' => array ('ExampleHostName.com', '80', TRUE)
		);
	
	}
	
	/**
	 * By default the user should have localhost selected and the port 8080
	 * opened w/no https for the a trial instance
	 *
	 * I should have a prompt to ask if the information should be tested otherwise
	 * because how am I to elsewise know the connectivity?
	 *
	 * @dataProvider initializeConnection
	 */
	public function testConnection($host, $port, $use_https) {
		$galaxy = new GalaxyInstance($host, $port, $use_https);
		$this->assertTrue($galaxy->verifyLive());
	}
	
	
	/**
	 * Test
	 *
	 * I should have a prompt to ask if the information should be tested otherwise
	 * because how am I to elsewise know the connectivity?
	 *
	 * @dataProvider initializeAuthenticate
	 */
	public function testAuthenticate (){
		$galaxy = new GalaxyInstance('localhost', '8080', FALSE);
		$galaxy->authenticate('cgpwytko@gmail.com', 'potato15');
		$usr = new Users($galaxy);
		print $usr->index(false, 'cgpwytko@gmail.com', NULL, false);
			
	}

	
	
	
	
}