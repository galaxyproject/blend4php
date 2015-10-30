<?php 
require_once 'GalaxyRequest.inc';

class Users extends GalaxyRequest{

	function __construct($galaxy) {
		parent::__construct($galaxy);
	}
	
	
	/**
	 * Accepts a user name, retuns the new api key, 
	 * Upon calling this function, the server should already have the 
	 * new api key for the user
	 * calls: 
	 * POST /api/users/{encoded_user_id}/api_key
	 */
	function create_user_apikey($username) {
		
		$user_id = $this->obtain_user_id($username);
		if($user_id === FALSE) {
			return "Error obtianing user id, have you entered the correct username?";
		}

		$URL = $this->galaxy->getURL() . '/api/users/'. $user_id ."/api_key/?key=" . $this->galaxy->getAPIKey();
		
		$this->rest->GET($URL);
		
	}
	
	/** 
	 * Shows the contents of a user based on given string username 
	 * returns a json array or error message string if not successful 
	 * calls: 
	 * GET /api/users/{encoded_user_id} GET /api/users/deleted/{encoded_user_id} GET /api/users/current
	 */
	function show_user($username) {
		
		$user_id = $this->obtain_user_id($username);
		if($user_id === FALSE) {
			return "Error obtianing user id, have you entered the correct username?";
		}
		
		$URL = $this->galaxy->getURL() . '/api/users/'. $user_id ."/api_key/?key=" . $this->galaxy->getAPIKey();
		return $this->rest->GET($URL);
	}
	
	
	
	/**
	 * Obtains the user id as a string
	 * Returns False if it encounters an issue
	 */
	function obtain_user_id($username) {
		$user_id = "";
		$ch = curl_init();
		curl_setopt_array($ch, array(
				CURLOPT_RETURNTRANSFER => 1,
				CURLOPT_URL => $this->galaxy->getURL(). '/api/users/' .'?key='. $this->galaxy->getAPIKey(),
		));
		$message = curl_exec($ch);
		if($this->debug){ 	//print $message;
		}
		if($ch === FALSE){
			print 'Curl error: ' . curl_error($ch);
			return FALSE ;
		}
		curl_close ($ch);
		
		$message = str_replace(array('[',']', " "), "", $message);
		$len = strlen($message);
		$good = FALSE;
		$current_string = "";
		// Break all the users intp json arrays, find the appropriate id
		for($i = 0; $i<= $len; $i++) {
			$char = substr($message, $i, 1);
			$current_string .= $char;
		
			// If we have reached the end of the user, time to evaluate him
			if($char == '}') {
				//print ($current_string);
				$current_string = json_decode($current_string, TRUE);
				if($current_string['username'] == $username) {
					$good = TRUE;
					$user_id = $current_string["id"];
					break;
		
				}
				// i++ to escape the comma
				$i++;
				$current_string = "";
			}
		
		}
		
		if(!$good) {
			return FALSE;
		}
		
		return $user_id;		
		
	}

	
	
	/**
	 * Creates new galaxy user using
	 * //POST /api/users
	 * For this method to work, the Galaxy instance must have the allow_user_creation
	 * option set to True and use_remote_user option set to False in the
	 * config/galaxy.ini configuration file.
	 */
	function create_local_user($username, $user_email, $password) {
		
		$URL = $this->galaxy->getURL() . '/api/users'. "?key=" . $this->galaxy->getAPIKey();

		$input = 		array(
						'username' => $username,
						'email' => $user_email,
						'password' => $password,
					);

		return $this->rest->POST($URL, $input);
	}
}


?>
