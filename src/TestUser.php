<?php
include 'Users.inc';
include_once 'GalaxyInstance.inc';
//include_once 'Workflows.inc';
include_once 'DataTypes.inc';
include_once 'Tools.inc';
include_once 'Histories.inc';
//include_once 'HistoryContents.inc';



 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 $tool = new Tools($galaxy);
 
 //print $tool->download("ucsc_table_direct_archaea1");
 print $tool->index("ucsc_table_direct_archaea1", NULL, TRUE)
 
 //$datatype = new Datatypes($galaxy);
 //print $datatype->edam_formats();
 //$history = new Histories($galaxy);
//print $history->index(); 


?>