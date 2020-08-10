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

use Models\WebAdmin;


/**
 * Class Auth
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
        } else {
            $id = 0;
        }

        $user = WebAdmin::find($id);

        if ($user->exists) {
            self::$data   = $user;
            self::$logged = true;
            self::$banned = ($config->max_login_tries && self::get('try') > $config->max_login_tries);

            $user->last_action = new DateTime();
            $user->save();

            self::$permissions = $user->permissions;
        }
    }

    public static function init(Config $config)
    {
        return new self($config);
    }

    /**
     * TODO: adjust LOGIN method
     *
     * @param WebAdmin $user
     * @param bool     $rem Remember (as cookie) or not
     *
     * @throws Exception
     */
    public function login(WebAdmin $user, bool $rem = false)
    {
        if (!$user->exists) {
            throw new Exception('Login: no user with ID: ' . $user->id . ' found');
        }

        if ($rem) {
            setcookie('unID', $user->id, [
                'expires'  => time() + (3600 * 24 * 7),
                'path'     => \Support\Path::getBaseURL(),
                'samesite' => 'Strict',
            ]);
        } else {
            $_SESSION['unID'] = $user->id;
        }
        $this->__construct($this->config);
    }

    public function logout()
    {
        setcookie('unID', 0, [
            'expires'  => 1,
            'path'     => \Support\Path::getBaseURL(),
            'samesite' => 'Strict',
        ]);
        unset($_SESSION['unID']);
        session_destroy();
    }

    public static function get($what = 'id') { return self::$data->$what ?? null; }

    public static function hasPermission($which, $power = 1)
    {
        return self::$logged && !self::$banned ? self::$permissions->$which == $power : false;
    }
}