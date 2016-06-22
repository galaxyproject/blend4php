<?php
class GalaxyError {
  // Global Variable that contains any errors received from a rest request.
  private $error = array(
    'type' => '',
    'message' => '',
  );

  /**
   * Constructor.
   */
  public function __construct() {

  }
  /**
   * Retrieves the most recent error.
   *
   * The error message uses the key 'message' and the type uses the key 'type'.
   * The following is a list of error types and their meaning:
   *
   *   - API:  The blend4php API functions have been improperly used
   *   - Galaxy:  The Galaxy server indicated an error.
   *   - HTTP:  An error occured using the REST HTTP protocols (e.g. PUT, POST,
   *       GET, PATCH, DELETE).
   *   - FILE: An error occured saving a download file from Galaxy.
   *
   * @return
   *   An associative array containing both the 'type' and 'message' for the
   *   error.
   */
  public function getError() {
    return $this->error;
  }

  /**
   * Retrieves the most recent error message.
   *
   * @return
   *   A string containing the error message.
   */
  public function getErrorMessage() {
    return $this->error['type'] . ' error. ' . $this->error['message'];
  }
  /**
   * Retrieves the most recent error type.
   *
   * The following is a list of error types and their meaning:
   *
   *   - API:  The blend4php API functions have been improperly used
   *   - Galaxy:  The Galaxy server indicated an error.
   *   - HTTP:  An error occured using the REST HTTP protocols (e.g. PUT, POST,
   *       GET, PATCH, DELETE).
   *   - FILE: An error occured saving a download file from Galaxy.
   *
   * @return
   *   A string indicating the type of error.
   */
  public function getErrorType() {
    $error = $this->error['type'];
  }

  /**
   * Set's the error type and message.
   *
   * The following is a list of error types and their meaning:
   *
   *   - API:  The blend4php API functions have been improperly used
   *   - Galaxy:  The Galaxy server indicated an error.
   *   - HTTP:  An error occured using the REST HTTP protocols (e.g. PUT, POST,
   *       GET, PATCH, DELETE).
   *   - FILE: An error occured saving a download file from Galaxy.
   *
   * @param $type
   *   The type of error.
   * @param $message
   *   The error message.
   */
  public function setError($type, $message) {
    $this->error = array(
      'type' => $type,
      'message' => $message,
    );
  }
}