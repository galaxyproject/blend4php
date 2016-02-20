<?php
/**
 * @file
 *
 * Implements the Folders class.
 *
 * The Folders Class interacts with Galaxy to manage contents of a folder.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

/**
 * @defgroup folders_class Folders class
 * @{
 *   The folders Class interacts with Galaxy to manage
 *   its folders. The functions in this class correspond to the Galaxy
 *   API functions and are named similarly to their Python counterpart.
 * @}
 */
require_once 'GalaxyRequest.inc';



class Folders extends GalaxyRequest {


  /**
	* The Folders constructor.
	*
	* @param GalaxyInstance $galaxy
	*   A GalaxyInstance object.
	*
	* @return
	*   An instance of a Folders object.
	*
	* @ingroup folder_contents_class
	*/
   public function __construct($galaxy) {
   	parent::__construct($galaxy);
   }

   /**
    * Retreive information about a specific folder
    * 
    * Corresponds to the Galaxy API function/path:
    *   GET /api/folders/{folder_id}
    *
    * @param $folder_id
    *   The folder that you would like to see. Please see the index()
    *   function in this class to obtain folder ids.
    *   
    * @return 
    *   JSON array containing information about the specified folder.   
    *   
	* @ingroup folder_contents_class
    */
   public function show ($folder_id) {
   	$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $folder_id .'/?key=' . $this->galaxy->getAPIKey();
   	return $this->rest->GET($URL);
   }

   /**
    * Create a new folder.
    * 
    * Corresponds to the API function/path:
    *   POST /api/folders/{encoded_parent_folder_id}
    *
    * @param $parent_folder_id
    *   The id of the parent folder that this folder will be created under.
    * @param $name
    *   The name of your folder.
    * @param $description
    *   The description of your folder.
    *   
    * @return 
    *   A JSON array containing information on the new folder.
    *   
	* @ingroup folder_contents_class   
    */
   public function create($parent_folder_id, $name, $description){
   	$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $parent_folder_id . '/?key=' . $this->galaxy->getAPIKey();
   	$postfields = array(
   			'name' => $name,
   			'description' => $description
   	);
   	return $this->rest->POST($URL, $postfields);
   }

	/**
	 * Load all permissions for the folder with the given id.
	 * 
	 * Corresponds to the Galaxy API/Path:
	 *   GET /api/folders/{folder_id}/permissions
	 *
	 * @param $folder_id
	 *   The id of the folder to view permissions. The id can be ontained
	 *   using the index() function in this class.
	 *
     * @return 
     *   A JSON array containing permission information on a specified folder.
     *   
	 * @ingroup folder_contents_class  
	 */
 	public function get_permissions($folder_id){
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
 	public function set_permissions($folder_id, $add_ids, $manage_ids, $modify_ids){
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
 	public function update($folder_id, $payload){
 			$URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id .'?key=' . $this->galaxy->getAPIKey();
 			return $this->rest->PATCH($URL, $payload);
 	}

}