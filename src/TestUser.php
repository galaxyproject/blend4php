<?php
include 'UserClient.inc';
include 'GalaxyInstance.inc';
include 'WorkflowClient.inc';




 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 $user= new UserClient($galaxy);
 $workflow = new WorkflowClient($galaxy);
 
 
 print 'I have started the test';
 print $workflow->show_workflow('f2db41e1fa331b3e');


?>