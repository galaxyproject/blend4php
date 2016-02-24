<?php
/**
 * @file 
 *
 * RequestError
 * 
 * The Request Error class dedicated to relaying error information given from a
 * curl server response. Note that each instance of the Request Error class 
 * contains at most one error.
 * 
 * @defgroup request_error_class 
 * @{
 *   The Request Error class dedicated to relaying error information given from a
 *    curl server response.
 * @}
 */

class RequestError {

  private $errorMessage = '';

  // Either 'Galaxy or HTTP
  private $errorType = '';
  
  /**
   * The Request Error constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Request Error object.
   *
   * @ingroup request_error_class
   */
  public function __construct() {
    $errorMessage = "No Error has occured";
  }

  /**
   * Set the error for this class by extracting from the given CURL response.
   *
   * @param $response
   *   curl response from galaxy page $message.
   *   
   * @return
   *   TRUE if error was found, FALSE otherwise.
   *   
   * @ingroup request_error_class
   */
  public function parseCURLResponse($response) {

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
   * Setter for the class's 'Error' attribute
   *
   * @param $type
   *   Type of Error, must be either 'HTTP' or 'Galaxy'.
   * @param $message
   *   The Error message.
   *   
   * @ingroup request_error_class
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
   * Getter for this class's 'Error message' attribute.
   * 
   * @return
   *   The error message of the objet.
   *   
   * @ingroup request_error_class
   */
  public function getErrorMessage() {
    return $this->errorMessage;
  }

  /**
   * Getter for this object's error type.
   *
   * @return 
   *   The rror type of this object's 'Error'.
   */
  public function getErrorType() {
    return $this->errorType;
  }
}

