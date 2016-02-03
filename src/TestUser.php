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
 $history = new HistoryContents($galaxy);
// print $history->create('290670ee50ab85f0', '6505e875ddb66fd2');
 //print $history->update('290670ee50ab85f0', '33b43b4e7093c91f');

 /*print $history->getErrorMessage();
 print $history->delete('290670ee50ab85f0', '6505e875ddb66fd2');
 print $history->getErrorMessage();
 */
 $tool = new Tools($galaxy);
 $inputs = array('33b43b4e7093c91f');
 print $tool->build('sort1', $inputs);
 print $tool->getErrorMessage();
?>