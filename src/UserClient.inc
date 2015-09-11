<?php 
class UserClient{
	private $debug = True;
	private $galaxy = NULL;

	function __construct($galaxy) {
		$this->galaxy = $galaxy;
	}

	/*
	 * Creates new galaxy user
	 * For this method to work, the Galaxy instance must have the allow_user_creation
	 * option set to True and use_remote_user option set to False in the
	 * config/galaxy.ini configuration file.
	 */
	function create_local_user($username, $user_email, $password) {
		//POST /api/users

		$url = $this->galaxy->getURL() . '/api/users'. "?key=" . $this->galaxy->getAPIKey();
		//print $this->galaxy->getAPIKey();
		$ch = curl_init();

		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_POST, 3);
		curl_setopt($ch, CURLOPT_POSTFIELDS,
				http_build_query(array(
						'username' => $username,
						'email' => $user_email,
						'password' => $password,
				)));
		$message = '';
		// receive server response ...
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		print curl_exec($ch);
		if(False)
		{
			$message = 'Curl error: ' . curl_error($ch);
		}else {
			$message = $ch;
			var_dump($message);
		}
		curl_close ($ch);
		return $message;
	}

}


?>