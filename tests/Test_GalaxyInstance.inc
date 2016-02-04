<?php
require_once '.././src/GalaxyInstance.inc';
/**
 * Testing to make sure the galaxy instance file will authenticate
 * and connect correctly
 *
 *
 * @author cwytko
 *         Jan 28, 2016 4:30:21 PM
 */
print "\nIf your hostname is not localhost, and/or your port is not 8080 please change the parameters within the function Test_GalaxyInstance.inc\n\n";
class Test_GalaxyInstance extends PHPUnit_Framework_TestCase {
	/**
	 * @timestamp Feb 2, 2016 1:03:13 PM
	 * I'm back I'm trying to see how to see if the server is up or not
	 * I'm not using phpunit not right yet but the dummy script that I was using
	 * up until this point did not return a NULL from my galaxyInstance despite
	 * not having the server up and running, I'll try running a curl and see
	 * what happens, because the object returns SOMETHING, I'm going to run a
	 * var_dump on the variable and see what it has
	 * @timestamp Feb 2, 2016 1:12:25 PM
	 * var_dump returned the same object when the server was on or off
	 * so I'll need to run a curl
	 * @timestamp Feb 2, 2016 1:20:43 PM
	 * The curl works so I'll use that...but now how do I use the result of the
	 * curl as an input to test the galaxy instance initialization?
	 * @timestamp Feb 2, 2016 1:56:40 PM
	 * I think I got it -- I was looking at the dataProvider parameter for the
	 * phpunit doc
	 * @timestamp Feb 2, 2016 2:05:01 PM
	 * Stafn has spoken to me I need to use phpunit only to run values through 
	 * established functions so that I need only worry about the fails and passes
	 * of the tests rather than making more functions within phpunit
	 * @timestamp Feb 2, 2016 2:37:30 PM
	 * I made a new function in GalaxyInstance.inc called verify
	 * @timestamp Feb 2, 2016 2:46:01 PM
	 * That should not have taken me that long to implement but oh well
	 * Now to learn from phpunit how to simply call this function and run maybe
	 * 3 or 4 different initializations other than the valid one
	 * I'll put things out of order and use the dataProvider example to then run
	 * the tests through 
	 * @timestamp Feb 2, 2016 2:52:39 PM
	 * Right now I need to see how use an instantiated object's member functions
	 * within phpunit's constraints
	 * @timestamp Feb 2, 2016 4:14:55 PM
	 * I have started the first phpunit test I'll run it by Stephen before 
	 * leaving, I want to go a little early
	 */
	public function initialize() {
		return array(
			'Default' => array ('localhost', '8080', FALSE),
			'Host/Port swap' => array ('8080', 'localhost', FALSE),
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
	 * @dataProvider initialize
	 */
	public function testConnection($host, $port, $use_https) {
		$galaxy = new GalaxyInstance($host, $port, $use_https);
		$this->assertTrue($galaxy->verifyLive());
	}
	
	/**
	 * @timestamp Feb 4, 2016 9:45:20 AM
	 * To check if the user is admin I'll need to look into the galaxy.ini
	 * file and check on line 786 and see if the email of that user is there in
	 * order to test this unit function
	 * If so I'll run the function
	 * 	NOTE***
	 * 	The function will expect a user to exist I will need to ask the user for
	 * 	their username and pass and then test the to see if authenticate works
	 * 	I'm not sure if this is the proper way to test this function though,
	 *  But to create a new user we would have to call the create() member
	 *  function and then 
	 * 
	 */

	
	
	
	
}