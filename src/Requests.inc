<?php

require_once "GalaxyInstance.inc";
require_once 'GalaxyRequest.inc';

class Requests{
	private $galaxy = NULL;
	// A variable to set to true if debugging, Toggles print statements
	private $debug = True;
	
	/**
	 * Implements the constructor.
	 *
	 * @param GalaxyInstance $galaxy
	 */
	function __construct($galaxy) {
		$this->galaxy = $galaxy;
	}
	
	/**
	 * Displays a collection (list) of sequencing requests.
	 *
	 * GET /api/requests
	 *
	 */
	public function index (){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();
		
		$url = $this->galaxy->getURL() . '/api/requests' .  '?key=' . $api_key;
		
		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
		
		$result = curl_exec($i);
			
		$info = curl_getinfo($i);
			
		$array = json_decode($result, true);
		
		print_r ($array);
			
		curl_close($i);
	}
	
	/**
	 * Displays details of a sequencing request.
	 *
	 * GET /api/requests/{encoded_request_id}
	 *
	 */
	public function show ($encoded_request_id){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();
		
		$url = $this->galaxy->getURL() . '/api/requests' .  '?key=' . $api_key . $encoded_request_id;
		
		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
		
		$result = curl_exec($i);
			
		$info = curl_getinfo($i);
			
		$array = json_decode($result, true);
		
		print_r ($array);
			
		curl_close($i);
		
	}
	
	public function update ($encoded_request_id){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();
		
		$url = $this->galaxy->getURL() . '/api/requests' .  '?key=' . $api_key . $encoded_request_id;
		
		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
		
		$result = curl_exec($i);
			
		$info = curl_getinfo($i);
			
		$array = json_decode($result, true);
		
		print_r ($array);
			
		curl_close($i);
		
		
	}
}

?>