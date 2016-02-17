<?php

/**
 * @file
 *
 * The GalaxyInstance class.
 *
 * The GalaxyInstance class is used to connect to a remote Galaxy server.
 * It authenticates and maintains the API key for the user.  The functions
 * in this class correspond to the Galaxy API functions and are named similarly
 * to their Python counterpart.
 */

/**
 * @defgroup galaxy_instance_class GalaxyInstance Class
 * @{
 *   The GalaxyInstance class is used to connect to a remote Galaxy server.
 *   It authenticates and maintains the API key for the user.  The functions
 *   in this class correspond to the Galaxy API functions and are named
 *   similarly to their Python counterpart.
 * @}
 */

class GalaxyInstance {
  // The hostname where the Galaxy server is located.
  private $host;
  // The port on which the remote Galaxy instance is runinng.
  private $port;
  // Should be set to TRUE if the remote server uses HTTPS.
  private $use_https;
  // The API Key for the user connection.
  private $api_key;

  /**
   * The GalaxyInstance constructor.
   *
   * @param $hostname
   *   The hostname where the Galaxy server is located.
   * @param $port
   *   The port on which the remote Galaxy instance is runinng.
   * @param $use_https
   *   Should be set to TRUE if the remote server uses HTTPS. Defaults
   *   to TRUE.
   *
   * @return
   *   An instance of a GalaxyInstance object.
   *
   * @ingroup galaxy_instance_class
   */
  function __construct($hostname, $port, $use_https = FALSE) {
    $this->host = $hostname;
    $this->port = $port;
    $this->use_https  = $use_https;
  }

  /**
   * Verify that the server hosting the galaxy service is live.
   *
   * This check is performed by connecting to the hostname and port to see
   * if a response is recieved.
   *
   * @return
   *   TRUE if a connection is succesfully established and FALSE otherwise.
   *
   * @ingroup galaxy_instance_class
   */
  public function checkConnection() {

    // Use curl to check the connection.
    $curl = curl_init();
    $url = $this->getURL();
    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
    $output = curl_exec($curl);

    // If curl failed to connect, the output will be NULL.
    if ($output == NULL) {
      return FALSE;
    }
    else {
      return TRUE;
    }
  }

  /**
   * Authenticates a user with the remote Galaxy instance.
   *
   * Corresponds to the Galaxy API method and path:
   * GET /api/authenticate/baseauth
   *
   * @param $username
   *   The username of the user.
   * @param $password
   *   The password for the user.
   * @param $message
   *   If authentication fails then this variable will be set to contain
   *   the error message.
   *
   * @return
   *   TRUE if authentication was successful, FALSE otherwise.
   *
   * @ingroup galaxy_instance_class
   */
  public function authenticate($username, $password, &$message = '') {

    // Instantiate the curl object.
    $curl = curl_init();

    // Set the curl options for this API call.
    curl_setopt($curl, CURLOPT_URL, $this->getURL() . '/api/authenticate/baseauth');
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($curl, CURLOPT_USERPWD, $username . ':' . $password);

    // Execute the connection.
    $output = curl_exec($curl);
    $curl_error = curl_error($curl);
    curl_close($curl);

    // Case 1: If the curl_exec function returns FALSE then there was some sort
    // of curl error not related to an incorrect authentication.
    if ($output === FALSE) {
      $message = "ERROR: $curl_error";
      return FALSE;
    }

    // Case 2: If the curl_exec function did return but has no output then
    // authentication failed.
    $output = json_decode($output, true);
    if ($output === NULL or !array_key_exists('api_key', $output)) {
      $message = "ERROR: Invalid user name or password.";
      return FALSE;
    }

    // Case 3: the authentication was successful.  Set the API Key for this
    // user.
    $api_key = $output['api_key'];
    $this->setAPIKey($api_key);

    return TRUE;
  }

  /**
   * Returns the URL for the remote Galaxy server.
   *
   * The URL returned will include the protocol (HTTP, HTTPS),
   * the hostname and the port.
   *
   * @return string
   *   The URL for the remote Galaxy instance.
   *
   * @ingroup galaxy_instance_class
   */
  public function getURL() {
    if ($this->use_https) {
      return "https://". $this->host .":". $this->port;
    }
    else {
      return "http://". $this->host .":". $this->port;
    }
  }

  /**
   * Sets the API Key for this Galaxy instance.
   *
   * @param $api_key
   *   The API key of the Galaxy user.
   *
   * @ingroup galaxy_instance_class
   */
  public function setAPIKey($api_key) {
    $this->api_key = $api_key;
  }

  /**
   * Acquires the API key
   *
   * @return string
   *    The API key that authorizes a user to certain actions.
   *
   * @ingroup galaxy_instance_class
   */
  public function getAPIKey(){
    return $this->api_key;
  }
}
