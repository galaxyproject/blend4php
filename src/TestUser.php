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
	$workflow = new Workflows($galaxy);
	//print $workflow->update("a799d38679e985db");
	print $workflow->build_module('6505e875ddb66fd2',array('8a81cf6f989c4467'));
	//print $workflow->invoke('ebfb8f50c6abde6d', array('33b43b4e7093c91f','3cc0effd29705aa3'));
	
	print $workflow->getErrorMessage();
?>