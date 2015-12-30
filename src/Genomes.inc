<?php 
require_once "GalaxyInstance.inc";
require_once 'GalaxyRequest.inc';

class Genomes{
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
	 * Returns a list of installed genomes
	 *
	 * GET /api/genomes
	 *
	 */
	public function index(){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();
		
		$url = $this->galaxy->getURL() . '/api/genomes'  .  '?key=' . $api_key;
		
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
	 * Returns infromation about build <genome_id>
	 *
	 * GET /api/genomes/{genome_id}
	 *
	 */
	public function show($genome_id){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();
		
		$url = $this->galaxy->getURL() . '/api/genomes/' . $genome_id .  '?key=' . $api_key;
		
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
