<?php

class Galaxy {
  private $host;
  private $port;
  
  function __construct($hostname, $port) {
  	$this->host = $hostname;
  	$this->port = $port;
  	
  }
  
  public function getURL() {
  	return "http://". $this->host .":". $this->port;
  }
}