<?php
include 'Users.inc';
include_once 'GalaxyInstance.inc';
include_once 'Roles.inc';
//include_once 'Workflows.inc';
include_once 'DataTypes.inc';
include_once 'Tools.inc';
include_once 'Histories.inc';
include_once 'HistoryContents.inc';
include_once 'Users.inc';


 $galaxy = new GalaxyInstance('localhost', '8080');

 
 
 print $users->index(true,"blarb@gmail.com",'bri',true);
 print $users->getErrorMessage();

 


 

?>