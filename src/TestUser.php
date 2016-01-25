<?php
include 'Users.inc';
include_once 'GalaxyInstance.inc';
include_once 'Roles.inc';
include_once 'Workflows.inc';
include_once 'DataTypes.inc';
include_once 'Tools.inc';
include_once 'Histories.inc';
include_once 'HistoryContents.inc';
include_once 'Users.inc';
include_once 'Search.inc';


 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy->authenticate('brian@yahoo.com', 'password');
 
 $workflow = new Workflows($galaxy);	
 $search = new Search($galaxy);



 
 //print $search->create('SELECT * FROM HISTORIES WHERE ID = 290670ee50ab85f0');
 print $search -> create('select * from history where id = \'290670ee50ab85f0\'');
 print $search->getErrorMessage();
 
 //'select'. trail: [expr]

 

?>