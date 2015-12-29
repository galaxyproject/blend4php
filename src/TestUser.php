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
 $galaxy-> authenticate('brian@gmail.com', 'password');
 $users = new Users($galaxy);
 //print $users->create("blarb", "blarb@gmail.com", "blarby");
 //print $users->api_key("f597429621d6eb2b");
 //print $users->delete("f597429621d6eb2b");
 //print $users->index();
 
 
 print $users->index(true,"blarb@gmail.com",'bri',true);
 print $users->getErrorMessage();

 

 

?>