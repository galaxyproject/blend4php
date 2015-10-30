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
 *        create( self, trans, history_id, payload, **kwd )
        * POST /api/histories/{history_id}/contents/{type}
            create a new HDA by copying an accessible LibraryDataset
      
         
        @param  str - history_id: encoded id string of the new HDA's History

        @param  str - type: Type of history content - 'dataset' (default) or
                      'dataset_collection'.

        @param  assoc-array payload: containins:
            copy from library (for type 'dataset'):
            'source'    = 'library'
            'content'   = [the encoded id from the library dataset]

            copy from library folder
            'source'    = 'library_folder'
            'content'   = [the encoded id from the library folder]

            copy from history dataset (for type 'dataset'):
            'source'    = 'hda'
            'content'   = [the encoded id from the HDA]

            copy from history dataset collection (for type 'dataset_collection')
            'source'    = 'hdca'
            'content'   = [the encoded id from the HDCA]

            create new history dataset collection (for type 'dataset_collection')
            'source'              = 'new_collection' (default 'source' if type is
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
	public function create($history_id, $type='dataset'){
		
	}
	
	
}
