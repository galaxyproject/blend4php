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
   * Checks if any required arguments are missing for a function call.
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

    // Get details about the calling function
    $caller = debug_backtrace()[1]['function'];
    $class = get_class($this);

    // First make sure the $parmas argument is an array.
    if (!is_array($params)) {
      $this->galaxy->setError('API', 'This function requires the $params argument to be provided as an array in function ' . $class . '::' . $caller . '().');
      return FALSE;
    }

    // Second check for missing paramters.
    $missing = array();
    foreach ($required as $param_name) {
      if (!array_key_exists($param_name, $params)) {
        $missing[] = $param_name;
      }
      else if(!isset($params[$param_name]) or $params[$param_name] === '') {
        $missing[] = $param_name;
      }
    }

    if (count($missing) > 0) {
      $this->galaxy->setError('API', 'The following parameters for function ' . $class . '::' . $caller . '() are required: ' . implode(', ', $missing) . '.');
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Checks if there are any parameters other than what is allowed.
   *
   * @param $params
   *   The associative array of parameters passed to the function.
   * @param $allowed
   *   An array of allowed parameters.
   *
   * @return
   *   TRUE if only allowed parameters are present, FALSE otherwise.
   */
  protected function checkAllowedParams($params, $allowed) {

    // Get details about the calling function
    $caller = debug_backtrace()[1]['function'];
    $class = get_class($this);

    // First make sure the $parmas argument is an array.
    if (!is_array($params)) {
      $this->galaxy->setError('API', 'This function requires the $params argument to be provided as an array in function ' . $class . '::' . $caller . '().');
      return FALSE;
    }

    // Second check for not allowed paramters.
    $not_allowed = array();
    foreach ($params as $param_name => $value) {
      if (!in_array($param_name, $allowed)) {
        $not_allowed[] = $param_name;
      }
    }
    if (count($not_allowed) > 0) {
      $this->galaxy->setError('API', 'The following parameters for function ' . $class . '::' . $caller . '() are not allowed: ' . implode(', ', $not_allowed) . '.');
      return FALSE;
    }
    return TRUE;
  }
}