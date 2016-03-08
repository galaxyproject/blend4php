<?php
require_once '../src/Tools.inc';


class ToolsTest extends PHPUnit_Framework_TestCase {
	/**
	 * Intializes the Galaxy object for all of the tests.
	 *
	 * This function provides the $galaxy object to all other tests as they
	 * are dependent on this one.
	 */
	function testInitGalaxy() {
		global $config;

		// Connect to Galaxy.
		$galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
		$response = $galaxy->authenticate($config['email'], $config['pass']);

		return $galaxy;
	}

	/**
	 * Will test if index() within the Tools class that it presents tools
	 * as specified by the filters
	 *
	 * @depends testInitGalaxy
	 */
	public function testindex($galaxy){

	}

}
