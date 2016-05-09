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
   * 
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

    $URL = $this->galaxy->getURL() . '/api/tools';
    
    if (array_key_exists('tool_id', $params))
      $URL .= '/'. $params['tool_id'];
    if (array_key_exists('trackster', $params))
      $URL .= '/?trackster=' . $params['trackster'];
    if (array_key_exists('in_panel', $params) and !array_key_exists('trackster', $params))
      $URL .= '/?in_panel=' . $params['in_panel'];
    else if (array_key_exists('in_panel', $params) and array_key_exists('trackster', $params))
      $URL .= '&in_panel=' . $params['in_panel'];
    if (array_key_exists('q', $params) and (!array_key_exists('trackster', $params)) and !array_key_exists('in_panel', $params))
      $URL .= '/?q=' . urlencode($params['q']);
    else if (array_key_exists('q', $params))
      $URL .= '&q=' . urlencode($params['q']);
    // All others are part of a query structure and therefore do not need a
    // qestion mark but an ampersand to include the key in the query.
    if(!array_key_exists('tool_id', $params) and (array_key_exists('trackster', $params) or array_key_exists('in_panel', $params) or array_key_exists('q', $params)))
      $URL .= '&key=' . $this->galaxy->getAPIKey();

    // tool_id is treated like a file accessing parameter.
    // This will also execute if all of the inputs are NULL
    else
      $URL .= '?key=' . $this->galaxy->getAPIKey();
    

    $response = $this->httpGET($URL);
    return $this->expectArray($response);
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
    if(array_key_exists('tool_id', $params)){
      $URL = $this->galaxy->getURL() . '/api/tools/' . $params['tool_id'] .'/?key='. $this->galaxy->getAPIKey();
      $response = $this->httpGET($URL);
      return $this->expectArray($response);
    }
    $this->setError("API", "A 'tool_id' is required in order to invoke this call");
    return FALSE;
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
     if(array_key_exists('tool_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/diagnostics/?key=' . $this->galaxy->getAPIKey();
       $response = $this->httpGET($URL);
       return $this->expectArray($response);
     }
     $this->setError("API", "A 'tool_id' is required in order to invoke this call");
     return FALSE;
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
     if(array_key_exists('tool_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/reload/?key=' . $this->galaxy->getAPIKey();
       $response = $this->httpGET($URL);
       return $this->expectArray($response);
     }
     $this->setError("API", "A 'tool_id' is required in order to invoke this call");
     return FALSE;
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
   *   - history_id: The id of the history to place the built tool.
   *   - tool_version: Optional, the version of the tool.
   *
   * @return
   *   An array containing the build model of the tool.
   *
   * 
   */
   public function build($params){
     
     if(array_key_exists('tool_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/build';
       if(array_key_exists('history_id', $params)){
         $URL .= '/?history_id=' . $params['history_id'];
         if(array_key_exists('tool_version', $params)){
           $URL .= '&tool_version='. $params['tool_version'];
         }
       }

       else{
         $this->setError("API", "A 'tool_id' is required in order to invoke this call");
         return FALSE;
       }
       
       $URL .= '&key=' . $this->galaxy->getAPIKey();
       $response = $this->httpGET($URL);
       return $this->expectArray($response);
     }
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
     
     if(array_key_exists('tool_id', $params)){
     $URL = $this->galaxy->getURL() . '/api/tools/' . $params['tool_id'] . '/citations/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
     }
     
     else{
       $this->setError("API", "A 'tool_id' is required in order to invoke this call");
       return FALSE;
     }
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
     if(array_key_exists('tool_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/tools/'. $params['tool_id'] . '/download/?key=' . $this->galaxy->getAPIKey();
       if(array_key_exists('file_path', $params))
         $response = $this->getRemoteFile($URL, $params['file_path']);
       else{
         $this->setError("API", "A 'file_path' is required in order to invoke this call");
         return FALSE;
       }
     return $response;
     }
     
     else{
       $this->setError("API", "A 'tool_id' is required in order to invoke this call");
       return FALSE;
     }
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
   *   - files: An array of file infromation, the array should be NULL or in
   *       the following format:
         $params['files'] = array(
           0 => array(
             'name' => [file name],
             'path' => [full path to the file],
           ),
           1 => array(
            'name' => [file name],
             'path' => [full path to the file],
           ),
           ...
         );
   *  - input_dataset_ids: Array of dataset id's where the tool should grab its
   *      inputs from. Please see the datasets class to obtain id's.
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

     $inputs = array();
     
     if (array_key_exists('tool_id', $params)) {
       if (array_key_exists('history_id', $params)) {
         
         $URL = $this->galaxy->getURL() . '/api/tools?key=' . $this->galaxy->getAPIKey();
         
         if(array_key_exists('input_datasets_ids', $params)){
            
           $input_ids = array();
           $i = 0;
           // Add any pre-existing Dataset ids to the inputs variables
           foreach ($params['input_dataset_ids'] as $input_dataset_id) {
             $input_ids[$i] = array('id' => $input_dataset_id, 'src' => 'hda');
             $i++;
           }
           $inputs = $input_ids;
           
           unset($params['input_dataset_ids']);
         }
         
         
         
         if(array_key_exists('files', $params)){
           //Append the appropriate file informaiton:
           $index = 0;
         
           foreach($params['files'] as $file){
             if( array_key_exists('name', $file) and array_key_exists('path', $file)){
               $file_data = "files_" . $index . "|file_data";
               $file_name = "files_" . $index . "|NAME";
               $file_to_posix_lines = "files_" . $index . "|to_posix_lines";
               $file_space_to_tab = "files_" . $index . "|space_to_tab";
               $files_type = "files_" . $index . "|type";
               //The inputs should look like:
               //  files_0|file_data => /path/to/file
               //  files_0|NAME => file_name
               //  files_0|File_to_posix_lines = false
               // ... etc
               $inputs[$file_data] = "@" . $file['path'];
               $inputs[$file_name] = $file['name'];
               $inputs[$file_to_posix_lines] = FALSE;
               $inputs[$file_space_to_tab] = FALSE;
               $inputs[$files_type] = "upload_dataset";
               $index++;
             }
           }
         
           //$inputs['dbkey'] = "?";
           unset($params['files']);
         
           
         }
         
         $elements = array_merge($params, $inputs);
         
         $notNullInputs = array();
         foreach($elements as $element=>$value) {
           if($value != NULL) {
             $notNullInputs[$element] = $value;
           }
         }
         
         print_r($notNullInputs);
         
         $response = $this->httpPOST($URL, $notNullInputs);
         
         return $this->expectArray($response);
         
       }
       
       else{
         $this->setError("API", "A 'history_id' is required in order to invoke this call");
         return FALSE;
       }
     }
     
     else{
       $this->setError("API", "A 'tool_id' is required in order to invoke this call");
       return FALSE;
     }

   }

 }

?>
