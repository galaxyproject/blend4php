<?php

require_once '../galaxy.inc';
require_once './testConfig.inc';



class WorkflowsTest extends phpunitClass {

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
    $success = $galaxy->authenticate($config['email'], $config['pass']);
    $this->assertTrue($success, $galaxy->getErrorMessage());

    return $galaxy;
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
    $workflows = new GalaxyWorkflows($galaxy);
    $workflow_id = "";
  
    // Case 1: successfully return a workflow created from json
    $json_workflow = file_get_contents("./files/Galaxy-Workflow-UnitTest_Workflow.ga");
    $workflow = $workflows->create(array('workflow' => $json_workflow));
    $this->assertTrue(is_array($workflow), $galaxy->getErrorMessage());
    $workflow_id = $workflow['id'];
  
    // Case 2: successfully return false when incorrect information provided
    // for the JSON workflow.
    $workflow = $workflows->create(array('workflow' => "{ Incorrect JSON }"));
    $this->assertFalse(is_array($workflow), $galaxy->getErrorMessage());
  
    // TODO: create more tests for the other parameters, once we understand how
    // the parameters are formated.
  
    return $workflow_id;
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
    $workflows = new GalaxyWorkflows($galaxy);

    // Case 1: A list of workflows is successfully retreived in an array.
    $workflows_list = $workflows->index(array());
    $this->assertTrue(is_array($workflows_list), $galaxy->getErrorMessage());

    // Case 2: enter boolean parameter also retreives an array
    $workflows_list = $workflows->index(array('is_published' => TRUE));
    $this->assertTrue(is_array($workflows_list), $galaxy->getErrorMessage());
    
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
    $workflows = new GalaxyWorkflows($galaxy);

    // Case 1: given a workflow id, the show function successfully retreive a
    // workflow
    $workflow = $workflows->show(array('workflow_id' => $workflow_id));
    $this->assertTrue(is_array($workflow), $galaxy->getErrorMessage());

    // Case 2: enter boolean parameter also retreives an array
    $workflow = $workflows->show(array('workflow_id' => $workflow_id, 'show_published' => TRUE));
    $this->assertTrue(is_array($workflow), $galaxy->getErrorMessage());

    // Case 3: providing a malformed workflow id with a TRUE paramater returns
    // false.
    $workflow = $workflows->show(array('workflow_id' => '123', 'show_published' => TRUE));
    $this->assertFalse(is_array($workflow), "Workflows class 'show' should have returned false upon incorrect workflow id");

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
    $workflows = new GalaxyWorkflows($galaxy);

    // Create the necessary obejcts for this function:
    $histories = new GalaxyHistories($galaxy);
    $history_content = new GalaxyHistoryContents($galaxy);
    $tools = new GalaxyTools($galaxy);

    // Create our very own history for this test!
    $ourHistory = $histories->create(array('name' => "Testing Workflows Invoke"));
    $history_id = $ourHistory['id'];

    // Now we need some content!
    $inputs['files'] = array(
      0 => array(
        'name'=> 'test.bed',
        'path'=> getcwd() . '/files/test.bed',
      ),
    );
    $inputs['tool_id'] = 'upload1';
    $inputs['history_id'] = $history_id;
    $tool = $tools->create($inputs);
    $content_list = $history_content->index(array('history_id' => $history_id));

    // Make sure the count of this list is greater than 0
    $this->assertTrue((count($content_list) > 0) , "Content was not added to history.");
    $content_id = $content_list[0]['id'];
	
    // Case 1: Successfully execute workflow with default parameters
    $invocation = $workflows->invoke(array('workflow_id' => $workflow_id, 'inputs' => array(array('id' => $content_id, 'src' => 'hda'))));
    $this->assertTrue(is_array($invocation), $galaxy->getErrorMessage());
    $this->assertTrue(array_key_exists('state', $invocation) and $invocation['state'] == 'new',
        "Workflow invoked returned an array but the workflow is not in the proper state.");
    // Make sure the newly created invoke workflow is not of state 'new' or state
    // 'running'.
    while ($invocation['state'] == 'running' or $invocation['state'] == 'new' ) {
      sleep(1);
      $invocation =  $workflows->showInvocations(array('workflow_id' => $workflow_id, 'invocation_id' => $invocation['id']));
      $this->assertTrue(is_array($invocation), $galaxy->getErrorMessage());
    }

