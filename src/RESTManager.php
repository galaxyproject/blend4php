<?php
require_once 'RequestError.php';
/**
 * Here a lies a class responsible for distributing the appropriat rest commands for the galaxy functionality
 *
 */

class RESTManager {

private $requestError = NULL;	

  public   function __construct($requestError = NULL) {
	if($requestError !==NULL){ $this->requestError = $requestError; }
	else { $this->requestError = new RequestError(); }
  }

  /**
   * Universal GET request
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
    $this->requestError->set_RequestError('HTTP', curl_error($ch));  
    return FALSE;  
    }   
    curl_close($ch);
    
   if( $this->requestError->look_for_error($output) ) {
   	$output = FALSE;
   }

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
  public function POST($URL, $input = NULL){
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $URL);
    curl_setopt($ch, CURLOPT_POST,1);
    if($input !==NULL)
    {
    curl_setopt($ch, CURLOPT_POSTFIELDS,http_build_query($input));
    }
    $message = '';
    // receive server response ...
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, True);
    $message = curl_exec($ch);
    curl_close($ch);
    if($message === FALSE) {
     $this->requestError->set_RequestError('HTTP', curl_error($ch));
      return FALSE;
    } 
    
    if( $this->requestError->look_for_error($message) ) {
    	return FALSE;
    }
    
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
  public function PUT($URL, $input=NULL){
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $URL);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
    if($input !=NULL) {
    curl_setopt($ch, CURLOPT_POSTFIELDS,http_build_query($input));
    }
    $message = '';
    // receive server response ...
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, True);
    $message = curl_exec($ch);
    if($message === FALSE) {
      $this->requestError->set_RequestError('HTTP', curl_error($ch));
      return FALSE;
    }
    curl_close($ch);
    
    if( $this->requestError->look_for_error($message) ) {
    	$message = FALSE;
    }
    
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
      $this->requestError->set_RequestError('HTTP', curl_error($ch));
      return FALSE;
    }
    curl_close($ch);
    
    if( $this->requestError->look_for_error($message) ) {
    	$message = FALSE;
    }
    
    return $message;
  }
  
  /**
   * @return string error message from the server or CURL 
   */
  public function getError(){
  	return $this->requestError->getErrorMessage();
  }
  
 /**
  * @return string error rtype either 'HTTP' or 'Galaxy' 
  */
  public function getErrorType(){
  	return $this->requestError->getErrorType();
  }

}



?>