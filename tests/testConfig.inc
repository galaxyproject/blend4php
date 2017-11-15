<?php

// Check the php version here
// If php 7.0 or greater  
if(version_compare(phpversion(), '7.0.0') >= 0)
{
	class_alias("PHPUnit\Framework\TestCase", "phpunitClass");
}
// Else less than php 7.0 (must be at least php 5.6 for phpunit to run)
else
{
	class_alias("PHPUnit_Framework_TestCase", "phpunitClass");
}
// Example of what the config array  should look like
$config = array(
  "host"=> 'localhost',
  "user" => 'blend4php',
  "email" => 'cgpwytko@gmail.com',
  "pass" => 'blend4php',
  "port" => '8080',
  "api_key" => 'dca3570433ca9766f5ec3411a5caf191', 
);