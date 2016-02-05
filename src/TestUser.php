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
 $galaxy->authenticate('brian@yahoo.com', 'password');
 $history = new Histories($galaxy);
 //print $history->create('blah blah3', '5969b1f7201f12ae', "GOOBA" );
 print $history->archive_download('be0a27b9edd0db03', '3');
 print $history->getErrorMessage();

?>