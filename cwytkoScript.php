<?php
require_once './src/GalaxyInstance.inc';
require_once './src/Workflows.inc';
require_once './src/ToolShedRepositories.inc';
require_once './src/Requests.inc';
require_once './src/Folders.inc';
require_once './src/FolderContents.inc';
require_once './src/Users.inc';
// Connect and authenticate via galaxy.
// Break all code down into logical blocks.
$galaxy = new GalaxyInstance('localhost','8080', FALSE);

$galaxy->authenticate('cgpwytko@gmail.com', 'potato15');

$usr = new Users($galaxy);

//print $usr->index(false, 'cgpwytko@gmail.com', NULL, false);
//$usr->show($username)



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
// $rec->index();

$fol = new Folders($galaxy);
// print_r($fol->show('1cd8e2f6b131e891'));
//$fol->create('f2db41e1fa331b3e', 'Pickle', 'Troos_Value');
// print_r($fol->get_permissions('1cd8e2f6b131e891'));
// $manage = array ('cgpwytko@gmail.com');
// list ($stuff) = $manage;
// $fol->set_permissions('1cd8e2f6b131e891', $add = NULL, $stuff, $modify = 'cgpwytko@gmail.com');
//  print_r($fol->get_permissions('1cd8e2f6b131e891'));
// $fol->delete('1cd8e2f6b131e891', TRUE);
// print_r($fol->show('1cd8e2f6b131e891'));

// $stuff = array ('name' => 'titanic', 'description' => 'allo');

// $fol->update('1cd8e2f6b131e891', $stuff);
// print_r($fol->show('1cd8e2f6b131e891'));

$fc = new FolderContents($galaxy);
//print_r($fc->index('1cd8e2f6b131e891'));
