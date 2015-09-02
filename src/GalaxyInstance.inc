<?php

/**
 * 
 */
 
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
  function __construct($hostname, $port, $use_https = TRUE) {
    $this->host = $hostname;
    $this->port = $port;
    $this->use_https  = $use_https;
  }
  
  
  /**
   * Authenticates a user with the remote Galaxy instance.
   * 
   * @param $username
   * @param $password
   */
  public function authenticate($username, $password) {
    $opts = array(
     'http' => array(
        'method'  => 'GET',
        'header'  => "Authorization: Basic " . base64_encode("$username:$password"),
        'content' => '',
        'timeout' => 60
      )
    );
  
    $context  = stream_context_create($opts);
    $url = $this->galaxy->getURL() . '/api/authenticate/baseauth';
    $result = file_get_contents($url, false, $context, -1, 40000);
    
    // TODO: make sure we get a correct result.
    $this->api_key = $result['api_key'];
    
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
   * @param unknown $api_key
   */
  public function setAPIKey($api_key) {
  	$this->api_key = $api_key;
  }
}