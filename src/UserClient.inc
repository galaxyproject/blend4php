<?php 
class UserClient{
	private $debug = True;
	private $galaxy = NULL;

	function __construct($galaxy) {
		$this->galaxy = $galaxy;
	}
	
	
	function create_user_apikey($username) {
		// POST /api/users/{encoded_user_id}/api_key
		$user_id = $this->obtain_user_id($username);
		if($user_id === FALSE) {
			return "Error obtianing user id, have you entered the correct username?";
		}

		$url = $this->galaxy->getURL() . '/api/users/'. $user_id ."/api_key/?key=" . $this->galaxy->getAPIKey();
		$ch = curl_init();
		
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_POST, 1);
		$message = curl_exec($ch);
		
		if($message === FALSE) {
			print 'Curl error: ' . curl_error($ch);
		}
			
		
			return $message;
	}
	
	
	
	/*
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

	
	/*
	 * Creates new galaxy user
	 * For this method to work, the Galaxy instance must have the allow_user_creation
	 * option set to True and use_remote_user option set to False in the
	 * config/galaxy.ini configuration file.
	 */
	function create_local_user($username, $user_email, $password) {
<<<<<<< HEAD
		//POST /api/users

		$url = $this->galaxy->getURL() . '/api/users'. "?key=" . $this->galaxy->getAPIKey();
		//print $this->galaxy->getAPIKey();
		$ch = curl_init();

		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_POST, 1);
		curl_setopt($ch, CURLOPT_POSTFIELDS,
				http_build_query(array(
						'username' => $username,
						'email' => $user_email,
						'password' => $password,
				)));
		$message = '';
		// receive server response ...
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		
		if($this->debug){
			print curl_exec($ch);
		}else // Do not print if not in debug mode 
		{
			curl_exec($ch);
		}
=======
		//POST /api/users 
		if($debug)
		print ("Im on line 19"); // That's a lie! @author cwytko

		
		$data = array(
			'username' => $username,
			'email' => $user_email,
			'password'=> $password,			
		);
		
		$opts = array(
			'http' => array(
				'headers' => ''	,
				'method'  => 'POST',
				'content' => http_build_query($data),
				'timeout' => 60
			)
		);
		if($debug) 
		print ("Im on line 35");
		
		$context  = stream_context_create($opts);
		$url = $this->galaxy->getURL() . '/api/users';
		
		if($debug)
		print ("Im on line 36");
		$result = file_get_contents($url, false, $context);
		
		return $result; 
	}
	
>>>>>>> ea6b15b3dac2194bec4303a973f0dd4054cbb0c9
		
		if($ch === FALSE)
		{
			$message = 'Curl error: ' . curl_error($ch);
		}else {
			$message = $ch;
		}
		curl_close ($ch);
		return $message;
	}
}


?>