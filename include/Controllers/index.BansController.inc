<?php
/**
 *    AMXBans v7
 * Copyright 2019 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

/**  */

namespace Controllers;

use Auth;
use Captcha;
use Models\Ban;
use PDO;
use Support\BaseController;
use Steam;

/**
 * Class BansController
 */
class BansController extends BaseController
{
    public function index()
    {
        $page = (int)($_GET['page'] ?? 0);
        $page = $page < 1 ? 0 : $page - 1;
        $offset = $page * $this->site->config->per_page;
        $offset = $offset ? $offset - 1 : 0;

        $bans = $this->site->config->getDb()->prepare("SELECT b.*, s.gametype, s.timezone_fixx, a.nickname  FROM ((`{$this->site->config->getDb()->prefix}_bans` b 
                LEFT JOIN `{$this->site->config->getDb()->prefix}_serverinfo` s ON s.address = b.server_ip)
                LEFT JOIN `{$this->site->config->getDb()->prefix}_amxadmins` a ON (a.steamid = b.admin_nick OR a.steamid = b.admin_ip OR a.steamid = b.admin_id))
                WHERE b.expired != 1 ORDER BY b.ban_created LIMIT $offset," . $this->site->config->per_page);
        $bans->execute();

        if ($this->site->config->bans_show_comments) {
            $comments = $this->site->config->getDb()
                ->prepare("SELECT id, bid FROM `{$this->site->config->getDb()->prefix}_comments` WHERE comment IS NOT NULL");
            $comments->execute();
            $comments = $comments->fetchAll(PDO::FETCH_GROUP | PDO::FETCH_COLUMN, 1);
        }

        $files = $this->site->config->getDb()
            ->prepare("SELECT id, bid FROM `{$this->site->config->getDb()->prefix}_comments` WHERE file IS NOT NULL");
        $files->execute();
        $files = $files->fetchAll(PDO::FETCH_GROUP | PDO::FETCH_COLUMN, 1);

        $bans = $bans->fetchAll(PDO::FETCH_OBJ);
        foreach ($bans as $ban) {
            $b['id'] = $ban->bid;
            $b['player'] = $ban->player_nick;
            $b['admin'] = $ban->admin_nick;
            $b['reason'] = $ban->ban_reason;
            $b['length'] = $ban->ban_length;
            $b['kick_count'] = $ban->ban_kicks;
            $b['created'] = $ban->ban_created + ($ban->timezone_fixx * 60 * 60);
            $b['ended'] = ($ban->ban_length > 0 && ($ban->ban_created + ($ban->ban_length * 60) + ($ban->timezone_fixx * 60 * 60)) < time());
            $b['type'] = $ban->gametype ?: 'website';
            $b['file_count'] = isset($files[$ban->bid]) ? count($files[$ban->bid]) : 0;

            $same = array_filter($bans, function ($value) use ($ban) {
                return $value->player_id == $ban->player_id;
            });
            $b['ban_count'] = count($same);
            if ($this->site->config->bans_show_comments) {
                $b['comment_count'] = isset($comments[$ban->bid]) ? count($comments[$ban->bid]) : 0;
            }

            $banned[] = $b;
        }
        $this->site->output->assign([
            'page'      => $page + 1,
            'page_prev' => !($page < 1),
            'page_next' => count($bans) == $this->site->config->per_page,
            'bans'      => $banned ?? [],
        ]);
        return $this->site->output->display('index.bans');
    }

    public function view($id)
    {
        $ban = Ban::find($id);
        if (!$ban) {
            die(header('HTTP/1.1 404'));
        }
        $ban->ban_created = $ban->ban_created + $ban->server->timezone_fixx * 3600;
        $ban->expired = ($ban->ban_length > 0 && ($ban->ban_created + ($ban->ban_length * 60)) < time());
        $ban->com_id = $ban->player_id ? Steam::GetFriendID($ban->player_id) : false;

        $this->site->output->assign('ban', $ban);
        $this->site->output->assign('can_user', [
            'edit_own_bans'   => Auth::hasPermission('bans_edit') || Auth::hasPermission('bans_edit', 2),
            'edit_bans'       => Auth::hasPermission('bans_edit', 2),
            'delete_own_bans' => Auth::hasPermission('bans_delete') || Auth::hasPermission('bans_delete', 2),
            'delete_bans'     => Auth::hasPermission('bans_delete', 2),
            'unban_own'       => Auth::hasPermission('bans_unban') || Auth::hasPermission('bans_unban', 2),
            'unban'           => Auth::hasPermission('bans_unban', 2),
            'view_admins'     => Auth::hasPermission('amxadmins_view'),
            'view_ips'        => Auth::hasPermission('ip_view'),
            'write_comments'  => $this->site->config->allow_unregistered_comments || Auth::$logged,
            'nocaptca'        => Auth::$logged,
        ]);

        Captcha::generateCode();
        $this->site->output->display('index.ban');
    }

    public function edit($id)
    {
        //TODO: generate EDIT method
    }

    public function update($id)
    {
        //TODO: generate UPDATE method
    }

    public function delete($id)
    {
        //TODO: generate DELETE method
    }

    public function unban($id)
    {
        //TODO: generate UNBAN method
    }

    public function comment($id)
    {

        //TODO: generate COMMENT method
    }
}