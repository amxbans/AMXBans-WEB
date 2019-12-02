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
 * @property-read string $allow_unregistered_comments
 * @property-read int    $delete_expired_bans
 * @property-read int    $max_login_tries
 */
class Config
{
    /**
     * @var array
     */
    const start_pages = [ 'bans', 'servers', 'admins' ];

    /**
     * @var string
     */
    const version = '7.0';

    /**
     * @var array
     */
    private $variables = [
        'per_page'                    => 50,
        'banner_src'                  => 'amxbans.png',
        'banner_url'                  => '//forum.amxbans.net',
        'default_lang'                => 'english',
        'start_page'                  => 0,
        'bans_show_kicks'             => TRUE,
        'bans_show_comments'          => TRUE,
        'uploaded_file_size'          => 2000000,
        'uploaded_file_types'         => [ 'dem', 'zip', 'rar', 'jpg', 'png', 'gif' ],
        'allow_unregistered_comments' => FALSE,
        'delete_expired_bans'         => 5,
        'max_login_tries'             => 5,
    ];

    /** @var Templating */
    public $output;

    /** @var PDO */
    protected $db;

    /** @var stdClass */
    protected $dbData;

    /** @var string */
    public $dbPrefix = '';

    /**
     * @return PDO
     */
    public function getDb (): PDO {
        return $this->db;
    }

    /**
     * Configuration constructor.
     *
     * @param bool $install
     */
    public function __construct ($install = FALSE) {
        // All the initial things
        spl_autoload_register(function ($cls) {
            if (file_exists(__DIR__ . '/class.' . $cls . '.inc')) require_once __DIR__ . '/class.' . $cls . '.inc';
            return;
        });


        if ($install) ;
        elseif (!file_exists(__DIR__ . "/db.Config.inc")) {
            if (is_dir(Route::getRootPath() . '/install'))
                header('Location: ' . Route::getBaseURL() . '/install');
            die("<h1>Server error</h1><p>Sorry, but there is database misconfiguration. Contact its administrator by email: " . $_SERVER['SERVER_ADMIN'] . "</p><hr />" . @$_SERVER['SERVER_SIGNATURE']);
        }
        else {
            $this->dbData = require "db.Config.inc";
            $this->dbPrefix = $this->dbData->prefix;
            try {
                $this->db = new PDO("mysql:dbname={$this->dbData->name};host={$this->dbData->host}", $this->dbData->user, $this->dbData->pass);
                $this->db->exec("SET CHARSET utf8");
            } catch (PDOException $e) {
                trigger_error($e->getMessage());
            }

            $this->setupWebConfig();
            User::init($this);
            include_once 'functions.inc.php';
        }

        //save current language to session
        if (!isset($_SESSION["lang"])) $_SESSION["lang"] = ($install ? 'english' : $this->default_lang);
        if (isset($_POST['lang'])) $_SESSION['lang'] = $_POST['lang'];

        //Setup language strings
        $lang = Route::getRootPath() . ($install ? '/install' : '') . '/language/' . $_SESSION['lang'] . '.php';
        if (file_exists($lang)) $lang = require $lang;
        else
            $lang = require str_ireplace($_SESSION['lang'], 'english', $lang);
        define('__LANG__', $lang);
        $this->output = new Templating($this);
    }

    public function __get ($name) {
        if (isset($this->variables[$name])) return $this->variables[$name];
    }


    /**
     *
     */
    private function setupWebConfig () {
        // webConfig
        $query = $this->db->prepare("SELECT `name`, `value` FROM `{$this->dbPrefix}_webconfig`");
        $query->execute();
        $query = $query->fetchAll(PDO::FETCH_KEY_PAIR);

        foreach ($query as $k => $v) {
            if (!isset($this->variables[$k])) $this->variables[$k] = $v;
            elseif (is_string($this->variables[$k])) $this->variables[$k] = $v;
            elseif (is_int($this->variables[$k]) && $v != '') $this->variables[$k] = (int)$v;
            elseif (is_array($this->variables[$k])) $this->variables[$k] = explode(', ', $v);
            elseif (is_bool($this->variables[$k])) $this->variables[$k] = (bool)$v;
            elseif (is_int($this->variables[$k]) && $v == '') $this->variables[$k] = NULL;
        }


        // Smilies
        $query = $this->db->prepare("SELECT `code`, `url`, `name` FROM `{$this->dbPrefix}_smilies`");
        $query->execute();

        $this->variables['smilies'] = $query->fetchAll(PDO::FETCH_GROUP|PDO::FETCH_NUM|PDO::FETCH_UNIQUE);
    }
}