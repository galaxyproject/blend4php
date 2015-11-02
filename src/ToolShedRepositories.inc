<?php

require_once "GalaxyInstance.inc";
		

class ToolShedClient{
	
	private $galaxy = NULL;
	// A variable to set to true if debugging, Toggles print statements
	private $debug = True;
	
	/**
	 * Implements the constructor.
	 *
	 * @param GalaxyInstance $galaxy
	 */
	function __construct($galaxy) {
		$this->galaxy = $galaxy;
	}
	
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
	// TODO: the way to acquire the tools is an inconsistent interface, sometimes
	// I need to browse the repository instead of the main tool shed repository
	// I would like to know if there's a reason for that
  
	public function exported_workflows ($tool_shed_repo_id){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();

		$url = $this->galaxy->getURL() . '/api/tool_shed_repositories/' . $tool_shed_repo_id . '/exported_workflows'  .  '?key=' . $api_key;
		
		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "GET");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
		
		$result = curl_exec($i);
		 
		$info = curl_getinfo($i);
		 
		$array = json_decode($result, true);
		
		// Do we want to print out our results? I would like to think so
		print_r ($array);
		 
		curl_close($i);
	}
	
	/**
	 * Get the latest installable revision of a specified repository from a 
	 * specified Tool Shed.
	 *
	 * @param $admin_api_key
	 *	The current Galaxy admin user's API key
	 *   
	 * @param $tool_shed_url
	 * 	The URL of the Tool Shed from which to retrieve the Repo revision
	 *  This should be something similar to this:
	 *  https://toolshed.g2.bx.psu.edu/repository?repository_id=253e22fdaf6a52c1

	 * @param $name_of_repo
	 * 	The name of the repository
	 * 
	 * @param $name_owner_of_repo
	 * 	The name of the owner of the repository
	 *
	 *  POST /api/tool_shed_repositories/get_latest_installable_revision
	 *  
	 *  Basically what this api function will do is take the url and api_key to
	 *  see if there is a new revision to the existing toolshed. While the user
	 *  could do it themselves just as easy, this enables a bit less user
	 *  interaction with the toolshed mechanics 
	 * 
	 *
	 * 
	 *
	 */
	public function get_latest_installable_revision ($admin_api_key, $tool_shed_url, $name_of_repo, $name_owner_of_repo){
		$i = curl_init();
		$api_key = $this->galaxy->getAPIKey();

		$url = $this->galaxy->getURL() . '/api/tool_shed_repositories/' . 'get_latest_installable_revision';
		
		$data = array(
				
				'tool_shed_url' => 'https://toolshed.g2.bx.psu.edu/repository?repository_id=253e22fdaf6a52c1', 
				'name' => 'codonlogo',
				'owner' => 'davidmurphy', 
				'key' => $api_key
				
		);
		$data_string = '';
		foreach($data as $key=>$value) { 
			$data_string .= $key.'='.$value.'&'; 
		}
		//rtrim($data_string, '&');
		print($data_string);
		print "\n";
		
		curl_setopt($i, CURLOPT_URL, $url);
		curl_setopt($i,CURLOPT_POST, count($data));
		curl_setopt($i, CURLOPT_POSTFIELDS, $data_string);
		curl_setopt($i, CURLOPT_CUSTOMREQUEST, "POST");
		curl_setopt($i, CURLOPT_RETURNTRANSFER, true);
		
		$result = curl_exec($i);
		  
		$info = curl_getinfo($i);
		 
		$array = json_decode($result, true);
		
		// Do we want to print out our results? I would like to think so
		print_r ($array);
		 
		curl_close($i);
		
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
