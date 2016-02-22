<?php


/**
 * @file
 *
 * The Genomes class.
 *
 * The Genomes class interacts with Galaxy to manage contents of a Galaxy 
 * Genomes. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts. 
 */

/**
 * @defgroup genomes_class GalaxyInstance Class
 * @{
 *   The GalaxyInstance class is used to connect to a remote Galaxy server.
 *   It authenticates and maintains the API key for the user.  The functions
 *   in this class correspond to the Galaxy API functions and are named
 *   similarly to their Python counterpart.
 * @}
 */

require_once "GalaxyInstance.inc";
require_once 'GalaxyRequest.inc';

class Genomes extends GalaxyRequest{

  /**
   * The Genomes constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Genomes object.
   *
   * @ingroup genomes_class
   */
  function __construct($galaxy) {
    parent::__contruct($galaxy);
  }

  /**
   * Returns a list of installed genomes.
   *
   * Corresponds to the Galaxy api function/path:
   *   GET /api/genomes
   *   
   * @return 
   *   A JSON object containing a list of all of the genome entities in Galaxy.
   *   
   * @ingroup genomes_class    
   */
  public function index(){
    $api_key = $this->galaxy->getAPIKey();
    $url = $this->galaxy->getURL() . '/api/genomes/'  .  '?key=' . $api_key;
    return $this->rest->GET($url);
  }

  /**
   * Returns  detailed infromation about a specific Galaxy genome.
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
   * @ingroup genomes_class    
   */
  public function show($genome_id){
    $api_key = $this->galaxy->getAPIKey();
    $url = $this->galaxy->getURL() . '/api/genomes/' . $genome_id .  '?key=' . $api_key;
  }
  
  
}

?>
