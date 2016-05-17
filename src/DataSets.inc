<?php
/**
 * @file
 *
 * Implements the DataSets class.
 *
 * The DataSets Class interacts with Galaxy to manage DataSet information.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

require_once 'HTTPRequest.inc';


class Datasets extends HTTPRequest {
  private $galaxy;

  /**
   * The DataSets constructor.
   *
   * @param GalaxyInstance $galaxy
   *          A GalaxyInstance object.
   *
   * @return An instance of a DataSet object.
   *
   *
   */
  public function __construct($galaxy) {
    $this->galaxy = $galaxy;

    parent::__construct();
  }

  /**
   * Retreive information about datasets made by converting
   * to a new file format.
   *
   * Corresponds to the galaxy API function at:
   * GET /api/datasets/{dataset_id}/converted/{ext}
   *
   * @param params
   *   Dictionary (associative array) containing the input parameters
   *   required and optional that this function can run.
   *
   *   - dataset_id: The dataset id of the information to pull.
   *       Can be obtained from this function's display().
   *   - extension (optional): If supplied this will look at the file extension.
   *
   * @return
   *   An array containing information about the matching dataset(s).
   *
   */
  public function converted($params) {
    $URL = "";

    if (array_key_exists('dataset_id', $params)) {
      if (array_key_exists('extension', $params)) {
        $URL = $this->galaxy->getURL() . '/api/datasets/' . $params ['dataset_id'] . '/converted/' . $params ['extension'] . '/?key=' . $this->galaxy->getAPIKey();
      }

      else {
        $URL = $this->galaxy->getURL() . '/api/datasets/' . $params ['dataset_id'] . '/converted/?key=' . $this->galaxy->getAPIKey();
      }
    }
    else {
      $this->setError("API", "This function expects at least a the parameter \'dataset_id\'.
        The \'extension'\ parameter is optional.");
      return FALSE;
    }

    $response = $this->httpGET($URL);

    return $this->expectArray($response);
  }

  /**
   * Retreives a list of datasets associated with a given history.
   *
   * Corresponds to the Galaxy Api method and path:
   * GET /api/histories/{encoded_history_id}/contents/{encoded_content_id}/display
   * history content (dataset).
   *
   * @param $params
   *   A dictionary (associative array) containing the input parameters that
   *   are required to run this function.
   *
   *   - hist_id: The history id of the datasets to find.
   *   - hist_content_id: The specified history content's dataset(s) to list.
   *       Please see the HistoryContents class to obtain the history content id
   *
   * @return
   *   An array containing information about the matching dataset(s).
   *
   */
  public function display($params) {
    if (array_key_exists('hist_id', $params)) {

      if (array_key_exists('hist_content_id', $params)) {
        $URL = $this->galaxy->getURL() . '/api/histories/' . $params ['hist_id'] . '/contents/' . $params ['hist_content_id'] . '/?key=' . $this->galaxy->getAPIKey();
      }

      else{
        $this->setError("API", "This function requires the \'hist_id\' AND the \'hist_content_id\'.
             If one or the other is missing you will receive this error.");
        return FALSE;
      }
    }

    else{
      $this->setError("API", "This function requires the \'hist_id\' AND the \'hist_content_id\'.
             If one or the other is missing you will receive this error.");
      return FALSE;
    }

    $response = $this->httpGET($URL);

    return $this->expectArray($response);
  }

  /**
   * Retreives a list of all datasets.
   *
   * Currently not supported by the Galaxy API
   */
  public function index() {
    $URL = $this->galaxy->getURL() . '/api/datasets/?key=' . $this->galaxy->getAPIKey();
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }

  /**
   * Retreives detailed content on a specific dataset.
   *
   * Corresponds to the Galaxy Api function and path:
   * GET /api/datasets/{encoded_dataset_id}
   *
   * @param $params
   *   A dictionary (associative array) containing the input parameters that
   *   are required to run this function.
   *
   *   - dataset_id: The dataset_id's information that the function is to
   *       retreive. To obtain the dataset id, please use the Display function.
   *
   * @return
   *   An array containing information about the matching dataset.
   *
   */
  public function show($dataset_id) {
    $URL = $this->galaxy->getURL() . '/api/datasets/' . $dataset_id . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->httpGET($URL);
    return $this->expectArray($response);
  }
}
