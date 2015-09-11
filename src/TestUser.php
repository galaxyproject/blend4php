<?php
include 'UserClient.inc';
include 'GalaxyInstance.inc';



print 'I have started the test';
 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 $user= new UserClient($galaxy);
 
 
 print ($user->create_local_user('brianghiktydffraer', 'blahtrdhetrohgre@yahoo.com', 'blahhtfrshtsr'));


?>