<?php
/**
 * @file
 *
 * The GalaxyService class.
 *
 * The GalaxyService class is used as a base class for all other Galaxy
 * classes.
 */

class GalaxyAPIService {

  protected $galaxy;

  /**
   * The constructor.
   *
   * @param GalaxyInstance $galaxy
   *   A GalaxyInstance object.
   */
  public function __construct($galaxy) {
    $this->galaxy = $galaxy;
  }

  /**
   * Checks to see if any required arguments are missing for a function call.
   *
   * @param $params
   *   The associative array of parameters passed to the function.
   * @param $required
   *   An array of required parameters.
   *
   * @return
   *   TRUE if all required parameters are present, FALSE otherwise.
   */
  protected function checkRequiredParams($params, $required) {
    // First make sure the $parmas argument is an array.
    if (!is_array($params)) {
      $this->galaxy->setError('API', 'This function requires the $params argument to be provided as an array');
      return FALSE;
    }

    // Second check for missing paramters.
    $missing = array();
    foreach ($required as $param_name) {
      if (!array_key_exists($param_name, $params)) {
        $missing[] = $param_name;
      }
    }

    if (count($missing) > 0) {
      $this->galaxy->setError('API', 'The following parameters are required: ' . implode(', ', $missing) . '.');
      return FALSE;
    }
    return TRUE;
  }
}