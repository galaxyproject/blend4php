<?php
include_once "GalaxyRequest.inc";


class Libraries extends GalaxyRequest{


/**
 * public constructor
 *
 * @param GalaxyInstance $galaxy
 */
 public function __construct($galaxy) {
   parent ::__construct($galaxy);
 }


 /**
    POST /api/libraries:

     Creates a new library. Only ``name`` parameter is required.

     @param string 'name':         the new library's name (required)
     @param 'description':  the new library's description (optional)
     @param 'synopsis':     the new library's synopsis (optional)
  *
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
  * GET /api/libraries
  *
  * returns a list of summary data for all libraries
  *
  * @param string deleted, if true, show deleted libraries
  */
 public function index($deleted=false){
   $URL = $this->galaxy->getURL() . '/api/libraries/?deleted=' . $deleted . '&key='. $this->galaxy->getAPIKey();
   return $this->rest->GET($URL);
 }

 /**
  * GET /api/libraries/lib_id
  * GET /api/libraries/deleted/lib_id
  *
  * returns detailed information about a library
  *
  * @param string $lib_id the id of the library to show
  * @param bool $deleted the option to show deleted libraries
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
   return $this->rest->delete($URL, $elements);
 }

/**
  GET /api/libraries/{encoded_library_id}/permissions

Load all permissions for the given library id and return it.
 *
 * @param string $lib_id, the library id to receive permissions for
 * @param string $scope, the scope of the permission, either 'available' or 'current'
 * @param bool $is_library_access
 */
 public function getPermissions($lib_id, $scope='available',$is_library_access=true ) {
   $URL = $this->galaxy->getURL() . '/api/libraries/' . $lib_id .'/permissions/?scope='
       . $scope . '&is_library_access='.$is_library_access. '/&ey='. $this->galaxy->getAPIKey();

   return $this->rest->GET($URL);
 }

/**
 * POST /api/libraries/{encoded_library_id}/permissions
 *
 * @param string $lib_id the id of the library to set permissions to
 * @param string $action either 'remove_restrictions' or 'set_permissions'
 * @param array $access_ids list of role.id deining roles that should have access permissions
 *     on the library
 * @param array $add_idslist of role.id defining roles that should have add item permissions
 *     on the library
 * @param array $manage_ids list of role.id defining roles that should have manage permissions
 *     on the library
 * @param array $modify_ids list of role.id defining roles that should have  modify permissions
 *     on the library
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
