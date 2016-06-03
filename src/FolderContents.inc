<?php
/**
 * @file
 *
 * Implements the FolderContents class.
 *
 * The FolderContents Class interacts with Galaxy to manage contents of a folder.
 * The functions in this class correspond to the Galaxy API functions and
 * are named similarly to their Python counterpart.
 *
 */

/**
 * @defgroup folder_contents_class FolderContents class
 * @{
 *   The folder contents Class interacts with Galaxy to manage
 *   content of folders. The functions in this class correspond to the Galaxy
 *   API functions and are named similarly to their Python counterpart.
 * @}
 */


class GalaxyFolderContents {

  private $galaxy;

  /**
  * The FolderContents constructor.
  *
  * @param GalaxyInstance $galaxy
  *   A GalaxyInstance object.
  *
  * @return
  *   An instance of a FolderContents object.
  *
  *
  */
   public function __construct($galaxy) {
     $this->galaxy = galaxy;
   }

   /**
    * Displays all the contents of a folder.
    *
    * Corresponds to the Galaxy API/path:
    *   GET /api/folders/F{folder_id}/contents.
    *
    * @param $folder_id
    *   Id of the folder whos contents to display.
    *   To obtain id, see the index() function in the Folder class.
    * @return
    *   An array of The specified folder's contents
    *
    *
    */
   public function index ($folder_id) {
     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $folder_id . '/contents' .'/?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

   /**
    * Create a new content for specified folder
    *
    * Corresponds to the Galaxy API/path at:
    *   POST /api/folders/{folder_id}/contents
    *
    * @param $parent_folder_id
    *   The parent folder of the new item
    *   To obtain id, see the index() function in the Folder class.
    * @param $from_hda_id (optional)
    *   The id of an accessible HDA to into the library
    *   To obtain this id, see index() in HistoryContents class.
    * @param $ldda_messge (optional)
    *   Any message to send along with the LibraryDatasetDatasetAssociation.
    * @param $extented_metadata (optional)
    *   Sub-dictionary containing any extended metadata to associate with the
    *   item.
    *
    * @return
    *   An array containing the newly created folder content.
    *
  *
    */
   public function create($parent_folder_id, $from_hda_id = NULL, $ldda_message = NULL, $extended_metadata = NULL){
     $URL = $this->galaxy->getURL() . '/api/folders/' . 'F' . $parent_folder_id . '/contents/?key=' . $this->galaxy->getAPIKey();
     $postfields = array(
         'name' => $name,
         'description' => $description,
     );
     if($from_hda_id !== NULL){
       $postfields['from_hda_id'] = $from_hda_id;
     }
     if($ldda_message!==NULL){
       $postfields['ldda_message'] = $ldda_message;
     }

     $response = $this->galaxy->httpPOST($URL, $postfields);
     return $this->galaxy->expectArray($response);
   }

  /**
   * Retreive details of for a specified folder.
   *
   * Corresponds to the Galaxy API/path:
   *   GET /api/folders/{folder_id}/
   *
   * @param $folder_id
   *   The id of the folder to view
   *
   * @return
   *   False.
   *
   *
   */
   public function show($folder_id){
    //Not implemented in the python counterpart
     return FALSE;
   }

   /**
    * Update the contents to a specific folder
    *
    * Corresponds to the Galaxy API/PATH
    *   PUT /api/folders/{folder_id}/
    *
    * @return
    *   False.
    *
     *
    */
   public function update($folder_id, $add_ids, $manage_ids, $modify_ids){
    //Not implemented by the python counterpart.
    return FALSE;
  }
}
