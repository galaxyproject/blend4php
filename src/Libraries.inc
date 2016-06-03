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

class GalaxyLibraries {
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
   *
   */
   public function __construct($galaxy) {
     $this->galaxy = $galaxy;
   }


  /**
   * Creates a new library.
   *
   * Corresponds to the Galaxy Api/path:
   *   POST /api/libraries:
   *
   * @param $params
   *    A key value (associative array) where the keys can be the following:
   *
   *    - name: The library's name.
   *    - description: Optional the new library's description.
   *    - synopsis: Optional a string containing a synopsis.
   *
   * @return
   *   An array containing the new library created.
   *
   *
   */
   public function create($params) {
     $URL = $this->galaxy->getURL() . '/api/libraries/?key=' . $this->galaxy->getAPIKey();

     if(array_key_exists('name', $params)){

       $response = $this->galaxy->httpPOST($URL, $params);
       return $this->galaxy->expectArray($response);
     }

     $this->galaxy->setError("API", "This function expects at least the associative parameter 'name' in order to run");
     return FALSE;

   }

  /**
   * Updates library.
   *
   * Corresponds to the Galaxy Api/path:
   *   PATCH /api/libraries/{encoded_id}
   *
   *
   * @param $params
   *    A key value (associative array) where the keys can be the following:
   *
   *    - name: New library's name.
   *    - description: New library's description.
   *    - synopsis: New string containing a synopsis.
   *
   * @return
   *   An array containing the new library created.
   *
   */
   public function update($params) {
     // TODO: We need to implement this function
     //       This requires a httpPATCH curl request
   }

  /**
   * Retreives a list of summary data for all libraries.
   *
   * Corresponds to the Galaxy Api/path:
   *   GET /api/libraries
   *
   * @param $params
   *    A key value (associative array) where the keys can be the following:
   *
   *    - deleted: if TRUE, show only deleted libraries, if FALSE show only
   *        non-deleted.
   *
   * @return
   *   An array of all of libraries. And all of the deleted libraries if
   *   appropriate.
   *
   *
   */
   public function index($params){
     $URL = $this->galaxy->getURL() . '/api/libraries?key=' . $this->galaxy->getAPIKey();
     if (array_key_exists('deleted', $params)) {
       $URL .= '?deleted=' . $params['deleted'];
     }

     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
  }

  /**
   * Retreives detailed infromation about a specific library.
   *
   * Corresponds t the Galaxy Api functions at
   *   GET /api/libraries/{encoded_id} and
   *   GET /api/libraries/deleted/{encoded_id}
   *
   *
   * @param $params
   *    A key value (associative array) where the keys can be the following:
   *
   *    - library_id: The id of the library to show. To obtain library ids,
   *        please use this class's index() function.
   *    - deleted: If TRUE, the function may return a deleted library.
   *
   * @return
   *   An array containing details of the specified library.
   *
   *
   */
   public function show($params){

     if (array_key_exists('deleted', $params) and $params['deleted'] == TRUE){

       if(array_key_exists('library_id', $params)){
         $URL = $this->galaxy->getURL() . '/api/libraries/deleted/' . $params['library_id'] . '/?key=' . $this->galaxy->getAPIKey();
       }
       else{
       $this->galaxy->setError("API", "This function expects at least the associative parameter 'library_id' in order to run");
       return FALSE;
       }
     }

     else {
       if(array_key_exists('library_id', $params)){
         $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'] . '/?key='. $this->galaxy->getAPIKey();
       }
       else{
         $this->galaxy->setError("API", "This function expects at least the associative parameter 'library_id' in order to run");
         return FALSE;
       }
     }

     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }


