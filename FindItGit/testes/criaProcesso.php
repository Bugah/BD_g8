<?php
error_reporting(E_ALL);

/* Add redirection so we can get stderr. */
$handle = popen('/bin/sh test.sh '.$_GET['a']. ' ' .$_GET['b'].  ' 2>&1', 'r');
echo "'$handle'; " . gettype($handle) . "\n";
$read = fread($handle, 2096);
echo $read;
pclose($handle);
?>