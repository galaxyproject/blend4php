<?php
/**
 * @file
 *
 * Request
 *
 * A class Built to manage basic Galaxy REST request options.
 *
 * @defgroup request_class Request
 * @{
 * A class Built to manage basic Galaxy REST request options.
 * @}
 */

class GalaxyRequests {

  private $galaxy = NULL;

  /**
   * The Request constructor.
   *
   * @return
   *   An instance of a Request object.
   *
   *
   */
  function __construct($galaxy) {
    $this->galaxy = $galaxy;
  }

  /**
   * Displays a collection (list) of sequencing requests.
   *
   * @return
   *   An array of the requests.
   *
   *
   */
  public function index (){
    $api_key = $this->galaxy->getAPIKey();
    $URL = $this->galaxy->getURL() . '/api/requests' .  '?key=' . $api_key;

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Displays details of a sequencing request.
   *
   * GET /api/requests/{encoded_request_id}
   *
   * @param encoded_request_id
   *   The id of the galaxy entity to show.
   *
   * @return
   *   An array containing detailed information about the requested
   *   galaxy entitiy.
   *
   *
   */
  public function show($encoded_request_id){
    $api_key = $this->galaxy->getAPIKey();

    $URL = $this->galaxy->getURL() . '/api/requests' .  '?key=' . $api_key . $encoded_request_id;

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);

  }

  /**
   * Updates a request state, sample state or sample dataset transfer status.
   *
   * @param $encoded_request_id
   *   The id of the galaxy entity to update.
   *
   * @return
   *   An array containing information on the updated Galaxy entity.
   *
   *
   */
  public function update ($encoded_request_id){
    $api_key = $this->galaxy->getAPIKey();

    $URL = $this->galaxy->getURL() . '/api/requests' .  '?key=' . $api_key . $encoded_request_id;

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);

  }
}

?>