<?php

/**
 * @file
 *
 * The Tools class.
 *
 * The Tools class interacts with Galaxy to manage contents of a Galaxy
 * Tool. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

/**
 * @defgroup tools_class tools Class
 * @{
 *   The tools class interacts with Galaxy to manage contents of a Galaxy
 *   tool. The functions in this class correspond to the Galaxy API
 *   functions and are named similarly to their Python counterparts.
 * @}
 */

require_once 'HTTPRequest.inc';

class Tools extends HTTPRequest{
  private $galaxy;
  /**
   * The Tools constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Tools object.
   *
   * @ingroup tools_class
   */
   public function __construct($galaxy) {
     $this->galaxy = $galaxy;
     parent ::__construct();
   }

   /**
    * Retreive a list of tools defined by the parameters.
    *
    * Corresponds to the Galaxy API/path:
    *   GET /api/tools:
    *
    * @param $tool_id
    *   Optional, the id of the tool to specify.
    * @param $q
    *   Optional, additional search details.
    * @param $in_panel
    *   If true, return tools marked as in panel.
    * @param $trackster
    *   If true, return tools marked as trackster.
    *
    *  @return
    *   An array containing all the tools in galaxy that match the
    *   the specified search.
    *
    * @ingroup tools_class
    */
   public function index($tool_id = NULL, $q = NULL, $in_panel = FALSE, $trackster = FALSE ) {

    $URL = $this->galaxy->getURL() . '/api/tools';
    if ($tool_id !== NULL) {
      $URL = $URL .'/'. $tool_id;
    }
    if ($trackster != FALSE ) {
      $URL = $URL . '/?trackster=true';
    }
    if ($in_panel != FALSE ) {
      $URL = $URL . '/?in_panel=true';
    }
    if ($q != NULL) {
      $URL = $URL . '/?q=' . urlencode($q);
    }

    // All others are part of a query structure and therefore do not need a
    // qestion mark but an ampersand to include the key in the query.
    if(!$tool_id && ($trackster || $in_panel || $q)){
      $URL = $URL . '&key=' . $this->galaxy->getAPIKey();
    }
    // tool_id is treated like a file accessing parameter.
    // This will also execute if all of the inputs are NULL
    else{
      $URL = $URL . '?key=' . $this->galaxy->getAPIKey();
    }
    $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

  /**
   * Retreives detailed informaiton of a specific tool.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/tools/{tool_id}
   *
   * @param $tool_id
   *   The id of the tool whos informaiton to obtain. To retreive a tool id
   *   please use this class's index funciton.
   *
   * @return
   *   An array containing detailed information about a specific tool.
   *
   * @ingroup tools_class
   */
  public function show($tool_id){
    $URL = $this->galaxy->getURL() . '/api/tools/' . $tool_id .'/?key='. $this->galaxy->getAPIKey();
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }

  /**
   * Return diagnostic information about a tool.
   *
   * Corresponds to the Galaxy API/path at
   *   GET /api/tools/{tool_id}/diagnostics
   *
   * @param  $tool_id
   *   The id of the tool to retreive diagnostics from, to obtain a tool id
   *   please see this class's index function.
   *
   * @return
   *   An array contaiing information about the diagnostics of a tool.
   *
   * @ingroup tools_class
   */
   public function diagnostics($tool_id){
     $URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/diagnostics/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

  /**
   * Reload specified tool.
   *
   * Corresponds to the Galaxy Api/path
   *   GET /api/tools/{tool_id}/reload
   *
   * @param $tool_id
   *   The id of the tool to reload.
   *
   * @return
   *   An array of the tool that was reloaded.
   *
   * @ingroup tools_class
   */
   public function reload($tool_id){
     $URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/reload/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

  /**
   * Returns a tool model that includes its parameters.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/tools/{tool_id}/build
   *
   * Note the original python function allows for an 'inputs' parameter,
   *   this is not supported here.
   *
   * @param $tool_id
   *   id of the tool to perform this aciton on. Please use this class's
   *   index() function to retreive a tool id.
   * @param history_id
   *   The id of the history to place the built tool.
   * @param $tool_version
   *   Optional, the version of the tool.
   *
   * @return
   *   An array containing the build model of the tool.
   *
   * @ingroup tools_class
   */
   public function build($tool_id, $history_id, $tool_version = NULL){

     $URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/build';
     if ($tool_version != NULL) {
       $URL = $URL . '/?tool_version='. $tool_version;
       $URL = $URL . '&key=' . $this->galaxy->getAPIKey();
       $URL .= '&history_id=' . $history_id;
       $response = $this->httpGET($URL);
       return $this->expectArray($response);
     }

     $URL = $URL . '/?key=' . $this->galaxy->getAPIKey();
     $URL .= '&history_id=' . $history_id;

     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

  /**
   * Retreive the citations for a given tool.
   *
   * Corresponds to the Galaxy Api/path
   *   GET /api/tools/{tool_id}/citations
   *
   * @param $tool_id
   *   The id of the specified tool. To obtain a tool id, please use this
   *   class' index() function.
   *
   * @return
   *   An array containing infromation about the citations of the specified
   *   tool.
   *
   * @ingroup tools_class
   */
   public function citations($tool_id){
     $URL = $this->galaxy->getURL() . '/api/tools/' . $tool_id . '/citations/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }


  /**
   * Download a specified tool.
   *
   * Corresponds to the Galaxy Api/Path at:
   *   GET /api/tools/{tool_id}/download
   *
   * @param $tool_id
   *   The id of the specified tool. To obtain a tool id, please use this
   *   class index() function.
   *
   * @param $file_path
   *   The path to where the file will be stored.
   *
   * @return
   *   Gzip of the tool.
   *
   * @ingroup tools_class
   */
   public function download($tool_id, $file_path){
     $URL = $this->galaxy->getURL() . '/api/tools/'. $tool_id . '/download/?key=' . $this->galaxy->getAPIKey();
     $response = $this->getRemoteFile($URL, $file_path);
     return $response;
   }


  /**
   * Executes a tool using specified inputs.
   *
   * Corresponds to the Galaxy API/path at
   *   POST /api/tools
   *
   * @param action
   *   Optional, 'rerun' to rerun the tool and not execute
   * @param $tool_id
   *   The id of the specified tool. To obtain a tool id, please use this
   *   class index() function.
   * @param tool_version
   *   Optional, specify specific tool version for the tool.
   * @param history_id
   *   The history_id where the tool is located. To obtain history id's please
   *   see the history class.
   * @param region
   *   Optional information on the region of the genome being rerun.
   * @param input_dataset_ds
   *   Array of dataset id's where the tool should grab the inputs from.
   *   Please see the datasets class to obtain id's.
   *
   * @return
   *   An array containing information about the created or executed tool.
   *
   * @ingroup tools_class
   */
   public function create($tool_id,  $input_dataset_ids, $history_id = NULL, $tool_version=NULL,
        $region = NULL, $action = NULL ) {

     $URL = $this->galaxy->getURL() . '/api/tools/?key=' . $this->galaxy->getAPIKey();

     $input_ids = array();
     $i = 0;
     foreach ($input_dataset_ids as &$input_dataset_id) {
       $input_ids[$i] = array('id'=> $input_dataset_id, 'src'=>'hda');
       $i++;
     }

     $elements = array(
       'tool_id' => $tool_id,
       'tool_version' => $tool_version,
       'inputs' => json_encode($input_ids,JSON_FORCE_OBJECT),
       'history_id' => $history_id,
       'region' => $region,
       'action' => $action,
     );

     // Create a list of input items that is not null
     $notNullInputs = array();
     foreach($elements as $element=>$value) {
       if($value != NULL) {
         $notNullInputs[$element] = $value;
       }
     }

     $response = $this->httpPOST($URL, $notNullInputs);
     return $this->expectArray($response);
   }
 }

?>
