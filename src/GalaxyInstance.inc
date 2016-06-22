<?php

/**
 * @file
 *
 * The GalaxyInstance class.
 *
 * The GalaxyInstance class is used to connect to a remote Galaxy server.
 * It authenticates and maintains the API key for the user.  The functions
 * in this class correspond to the Galaxy API functions and are named similarly
 * to their Python counterpart.
 */

/*! \mainpage blend4php Documentation
 *
 * \section intro_sec Introduction
 *
 * The blend4php package is a PHP wrapper for the Galaxy API
 * (https://docs.galaxyproject.org/en/master/api_doc.html).  It follows the
 * lead of BioBlend (https://bioblend.readthedocs.io/en/latest/) which
 * provides a Python package for interacting with Galaxy and CloudMan--hence
 * the use of 'blend' in the name of this package.   blend4php currently
 * offers a partial implementation of the Galaxy API and includes support
 * for datasets, data types, folder contents, folders,  genomes, group roles,
 * groups, group users, histories, history contents, jobs, libraries, library
 * contents, requests, roles, search, tools, toolshed repositories, users,
 * visualizations and workflows.
 *
 * The motivation for development of this library is for integration with
 * Tripal (http://tripal.info), an open-source toolkit for creation of
 * online genomic, genetic and biological databases.  Integration of Tripal
 * and Galaxy will allow the community research databases to provide
 * next-generation analytical tools to their users using Galaxy.
 * However, this library was created independently of Tripal to support
 * integration of any PHP application with Galaxy.
 *
 * \section usage_sec Usage
 *
 * To use blend4php, first include the galaxy.inc file in your program.  For example:
 *
 * @code
 *    require_once('[blend4php installation dir]/galaxy.inc')
 * @endcode
 *
 * Where [blend4php installation dir] is where the blend4php package is installed.
 *
 * To Connect to a galaxy instance:
 *
 * @code
 *   $galaxy = new GalaxyInstance($hostname, $port, $use_https);
 * @endcode
 *
 * The variables $hostname and $port should be the hostname (or IP address)
 * and port number of the remote Galaxy server.  If the server requires HTTPs
 * then $use_https should be TRUE.
 *
 * To authenticate and retrieve the user's API key for future requests:
 *
 * @code
 *   $success = $galaxy->authenticate($username, $password, $error)
 *   if (!$success) {
 *     // Handle a failed authentication.
 *   }
 * @endcode
 *
 * Where $username is the name of the user on the remote Galaxy server and
 * $password is the user's password. The $error variable will contain any
 * error message if authentication fails.  The function will return false
 * if authentication fails.
 *
 * If the API key for the user is already known, the authentication step can
 * be skiped and the API key directly set:
 *
 * @code
 *   $galaxy->setAPIKey($api_key);
 * @endcode
 *
 * Where the $api_key variable contains the API key of the user on the
 * remote Galaxy server.
 *
 * To interact with Galaxy regarding jobs, workflows, users, etc.  Please
 * review the Classes pages for each respective class.
 *
 * \section error_sec Error Handling
 *
 * All functions in the blend4php library return FALSE on failure. If failure
 * occurs then the most recent error can be retrieved using the following:
 *
 * @code
 *   $error = $galaxy->getError();
 *   $emessage = $error['message']
 *   $etype = $error['type']
 * @endcode
 *
 * Alternatively, the message and type can be retrieved independently:
 *
 * @code
 *   $emessage = $galaxy->getErrorMessage();
 *   $etype = $galaxy->getErrorType();
 * @endcode
 *
 *
 * \section funding_sec Funding
 * This work is supported by the US National Science Foundation (NSF)
 * award #1443040, titled “CIF21 DIBBS: Tripal Gateway, a Platform for
 * Next-Generation Data Analysis and Sharing.”
 *
 * \section license_sec License
 * blend4php is available under version 2 of the GNU General Public License
 */

require_once 'HTTPRequest.inc';

class GalaxyInstance extends GalaxyHTTPRequest {
  /** The hostname where the Galaxy server is located. */
  protected $host;
  /** The port on which the remote Galaxy instance is runinng. */
  protected $port;
  /** Should be set to TRUE if the remote server uses HTTPS. */
  protected $use_https;
  /** The API Key for the user connection. */
  protected $api_key;


  /**
   * The GalaxyInstance constructor.
   *
   * @param $hostname
   *   The hostname where the Galaxy server is located.
   * @param $port
   *   The port on which the remote Galaxy instance is runinng.
   * @param $use_https
   *   Should be set to TRUE if the remote server uses HTTPS. Defaults
   *   to TRUE.
   *
   * @return
   *   An instance of a GalaxyInstance object.
   *
   *
   */
  function __construct($hostname, $port, $use_https = FALSE) {
    parent::__construct();

    $this->host = $hostname;
    $this->port = $port;
    $this->use_https  = $use_https;
    $this->api_key = '';

  }

  /**
   * Retrieves the version of the Galaxy API.
   *
   * @return
   *
   *
   *
   */
  public function getVersion() {
    return $this->httpGET($this->getURL() . '/api/version');
  }

  /**
   * Authenticates a user with the remote Galaxy instance.
   *
   * Corresponds to the Galaxy API method and path:
   * GET /api/authenticate/baseauth
   *
   * @param $username
   *   The username of the user.
   * @param $password
   *   The password for the user.
   * @param $message
   *   If authentication fails then this variable will be set to contain
   *   the error message.
   *
   * @return
   *   TRUE if authentication was successful, FALSE otherwise.
   *
   *
   */
  public function authenticate($username, $password, &$message = '') {

    // First just try to get the version.  If not, then this means
    // Galaxy may not be available and we should error out before trying
    // further.
    $URL = $this->getURL();
    $version = $this->getVersion();
    if (!$version) {
      $this->setError('Galaxy', "Cannot connect to Galaxy server: $URL.");
      return FALSE;
    }

    // Now try to authenticate.
    $response = $this->auth($URL . '/api/authenticate/baseauth', $username, $password);
    if (!$response) {
      return FALSE;
    }
    $this->setAPIKey($response['api_key']);

    return TRUE;
  }

  /**
   * Returns the URL for the remote Galaxy server.
   *
   * The URL returned will include the protocol (HTTP, HTTPS),
   * the hostname and the port.
   *
   * @return string
   *   The URL for the remote Galaxy instance.
   *
   *
   */
  public function getURL() {
    if ($this->use_https) {
      return "https://". $this->host .":". $this->port;
    }
    else {
      return "http://". $this->host .":". $this->port;
    }
  }

  /**
   * Sets the API Key for this Galaxy instance.
   *
   * @param $api_key
   *   The API key of the Galaxy user.
   *
   *
   */
  public function setAPIKey($api_key) {
    $this->api_key = $api_key;
  }

  /**
   * Acquires the API key
   *
   * @return string
   *    The API key that authorizes a user to certain actions.
   *
   *
   */
  public function getAPIKey(){
    return $this->api_key;
  }
}
