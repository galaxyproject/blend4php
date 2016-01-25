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


 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy->authenticate('brian@yahoo.com', 'password');
 
 $workflow = new Workflows($galaxy);	
 $search = new Search($galaxy);
$visualization = new Visualizations($galaxy);

print $visualization->create('blob3','it worked again!','00112');
print $visualization->getErrorMessage();


 

?>