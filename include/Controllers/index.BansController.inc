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
use Models\BansLog;
use Models\Comment;
use PDO;
use Support\BaseController;
use Steam;
use Support\Path;

/**
 * Class BansController
 */
class BansController extends BaseController
{
    public function index()
    {
        $page   = (int)($_GET['page'] ?? 0);
        $page   = $page < 1 ? 0 : $page - 1;
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
            $comments = $comments->fetchAll(PDO::FETCH_GROUP|PDO::FETCH_COLUMN, 1);
        }

        $files = $this->site->config->getDb()
                                    ->prepare("SELECT id, bid FROM `{$this->site->config->getDb()->prefix}_comments` WHERE file IS NOT NULL");
        $files->execute();
        $files = $files->fetchAll(PDO::FETCH_GROUP|PDO::FETCH_COLUMN, 1);

        $bans = $bans->fetchAll(PDO::FETCH_OBJ);
        foreach ($bans as $ban) {
            $b['id']         = $ban->bid;
            $b['player']     = $ban->player_nick;
            $b['admin']      = $ban->admin_nick;
            $b['reason']     = $ban->ban_reason;
            $b['length']     = $ban->ban_length;
            $b['kick_count'] = $ban->ban_kicks;
            $b['created']    = $ban->ban_created + ($ban->timezone_fixx * 60 * 60);
            $b['ended']      = ($ban->ban_length > 0 && ($ban->ban_created + ($ban->ban_length * 60) + ($ban->timezone_fixx * 60 * 60)) < time());
            $b['type']       = $ban->gametype ?: 'website';
            $b['file_count'] = isset($files[$ban->bid]) ? count($files[$ban->bid]) : 0;

            $same           = array_filter($bans, function ($value) use ($ban) {
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
        if (!$ban->exists) {
            die(header('HTTP/2.0 404 Not Found'));
        }
        $ban->ban_created = $ban->ban_created + $ban->server->timezone_fixx * 3600;
        $ban->expired     = ($ban->ban_length > 0 && ($ban->ban_created + ($ban->ban_length * 60)) < time());
        $ban->com_id      = $ban->player_id ? Steam::GetFriendID($ban->player_id) : false;

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
        $this->site->output->display('index.ban.tpl');
    }

    public function edit($id)
    {
        if (!($ban = $this->recoverBan($id, 'bans_edit'))) {
            exit;
        }

        $this->site->output->assign('ban', $ban);
        $this->site->output->assign('can_user', [
            'view_ips' => Auth::hasPermission('ip_view'),
        ]);
        $this->site->output->display('index.ban.edit.tpl');
    }

    public function update($id)
    {
        if (!$this->site->validateFormAuth()) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => __LANG__['invalidCSRF']]);
            return $this->edit($id);
        }
        if (!($ban = $this->recoverBan($id, 'bans_edit'))) {
            exit;
        }

        $errors = new \FormErrors($_POST, __LANG__['validation_errors']);
        $errors->validate([
            'player_nick' => 'required|max:31',
            'player_id'   => 'steamid',
            'edit_reason' => 'required|max:250',
        ]);
        if (Auth::hasPermission('ip_view')) {
            $errors->validate(['player_ip' => 'ip']);
            $ban->player_ip = $_POST['player_ip'];
        }

        //Ban length must be the same, permanent (0) or later than now (created+length)
        if ($_POST['ban_length'] != 0 && $_POST['ban_length'] != $ban->ban_length && $ban->ban_created + $_POST['ban_length'] * 60 < time()) {
            $errors->addValidationError('ban_length', 'later');
        }
        if ($errors->has()) {
            $this->site->output->assign('messages', $errors);
            return $this->edit($id);
        }

        db_log('Ban edit', 'Edit ID ' . $ban->bid . ' (' . $ban->player_nick . ' <' . $ban->player_id . '>)');
        $ban->player_nick = $_POST['player_nick'];
        $ban->player_id   = $_POST['player_id'];
        $ban->ban_type    = in_array($_POST['ban_type'], __LANG__['index']['ban']['types']) ? $_POST['ban_type'] : '';
        $ban->ban_reason  = $_POST['ban_reason'];
        $ban->save();

        $bl              = new BansLog();
        $bl->admin_nick  = Auth::get('username');
        $bl->bid         = $ban->bid;
        $bl->edit_reason = $_POST['edit_reason'];
        $bl->created_at  = new \DateTime();
        $bl->save();

