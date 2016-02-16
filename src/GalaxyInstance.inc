<?php


/**
 *
 */
class GalaxyInstance {
  // The hostname where the Galaxy server is located.
  private $host;
  // The port on which the remote Galaxy instance is runinng.
  private $port;
  // Should be set to TRUE if the remote server uses HTTPS.
  private $use_https;
  //  The API Key for the user connection.
  private $api_key;

  private $debug = true;

  /**
   * Implements the constructor.
   *
   * @param $hostname
   *   The hostname where the Galaxy server is located.
   * @param $port
   *   The port on which the remote Galaxy instance is runinng.
   * @param $use_https
   *   Should be set to TRUE if the remote server uses HTTPS. Defaults
   *   to TRUE.
   * @return Galaxy
   *
   */
  function __construct($hostname, $port, $use_https = FALSE) {
    $this->host = $hostname;
    $this->port = $port;
    $this->use_https  = $use_https;

  }

  /**
   * Verify that the server hosting the galaxy services is live.
   *
   * @return
   *   TRUE if a connection is succesfully established and FALSE otherwise.
   */
  public function checkConnection() {

    $ch = curl_init();
    $url = $this->getURL();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    $output = curl_exec($ch);

    if ($output == NULL)
      return FALSE;
    else
      return TRUE;
  }

  /**
   * Authenticates a user with the remote Galaxy instance.
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
   */
  public function authenticate($username, $password, &$message = '') {

    $i = curl_init();

    curl_setopt($i, CURLOPT_URL, $this->getURL() . '/api/authenticate/baseauth');
    curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($i, CURLOPT_USERPWD, $username . ':' . $password);

    $output = curl_exec($i);

    if ($output === FALSE) {
        $output = "invalidusernameorpassword";
      $message = "ERROR: " . curl_error($i);
      return FALSE;
    }

    $output = json_decode($output, true);
    if ($output === NULL or !array_key_exists('api_key', $output)) {
      $output = "invalidusernameorpassword";
      $message = "ERROR: Invalid Username or Password";
      return FALSE;
    }
    $output = $output['api_key'];
    $this->api_key = $output;

    curl_close($i);
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
   * @param string $api_key
   */
  public function setAPIKey($api_key) {
    $this->api_key = $api_key;
  }

  /**
   * Acquires the API key
   * @return string
   *    The API key that authorizes a user to certain actions
   */
  public function getAPIKey(){
    return $this->api_key;
  }
}
