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

namespace Controllers;

use Models\Ban;
use Support\BaseController;

/**
 * Class LoginController
 */
class LoginController extends BaseController
{
    private function getLogin()
    {
        if (Route::getFakePathWay(1) == 'pass_rec') {
            return $this->getPassRec();
        }

        $remaining = @$_SESSION['login_block'] ? time() - $_SESSION['login_block'] : null;
        $this->site->output->assign('blocked', $remaining);

        $this->site->output->display($this->site->getTplFile());
    }

    private function postLogin()
    {
        if (Route::getFakePathWay(1) == 'pass_rec') {
            return $this->postPassRec();
        }
    }

    private function postPassRec()
    {
        if ($this->site->validateFormAuth()) {
            $d = $this->site->config->getDb();
            $user = $d->prepare("SELECT id, username, passreset_code as code, passreset_until as until FROM {$this->site->config->getDb()->prefix}_webadmins WHERE email=?");
            $user->execute([trim($_POST['email'])]);

            if ($user->rowCount() == 1) {
                $t = new DateTime();
                $user = $user->fetchObject();
                if ($user->code && (new DateTime($user->until) > $t)) {
                    $msg[] = ['type' => 'warning', 'text' => __LANG__['index']['login']['passcode_exist']];
                } else {
                    $code = md5($user->id . $user->username . $t->format('U'));
                    db_log('Password Recovery', 'Unset password', $user->username);
                    $q = $d->prepare("UPDATE `{$this->site->config->getDb()->prefix}_webadmins` SET passreset_code=?, passreset_until=? WHERE id=?");
                    $q->execute([$code, (new DateTime('+1 day'))->format('Y-m-d H:i:s'), $user->id]);

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

    private function getPassRec()
    {
        if (isset($_GET['code'])) {
            if ($this->passwordRecovery(trim($_GET['code']))) {
                return;
            }
            return $this->site->config->output->append('messages', [
                'type' => 'warning',
                'text' => __LANG__['index']['login']['passreset_nocode'],
            ])
                ->display('index.login.pass_rec.tpl');
        }

        $this->site->config->output->display('index.login.lost_pass.tpl');
    }

    protected function passwordRecovery(string $code = null, $pw = null)
    {
        if ($code) {
            $d = $this->site->config->getDb();
            $u = $d->prepare("SELECT id, passreset_until as until, username, email FROM `{$this->site->config->getDb()->prefix}_webadmins` WHERE passreset_code=?");
            $u->execute([$code]);

            if ($u->rowCount() == 1) {
                $u = $u->fetchObject();
                $t = new DateTime();

                if ($t < new DateTime($u->until)) {
                    if ($pw) {
                        $q = $d->prepare("UPDATE `{$this->site->config->getDb()->prefix}_webadmins` SET passreset_until=null, passreset_code=null, try=0, password=? WHERE id=?");
                        $q->execute([password_hash($pw, PASSWORD_DEFAULT), $u->id]);
                    }
                    $this->site->config->output->append('messages', [
                        'type' => 'success',
                        'text' => __LANG__['index']['login']['pass'],
                    ])->display();
                    $this->site->config->output->display('index.login.pass_change.tpl');
                    return true;
                }
            }
        }
        return false;
    }

    private function putLogin()
    {
        if ($this->site->validateFormAuth() && isset($_GET['code'])) {
            $err = new FormErrors($_POST, __LANG__['validation_errors']);
            $err->validate([
                __LANG__['index']['login']['pass']        => 'required',
                __LANG__['index']['login']['pass'] . '_2' => 'required|same:' . __LANG__['index']['login']['pass'],
            ]);
            if ($this->passwordRecovery(trim($_GET['code']), $_POST['pw'])) {
                return;
            }
        }
    }
}