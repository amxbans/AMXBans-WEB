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
    private $site;
    private $method;
    protected $config;

    /**
     * IndexController constructor.
     *
     * @param Site   $config
     * @param string $method
     * @param string $site
     *
     * @throws Exception
     */
    public function __construct (Site $config, string $method, string $site) {
        $this->config = $config;
        $this->method = $method;
        $this->site = $site;

        // If there's any extra action needed, it has to be placed here for all the 'index' sites


        $m = $method . ucfirst($site);
        if (method_exists($this, $m))
            $this->$m();
        else
            throw new Exception('Method "' . $m . '" not found');
    }

    private function getLogin () {
        if (Route::getFakePathWay(1) == 'pass_rec')
            return $this->getPassRec();

        $remaining = @$_SESSION['login_block'] ? time() - $_SESSION['login_block'] : NULL;
        $this->config->config->output->assign('blocked', $remaining);

        $this->config->config->output->display($this->config->getTplFile());
    }

    private function postLogin () {
        if (Route::getFakePathWay(1) == 'pass_rec')
            return $this->postPassRec();
    }

    private function postPassRec () {
        if ($this->config->validateFormAuth()) {
            $d = $this->config->config->getDb();
            $user = $d->prepare("SELECT id, username, passreset_code as code, passreset_until as until FROM {$this->config->config->dbPrefix}_webadmins WHERE email=?");
            $user->execute([ trim($_POST['email']) ]);

            if ($user->rowCount() == 1) {
                $t = new DateTime();
                $user = $user->fetchObject();
                if ($user->code && (new DateTime($user->until) > $t))
                    $msg[] = [ 'type' => 'warning', 'text' => __LANG__['index']['login']['passcode_exist'] ];
                else {
                    $code = md5($user->id . $user->username . $t->format('U'));
                    db_log('Password Recovery', 'Unset password', $user->username);
                    $q = $d->prepare("UPDATE `{$this->config->config->dbPrefix}_webadmins` SET passreset_code=?, passreset_until=? WHERE id=?");
                    $q->execute([ $code, (new DateTime('+1 day'))->format('Y-m-d H:i:s'), $user->id ]);

                    $msg = new Templating($this->config->config);
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
            return $this->config->config->output->append('messages', [
                'type' => 'warning',
                'text' => __LANG__['index']['login']['passreset_nocode'],
            ])
                                                ->display('index.login.pass_rec.tpl');
        }

        $this->config->config->output->display('index.login.lost_pass.tpl');
    }

    protected function passwordRecovery (string $code = NULL, $pw = NULL) {
        if ($code) {
            $d = $this->config->config->getDb();
            $u = $d->prepare("SELECT id, passreset_until as until, username, email FROM `{$this->config->config->dbPrefix}_webadmins` WHERE passreset_code=?");
            $u->execute([ $code ]);

            if ($u->rowCount() == 1) {
                $u = $u->fetchObject();
                $t = new DateTime();

                if ($t < new DateTime($u->until)) {
                    if ($pw) {
                        $q = $d->prepare("UPDATE `{$this->config->config->dbPrefix}_webadmins` SET passreset_until=null, passreset_code=null, try=0, password=? WHERE id=?");
                        $q->execute([ password_hash($pw, PASSWORD_DEFAULT), $u->id ]);
                    }
                    $this->config->config->output->append('messages', [
                        'type' => 'success',
                        'text' => __LANG__['index']['login']['pass'],
                    ])->display();
                    $this->config->config->output->display('index.login.pass_change.tpl');
                    return TRUE;
                }
            }
        }
        return FALSE;
    }

    private function putLogin () {
        if ($this->config->validateFormAuth() && isset($_GET['code'])) {
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
        $offset = $page * $this->config->config->per_page;
        $offset = $offset ? $offset - 1 : 0;

        $bans = $this->config->config->getDb()->prepare("SELECT b.*, s.gametype, s.timezone_fixx, a.nickname  FROM ((`{$this->config->config->dbPrefix}_bans` b 
                LEFT JOIN `{$this->config->config->dbPrefix}_serverinfo` s ON s.address = b.server_ip)
                LEFT JOIN `{$this->config->config->dbPrefix}_amxadmins` a ON (a.steamid = b.admin_nick OR a.steamid = b.admin_ip OR a.steamid = b.admin_id))
                WHERE b.expired != 1 ORDER BY b.ban_created LIMIT $offset," . $this->config->config->per_page);
        $bans->execute();

        if ($this->config->config->bans_show_comments) {
            $comments = $this->config->config->getDb()
                                             ->prepare("SELECT id, bid FROM `{$this->config->config->dbPrefix}_comments` WHERE comment IS NOT NULL");
            $comments->execute();
            $comments = $comments->fetchAll(PDO::FETCH_GROUP|PDO::FETCH_COLUMN, 1);
        }

        $files = $this->config->config->getDb()
                                      ->prepare("SELECT id, bid FROM `{$this->config->config->dbPrefix}_comments` WHERE file IS NOT NULL");
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
            if ($this->config->config->bans_show_comments)
                $b['comment_count'] = isset($comments[$ban->bid]) ? count($comments[$ban->bid]) : 0;

            $banned[] = $b;
        }
        $this->config->config->output->assign([
            'page'      => $page + 1,
            'page_prev' => !($page < 1),
            'page_next' => count($bans) == $this->config->config->per_page,
            'bans'      => $banned ?? [],
        ]);
        $this->config->config->output->display($this->config->getTplFile());
    }

    private function getBan () {
        if (!Route::getFakePathWay(1))
            return header('HTTP/1.1 404');
        if (Route::getFakePathWay(2)) {
            return $this->editBan();
        }
        $ban = $this->config->config->getDb()
                                    ->prepare("SELECT b.*, s.gametype, s.timezone_fixx, a.nickname,a.username FROM ((`{$this->config->config->dbPrefix}_bans` b
    LEFT JOIN `{$this->config->config->dbPrefix}_serverinfo` s ON b.server_ip = s.address)
    LEFT JOIN `{$this->config->config->dbPrefix}_amxadmins` a ON (a.steamid = b.admin_nick OR a.steamid = admin_ip OR a.steamid = b.admin_id))
    WHERE bid=" . (int)Route::getFakePathWay(1));
        $ban->execute();
        if ($ban->rowCount() != 1)
            die(header('HTTP/1.1 404'));

        $ban = $ban->fetch(PDO::FETCH_ASSOC);
        $ban['ban_created'] = $ban['ban_created'] + ($ban['timezone_fixx'] * 3600);
        $ban['expired'] = ($ban['ban_length'] > 0 && ($ban['ban_created'] + ($ban['ban_length'] * 60)) < time());
        $ban['com_id'] = $ban['player_id']? GetFriendID($ban['player_id']) : FALSE;

        $comments = $this->config->config->getDb()->prepare('');


        $this->config->config->output->assign('ban', $ban);
        $this->config->config->output->assign('can_user', [
            'edit_own_bans'   => User::hasPermission('bans_edit') || User::hasPermission('bans_edit', 2),
            'edit_bans'       => User::hasPermission('bans_edit', 2),
            'delete_own_bans' => User::hasPermission('bans_delete') || User::hasPermission('bans_delete', 2),
            'delete_bans'     => User::hasPermission('bans_delete', 2),
            'unban_own'      => User::hasPermission('bans_unban') || User::hasPermission('bans_unban', 2),
            'unban'           => User::hasPermission('bans_unban', 2),
            'view_admins'     => User::hasPermission('amxadmins_view'),
            'view_ips'        => User::hasPermission('ip_view'),
            'write_comments'  => $this->config->config->allow_unregistered_comments || User::get(),
            'nocaptca'        => User::$logged,
        ]);
        $this->config->config->output->assign('comments', $comments);

        Captcha::generateCode();
        $this->config->config->output->display('index.ban.tpl');
    }


}