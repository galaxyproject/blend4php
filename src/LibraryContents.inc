<?php

require_once("GalaxyAPIService.inc");

class GalaxyLibraryContents extends GalaxyAPIService {


  /**
   * Gather the contents from the specified libarary.
   * 
   * Corresponds to an HTTP GET on the Galaxy API path
   *   api/libraries/{encoded_library_id}
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - library_id: Unique ID of a library to view its contents.
   *
   * @return
   *   Files and Folders within the specified library.
   */
  public function index($params){

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('library_id'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('library_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'] . '?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * View the specified library content within a given library.
   *
   *
   * Corresponds to an HTTP GET on the Galaxy API path
   *   /api/libraries/{encoded_library_id}/
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - library_id: Unique ID of a libary to view a specified content.
   *   - library_content_id: An entry within the library that contains data.
   *
   * @return
   *   Detailed library item information.
   */
  public function show($params){

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('library_id', 'library_content_id'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array('library_id', 'library_content_id'))) {
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'] . '/contents/' . $params['library_content_id'] .  '?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
   * Add a folder/file/data collection to the specified the library.
   *
   * This funciton is used when a users wants to upload files to said library
   * from a local filesystem to a given galaxy instance.
   * 
   * Corresponds to an HTTP POST on the Galaxy API path
   *   /api/libraries/{library_id}/contents
   * 
   * To copy an HDA into a library set the 'create_type' to type 'file' and set
   * the 'from_hda_id' to the HDA's encoded ID.
   *
   * @param $params
   *   An associative array containing the input parameters for this function.
   *   The following parameters are available:
   *
   *   - library_id: The repository where to 'create' the new data.
   *   - folder_id: A folder within a library to 'create' the new data.
   *   - create_type: The type of data category - file, folder, or collection.
   *   - collection_type (Only if create_type is 'collection'): Can be list,
   *      paired, list:paired.
   *   - element_identifiers (Only if create_type is 'collection'): List
   *       defining collection (the actual data for this new collection).
   *   - from_hda_id (Only if create_type is file): Id of HDA to copy into The
   *       library.
   *   - ldda_message (Optional): The new message attribute of the LDDA created.
   *   - extended_metadata (Optional): Sub-dictionary containing metadata to
   *       associate with the item.
   *   - upload_option (Optional): When POST'ed to the url, the default value
   *       is 'upload_file'. Other options include 'upload_directory' or
   *       'upload_paths'.
   *   - server_dir (Only if upload_option is 'upload_directory'): Relative
   *       path of the subdirectory of Galaxy 'library_import_dir' (look for in
   *       galaxy.ini) to upload. All and only the files (no subdirectories)
   *       contained in the specified directory will be uploaded.
   *   - filesystem_paths (Only if upload_option is 'upload_paths' AND if user
   *       is an admin): File paths on the Galaxy server to upload to the library
   *       one file per line.
   *   - link_data_only (Only when upload_option is 'upload_directory' or
   *       'upload_paths'): Either 'copy_files' which is default, or
   *       'link_to_files'. Setting to 'link_to_files' symlinks instead of
   *       copying the files.
   *   - name (Only if create_type is 'folder'): Name of the folder to create.
   *   - description (Only if create_type is 'folder'): Description of folder.
   *
   * @return
   *   The data that was uploaded and its metadata.
   */
  public function create($params){

    // Check for required fields.
    if (!$this->checkRequiredParams($params, array('library_id', 'folder_id', 'create_type'))) {
      return FALSE;
    }
    // Check for allowed fields.
    if (!$this->checkAllowedParams($params, array(
        'library_id', 'folder_id', 'create_type', 'collection_type', 'element_identifiers',
        'from_hda_id', 'ldda_message', 'extended_metadata', 'upload_option',
        'server_dir', 'filesystem_paths', 'link_data_only', 'name', 'description'))) {
      return FALSE;
    }


    $URL = $this->galaxy->getURL() . '/api/libraries/' . $params['library_id'] . '/contents/?key=' . $this->galaxy->getAPIKey();
    unset($params['library_id']);
    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }
}
