<?php
require_once '../src/RESTManager.php';
require_once 'loadConfig.php';

/**
 * @file
 *
 * Testing to be sure the program processes GET, POST, PUT, and DELETE requests.
 * 
 */

class RESTManagerTest extends PHPUnit_Framework_TestCase {
	
	/**
	 * Uses a default curl call and returns the resposnse made by the call.
	 * 
	 * This case will be the most simple as we are simply seeing if we can grab
	 * something from the net.
	 */
	public function testGET(){
		$curl = new RESTManager();
		
		// We pass a URL to the the GET member function and make sure we receive
		// the proper response
		
		// Now this will be the way I access the credentials of the particular 
		// instance we are testing on, there is a more efficient way but I'll wait
		// for when Stephen sees this and then he'll fuss at me.
		$host = readConfigFile()['host'];
		$user = readConfigFile()['user'];
		$pass = readConfigFile()['pass'];
		$port = readConfigFile()['port'];
		$apikey = readConfigFile()['apikey'];
		
		$response = $curl->GET($host . ':' . $port . '/api/users/' . '?key=' . $apikey);
		// By default the host will be the first entry so I'll run an assertEquals.
		
    $this->assertEquals($user, $response[0]['username']);
		
	}
	
	/**
	 * Uses the curl POST to place data on the server.
	 * 
	 * In our case we will test the user api and make sure that we POST there
	 * correctly. 
	 * The subsequent function will delete the user we create here.
	 */
	public function testPOST() {
		$curl = new RESTManager();
		$host = readConfigFile()['host'];
		$user = readConfigFile()['user'];
		$pass = readConfigFile()['pass'];
		$port = readConfigFile()['port'];
		$apikey = readConfigFile()['apikey'];
		$i = 0;
		// This one will only be slightly tricky as we are to make sure we can 
		// make a simply post into our instance.
		
		// Seeing that we'll be the administrator I'll create a dummy user
		// and then make sure the POST happened that's where the assertTrue will
		// happen.
    
		// TODO: Uncomment these after the DELETE has been employed so then we do
		// have an extra user floating around on the given galaxy instance
		/** $input = array ('username' => "phpunittestuser", 'email' => "phpunitTestUser@mail.com", 'password' => "phpunitTestUserPass");
		 * $success = $curl->POST($host . ':' . $port . '/api/users/' . '?key=' . $apikey, $input);
		 */
		// Now we check to see if the user we just posted to is in fact there.
		// We'll run a GET (assuming it has done its job in working)
		
		$response = $curl->GET($host . ':' . $port . '/api/users/' . '?key=' . $apikey);

		// $response[$i] to iterate through each user that is to be found
		// a little sloppy so we'll see what Stephen has to say
		while (array_key_exists('username', $response[$i])){
			
			if("phpunittestuser" == $response[$i]['username']){
				break;
			}
			$i++;
		}
		// When we break we either have found phpunittestuser or we have not and 
		// our POST has failed and we are at the last user
		$this->assertEquals('phpunittestuser', $response[$i]['username']);
				
	}
	
	/**
	 * Uses the curl DELETE to remove data from the server.
	 * 
	 * I do not think the user will be removed as much as the user being simply
	 * having a field marked as 'deleted' and removed from view, we shall see.
	 * 
	 * I do think there is a traditional way of removing a user as I could not
	 * find one through the admin ui in my galaxy instance, I did a little 
	 * skimming on the galaxy ini but I might check again if this does not
	 * go well
	 */
	public function testDELETE(){
		$curl = new RESTManager();
		$host = readConfigFile()['host'];
		$user = readConfigFile()['user'];
		$pass = readConfigFile()['pass'];
		$port = readConfigFile()['port'];
		$apikey = readConfigFile()['apikey'];
		
		$input = array ('id' => "1cd8e2f6b131e891");
		$response = $curl->DELETE($host . ':' . $port . '/api/users/' . '1cd8e2f6b131e891' . '?key=' . $apikey);
		
		//var_dump($curl->getError());
		var_dump($response);
	}

}