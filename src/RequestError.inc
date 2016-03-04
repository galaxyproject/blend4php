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
   * @ingroup request_error_class
   */
  public function __construct() {
    $errorMessage = "No Error has occured";
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
  public function getError() {
    return array(
      'message' => $this->errorMessage,
      'type' => $this->errorType
     );
  }

}

