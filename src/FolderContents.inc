<?php
/**
 * @file
 *
 * API operations on folders contents.
 *
 * Functions correspond to the Galaxy API file at:
 * https://github.com/galaxyproject/galaxy/blob/dev/lib/galaxy/webapps/galaxy/api/folders_contents.py
 *
 */
require_once 'GalaxyRequest.inc';


/**
 *
 *
 */
class FolderContents extends GalaxyRequest {


  /**
   *
   * @param unknown $galaxy
   */
   public function __construct($galaxy) {
   	parent::__construct($galaxy);
   }

   /**
    * GET /api/folders/{folder_id}/contents
    *
    * Displays the contents of a folder
    *
    * The $folder_id must have an 'F' prefixing the id string
    *
    * @param str $folder_id
    * The folder's contents that you would like to see
    *
    */
   public function index ($folder_id) {
   	$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $folder_id . '/contents' .'/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }


   /**
    * POST /api/folders/{folder_id}/contents
    *
    *  Create a new library file from an HDA (History Dataset Association)
    *
    * @param string $parent_folder_id
    * The parent folder of the new item
    * @param string $from_hda_id (optional)
    * The id of an accessible HDA to into the library
    * @param string $ldda_messge (optional)
    * ldda - LibraryDatasetDatasetAssociation
    * The new message attribute of the LDDA created
    * @param $extented_metadata (optional)
    * Sub-dictionary containing any extended metadata to associate with the
    * item
    *
    */
   public function create($parent_folder_id, $from_hda_id = NULL, $ldda_message = NULL, $extended_metadata = NULL){
   	$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $parent_folder_id . '/?key=' . $this->galaxy->getAPIKey();
   	$postfields = array(
   			'name' => $name,
   			'description' => $description
   	);
   	return $this->rest->POST($URL, $postfields);
   }

	/**
	 * GET /api/folders/{folder_id}/permissions
	 *
	 * Load all permissions for the folder id.
	 *
	 * @param string $folder_id
	 * The folder you want to view permissions
	 *
	 */
 	public function show($folder_id){
 	 $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id . '/permissions' .'?key=' . $this->galaxy->getAPIKey();
 	 return $this->rest->GET($URL);
 	}

 	/**
 	 * POST /api/folders/{folder_id}/permissions
 	 *
 	 * Set permissions for the folder id.
 	 *
 	 * There are 3 options that can be manipulated:
 	 * 1. Modify library item: Users can modify this library ($folder_id) item
 	 * 2. Add library item: Users can add library items to this ($folder_id) item
 	 * 3. Manage library permissions: Users can manage roles associated with
 	 * 	  permissions on this library item
 	 *
 	 * **IMPORTANT**
 	 * 					The options inputted will wipe the previous users in that
 	 * 					permissions folder (does not append more users to the particular
 	 * 					permissions folder)
 	 *
 	 * @param string $folder_id
 	 * The folder you want to view permissions
 	 * @param list/string $add_ids
 	 * List of users that will have add item permission on the folder
 	 * @param list/string $manage_ids
 	 * List of users that will have manage permission on the folder
 	 * @param list/string $modify_ids
 	 * List of users that will have modify permission on the folder
 	 *
 	 */
 	public function update($folder_id, $add_ids, $manage_ids, $modify_ids){
 		$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id . '/permissions' .'?key=' . $this->galaxy->getAPIKey();
 		$postfields = array(
 				'action' => 'set_permissions',
 				'add_ids[]' => $add_ids,
 				'manage_ids[]' => $manage_ids,
 				'modify_ids[]' => $modify_ids
 		);
 		return $this->rest->POST($URL, $postfields);
 	}

 	/**
 	 * DELETE /api/folders/{folder_id}/
 	 *
 	 * Mark the folder as 'deleted' or 'undeleted'.
 	 *
 	 * Only admin users can delete/undelete folders
 	 *
 	 * @param string $folder_id
 	 * The folder you want to delete/undelete
 	 * @param bool $undelete
 	 * Specifying whether the item should be deleted or undeleted (default false)
 	 */
 	public function delete($folder_id, $undelete = FALSE){
 		if ($undelete == FALSE){
 		$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id .'?key=' . $this->galaxy->getAPIKey();
 		return $this->rest->delete($URL);
 		}
 		else{
 			$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id  .'?key=' . $this->galaxy->getAPIKey(). '&undelete=True';
 			return $this->rest->delete($URL);
 		}
 	}

 	/**
 	 * PATCH /api/folders/{folder_id}/
 	 *
 	 * Updated the folder's name and description.
 	 *
 	 * Only admin users can update folders
 	 *
 	 * @param string $folder_id
 	 * The folder you want to update
 	 * @param  $array $payload
 	 * contains 'name' => [new_name] and 'description' => [can be null]
 	 */
 	public function updateName($folder_id, $payload){
 			$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id .'?key=' . $this->galaxy->getAPIKey();
 			return $this->rest->PATCH($URL, $payload);
 	}

}
