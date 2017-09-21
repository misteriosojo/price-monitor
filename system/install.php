<?php
include("../system/config.inc");
require_once("db.inc");

$db = new DatabaseManager();

echo 'Creating necessary tables...<br>';
$db->createTables();

echo '<br><br>Tables created, tool ready to be used!<br>In '.Config::$redirectTimeout.' seconds you\'ll be redirect to the HomePage';

header('Refresh: '.Config::$redirectTimeout.'; URL=../index.php');
