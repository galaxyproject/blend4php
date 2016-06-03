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

class GalaxyFolders {

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
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Retreive information about a specific folder
   *
   * Corresponds to the Galaxy API function/path:
   *   GET /api/folders/{folder_id}
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - folder_id: The folder that you would like to see. Please see the
   *       index() function in this class to obtain folder ids.
   *
   * @return
   *   An array containing information about the specified folder.
   *
   *
   */
   public function show($params) {
     if(array_key_exists('folder_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $params['folder_id'] .'/?key=' . $this->galaxy->getAPIKey();
       $response = $this->galaxy->httpGET($URL);
       return $this->galaxy->expectArray($response);
     }
     $this->galaxy->setError("API", "A 'folder_id' is required in order to show a specific folder.");
     return FALSE;

   }

  /**
   * Create a new folder.
   *
   * Corresponds to the API function/path:
   *   POST /api/folders/{encoded_parent_folder_id}
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *  - parent_folder_id: The id of the parent folder that this folder will be
   *      created under.
   *  - name: The name of your new folder.
   *  - description (optional): The description of your new folder.
   *
   * @return
   *   An array containing information on the new folder.
   *
   *
   */
   public function create($params){
     if(!array_key_exists('parent_folder_id', $params)){
       $this->galaxy->setError("API", "A 'parent_folder_id' is required in order to create a new folder");
       return FALSE;
     }

     if(!array_key_exists('name', $params)){
       $this->galaxy->setError("API", "A 'name' is required in order to create a new folder.");
        return FALSE;
      }

      $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $params['parent_folder_id'] . '/?key=' . $this->galaxy->getAPIKey();
      unset($params['parent_folder_id']);
      $response = $this->galaxy->httpPOST($URL, $params);
      return $this->galaxy->expectArray($response);
   }

  /**
   * Load all permissions for the folder with the given id.
   *
   * Corresponds to the Galaxy API/Path:
   *   GET /api/folders/{folder_id}/permissions
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - folder_id: The id of the folder to view permissions. The id can be
   *       obtained using the index() function in this class.
   *
   * @return
   *   An array containing permission information on a specified folder.
   *
   *
   */
   public function getPermissions($params){
     if(!array_key_exists('folder_id', $params)){
       $this->galaxy->setError("API", "A 'folder_id' is required in order to create a new folder");
       return FALSE;
     }

       $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$params['folder_id'] . '/permissions' .'?key=' . $this->galaxy->getAPIKey();
       $response = $this->galaxy->httpGET($URL);
       return $this->galaxy->expectArray($response);
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
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - folder_id: The folder id you want to set permissions.
   *   - add_ids: An array of users that will have add item permission on the
   *       folder. To obtain a user id, please use the 'Users' class index()
   *       function.
   *   - manage_ids: An array of users that will have manage permission on the
   *       folder.
   *   - modify_ids: An array of users that will have modify permission on the
   *       folder.
   *
   *
   */
   public function setPermissions($params){
     if(array_key_exists('folder_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$params['folder_id'] . '/permissions' .'?key=' . $this->galaxy->getAPIKey();
       $params['action'] = 'set_permissions';
       unset($params['folder_id']);
       $response = $this->galaxy->httpPOST($URL, $params);
       return $this->galaxy->expectArray($response);
     }
   }

  /**
   * Mark the folder as 'deleted' or 'undeleted'.
   *
   * Corresponds to the Galaxy API function at
   *   DELETE /api/folders/{folder_id}/
   *
   * Only admin users can delete/undelete folders
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *  - folder_id: The folder you want to delete/undelete.
   *  - undelete: Specifying whether the item should be deleted (TRUE) or
   *      undeleted (FALSE).
   *
   * @return
   *   Json Array containing information on the deleted (or undeleted)
   *   folder.
   *
   *
   */
   public function delete($params){
     if(!array_key_exists('folder_id', $params)){
       $this->galaxy->setError("API", "A 'folder_id' is required in order to delete/undelete a folder");
       return FALSE;
     }

     if(!array_key_exists('undelete', $params) and $params['undelete'] == TRUE){
       $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$params['folder_id']  .'?key=' . $this->galaxy->getAPIKey(). '&undelete=True';
       return $this->rest->delete($URL);
     }

     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $params['folder_id'] .'?key=' . $this->galaxy->getAPIKey();
     return $this->galaxy->httpDELETE($URL);
   }

  /**
   * Updated the folder's name and description.
   *
   * Corresponds to the Galaxy API/path at:
   *   PATCH /api/folders/{folder_id}/
   *
   *  Only admin users can update folders.
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - folder_id: The folder you want to update
   *   - payload: An array that contains 'name' => [new_name] and
   *       'description' => [can be null].
   *
   * @return
   *   Json array containing details about the deleted file history content.
   *
   *
   */
   public function update($params){
     if(!array_key_exists('folder_id', $params)){
       $this->galaxy->setError("API", "A 'folder_id' is required in order to update a folder");
       return FALSE;
     }
     if(!array_key_exists('payload', $params)){
       $this->galaxy->setError("API", "A 'payload' is required in order to update a folder");
         return FALSE;
     }
     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' .$params['folder_id'] .'/?key=' . $this->galaxy->getAPIKey();
     return $this->galaxy->httpPATCH($URL, $params['payload']);
   }
}