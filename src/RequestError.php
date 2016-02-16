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
   * @param $message
   *   curl response from galaxy page $message
   * @return
   *   TRUE if error was found, FALSE otherwise.
   */
  public function parseCURLError($message) {
    $newMessage = '';
    // print $message;
    // If we have a traceback element, we know the error originated from python,
    // meaning the Request successfully made it to python.
    if (strpos($message, 'traceback') !== FALSE) {

      if (strpos($message, 'err_msg') !== FALSE) {
        $newMessage = substr($message, strpos($message, 'err_msg'));
        $this->setError('Galaxy', $newMessage);
        return TRUE;
      }
      else {
        // WARNING: is it possible for there to be a 'traceback and no 'err_msg?
        // If so we will need to define a more elaborate way to check for traceback err messages
        $newMessage = 'A galaxy error was detected, though its contents are unkown';
        $this->setError('Galaxy', $newMessage);
        return TRUE;
      }
    }
    else if (strpos($message, 'error') !== FALSE) {
      $message = json_decode($message, TRUE);

      if ($message !== NULL) {

        if (array_key_exists('error', $message)) {
          $message = $message['error'];
          $newMessage = $message;
          $this->setError('Galaxy', $newMessage);
          return TRUE;
        }
        else {
          return FALSE;
        }
      }
      else {
        $this->setError('Galaxy', 'unkown error encountered, error not json compatible');
        return TRUE;
      }
    }

    return FALSE;
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
    if ($type = 'HTTP' or $type = 'Galaxy') {
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