        $this->site->output->assign('message', __LANG__['admin']['saved']);
        return $this->edit($id);
    }

    public function delete($id)
    {
        if (!($ban = $this->recoverBan($id, 'bans_delete'))) {
            exit;
        }

        $comms = Comment::query(Comment::FILES)->where('bid', $id)->select('file');
        foreach ($comms ?? [] as $comment) {
            unlink($comment->file);
        }
        Comment::query()->where('bid', $id)->delete();
        Ban::query()->where('bid', $id)->delete();
        db_log('Ban edit', 'Delete ID ' . $ban->bid . ' (' . $ban->player_nick . ' <' . $ban->player_id . '>)');
        $this->site->output->assign('message', __LANG__['admin']['deleted']);
        return $this->index();
    }

    public function unban($id)
    {
        if (!($ban = $this->recoverBan($id, 'bans_unban'))) {
            return;
        }

        $ban->expired    = true;
        $ban->ban_length = -1;
        $ban->save();
        db_log('Ban edit', 'Unban ID ' . $ban->bid . ' (' . $ban->player_nick . ' <' . $ban->player_id . '>)');
        return $this->view($id);
    }

    /**
     * Form validation and comment creation on new ban comment submission.
     *
     * @param $id Ban ID to save comment under
     */
    public function comment($id)
    {
        if (!$this->site->validateFormAuth()) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => __LANG__['invalidCSRF']]);
            return $this->view($id);
        }
        if (!$this->site->config->allow_unregistered_comments && !Auth::$logged) {
            $this->site->output->assign('message', __LANG__['index']['ban']['no_commenting']);
            return $this->view($id);
        }

        $errorChecker = new \FormErrors($_POST, __LANG__['validation_errors']);
        $errorChecker->validate([
            'comment' => 'required|max:65535',
        ]);
        if (!Auth::$logged) {
            $errorChecker->validate([
                'name'    => 'required|max:100',
                'email'   => 'required|email',
                'captcha' => 'required|captcha',
            ]);
        }

        if ($errorChecker->has()) {
            $this->site->output->assign('messages', $errorChecker);
            return $this->view($id);
        }

        if (isset($_FILES['file']) && $_FILES['file']['error'] != UPLOAD_ERR_NO_FILE) {
            $file = $_FILES['file'];
            if ($file['error'] == UPLOAD_ERR_INI_SIZE || $file['error'] == UPLOAD_ERR_FORM_SIZE || $file['size'] > $this->site->config->uploaded_file_size) {
                $this->site->output->assign('message',
                    ['type' => 'warning', 'text' => __LANG__['index']['ban']['file_too_big']]);
                return $this->view($id);
            }

            if ($file['error'] != UPLOAD_ERR_OK) {
                $this->site->output->assign('message',
                    ['type' => 'warning', 'text' => __LANG__['index']['ban']['file_not_uploaded']]);
                return $this->view($id);
            }

            $extension = strtolower(pathinfo($file["name"], PATHINFO_EXTENSION));
            if (!in_array($extension, $this->site->config->uploaded_file_types)) {
                $this->site->output->assign('message',
                    ['type' => 'warning', 'text' => __LANG__['index']['ban']['file_not_type']]);
                return $this->view($id);
            }


            $newName = 'webSources/uploads/' . date('Ymd_His-') . rand(0, 9) . '.' . $extension;
            move_uploaded_file($file['tmp_name'], Path::getRootPath() . '/' . $newName);
        }


        $comment           = new Comment();
        $comment->file     = $newName ?? null;
        $comment->comment  = $_POST['comment'];
        $comment->name     = $_POST['name'] ?: Auth::get('username');
        $comment->email    = $_POST['email'] ?: Auth::get('email');
        $comment->addr     = $_SERVER['REMOTE_ADDR'];
        $comment->bid      = $id;
        $comment->admin_id = Auth::get() ?: null;
        $comment->save();

        $this->site->output->assign('message', __LANG__['index']['ban']['comment_saved']);
        return header('Location: ' . Path::makeURL('bans/' . $id));
    }

    /**
     * Checks permission and returns model if all ok, false otherwise.
     *
     * @param $id
     * @param $permission
     *
     * @return bool|Ban
     */
    private function recoverBan($id, $permission)
    {

        if (!Auth::hasPermission($permission) && !Auth::hasPermission($permission, 2)) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => __LANG__['admin']['no_access']]);
            $this->view($id);
            return false;
        }

        $ban = Ban::find($id);
        if (!$ban->exists) {
            die(header('HTTP/2.0 404 Not Found'));
        }

        if (Auth::get('username') != $ban->admin_nick && !Auth::hasPermission($permission, 2)) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => __LANG__['admin']['no_access']]);
            $this->view($id);
            return false;
        }

        return $ban;
    }
}