<?php
require_once './testConfig.inc';
require_once '../galaxy.inc';

class ToolShedRepositoriesTest extends phpunitClass {
  /**
   * Intializes the Galaxy object for all of the tests.
   *
   * This function provides the $galaxy object to all other tests as they
   * are dependent on this one.
   */
  function testInitGalaxy() {
    global $config;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);
    $success = $galaxy->authenticate($config['email'], $config['pass']);
    $this->assertTrue($success, $galaxy->getErrorMessage());

    return $galaxy;
  }

  /**
  * Test the installation of a repository.
  *
  * @depends testInitGalaxy
  */
  public function testInstall($galaxy){
    // Case 1: We want to grab a test toolshed repository, keep in mind that we
    // need to grab something that would be specific to this test, small, and
    // not contribute to too much overhead to the tester's server.
    $tool_shed_repository = new GalaxyToolShedRepositories ($galaxy);

    $installed = $tool_shed_repository->install(array(
      'tool_shed_url' => 'https://testtoolshed.g2.bx.psu.edu/',
      'changeset' => 'd372217872de',
      'name' => 'apitooltests',
      'owner' => 'jmchilton',
      'install_tool_dependencies' => TRUE,
      'install_repository_dependencies' => TRUE,
    ));
    $this->assertTrue(!empty($installed), $galaxy->getErrorMessage());
    $result = preg_split('/ids=/' ,$installed)[1];
    return $result;
  }

//
//   /**
//   * Tests the check_for_updates functions
//   *
//   * @depends testInitGalaxy
//   * @depends testInstall
//   */
//   public function testCheckForUpdates($galaxy, $result){
//     $tool_shed_repository = new GalaxyToolShedRepositories ($galaxy);

//     // print_r($result);
//     $updates = $tool_shed_repository->checkForUpdates(array());
//     $this->assertTrue(is_array($updates), $galaxy->getErrorMessage());
//   }
//

  /**
   * Lists remote repositories connected to the local instance.
   *
   *
   * @depends testInitGalaxy
   */
  public function testIndex($galaxy){

    $tool_shed_repo = new GalaxyToolShedRepositories($galaxy);

    $result = $tool_shed_repo->index();

    $this->assertTrue(is_array($result), $galaxy->getErrorMessage());

//     $this->assertTrue(!empty($result), "You have no remote repositories to test the rest of this unit test suite with. Please
//         refer to the following URL https://wiki.galaxyproject.org/Admin/Tools/AddToolFromToolShedTutorial");

    return $result;
  }

  /**
   * Tests about a given tool shed repository's list of exported workflows
   * Whether the list is populated or not would imply if any of the workflows
   * from the remote repository are on the given galaxy instance.
   *
   * @depends testIndex
   * @depends testInitGalaxy
   */
  public function testExportWorkflow($result, $galaxy){

    $tool_shed_repo = new GalaxyToolShedRepositories($galaxy);

    $exports = $tool_shed_repo->exportedWorkflows(array('tool_shed_repo_id' => $result[0]['id']));

    $this->assertTrue(is_array($exports), $galaxy->getErrorMessage());
  }

  /**
   * Tests to see if a changeset revision string will be presented.
   * This will only happen if there exists a more recent version of the tool
   * shed
   *
   * @depends testIndex
   * @depends testInitGalaxy
   */
  public function testGetLatestInstallable($result, $galaxy){

    $tool_shed_repo = new GalaxyToolShedRepositories($galaxy);

    $inputs = array(
      'tool_shed_url' => 'https://' . $result[0]['tool_shed'],
      'name' => $result[0]['name'],
      'owner' => $result[0]['owner']
    );

    $result = $tool_shed_repo->getLatestInstallable($inputs);

    $this->assertTrue(is_string($result), $galaxy->getErrorMessage());
  }

  /**
   * Import specified workflow from external toolshed to local instance
   *
   * For the importing a workflow I need to have access to a repo that has
   * exported workflows.
   * Therefore I need to go through the index until I find a toolshed
   * that has an exported workflow that I can import.
   *
   * @depends testInitGalaxy
   * @depends testIndex
   *
   */
  public function testImportWorkflow($galaxy, $result){
    $tool_shed_repo = new GalaxyToolShedRepositories($galaxy);

    foreach ($result as $candidate){
      if (!empty($tool_shed_repo->exportedWorkflows(array('tool_shed_repo_id' => $candidate['id'])))){
        $inputs = array(
          'id' => $candidate['id'],
          'index' => $tool_shed_repo->exportedWorkflows(array('tool_shed_repo_id' => $candidate['id'][0]['index'])),
        );
//         ($candidate['id'], $tool_shed_repo->exportedWorkflows($candidate['id'])[0]['index']))
        $var = $tool_shed_repo->importWorkflow($inputs);
        print_r($var);
//         $this->assertTrue(, $galaxy->getErrorMessage());
      }
    }
  }

}
