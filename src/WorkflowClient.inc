<?php 

require_once "GalaxyInstance.inc";

class WorkflowClient {
	
	private $galaxy = NULL;
	
	function __construct(GalaxyInstance $galaxy) {
      $this->galaxy = $galaxy;
	}
	
	/**
	 * Delete a workflow identified by workflow_id.
	 * 
	 * @param $workflow_id
	 *   Encoded workflow ID
	 */
	public function delete_workflow($workflow_id) {
		
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
		
	}
	
	/**
	 * Exports a workflow in json format to a given local path.
	 *
	 * 
	 * 
	 * @param $workflow_id
	 *   Encoded workflow ID
	 * @param $file_local_path
	 *   Local path to which the exported file will be saved. (Should not contain 
	 *   filename if use_default_name=True).
	 * @param $use_default_filename
	 *  If the use_default_name parameter is True, the exported file will be saved 
	 *  as file_local_path/Galaxy-Workflow-%s.ga, where %s is the workflow name. 
	 *  If use_default_name is False, file_local_path is assumed to contain the 
	 *  full file path including filename.
	 */
	public function export_workflow_to_local_path($workflow_id, $file_local_path, $use_default_filename =  TRUE) {
		
	}
	
	
	/**
	 * 
	 * @param $workflow_id
	 *   Encoded workflow ID
	 * @param $label
	 */
	public function get_workflow_inputs($workflow_id, $label) {
		
	}
	
	/**
	 * Get workflows and/or filter specific one(s) providing $name or $workflow_id
	 * 
	 * @param $workflow_id
	 * @param $name
	 * @param $published
	 * Last Edited: @timestamp Sep 3, 2015 10:55:09 AM
	 */
	public function get_workflows($workflow_id = NULL, $name = NULL, $published = FALSE) {
		
	}
	
	/**
	 * 
	 * @param $workflow_id
	 *   Encoded workflow ID
	 */
	public function import_shared_workflow($workflow_id) {
	
	}
	
	/**
	 * 
	 * @param $file_local_path
	 */
	public function import_workflow_from_local_path($file_local_path) {
		
	}
	/**
	 * 
	 * @param $workflow_json
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
	public function run_workflow($workflow_id, $dataset_map=None, $params = NULL, 
			$history_id = NULL, $history_name = NULL, $import_inputs_to_history = FALSE, 
			$replacement_params = NULL) {
	
	}
	/**
	 * Display information needed to run a workflow.
	 * 
	 * @param $workflow_id
	 *   Encoded workflow ID.
	 * @return
	 *   A description of the workflow and its inputs as a JSON object. For example:
   *  {u'id': u'92c56938c2f9b315',
   *    u'inputs': {u'23': {u'label': u'Input Dataset', u'value': u''}},
   *    u'name': u'Simple',
   *    u'url': u'/api/workflows/92c56938c2f9b315'}
	 */
	public function show_workflow($workflow_id) {
		
	}
	
}