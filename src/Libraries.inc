<?php
/**
 * @file
 *
 * Implements the Libraries class.
 *
 * The Libraries Class interacts with Galaxy to manage contents of a libraries.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 */

/**
 * @defgroup libraries_class Folders class
 * @{
 *   The libraries Class interacts with Galaxy to manage
 *   its libraries. The functions in this class correspond to the Galaxy
 *   API functions and are named similarly to their Python counterpart.
 * @}
 */

include_once "GalaxyRequest.inc";


class Libraries extends GalaxyRequest{

  /**
	* The Folders constructor.
	*
	* @param GalaxyInstance $galaxy
	*   A GalaxyInstance object.
	*
	* @return
	*   An instance of a Libraries object.
	*
	* @ingroup libraries_class
	*/
   public function __construct($galaxy) {
     parent ::__construct($galaxy);
   }


  /**
    * Creates a new library.
    * 
    * Corresponds to the Galaxy Api/path: 
    *   POST /api/libraries:
    * 
    * @param Name 
    *   The new library's name.
    * @param description' 
    *   Optional the new library's description.
    * @param synopsis     
    *   Otional The new library's synopsis.
    *
    * @return 
    *   A Json array containing the new library created.
    *   
	* @ingroup libraries_class
    */
   public function create($name, $description=NULL, $synopsis=NULL) {
     $URL = $this->galaxy->getURL() .'/api/libraries/?key='. $this->galaxy->getAPIKey();
     $inputs = array(
       'name' => $name,
       'description'=> $description,
       'synopsis' => $synopsis,
     );
     return $this->rest->POST($URL, $inputs);
   }

  /**
    * Retreives a list of summary data for all libraries.
    * 
    * Corresponds to the Galaxy Api/path:
    *   GET /api/libraries
    *
    * @param deleted 
    *   If True, show deleted libraries.
    *   
    * @return 
    *   A JSON array of all of libraries. And all of the deleted libraries if
    *   appropriate. 
    *   
    * @ingroup libraries_class
    */
   public function index($deleted=false){
    $URL = $this->galaxy->getURL() . '/api/libraries/?deleted=' . $deleted . '&key='. $this->galaxy->getAPIKey();
    return $this->rest->GET($URL);
  }

  /**
    * Retreives detailed infromation about a specific library.
    * 
    * Corresponds t the Galaxy Api functions at
    *   GET /api/libraries/lib_id and 
    *   GET /api/libraries/deleted/lib_id
    *
    * @param lib_id 
    *   The id of the library to show. To obtain library ids, please use this 
    *   class's index() function.
    * @param deleted 
    *    If true, the function may return a deleted library.
    *   
    * @return 
    *   A JSON array containing details of the specified library.
    *   
    * @ingroup libraries_class
    */
   public function show($lib_id, $deleted=false){
     if(!$deleted) {
       $URL = $this->galaxy->getURL() . '/api/libraries/' . $lib_id . '/?key='. $this->galaxy->getAPIKey();
     }
     else {
       $URL =  $this->galaxy->getURL() . '/api/libraries/deleted/' . $lib_id . '/?key='. $this->galaxy->getAPIKey();
     }
     return $this->rest->GET($URL);
   }
<<<<<<< HEAD
=======
   return $this->rest->GET($URL);
 }

 /**
  *  Updates the library defined by an ``encoded_id``
  *  with the data in the payload.
  *
  * TODO: This function uses a 'patch' rest request, patch is currently not supported
  */
 public function update(){

 }

 /**
  * DELETE /api/libraries/{id}
  *
  *  marks the library with the given ``id`` as `deleted`
  *  (or removes the `deleted` mark if the `undelete` param is true)
  *
  * @param string $lib_id, the id of the library to delete or undelete
  * @param bool undelete option to undelete item
  */
 public function delete($lib_id,$undelete=false){
   $URL = $this->galaxy->getURL() . '/api/libraries/' . $lib_id . '/?key='. $this->galaxy->getAPIKey();
   $elements = array(
     'undelete' => $undelete,
   );
   return $this->rest->DELETE($URL, $elements);
 }
>>>>>>> f985cf0f6455492daa935b6e64dee3176ef74fa2


  /**
    * Marks a specific library as deleted or a deleted library as not-deleted.
    * 
    * Corresponds to the Galaxy Api/path at
    *   DELETE /api/libraries/{id}
    *
    * @param lib_id 
    *   The id of the library to delete or undelete, to obtain library id's
    *   please use this class's index() function.
    * @param undelete 
    *   If true,function will undelete the item.
    *   
    * @return
    *   A JSON array containing details of the deleted or undeleted library.
    *   
    * @ingroup libraries_class
    */
   public function delete($lib_id,$undelete=false){
     $URL = $this->galaxy->getURL() . '/api/libraries/' . $lib_id . '/?key='. $this->galaxy->getAPIKey();
     $elements = array(
       'undelete' => $undelete,
     );
     return $this->rest->delete($URL, $elements);
   }

  /**
    * Retreives the permission details for a given library.
    * 
    * Corresponds to the Galaxy API/path 
    *   GET /api/libraries/{encoded_library_id}/permissions
    *
    * @param lib_id 
    *   The if of the library to receive permissions for. To obtain library 
    *   id's please use this class's index function
.   * @param scope 
    *    The scope of the permission, either 'available' or 'current'.
    * @param is_library_access 
    *    If false, the function will not look for libraries with user access. 
    *    
    * @return
    *   A JSON array containing details of the permissions of all libraries.
    *   
    * @ingroup libraries_class
    */
   public function getPermissions($lib_id, $scope='available',$is_library_access=true ) {
     $URL = $this->galaxy->getURL() . '/api/libraries/' . $lib_id .'/permissions/?scope='
         . $scope . '&is_library_access='.$is_library_access. '/&ey='. $this->galaxy->getAPIKey();

     return $this->rest->GET($URL); 
   }

  /**
    * Sets the permissions for a specified library.
    * 
    * Corresponds to the Galaxy Api function at
    *   POST /api/libraries/{encoded_library_id}/permissions
    *
    * @param lib_id 
    *   The id of the library to set permissions to. To obtain the library id
    *   refer to this class's index() function.
    * @param action 
    *   Set to either. 'remove_restrictions' or 'set_permissions', to specify 
    *   appropriate action for the function.
    * @param access_ids 
    *   A list of role id deining roles that should have access permissions
    *   on the library. To obtain role id's please refer to the roles class.
    * @param add_ids 
    *   A list of role id defining roles that should have add item permissions
    *   on the library. 
    * @param $manage_ids 
    *   A list of role id defining roles that should have manage permissions
    *   on the library.
    * @param $modify_ids 
    *   A list of role id defining roles that should have  modify permissions
    *    on the library.
    *    
    * @return 
    *   A JSON array of librariy objects who's permissions have 
    *   been modieifed.   
    *   
    * @ingroup libraries_class
    */
   public function setPermissions($lib_id, $action='set_permissions',
     $access_ids = array(), $add_ids=array(), $manage_ids = array(),
     $modify_ids = array()){

    $URL = $this->galaxy->getURL() . '/api/libraries/' . $lib_id . '/permissions/?key='. $this->galaxy->getAPIKey();

    $elements= array(
      'action' => $action,
      'access_ids[]' => $access_ids,
      'add_ids[]' => $add_ids,
      'manage_ids[]'=>$manage_ids,
      'modify_ids[]'=>$modify_ids,
    );

    return $this->rest->POST($URL, $elements);
   }
 
}
