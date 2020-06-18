<?php
/**
 *    AMXBans v7
 * Copyright 2018 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

class Auth
{
    /** @var array */
    public static $data;
    /** @var bool */
    public static $logged = false;
    /** @var bool */
    public static $banned = false;

    /** @var Config */
    private $config;
    /** @var stdClass */
    protected static $permissions;

    public function __construct(Config $config)
    {
        $this->config = $config;

        if (isSet ($_SESSION['unID'])) {
            $id = (int)$_SESSION['unID'];
        } elseif (Site::hasCookie()) {
            $id = (int)$_COOKIE['unID'];
        } elseif (isset($_POST['login_name'])) {
            $id = $this->config->getDb()
                ->prepare("SELECT id FROM `{$config->getDb()->prefix}_webadmins` WHERE username=?");
            $id->execute([$_POST['login_name']]);
            $id = $id->fetchObject()->id;
        } else {
            $id = 0;
        }

        $user = $config->getDb()
            ->prepare("SELECT * FROM `{$config->getDb()->prefix}_webadmins` WHERE id=?");
        $user->execute([$id]);

        if ($user->rowCount() === 1) {
            self::$data = $user->fetch(PDO::FETCH_ASSOC);
            self::$logged = true;
            self::$banned = ($config->max_login_tries && self::get('try') > $config->max_login_tries);

            $last = $config->getDb()
                ->prepare("UPDATE `{$config->getDb()->prefix}_webadmins` SET last_action=CURRENT_TIMESTAMP() WHERE id=?");
            $last->execute([self::get()]);

            $perms = $config->getDb()->prepare("SELECT * FROM `{$config->getDb()->prefix}_permissions` WHERE level=?");
            $perms->execute([self::get('perm_level')]);
            self::$permissions = $perms->fetch(PDO::FETCH_OBJ);
        }
    }

    public static function init(Config $config)
    {
        return new self($config);
    }

    /**
     * TODO: adjust LOGIN method
     *
     * @param string $name Username
     * @param string $pass Password
     * @param bool   $rem  Remember (as cookie) or not
     * @param string $from Send back user to place they came from (by default - homepage)
     *
     * @return string
     */
    public function login($name, $pass, bool $rem = false, string $from = '')
    {
        $user = "SELECT * FROM userTable WHERE";
        if (CONFIG['login_type'] == 1) {
            $user .= " `email=:name`";
        } elseif (CONFIG['login_type'] == 2) {
            $user .= " `name`=:name OR email=:name";
        } else {
            $user .= " `name=:name`";
        }

        try {
            $user = $this->db->prepare($user);
            $user->execute(['name' => $name]);
        } catch (PDOException $e) {
            return msg::error();
        }

        if ($user->rowCount() === 1 AND password_verify($pass, $user->fetch()['pass'])) {
            if ($rem) {
                setcookie('unID', $user->fetch()['unique_id'], CONFIG['login_remember_time'], '', '', false, true);
            } else {
                $_SESSION['unID'] = $user->fetch()['unique_id'];
            }
            header('Location: ' . CONFIG['HOME_URL'] . $from);
        } else {
            return msg::warn(lang('LOGIN_FAILED', 'ERRORS'));
        }
    }

    public function get($what = 'id') { return self::$data[$what] ?? null; }

    public static function hasPermission($which, $power = 1)
    {
        return self::$logged && !self::$banned ? self::$permissions[$which] == $power : false;
    }
}