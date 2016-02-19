<?php
/**
 *
 * RequestError: A class dedicated to relaying error information given from a
 * curl server response
 *
 */
class RequestError {

  private $errorMessage = '';

  // Either 'Galaxy or HTTP
  private $errorType = '';

  /**
   */
  public function __construct() {
    $errorMessage = "No Error has occured";
  }

  /**
   * Set the error for this class by extracting from the CURL response.
   *
   * @param $response
   *   curl response from galaxy page $message
   * @return
   *   TRUE if error was found, FALSE otherwise.
   */
  public function parseCURLResponse($response) {
  	print "\n\n\n";
  	var_dump($response);
  	print "\n\n\n";
  	$response = json_decode($response, TRUE);
  	
  	// Case 1:  There message is not in JSON format.
  	if ($response == NULL) {
  		$this->setError('Galaxy', 'Unknown CURL response: not json compatible.');
  		return FALSE;
  	}	
    
    // Case 2: If we have a traceback element, we know the error originated 
    // from python, meaning the request successfully made it to python but 
    // there is ap problemo in the Galaxy code.
    if (array_key_exists('traceback', $response)) {
    	// Case 2a: The traceback had an error message.
    	if (array_key_exists('err_msg', $response)) {
        $this->setError('Galaxy', $response['err_msg']);
        return FALSE;
      }
      // Case 2b: The traceback did not have an error.
      else {
        $this->setError('Galaxy', 'A galaxy error was detected, though its contents are unkown');
        return FALSE;
      }
    }
    // Case 3: Galaxy generated the error.
    else if (array_key_exists('error', $response)) {
      $this->setError('Galaxy', $response['error']);
      return FALSE;
    }

    // Case 4:  No error found.
    
    return $response;
  }

  /**
   * In order to set the request error, both the type and message must be known.
   *
   * @param $type
   * @param $message
   * @return
   *
   */
  public function setError($type, $message) {
    $this->errorMessage = $message;
    // Assure that the type is either HTTP or Galaxy
    if ($type == 'HTTP' or $type == 'Galaxy') {
      $this->errorType = $type;
    }
    else {
      $this->$type = 'Galaxy';
    }
  }

  /**
   *
   * @return
   */
  public function getErrorMessage() {
    return $this->errorMessage;
  }

  /**
   *
   * @return
   */
  public function getErrorType() {
    return $this->errorType;
  }
}

