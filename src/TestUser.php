<?php
include 'UserClient.inc';
include 'GalaxyInstance.inc';
include 'WorkflowClient.inc';




 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 $user= new UserClient($galaxy);
 $workflow = new WorkflowClient($galaxy);
 
 
 print 'I have started the test';

 $workflow_id = $workflow->obtainWorkflow_id('connor');
 print $workflow->create(NULL, NULL, NULL, NULL, NULL, NULL, "5969b1f7201f12ae", NULL, NULL, NULL, 'I hope this works');

?>