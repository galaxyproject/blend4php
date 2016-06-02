<?php

/**
 * @file
 *
 * The Genomes class.
 *
 * The Genomes class interacts with Galaxy to manage contents of a Galaxy
 * Genome. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

/**
 * @defgroup genomes_class genome Class
 * @{
 *   The Genomes class interacts with Galaxy to manage contents of a Galaxy
 *   Genome. The functions in this class correspond to the Galaxy API
 *   functions and are named similarly to their Python counterparts.
 * @}
 */


class GalaxyGenomes {
  private $galaxy;

  /**
   * The Genomes constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Genomes object.
   *
   *
   */
  public function __construct($galaxy) {
    $this->galaxy = $galaxy;
  }

  /**
   * Returns a list of installed genomes.
   *
   * Corresponds to the Galaxy api function/path:
   *   GET /api/genomes
   *
   * @return
   *   An array containing a list of all of the genome entities in Galaxy.
   *
   *
   */
  public function index(){
    $api_key = $this->galaxy->getAPIKey();

    $URL = $this->galaxy->getURL() . '/api/genomes/'  .  '?key=' . $api_key;

    $response = $this->galaxy->httpGET($URL);
    return $this->expectArray($response);
  }

  /**
   * Returns  detailed information about a specific Galaxy genome.
   *
   * Corresponds to the Galaxy api function/path:
   *   GET /api/genomes/{encodedGenomeid}
   *
   * @param $genome_id
   *   The id of the genome to examine. To obtained genome id's please
   *   use this class's index() funciton.
   *
   * @return
   *   A JSON object containint detailed information about the specified
   *   Galaxy Genome.
   *
   *
   */
  public function show($genome_id){
    $api_key = $this->galaxy->getAPIKey();
    $URL = $this->galaxy->getURL() . '/api/genomes/' . $genome_id .  '?key=' . $api_key;

    $response = $this->galaxy->httpGET($URL);
    return $this->expectArray($response);
  }


}

?>
