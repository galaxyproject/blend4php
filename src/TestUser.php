<?php
include 'UserClient.inc';
include 'GalaxyInstance.inc';
include 'WorkflowClient.inc';




 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 $user= new UserClient($galaxy);
 $workflow = new WorkflowClient($galaxy);
 
 
 print 'I have started the test';
 //print $user->obtain_user_id('anotherbrian');
 #print $workflow->show_workflow('f2db41e1fa331b3e');
 #print $workflow->run_workflow('f2db41e1fa331b3e'); 
 print $workflow->obtainWorkflow_id('connor');
?>