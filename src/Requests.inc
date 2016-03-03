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

require_once "GalaxyInstance.inc";
require_once 'HTTPRequest.inc';

class Requests {
	private $galaxy = NULL;
	// A variable to set to true if debugging, Toggles print statements
	private $debug = True;

	/**
	 * The Request constructor.
	 *
	 * @return
	 *   An instance of a Request object.
	 *
	 * @ingroup request_class
	 */
	function __construct($galaxy) {
		$this->galaxy = $galaxy;
	}

	/**
	 * Displays a collection (list) of sequencing requests.
	 *
	 * @return
	 *   JSON array of the server response.
	 *
	 * @ingroup request_class
	 */
	public function index (){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();

		$url = $this->galaxy->getURL() . '/api/requests' .  '?key=' . $api_key;

		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);

		$result = curl_exec($i);

		$info = curl_getinfo($i);

		$array = json_decode($result, true);

		print_r ($array);

		curl_close($i);
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
	 *   JSON array containing detailed information about the requested
	 *   galaxy entitiy.
	 *
	 * @ingroup request_class
	 */
	public function show ($encoded_request_id){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();

		$url = $this->galaxy->getURL() . '/api/requests' .  '?key=' . $api_key . $encoded_request_id;

		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);

		$result = curl_exec($i);

		$info = curl_getinfo($i);

		$array = json_decode($result, true);

		print_r ($array);

		curl_close($i);

	}

	/**
	 * Updates a sepcified Galaxy entity.
	 *
	 * @param $encoded_request_id
	 *   The id of the galaxy entity to update.
	 *
	 * @return
	 *   JSON object containing information on the updated Galaxy entity.
	 *
	 * @ingroup request_class
	 */
	public function update ($encoded_request_id){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();

		$url = $this->galaxy->getURL() . '/api/requests' .  '?key=' . $api_key . $encoded_request_id;

		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);

		$result = curl_exec($i);

		$info = curl_getinfo($i);

		$array = json_decode($result, true);

		print_r ($array);

		curl_close($i);


	}
}

?>