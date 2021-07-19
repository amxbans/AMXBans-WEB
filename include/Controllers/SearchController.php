<?php
/**
 *    AMXBans v7
 * Copyright 2020 by indianiso1, SeToY & |PJ|ShOrTy
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

/**  */

namespace Controllers;

use Lang;
use Models\Ban;
use PDO;
use Support\BaseController;
use Support\DB;

/**
 * Class SearchController
 *
 * @package Controllers
 */
class SearchController extends BaseController
{
    public function index()
    {
        $db      = $this->site->config->getDb();
        $servers = $db->prepare("SELECT `server_ip`,`server_name` FROM `{$db->prefix}_bans` GROUP BY `server_ip` ORDER BY `server_name`");
        $servers->execute();
        $servers = $servers->fetch(PDO::FETCH_KEY_PAIR);
        $this->site->output->assign([
            'amxadmins' => Ban::query()->select(['admin_id', 'admin_nick']),
            'servers'   => $servers,
        ]);
        return $this->site->output->display('index.search.tpl');
    }

    public function store()
    {
        if (!$this->site->validateFormAuth()) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => Lang::get('invalidCSRF')]);
            return $this->index();
        }
        if (empty($_POST['search'])
            || $_POST['search'] == 'text' && empty($_POST['text'])
            || $_POST['search'] == 'date' && empty($_POST['date'])
            || $_POST['search'] == 'ban_count' && empty($_POST['ban_count'])
            || $_POST['search'] == 'admin' && empty($_POST['admin'])
            || $_POST['search'] == 'server' && empty($_POST['server'])) {
            return $this->index();
        }

        $db  = new DB();
        $pdo = $this->site->config->getDb();
        if ($_POST['search'] == 'text') {
            if ($_POST['text'] == 'name') {
                $bans = Ban::query()->where('player_nick', $_POST['value'])->limit(100)->orderBy('ban_created', true)
                    ->select();
            } elseif ($_POST['text'] == 'steamid') {
                $bans = Ban::query()->where('player_id', $_POST['value'])->limit(100)->orderBy('ban_created', true)
                    ->select();
            } elseif ($_POST['text'] == 'ip') {
                $bans = Ban::query()->where('player_ip', $_POST['value'])->limit(100)->orderBy('ban_created', true)
                    ->select();
            } elseif ($_POST['text'] == 'reason') {
                $bans = Ban::query()->where('ban_reason', $_POST['value'])->limit(100)->orderBy('ban_created', true)
                    ->select();
            }
        } elseif ($_POST['search'] == 'date') {
            $bans = $db::selectRaw("SELECT * FROM `{$pdo->prefix}_bans` WHERE FROM_UNIXTIME(ban_created, %d%m%Y) LIKE ? ORDER BY ban_created",
                [$_POST['date']], Ban::class);
        } elseif ($_POST['search'] == 'ban_count') {
            $valid = $db::selectRaw("SELECT player_id, COUNT(bid) as ban_count FROM `{$pdo->prefix}_bans` GROUP BY player_id, ban_created HAVING COUNT(bid) >= ? ORDER BY ban_created DESC,player_id",
                [(int)$_POST['ban_count']]);
            foreach ($valid as $item) {
                if (!$item->player_id) {
                    continue;
                }
                $ban               = Ban::query()->orderBy('ban_created')->where('player_id', $item->player_id)
                    ->where('expired', false)->selectOne();
                $ban->times_banned = $item->ban_count;
                $bans[]            = $ban;
            }
        } elseif ($_POST['search'] == 'admin') {
            $bans = Ban::query()->where('admin_id', $_POST['admin'])->orderBy('ban_created', true)->limit(100)
                ->select();
        } elseif ($_POST['search'] == 'server') {
            $bans = Ban::query()->where('server_ip', $_POST['server'])->orderBy('ban_created', true)->limit(100)
                ->select();
        }

        $this->site->output->assign('bans', $bans ?? []);
        $this->site->output->assign('ban_count', isset($valid));
        return $this->index();
    }
}