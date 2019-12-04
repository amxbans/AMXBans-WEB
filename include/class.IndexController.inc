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
    public function __construct(Site $config, string $method, string $site)
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

    private function getLogin()
    {
        if (Route::getFakePathWay(1) == 'pass_rec')
            return $this->getPassRec();

        $remaining = @$_SESSION['login_block'] ? time() - $_SESSION['login_block'] : NULL;
        $this->config->config->output->assign('blocked', $remaining);

        $this->config->config->output->display($this->config->getTplFile());
    }

    private function postLogin()
    {
        if (Route::getFakePathWay(1) == 'pass_rec')
            return $this->postPassRec();
    }

    private function postPassRec()
    {
        if ($this->config->validateFormAuth()) {
            $d = $this->config->config->getDb();
            $user = $d->prepare("SELECT id, username, passreset_code as code, passreset_until as until FROM {$this->config->config->dbPrefix}_webadmins WHERE email=?");
            $user->execute([trim($_POST['email'])]);

            if ($user->rowCount() == 1) {
                $user = $user->fetchObject();
                if ($user->code && (new DateTime($user->until) > new DateTime()))
                    $eMsg[] = __LANG__['index']['login']['passcode_exist'];
                else {
                    db_log('Password Recovery', 'Unset password', $user->username);
                    $q = $d->prepare("UPDATE `{$this->config->config->dbPrefix}_webadmins` SET passreset_code=?, passreset_until=? WHERE id=?");
                    $q->execute([md5($user->id . $user->username . time()), (new DateTime('+1 day'))->format('Y-m-d H:i:s'), $user->id]);

                    $msg = $this->config->config->output-> // TODO: needs finishing
                    mail($user->username . '<' . trim($_POST['email']) . '>', 'Password reset');

                    $sMsg[] = __LANG__['index']['login']['passcode_sent'];
                }
            }
        }

    }

    private function getPassRec()
    {
        if (isset($_GET['code'])) {
            $c = trim($_GET['code']);


        }

        $this->config->config->output->display('index.login.lost_pass.tpl');
    }
}