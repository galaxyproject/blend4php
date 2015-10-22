<?php
/**
 * Here a lies a class responsible for distributing the appropriat rest commands for the galaxy functionality
 * 
 */

class RESTManager{
	
	/**
	 * Constructor, does anythign need to be here? 
	 */
	public 	function __construct() {
		
	}
	
	/**
	 * Universal POST request
	 *
	 * @param array Input
	 * @param str url
	 *
	 *@return curl server response
	 */
	public function GET($URL){
		$ch = curl_init();
		curl_setopt($ch,CURLOPT_URL,$URL);
		curl_setopt($ch,CURLOPT_RETURNTRANSFER,True);	
		$output = curl_exec($ch);	
		if($output === FALSE) {
			return 'A Curl error has occured: ' . curl_error($ch);
		}		
		curl_close($ch);
		
		return $output;
	}
	
	/**
	* Universal POST request
	*
	* @param array Input
	* @param str url
	*
	*@return curl server response
	*/
	public function POST($URL, $input){
		$ch = curl_init();	
		curl_setopt($ch, CURLOPT_URL, $URL);
		curl_setopt($ch, CURLOPT_POST,1);
		curl_setopt($ch, CURLOPT_POSTFIELDS,http_build_query($input));
		$message = '';
		// receive server response ...
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, True);
		$message = curl_exec($ch);			
		if($message === FALSE) {
			
			return 'A Curl Error has occured: ' . curl_error($ch);
		}
		curl_close($ch);
		return $message;		
	}
	
	/**
	* Universal PUT request
	* 
	* @param array Input
	* @param str url
	* 
	* @return curl server response 
	*/
	public function PUT($URL, $input){
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $URL);
		curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_setopt($ch, CURLOPT_POSTFIELDS,http_build_query($input));
		$message = '';
		// receive server response ...
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, True);
		$message = curl_exec($ch);
		if($message === FALSE) {
				
			return 'A Curl Error has occured: ' . curl_error($ch);
		}
		curl_close($ch);
		return $message;
		
	}
	
	
	/**
	 * Universal POST request
	 *
	 * @param array Input
	 * @param str url
	 *
	 *@return curl server response
	 */
	
	public function Delete($URL){
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $URL);
		curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "DELETE");
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, True);
		$message = curl_exec($ch);
		if($message === FALSE) {
				
			return 'A Curl Error has occured: ' . curl_error($ch);
		}
		curl_close($ch);
		return $message;
		
	}
	
	
	
}



?>