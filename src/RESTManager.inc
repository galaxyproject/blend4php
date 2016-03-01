<?php
require_once 'RequestError.inc';

/**
 * @file
 *
 * RestManager
 * 
 * The Rest Manager Class contains methods for using CURL rest options. 
 * More specifically, UPDATE, POST, DELETE, PUT and GET. 
 *
 * @defgroup rest_manager_class RestManager
 * @{
 * The Rest Manager Class contains methods for using CURL rest options. 
 * More specifically, UPDATE, POST, DELETE, PUT and GET. 
 * @}
 */

class RESTManager {
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
   public function __construct($requestError = NULL) {
     if ($requestError !==NULL) {
       $this->requestError = $requestError;
     }
     else {
       $this->requestError = new RequestError();
     }
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

    return $this->requestError->parseCURLResponse($output);
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


    return $this->requestError->parseCURLResponse($message);
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

    return $this->requestError->parseCURLResponse($message);
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