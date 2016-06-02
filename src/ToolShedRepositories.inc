<?php
/**
 * @file
 *
 * The Tool Shed Repositories Class
 *
 * The tool shed repositories class interacts with Galaxy to manage contents
 * regarding its tool shed repositories. The functions in this class correspond to the Galaxy API functions
 * and are named similarly to their Python counterparts.
 */

/**
 * @defgroup tool_shed_repositories_class Tool Shed Repositories
 * @{
 *   The tool shed repositories class interacts with Galaxy to manage contents
 *   regarding its tool shed repositories. The functions in this class correspond to the Galaxy API functions
 *   and are named similarly to their Python counterparts.
 * @}
 */


class GalaxyToolShedRepositories {
   private $galaxy;

  /**
   * The Tools constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   *
   * @return
   *   An instance of a Tool shed repositories object.
   *
   *
   */
   function __construct($galaxy) {
     $this->galaxy = $galaxy;
     parent::__construct();
   }

  /**
  * Displays a list of dictionaries containing information about this tool
  * shed repository's exported workflows
  *
  * Corresponds to the Galaxy API/path at
  *   GET /api/tool_shed_repositories/{encoded_tool_shed_repository_id}/
  *   exported_workflows
  *
  * @param $tool_shed_repo_id Encoded
  *   Tool Shed Repository object encoded ID. To obtain a tool shed
  *   repository id, please use this class's index() function.
  *
  * @return
  *   An array containing information about a tool shed repositorie's
  *   exported workflow.
  *
  *
  */
    public function exportedWorkflows ($tool_shed_repo_id){
     $api_key = $this->galaxy->getAPIKey();
     $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/' . $tool_shed_repo_id . '/exported_workflows'  .  '?key=' . $api_key;
     $response = $this->galaxy->httpGET($URL);
     return $this->expectArray($response);
   }

  /**
  * Get the latest installable revision of a specified repository from a
  * specified Tool Shed.
  *
  * Corresponds to the Galaxy API/path at
  *   POST /api/tool_shed_repositories/get_latest_installable_revision
  *
  * @param $tool_shed_url
  *   The URL of the Tool Shed from which to retrieve the Repo revision
  *   This should be something similar to this:
  *   https://toolshed.g2.bx.psu.edu/repository?repository_id=253e22fdaf6a52c1
  * @param $name_of_repo
  *   The name of the repository
  * @param $owner_of_repo
  *   The name of the owner of the repository
  *
  * @return
  *   A changeset_revision hash yo (describes the revison 'number' of the tool)
  *   i.e 1:7002b364c3f8
  *   1 being the true rev. number (the larger the more changes it's been
  *   through, behind the colon is a supposed unique hash string, though
  *   collisions happen)
  *
  *
  */
   public function getLatestInstallable ($tool_shed_url, $name_of_repo, $owner_of_repo){
     $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/' . 'get_latest_installable_revision' . '?key=' . $this->galaxy->getAPIKey();

     $data = array(
       'tool_shed_url' => $tool_shed_url,
       'name' => $name_of_repo,
       'owner' => $owner_of_repo,
     );

     $response = $this->galaxy->httpPOST($URL, $data);

     // This will NOT be an array, just a simple hash string
     return $response;
  }

  /**
  * Import the specified exported workflow contained in a tool shed repo.
  *
  * Corresponds to the Galaxy API/method at
  *   POST /api/tool_shed_repositories/import_workflow
  *
  * @param $tool_shed_repo_id
  *   The encoded id of the Tool Shed Repository object
  *
  * @param $index
  *   The location of the workflow to import from within the specified
  *   toolshed, defaults to 0
  * @return
  *   An array containing informaiton of the imported workflow.
  *
  *
  */
   public function importWorkflow ($tool_shed_repo_id, $index = 0){
     $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/' . $tool_shed_repo_id . '/import_workflow?key=' . $this->galaxy->getAPIKey();

     $data = array(
       'id' => $tool_shed_repo_id,
       'index' => $index,
     );

   $result = $this->galaxy->httpPOST($URL, $data);

   return $this->expectArray($result);
  }

