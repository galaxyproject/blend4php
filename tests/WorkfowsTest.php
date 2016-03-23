<?php
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';
require_once '.././src/Workflows.inc';
require_once './HistoryContentsTest.php';

class WorkflowsTest extends PHPUnit_Framework_TestCase {

  /**
   * Intializes the Galaxy object for all of the tests.
   *
   * This function provides the $galaxy object to all other tests as they
   * are  on this one.
   */
  function testInitGalaxy() {
    global $config;

    // Connect to Galaxy.
    $galaxy = new GalaxyInstance($config['host'], $config['port'], FALSE);

    $response = $galaxy->authenticate($config['email'], $config['pass']);

    return $galaxy;
  }

  /**
   * Tests the index funciton of workflows
   *
   * retreives a list of workflows from galaxy
   *
   * @depends testInitGalaxy
   */
  function testIndex($galaxy){
    global $config;
    $workflows = new Workflows($galaxy);

    // Case 1: A list of workflows is successfully retreived in an array.
    $workflows_list = $workflows->index();
    $this->assertTrue(is_array($workflows_list), $workflows->getErrorMessage());

    // Case 2: enter boolean parameter also retreives an array
    $workflows_list = $workflows->index(TRUE);
    $this->assertTrue(is_array($workflows_list), $workflows->getErrorMessage());

    // Return a workflow id
    return $workflows_list[0]['id'];
  }

  /**
   * Tests the show function of the workflows class
   *
   * Retreives detailed information about a specific workflow
   *
   * @depends testInitGalaxy
   * @depends testIndex
   */
  function testShow($galaxy, $workflow_id){
    global $config;
    $workflows = new Workflows($galaxy);

    // Case 1: given a workflow id, the show function successfully retreive a
    // workflow
    $workflow = $workflows->show($workflow_id);
    $this->assertTrue(is_array($workflow), $workflows->getErrorMessage());

    // Case 2: enter boolean parameter also retreives an array
    $workflow = $workflows->show($workflow_id, TRUE);
    $this->assertTrue(is_array($workflow), $workflows->getErrorMessage());

    // Case 3: providing a malformed workflow id with a TRUE paramater returns
    // false.
    $workflow = $workflows->show("123", TRUE);
    $this->assertFalse(is_array($workflow), "Workflows class 'show' should have returned false upon incorrect workflow id");

    // Case 4: Providing a malformed id alone also returns false
    $workflow = $workflows->show("123");
    $this->assertFalse(is_array($workflow), "Workflows class 'show' should have returned false upon incorrect workflow id");
  }

  /**
   * Tests the create function of the workflows class.
   *
   * Creates or updates a workflow.
   *
   * @depends testInitGalaxy
   */
  function testCreate($galaxy){
    global $config;
    $workflows = new Workflows($galaxy);
    $workflow_id = "";

    // Case 1: successfully return a workflow created from json
    $json_workflow = file_get_contents("./files/Galaxy-Workflow-UnitTest_Workflow.ga");
    $workflow = $workflows->create(array('workflow'=>$json_workflow));
    $this->assertTrue(is_array($workflow), $workflows->getErrorMessage());
    $workflow_id = $workflow['id'];

    // Case 2: successfully return false when incorrect information provided
    // for the JSON workflow.
    $workflow = $workflows->create(array('workflow'=>"{ Incorrect JSON }"));
    $this->assertFalse(is_array($workflow), $workflows->getErrorMessage());

    // TODO: create more tests for the other parameters, once we understand how
    // the parameters are formated.

    return $workflow_id;
  }

  /**
   * Tests the invoke function of workflows
   *
   * Invokes a specific workflow
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testInvoke($galaxy, $workflow_id){
    global $config;
    $workflows = new Workflows($galaxy);

    // We need a dataset_id
    $history_contents_test = new HistoryContentsTest();
    $content_id = $history_contents_test->testCreate($galaxy);

    $workflow_results = $workflows->invoke($workflow_id, array($content_id));
    print("\n THIS IS THE RESULTS FROM THE WORKFLOW! \n");
    print_r($workflow_results);
    $this->assertTrue(is_array($workflow_results), $workflows->getErrorMessage());


  }

}
