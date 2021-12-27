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

use Models\WebSetting;
use Support\Path;

/**
 * Class Config
 *
 * @property-read string      $cookie
 * @property-read int         $per_page
 * @property-read string|null $banner_src
 * @property-read string      $banner_url
 * @property-read string      $default_lang
 * @property-read int         $start_page
 * @property-read bool        $bans_show_kicks
 * @property-read bool        $bans_show_comments
 * @property-read int         $uploaded_file_size
 * @property-read array       $uploaded_file_types
 * @property-read bool        $allow_unregistered_comments
 * @property-read int         $prune_bans
 * @property-read int         $max_login_tries
 * @property-read array       $smilies
 */
class Config implements ArrayAccess
{
    public const VARS_ARRAYS = ['uploaded_file_types', 'smilies'];
    public const VARS_INTEGERS = ['per_page', 'start_page', 'uploaded_file_size', 'prune_bans', 'max_login_tries'];
    public const VARS_BOOLEANS = ['bans_show_kicks', 'bans_show_comments', 'allow_unregistered_comments'];
    public const VARS_NULLABLE = ['banner_src', 'prune_bans'];

    /**
     * @var array
     */
    public const start_pages = ['bans', 'servers', 'admins'];

    /**
     * @var string Core AMXBans version. <br />
     * Please do NOT change this by Yourself.
     */
    const version = '7.0';

    /**
     * @var array Default values for configuration
     */
    private array $variables = [
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
        'smilies'                     => [],
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
    public function getDb(): DB
    {
        return $this->db;
    }

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
            if (in_array($k, self::VARS_NULLABLE) && is_null($v)) { // Check if nullable
                $this->variables[$k] = null;
            } elseif (in_array($k, self::VARS_ARRAYS)) {            // Check if array
                $this->variables[$k] = json_decode($v, true);
            } elseif (in_array($k, self::VARS_BOOLEANS)) {          // Check if boolean
                $this->variables[$k] = (bool)$v;
            } elseif (in_array($k, self::VARS_INTEGERS)) {           // Check if integer
                $this->variables[$k] = (int)$v;
            } else {                                                        // Fill all the other settings
                $this->variables[$k] = $v;
            }
        }
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

    public function changeValueIfDifferent($variable, string $newRawInputValue): bool
    {
        $value = $this->variables[$variable] ?? null;

        //nullables beforehand
        if (in_array($variable, self::VARS_NULLABLE) && empty($newRawInputValue)) {
            if (array_key_exists($variable, $this->variables) && $value === $newRawInputValue) {
                return false;
            }

            $this->variables[$variable] = null;
            WebSetting::query()->where('name', $variable)->delete();
            WebSetting::query()->insert(['name' => $variable, 'value' => null]);
            return true;
        }

        // First - arrays (because the most complicated)
        if (in_array($variable, Config::VARS_ARRAYS)) {
            if (implode(", ", $this->$variable) === $newRawInputValue) {
                return false;
            }
            // Save new value in config
            $newValue                   = explode(", ", $newRawInputValue);
            $this->variables[$variable] = $newValue;
            // And in database
            $newValue = json_encode($newValue);
            WebSetting::query()->where('name', $variable)->delete();
            WebSetting::query()->insert(['name' => $variable, 'value' => $newValue]);
            return true;
        }

        // Booleans before integers (because bool can be interpreted as int)
        if (in_array($variable, self::VARS_BOOLEANS)) {
            if ($value === (bool)$newRawInputValue) {
                return false;
            }
            $this->variables[$variable] = (bool)$newRawInputValue;
            WebSetting::query()->where('name', $variable)->delete();
            WebSetting::query()->insert(['name' => $variable, 'value' => $this->$variable]);
            return true;
        }

        // Integer check
        if (in_array($variable, self::VARS_INTEGERS)) {
            if ($value === (int)$newRawInputValue) {
                return false;
            }
            $this->variables[$variable] = (int)$newRawInputValue;
            WebSetting::query()->where('name', $variable)->delete();
            WebSetting::query()->insert(['name' => $variable, 'value' => $this->$variable]);
            return true;
        }

        // All other values
        if ($value === $newRawInputValue) {
            return false;
        }

        $this->variables[$variable] = $newRawInputValue;
        WebSetting::query()->where('name', $variable)->delete();
        WebSetting::query()->insert(['name' => $variable, 'value' => $this->$variable]);
        return true;
    }
}