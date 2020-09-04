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
use Support\Path;
use Templating;

/**
 * Class LoginController
 */
class LoginController extends BaseController
{
    /**
     * Blockage time (in seconds) at reaching max tries.
     */
    private $blockTime = 600;

    /**
     * Shows initial login form
     *
     * @throws \SmartyException
     */
    public function index()
    {
        $remaining = @$_SESSION['login_block'] ? time() - $_SESSION['login_block'] : null;
        $this->site->output->assign('blocked', $remaining);

        $this->site->output->display('index.login.tpl');
    }

    /**
     * Process submitted login info
     *
     * @throws \SmartyException
     * @throws \Exception
     */
    public function store()
    {
        if (!$this->site->validateFormAuth()) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => \Lang::get('invalidCSRF')]);
            return $this->index();
        }
        if ($this->isLoginBlocked()) {
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => \Lang::get('login_blocked')]);
            return $this->index();
        }
        /** @var WebAdmin $user */
        $user = WebAdmin::query()->where('username', $_POST['username'])->selectOne();
        if (!$user->exists) {
            $this->addLoginTry();
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => \Lang::get('err_no_user')]);
            return $this->index();
        }
        if ($this->isLoginBlocked($user)) {
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => \Lang::get('login_blocked')]);
            return $this->index();
        }
        if (!password_verify($_POST['password'], $user->password)) {
            db_log('Login', 'Attempt: wrong password', $user->username);
            $this->addLoginTry($user);
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => \Lang::get('err_wrong_pass')]);
        }

        $this->site->user->login($user, isset($_POST['rem']));
            $user->last_action = new DateTime();
            $user->passreset_code = null;
            $user->passreset_until = null;
            $user->save();
            header('Location: ' . Path::makeURL('index/sys_info', 'admin.php'));
            return true;
    }

    /**
     * Shows the form for password recovery request
     *
     * @throws \SmartyException
     */
    public function lostPassForm()
    {
        $this->site->output->display('index.login.lost_pass');
    }

    /**
     * Checks user existence and sends email for password recovery request
     *
     * @throws \SmartyException
     * @throws \Exception
     */
    public function lostPassSend()
    {
        if (!$this->site->validateFormAuth()) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => \Lang::get('invalidCSRF')]);
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
                ['type' => 'warning', 'text' => \Lang::get('err_no_user_email')]);
            $this->site->output->display('index.login.lost_pass');
            return;
        }
        if ($user->passreset_code && ($user->passreset_until > $t)) {
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => \Lang::get('passcode_exist')]);
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
            ':now'      => $t->format(\Lang::$properties['date_format']),
        ]);
        $msg->assign('code', $code);

        $mail_headers = [
            'From'         => $_SERVER['SERVER_ADMIN'],
            'MIME-Version' => '1.0',
            'Content-type' => 'text/html; charset=utf-8',
        ];
        $mail         = Templating::$_MBSTRING ? 'mb_send_mail' : 'mail';
        $mail($user->username . '<' . trim($_POST['email']) . '>', \Lang::get('lost_pass_email')['subject'],
            $msg->fetch('email.tpl'), $mail_headers);
        $this->site->output->assign('message',
            str_replace(':email', $_POST['email'], \Lang::get('passcode_sent')));

        $this->site->output->display('index.login.lost_pass');
        return;
    }

    /**
     * Shows the form for password change @ password recovery
     *
     * @param $code
     * @throws \SmartyException
     */
    public function passwordRecovery($code)
    {
        if (!$this->checkCode($code, $user)) {
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => \Lang::get('passreset_nocode')]);
            return $this->index();
        }
        return $this->site->output->display('index.login.pass_change.tpl');
    }

    /**
     * Submitted form for password change @ password recovery
     *
     * @param $code
     * @throws \SmartyException
     */
    public function updatePassword($code)
    {
        if (!$this->checkCode($code, $user)) {
            $this->site->output->assign('message',
                ['type' => 'warning', 'text' => \Lang::get('passreset_nocode')]);
            return $this->index();
        }

        if (!$this->site->validateFormAuth()) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => \Lang::get('invalidCSRF')]);
            return $this->site->output->display('index.login.pass_change.tpl');
        }

        $err = new FormErrors($_POST, \Lang::get('validation_errors'));
        $err->validate([
            \Lang::get('password')        => 'required',
            \Lang::get('password') . '_2' => 'required|same:' . \Lang::get('password'),
        ]);
        if ($err->has()) {
            $this->site->output->assign('messages', $err);
            return $this->site->output->display('index.login.pass_change.tpl');
        }

        /** @var WebAdmin $user */
        $user->password        = password_hash($_POST[\Lang::get('password')], PASSWORD_DEFAULT);
        $user->passreset_until = null;
        $user->passreset_code  = null;
        $user->save();

        $_SESSION['login_try'] = 0;
        $_SESSION['login_block'] = 0;

        $this->site->output->assign('message',
            ['type' => 'success', 'text' => \Lang::get('pass_changed')]);
        return $this->index();
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

    private function isLoginBlocked(WebAdmin $webAdmin = null): bool
    {
        $_SESSION['login_try'] = $_SESSION['login_try'] ?? ($webAdmin ? $webAdmin->try : 0);
        if ($_SESSION['login_try'] >= $this->site->config->max_login_tries) {
            $left = $webAdmin ? $webAdmin->last_action->getTimestamp() + $this->blockTime : ($_SESSION['login_block'] ?? 0);
            if ($left < time()) {
                return false;
            }
            return true;
        }
        return false;
    }

    /**
     * @param WebAdmin|null $toUser
     * @throws \Exception
     */
    private function addLoginTry(WebAdmin $toUser = null)
    {
        $_SESSION['login_try']++;
        if ($toUser) {
            $toUser->try         += 1;
            $toUser->last_action = new DateTime();
            $toUser = $toUser->save();
        }

        if ($this->isLoginBlocked($toUser)) {
            $_SESSION['login_block'] = time() + 600;
            db_log('Login', 'Attempt: blocked (too many tries)', $toUser? $toUser->username : $_POST['username']);
        }
    }
}