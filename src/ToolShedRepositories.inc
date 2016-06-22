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
   function __construct(GalaxyInstance $galaxy) {
     $this->galaxy = $galaxy;
   }

  /**
  * Check for updates to the specified repository, or all installed repositories.
  *   GET /api/tool_shed_repositories/check_for_updates
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *
  *   - id: the galaxy-side encoded repository ID
  *
  * @return
  *
  *
  */
  public function checkForUpdates($params){
    if(!array_key_exists('id', $params)){
      $this->galaxy->setError("API", "Specify an 'id' of a tool shed repository in order to check for updates.");
      return FALSE;
    }
     $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/check_for_updates' .  '?key=' . $this->galaxy->getAPIKey();
     $response = $this->httpGET($URL, $params);
     return $this->galaxy->expectArray($response);
  }



  /**
  * Displays a list of dictionaries containing information about this tool
  * shed repository's exported workflows
  *
  * Corresponds to the Galaxy API/path at
  *   GET /api/tool_shed_repositories/{encoded_tool_shed_repository_id}/
  *   exported_workflows
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *
  *   - tool_shed_repo_id: Encoded Tool Shed Repository object encoded ID. To
  *       obtain a tool shed repository id, please use this class's index() function.
  *
  * @return
  *   An array containing information about a tool shed repository's
  *   exported workflow.
  *
  *
  */
    public function exportedWorkflows ($params){
      if(!array_key_exists('tool_shed_repo_id', $params)){
        $this->galaxy->setError("API", "This function requires a 'tool_shed_repo_id' in order to invoke this function.");
        return FALSE;
      }

     $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/' . $params['tool_shed_repo_id'] . '/exported_workflows?key=' . $this->galaxy->getAPIKey();
     $response = $this->galaxy->httpGET($URL);
     return $this->galaxy->expectArray($response);
   }

  /**
  * Initiate the installation of a repository.
  *   POST /api/tool_shed_repositories/install
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *
  *   - tool_shed_url: The URL for the toolshed whence this repository is being
  *       installed.
  *   - install_tool_dependencies (Optional): True to install tool dependencies.
  *   - tool_panel_section_id (Optional): The unique identifier for an existing
  *       tool panel section
  *   - install_repository_dependencies (Optional): True to install repository
  *       dependencies.
  *   - new_tool_panel_section_label (Optional): Create a new tool panel
  *       section with this label.
  *   - shed_tool_conf (Optional): The shed tool config file to use for this
  *       installation.
  *   - changeset (Optional): The changeset to update to after cloning the
  *       repository.
  *
  * @return
  *
  *
  */
  public function install($params){
    if(!array_key_exists('tool_shed_url', $params)){
      $this->galaxy->setError("API", "This function needs at least a tool_shed_url in order to install a toolshed.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . 'api/tool_shed_repositories/install' . '?key=' . $this->galaxy->getAPIKey();

     $response = $this->galaxy->httpPOST($URL, $params);
     return $this->galaxy->expectArray($response);
  }

  /**
  * Get the latest installable revision of a specified repository from a
  * specified Tool Shed.
  *
  * Corresponds to the Galaxy API/path at
  *   POST /api/tool_shed_repositories/get_latest_installable_revision
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *
  *   - tool_shed_url: The URL of the Tool Shed from which to retrieve the Repo
  *        revision. This should be something similar to this:
  *   https://toolshed.g2.bx.psu.edu/repository?repository_id=253e22fdaf6a52c1
  *   - name_of_repo: The name of the repository.
  *   - owner_of_repo: The name of the owner of the repository.
  *
  * @return
  *   A changeset_revision hash (describes the revison 'number' of the tool)
  *   i.e 1:7002b364c3f8
  *
  *   1 being the true rev. number (the larger the more changes it's been
  *   through, behind the colon is a supposed unique hash string, though
  *   collisions happen)
  *
  *
  */
   public function getLatestInstallable ($params){

     $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/' . 'get_latest_installable_revision' . '?key=' . $this->galaxy->getAPIKey();

     $response = $this->galaxy->httpPOST($URL, $params);

     // This will NOT be an array, just a simple hash string
     return $response;
  }

  /**
  * Import the specified exported workflow contained in a tool shed repo.
  *
  * Corresponds to the Galaxy API/method at
  *   POST /api/tool_shed_repositories/import_workflow
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *
  *   - tool_shed_repo_id: The encoded id of the Tool Shed Repository object.
  *   - index: The location of the workflow to import from within the specified
  *       toolshed, defaults to 0
  *       the index location of the workflow tuple in the list of exported
  *       workflows stored in the metadata for the specified repository.
  *
  * @return
  *   An array containing informaiton of the imported workflow.
  *
  *
  */
  public function importWorkflow ($params){
    $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/import_workflow?key=' . $this->galaxy->getAPIKey();

     $result = $this->galaxy->httpPOST($URL, $params);

     return $this->galaxy->expectArray($result);
   }

  /**
  * Import all of the exported workflows contained in the specified installed tool shed repository into Galaxy.
  *   POST /api/tool_shed_repositories/import_workflows
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *
  *   - id: the encoded id of the ToolShedRepository object.
  *
  * @return
  *
  *
  */
  public function importWorkflows($params){
    if(!array_key_exists('id', $params)){
      $this->galaxy->setError("API", "This function needs an 'id' of the tool shed repository to draw the workflows from.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/import_workflows?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  /**
  * Display metadata on external tool shed repositories in galaxy instance
  *
  * Corresponds to the Galaxy API/path at
  *   GET /api/tool_shed_repositories
  *
  * @return
  *  An array containing metadata on remote toolsheds galaxy instance.
  *
  *
  */
  public function index (){
    $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories' . '?key=' . $this->galaxy->getAPIKey();

    $result = $this->galaxy->httpGET($URL);

    return $this->galaxy->expectArray($result);
  }

   /**
   * Install a specified repository revision from a specified tool shed repo.
   *
   * Corresponds to the Galaxy API/path
   *   POST /api/tool_shed_repositories/install_repository_revision
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - tool_shed_url: The base URL of the Tool Shed from which to install the
   *       repository.
   *   - name: The name of the repository.
   *   - owner: The name of the owner of the repository.
   *   - changeset_revision: The changeset_revision of the Repository Meta Data
   *       object associated with the Repository.
   *   - new_tool_panel_section_label (Optional): Label of a new section to be
   *       added to the Galaxy tool panel in which to load tools contained in
   *       the Repository. Either this parameter must be an empty string or the
   *       tool_panel_section_id paramter must be an empty string or both must
   *       be an empty string.
   *       **BOTH CANNOT BE USED SIMULTANEOUSLY**
   *   - tool_panel_section_id (Optional): Id of the Galaxy tool panel section
   *       in which to load tools contained in the Repository. Either this
   *       parameter must be an empty string or new_tool_panel_section_label
   *       paramter must be an empty string or both must be an empty string.
   *       **BOTH CANNOT BE USED SIMULTANEOUSLY**
   *   - install_repository_dependencies (Optional): Set to True if you want to
   *       install repository dependencies defined for the specified repository
   *       being installed. The default setting is False.
   *   - install_tool_dependencies (Optional): Set to True if you want to
   *       install tool dependencies defined for the specified repository being
   *       installed.  The default setting is False.
   *   - shed_tool_conf (Optional): The shed-related tool panel configuration
   *       file configured in the "tool_config_file" setting in the Galaxy
   *       config file (ex: galaxy.ini). At least oneshed-reelated tool panel
   *       config file is required to be configured. Setting this paramter to a
   *       specific file enables you to choose where the specified repository
   *       will be installed because the tool_path attribute of the toolbox
   *       from the specified file is used as the installation location (ex:
   *       toolbox tool_path="../shed_tools"). If this parameter is not set,
   *       a shed-related tool ppanel configuration file will be selected
   *       automatically.
   *
   *
   */
  public function install_repository_revision ($params){
    if(!array_key_exists('tool_shed_url',$params)){
      $this->galaxy->setError("API", "A 'tool_shed_url' is required in order to invoke this call.");
      return FALSE;
    }
    if(!array_key_exists('name',$params)){
      $this->galaxy->setError("API", "A 'name' is required in order to invoke this call.");
      return FALSE;
    }
    if(!array_key_exists('owner',$params)){
      $this->galaxy->setError("API", "An 'owner' is required in order to invoke this call.");
      return FALSE;
    }
    if(!array_key_exists('changeset_revision',$params)){
      $this->galaxy->setError("API", "A 'changeset_revision' is required in order to invoke this call.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/install_repository_revision?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }


  /**
   * Repair a specified repository revision previously installed into Galaxy
   *
   * Corresponds to the Galaxy method/path
   *   POST /api/tool_shed_repositories/repair_repository_revision
   *
   * @param $params
   *   A key value (associative array) where the keys can be the following:
   *
   *   - tool_shed_url: The base URL of the Tool Shed from which the Repo was installed.
   *   - name: The name of the Repository.
   *   - owner: The owner of the Repository.
   *   - changeset_revision: The changeset_revision of the Repository Meta data
   *       object associated with the Repository.
   *
   *
   */
  public function repair_repository_revision ($params){
      if(!array_key_exists('tool_shed_url',$params)){
      $this->galaxy->setError("API", "A 'tool_shed_url' is required in order to invoke this call.");
      return FALSE;
    }
    if(!array_key_exists('name',$params)){
      $this->galaxy->setError("API", "A 'name' is required in order to invoke this call.");
      return FALSE;
    }
    if(!array_key_exists('owner',$params)){
      $this->galaxy->setError("API", "An 'owner' is required in order to invoke this call.");
      return FALSE;
    }
    if(!array_key_exists('changeset_revision',$params)){
      $this->galaxy->setError("API", "A 'changeset_revision' is required in order to invoke this call.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/repair_repository_revision?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpPOST($URL, $params);
    return $this->galaxy->expectArray($response);
  }

  /**
  * Resets all metadata on all repositories installed.
  *
  * Corresponds to the Galaxy API/path
  *   PUT /api/tool_shed_repositories/reset_metadata_on_installed_repositories
  *
  *
  */
  public function reset_metadata_on_installed_repositories (){
    $URL = $this->galaxy->getURL() . 'api/tool_shed_repositories/reset_metadata_on_installed_repositories?key=' . $this->galaxy->getAPIKey();

    $response = $this->galaxy->httpPUT($URL);
    return $this->galaxy->expectArray($response);
   }

  /**
  * Display a dictionary containing information about a specified tool_shed_repository.
  *   GET /api/tool_shed_repositories/{encoded_tool_shed_repsository_id}
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *
  *   - id: the encoded id of the ToolShedRepository object.
  *
  * @return
  *
  *
  */
  public function show($params){
    if(!array_key_exists('id', $params)){
      $this->galaxy->setError("API", "An 'id' is required in order to see a tool shed repository.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/' . $params['id'] . '?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }

  /**
  * Display a dictionary containing information about a specified repository's installation
  * status and a list of its dependencies and the status of each.
  *   GET /api/tool_shed_repositories/{id}/status
  *
  * @param $params
  *   A key value (associative array) where the keys can be the following:
  *
  *   - id: the repository's encoded id
  *
  * @return
  *
  *
  */
  public function status($params){
    if(!array_key_exists('id', $params)){
      $this->galaxy->setError("API", "An 'id' is required in order to see a tool shed repository's status.");
      return FALSE;
    }

    $URL = $this->galaxy->getURL() . '/api/tool_shed_repositories/' . $params['id'] . '/status?key=' . $this->galaxy->getAPIKey();
    $response = $this->galaxy->httpGET($URL);
    return $this->galaxy->expectArray($response);
  }
}
