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
//TODO: Move controllers to Controllers directory
use Models\Ban;

/**
 * Class IndexController
 */
class IndexController
{
    private $section;
    private $method;
    protected $site;

    /**
     * IndexController constructor.
     *
     * @param Site   $site
     * @param string $method
     * @param string $section
     *
     * @throws Exception
     */
    public function __construct (Site $site, string $method, string $section) {
        $this->site = $site;
        $this->method = $method;
        $this->section = $section;

        // If there's any extra action needed, it has to be placed here for all the 'index' sites


        $m = $method . ucfirst($section);
        if (method_exists($this, $m))
            $this->$m();
        else
            throw new Exception('Method "' . $m . '" not found');
    }

    private function getLogin () {
        if (Route::getFakePathWay(1) == 'pass_rec')
            return $this->getPassRec();

        $remaining = @$_SESSION['login_block'] ? time() - $_SESSION['login_block'] : NULL;
        $this->site->output->assign('blocked', $remaining);

        $this->site->output->display($this->site->getTplFile());
    }

    private function postLogin () {
        if (Route::getFakePathWay(1) == 'pass_rec')
            return $this->postPassRec();
    }

    private function postPassRec () {
        if ($this->site->validateFormAuth()) {
            $d = $this->site->config->getDb();
            $user = $d->prepare("SELECT id, username, passreset_code as code, passreset_until as until FROM {$this->site->config->getDb()->prefix}_webadmins WHERE email=?");
            $user->execute([ trim($_POST['email']) ]);

            if ($user->rowCount() == 1) {
                $t = new DateTime();
                $user = $user->fetchObject();
                if ($user->code && (new DateTime($user->until) > $t))
                    $msg[] = [ 'type' => 'warning', 'text' => __LANG__['index']['login']['passcode_exist'] ];
                else {
                    $code = md5($user->id . $user->username . $t->format('U'));
                    db_log('Password Recovery', 'Unset password', $user->username);
                    $q = $d->prepare("UPDATE `{$this->site->config->getDb()->prefix}_webadmins` SET passreset_code=?, passreset_until=? WHERE id=?");
                    $q->execute([ $code, (new DateTime('+1 day'))->format('Y-m-d H:i:s'), $user->id ]);

                    $msg = new Templating($this->site->config);
                    $msg->assign('replace', [
                        ':username' => $user->username,
                        ':now'      => $t->format(__LANG__['date_format']),
                    ]);
                    $msg->assign('code', $code);

                    $mail_headers = [
                        'From'         => $_SERVER['SERVER_ADMIN'],
                        'MIME-Version' => '1.0',
                        'Content-type' => 'text/html; charset=utf-8',
                        'To'           => $user->username . '<' . trim($_POST['email']) . '>',
                    ];
                    $mail = Smarty::$_MBSTRING ? 'mb_send_mail' : 'mail';
                    $mail(trim($_POST['email']), __LANG__['email']['subject'], $msg->fetch('email.tpl'), $mail_headers);
                    $msg[] = [
                        'type' => 'info',
                        'text' => str_replace(':email', $_POST['email'], __LANG__['index']['login']['passcode_sent']),
                    ];
                }
            }
        }

    }

    private function getPassRec () {
        if (isset($_GET['code'])) {
            if ($this->passwordRecovery(trim($_GET['code'])))
                return;
            return $this->site->config->output->append('messages', [
                'type' => 'warning',
                'text' => __LANG__['index']['login']['passreset_nocode'],
            ])
                                                ->display('index.login.pass_rec.tpl');
        }

        $this->site->config->output->display('index.login.lost_pass.tpl');
    }

    protected function passwordRecovery (string $code = NULL, $pw = NULL) {
        if ($code) {
            $d = $this->site->config->getDb();
            $u = $d->prepare("SELECT id, passreset_until as until, username, email FROM `{$this->site->config->getDb()->prefix}_webadmins` WHERE passreset_code=?");
            $u->execute([ $code ]);

            if ($u->rowCount() == 1) {
                $u = $u->fetchObject();
                $t = new DateTime();

                if ($t < new DateTime($u->until)) {
                    if ($pw) {
                        $q = $d->prepare("UPDATE `{$this->site->config->getDb()->prefix}_webadmins` SET passreset_until=null, passreset_code=null, try=0, password=? WHERE id=?");
                        $q->execute([ password_hash($pw, PASSWORD_DEFAULT), $u->id ]);
                    }
                    $this->site->config->output->append('messages', [
                        'type' => 'success',
                        'text' => __LANG__['index']['login']['pass'],
                    ])->display();
                    $this->site->config->output->display('index.login.pass_change.tpl');
                    return TRUE;
                }
            }
        }
        return FALSE;
    }

