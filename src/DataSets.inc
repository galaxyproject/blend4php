<?php

require_once('GalaxyAPIService.inc');

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


class GalaxyDatasets extends GalaxyAPIService {
  private $galaxy;

  /**
   * Retreive information about datasets made by converting
   * to a new file format.
   *
   * Corresponds to the galaxy API function at:
   * GET /api/datasets/{dataset_id}/converted/{ext}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
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

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('dataset_id'))) {
      return FALSE;
    }

    $URL = "";
    if (array_key_exists('extension', $params)) {
      $URL = $this->galaxy->getURL() . '/api/datasets/' . $params ['dataset_id'] . '/converted/' . $params ['extension'] . '/?key=' . $this->galaxy->getAPIKey();
    }
    else {
      $URL = $this->galaxy->getURL() . '/api/datasets/' . $params ['dataset_id'] . '/converted/?key=' . $this->galaxy->getAPIKey();
    }

    $response = $this->galaxy->httpGET($URL);

    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreives a list of datasets associated with a given history.
   *
   * Corresponds to the Galaxy Api method and path:
   * GET /api/histories/{encoded_history_id}/contents/{encoded_content_id}/display
   * history content (dataset).
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
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

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('hist_id', 'hist_content_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/histories/' . $params['hist_id'] . '/contents/' . $params['hist_content_id'] . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreives a list of all datasets.
   *
   * Currently not supported by the Galaxy API
   */
  public function index() {
    $URL = $this->galaxy->getURL() . '/api/datasets/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreives detailed content on a specific dataset.
   *
   * Corresponds to the Galaxy Api function and path:
   * GET /api/datasets/{encoded_dataset_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - dataset_id: The dataset_id's information that the function is to
   *       retreive. To obtain the dataset id, please use the Display function.
   *
   * @return
   *   An array containing information about the matching dataset.
   *
   */
  public function show($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('dataset_id'))) {
      return FALSE;
    }

    $dataset_id = $params['dataset_id'];
    $URL = $this->galaxy->getURL() . '/api/datasets/' . $dataset_id . '/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }
}
