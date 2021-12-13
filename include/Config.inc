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

use Support\Path;

/**
 * Class Config
 *
 * @property-read string $cookie
 * @property-read int    $per_page
 * @property-read string $banner_src
 * @property-read string $banner_url
 * @property-read string $default_lang
 * @property-read int    $start_page
 * @property-read bool   $bans_show_kicks
 * @property-read bool   $bans_show_comments
 * @property-read int    $uploaded_file_size
 * @property-read array  $uploaded_file_types
 * @property-read bool   $allow_unregistered_comments
 * @property-read int    $prune_bans
 * @property-read int    $max_login_tries
 * @property-read array  $smilies
 */
class Config implements ArrayAccess
{
    /**
     * @var array
     */
    public const start_pages = ['bans', 'servers', 'admins'];

    /**
     * @var string
     */
    const version = '7.0';

    /**
     * @var array
     */
    private $variables = [
        'cookie'                      => 'amxx',
        'per_page'                    => 50,
        'banner_src'                  => 'amxbans.png',
        'banner_url'                  => '//forum.amxbans.net',
        'default_lang'                => 'english',
        'start_page'                  => 1,
        'bans_show_kicks'             => true,
        'bans_show_comments'          => true,
        'uploaded_file_size'          => 2000000,
        'uploaded_file_types'         => ['dem', 'zip', 'rar', 'jpg', 'png', 'gif'],
        'allow_unregistered_comments' => false,
        'prune_bans'                  => 5,
        'max_login_tries'             => 5,
    ];

    /** @var DB */
    protected $db;

    public function __construct(bool $install = false)
    {
        if (!$install) {
            if (!file_exists(__DIR__ . "/db.Config.inc")) {
                if (is_dir(Path::getRootPath() . '/install')) {
                    header('Location: ' . Path::getBaseURL() . '/install');
                }
                die("<h1>Server error</h1><p>Sorry, but there is database misconfiguration. Contact its administrator by email: " . $_SERVER['SERVER_ADMIN'] . "</p><hr />" . @$_SERVER['SERVER_SIGNATURE']);
            } else {
                $this->db = new DB();

                $this->setupWebConfig();
            }
        }

        //Setup language strings
        Lang::init($install, $this->default_lang);
    }

    /**
     * @return DB
     */
    public function getDb(): DB { return $this->db; }

    /**
     * @param $name
     *
     * @return mixed
     * @throws Exception
     */
    public function __get($name)
    {
        if (isset($this->variables[$name])) {
            return $this->variables[$name];
        }
        $caller = debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS, 1)[0];
        throw new Exception("Configuration variable '$name' was not found [L{$caller['line']} @ {$caller['file']}]");
    }


    /**
     *
     */
    private function setupWebConfig()
    {
        // webConfig
        $query = $this->db->prepare("SELECT `name`, `value` FROM `{$this->db->prefix}_webconfig`");
        $query->execute();
        $query = $query->fetchAll(PDO::FETCH_KEY_PAIR);

        foreach ($query as $k => $v) {
            if (!isset($this->variables[$k])) {
                $this->variables[$k] = $v;
            } elseif (is_string($this->variables[$k])) {
                $this->variables[$k] = $v;
            } elseif (is_int($this->variables[$k]) && $v != '') {
                $this->variables[$k] = (int)$v;
            } elseif (is_array($this->variables[$k])) {
                $this->variables[$k] = explode(', ', $v);
            } elseif (is_bool($this->variables[$k])) {
                $this->variables[$k] = (bool)$v;
            } elseif (is_int($this->variables[$k]) && $v == '') {
                $this->variables[$k] = null;
            }
        }


        // Smilies
        $query = $this->db->prepare("SELECT `code`, `url`, `name` FROM `{$this->db->prefix}_smilies`");
        $query->execute();

        $this->variables['smilies'] = $query->fetchAll(PDO::FETCH_GROUP|PDO::FETCH_NUM|PDO::FETCH_UNIQUE);
    }

    /**
     * @inheritDoc
     */
    public function offsetExists($offset): bool
    {
        return isset($this->$offset);
    }

    /**
     * @inheritDoc
     */
    public function offsetGet($offset): mixed
    {
        return $this->$offset;
    }

    /**
     * @inheritDoc
     */
    public function offsetSet($offset, $value): void
    {
        // Nope. Preventing!
    }

    /**
     * @inheritDoc
     */
    public function offsetUnset($offset): void
    {
        // Nope. Preventing!
    }

    /**
     * @return array
     */
    public function getVariables(): array
    {
        return $this->variables;
    }
}