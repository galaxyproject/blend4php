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
		$URL = '/api/histories/'.$history_id .'/contents/'. $type .'/?key='. $this->galaxy->getAPIKey();
		$inputs = array(
			'source' => $source,
			'content'=> $content,
			'collection_type' => $collection_type,
			'element_identifiers' => $element_identifiers,
			'collection_type' => $collection_type,	
		);
		return $this->rest->POST($URL, $inputs);	
	}
	

	/**
	 *  show( self, trans, id, history_id, **kwd )
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
	 * TODO: payload not inputting value? 
	 update( self, trans, history_id, id, payload, **kwd )
	 PUT /api/histories/{history_id}/contents/{id}
	 updates the values for the HDA with the given ``id``
	
	 param history_id: encoded id string of the HDA's History
	
	 param id: the encoded id of the history to update
	
	 type payload: array
	 param payload: an associative arrray containing any or all the
	 fields in :func:`galaxy.model.HistoryDatasetAssociation.to_dict`
	 and/or the following:
	 annotation: an annotation for the HDA
	
	possible inputs for payload: 
	 "history_dataset_association", metadata,
	 Column( "id", Integer, primary_key=True ),
	 Column( "history_id", Integer, ForeignKey( "history.id" ), index=True ),
	 Column( "dataset_id", Integer, ForeignKey( "dataset.id" ), index=True ),
	 Column( "create_time", DateTime, default=now ),
	 Column( "update_time", DateTime, default=now, onupdate=now ),
	 Column( "state", TrimmedString( 64 ), index=True, key="_state" ),
	 Column( "copied_from_history_dataset_association_id", Integer,
	 ForeignKey( "history_dataset_association.id" ), nullable=True ),
	 Column( "copied_from_library_dataset_dataset_association_id", Integer,
	 ForeignKey( "library_dataset_dataset_association.id" ), nullable=True ),
	 Column( "name", TrimmedString( 255 ) ),
	 Column( "info", TrimmedString( 255 ) ),
	 Column( "blurb", TrimmedString( 255 ) ),
	 Column( "peek" , TEXT ),
	 Column( "tool_version" , TEXT ),
	 Column( "extension", TrimmedString( 64 ) ),
	 Column( "metadata", MetadataType(), key="_metadata" ),
	 Column( "parent_id", Integer, ForeignKey( "history_dataset_association.id" ), nullable=True ),
	 Column( "designation", TrimmedString( 255 ) ),
	 Column( "deleted", Boolean, index=True, default=False ),
	 Column( "visible", Boolean ),
	 Column( "extended_metadata_id", Integer, ForeignKey( "extended_metadata.id" ), index=True ),
	 Column( "hid", Integer ),
	 Column( "purged", Boolean, index=True, default=False ),
	 Column( "hidden_beneath_collection_instance_id",
	
	
	
	 rtype: dict
	 returns: an error object if an error occurred or a dictionary containing
	 any values that were different from the original and, therefore, updated
	 
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
	 * TODO: payload not inputting value?
 	 delete( self, trans, history_id, id, **kwd )
	 DELETE /api/histories/{history_id}/contents/{id}
	 delete the HDA with the given ``id``
	 note:: Currently does not stop any active jobs for which this dataset is an output.

	 param id: the encoded id of the history to delete
     type purge: bool
	 param purge: if True, purge the HDA


	 payload: a dictionary itself containing:
		 purge: if True, purge the HDA
			note:: that payload optionally can be placed in the query string of the request.
			This allows clients that strip the request body to still purge the dataset.
			
			
	returns: an error object if an error occurred or a dictionary containing:
		id: the encoded id of the history,
		deleted: if the history was marked as deleted,
		purged: if the history was purged

	 */
	public function delete($history_id, $hda_id, $purge = false){
	 $URL = $this->galaxy->getURL() .'/api/histories/' .$history_id . '/contents/' . $hda_id .'/?key='. $this->galaxy->getAPIKey();
	 //print $URL;
	// $inputs = json_encode(array('purged' => $purge));
	 return $this->rest->Delete($URL);
		
	}
	
	
	/**
	 * index( self, trans, history_id, ids=None, **kwd )
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
