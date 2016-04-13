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
 * @defgroup request_error_class RequestError
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
   * @return
   *   An instance of a Request Error object.
   *
   * 
   */
  public function __construct() {
    $errorMessage = "No Error has occured";
  }



  /**
   * Setter for the class's 'Error' attribute
   *
   * @param $type
   *   Type of Error.  Typical types are 'HTTP' or 'Galaxy'.
   * @param $message
   *   The Error message.
   *
   * 
   */
  public function setError($type, $message) {
    $this->errorMessage = $message;
    $this->errorType = $type;
  }

  /**
   * Getter for this class's 'Error message' attribute.
   *
   * @return
   *   The error message of the objet.
   *
   * 
   */
  public function getError() {
    return array(
      'message' => $this->errorMessage,
      'type' => $this->errorType
    );
  }

}

