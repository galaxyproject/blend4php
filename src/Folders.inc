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

require_once 'HTTPRequest.inc';

class Folders extends HTTPRequest {

  private $galaxy;

  /**
  * The Folders constructor.
  *
  * @param GalaxyInstance $galaxy
  *   A GalaxyInstance object.
  *
  * @return
  *   An instance of a Folders object.
  *
  * 
  */
   public function __construct($galaxy) {
     $this->galaxy = $galaxy;
      parent::__construct();
   }
   /**
    * Retreive information about folders.
    *
    * Corresponds to the Galaxy API function/path:
    *   GET /api/folders/
    *
    * @return
    *   An array containing information about the specified folder.
    *
    * 
    */
   public function index() {
     // Currentlly, listing all of the folders is not implmented. But we
     // provide the API function for when it is.

     $URL = $this->galaxy->getURL() . '/api/folders?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
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
    *   An array containing information about the specified folder.
    *
    * 
    */
   public function show($folder_id) {
     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $folder_id .'/?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
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
    *   The name of your new folder.
    * @param $description
    *   The description of your new folder.
    *
    * @return
    *   An array containing information on the new folder.
    *
  * 
    */
   public function create($parent_folder_id, $name, $description){
     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $parent_folder_id . '/?key=' . $this->galaxy->getAPIKey();
     $postfields = array(
         'name' => $name,
         'description' => $description
     );
     $response = $this->httpPOST($URL, $postfields);
     return $this->expectArray($response);
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
     *   An array containing permission information on a specified folder.
     *
   * 
   */
   public function getPermissions($folder_id){
    $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id . '/permissions' .'?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }

   /**
    * Set permissions for a specified folder.
    *
    * Corresponds to the Galaxy API function/path at:
    *   POST /api/folders/{folder_id}/permissions
    * There are 3 options that can be manipulated:
    * 1. Modify library item: Users can modify this library ($folder_id) item
    * 2. Add library item: Users can add library items to this ($folder_id) item
    * 3. Manage library permissions: Users can manage roles associated with
    *     permissions on this library item
    *
    * @param $folder_id
    *   The folder you want to view permissions. To obtain a folder id, please
    *   use the index() function in this class.
    * @param $add_ids
    *   List of users that will have add item permission on the folder. To
    *   obtain a user id, please use the user class's index() function.
    * @param $manage_ids
    *   List of users that will have manage permission on the folder
    * @param $modify_ids
    *   An array of users that will have modify permission on the folder
    *
    * 
    */
   public function setPermissions($folder_id, $add_ids, $manage_ids, $modify_ids){
     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id . '/permissions' .'?key=' . $this->galaxy->getAPIKey();
     $postfields = array(
         'action' => 'set_permissions',
         'add_ids[]' => $add_ids,
         'manage_ids[]' => $manage_ids,
         'modify_ids[]' => $modify_ids
     );
     $response = $this->httpPOST($URL, $postfields);
     return $this->expectArray($response);
   }

   /**
    * Mark the folder as 'deleted' or 'undeleted'.
    *
    * Corresponds to the Galaxy API function at
    *   DELETE /api/folders/{folder_id}/
    *
    * Only admin users can delete/undelete folders
    *
    * @param $folder_id
    *   The folder you want to delete/undelete. To obtain a folder id, please
    *   use this class's index() function.
    * @param $undelete
    *   Specifying whether the item should be deleted(true) or undeleted
    *   (false).
    *
    * @return
    *   Json Array containing information on the deleted (or undeleted)
    *   folder.
    *
    * 
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
    * @param $folder_id
    *   The folder you want to update
    * @param $payload
    *   An array that contains 'name' => [new_name] and 'description' => [can be null].
    *
    * @return
    *   Json array containing details about the deleted file history content.
    *
    * 
    */
   public function update($folder_id, $payload){
     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$folder_id .'/?key=' . $this->galaxy->getAPIKey();
     return $this->rest->PATCH($URL, $payload);
   }

}