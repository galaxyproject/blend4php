<?php

require_once ("GalaxyAPIService.inc");

/**
 * @file
 *
 * The GalaxyTools class.
 *
 * The Tools class interacts with Galaxy to manage contents of a Galaxy
 * Tool. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

class GalaxyTools extends GalaxyAPIService {

  /**
   * Retreive a list of tools defined by the parameters.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/tools
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - tool_id: (Optional) the id of the tool to specify.
   *   - q: (Optional) additional search details.
   *   - in_panel: (Optional) If TRUE, return tools marked as in panel.
   *   - trackster: (Optional) If TRUE, return tools marked as trackster.
   *
   *  @return
   *   An array containing all the tools in galaxy that match the
   *   the specified search.
   */
  public function index($params = array()) {

    // Make sure only allowed parameters are included.
    if (!$this->checkAllowedParams($params, array('tool_id', 'q', 'in_panel', 'trackster'))) {
      return FALSE;
    }

    // Create the basic URL. If a tool_id is provided we need to add it as
    // part of the URL.
    $URL = $this->galaxy->getURL() . '/api/tools/';
    if (array_key_exists('tool_id', $params)) {
      $URL .=  urlencode($params['tool_id']) . '/';
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
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/tools/{tool_id}
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - tool_id: The ID of the tool to obtain information. To retreive a
   *       tool id use Tools::index().
   *
   * @return
   *   An array containing detailed information about a specific tool.
   */
  public function show($params) {

       // Make sure only allowed parameters are included.
     if (!$this->checkAllowedParams($params, array('tool_id'))) {
       return FALSE;
     }

     // Check for required fields.
     if (!$this->checkRequiredParams($params, array('tool_id'))) {
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
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/tools/{tool_id}/diagnostics
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - tool_id: The ID of the tool to obtain diagnostics. To retreive a
   *       tool id use Tools::index().
   *
   * @return
   *   An array containin diagnostic information.
   */
   public function diagnostics($params) {

     // Make sure only allowed parameters are included.
     if (!$this->checkAllowedParams($params, array('tool_id'))) {
       return FALSE;
     }

     // Check for required fields.
     if (!$this->checkRequiredParams($params, array('tool_id'))) {
       return FALSE;
     }

     // Contruct the basic URL to the Galaxy API.
     $URL = $this->galaxy->getURL() . '/api/tools/'. urlencode($params['tool_id']) . '/diagnostics';
     $URL .= '?key=' . $this->galaxy->getAPIKey();

     // Get the response from the Galaxy server.
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Reload specified tool.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/tools/{tool_id}/reload
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - tool_id: The ID of the tool to reload.
   *
   * @return
   *   An array of the tool that was reloaded.
   */
  public function reload($params) {

    // Make sure only allowed parameters are included.
    if (!$this->checkAllowedParams($params, array('tool_id'))) {
      return FALSE;
    }

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('tool_id'))) {
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/tools/' . urlencode($params['tool_id']) . '/reload/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Returns a tool model including dynamic parameters and updated values.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/tools/{tool_id}/build
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - tool_id: The ID of the tool to perform this aciton on. Use
   *       Tools::index() to retreive a tool ID.
   *   - history_id: The ID of the history to place the built tool.
   *   - tool_version: (Optional) The version of the tool.
   *
   * @return
   *   An array containing the build model of the tool.
   *
   *
   */
  public function build($params) {

    // Make sure only allowed parameters are included.
    if (!$this->checkRequiredParams($params, array('tool_id', 'history_id'))) {
      return FALSE;
    }

    // Check for required fields.
    if (!$this->checkAllowedParams($params, array('tool_id', 'history_id', 'tool_version'))) {
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/tools/' . urlencode($params['tool_id']) . '/build/';
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
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/tools/{tool_id}/citations
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - tool_id: The ID of the specified tool. To obtain a tool id, use
   *       Tools::index().
   *
   * @return
   *   An array containing infromation about the citations of the specified
   *   tool.
   */
  public function citations($params) {

    // Make sure only allowed parameters are included.
    if (!$this->checkAllowedParams($params, array('tool_id'))) {
      return FALSE;
    }

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('tool_id'))) {
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/tools/' . urlencode($params['tool_id']) . '/citations/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Download a tool.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/tools/{tool_id}/download
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - tool_id: The ID of the specified tool. To obtain a tool ID, use
   *      Tools::index().
   *  - file_path: The path to where the file will be stored.
   *
   * @return
   *   TRUE if the file was downloaded, FALSE otherwise.
   */
  public function download($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('tool_id', 'file_path'))) {
      return FALSE;
    }

    // Make sure only allowed parameters are included.
    if (!$this->checkAllowedParams($params, array('tool_id', 'file_path'))) {
      return FALSE;
    }

    // Contruct the basic URL to the Galaxy API.
    $URL = $this->galaxy->getURL() . '/api/tools/'. urlencode($params['tool_id']) . '/download/';
    $URL .= '?key=' . $this->galaxy->getAPIKey();

    // Get the response from the Galaxy server.
    return $this->galaxy->getRemoteFile($URL, $params['file_path']);
  }

  /**
   * Executes a tool using specified inputs.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/tools
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - tool_id: The ID of the specified tool. To obtain a tool ID, use
   *       Tools::index().
   *   - history_id: The history_id where the tool is located. To obtain
   *       history IDs, use Histories::index().
   *   - files: (Optional) an array of file information, the array should be
   *       NULL or in the following format:
   *      @code
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
   *      @endcode
   *  - input_dataset_ids: (Optional) An array of dataset IDs where the tool
   *      should grab its inputs. Use Datasets::index() to obtain IDs. Each
   *      element of the array is itself an associative array with a key of
   *      'id' containing the dataset ID and an optional 'src' key if the src
   *       is anything other than 'hda'.
   *  - tool_version: (Optional) Specify a build version of the tool.
   *  - region: (Optional) Information on the region of the genome being rerun.
   *  - action: (Optional) Set to 'rerun' and the tool will not execute
   *
   * @return
   *   An array containing information about the created or executed tool.
   */
  public function create($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('tool_id', 'history_id'))) {
      return FALSE;
    }

    // Make sure only allowed parameters are included.
    if (!$this->checkAllowedParams($params, array('tool_id', 'history_id', 'files', 'input_dataset_ids', 'tool_version', 'region', 'action'))) {
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
          //The inputs should look like:
          //  files_0|file_data => /path/to/file
          //  files_0|NAME => file_name
          // ... etc
          $file_data = "files_" . $index . "|file_data";
          $file_name = "files_" . $index . "|NAME";
          $files_type = "files_" . $index . "|type";
          $files[$file_data] = $file['path'];
          if(array_key_exists('type', $file))
            $inputs[$files_type] = $file['type'];

          $inputs[$file_name] = $file['name'];
          $index++;
        }
      }
    }
    unset($params['files']);
	
	if(!empty($inputs))
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
