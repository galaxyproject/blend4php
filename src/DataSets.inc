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

/**
 * @defgroup data_sets_class DataSets class
 * @{
 *   The DataSets Class interacts with Galaxy to manage DataSets.
 *   The functions in this class correspond to the Galaxy API functions and
 *   are named similarly to their Python counterpart.
 * @}
 */
require_once 'HTTPRequest.inc';


class Datasets extends HTTPRequest {
  private $galaxy;

   /**
   * The DataSets constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a DataSet object.
   *
   * @ingroup data_sets_class
   */
   public function __construct($galaxy) {
     $this->galaxy = $galaxy;

     parent::__construct();
   }

   /**
    * Retreive information about datasets made by converting
    *  to a new file format.
    *
    * Corresponds to the galaxy API function at:
    *  GET /api/datasets/{dataset_id}/converted/{ext}
  *
    * @param $dataset_id
    *   The dataset id of the information to pull.
    *   Can be obtained from this function's display()
    * @param $extension
    *   (optional )The file extension to look for
    *
    * @return
    *   An array containing information about the matching dataset(s).
    *
    * @defgroup data_sets_class
    */
   public function converted($dataset_id, $extension=NULL) {
     if($URL !== NULL) {
       $URL = $this->galaxy->getURL() . '/api/datasets/' . $dataset_id . '/converted/' . $extension . '/?key=' . $this->galaxy->getAPIKey();
     }
     else {
       $URL = $this->galaxy->getURL() . '/api/datasets/' . $dataset_id . '/converted/?key=' . $this->galaxy->getAPIKey();
     }

     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Retreives a list of datasets associated with a given history.
    *
    * Corresponds to the Galaxy Api method and path:
    *   GET /api/histories/{encoded_history_id}/contents/{encoded_content_id}/display
    *   history content (dataset).
    *
    * @param $hist_id
    *   The history id of the datasets to find.
    * @param $hist_content_id
    *   The history content whose datasets to list.
    *   Please see the HistoryContents class to obtain the history content id
    *
    * @return
    *   An array containing information about the matching dataset(s).
    *
    * @defgroup data_sets_class
    */
   public function display($hist_id, $hist_content_id){
     $URL = $this->galaxy->getURL() . '/api/histories/' . $hist_id . '/contents/' . $hist_content_id. '/?key=' . $this->galaxy->getAPIKey();

     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Retreives a list of all datasets.
    *
    * Currently not supported by the Galaxy API
    *
    * @defgroup data_sets_class
    */
   public function index(){
     $URL = $this->galaxy->getURL() . '/api/datasets/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Retreives detailed content on a specific dataset.
    *
    * Corresponds to the Galaxy Api function and path:
    *   GET /api/datasets/{encoded_dataset_id}
    *
    * @param $dataset_id
    *   The dataset id whos information the function is retreiving.
    *   To obtain the dataset id, please use the Display function.
    *
     * @return
     *   An array containing information about the matching dataset.
    *
     * @defgroup data_sets_class
    */
   public function show($dataset_id){
     $URL = $this->galaxy->getURL().'/api/datasets/' . $dataset_id . '/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }
}
