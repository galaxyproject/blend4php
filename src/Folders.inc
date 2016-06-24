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

class GalaxyFolders {

  /** The GalaxyInstance object */
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
   public function __construct(GalaxyInstance $galaxy) {
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
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/folders/{folder_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
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
   * Creates a new folder.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/folders/{encoded_parent_folder_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - parent_id: The id of the parent folder or library into which the
   *      folder will be placed.
   *  - name: The name of the folder.
   *  - description: (Optional) A description of the folder.
   *
   * @return
   *   An associative array containing details about the created folder such
   *   as the creation time, access constraints, location, etc.
   */
  public function create($params){
    if(!array_key_exists('parent_id', $params)){
      $this->galaxy->setError("API", "A 'parent_id' is required in order to create a new folder");
      return FALSE;
    }

    if(!array_key_exists('name', $params)){
      $this->galaxy->setError("API", "A 'name' is required in order to create a new folder.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $params['parent_id'] . '/?key=' . $this->galaxy->getAPIKey();
    unset($params['parent_id']);
    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Load all permissions for the folder with the given id.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/folders/{folder_id}/permissions
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - folder_id: The id of the folder to view permissions. The id can be
   *       obtained using the index() function in this class.
   *
   * @return
   *   An array containing permission information on a specified folder.
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
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/folders/{folder_id}/permissions
   *
   * This funciton requires the folder ID and a set of user IDs that will
   * receive the desired permissions. To obtain user IDs, use the GalaxyUsers
   * class.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - folder_id: The folder id to set permissions.
   *   - add_ids: An array of user IDs that should be given permission to
   *     add items to the folder.
   *   - manage_ids: An array of user IDs that should be given permission to
   *     manage the folder.
   *   - modify_ids: An array of user IDs that should be given permission to
   *     modify the folder.
   *
   * @return
   *   An associative array containing details about newly set permissions.
   */
   public function setPermissions($params){
     if(!array_key_exists('folder_id', $params)){
       $this->galaxy->setError("API", "A 'folder_id' is required in order to set permissions.");
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $params['folder_id'] . '/permissions' .'?key=' . $this->galaxy->getAPIKey();
     $params['action'] = 'set_permissions';
     unset($params['folder_id']);
     $response = $this->galaxy->httpPOST($URL, $params);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Mark the folder as 'deleted' or 'undeleted'.
   *
   * Corresponds to an HTTP DELETE on the Galaxy API path
   *   /api/folders/{folder_id}/
   *
   * Only admin users can delete/undelete folders
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *  - folder_id: The folder you want to delete/undelete.
   *  - undelete: Specifying whether the item should be deleted (TRUE) or
   *      undeleted (FALSE).
   *
   * @return
   *   An array containing information on the deleted (or undeleted)
   *   folder.
   */
   public function delete($params){
     if(!array_key_exists('folder_id', $params)){
       $this->galaxy->setError("API", "A 'folder_id' is required in order to delete/undelete a folder");
       return FALSE;
     }

     if(!array_key_exists('undelete', $params) and $params['undelete'] == TRUE){
       $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $params['folder_id']  .'?key=' . $this->galaxy->getAPIKey(). '&undelete=True';
       return $this->rest->delete($URL);
     }

     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $params['folder_id'] .'?key=' . $this->galaxy->getAPIKey();
     return $this->galaxy->httpDELETE($URL);
   }

  /**
   * Updated the folder's name and description.
   *
   * Corresponds to an HTTP PATCH on the Galaxy API path
   *   /api/folders/{folder_id}/
   *
   *  Only admin users can update folders.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - folder_id: The folder you want to update
   *   - payload: An array that contains 'name' => [new_name] and
   *       'description' => [can be null].
   *
   * @return
   *   An array containing details about the deleted file history content.
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
