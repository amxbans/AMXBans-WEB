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

use DateTime;
use FormErrors;
use Models\WebAdmin;
use Support\BaseController;
use Templating;

/**
 * Class LoginController
 */
class LoginController extends BaseController
{
    public function index()
    {
        $remaining = @$_SESSION['login_block'] ? time() - $_SESSION['login_block'] : null;
        $this->site->output->assign('blocked', $remaining);

        $this->site->output->display('index.login');
    }

    public function store()
    {
        // Logging in
        //TODO: Remove passreset_* fields if they are present
    }

    public function lostPassForm()
    {
        $this->site->output->display('index.login.lost_pass');
    }

    /**
     * @throws \SmartyException
     * @throws \Exception
     */
    public function lostPassSend()
    {
        if (!$this->site->validateFormAuth()) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => __LANG__['invalidCSRF']]);
            $this->site->output->display('index.login.lost_pass');
            return;
        }
        $t = new DateTime();
        /** @var WebAdmin $user */
        $user = WebAdmin::query()->where('email', trim($_POST['email']))->selectOne([
            'id',
            'username',
            'passreset_code',
            'passreset_until',
        ]);
        if (!$user->exists) {
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => __LANG__['index']['login']['err_no_user_email']]);
            $this->site->output->display('index.login.lost_pass');
            return;
        }
        if ($user->passreset_code && ($user->passreset_until > $t)) {
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => __LANG__['index']['login']['passcode_exist']]);
            $this->site->output->display('index.login.lost_pass');
            return;
        }
        $code = md5($user->id . $user->username . $t->format('U'));
        db_log('Login', 'Password recovery: get recovery code', $user->username);
        $user->passreset_code  = $code;
        $user->passreset_until = new $t('+1 day');
        $user->save();

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
        ];
        $mail         = Templating::$_MBSTRING ? 'mb_send_mail' : 'mail';
        $mail($user->username . '<' . trim($_POST['email']) . '>', __LANG__['email']['subject'], $msg->fetch('email.tpl'), $mail_headers);
        $this->site->output->assign('message',
            str_replace(':email', $_POST['email'], __LANG__['index']['login']['passcode_sent']));

        $this->site->output->display('index.login.lost_pass');
        return;
    }

    public function passwordRecovery($code)
    {
        if (!$this->checkCode($code, $user)) {
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => __LANG__['index']['login']['passreset_nocode']]);
            return $this->index();
        }
        return $this->site->output->display('index.login.pass_change.tpl');
    }

    public function updatePassword($code)
    {
        if (!$this->checkCode($code, $user)) {
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => __LANG__['index']['login']['passreset_nocode']]);
            return $this->index();
        }

        if (!$this->site->validateFormAuth()) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => __LANG__['invalidCSRF']]);
            return $this->site->output->display('index.login.pass_change.tpl');
        }

        $err = new FormErrors($_POST, __LANG__['validation_errors']);
        $err->validate([
            __LANG__['index']['login']['pass']        => 'required',
            __LANG__['index']['login']['pass'] . '_2' => 'required|same:' . __LANG__['index']['login']['pass'],
        ]);
        if ($err->has()) {
            $this->site->output->assign('messages', $err);
            return $this->site->output->display('index.login.pass_change.tpl');
        }

        /** @var WebAdmin $user */
        $user->password        = password_hash($_POST[__LANG__['index']['login']['pass']], PASSWORD_DEFAULT);
        $user->passreset_until = null;
        $user->passreset_code  = null;
        $user->save();

        $this->site->output->assign('message',
            ['type' => 'success', 'text' => __LANG__['index']['login']['pass_changed']]);
        return $this->site->output->display('index.login.tpl');
    }

    private function checkCode($code, &$user = null): bool
    {
        /** @var WebAdmin $user */
        $user = WebAdmin::query()->where('passreset_code', $code)->selectOne();
        if (!$user->exists) {
            return false;
        }
        if (new DateTime() > $user->passreset_until) {
            return false;
        }
        return true;
    }
}