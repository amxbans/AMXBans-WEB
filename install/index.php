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


$smarty = new Templating($config);
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
            "templates_c" => is_writable(Route::getRootPath() . "/include/templates/compiled"),
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

            if (!$errors->has()) {
                $smarty->assign('next', TRUE);
                $_SESSION['OkoK'] = true;
            }
            $smarty->assign('errors', $errors);
        }
        else
            $smarty->assign('errors', new FormErrors([], []));
        break;

    case 5:
        $smarty->assign('securit', 'here!');
        $smarty->assign('route', Route::getBaseURL());
        break;
}

// Generate template
$smarty->assign("site", $site);
$smarty->assign("version", $config::version);

$smarty->display('setup.tpl');