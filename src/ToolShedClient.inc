<?php
require_once "GalaxyInstance.inc";
		

class ToolShedClient{
	
	/**
	 * Displays a list of dictionaries containing information about this tool
	 * shed repository's exported workflows
	 *
	 * @param $tool_shed_repo_id Encoded
	 *   Tool Shed Repository object encoded ID
	 * 
	 * GET /api/tool_shed_repositories/{encoded_tool_shed_repository_id}/
	 * exported_workflows
	 * 
	 */
  
	public function exported_workflows ($tool_shed_repo_id){
		
	}
	
	/**
	 * Displays a list of dictionaries containing information about this tool
	 * shed repository's exported workflows
	 *
	 * @param $admin_api_key
	 *	The current Galaxy admin user's API key
	 *   
	 * @param $tool_shed_url
	 * 	The base URL of the Tool Shed from which to retrieve the Repo revision
	 * 
	 * @param $name_of_repo
	 * 	The name of the repository
	 * 
	 * @param $name_owner_of_repo
	 * 	The name of the owner of the repository
	 *
	 * GET /api/tool_shed_repositories/{encoded_tool_shed_repository_id}/
	 * exported_workflows
	 *
	 */
	public function get_latest_installable_revision ($admin_api_key, $tool_shed_url, $name_of_repo, $name_owner_of_repo){
		
	}
	
	/**
	 * Import the specified exported workflow contained in the specified 
	 * installed tool shed repository into Galaxy
	 * 
	 * @param $api_key_of_importer
	 * 	The API key of the Galaxy user with which the imported workflow will be
	 * 	associated
	 * 
	 * @param $tool_shed_repo_id
	 *   The encoded id of the Tool Shed Repository object
	 *
	 * POST /api/tool_shed_repositories/import_workflow
	 * 
	 */
	public function import_workflow ($api_key_of_importer, $tool_shed_repo_id){
		
	}
	
	/**
	 * Import all of the exported workflows contained in the specified installed
	 * tool shed repository into the Galaxy
	 * 
	 * @param $api_key_of_importer
	 * 	The API key of the Galaxy user with which the imported workflows will be
	 * 	associated
	 *
	 * @param $tool_shed_repo_id
	 *   The encoded id of the Tool Shed Repository object
	 *
	 * POST /api/tool_shed_repositories/import_workflows
	 *
	 */
	public function import_workflows ($api_key_of_importer, $tool_shed_repo_id){
		
	}
	
	/**
	 * Display a list of dictionaries containing information about installed tool
	 * shed repositories
	 *
	 * GET /api/tool_shed_repositories
	 *
	 */
	public function index (){
		
	}
	
/**
	 * Install a specified repository revision from a specified tool shed into
	 * Galaxy
	 * 
	 * @param $admin_api_key
	 *	The current Galaxy admin user's API key
	 *   
	 * @param $tool_shed_url
	 * 	The base URL of the Tool Shed from which to install the repo
	 * 
	 * @param $name_of_repo
	 * 	The name of the repository
	 * 
	 * @param $name_owner_of_repo
	 * 	The name of the owner of the repository
	 *
	 * @param $changeset_revision
	 *	The changeset_revision of the Repository Meta Data object associated 
	 *	with the Repository
	 *
	 * @param $new_tool_panel_section_label (OPTIONAL)
	 * 	Label of a new section to be added to the Galaxy tool panel in which to
	 * 	load tools contained in the Repository. Either this parameter must be an
	 * 	empty string or the tool_panel_section_id paramter must be an empty string
	 *  or both must be an empty string
	 *  BOTH CANNOT BE USED SIMULTANEOUSLY
	 *  
	 * @param $tool_panel_section_id (OPTIONAL)
	 *  Id of the Galaxy tool panel section in which to load tools contained in
	 *  the Repository. Either this parameter must be an
	 * 	empty string or the new_tool_panel_section_label paramter must be an empty
	 *  string or both must be an empty string
	 *  BOTH CANNOT BE USED SIMULTANEOUSLY
	 *  
	 * @param $install_repo_dependencies (OPTIONAL)
	 *  Set to True if you want to install repository dependencies defined for 
	 *  the specified repository being installed. The default setting is False
	 *  
	 * @param $shed_tool_conf (OPTIONAL)
	 *  The shed-related tool panel configuration file configured in the 
	 *  "tool_config_file" setting in the Galaxy config file (ex: galaxy.ini). 
	 *  At least oneshed-reelated tool panel config file is required to be 
	 *  configured. Setting this paramter to a specific file enables you to choose 
	 *  where the specified repository will be installed because the tool_path
	 *  attribute of the <toolbox> from the specified file is used as the 
	 *  installation location (ex: <toolbox tool_path="../shed_tools">). If this
	 *  parameter is not set, a shed-related tool ppanel configuration file will 
	 *  be selected automatically
	 *  
	 * POST /api/tool_shed_repositories/install_repository_revision
	 *
	 */
	public function install_repository_revision ($admin_api_key, $tool_shed_url, $name_of_repo, $name_owner_of_repo, $changeset_revision, 
			$new_tool_panel_section_label = NULL, $tool_panel_section_id = NULL, $install_repo_dependencies = FALSE, $shed_tool_conf = NULL){
		
	}
	
