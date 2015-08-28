<?php

require_once "../Galaxy.inc";

// def get_api_key( self,trans, **kwd) *GET /api/authenticate/baseauth
// This was the first example of what Stephen was teaching us with the base authentication with the base64 encryption etc...

class AUTHENTICATION {
  private $galaxy = NULL;
  
  function __construct(Galaxy $galaxy){
    $this->galaxy = $galaxy;
  
  }
  
  public function get_api_key($username, $password){
  
  }
  
}
