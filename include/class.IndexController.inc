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
    public function __construct (Site $config, string $method, string $site)
    {
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

    private function getLogin ()
    {
        if (Route::getFakePathWay(1) == 'pass_rec')
            return $this->getPassRec();

        $remaining = @$_SESSION['login_block'] ? time() - $_SESSION['login_block'] : NULL;
        $this->config->config->output->assign('blocked', $remaining);

        $this->config->config->output->display($this->config->getTplFile());
    }

    private function postLogin ()
    {
        if (Route::getFakePathWay(1) == 'pass_rec')
            return $this->postPassRec();
    }

    private function postPassRec ()
    {
        if ($this->config->validateFormAuth()) {
            $d = $this->config->config->getDb();
            $user = $d->prepare("SELECT id, username, passreset_code as code, passreset_until as until FROM {$this->config->config->dbPrefix}_webadmins WHERE email=?");
            $user->execute([trim($_POST['email'])]);

            if ($user->rowCount() == 1) {
                $t = new DateTime();
                $user = $user->fetchObject();
                if ($user->code && (new DateTime($user->until) > $t))
                    $msg[] = ['type' => 'warning', 'text' => __LANG__['index']['login']['passcode_exist']];
                else {
                    $code = md5($user->id . $user->username . $t->format('U'));
                    db_log('Password Recovery', 'Unset password', $user->username);
                    $q = $d->prepare("UPDATE `{$this->config->config->dbPrefix}_webadmins` SET passreset_code=?, passreset_until=? WHERE id=?");
                    $q->execute([$code, (new DateTime('+1 day'))->format('Y-m-d H:i:s'), $user->id]);

                    $msg = new Templating($this->config->config);
                    $msg->assign('replace', [
                        ':username' => $user->username,
                        ':now' => $t->format(__LANG__['date_format']),
                    ]);
                    $msg->assign('code', $code);

                    $mail_headers = [
                        'From' => $_SERVER['SERVER_ADMIN'],
                        'MIME-Version' => '1.0',
                        'Content-type' => 'text/html; charset=utf-8',
                        'To' => $user->username . '<' . trim($_POST['email']) . '>',
                    ];
                    $mail = Smarty::$_MBSTRING ? 'mb_send_mail' : 'mail';
                    $mail(trim($_POST['email']), __LANG__['email']['subject'], $msg->fetch('email.tpl'), $mail_headers);
                    $msg[] = ['type' => 'info', 'text' => str_replace(':email', $_POST['email'], __LANG__['index']['login']['passcode_sent'])];
                }
            }
        }

    }

    private function getPassRec ()
    {
        if (isset($_GET['code'])) {
            if ($this->passwordRecovery(trim($_GET['code'])))
                return;
            $this->config->config->output->assign('messages', [['type' => 'warning', 'text' => __LANG__['login']['passreset_nocode']]]);
            return $this->config->config->output->display('index.login.pass_rec.tpl');
        }

        $this->config->config->output->display('index.login.lost_pass.tpl');
    }

    protected function passwordRecovery (string $code = null, $pw = NULL)
    {
        if ($code) {
            $d = $this->config->config->getDb();
            $u = $d->prepare("SELECT id, passreset_until as until, username, email FROM `{$this->config->config->dbPrefix}_webadmins` WHERE passreset_code=?");
            $u->execute([$code]);

            if ($u->rowCount() == 1) {
                $u = $u->fetchObject();
                $t = new DateTime();

                if ($t < new DateTime($u->until)) {
                    if ($pw) {
                        $q = $d->prepare("UPDATE `{$this->config->config->dbPrefix}_webadmins` SET passreset_until=null, passreset_code=null, try=0, password=? WHERE id=?");
                        $q->execute([password_hash($pw, PASSWORD_DEFAULT), $u->id]);
                    }
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
                __LANG__['index']['login']['pass'] => 'required',
                __LANG__['index']['login']['pass'] . '_2' => 'required|same:' . __LANG__['index']['login']['pass'],
            ]);
            if ($this->passwordRecovery(trim($_GET['code']), $_POST['pw']))
                return;
        }
    }
}