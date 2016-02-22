<?php
require_once 'RequestError.inc';

/**
 * Here a lies a class responsible for distributing the appropriat rest commands for the galaxy functionality
 */
class RESTManager {
  private $requestError = NULL;

  public function __construct($requestError = NULL) {
    if ($requestError !==NULL) {
      $this->requestError = $requestError;
    }
    else {
      $this->requestError = new RequestError();
    }
  }

  /**
   * Universal GET request
   *
   * @param Input
   * @param url
   *
   * @return curl server response
   */
  public function GET($URL) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $URL);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, True);
    $output = curl_exec($ch);

    if ($output === FALSE) {
      $this->requestError->setError('HTTP', curl_error($ch));
      return FALSE;
    }
    curl_close($ch);

    return $this->requestError->parseCURLResponse($output);
  }

  /**
   * Universal POST request
   *
   * @param Input
   * @param url
   *
   * @return curl server response
   */
  public function POST($URL, $input = NULL) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $URL);
    curl_setopt($ch, CURLOPT_POST, 1);
    if ($input !== NULL) {
      curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($input));
      // curl_setopt($ch, CURLOPT_POSTFIELDS,$input);
    }
    $message = '';
    // print (http_build_query($input));
    // receive server response ...
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, True);
    $message = curl_exec($ch);

    if ($message === FALSE) {
      $this->requestError->setError('HTTP', curl_error($ch));
      return FALSE;
    }
    curl_close($ch);

    return $this->requestError->parseCURLResponse($message);
  }

  /**
   * Universal PUT request
   *
   * @param Input
   * @param url
   *
   * @return curl server response
   */
  public function PUT($URL, $input = NULL) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $URL);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
    if ($input != NULL) {
      print http_build_query($input);
      curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($input));
    }
    $message = '';

    $message = curl_exec($ch);
    // print "server response: " .$message;
    if ($message ===FALSE) {
      $this->requestError->setError('HTTP', curl_error($ch));
      return FALSE;
    }
    curl_close($ch);

    return $this->requestError->parseCURLResponse($message);
  }

  /**
   * Universal DELETE request
   *
   * @param $URL
   * @param $input
   *
   * @return
   *   curl server response
   */
  public function DELETE($URL, $input = NULL) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $URL);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, True);

    if ($input != NULL) {
      curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($input));
    }

    $message = curl_exec($ch);
    if ($message === FALSE) {
      $this->requestError->setError('HTTP', curl_error($ch));
      return FALSE;
    }
    curl_close($ch);

    return $this->requestError->parseCURLResponse($message);
  }

  /**
   *
   * @return string error message from the server or CURL
   */
  public function getError() {
    return $this->requestError->getErrorMessage();
  }

  /**
   *
   * @return string error rtype either 'HTTP' or 'Galaxy'
   */
  public function getErrorType() {
    return $this->requestError->getErrorType();
  }
}

?>