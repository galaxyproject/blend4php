<?php

require_once('GalaxyAPIService.inc');

/**
 * @file
 *
 * The Search class
 *
 * The search class contains amethod for quering SQL searches
 * accross Galaxy tables. This class corresponds to its Galaxy API equivalent
 * and is named similarly.
 */


class GalaxySearch extends GalaxyAPIService {


  /**
   * Performs a search of the various elements in Galaxy.
   *
   * Corresponds to the galaxy method/path:
   *   Post /api/search
     *
   * @param $query
   *   Must be a valid, lowercase,  SQL expression, example:
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
     $response = $this->galaxy->httpPOST($URL, $elements);
     return $this->galaxy->expectArray($response);
   }






}
