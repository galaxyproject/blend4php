<?php

require_once('GalaxyAPIService.inc');

/**
 * @file
 *
 * Implements the Libraries class.
 *
 * The Libraries Class interacts with Galaxy to manage contents of a libraries.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 */

class GalaxyLibraries extends GalaxyAPIService {


  /**
   * Creates a new library.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/libraries
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *    - name: The library's name.
   *    - description: (Optional) The new library's description.
   *    - synopsis: (Optional) A string containing a synopsis.
   *
   * @return
   *   An array containing the new library created.
   */
  public function create($params) {
     
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('name'))) {
      return FALSE;
    }
     
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('name', 'description', 'synopsis'))) {
      return FALSE;
    }
     
    $URL = $this->galaxy->getURL() . '/api/libraries/?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Updates library.
   *
   * Corresponds to an HTTP PATCH on the Galaxy API path
   *   /api/libraries/{encoded_id}
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *    - name: The new library's name.
   *    - description: (Optional) The new library's description.
   *    - synopsis: (Optional) The new string containing a synopsis.
   *
   * @return
   *   An array containing the new library created.
   */
   public function update($params) {
     // TODO: We need to implement this function
     //       This requires a httpPATCH curl request
   }

  /**
   * Retreives a list of summary data for all libraries.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/libraries
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *    - deleted: (Optional) If TRUE, show only deleted libraries, if FALSE show only
   *        non-deleted.
   *
   * @return
   *   An array of all of libraries. And all of the deleted libraries if
   *   appropriate.
   */
  public function index($params) {
    
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('deleted'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/libraries?key=' . $this->galaxy->getAPIKey();
    
    // Does the user only want to see deleted libraries or undeleted libraries.
     if (array_key_exists('deleted', $params)) {
       $URL .= '?deleted=' . $params['deleted'];
     }

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreives detailed infromation about a specific library.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/libraries/{encoded_id} 
   *   and
   *   /api/libraries/deleted/{encoded_id}
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *    - library_id: The ID of the library to show. To obtain library IDs,
   *        use Libraries::index().
   *    - deleted: (Optional) If TRUE, the function may return a deleted library.
   *
   * @return
   *   An array containing details of the specified library.
   */
  public function show($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('library_id'))) {
      return FALSE;
    }
     
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('library_id', 'deleted'))) {
      return FALSE;
    }

    if (array_key_exists('deleted', $params) and $params['deleted'] == TRUE){
      $URL = $this->galaxy->getURL() . '/api/libraries/deleted/' . $params['library_id'] . '/?key=' . $this->galaxy->getAPIKey();
    }

    else {
      $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'] . '/?key='. $this->galaxy->getAPIKey();
    }

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }


  /**
   * Marks a specific library as deleted or a deleted library as not-deleted.
   *
   * Corresponds to an HTTP DELETE on the Galaxy API path
   *   /api/libraries/{encoded_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *    - library_id: The ID of the library to delete or undelete, to obtain
   *        library IDs, use Libraries::index().
   *    - undelete: (Optional) If TRUE, the library will be undeleted if it is already
   *        deleted.
   *
   * @return
   *   An array containing details of the deleted or undeleted library.
   */
  public function delete($params) {

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('library_id'))) {
      return FALSE;
    }
     
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('library_id', 'deleted'))) {
      return FALSE;
    }
    
    $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'] . '/?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpDELETE($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Retreives the permission details for a given library.
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/libraries/{encoded_library_id}/permissions
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *    - library_id: The ID of the library to retreive permissions. To
   *        obtain library IDs use Libraries::index().
.  *    - scope: (Optional) The scope of the permissions, either 'available' or 'current'.
   *        This parameter defaults to 'current'
   *    - is_library_access: (Optional) If FALSE, the function will not look for
   *        libraries with user access, defaults to TRUE.
   *
   * @return
   *   An array containing details of the permissions of all libraries.
   */
  public function getPermissions($params) {
     
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('library_id'))) {
      return FALSE;
    }
      
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('library_id', 'scope', 'is_library_access'))) {
      return FALSE;
    }

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

  /**
   * Sets the permissions for a specified library.
   *
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/libraries/{encoded_library_id}/permissions
   *
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *    - library_id: The ID of the library to set permissions. To obtain
   *        library ids, refer to Libraries::index().
   *    - action: Set to either: 'remove_restrictions' or 'set_permissions',
   *        to specify appropriate action for the function.
   *    - access_ids: (Optional) A list of role ids defining roles that should
   *        have access permissions on the library. To obtain role IDs, refer
   *         to Roles::index().
   *    - add_ids: (Optional) A list of role id defining roles that should have
   *        add item permissions on the library.
   *    - manage_ids: (Optional) A list of role id defining roles that should
   *        have manage permissions on the library.
   *    - modify_ids: (Optioal) A list of role id defining roles that should 
   *        have modify permissions on the library.
   *
   * @return
   *   An array of librariy objects who's permissions have
   *   been modified.
   *
   *
   */
  public function setPermissions($params){
     
    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('library_id', 'action'))) {
      return FALSE;
    }
     
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('library_id', 'action', 'access_ids', 'add_ids', 'manage_ids', 'modify_ids'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'] . '/permissions/?key='. $this->galaxy->getAPIKey();
    
    // A POST does not deal well with arrays as post fields, so encode them
    // into a string-like format (json!).
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
   
}