  /**
   * Marks a specific library as deleted or a deleted library as not-deleted.
   *
   * Corresponds to the Galaxy Api/path at
   *   DELETE /api/libraries/{encoded_id}
   *
   * @param $params
   *    A key value (associative array) where the keys can be the following:
   *
   *    - library_id: The id of the library to delete or undelete, to obtain
   *        library id's. Please use this class's index() function.
   *    - undelete: If TRUE, the library will be undeleted if it is already
   *        deleted.
   *
   * @return
   *   An array containing details of the deleted or undeleted library.
   *
   *
   */
   public function delete($params){

     if (!array_key_exists('library_id', $params)) {
       $this->galaxy->setError('API', 'Please provide a value for the \'library_id\' argument.');
       return FALSE;
     }

     $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'] .
            '/?key=' . $this->galaxy->getAPIKey();

     $input = array();
     if (array_key_exists('undelete', $params) and $params['undelete'] == TRUE) {
       $input['undelete'] = True;
     }
     $response = $this->galaxy->httpDELETE($URL, $input);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Retreives the permission details for a given library.
   *
   * Corresponds to the Galaxy API/path
   *   GET /api/libraries/{encoded_library_id}/permissions
   *
   * @param $params
   *    A key value (associative array) where the keys can be the following:
   *
   *    - library_id: The if of the library to receive permissions for. To
   *        obtain library id's please use this class's index function.
.  *    - scope: The scope of the permission, either 'available' or 'current'.
   *        This parameter defaults to 'current'
   *    - is_library_access: If FALSE, the function will not look for
   *        libraries with user access, defaults to TRUE.
   *
   * @return
   *   An array containing details of the permissions of all libraries.
   *
   *
   */
   public function getPermissions($params) {

     if(array_key_exists('library_id', $params)){
       $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'];

       if (!array_key_exists('scope', $params) and !array_key_exists('is_library_access', $params))
         $URL .= '?key='. $this->galaxy->getAPIKey();

       else if(array_key_exists('scope', $params) and !array_key_exists('is_library_access', $params))
         $URL .=  '/permissions/?scope=' . $params['scope'] . '&key='. $this->galaxy->getAPIKey();

       else if(array_key_exists('is_library_access', $params) and array_key_exists('scope', $params))
         $URL .= '/permissions/?scope=' . $params['scope'] . '&is_library_access=' . $params['is_library_access'] . '&key=' . $this->galaxy->getAPIKey();

       else if (array_key_exists('is_library_access', $params) and !array_key_exists('scope', $params))
         $URL .= '/permissions/?is_library_access=' . $params['is_library_access'] . '&key=' . $this->galaxy->getAPIKey();

       $response = $this->galaxy->httpGET($URL);
       return $this->galaxy->expectArray($response);

     }

     else{
       $this->galaxy->setError('API', 'Please provide a value for the \'library_id\' argument.');
       return FALSE;
     }


   }

  /**
   * Sets the permissions for a specified library.
   *
   * Corresponds to the Galaxy API function at
   *   POST /api/libraries/{encoded_library_id}/permissions
   *
   *
   * @param $params
   *    A key value (associative array) where the keys can be the following:
   *
   *    - library_id: The id of the library to set permissions to. To obtain
   *        the library id. Refer to this class's index() function.
   *    - action: Set to either: 'remove_restrictions' or 'set_permissions',
   *        to specify appropriate action for the function.
   *    - access_ids: A list of role ids defining roles that should have access
   *        permissions on the library. To obtain role id's please refer to the
   *         roles class.
   *    - add_ids: A list of role id defining roles that should have add item
   *        permissions on the library.
   *    - manage_ids: A list of role id defining roles that should have manage
   *        permissions on the library.
   *    - modify_ids: A list of role id defining roles that should have modify
   *       permissions on the library.
   *
   * @return
   *   An array of librariy objects who's permissions have
   *   been modified.
   *
   *
   */
   public function setPermissions($params){

    if(array_key_exists('library_id', $params)) {
      $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'] . '/permissions/?key='. $this->galaxy->getAPIKey();
      if(array_key_exists('action', $params)) {
        if(array_key_exists('access_ids', $params))
          $params['access_ids'] = json_encode($params['access_ids']);
        if(array_key_exists('add_ids', $params))
          $params['add_ids'] = json_encode($params['add_ids']);
        if(array_key_exists('manage_ids', $params))
          $params['manage_ids'] = json_encode($params['manage_ids']);
        if(array_key_exists('modify_ids', $params))
          $params['modify_ids'] = json_encode($params['modify_ids']);

        $response = $this->galaxy->httpPOST($URL, $params);
        return $this->galaxy->expectArray($response);
      }
      else{
        $this->galaxy->setError('API', 'Please provide an action for the \'action\' argument.');
        return FALSE;
      }
    }
    $this->galaxy->setError('API', 'Please provide a value for the \'library_id\' argument.');
    return FALSE;


  }

}
