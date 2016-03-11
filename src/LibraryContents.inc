<?php
include_once "HTTPRequest.inc";

class LibraryContents extends HTTPRequest{
  private $galaxy;
  /**
   * The Folders constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Libraries object.
   *
   * @ingroup libraries_class
   */
  public function __construct($galaxy) {
    $this->galaxy = $galaxy;
    parent ::__construct();
  }

  /**
   * Gather the contents from the specified libarary.
   *
   * @param  $library_id
   *
   * @return Files and Folders within the specified library.
   */
  public function index($library_id){
    $URL = $this->galaxy->getURL() . '/api/libraries/' . $library_id . '?key=' . $this->galaxy->getAPIKey();

    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }

  /**
   * View the specified library content within a given library.
   *
   * You need both of the specific id's in order to see the information
   * of the content.
   *
   * @param $library_id
   * @param $library_content_id
   *
   * @return Detailed library item information.
   */
  public function show($library_id, $library_content_id){
    $URL = $this->galaxy->getURL() . '/api/libraries/' . $library_id . '?key=' . $this->galaxy->getAPIKey();

    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }

  /**
   * Add a folder/file/data collection to the specified the library.
   *
   * This is one is important when you want to upload files to said library
   * from a local filesystem to the given galaxy instance.
   *
   * @param $library_id
   * @param $folder_id
   * @param $create_type
   * @param $from_hda_id
   * @param $ldda_message
   * @param $ldda_message
   * @param $upload_option
   * @param $server_dir
   * @param $filesystem_paths
   * @param $link_data_only
   * @param $name
   * @param $description
   */
  public function create($library_id, $folder_id, $create_type, $from_hda_id = NULL, $ldda_message = NULL,
      $ldda_message = NULL, $upload_option = NULL, $server_dir = NULL, $filesystem_paths = NULL, $link_data_only = NULL,
      $name = NULL, $description = NULL){

    $URL = $this->galaxy->getURL() . '/api/libraries/' . $library_id . '/contents/?key=' . $this->galaxy->getAPIKey();
    $elements = array('source' => $source, 'content' => $content_id);
    $notNullInputs = array();
    foreach ($elements as $element => $value) {
      if ($value != NULL) {
        $notNullInputs[$element] = $value;
      }
    }
    $response = $this->httpPOST($URL, $notNullInputs);
    return $this->expectArray($response);

  }
}