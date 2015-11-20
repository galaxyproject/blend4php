<?php
require_once './src/GalaxyInstance.inc';
require_once './src/Workflows.inc';
require_once './src/ToolShedRepositories.inc';
require_once './src/Requests.inc';


// Connect and authenticate via galaxy.
// Break all code down into logical blocks.
$galaxy = new GalaxyInstance('localhost','8080', FALSE);
$galaxy->authenticate('cgpwytko@gmail.com', 'potato15');






// Test the functions within the WorkflowClinet.
// Start by testing the delete_workflow function
// We need to provide some workflow_id in delete_workflow($workflow_id);
$wfc = new Workflows($galaxy);

//$wfc->delete_workflow('1cd8e2f6b131e891');
//f597429621d6eb2b ebfb8f50c6abde6d 33b43b4e7093c91f
//$wfc->export_workflow_json('5969b1f7201f12ae');
//$wfc -> index();


//$wfc -> export_workflow_to_local_path('ebfb8f50c6abde6d', '/home/cwytko/Downloads');
 //$wfc -> get_workflow_inputs('f597429621d6eb2b', 'Reference annotati');
 //$wfc -> get_workflows(NULL, 'potato');
 
//$wfc -> import_shared_workflow();

//$wfc -> import_workflow_from_local_path ('/home/cwytko/Downloads/Galaxy-Workflow-RNAseqTRAPLINE.ga');
$tsc = new ToolShedClient($galaxy);

//$tsc->exported_workflows('3f5830403180d620');
//$tsc->get_latest_installable_revision(NULL,NULL,NULL, NULL);


$rec = new Requests($galaxy);
$rec->index();