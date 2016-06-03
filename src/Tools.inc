<?php

/**
 * @file
 *
 * The GalaxyTools class.
 *
 * The Tools class interacts with Galaxy to manage contents of a Galaxy
 * Tool. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

class GalaxyTools {

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
   *
   */
   public function __construct($galaxy) {
     $this->galaxy = $galaxy;
   }

  /**
   * Retreive a list of tools defined by the parameters.
   *
   * Corresponds to the Galaxy API/path:
   *   GET /api/tools:
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - tool_id: Optional, the id of the tool to specify.
   *   - q: Optional, additional search details.
   *   - in_panel: If TRUE, return tools marked as in panel.
   *   - trackster: If TRUE, return tools marked as trackster.
   *
   *  @return
   *   An array containing all the tools in galaxy that match the
   *   the specified search.
   *
   *
   */
   public function index($params) {

    // Create the basic URL. If a tool_id is provided we need to add it as
    // part of the URL.
    $URL = $this->galaxy->getURL() . '/api/tools/';
    if (array_key_exists('tool_id', $params)) {
      $URL .=  $params['tool_id'] . '/';
    }
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Add all other parameters to the URL.
    foreach ($params as $key => $value) {
      $URL .= '&' . $key . '=' . $value;
    }

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
   }

  /**
   * Retreives detailed informaiton of a specific tool.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/tools/{tool_id}
   *
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - tool_id: The id of the tool whos informaiton to obtain. To retreive a
   *       tool id please use this class's index funciton.
   *
   * @return
   *   An array containing detailed information about a specific tool.
   *
   *
   */
  public function show($params){

    // The 'tool_id' is required.
    if (!array_key_exists('tool_id', $params)) {
      $this->galaxy->setError("API", "A 'tool_id' is required in order to invoke this call");
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Return diagnostic information about a tool.
   *
   * Corresponds to the Galaxy API/path at
   *   GET /api/tools/{tool_id}/diagnostics
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - tool_id: The id of the tool whos informaiton to obtain. To retreive a
   *       tool id please use this class's index funciton.
   *
   * @return
   *   An array contaiing information about the diagnostics of a tool.
   *
   *
   */
   public function diagnostics($params){

     // The 'tool_id' is required.
     if (!array_key_exists('tool_id', $params)) {
       $this->galaxy->setError("API", "A 'tool_id' is required in order to invoke this call");
       return FALSE;
     }

     // Contruct the basic URL to the Galaxy API.
     $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/diagnostics/';
     $URL .= '?key=' . $this->galaxy->getAPIKey();

     // Get the response from the Galaxy server.
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Reload specified tool.
   *
   * Corresponds to the Galaxy Api/path
   *   GET /api/tools/{tool_id}/reload
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - tool_id: The id of the tool to reload.
   *
   * @return
   *   An array of the tool that was reloaded.
   *
   *
   */
   public function reload($params){

     // The 'tool_id' is required.
     if (!array_key_exists('tool_id', $params)) {
       $this->galaxy->setError("API", "A 'tool_id' is required in order to invoke this call");
       return FALSE;
     }

     // Contruct the basic URL to the Galaxy API.
     $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/reload/';
     $URL .= '?key=' . $this->galaxy->getAPIKey();

     // Get the response from the Galaxy server.
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Returns a tool model that includes its parameters.
   * Returns a tool model including dynamic parameters and updated values.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/tools/{tool_id}/build
   *
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - tool_id: The id of the tool to perform this aciton on. Please use
   *       this class's index() function to retreive a tool id.
   *   - history_id: The id of the history to place the built tool.  This
   *       parameter is required only if the authentication of the galaxy
   *       instance has been authenticated.
   *   - tool_version: Optional, the version of the tool.
   *
   * @return
   *   An array containing the build model of the tool.
   *
   *
   */
   public function build($params){

     // The 'tool_id' is required.
     if (!array_key_exists('tool_id', $params)) {
       $this->galaxy->setError("API", "A 'tool_id' is required in order to invoke this call");
       return FALSE;
     }

     // The 'history_id' parameters is required.
     if (!array_key_exists('history_id', $params)) {
       $this->galaxy->setError("API", "A 'history_id' is required in order to invoke this call");
       return FALSE;
     }

     // Contruct the basic URL to the Galaxy API.
     $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/build/';
     $URL .= '?key=' . $this->galaxy->getAPIKey();

     // The tool_id is part of the URL path, so remove it from the $params
     // array before adding in the other arguments.
     unset($params['tool_id']);
     foreach ($params as $key => $value) {
       $URL .= '&' . $key . '=' . $value;
     }

     // Get the response from the Galaxy server.
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);

   }

  /**
   * Retreive the citations for a given tool.
   *
   * Corresponds to the Galaxy Api/path
   *   GET /api/tools/{tool_id}/citations
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - tool_id: The id of the specified tool. To obtain a tool id, please use
   *       this class' index() function.
   *
   * @return
   *   An array containing infromation about the citations of the specified
   *   tool.
   *
   *
   */
   public function citations($params){

     // The 'tool_id' is required.
     if (!array_key_exists('tool_id', $params)) {
       $this->galaxy->setError("API", "A 'tool_id' is required in order to invoke this call");
       return FALSE;
     }

     // Contruct the basic URL to the Galaxy API.
     $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/citations/';
     $URL .= '?key=' . $this->galaxy->getAPIKey();

     // Get the response from the Galaxy server.
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);

   }


  /**
   * Download a specified tool.
   *
   * Corresponds to the Galaxy Api/Path at:
   *   GET /api/tools/{tool_id}/download
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *  - tool_id: The id of the specified tool. To obtain a tool id, please use
   *      this class's index() function.
   *  - file_path: The path to where the file will be stored.
   *
   * @return
   *   Gzip of the tool.
   *
   *
   */
   public function download($params){

     // The 'tool_id' is required.
     if (!array_key_exists('tool_id', $params)) {
       $this->galaxy->setError("API", "A 'tool_id' is required in order to invoke this call");
       return FALSE;
     }

     // The 'file_path' is required.
     if (!array_key_exists('file_path', $params)) {
       $this->galaxy->setError("API", "A 'file_path' is required in order to invoke this call");
       return FALSE;
     }

     // Contruct the basic URL to the Galaxy API.
     $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/download/';
     $URL .= '?key=' . $this->galaxy->getAPIKey();

     // Get the response from the Galaxy server.
     $response = $this->galaxy->getRemoteFile($URL, $params['file_path']);
     return $this->galaxy->expectArray($response);
   }


  /**
   * Executes a tool using specified inputs.
   *
   * Corresponds to the Galaxy API/path at
   *   POST /api/tools
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - tool_id: The id of the specified tool. To obtain a tool id, please use
   *       this class's index() function.
   *   - history_id: The history_id where the tool is located. To obtain
   *       history id's please see the history class.
   *   - files: Optional. an array of file infromation, the array should be
   *       NULL or in the following format:
   *      $params['files'] = array(
   *        0 => array(
   *          'name' => [file name],
   *          'path' => [full path to the file],
   *        ),
   *        1 => array(
   *         'name' => [file name],
   *          'path' => [full path to the file],
   *        ),
   *        ...
   *      );
   *  - input_dataset_ids: Optional. An array of dataset id's where the tool
   *      should grab its inputs from. Please see the datasets class to
   *      obtain id's.  Each element of the array is itself an associative
   *      array with a key of 'id' containing the dataset ID and an optional
   *      'src' key if the src is anything other than 'hda'.
   *  - tool_version: Optional, specify specific tool version for the tool.
   *  - region: Optional information on the region of the genome being rerun.
   *  - action: Optional, 'rerun' to rerun the tool and not execute
   *
   * @return
   *   An array containing information about the created or executed tool.
   *
   *
   */
   public function create($params) {

     // The 'tool_id' is required.
     if (!array_key_exists('tool_id', $params)) {
       $this->galaxy->setError("API", "A 'tool_id' is required in order to invoke this call");
       return FALSE;
     }

     // The 'history_id' parameters is required.
     if (!array_key_exists('history_id', $params)) {
       $this->galaxy->setError("API", "A 'history_id' is required in order to invoke this call");
       return FALSE;
     }

     // Contruct the basic URL to the Galaxy API.
     $URL = $this->galaxy->getURL() . '/api/tools/';

     // Because this is a POST we need to add the key to the parameters.
     $params['key'] = $this->galaxy->getAPIKey();

     // If the 'input_datasets_ids' is present we need to check for the 'src'
     // key and if not present add one.
     if (array_key_exists('input_datasets_ids', $params)) {
       for ($i = 0; $i < count($params['input_dataset_ids']); $i++) {
         if (!array_key_exists('src', $params['input_dataset_ids'][$i]))
         $params['input_dataset_ids'][$i]['src'] = 'hda';
       }
     }

     // We need to format the files array so it's appropriate for Galaxy.
     // Galaxy requires a key named 'inputs' for the files and the value
     // is JSON encoded.
     $inputs = array();
     $files = array();
     if (array_key_exists('files', $params)) {
       // Append the appropriate file information:
       $index = 0;
       foreach ($params['files'] as $file) {
         if (array_key_exists('name', $file) and array_key_exists('path', $file)) {
           $file_data = "files_" . $index . "|file_data";
           $file_name = "files_" . $index . "|NAME";
           $files_type = "files_" . $index . "|type";
           //The inputs should look like:
           //  files_0|file_data => /path/to/file
           //  files_0|NAME => file_name
           // ... etc
           $files[$file_data] = $file['path'];
           if(array_key_exists('type', $params))
             $inputs[$files_type] = $params['type'];

           $inputs[$file_name] = $file['name'];
           $index++;
         }
       }
     }
     unset($params['files']);
     $params['inputs'] = json_encode($inputs);

     // If we have files to upload with the tool, then call the 'uploadFile'
     // function, otherwise just use an httpPOST.
     if (count($files) > 0) {
       $response = $this->galaxy->uploadFile($URL, $params, $files);
       return $this->galaxy->expectArray($response);
     }
     else {
       $response = $this->galaxy->httpPOST($URL, $params);
       return $this->galaxy->expectArray($response);
     }
   }
 }

?>
