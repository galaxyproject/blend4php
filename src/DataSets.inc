<?php 
require_once "GalaxyInstance.inc";
require_once 'GalaxyRequest.inc';

class DataSets{
	private $galaxy = NULL;
	// A variable to set to true if debugging, Toggles print statements
	private $debug = True;
	
	/**
	 * Implements the constructor.
	 *
	 * @param GalaxyInstance $galaxy
	 */
	function __construct($galaxy) {
		$this->galaxy = $galaxy;
	}
	
	/**
	 * Lists history datasets
	 *
	 * GET /api/datasets
	 *
	 */
	public function index(){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();
		
		$url = $this->galaxy->getURL() . '/api/datasets'  .  '?key=' . $api_key;
		
		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
		
		$result = curl_exec($i);
			
		$info = curl_getinfo($i);
			
		$array = json_decode($result, true);
		
		print_r ($array);
			
		curl_close($i);
	
	}
	
	/**
	 * Returns infromation about build <dataset_id>
	 *
	 * GET /api/datasets/{dataset_id}
	 *
	 */
	public function show($dataset_id){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();
		
		$url = $this->galaxy->getURL() . '/api/datasets/' . $dataset_id .  '?key=' . $api_key;
		
		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
		
		$result = curl_exec($i);
			
		$info = curl_getinfo($i);
			
		$array = json_decode($result, true);
		
		print_r ($array);
			
		curl_close($i);
	}
	/**
	 * Displays history content (dataset).
	 * 
	 * @param  $history_id
	 * @param  $content_id
	 * 
	 * GET /api/histories/{encoded_history_id}/contents/{encoded_content_id}/display
	 * 
	 */
	public function display($history_id, $content_id){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();
		
		$url = $this->galaxy->getURL() . '/api/histories/' . $history_id . '/contents/' . $content_id . '/display' . '?key=' . $api_key;
		
		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
		
		$result = curl_exec($i);
			
		$info = curl_getinfo($i);
			
		$array = json_decode($result, true);
		
		print_r ($array);
			
		curl_close($i);
	}
	
	public function converted ($dataset_id, $ext){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();
		
		$url = $this->galaxy->getURL() . '/api/histories/' . $history_id . '/contents/' . $content_id . '/display' . '?key=' . $api_key;
		
		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
		
		$result = curl_exec($i);
			
		$info = curl_getinfo($i);
			
		$array = json_decode($result, true);
		
		print_r ($array);
			
		curl_close($i);
	}
	
}

?>

