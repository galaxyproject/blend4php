<?php
include 'UserClient.inc';
include 'GalaxyInstance.inc';
include 'WorkflowClient.inc';
include 'ToolClient.inc';


 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 $user= new UserClient($galaxy);
 $workflow = new WorkflowClient($galaxy);
 $tool = new ToolClient($galaxy);
 
 print 'I have started the test';

 print $tool->executeTool("sort1", "1.0.3", "files__UCSC_Main_on_Human__knownGene_(genome).bed");
// $workflow_id = $workflow->obtainWorkflow_id('connor');
// print $workflow->create(NULL, NULL, NULL, NULL, NULL, NULL, "5969b1f7201f12ae", NULL, NULL, NULL, 'I hope this works');
//$tool_id = $tool->obtainTool_id("HbVar");
//print $tool_id;
print $tool->get_tools(); 

?>