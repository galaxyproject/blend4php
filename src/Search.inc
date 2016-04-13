<?php

/**
 * @file
 *
 * The Search class
 *
 * The search class contains amethod for quering SQL searches
 * accross Galaxy tables. This class corresponds to its Galaxy API equivalent
 * and is named similarly.
 */

/**
 * @defgroup search_class Search Class
 * @{
 *   The Search class contains a method for quering SQL searches
 *   accross Galaxy tables. This class corresponds to its Galaxy API equivalent
 *   and is named similarly.
 * @}
 */

include_once 'HTTPRequest.inc';

class Search extends HTTPRequest{
  private $galaxy;

  /**
   * Implements the Search constructor.
   *
   * @param GalaxyInstance galaxy
   *   A Galaxy Instance object.
   *
   * @return
   *   An instance of a search object.
   *
     * 
   */
  function __construct($galaxy) {
    $this->galaxy = galaxy;
    parent::__construct();
  }


  /**
   * Performs a search of the various elements in Galaxy.
   *
   * Corresponds to the galaxy method/path:
   *   Post /api/search
     *
   * @param $query,
   *   must be a valid, lowercase,  SQL expression, example:
   *   'select * from history where id = \'290670ee50ab85f0\''
   *
   * @return
   *   An array of the Galaxy elements that matches the query.
   *
     * 
   */
   function create($query) {
     $URL = $this->galaxy->getURL() . '/api/search/?key=' . $this->galaxy->getAPIKey();
     $elements = array (
       'query'=> $query,
     );
     $response = $this->httpPOST($URL, $elements);
     return $this->expectArray($response);
   }






}
