<?php
require_once '../src/GalaxyInstance.inc';
require_once './testConfig.inc';
require_once '../src/Genomes.inc';


class GenomesTest extends PHPUnit_Framework_TestCase {

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
   * Tests the index function to Genomes.
   *
   * Retreives a list of all of galaxy's genome information.
   *
   * @depends testInitGalaxy
   */
  function testIndex($galaxy){
    global $config;

    $genomes = new GalaxyGenomes($galaxy);

    // Case 1: An array of datatypes is successfully retreived in an array.
    $genomes_list = $genomes->index();
    $this->assertTrue(is_array($genomes_list), $galaxy->getErrorMessage());

    // Return a genome id.
    return $genomes_list[0][1];
  }

  /**
   * Tests the show function of Genomes.
   *
   * Retreives detailed information about a specific genome
   *
   * @depends testInitGalaxy
   * @depends testIndex
   */
  function testShow($galaxy, $genome_id){

    $genomes = new GalaxyGenomes($galaxy);

    // Case 1: Our method should return false given correct inputs,
    // at the moment, galaxy is still constructing this function
    $genome_details = $genomes->show($genome_id);
    $this->assertFalse(is_array($genome_details), $galaxy->getErrorMessage());

    // Case 2: our method should return false given incorrect inputs,
    $genome_details = $genomes->show("Incorrect");
    $this->assertFalse(is_array($genome_details), $galaxy->getErrorMessage());
  }

}