  /**
  * Display metadata on external tool shed repositories in galaxy instance
  *
  * Corresponds to the Galaxy API/path at
  *   GET /api/tool_shed_repositories
  *
  * @return
  *   Json containing metadata on remote toolsheds galaxy instance
  *
  *
  */
  public function index (){
    $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories' . '?key=' . $this->galaxy->getAPIKey();

    $result = $this->galaxy->httpGET($URL);

    return $this->expectArray($result);
  }

   /**
   * Install a specified repository revision from a specified tool shed repo.
   *
   * Corresponds to the Galaxy API/path
   *   POST /api/tool_shed_repositories/install_repository_revision
   *
   * @param $tool_shed_url
   *   The base URL of the Tool Shed from which to install the repo
   * @param $name_of_repo
   *   The name of the repository
   * @param $name_owner_of_repo.
   *    The name of the owner of the repository
   * @param $changeset_revision
   *   The changeset_revision of the Repository Meta Data object associated
   *   with the Repository
   * @param $new_tool_panel_section_label (OPTIONAL)
   *    Label of a new section to be added to the Galaxy tool panel in which to
   *    load tools contained in the Repository. Either this parameter must be an
   *    empty string or the tool_panel_section_id paramter must be an empty string
   *   or both must be an empty string
   *   BOTH CANNOT BE USED SIMULTANEOUSLY
   * @param $tool_panel_section_id (OPTIONAL)
   *   Id of the Galaxy tool panel section in which to load tools contained in
   *   the Repository. Either this parameter must be an
   *    empty string or the new_tool_panel_section_label paramter must be an empty
   *   string or both must be an empty string
   *   BOTH CANNOT BE USED SIMULTANEOUSLY
   * @param $install_repo_dependencies (OPTIONAL)
   *   Set to True if you want to install repository dependencies defined for
   *   the specified repository being installed. The default setting is False
   * @param $shed_tool_conf (OPTIONAL)
   *   The shed-related tool panel configuration file configured in the
   *   "tool_config_file" setting in the Galaxy config file (ex: galaxy.ini).
   *   At least oneshed-reelated tool panel config file is required to be
   *   configured. Setting this paramter to a specific file enables you to choose
   *   where the specified repository wilel be installed because the tool_path
   *   attribute of the <toolbox> from the specified file is used as the
   *   installation location (ex: <toolbox tool_path="../shed_tools">). If this
   *   parameter is not set, a shed-related tool ppanel configuration file will
   *   be selected automatically
   *
   *
   */
  public function install_repository_revision ($tool_shed_url, $name_of_repo, $name_owner_of_repo, $changeset_revision,
      $new_tool_panel_section_label = NULL, $tool_panel_section_id = NULL, $install_repo_dependencies = FALSE, $shed_tool_conf = NULL){

  }


  /**
   * Repair a specified repository revision previously installed into Galaxy
   *
   * Corresponds to the Galaxy method/path
   *   POST /api/too_sed_repositories/repair_repository_revision
   *
   * @param $admin_api_key
   *   The current Galaxy damin user's API key
   * @param $tool_shed_url
   *   The base URL of the Toool Shed from which the Repo was installed
   * @param $name_of_repo
   *   The name of the Repository
   * @param $owner_of_repo
   *   The owner of the Repository
   * @param $changeset_revision
   *   The changeset_revision of the Repository Meta data object associated
   *   with the Repository
   *
   *
   */
  public function repair_repository_revision ($admin_api_key, $tool_shed_url, $name_of_repo, $owner_of_repo, $changeset_revision){

  }

  /**
  * Resets all metadata on all repositories installed.
  *
  * Corresponds to the Galaxy API/path
  *   PUT /api/tool_shed_repositories/reset_metadata_on_installed_repositories
  *
  * @param $admin_api_key
  *   The current Galaxy damin user's API key
  *
  *
  */
   public function reset_metadata_on_installed_repositories ($admin_api_key){

   }

}

?>
