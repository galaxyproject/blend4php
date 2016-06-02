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
   *
   * @return
   *   string error message from the server or CURL.
   *
   *
   */
  public function getError() {
    return $this->error;
  }

  /**
   *
   * @return The
   */
  public function getErrorMessage() {
    return $this->error['type'] . ' error. ' . $this->error['message'];
  }
  /**
   *
   * @return The
   */
  public function getErrorType() {
    $error = $this->error['type'];
  }

  /**
   *
   * @param $type
   * @param $message
   */
  public function setError($type, $message) {
    $this->error = array(
      'type' => $type,
      'message' => $message,
    );
  }
}