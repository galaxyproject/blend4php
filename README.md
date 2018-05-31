![alt tag](https://raw.githubusercontent.com/galaxyproject/blend4php/master/misc/logo_500px.png)

![alt tag](https://travis-ci.org/galaxyproject/blend4php.svg?branch=master)
    
# About
The blend4php package is a PHP wrapper for the [Galaxy API](https://docs.galaxyproject.org/en/master/api_doc.html).  It follows the lead of [BioBlend](https://bioblend.readthedocs.io/en/latest/) which provides a Python package for interacting with Galaxy and CloudMan--hence the use of 'blend' in the name of this package.   blend4php currently offers a partial implementation of the Galaxy API and includes support for datasets, data types, folder contents, folders,  genomes, group roles, groups, group users, histories, history contents, jobs, libraries, library contents, requests, roles, search, tools, toolshed repositories, users, visualizations and workflows.  

The motivation for development of this library is for integration with [Tripal](http://tripal.info), an open-source toolkit for creation of online genomic, genetic and biological databases.  Integration of Tripal and Galaxy will allow the community research databases to provide next-generation analytical tools to their users using Galaxy.  However, this library was created independently of Tripal to support integration of any PHP application with Galaxy.

# Usage
Please see the [API documentation page](http://galaxyproject.github.io/blend4php/docs-v0.1a/html/index.html) for full information.

To use blend4php, first include the galaxy.inc file in your program.  For example:

    require_once('[blend4php installation dir]/galaxy.inc');

Where [blend4php installation dir] is where the blend4php package is installed.  

To Connect to a galaxy instance:

    $galaxy = new GalaxyInstance($hostname, $port, $use_https);
    
The variables $hostname and $port should be the hostname (or IP address) and port number of the remote Galaxy server.  If the server requires HTTPs then $use_https should be TRUE.

To authenticate and retrieve the user's API key for future requests:

    $success = $galaxy->authenticate($username, $password, $error);
    if (!$success) {
      // Handle a failed authentication.
    }

Where $username is the name of the user on the remote Galaxy server and $password is the user's password. The $error variable will contain any error message if authentication fails.  The function will return false if authentication fails.

If the API key for the user is already known, the authentication step can be skiped and the API key directly set:

    $galaxy->setAPIKey($api_key);
    
Where the $api_key variable contains the API key of the user on the remote Galaxy server.  

To interact with Galaxy regarding jobs, workflows, users, etc.  Please see the [blend4php API documentation](http://galaxyproject.github.io/blend4php/docs-v0.1a/html/index.html).

# Example
## Connecting to an existing Galaxy Server
The following is an example script that can be executed on the command-line. It is contained in the examples directory of this repository and named 'check_job_status.php'.  Typically PHP scripts are not used on the command-line but here we do so for the sake of demonstration.  The following script receives as its first argument the API key of a user on the public Galaxy server at https://usegalaxy.org.  It authenticates the user using the API key, queries the remote server to find the list of workflows that the user has created and prints the names of those workflows.

    <?php
    
    // Include the blend4php library.
    require_once('../galaxy.inc');
    
    // The domain name of the host to connect to.
    $hostname  = 'usegalaxy.org';
    // Port 443 is the typical port for HTTPS.
    $port      = '443';
    // The remote server uses HTTPS for secure connections.
    $use_https = TRUE;
    // The API key to use for connections will be provided on the command-line
    // by the user calling this script.
    $api_key   = $argv[1];
    
    // Instantiate the Galaxy object.
    $galaxy = new GalaxyInstance($hostname, $port, $use_https);
    $galaxy->setAPIKey($api_key);
    
    // Check the version of Galaxy.
    $version = $galaxy->getVersion();
    if (!$version) {
      print $galaxy->getErrorMessage() . "\n";
      exit -1;
    }
    print "Found Galaxy version: " . $version['version_major'] . "\n";

    // Instantiate a GalaxyWorkflows object.
    $gwf = new GalaxyWorkflows($galaxy);

    // Get the list of workflows that the user currently has on the remote Galaxy
    // server.
    $workflows = $gwf->index();
    print "You have the following workflows:\n";
    foreach ($workflows as $index => $workflow) {
      print ($index + 1) . ". " . $workflow['name'] . "\n";
    }

# Error Handling
All functions in the blend4php library return FALSE on failure. If failure
occurs then the most recent error can be retrieved using the following:

    $error = $galaxy->getError();
    $emessage = $error['message'];
    $etype = $error['type'];

Alternatively, the message and type can be retrieved independently:

    $emessage = $galaxy->getErrorMessage();
    $etype = $galaxy->getErrorType();

# Testing
blend4php contains unit testing using the PHPUnit framework.  It is recommended to not run any tests on a Galaxy instance that will be used for production as these tests will add a lot of records (i.e. jobs, histories etc.) that cannot easily be removed.  Testing should be perofrmed on a test Galaxy instance. To execute test on an Ubuntu 14.04 LTS server.

1) Install PHPUnit

    sudo apt-get install phpunit

2) Install CURL support for PHP

    sudo apt-get install php5-curl

3) Edit the tests/testConfig.inc file to provide login credentials to your Galaxy Test server.
   
4) Execute all testing

    phpunit

5) Execute a single test
 
    phpunit GalaxyInstanceTest.php

# Funding
This work is supported by the US National Science Foundation (NSF) award #1443040, titled “CIF21 DIBBS: Tripal Gateway, a Platform for Next-Generation Data Analysis and Sharing.” 

# License
blend4php is made available under version 3 of the GNU Lesser General Public License

# Cite
If you find blend4php useful in your publishable work. Please include this reference in your citation list:

Wytko, C., Soto, B., & Ficklin, S. P. (2017). blend4php: a PHP API for galaxy. Database: The Journal of Biological Databases and Curation, 2017, baw154. http://doi.org/10.1093/database/baw154
