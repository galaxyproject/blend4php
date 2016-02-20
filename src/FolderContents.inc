<?php
/**
 * @file
 *
 * Implements the FolderContents class.
 *
 * The FolderContents Class interacts with Galaxy to manage contents of a folder.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

/**
 * @defgroup folder_contents_class DataTypes class
 * @{
 *   The folder contents Class interacts with Galaxy to manage 
 *   content of folders. The functions in this class correspond to the Galaxy 
 *   API functions and are named similarly to their Python counterpart.
 * @}
 */
require_once 'GalaxyRequest.inc';


class FolderContents extends GalaxyRequest {

  /**
	* The FolderContents constructor.
	*
	* @param GalaxyInstance $galaxy
	*   A GalaxyInstance object.
	*
	* @return
	*   An instance of a FolderContents object.
	*   
	* @ingroup folder_contents_class
	*/
   public function __construct($galaxy) {
   	parent::__construct($galaxy);
   }

   /**
    * Displays the contents of a folder.
    * 
    * Corresponds to the Galaxy API/path:
    *   GET /api/folders/F{folder_id}/contents.
    *
    * @param $folder_id
    *   Id of the folder whos contents to display. 
    *   To obtain id, see the index() function in the Folder class.
    * @return 
    *   JSON array of The specified folder's contents
    *
	* @ingroup folder_contents_class
    */
   public function index ($folder_id) {
   	$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $folder_id . '/contents' .'/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }

   /**
    * Create a new content for specified folder
    * 
    * Corresponds to the Galaxy API/path at: 
    *   POST /api/folders/{folder_id}/contents
    *
    * @param $parent_folder_id
    *   The parent folder of the new item
    *   To obtain id, see the index() function in the Folder class.
    * @param $from_hda_id (optional)
    *   The id of an accessible HDA to into the library
    *   To obtain this id, see index() in HistoryContents class.
    * @param $ldda_messge (optional)
    *   Any message to send along with the LibraryDatasetDatasetAssociation. 
    * @param $extented_metadata (optional)
    *   Sub-dictionary containing any extended metadata to associate with the
    *   item.
    *   
    * @return 
    *   JSON array containing the newly created folder content 
    *    
	* @ingroup folder_contents_class
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
	 * Retreive all permissions for the folder id.
	 * 
	 * Corresponds to the Galaxy API/path:
	 *   GET /api/folders/{folder_id}/permissions
	 *
	 * @param $folder_id
	 *   The folder you want to view permissions
	 *
	 * @return 
	 *   Json array containing details about the permission of the folder.
	 *   
	 * @ingroup folder_contents_class
	 */
 	public function show($folder_id){
 	 $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id . '/permissions' .'?key=' . $this->galaxy->getAPIKey();
 	 return $this->rest->GET($URL);
 	}

 	/**
 	 * Set the permissions for a specified folder
 	 * 
 	 * Corresponds to the Galaxy API/PATH
 	 *   POST /api/folders/{folder_id}/permissions
 	 *
 	 * There are 3 options that can be manipulated:
 	 *   1. Modify library item: Users can modify this library ($folder_id) item.
 	 *   2. Add library item: Users can add library items to this ($folder_id) item.
 	 *   3. Manage library permissions: Users can manage roles associated with
 	 * 	    permissions on this library item.
 	 *  The options inputted will wipe the previous users in that
 	 *  permissions folder (does not append more users to the particular
 	 *  permissions folder).
 	 *
 	 * @param $folder_id
 	 *   The folder id of the folder to be updated. To obtain folder ids,
 	 *   please see int index() function of the folder class.
 	 * @param $add_ids
 	 *   List of user ids that will have add item permission on the folder
 	 *   To obtain uder ids, please see the index() function of the user class.
 	 * @param $manage_ids
 	 *   List of users ids that will have manage permission on the folder.
 	 *   To obtain uder ids, please see the index() function of the user class.
 	 * @param $modify_ids
 	 *   List of users ids that will have modify permission on the folder.
 	 *   
	 * @return 
	 *   Json array containing details about the new permissions of the folder.
 	 *
     * @ingroup folder_contents_class
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
 	 * Mark a specified folder as 'deleted' or 'undeleted'.
 	 * 
 	 * Corresponds to Galaxy API/path at: 
 	 *   DELETE /api/folders/{folder_id}/
 	 *
 	 * @param $folder_id
 	 *   The folder to delete or undelete.
 	 * @param $undelete
 	 *   Specifies whether the item should be deleted or undeleted.
 	 *   
	 * @return 
	 *   Json array containing details about the deleted file history content.
	 *   
     * @ingroup folder_contents_class
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
 	 * Updated the folder's name and description.
 	 * 
 	 * Corresponds to the Galaxy API/path at:
 	 *   PATCH /api/folders/{folder_id}/
 	 *
 	 *  Only admin users can update folders.
 	 *
 	 * @param string $folder_id
 	 *   The folder you want to update
 	 * @param  $array $payload
 	 *   contains 'name' => [new_name] and 'description' => [can be null].
 	 *   
 	 * @return 
	 *   Json array containing details about the deleted file history content.
 	 * 
     * @ingroup folder_contents_class
 	 */
 	public function updateName($folder_id, $payload){
 			$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id .'?key=' . $this->galaxy->getAPIKey();
 			return $this->rest->PATCH($URL, $payload);
 	}
 	
}
