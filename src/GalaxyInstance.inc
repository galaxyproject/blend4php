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

require_once 'HTTPRequest.inc';

class GalaxyInstance extends HTTPRequest {
  // The hostname where the Galaxy server is located.
  protected $host;
  // The port on which the remote Galaxy instance is runinng.
  protected $port;
  // Should be set to TRUE if the remote server uses HTTPS.
  protected $use_https;
  // The API Key for the user connection.
  protected $api_key;

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

    parent::__construct();
  }

  /**
   * Retrieves the version of the Galaxy API.
   *
   * @return
   *
   *
   * @ingroup galaxy_instance_class
   */
  public function getVersion() {
    return $this->httpGET($this->getURL() . '/api/version');
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

    // First just try to get the version.  If not, then this means
    // Galaxy may not be available and we should error out before trying
    // further.
    $URL = $this->getURL();
    $version = $this->getVersion();
    if (!$version) {
      $this->setError('Galaxy', "Cannot connect to Galaxy server: $URL.");
      return FALSE;
    }

    // Now try to authenticate.
    $response = $this->auth($URL . '/api/authenticate/baseauth', $username, $password);
    if (!$response) {
      return FALSE;
    }
    $this->setAPIKey($response['api_key']);

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
