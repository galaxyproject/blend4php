<?php
/**
 * @file
 *
 * Implements the DataTypes class.
 *
 * The DataTypes Class interacts with Galaxy to manage DataType information.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

/**
 * @defgroup data_types_class DataTypes class
 * @{
 *   The DataTypes Class interacts with Galaxy to manage DataTypes.
 *   The functions in this class correspond to the Galaxy API functions and
 *   are named similarly to their Python counterpart.
 * @}
 */
require_once 'HTTPRequest.inc';


class Datatypes extends HTTPRequest {
  private $galaxy;

  /**
   * The DataTypes constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Datatypes object.
   *
   * 
   */
  public function __construct($galaxy) {
    $this->galaxy = $galaxy;
    parent::__construct();
  }


    /**
     * Retreive a list of all datatype sniffers.
     *
     * Corresponds to the Galaxy API/Path:
     *   GET /api/datatypes/sniffers
     *
     * @return
     *   An array containing sniffers of all datatypes
     *
     * 
     */
    public function sniffers(){
      $URL = $this->galaxy->getURL() . '/api/datatypes/sniffers/?key=' . $this->galaxy->getAPIKey();
      $response = $this->httpGET($URL);
      return $this->expectArray($response);
    }

    /**
     * Retreive a list of all datatype converters.
     *
     * Corresponds to the Galaxy API/Path:
     *   GET /api/datatypes/converters
     *
     * @return
     *   An array containing converters of all datatypes
     *
     * 
     */
    public function converters(){
      $URL = $this->galaxy->getURL() . '/api/datatypes/converters/?key=' . $this->galaxy->getAPIKey();

      $response = $this->httpGET($URL);
      return $this->expectArray($response);
    }

    /**
     * Retreive a list of all datatypes in the edam format.
     *
     * Corresponds to the Galaxy API/Path:
     *   GET /api/datatypes/edam_formats
     *
     * @return
     *   An array containing all datatypes in edam_format.
     *
     * 
     */
   public function edamFormats(){
     $URL = $this->galaxy->getURL() . '/api/datatypes/edam_formats/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Retreive a list of all datatypes in mapping.
    *
    * Corresponds to the Galaxy API/Path:
    *   GET /api/datatypes/mapping.
    *
    * @return
    *   An array containing all datatypes in mapping.
    *
    * 
    */
   public function mapping () {
     $URL = $this->galaxy->getURL() . '/api/datatypes/mapping/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Retreive a list of all datatypes
    *
    * Corresponds to the Galaxy API/Path:
    *   GET /api/datatypes/
    *
    * @return
    *   An array containing all datatypes
    *
    * 
    */
  public function index(){
    $URL = $this->galaxy->getURL() . '/api/datatypes/?key=' . $this->galaxy->getAPIKey();
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }

}