    // Case 2: Successfully execute workflow with history id
    $invocation = $workflows->invoke(array(
      'workflow_id' => $workflow_id,
      'inputs' => array(array('id' => $content_id, 'src' => 'hda')),
      'history_id' => $history_id
      
    ));
    $this->assertTrue(is_array($invocation), $galaxy->getErrorMessage());
    // Make sure the newly created invoke workflow is not of state 'new' or state
    // 'running'.
    while ($invocation['state'] == 'running' or $invocation['state'] == 'new' ) {
      sleep(1);
      $invocation =  $workflows->showInvocations(array('workflow_id' => $workflow_id, 'invocation_id' => $invocation['id']));
      $this->assertTrue(is_array($invocation), $galaxy->getErrorMessage());
    }
    // Check to make sure history has the outputted dataset
    $content_list = $history_content->index(array('history_id' => $history_id));
    $this->assertTrue(count($content_list) > 1 and
        array_key_exists('name', $content_list[1]) and $content_list[1]['name'] ==
        'Line/Word/Character count on data 1', "Content not in the desired history");

  }

  /**
   * Tests the indexInvocation function of workflows
   *
   * Retreives a list of invocation steps
   *
   * @depends testInitGalaxy
   * @depends testCreate
   */
  function testIndexInvocation ($galaxy, $workflow_id){
    global $config;
    $workflows = new GalaxyWorkflows($galaxy);
    $invocation_id = '';

    // Case 1: correctly return a list of invocations upon a correct workflow_id
    $invocations = $workflows->indexInvocations(array('workflow_id' => $workflow_id));
    $this->assertTrue(is_array($invocations), $galaxy->getErrorMessage());
	$invocation_id = $invocations[0]['id'];

    // Case 2: correctly return false upon an incorrect workflow_id
    $invocations = $workflows->indexInvocations(array('workflow_id' => "@@@"));
    $this->assertFalse(is_array($invocations), "Returned non-false on incorrect workflow id");

    return $invocation_id;
  }

 /**
  * Tests the showInvocation function of workflows
  *
  * Retreives a detailed view of a workflow invocation
  *
  * @depends testInitGalaxy
  * @depends testCreate
  * @depends testIndexInvocation
  */
 function testShowInvocation($galaxy, $workflow_id, $invocation_id){
  global $config;
  $workflows = new GalaxyWorkflows($galaxy);
  $step_id = '';

  // Case 1: correctly return a list of invocations upon a correct workflow_id
  $invocation = $workflows->showInvocations(array('workflow_id' => $workflow_id, 'invocation_id' => $invocation_id));
  $this->assertTrue(is_array($invocation), $galaxy->getErrorMessage());
  $this->assertTrue(count($invocation) > 0);
  $step_id = $invocation['steps'][0]['id'];

  // Case 2: return false if incorrect $invocation_id entered
  $invocation = $workflows->showInvocations(array('workflow_id' => $workflow_id, 'invocation_id' => "@@"));
  $this->assertFalse(is_array($invocation), $galaxy->getErrorMessage());

  return $step_id;
 }


 /**
  * Tests the invocationSteps method of workflows
  *
  * retreives information regarding a given invocation step.
  *
  * @depends testInitGalaxy
  * @depends testCreate
  * @depends testIndexInvocation
  * @depends testShowInvocation
  */
 function testInvocationSteps($galaxy, $workflow_id, $invocation_id, $step_id){
   global $config;
   $workflows = new GalaxyWorkflows($galaxy);

   // Case 1: Correctly find information about an invocation step, given correct
   // parameters
   $invocation_step = $workflows->invocationSteps(array('workflow_id' => $workflow_id, 'invocation_id' => $invocation_id, 'step_id' => $step_id));
   $this->assertTrue(is_array($invocation_step), $galaxy->getErrorMessage());
 }

 /**
  * Tests the workflows updateInvocationSteps function
  *
  * Updates the steps to a given workflow
  * This workflow function is incomplete and should return false.
  *
  * @depends testInitGalaxy
  * @depends testCreate
  * @depends testIndexInvocation
  * @depends testShowInvocation
  */
 function testUpdateInvocation($galaxy, $workflow_id, $invocation_id, $step_id){
   global $config;
   $workflows = new GalaxyWorkflows($galaxy);

   $error = $workflows->updateInvocationSteps($workflow_id, $invocation_id, $step_id);
   $this->assertFalse($error,"updateInvocations function should return false");
 }

 /**
  * Tests the workflows cancelInvocation function
  *
  * Deletes an invocation
  * This workflow function is incomplete and should return false.
  *
  * @depends testInitGalaxy
  * @depends testCreate
  * @depends testIndexInvocation
  * @depends testShowInvocation
  */
 function testCancelInvocation($galaxy, $workflow_id, $invocation_id){
   global $config;
   $workflows = new GalaxyWorkflows($galaxy);

   $error = $workflows->cancelInvocation(array('workflow_id' => $workflow_id, 'invocation_id' => $invocation_id));
   $this->assertFalse($error,"updateInvocations function should return false");
 }

 /**
  * Tests Workflows update function
  *
  * Updates a workflow based on a given JSON object
  *
  * @depends testInitGalaxy
  * @depends testCreate
  */
 function testUpdate($galaxy, $workflow_id){
   global $config;
   $workflows = new GalaxyWorkflows($galaxy);

   $json_workflow = file_get_contents("./files/Galaxy-Workflow-update.ga");

   // Case 1: Successfully update workflows given a correct json workflow
   $updated_workflow = $workflows->update(array('workflow_id' => $workflow_id, 'workflow' => $json_workflow));
   $this->assertTrue(is_array($updated_workflow), $galaxy->getErrorMessage());

   // Case 2: Gracefully return false given an incorrect workflow_id
   $updated_workflow = $workflows->update(array('workflow_id' => "@@", 'workflow' => $json_workflow));
   $this->assertFalse(is_array($updated_workflow), "Incorrect workflow returned true");

   // Case 3: Gracefully return false given an incorrect json
   $updated_workflow = $workflows->update((array('workflow_id' => $workflow_id, 'workflow' => "{Workflow Update Test}")));
   $this->assertFalse(is_array($updated_workflow), "Incorrect workflow returned true");

 }

 /**
  * Tests downloads
  *
  * Obtains a workflow and returns it as if to download. It differs from export
  * in terms of its returned 'input' parameters.
  *
  * @depends testInitGalaxy
  * @depends testCreate
  */
 function testDownload($galaxy, $workflow_id){
   global $config;

   $workflows = new GalaxyWorkflows($galaxy);

   // Case 1: Successfully export workflow as an array
   $array_workflow = $workflows->download(array('workflow_id' => $workflow_id));
   $this->assertTrue(is_array($array_workflow), $galaxy->getErrorMessage());

   // Case 2: Gracefully return false if an incorrect workflow id is entered.
   $array_workflow = $workflows->download(array('workflow_id' => "@@@"));
   $this->assertFalse(is_array($array_workflow), $galaxy->getErrorMessage());
 }

 /**
  * Tests the buildModule() funciton
  *
  * Builds a workflow module.
  * This workflow function is incomplete and should return false.
  *
  * @depends testInitGalaxy
  * @depends testCreate
  */
 function testBuildModule($galaxy, $workflow_id){
   global $config;

   $workflows = new GalaxyWorkflows($galaxy);

   // Case 1: Successfully export workflow as an array
   $error = $workflows->buildModule(NULL);
   $this->assertFalse($error, "the buildModule function should return false");

 }
 /**
  * Tests the deletion of a workflow
  *
  * @depends testInitGalaxy
  * @depends testCreate
  * @depends testIndex
  * @depends testShow
  * @depends testInvoke
  * @depends testIndexInvocation
  * @depends testShowInvocation
  * @depends testInvocationSteps
  * @depends testUpdateInvocation
  * @depends testCancelInvocation
  * @depends testUpdate
  * @depends testExport
  * @depends testDownload
  * @depends testBuildModule
  *
  */
 function delete($galaxy, $workflow_id){
   global $config;

   $workflows = new GalaxyWorkflows($galaxy);

   // Case 1: Successfully export workflow as an array
   $deleted = $workflows->delete(array('workflow_id' => $workflow_id));
   $this->assertTrue(is_array($deleted), $galaxy->getErrorMessage());

   $marked_deleted = $deleted['deleted'] == "true";
   $this->assertTrue($marked_deleted, "Workflow not marked as deleted");

   // Case 2: Gracefully return false upon incorrect wokrflow id
   $deleted = $workflows->delete(array('workflow_id' => "@@@"));
   $this->assertFalse(is_array($deleted), "Deleting a non-existing workflow should return false");

 }

}
