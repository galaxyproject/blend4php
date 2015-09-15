<?php

/*
Update (09/01):
The function file_get_contents does not appear to be working with the  
$url = 'http://localhost:8080/api/authenticate/baseauth'; 
despite the fact that manual input of this url into the browser retrieves data 
and the function retrieves data from $url = “localhost:8080” 
(implying there is no issue with locating the port). 
The terminal states the error is: 
HTTP request failed! HTTP/1.0 404 Not Found and apache 2 error log reads: 
Invalid method in request Get /api/authenticate/baseauth HTTP/1.0
*/

Class Authenticate {
	public $opts = NULL;
	public function __construct() {
		
	}
		
	public function obtainKey($username, $password) {
		// Temporary username and password of an already existing admin user
		$username = 'xx1brian1xx@yahoo.com';
		$password = 'crabical1';		

		//$body = 'TODO';
		 $opts = array('http' =>
			array(
			  'method'  => 'GET',
			  'header'  => "Authorization: Basic " . base64_encode("$username:$password"),
			  'content' => '',
			  'timeout' => 60, 				
			),
		);
		 
		$context  = stream_context_create($opts);
		$url = 'http://'. "127.0.0.1:8080/api/authenticate/baseauth";
		//$url = 'http://localhost:8080';
		//$url = 'http://localhost:8080/api/authenticate/baseauth';
		$result = file_get_contents($url, false, $context, -1, 1000);
		//$url = 'localhost:8080';
		//$result = file_get_contents($url);
		
		return $result;
	}
		
}// end class 

// Temporary test functionality 
$authy = new Authenticate();
print $authy->obtainKey('blah', 'weee');



?>