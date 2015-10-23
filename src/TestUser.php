<?php
include 'UserClient.inc';
include 'GalaxyInstance.inc';
include 'WorkflowClient.inc';
include 'ToolClient.inc';
include 'HistoryClient.inc';


 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 $user= new UserClient($galaxy);
 $workflow = new WorkflowClient($galaxy);
 $tool = new ToolClient($galaxy);
 $history = new HistoryClient($galaxy);
 
 print 'I have started the test ';

print $workflow->get_workflows();
//print $workflow->workflow_dict('f597429621d6eb2b', './')
//print $workflow->delete_workflow('1cd8e2f6b131e891');
// $workflow_id = $workflow->obtainWorkflow_id('connor');
// print $workflow->create(NULL, NULL, NULL, NULL, NULL, NULL, "5969b1f7201f12ae", NULL, NULL, NULL, 'I hope this works');
//$tool_id = $tool->obtainTool_id("HbVar");
//print $tool_id;
//print $tool->get_tools(); 
//print $tool->executeTool('genomespace_file_browser_prod', '1.01');
//print $workflow->index(); 
//print $tool->build_tool('genomespace_file_browser_prod');
//print $tool->diagnostics('genomespace_file_browser_prod');
//print $tool->reload('genomespace_file_browser_prod');
//print $history->archive_download('df7a1f0c02a5b08e', 'df7a1f0c02a5b08e');

?>