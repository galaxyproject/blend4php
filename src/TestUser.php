<?php
//include 'Users.inc';
include 'GalaxyInstance.inc';
//include 'Workflows.inc';
include 'Tools.inc';



 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 //$user= new Users($galaxy);
 //$workflow = new Workflows($galaxy);
 $tool = new Tools($galaxy);
 //$history = new Histories($galaxy);
 
 print 'I have started the test ';

 print $tool->build_tool('Intervalfeaw2Maf_pairwise1');
 print $tool->getErrorMessage();
//print $workflow->get_workflows();
//print $history->archive_export("5969b1f7201f12ae");
//print $history->deleteHistory('df7a1f0c02a5b08e');
?>