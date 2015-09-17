<?php
include 'UserClient.inc';
include 'GalaxyInstance.inc';




 $galaxy = new GalaxyInstance('localhost', '8080');
 $galaxy-> authenticate('brian@yahoo.com', 'password');
 $user= new UserClient($galaxy);
 
 print 'I have started the test';
 print ($user->create_user_apikey('briangffraer'));


?>