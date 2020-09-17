<?php
/**
 *    AMXBans v7
 * Copyright 2020 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

/**  */

namespace Controllers;

use Models\Ban;
use Models\DB;
use Models\Server;
use Support\Path;

/**
 * Class IndexController
 *
 * @package Controllers
 */
class IndexController extends \Support\BaseController
{
    public function getSysInfo()
    {
        //optimise tables
        if (isset($_GET["optimise"])) {
            $tables = DB::selectRaw(
                "SHOW TABLES FROM `" . $this->site->config->getDb()->getDbName() . "` LIKE ?",
                [$this->site->config->getDb()->prefix . '_%'],
                null,
                \PDO::FETCH_COLUMN
            );
            $tables = implode('`, `', $tables);

            $tables = DB::rawSQL("OPTIMIZE TABLES `$tables`");

            $this->site->output->assign(
                'message',
                [
                    'type' => $tables ? 'success' : 'warning',
                    'text' => $tables ? \Lang::get('db_optimised') : \Lang::get('db_not_optimised')
                ]
            );
            db_log('Web config', 'Optimised tables ' . $tables ? 'successfully' : 'NOT successfully');
        }

        //prune db
        if (isset($_GET["prune"]) && \Auth::hasPermission('prune_db')) {
            /** @var Ban[] $bans */
            $bans   = Ban::query()->where('expired', 0)->select(['bid', 'ban_created', 'ban_length']);
            $pruned = 0;
            foreach ($bans as $ban) {
                $tz = $ban->server->timezone_fixx * 3600;
                $bl = $ban->ban_length * 60;
                //prune expired bans
                if ($ban->ban_created + $tz + $bl < time() && $bl) {
                    $pruned++;
                    $ban->expired = true;
                    $ban->save();

                    // Saving ban log of pruned ban
                    $banLog              = new \Models\BansLog();
                    $banLog->bid         = $ban->bid;
                    $banLog->admin_nick  = '--SYSTEM--';
                    $banLog->edit_reason = 'Bantime expired';
                    $banLog->created_at  = new \DateTime('@' . ($ban->ban_created + $tz + $bl));
                    $banLog->save();
                }
            }
            $this->site->output->assign(compact('pruned'));
            $this->site->output->append('messages', ['type' => 'success', 'text' => \Lang::get('bans_pruned')]);
            db_log('Web config', 'Pruned bans');
        }
        $php = [
            "display_errors"      => toBool(ini_get('display_errors')),
            "post_max_size"       => ini_get('post_max_size') . " (" . return_bytes(
                    ini_get('post_max_size')
                ) . " bytes)",
            "upload_max_filesize" => ini_get('upload_max_filesize') . " (" . return_bytes(
                    ini_get('upload_max_filesize')
                ) . " B)",
            "max_execution_time"  => ini_get('max_execution_time'),
            "version_php"         => phpversion(),
            'version_mysql'       => DB::selectRaw('SELECT VERSION();', null, null, \PDO::FETCH_COLUMN)[0],
            "server_software"     => $_SERVER["SERVER_SOFTWARE"],
            "bc-gmp"              => (extension_loaded('bcmath') or extension_loaded('gmp')) ? \Lang::get(
                'yes'
            ) : \Lang::get('no'),
            "gd"                  => extension_loaded('gd') ? gd_info()['GD Version'] : false,
        ];
        $this->site->output->assign(compact('php'));

        /* TODO WEBSITE SETTINGS (web/settings): move this action to there
                //clear smarty cache
                if (isset($_POST["clear"]) && $_SESSION["loggedin"]) {
                    //special function available from smarty
                    $smarty->clear_compiled_tpl();
                    $user_msg = "_CACHEDELETED";
                }*/
        /* TODO: v7.1
                //repair files db
                if (isset($_POST["file_repair"]) && $_SESSION["loggedin"]) {
                    $repaired = sql_get_files_count_fail(1);
                }
                //repair comments db
                if (isset($_POST["comment_repair"]) && $_SESSION["loggedin"]) {
                    $repaired = sql_get_comments_count_fail(1);
                }*/

        $this->site->output->assign(
            [
                'bans'          => [
                    'total'  => Ban::query()->count('bid'),
                    'active' => Ban::query()->where('expired', false)->count('bid'),
                ],
                'db_size'       => format_size($this->site->config->getDb()->getSize()),
                'prune'         => $this->site->config->prune_bans,
                'comment_count' => \Models\Comment::query(\Models\Comment::COMMENTS)->count('id'),
                'file_count'    => \Models\Comment::query(\Models\Comment::FILES)->count('id'),
            ]
        );
        $this->site->output->display('admin.index.sys_info.tpl');
    }

