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
include_once 'Visualizations.inc';
include_once 'Jobs.inc';
include_once 'Groups.inc';



 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy->authenticate('bob@gmail.com', 'password');
 $user = new Users($galaxy);
 //print $user->create('blarb', 'blarb@gmail.com', 'password');
 $role = new Roles($galaxy);
 //print $role->create('Teddy Bear Hugger3', 'Hugs teddy bears', array('f597429621d6eb2b'));
 //print $role->getErrorMessage();
 $group = new Groups($galaxy);
 //print $group->create('pedophilia2 attack of the bear', array('f597429621d6eb2b'), array('f2db41e1fa331b3e'));
 print $group->update('f2db41e1fa331b3e', 'name changed to this');
 //$Job = new Jobs($galaxy);
 //print $Job->search('sort1',array('a676e8f07209a3be'));
 //$workflow = new Workflows($galaxy);
 
 //$search = new Search($galaxy);
//$visualization = new Visualizations($galaxy);

//print $visualization->create('blob3','it worked again!','00112');
//print $visualization->getErrorMessage();


 

?>