    private function putLogin () {
        if ($this->site->validateFormAuth() && isset($_GET['code'])) {
            $err = new FormErrors($_POST, __LANG__['validation_errors']);
            $err->validate([
                __LANG__['index']['login']['pass']        => 'required',
                __LANG__['index']['login']['pass'] . '_2' => 'required|same:' . __LANG__['index']['login']['pass'],
            ]);
            if ($this->passwordRecovery(trim($_GET['code']), $_POST['pw']))
                return;
        }
    }

    private function getBans () {
        $page = (int)(Route::getFakePathWay(1) ?? 0);
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
            $comments = $comments->fetchAll(PDO::FETCH_GROUP|PDO::FETCH_COLUMN, 1);
        }

        $files = $this->site->config->getDb()
                                      ->prepare("SELECT id, bid FROM `{$this->site->config->getDb()->prefix}_comments` WHERE file IS NOT NULL");
        $files->execute();
        $files = $files->fetchAll(PDO::FETCH_GROUP|PDO::FETCH_COLUMN, 1);

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
            if ($this->site->config->bans_show_comments)
                $b['comment_count'] = isset($comments[$ban->bid]) ? count($comments[$ban->bid]) : 0;

            $banned[] = $b;
        }
        $this->site->output->assign([
            'page'      => $page + 1,
            'page_prev' => !($page < 1),
            'page_next' => count($bans) == $this->site->config->per_page,
            'bans'      => $banned ?? [],
        ]);
        $this->site->output->display($this->site->getTplFile());
    }

    private function getBan () {
        if (!Route::getFakePathWay(1))
            return header('HTTP/1.1 404');
        if (Route::getFakePathWay(2)) {
            return $this->editBan();
        }

        $ban = Ban::with(['server', 'admin'])->find(1);
        $ban = $this->site->config->getDb()
                                    ->prepare("SELECT b.*, s.gametype, s.timezone_fixx, a.nickname,a.username FROM ((`{$this->site->config->getDb()->prefix}_bans` b
    LEFT JOIN `{$this->site->config->getDb()->prefix}_serverinfo` s ON b.server_ip = s.address)
    LEFT JOIN `{$this->site->config->getDb()->prefix}_amxadmins` a ON (a.steamid = b.admin_nick OR a.steamid = admin_ip OR a.steamid = b.admin_id))
    WHERE bid=" . (int)Route::getFakePathWay(1));
        $ban->execute();
        if ($ban->rowCount() != 1)
            die(header('HTTP/1.1 404'));

        $ban = $ban->fetch(PDO::FETCH_ASSOC);
        $ban['ban_created'] = $ban['ban_created'] + ($ban['timezone_fixx'] * 3600);
        $ban['expired'] = ($ban['ban_length'] > 0 && ($ban['ban_created'] + ($ban['ban_length'] * 60)) < time());
        $ban['com_id'] = $ban['player_id']? GetFriendID($ban['player_id']) : FALSE;

        $comments = $this->site->config->getDb()->prepare('');


        $this->site->output->assign('ban', $ban);
        $this->site->output->assign('can_user', [
            'edit_own_bans'   => Auth::hasPermission('bans_edit') || Auth::hasPermission('bans_edit', 2),
            'edit_bans'       => Auth::hasPermission('bans_edit', 2),
            'delete_own_bans' => Auth::hasPermission('bans_delete') || Auth::hasPermission('bans_delete', 2),
            'delete_bans'     => Auth::hasPermission('bans_delete', 2),
            'unban_own'      => Auth::hasPermission('bans_unban') || Auth::hasPermission('bans_unban', 2),
            'unban'           => Auth::hasPermission('bans_unban', 2),
            'view_admins'     => Auth::hasPermission('amxadmins_view'),
            'view_ips'        => Auth::hasPermission('ip_view'),
            'write_comments'  => $this->site->config->allow_unregistered_comments || Auth::get(),
            'nocaptca'        => Auth::$logged,
        ]);
        $this->site->output->assign('comments', $comments);

        Captcha::generateCode();
        $this->site->output->display('index.ban.tpl');
    }


}