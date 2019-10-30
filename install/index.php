<?php
/**
 *    AMXBans v7
 * Copyright 2018 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

session_start();
error_reporting(E_ALL);
ini_set('display_errors', 1);

require_once "../include/class.Config.inc";
require_once("functions.inc");
$config = new Config(TRUE);


/**
 * Sites:
 * 1. Intro w/ licence agreement
 * 2. Checking settings
 * 3. Form things
 * 4. Review
 * 5. Running and completing installation
 */

$site = (int)(Route::getFakePathWay() ?: 1);
$siteMax = Route::getFakePathWay(1) == "CHECKED" ? 5 : 4;
if ($site < 1 || $site > $siteMax) $site = 1;


$smarty = new Templating();
$smarty->setTemplateDir(__DIR__ . '/templates')->setCompileDir(__DIR__ . '/templates');

switch ($site)
{
	case 1: // 1. Intro w/ licence agreement
		$langs = scandir('language');
		foreach ($langs as $file)
			if ($file != "." && $file != ".." && substr($file, 0, 4) != "lang" && substr($file, 0, 5) != "index")
				$lang[] = explode('.', $file)[0];
		$smarty->assign('languages', $lang);
		break;

	case 2:
		$php_settings = [
			"display_errors"      => toBool(ini_get('display_errors')),
			"register_globals"    => toBool(ini_get('register_globals')),
			"version_php"         => phpversion(),
			"server_software"     => $_SERVER["SERVER_SOFTWARE"],
			"mysql_enabled"       => in_array('mysql', PDO::getAvailableDrivers()),
		];

		$dirs_settings = [
			"include"     => is_writable(Route::getRootPath() . "/include"),
			"templates_c" => is_writable(Route::getRootPath() . "/templates/compiled"),
			'uploads'     => is_writable(Route::getRootPath() . '/webSources/uploads'),
		];

		if (version_compare(phpversion(), 7.2) > -1 AND $php_settings['mysql_enabled'] AND $dirs_settings['include'] AND $dirs_settings['templates_c'] AND $dirs_settings['uploads'])
			$smarty->assign('next', TRUE);
		$smarty->assign('php_settings', $php_settings);
		$smarty->assign('dirs_settings', $dirs_settings);
		break;

	case 3:
		if (isset($_POST['validate']))
		{
		    $errors = new FormErrors($_POST, __LANG__['STEP3_ERRORS']);
		    // DATABASE check
            $errors->validate([
                'db_host' => 'required',
                'db_user' => 'required',
                'db_name' => 'required',
            ]);
            $_SESSION["db_host"] = trim($_POST["db_host"]);
            $_SESSION["db_user"] = trim($_POST["db_user"]);
            $_SESSION["db_pass"] = trim($_POST["db_pass"]);
            $_SESSION["db_name"] = trim($_POST["db_name"]);
            $_SESSION["db_prefix"] = trim($_POST["db_prefix"]);
            if (!$errors->has('db_user')) {
                try {
                    $db = new PDO("mysql:dbname={$_SESSION['db_name']};host={$_SESSION['db_host']}", $_SESSION['db_user'], $_SESSION['db_pass']);
                    $db->exec("SET CHARSET utf8");
                } catch (PDOException $e) {
                    $errors->addError(__LANG__['STEP3_ERR_DB_CRED'] . ': ' . $e->getMessage(), ['db_host', 'db_user', 'db_pass', 'db_name']);
                }
            }
            if (!$errors->has() && $db->query('SELECT * FROM ' . $_SESSION['db_prefix'] . '_webconfig'))
                $errors->addError(__LANG__['STEP3_ERR_ALREADY_INSTALLED'], ['db_prefix']);
            if (!$errors->has() && !sql_has_all_privileges($db))
                $errors->addError(__LANG__['STEP3_ERR_NO_PRIVILEGES']);

			// admin account validation
            $errors->validate([
                'admin_email' => 'required',
                'admin_user' => 'required',
                'admin_pass' => 'required',
                'admin_pass2' => 'required|same:admin_pass',
            ]);
				$_SESSION["admin_email"] = trim($_POST["admin_email"]);
				$_SESSION["admin_user"] = trim($_POST["admin_user"]);
				$_SESSION["admin_pass"] = trim($_POST["admin_pass"]);
				$admin_pass = trim($_POST["admin_pass2"]);

			if (!$errors->has())
				$smarty->assign('next', TRUE);
			$smarty->assign('errors', $errors);
		}
		else
		    $smarty->assign('errors', new FormErrors([], []));
		break;

    case 5:
        $smarty->assign('securit', 'here!');
        break;
}
/*
/////////////// site 7 end /////////////////
if ($sitenr == 7 && $_SESSION["dbcheck"] == TRUE && $_SESSION["admincheck"] == TRUE && !isset($_POST["check7"]))
{
	// Open connection to database again
	$mysql = new mysqli($_SESSION["dbhost"], $_SESSION["dbuser"], $_SESSION["dbpass"], $_SESSION["dbdb"]);
	if (mysqli_connect_errno()) $msg = "_CANTCONNECT";
	include("tables.inc");
	//create db structure
	foreach ($table_create as $k => $v)
	{
		$table = ["table" => $k, "success" => ($mysql->query("CREATE TABLE " . $k . " (" . $v . ") DEFAULT CHARSET=utf8") ? "_CREATED" : "_ALREADYEXISTS")];
		$tables[] = $table;
	}
	//get default data
	include("datas.inc");
	//create default data
	foreach ($data_create as $k => $v)
	{
		$data = ["data" => $k, "success" => ($mysql->query("INSERT INTO " . $k . " " . $v) ? "_INSERTED" : "_FAILED")];
		$datas[] = $data;
	}
	//create default websettings
	$websettings_create = ["data" => "_CREATEWEBSETTINGS", "success" => ($mysql->query($websettings_query) ? "_INSERTED" : "_FAILED")];
	//create default usermenu
	$usermenu_create = ["data" => "_CREATEUSERMENU", "success" => ($mysql->query($usermenu_query) ? "_INSERTED" : "_FAILED")];
	//create webadmin userlevel
	$webadmin_create[] = ["data" => "_CREATEUSERLEVEL", "success" => ($mysql->query($userlevel_query) ? "_INSERTED" : "_FAILED")];
	//create webadmin
	$webadmin_create[] = ["data" => "_CREATEWEBADMIN", "success" => ($mysql->query($webadmin_query) ? "_INSERTED" : "_FAILED")];
	//install default modules
	foreach ($modules_install as $k => $v)
	{
		$modul = ["name" => $k, "success" => ($mysql->query($v) ? "_INSERTED" : "_FAILED")];
		$modules[] = $modul;
	}

	//write db.Config.inc

	$smarty->assign("content", $content);
	//create first log ;-)
	$mysql->query($log_query);

	$smarty->assign("tables", $tables);
	$smarty->assign("datas", $datas);
	$smarty->assign("modules", $modules);
	$smarty->assign("usermenu_create", $usermenu_create);
	$smarty->assign("websettings_create", $websettings_create);
	$smarty->assign("webadmin_create", $webadmin_create);
	$smarty->assign("checkvalue", "_SETUPEND");
}
if ($sitenr == 7 && isset($_POST["check7"]))
{
	//clear smarty cache
	$smarty->clear_compiled_tpl();
	//delete setup info
	//@unlink("setup.php");
	//@rmdir("install");
	header("Location: index.php");
	exit;
}*/

// Generate template
$smarty->assign("site", $site);
$smarty->assign("version", $config::version);

$smarty->display('setup.tpl');