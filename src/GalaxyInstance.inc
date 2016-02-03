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
   * Implements a constructor.
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
   * Verify that the server hosting the galaxy services is live
   * 
   */
  
	public function verifyLive(){
		$ch = curl_init ();
		curl_setopt ( $ch, CURLOPT_URL, "$this->host" . ":" . "$this->port");
		curl_setopt ( $ch, CURLOPT_RETURNTRANSFER, True );
		$output = curl_exec ( $ch );
		if ($output == NULL)
			return FALSE;
		else
			return TRUE;
	}
  
  /**
   * Authenticates a user with the remote Galaxy instance.
   *
   * @param $username
   * @param $password
   *
   *
   */
  public function authenticate($username, $password) {

    $i = curl_init();

    curl_setopt($i, CURLOPT_URL, $this->getURL() . '/api/authenticate/baseauth');
    curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($i, CURLOPT_USERPWD, $username . ':' . $password);

    $output = curl_exec($i);

    if($output === FALSE) {
      	$output = "invalidusernameorpassword";
    	return "Error: " . curl_error($i);
    }
   
    $output = json_decode($output, true);
    if($output ===NULL or !array_key_exists('api_key', $output)){
    	$output = "invalidusernameorpassword";
    	return "error";
    }
    $output = $output['api_key'];
    $this->api_key = $output;


    curl_close($i);

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
