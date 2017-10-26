<?php
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';
require_once '../src/DataTypes.inc';


class DataTypesTest extends phpunit56Class {

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
   * Tests Datatypes sniffers() function
   *
   * Retreives the sniffer datatypes.
   *
   * @depends testInitGalaxy
   */
  function testSniffers($galaxy){
    global $config;
    $datatypes = new GalaxyDatatypes($galaxy);

    // Case 1: Sniffer datatypes returned in an array successfully.
    $sniffer = $datatypes->sniffers();
    $this->assertTrue(is_array($sniffer), $galaxy->getErrorMessage());

  }

  /**
   * Tests Datatypes converters() function
   *
   * Retreives the converter datatypes.
   *
   * @depends testInitGalaxy
   */
  function testConverters($galaxy){
    global $config;
    $datatypes = new GalaxyDatatypes($galaxy);

    // Case 1: Converter datatypes returned in an array successfully.
    $converter = $datatypes->converters();
    $this->assertTrue(is_array($converter), $galaxy->getErrorMessage());
  }

  /**
   * Tests Datatypes edamFormats() function.
   *
   * Retreives the edam format datatypes.
   *
   * @depends testInitGalaxy
   */
  function testEdamFormats($galaxy){
    global $config;
    $datatypes = new GalaxyDatatypes($galaxy);

    // Case 1: Edam Formats datatypes returned in an array successfully.
    $edam = $datatypes->edamFormats();
    $this->assertTrue(is_array($edam), $galaxy->getErrorMessage());
  }

  /**
   * Tests Datatype mapping() function.
   *
   * Retreives the edam format datatypes.
   *
   * @depends testInitGalaxy
   */
  function testMapping($galaxy){
    global $config;
    $datatypes = new GalaxyDatatypes($galaxy);

    // Case 1: Mapper datatypes are returned in an array successfully.
    $mapping = $datatypes->mapping();
    $this->assertTrue(is_array($mapping), $galaxy->getErrorMessage());
  }

  /**
   * Tests Datatype index() function.
   *
   * Retreives a list of all of the datatypes.
   *
   * @depends testInitGalaxy
   */
  function testIndex($galaxy){
    global $config;
    $datatypes = new GalaxyDatatypes($galaxy);

    // Case 1: A list of datatypes is successfully retreived in an array.
    $datatypes_list = $datatypes->index();
    $this->assertTrue(is_array($datatypes_list), $galaxy->getErrorMessage());
  }
}
