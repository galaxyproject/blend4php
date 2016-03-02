<?php
require_once 'RequestError.inc';

/**
 * @file
 *
 * GalaxyRequest
 *
 * The RGalaxyRequest Class contains methods for using CURL rest options.
 * More specifically, UPDATE, POST, DELETE, PUT and GET.
 *
 * @defgroup rest_manager_class RestManager
 * @{
 * The Rest Manager Class contains methods for using CURL rest options.
 * More specifically, UPDATE, POST, DELETE, PUT and GET.
 * @}
 */

class GalaxyRequest  {

   // Global Variable that contains any errors received from a rest request.
   private $requestError = NULL;

   /**
    * The Rest Manager constructor.
    *
    * @param RequestError requesterror
    *   Optional, set the class's request error to a pre-existing RequestError.
    *
    * @return
    *   An instance of a RestManager class.
    *
    * @ingroup rest_manager_class
    */
   function __construct() {
     $this->requestError = new RequestError();
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
  private function parseCURLResponse($response) {

     $response = json_decode($response, TRUE);

     // Case 1:  There message is not in JSON format.
     if ($response == NULL) {
       $this->requestError->setError('Galaxy', 'Unknown CURL response: not json compatible.');
       return FALSE;
     }

     // Case 2: If we have a traceback element, we know the error originated
     // from python, meaning the request successfully made it to python but
     // there is ap problemo in the Galaxy code.
     if (array_key_exists('traceback', $response)) {
       // Case 2a: The traceback had an error message.
       if (array_key_exists('err_msg', $response)) {
         $this->requestError->setError('Galaxy', $response['err_msg']);
         return FALSE;
       }
       // Case 2b: The traceback did not have an error.
       else {
         $this->requestError->setError('Galaxy', 'A galaxy error was detected, though its contents are unknown');
         return FALSE;
       }
     }
     // Case 3: Galaxy generated the error.
     else if (array_key_exists('error', $response)) {
       $this->requestError->setError('Galaxy', $response['error']);
       return FALSE;
     }
     // Case 4: Galaxy generated the error but the message has two separate
     // components
     else if (array_key_exists('err_msg', $response)) {
       $this->requestError->setError('Galaxy', $response['err_msg']);
       return FALSE;
     }

     // Case 4:  No error found.
     return $response;
  }

  /**
   * Performs a GET request.
   *
   * @param url
   *   The URL to perform the GET request on.
   *
   * @return
   *   curl server response.
   *
   * @ingroup rest_manager_class
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

    return $this->parseCURLResponse($output);
  }

  /**
   * Perform a POST request.
   *
   * @param Input
   *   The input data to a given URL.
   * @param URL
   *   The url to perform the POST request on.
   *
   * @return
   *   curl server response.
   *
   * @ingroup rest_manager_class
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


    return $this->parseCURLResponse($message);
  }

  /**
   * Perform a PUT request
   *
   * @param URL
   *   The URL to perform the PUT request on.
   * @param Input
   *   The input data to give to the URL.
   *
   * @return
   *   curl server response.
   *
   * @ingroup rest_manager_class
   */
  public function PUT($URL, $input = NULL) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $URL);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
    if ($input != NULL) {
      http_build_query($input);
      curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($input));
    }
    $message = '';

    $message = curl_exec($ch);
    // print "server response: " .$message;
    if ($message === FALSE) {
      $this->requestError->setError('HTTP', curl_error($ch));
      return FALSE;
    }
    curl_close($ch);

    return $this->parseCURLResponse($message);
  }

  /**
   * Universal DELETE request
   *
   * @param $input
   *   The input data to give to the url.
   * @param $URL
   *   The path to perform the DELETE request.
   *
   * @return
   *   curl server response
   *
   * @ingroup rest_manager_class
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

    return $this->parseCURLResponse($message);
  }

  /**
   *
   * @param unknown $URL
   * @param unknown $username
   * @param unknown $password
   */
  public function AUTH($URL, $username, $password) {
    // Instantiate the curl object.
    $ch = curl_init();

    // Set the curl options for this API call.
    curl_setopt($ch, CURLOPT_URL, $URL);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_USERPWD, $username . ':' . $password);

    // Execute the connection.
    $message = curl_exec($ch);
    if ($message === FALSE) {
      $this->requestError->setError('HTTP', curl_error($ch));
      return FALSE;
    }
    curl_close($ch);

    return $this->parseCURLResponse($message);
  }

  /**
   *
   * @return
   *   string error message from the server or CURL.
   *
   * @ingroup rest_manager_class
   */
  public function getError() {
    return $this->requestError->getErrorMessage();
  }

  /**
   *
   * @return
   *   string error rtype either 'HTTP' or 'Galaxy'.
   *
   * @ingroup rest_manager_class
   */
  public function getErrorType() {
    return $this->requestError->getErrorType();
  }
}

?>