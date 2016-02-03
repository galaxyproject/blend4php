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
   @param  string  'content_id'  the content to add (dataset id's work) 
   to find dataset id's go to:
   			/api/histories/<history_id>/content  only 'ok' state datasets work
*/ 
	public function create($history_id, $content_id,  $source='hda') {
		$URL = $this->galaxy->getURL(). '/api/histories/'.$history_id .
		'/contents/dataset/?key='. $this->galaxy->getAPIKey();
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
	 
	 @param content_id: the encoded id of the HDA to return (History data association)
	 @param history_id: encoded id string of the HDA's History
	 @return: dictionary containing detailed HDA information
	 */
	public function show($history_id, $content_id) {
		$URL = $this->galaxy->getURL() . '/api/histories/'.$history_id .'/contents/'. $content_id .'/?key='. $this->galaxy->getAPIKey();
		return $this->rest->GET($URL);
	}

/**
 Some functionality from original python function is not available
   PUT /api/histories/{history_id}/contents/{id}
   
   updates the values for the HDA with the given ``id``
   
 * @param string $history_id history id of the history to update
 * @param string $content_id content id of the content to update the history with, can be a dataset
 *   to find dataset id's go to:
   			/api/histories/<history_id>/content, only 'ok' state datasets work 
 * @param string $annotation annotation for the hda 
 */
	public function update($history_id, $content_id,  $annotation =''){
		$URL = $this->galaxy->getURL() .'/api/histories/' .$history_id . '/contents/' 
				. $content_id .'/?key='. $this->galaxy->getAPIKey();
		$elements = array(
			'annotation' => $annotation,	
		);
		return $this->rest->PUT($URL, $elements);
	}
	
/**
 *    DELETE /api/histories/{history_id}/contents/{id}
       
       delete the HDA with the given ``id``
 * 
 * @param string $history_id history id of the history to update
 * @param string $content_id content id of the content to update the history with, can be a dataset
 *   to find dataset id's go to:
   			/api/histories/<history_id>/content, only 'ok' state datasets work 
   @param bool purge
 */
	public function delete($history_id, $content_id, $purge = false){
	 $URL = $this->galaxy->getURL() .'/api/histories/' .$history_id . '/contents/' . $content_id .'/?key='. $this->galaxy->getAPIKey();
	 if($purge)
	 {
	 	$URL .= '&purge=true';
	 }
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
