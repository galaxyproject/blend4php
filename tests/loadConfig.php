<?php

include_once 'json.php';

/**
 * @file
 *
 * The UnitTest Authentication file.
 *
 * This file is made for the purpose of the user for putting in their
 * information of their galaxy instance, i.e. host, port, username, etc
 * to allow the testing functions to access the API functions to ensure galaxy
 * and the bindings are working properly
 */
 
	
  function readConfigFile (){
		// the file config will be within this directory and return the text within
		// the file (in json format) will be returned as an array
		global $object;
  	
  	return json_decode($object, TRUE);
	 }