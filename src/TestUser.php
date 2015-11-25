<?php
include 'Users.inc';
include_once 'GalaxyInstance.inc';
//include_once 'Workflows.inc';
include_once 'DataTypes.inc';
//include_once 'Tools.inc';
//include_once 'Histories.inc';
//include_once 'HistoryContents.inc';



 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('bob@gmail.com', 'password');
 $datatype = new Datatypes($galaxy);
 print $datatype->edam_formats();


//print $historyContent->create('5969b1f7201f12ae');
?>