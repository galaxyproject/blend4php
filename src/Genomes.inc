<?php

require_once('GalaxyAPIService.inc');


/**
 * @file
 *
 * The Genomes class.
 *
 * The Genomes class interacts with Galaxy to manage contents of a Galaxy
 * Genome. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */


class GalaxyGenomes extends GalaxyAPIService {

  /**
   * Returns a list of installed genomes.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/genomes
   *
   * @return
   *   An array containing a list of all of the genome entities in Galaxy.
   */
  public function index(){

    $URL = $this->galaxy->getURL() . '/api/genomes/'  .  '?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Returns  detailed information about a specific Galaxy genome.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   GET /api/genomes/{genome_id}
   *   
   * @param $params
   *  An associative array containing the input parameters for this function.
   *  The following parameters are available:
   *
   *  - genome_id: The id of the genome to examine. To obtain genome ids refer
   *      to Genomes::index() funciton.
   *
   * @return
   *   An array containing detailed information about the specified
   *   Galaxy Genome.
   */
  public function show($params){
    
    $URL = $this->galaxy->getURL() . '/api/genomes/' . $params['genome_id'] .  '?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }


}

?>
