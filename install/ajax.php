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
// TODO: Pārbaudīt instalēšanas gaitu + pabeigt izvadīt JSON ar success vai error

require_once "../include/class.Config.inc";
$config = new Config(TRUE);

if ($_SESSION['db_ok'] && $_SESSION['admin_ok']):
    header('Content-Type: application/json');
    switch ($_GET['action']) {
        case 'dbc':
            $content = "<?php
\$out = new stdClass();
\$out->host = '{$_SESSION["db_host"]}';
\$out->user = '{$_SESSION["db_user"]}';
\$out->pass = '{$_SESSION["db_pass"]}';
\$out->name = '{$_SESSION["db_name"]}';
\$out->prefix = '{$_SESSION["db_prefix"]}';

return \$out;";
            $error = !file_put_contents(Route::getRootPath() . "/include/db.Config.inc", $content);
            break;
        case 'dbt':
            try {
                $query = file_get_contents('install.sql');
                $query = str_replace('PREFIX_', $config->dbData->prefix, $query);
                $config->getDb()->exec($query);
                $error = FALSE;
            } catch (PDOException $e) {
                $error = $e->getMessage();
            }
            break;
        case 'dbd':
            try {
                $query = file_get_contents('install-data.sql');
                $query = str_replace('PREFIX', $config->dbData->prefix, $query);
                $config->getDb()->exec($query);
                $error = FALSE;
            } catch (PDOException $q) {
                $error = $q->getMessage();
            }
            break;
        case 'acc':
            $q0 = $config->getDb()->query('SELECT id FROM ' . $config->dbData->prefix . '_levels LIMIT 1')
                ->fetchObject();
            $q = $config->getDb()
                ->prepare('INSERT INTO ' . $config->dbData->prefix . '_webadmins (username, password, perm_level, email) VALUES (?, ?, ?, ?)');
            $q->execute([$_SESSION['admin_name'], password_hash($_SESSION['admin_pass'], PASSWORD_DEFAULT), $q0->id, $_SESSION['admin_email']]);
            $error = FALSE;
            break;

        case 'cif':
            delTree(__DIR__);
    }
endif;
function delTree($dir) {
    $files = array_diff(scandir($dir), array('.','..'));
    foreach ($files as $file) {
        (is_dir("$dir/$file")) ? delTree("$dir/$file") : unlink("$dir/$file");
    }
    return rmdir($dir);
}