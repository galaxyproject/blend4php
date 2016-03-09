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

include_once "HTTPRequest.inc";


class Libraries extends HTTPRequest{
  private $galaxy;
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
     $this->galaxy = galaxy;
     parent ::__construct();
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
    *   An array containing the new library created.
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
     $response = $this->httpPOST($URL, $inputs);
     return $this->expectArray($response);
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
    *   An array of all of libraries. And all of the deleted libraries if
    *   appropriate.
    *
    * @ingroup libraries_class
    */
   public function index($deleted=false){
     $URL = $this->galaxy->getURL() . '/api/libraries/?deleted=' . $deleted . '&key='. $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
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
    *   An array containing details of the specified library.
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
     $response = $this->httpGET($URL);
     return $this->expectArray($response);
   }


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
    *   An array containing details of the deleted or undeleted library.
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
    *   An array containing details of the permissions of all libraries.
    *
    * @ingroup libraries_class
    */
   public function getPermissions($lib_id, $scope='available',$is_library_access=true ) {
     $URL = $this->galaxy->getURL() . '/api/libraries/' . $lib_id . '/permissions/?scope='
         . $scope . '&is_library_access='.$is_library_access. '/&key='. $this->galaxy->getAPIKey();

     $response = $this->httpGET($URL);
     return $this->expectArray($response);
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
    *   An array of librariy objects who's permissions have
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

    $response = $this->httpPOST($URL, $elements);
    return $this->expectArray($response);
  }

}
