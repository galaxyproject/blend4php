<?php
include 'Users.inc';
include_once 'GalaxyInstance.inc';
include_once 'Roles.inc';
//include_once 'Workflows.inc';
include_once 'DataTypes.inc';
include_once 'Tools.inc';
include_once 'Histories.inc';
include_once 'HistoryContents.inc';



 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 $tool = new Tools($galaxy);
 $roles = new Roles($galaxy);
 $historyContents = new HistoryContents($galaxy);
 //print $historyContents ->update("5969b1f7201f12ae", '5969b1f7201f12ae', array('name'=>'booba'));
 //print $historyContents->delete('5969b1f7201f12ae', '5969b1f7201f12ae', True);
 print $historyContents->index('5969b1f7201f12ae',"5969b1f7201f12ae,a799d38679e985db" );
 print "! ! !! The error message is: ". $historyContents -> getErrorMessage() . " ";
 //print $roles->create('Make Admin out of you 12', 'I am testing how this role stuff works', array('df7a1f0c02a5b08e', '1cd8e2f6b131e891'));
 //print "the error report: " . $roles->getErrorMessage();
 //print $roles->index();
 //print $roles->show('f2db41e1fa331b3e');
 //print $tool->download("ucsc_table_direct_archaea1");
 //print $tool->index("ucsc_table_direct_archaea1", NULL, TRUE)
 //print $tool->build("ucsc_table_direct_archaea1");
 //$datatype = new Datatypes($galaxy);
 //print $datatype->edam_formats();
 //$history = new Histories($galaxy);
//print $history->index(); 


?>