    public function getBanAdd()
    {
        $this->site->output->assign('reasons', DB::table('reasons')->select(['id', 'reason'], \PDO::FETCH_KEY_PAIR));
        $this->site->output->display('admin.index.ban_add.tpl');
    }

    public function postBanAdd()
    {
        if (!$this->site->validateFormAuth()) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => \Lang::get('invalidCSRF')]);
            return $this->getBanAdd();
        }
        if (!\Auth::hasPermission('bans_add')) {
            $this->site->output->assign('message', \Lang::get('no_access'));
            return $this->getBanAdd();
        }

        $validator = new \FormErrors($_POST, \Lang::get('validation_errors'));
        $validator->validate(
            [
                'ban_type' => 'required',
                'SteamID'  => (false !== strpos($_POST['ban_type'], 'S') ? 'required|' : '') . 'steamid',
                'IP'       => (false !== strpos($_POST['ban_type'], 'I') ? 'required|' : '') . 'ip',
                'username' => 'required',
            ]
        );
        if (!@$_POST['reason'] && !@$_POST['custom_reason']) {
            $validator->addValidationError('custom_reason', 'required_without', ['reason']);
        }
        if ($validator->has()) {
            $this->site->output->assign('messages', $validator);
            return $this->getBanAdd();
        }

        // Chech if an active ban exist
        $active = Ban::query()->where('expired', 0);
        if (false !== strpos($_POST['ban_type'], 'S')) {
            $active->where('player_id', $_POST['SteamID']);
        }
        if (false !== strpos($_POST['ban_type'], 'I')) {
            $active->where('player_ip', $_POST['IP']);
        }
        if ($active->count('bid')) {
            $this->site->output->assign('message', \Lang::get('active_ban_exists'));
            return $this->getBanAdd();
        }

        Ban::query()->insert(
            [
                'player_ip'   => $_POST['IP'],
                'player_id'   => $_POST['SteamID'],
                'player_nick' => $_POST['username'],
                'admin_nick'  => \Auth::get('username'),
                'admin_id'    => \Auth::get('username'),
                'admin_ip'    => $_SERVER['REMOTE_ADDR'],
                'ban_type'    => $_POST['ban_type'],
                'ban_reason'  => @$_POST['reason'] ?: $_POST['custom_reason'],
                'ban_created' => time(),
                'ban_length'  => $_POST['length'] ?: 0,
                'server_name' => 'website',
            ]
        );
        db_log(
            'BAN MANAGEMENT',
            'Added ban: ID ' . DB::lastInsertId(
            ) . ' (' . $_POST['username'] . ') for ' . ($_POST['length'] ? $_POST['length'] . ' minutes' : 'permanent time')
        );

        return $this->getBanAdd();
    }

    public function getOnlineBan()
    {
        $this->site->output->assign('servers', \Models\Server::query()->select());
        if (Path::getFakePathWay(2)) {
            $this->site->output->assign('selected', \Models\Server::find(Path::getFakePathWay(2)));
        } else {
            $this->site->output->assign('selected', new \Models\Server);
        }
        $this->site->output->display('admin.index.online_ban.tpl');
    }

    public function ajaxServerPlayers($server) // TODO: Must ask for some active server info (rcon)
    {
        $server = Server::find($server);
        [$ip, $port] = explode(':', $server->address);
        try {
            $live = new \Rcon($ip, $port, $server->rcon);
            $live = $live->serverInfo();
            $out  = [
                'success' => true,
                'info'    => $live,
            ];
        } catch (\Exception $e) {
            $out = [
                'success' => false,
                'message' => $e->getMessage(),
            ];
        }

        header('Content-Type: application/json');
        echo json_encode($out);
    }

}