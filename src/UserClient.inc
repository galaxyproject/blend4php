<?php 
class UserClient{

	private $debug = True; 
	private $galaxy = NULL;
	
	function __construct(GalaxyInstance $galaxy) {
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
	
		
}


?>