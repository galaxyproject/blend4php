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

//print $workflow->get_workflows();
print $history->archive_export("5969b1f7201f12ae");

?>