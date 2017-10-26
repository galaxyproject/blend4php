<?php
require_once '../galaxy.inc';
require_once './testConfig.inc';


class LibraryContentsTest extends phpunit_5.6_Class {
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
  * Tests the index() function.
  *
  * The index function retrieves a list of the library contents.
  *
  * @depends testInitGalaxy
  *
  */
  public function testIndex($galaxy){
    $library_contents = new GalaxyLibraryContents($galaxy);
    $libraries = new GalaxyLibraries($galaxy);

    $library_index = $libraries->index(array());
    $index = $library_contents->index(array('library_id' =>$library_index[0]['id']));
    $this->assertTrue(is_array($index), $galaxy->getErrorMessage());

    $return_array = array(
      'index' => $index,
      'library_index' => $library_index,
    );
    return $return_array;
  }

  /**
  * Tests the create() function.
  *
  * The create function creates a library content within the specified
  * library.
  *
  * @depends testInitGalaxy
  * @depends testIndex
  */
  public function testCreate($galaxy, $return_array){
    $library_contents = new GalaxyLibraryContents($galaxy);
    $histories = new GalaxyHistories($galaxy);
    $folders = new GalaxyFolders($galaxy);

    $library_id = $return_array['library_index'][0]['id'];

    $history_index = $histories->index(array());
    $this->assertTrue(is_array($history_index), $galaxy->getErrorMessage());

    // Case 1: Place a file in the root of the library (not placing the
    // content within a sub-folder).
    $library_content = $library_contents->create(array(
      'library_id' => $library_id,
      // The id of the library is a folder so we use this as a folder_id.
      'folder_id' => $return_array['index']['id'],
      'create_type' => 'file',
      // This will give a the 'oldest', undeleted history.
      'from_hda_id' => end($history_index)['id'],
    ));
    $this->assertTrue(is_array($library_content), $galaxy->getErrorMessage());

    // Case 2: Place a folder-content within a sub-folder in the library
    // A folder within a folder *inception music*.
    $new_folder = $folders->create(array(
      'parent_id' => $library_id,
      'name' => uniqid($return_array['library_index'][0]['id'] . '-sub-folder-'),
      'description' => 'A sub-folder to test the 2nd case of the library content create test function.',
    ));
    $this->assertTrue(is_array($new_folder), $galaxy->getErrorMessage());

    $library_content = $library_contents->create(array(
      'library_id' => $library_id,
      'folder_id' => $new_folder['id'],
      'create_type' => 'folder',
      'name' => 'Library content sub-folder',
      'description' => 'A folder created by the library content create function during the unit test.'
    ));
    $this->assertTrue(is_array($library_content), $galaxy->getErrorMessage());

    // Case 3: Change the upload_option to something else other than the
    // default. Unsure on how to use the 'collection' option in create_type.
    // This test will FAIL if you are not admin OR if you haven't set your
    // library_import_dir in the galaxy.ini.

//     $library_content = $library_contents->create(array(
//       'library_id' => $library_id,
//       'folder_id' => $new_folder['id'],
//       'create_type' => 'file',
//       'upload_option' => 'upload_directory',
//       'server_dir' => getcwd() . '/LibContents/',
//     ));
//     $this->assertTrue(is_array($library_content), $galaxy->getErrorMessage());

    // Case 4: Use the 'collection' create_type for this test case.
    // On Case 3 I attempted to use a 'collection' while using the
    // 'upload_directory' in upload_option and it did not work.
    // This type of data is still shaky and is difficult to deal with at this
    // This test will FAIL if you are not admin OR if you haven't set your
    // time: https://github.com/galaxyproject/planemo/commit/fea51fc

    // $inputs = array(
    //   'library_id' => $return_array['library_index'][0]['id'],
    //   'folder_id' => $return_array['index']['id'],
    //   'create_type' => 'collection',
    //   'collection_type' => 'list',
    //   'element_identifiers' => getcwd() . '/files/test.bed',
    // );
    //
    // $library_content = $library_contents->create($inputs);
    // $this->assertTrue(is_array($library_content), $galaxy->getErrorMessage());

  }


  /**
  * Tests the show() function.
  *
  * The index function retrieves a list of the library contents.
  *
  * @depends testInitGalaxy
  * @depends testIndex
  */
//   public function testShow($galaxy){
//     $library_contents = new GalaxyLibraryContents($galaxy);
//     $libraries = new GalaxyLibraries($galaxy);
//
//     $library_index = $libraries->index(array());
//     $index = $library_contents->index(array('library_id' =>$library_index[0]['id']));
//     $this->assertTrue(is_array($index), $galaxy->getErrorMessage());
//   }
}
