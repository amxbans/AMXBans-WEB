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

if (isset($_SESSION['OkoK'], $_GET['action'])):
    header('Content-Type: application/json');

    if ($_GET['action'] != 'dbc') {
        require_once "../include/class.Config.inc";
        $config = new Config();
    }

    switch ($_GET['action']) {
        case 'dbc':
            require_once '../include/class.Route.inc';
            $content = "<?php
\$out = new stdClass();
\$out->host = '{$_SESSION["db_host"]}';
\$out->user = '{$_SESSION["db_user"]}';
\$out->pass = '{$_SESSION["db_pass"]}';
\$out->name = '{$_SESSION["db_name"]}';
\$out->prefix = '{$_SESSION["db_prefix"]}';

return \$out;";
            $error = file_put_contents(Route::getRootPath() . "/include/db.Config.inc", $content) ? false : 'FILE WRITE ERROR';
            break;
        case 'dbt':
            try {
                $query = file_get_contents('install.sql');
                $query = str_replace('PREFIX', $config->dbPrefix, $query);
                $config->getDb()->exec($query);
                $error = FALSE;
            } catch (PDOException $e) {
                $error = $e->getMessage();
            }
            break;
        case 'dbd':
            try {
                $query = file_get_contents('install-data.sql');
                $query = str_replace('PREFIX', $config->dbPrefix, $query);
                $config->getDb()->exec($query);
                $error = FALSE;
            } catch (PDOException $q) {
                $error = $q->getMessage();
            }
            break;
        case 'acc':
            $q0 = $config->getDb()
                ->query('SELECT level FROM ' . $config->dbPrefix . '_permissions LIMIT 1')->fetchObject();
            $q = $config->getDb()
                ->prepare('INSERT INTO ' . $config->dbPrefix . '_webadmins (username, password, perm_level, email) VALUES (?, ?, ?, ?)');
            $q->execute([$_SESSION['admin_user'], password_hash($_SESSION['admin_pass'], PASSWORD_DEFAULT), $q0->level, $_SESSION['admin_email']]);
            $error = FALSE;
            break;

        case 'cif':
            delTree(__DIR__);
    }

    echo json_encode([
        'status' => $error? 'error' : 'success',
        'text' => $error ?: '',
    ]);
endif;
function delTree($dir)
{
    $files = array_diff(scandir($dir), array('.', '..'));
    foreach ($files as $file)
        (is_dir("$dir/$file")) ? delTree("$dir/$file") : unlink("$dir/$file");
    return rmdir($dir);
}