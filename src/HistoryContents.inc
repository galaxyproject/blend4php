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
	TODO: examples. See also bioblend and API tests for specific examples.

  POST /api/histories/{history_id}/contents/{type}
           
       create a new HDA by copying an accessible LibraryDataset
      
         
   @param  string - history_id: encoded id string of the new HDA's History

   @param  string - type: Type of history content - 'dataset' (default) or
                      'dataset_collection'.

         copy from library (for type 'dataset'):
   @param     'source'    = 'library'
   @param     'content'   = [the encoded id from the library dataset]

         copy from library folder (for type 'dataset'):
   @param    'source'    = 'library_folder'
   @param    'content'   = [the encoded id from the library folder]

         copy from history dataset (for type 'dataset'):
   @param    'source'    = 'hda'
   @param    'content'   = [the encoded id from the HDA]

         copy from history dataset collection (for type 'dataset_collection')
   @param    'source'    = 'hdca'
   @param    'content'   = [the encoded id from the HDCA]

         create new history dataset collection (for type 'dataset_collection')
   @param    'source'              = 'new_collection' (default 'source' if type is
                                    'dataset_collection' - no need to specify this)
            'collection_type'     = For example, "list", "paired", "list:paired".
            'name'                = Name of new dataset collection.
            'element_identifiers' = Recursive list structure defining collection.
                                    Each element must have 'src' which can be
                                    'hda', 'ldda', 'hdca', or 'new_collection',
                                    as well as a 'name' which is the name of
                                    element (e.g. "forward" or "reverse" for
                                    paired datasets, or arbitrary sample names
                                    for instance for lists). For all src's except
                                    'new_collection' - a encoded 'id' attribute
                                    must be included wiht element as well.
                                    'new_collection' sources must defined a
                                    'collection_type' and their own list of
                                    (potentially) nested 'element_identifiers'.

	 */	
	
	public function create($history_id,  $content=NULL,  $type='dataset', $source='new_collection', $collection_type ='list',
			$name=NULL, $element_identifiers = NULL) {
		$URL = '/api/histories/'.$history_id .'/contents/'. $type .'/?key ='. $this->galaxy->getAPIKey();
		$inputs = array(
			'source' => $source,
			'content'=> $content,
			'collection_type' => $collection_type,
			'element_identifiers' => $element_identifiers,
			'collection_type' => $collection_type,	
		);
		return $this->rest->POST($URL, $inputs);	
	}
	
	
}
