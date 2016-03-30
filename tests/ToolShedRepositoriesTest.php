<?php
require_once '../src/ToolShedRepositories.inc';
require_once './testConfig.inc';
require_once '../src/GalaxyInstance.inc';


class ToolShedRepositoriesTest extends PHPUnit_Framework_TestCase {
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
   * Lists remote repositories connected to the
   *
   * @depends testInitGalaxy
   */
  public function testIndex($galaxy){

    $tool_shed_repo = new ToolShedRepositories($galaxy);

    $result = $tool_shed_repo->index();

    $this->assertTrue(is_array($result), $tool_shed_repo->getErrorMessage());

    $this->assertTrue(!empty($result), "You have no remote repositories to test the rest of this unit test suite with. Please
        refer to the following URL https://wiki.galaxyproject.org/Admin/Tools/AddToolFromToolShedTutorial");

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

    $tool_shed_repo = new ToolShedRepositories($galaxy);

    $exports = $tool_shed_repo->exportedWorkflows($result[0]['id']);

    $this->assertTrue(is_array($exports), $tool_shed_repo->getErrorMessage());
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

    $tool_shed_repo = new ToolShedRepositories($galaxy);

    $result = $tool_shed_repo->getLatestInstallable('https://' . $result[0]['tool_shed'], $result[0]['name'], $result[0]['owner']);

    $this->assertTrue(is_string($result), $tool_shed_repo->getErrorMessage());
  }

  /**
   * Import specified workflow from external toolshed to local instance
   *
   * For the importing a workflow I need to have access to a repo that has
   * exported workflows.
   * Therefore I need to go thorugh the index until I find a toolshed
   * that has an exported workflow that I can import.
   *
   * @depends testInitGalaxy
   * @depends testIndex
   *
   */
  public function testImportWorkflow($galaxy, $result){
    $tool_shed_repo = new ToolShedRepositories($galaxy);

    foreach ($result as $candidate){
      if (!empty($tool_shed_repo->exportedWorkflows($candidate['id']))){
        $this->assertTrue(($tool_shed_repo->importWorkflow($candidate['id'], $tool_shed_repo->exportedWorkflows($candidate['id'])[0]['index'])), $tool_shed_repo->getErrorMessage());
      }
    }
  }

}
