<?php
require_once '.././src/GalaxyInstance.inc';
/**
 * Testing to make sure the galaxy instance file will authenticate
 * and connect correctly
 * 
 * 
 * @author cwytko
 * Jan 28, 2016 4:30:21 PM
 */

class Test_GalaxyInstance extends PHPUnit_Framework_TestCase {
	/**
	 * By default the user should have localhost selected and the port 8080
	 * opened w/no https for the a trial instance
	 * 
	 * I should have a prompt to ask if the information should be tested otherwise
	 * because how am I to elsewise know the connectivity?
	 * 
	 * @param string $hostname
	 * @param string $port
	 * @param bool $HTTPS
	 */
	public function testConnection ($hostname = 'localhost', $port = 8080, $HTTPS = FALSE) {
		
		$galaxy = new GalaxyInstance($hostname,$port , $HTTPS);
	}
}