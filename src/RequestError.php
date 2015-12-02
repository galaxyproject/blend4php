<?php
/**
 * 
 * RequestError: A class dedicated to relaying error information given from a curl server response 
 *
 */

 class RequestError{
 	private $errorMessage = '';
 	
 	// Either 'Galaxy or HTTP
 	private $errorType = '';
 	
 	/**
 	 */
 	public function  __construct(){
 		$errorMessage = "No Error has occured";
 	}
 	
 	/**
 	 * scans input message to see if there are any errors. 
 	 * of the inputted $message 
 	 * @param curl response from galaxy page $message
 	 * @return bool true if error was found, false otherwise  
 	 */
 	public function look_for_error($message){
 	
 		$newMessage = ''; 
 		//print $message;
 		// If we have a traceback element, we know the error originated from python, meaning the 
 		// Request successfully made it to python 
 		if (strpos($message, 'traceback') !== false ) {
 			
 			if(strpos($message, 'err_msg') !==false ){
 				$newMessage = substr($message, strpos($message, 'err_msg')); 
 				$this->set_RequestError('Galaxy', $newMessage);
 				return True; 
 			}else {
 				//WARNING: is it possible for there to be a 'traceback and no 'err_msg?
 				// If so we will need to define a more elaborate way to check for traceback err messages
 				$newMessage = 'A galaxy error was detected, though its contents are unkown';
 				$this->set_RequestError('Galaxy', $newMessage); 
 				return True; 
 			}
 						
 		}
 		else if(strpos($message, 'error') !==false ) {
 			$message = json_decode($message,true); 
 			
 			if($message!==NULL) {
 				
 			 if(array_key_exists('error', $message)){ 
 			  $message = $message['error']; 
 			  $newMessage = $message; 
 			  $this->set_RequestError('Galaxy', $newMessage);
 			  return True;
 			  } else {
 			  	return false;
 			  }
 			 } else {
 			 	$this->set_RequestError('Galaxy', 'unkown error encountered, error not json compatible');
 			 	return True;
 			 }
 		}
 		
 		return False; 
 	}
 	
 	/**
 	 * in order to set the request error, both the type and message must be knwon 
 	 *@param $str -type
 	 *@param $str - message
 	 */
 	public function set_RequestError($type, $message){
 		$this->errorMessage = $message;
 		// Assure that the type is either HTTP or Galaxy 
 		if($type = 'HTTP' or $type = 'Galaxy') {
 		$this->errorType = $type;
 		}else { $this->$type = 'Galaxy'; } 
 	}
 	
 	public function getErrorMessage(){
 		return $this-> errorMessage;
 	}
 	
 	public function getErrorType(){
 		return $this-> errorType;
 	}
 	
	 
}

