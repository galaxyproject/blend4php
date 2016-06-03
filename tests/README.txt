It is recommended to not run any tests on a Galaxy instance that will be used
for production as these tests will add a lot of records (i.e. jobs, histories
etc.) that cannot easily be removed.  Testing should be perofrmed on a test
Galaxy iinstance. To execute test on an Ubuntu 14.04 LTS server.

1) Install PHPUnit

   sudo apt-get install phpunit

2) Install CURL support for PHP

  sudo apt-get install php5-curl

3) Edit the testConfig.inc file to provide login credentials to your 
   Galaxy Test server.  Copy an example from the file.
   
4) Execute all testing

  phpunit

5) Execute a single test
 
  phpunit GalaxyInstanceTest.php
