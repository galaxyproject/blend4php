<?php
require_once "GalaxyInstance.inc";

class WorkflowClient {
  private $galaxy = NULL;

  /**
   * Implements the constructor.
   *
   * @param GalaxyInstance $galaxy
   */
  function __construct(GalaxyInstance $galaxy) {
    $this->galaxy = $galaxy;
  }

  /**
   * Delete a workflow identified by workflow_id.
   *
   * @param $workflow_id
   */
  public function delete_workflow($workflow_id) {
    // TODO: We should return something to the user saying that
    // the delete was successful or not successful in
    // deleting the workflow

    // Set the POST data
    $postdata = http_build_query(array(
      'key' => $this->galaxy->getAPIKey()
    ));

    // Set the POST options
    $opts = array(
      'http' => array(
        'method' => 'DELETE',
        'content' => $postdata
      )
    );

    // Create the POST context
    $context = stream_context_create($opts);

    // POST the data to an api
    $url = $this->galaxy->getURL() . '/api/workflows/' . base64_encode($workflow_id);
    $result = file_get_contents($url, false, $context);
  }

  /**
   * Exports a workflow
   *
   * @param $workflow_id
   *   Encoded workflow ID.
   * @return
   *   Dict representing the workflow requested.
   */
  public function export_workflow_json($workflow_id) {
    // I do not know what a Dict is
    $dict = 'potato';
    // Based off of some reading this should be a put not a post
    // http://stackoverflow.com/questions/630453/put-vs-post-in-rest

    $putdata = http_build_query(array(
      // I'm not sure if this is right
      // I'm copying what Stephen had developed in
      // the function above
      // TODO: Exporting a workflow involves making url for
      // that resource so this should be included...
      'key' => $this->galaxy->getAPIKey(),
      // It probably doesn't work this way but I'm going to
      // put it here for now so Stephen can at least see it
      // and attempt to make sense of it
      /**
       * I want this URL to be visible to the end user
       */
      'url' => $this->galaxy->getURL() . '/api/workflows/' . base64_encode($workflow_id)
    ));
    // Set the PUT options
    $opts = array(
      'http' => array('method' => 'PUT','content' => $putdata
      )
    );
    // Create the PUT context
    $context = stream_context_create($opts);

    // PUT the data to an api
    $url = $this->galaxy->getURL() . '/api/workflows/' . base64_encode($workflow_id);
    $result = file_get_contents($url, false, $context);

    return $dict;
  }

  /**
   * Exports a workflow in json format to a given local path.
   *
   * @param $workflow_id
   *   Encoded workflow ID
   * @param $file_local_path Local
   *   Path to which the exported file will be saved. (Should not contain
   *   filename if use_default_name=True).
   * @param $use_default_filename
   *   If the use_default_name parameter is True, the exported file will be saved
   *   as file_local_path/Galaxy-Workflow-%s.ga, where %s is the workflow name.
   *   If use_default_name is False, file_local_path is assumed to contain the
   *   full file path including filename.
   */
  public function export_workflow_to_local_path($workflow_id, $file_local_path,
    $use_default_filename = TRUE) {
    // How to you send a resource to local machine? how would that be
    // an HTTP request?
    // Can you PUT/POST into a user local path?
    // http://stackoverflow.com/questions/386845/http-headers-for-file-downloads
    // This says to "offer" to put the data in a file

    // Found on http://yagudaev.com/posts/resolving-php-relative-path-problem/
    // Supposedly we could run a script into the local filesystem of our end
    // user that is we run a script that will transfer the specified workflow
    // to the user's downloading area
    // include (dirname (__FILE__) . "");

    // http://php.net/manual/en/function.readfile.php
    // Or should I use this?
    // We can use readfile

    // hopefully this will pull up the location of the selected workflow
    $file = $this->galaxy->getURL() . '/api/workflows/' . base64_encode($workflow_id);

    // This was copied from http://php.net/manual/en/function.readfile.php
    // TODO; This needs to be reformatted in the http_build_query style
    if (file_exists($file)) {
      header('Content-Description: File Transfer');
      header('Content-Type: application/octet-stream');
      header('Content-Disposition: attachment; filename="' . basename($file) . '"');
      header('Expires: 0');
      header('Cache-Control: must-revalidate');
      header('Pragma: public');
      header('Content-Length: ' . filesize($file));
      readfile($file);
    }
  }
  /**
   *
   * @param $workflow_id Encoded
   *   workflow ID
   * @param $label
   */
  public function get_workflow_inputs($workflow_id, $label) {
  }

  /**
   *
   * @param
   *          $workflow_id
   * @param
   *          $name
   * @param
   *          $published
   */
  public function get_workflows($workflow_id = NULL, $name = NULL, $published = FALSE) {
  }

  /**
   *
   * @param $workflow_id Encoded
   *          workflow ID
   */
  public function import_shared_workflow($workflow_id) {
  }

  /**
   *
   * @param
   *          $file_local_path
   */
  public function import_workflow_from_local_path($file_local_path) {
  }
  /**
   *
   * @param
   *          $workflow_json
   */
  public function import_workflow_json($workflow_json) {
  }
  /**
   *
   * @param $workflow_id
   *   Encoded workflow ID
   * @param $dataset_map
   * @param $params
   * @param $history_id
   * @param $history_name
   * @param $import_inputs_to_history
   * @param $replacement_params
   */
  public function run_workflow($workflow_id, $dataset_map = None, $params = NULL, $history_id = NULL,
    $history_name = NULL, $import_inputs_to_history = FALSE, $replacement_params = NULL) {
  }
  /**
   * Display information needed to run a workflow.
   *
   * @param $workflow_id
   *   Encoded workflow ID.
   * @return
   *   A description of the workflow and its inputs as a JSON object. For example:
   *    {
   *      u'id': u'92c56938c2f9b315',
   *      u'inputs': {u'23': {u'label': u'Input Dataset', u'value': u''}},
   *      u'name': u'Simple',
   *      u'url': u'/api/workflows/92c56938c2f9b315'
   *    }
   */
  public function show_workflow($workflow_id) {
  }
}