	/**
	 * Install a specified repository revision from a specified tool shed into
	 * Galaxy
	 *
	 * @param $admin_api_key
	 *	The current Galaxy admin user's API key
	 *
	 * @param $tool_shed_urls
	 * 	The base URLs of the Tool Shed from which to install a specified Repo
	 *
	 * @param $names_of_repo
	 * 	The names of the repositories
	 *
	 * @param $owners_of_repo
	 * 	The names of the owners of the repositories
	 *
	 * @param $changeset_revisions
	 *	The changeset_revisions of each Repository Meta Data object associated
	 *	with each Repository to be installed
	 *
	 * @param $new_tool_panel_section_label (OPTIONAL)
	 * 	Label of a new section to be added to the Galaxy tool panel in which to
	 * 	load tools contained in the Repository. Either this parameter must be an
	 * 	empty string or the tool_panel_section_id paramter must be an empty string
	 *  or both must be an empty string
	 *  BOTH CANNOT BE USED SIMULTANEOUSLY
	 *
	 * @param $tool_panel_section_id (OPTIONAL)
	 *  Id of the Galaxy tool panel section in which to load tools contained in
	 *  the Repository. Either this parameter must be an
	 * 	empty string or the new_tool_panel_section_label paramter must be an empty
	 *  string or both must be an empty string
	 *  BOTH CANNOT BE USED SIMULTANEOUSLY
	 *
	 * @param $install_repo_dependencies (OPTIONAL)
	 *  Set to True if you want to install repository dependencies defined for
	 *  the specified repository being installed. The default setting is False
	 *
	 * @param $shed_tool_conf (OPTIONAL)
	 *  The shed-related tool panel configuration file configured in the
	 *  "tool_config_file" setting in the Galaxy config file (ex: galaxy.ini).
	 *  At least oneshed-reelated tool panel config file is required to be
	 *  configured. Setting this paramter to a specific file enables you to choose
	 *  where the specified repository will be installed because the tool_path
	 *  attribute of the <toolbox> from the specified file is used as the
	 *  installation location (ex: <toolbox tool_path="../shed_tools">). If this
	 *  parameter is not set, a shed-related tool ppanel configuration file will
	 *  be selected automatically
	 *
	 * POST /api/tool_shed_repositories/install_repository_revisions
	 *
	 */
	public function install_repository_revisions ($admin_api_key, $tool_shed_urls, $names_of_repos, $owners_of_repos, $changeset_revisions,
			$new_tool_panel_section_label = NULL, $tool_panel_section_id = NULL, $install_repository_dependencies = NULL,
			$install_tool_dependencies = NULL, $shed_tool_conf = NULL){
		
	}
	
	/**
	 * Repair a specified repository revision previously installed into Galaxy
	 * 
	 * @param $admin_api_key 
	 *  The current Galaxy damin user's API key
	 *  
	 * @param $tool_shed_url
	 *  The base URL of the Toool Shed from which the Repo was installed
	 *  
	 * @param $name_of_repo
	 *  The name of the Repository
	 *  
	 * @param $owner_of_repo
	 *  The owner of the Repository
	 *  
	 * @param $changeset_revision
	 *  The changeset_revision of the Repository Meta data object associated
	 *  with the Repository
	 *
	 * POST /api/too_sed_repositories/repair_repository_revision
	 *
	 */
	public function repair_repository_revision ($admin_api_key, $tool_shed_url, $name_of_repo, $owner_of_repo, $changeset_revision){
		
	}
	
	/**
	 * Resets all metadata on all repositories installed into Galaxy in an 
	 * "orderly fashion"
	 *
	 * @param $admin_api_key
	 *  The current Galaxy damin user's API key
	 *
	 * PUT /api/tool_shed_repositories/reset_metadata_on_installed_repositories
	 *
	 */
	public function reset_metadata_on_installed_repositories ($admin_api_key){
		
	}
	
	/**
	 * Display a dictionary containing information about a specified 
	 * tool_shed_repository
	 *
	 * @param $id_of_repo
	 *  The encoded id of the Tool Shed Repository object
	 *
	 * GET /api/tool_shed_repositories/{encoded_tool_shed_repository_id}
	 *
	 */
	public function show ($id_of_repo){
		
	}
	
}

?>