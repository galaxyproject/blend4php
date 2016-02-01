<?php
/**
 * @file
 *
 * API operations on a historycontent.
 *
 * Functions correspond to the Galaxy API file at:
 * https://github.com/galaxyproject/galaxy/blob/dev/lib/galaxy/webapps/galaxy/api/histories.py
 *
 */

require_once 'GalaxyRequest.inc';


/**

 */
class HistoryContents extends GalaxyRequest {
	
	public function __construct($galaxy){
		parent::__construct($galaxy);
	}
	
	
/**
#complete!! 
  	POST /api/histories/{history_id}/contents/datasets
           
    create a new History Dataset Association by copying an 
    accessible LibraryDataset or History Dataset Association, and assigning it to the given history_id
        
    NOTE, currently, only creating new 'datasets' is supported, 
    as opposed to creating dataset Collections  
          
   @param  string history_id: encoded id string of the new HDA's History
   @param  string  'source'  The source of the new dataset, either hda or library
   @param  string  'content_id'  
*/ 
	public function create($history_id, $content_id,  $source='hda') {
		$URL = $this->galaxy->getURL(). '/api/histories/'.$history_id .
		'/contents/dataset/?key='. $this->galaxy->getAPIKey();
		print($URL);
		$elements = array(
			'source' => $source,
			'content'=> $content_id,
			'collection_type' => $collection_type,
			'element_identifiers' => $element_identifiers,
			'collection_type' => $collection_type,	
		);
		$notNullInputs = array();
		foreach($elements as $element=>$value) {
			if($value != NULL ) {
				$notNullInputs[$element] = $value;
			}
		}
		return $this->rest->POST($URL, $notNullInputs);	
	}
	

	/**
#complete
	 GET /api/histories/{history_id}/contents/{id}
	 
	 @param hda_id: the encoded id of the HDA to return (History data association)
	 @param history_id: encoded id string of the HDA's History

	 @return: dictionary containing detailed HDA information
	 */
	public function show($history_id, $hda_id) {
		$URL = $this->galaxy->getURL() . '/api/histories/'.$history_id .'/contents/'. $hda_id .'/?key='. $this->galaxy->getAPIKey();
		return $this->rest->GET($URL);
	}

	
	/**
	  TODO: What are the fileds in galaxy.mmodel.HistoryDatasetAssociation.to_dict? 
	  Apparently these are the fields that must go into our function
	 
	 */
	
	public function update($history_id, $hda_id, $payload=NULL){
		$URL = $this->galaxy->getURL() .'/api/histories/' .$history_id . '/contents/' . $hda_id .'/?key='. $this->galaxy->getAPIKey();
		if($payload == null) {
			$payload = array("Nothing"=>"Nothing to see here");
		}
		//$payload = array (json_encode($payload));
		var_dump($payload);
		//$payload = json_encode($payload,true);
		//$payload = json_encode($payload,true);
	
		//var_dump($payload);
	
		return $this->rest->PUT($URL, $payload);
	}
	
	
	
	/**
	 * TODO:
	 * 	

	 */
	public function delete($history_id, $hda_id, $purge = false){
	 $URL = $this->galaxy->getURL() .'/api/histories/' .$history_id . '/contents/' . $hda_id .'/?key='. $this->galaxy->getAPIKey();
	 //print $URL;
	// $inputs = json_encode(array('purged' => $purge));
	 return $this->rest->Delete($URL);
		
	}
	
	
	/**
#complete!
	   GET /api/histories/{history_id}/contents
	 
	  @param history_id: encoded id string of the HDA's History
	  @param ids: (optional) a comma separated string of encoded `HDA` ids
	  
	  @return: dictionaries containing summary or detailed HDA information
	 */
	public function index($history_id, $ids = NULL){
		
		$URL = $this->galaxy->getURL() .'/api/histories/' .$history_id . '/contents';
		$URL .='/?key='. $this->galaxy->getAPIKey();
		if($ids !==NULL) {
			$URL .= '/&ids=' .$ids;
		}					
		return $this->rest->GET($URL);			
	}
	
		
	
	
	
}
