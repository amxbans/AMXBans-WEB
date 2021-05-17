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
 * Class Site
 */
class Site
{
    /** @var self */
    public static $instance;

    /** @var Config */
    public $config;

    /** @var Auth */
    public $user;

    /** @var Templating */
    public $output;

    /** @var Route */
    public $route;

    /** @var string */
    private $method;

    /** @var array|Closure */
    private $site;
    /** @var array */
    private $siteArgs;

    protected $form = 600; // 10 minutes

    /**
     * Site constructor.
     *
     * @param bool $install
     */
    public function __construct($install = false)
    {
        self::$instance = $this;
        // All the initial things
        include_once 'functions.inc.php';
        spl_autoload_register('init_autoload');

        $this->config = new Config($install);
        $this->output = new Templating($this->config);
        $this->user = Auth::init($this->config);
        $this->route = new Route(basename($_SERVER['SCRIPT_FILENAME']));

        $this->method = $this->resolveMethod();
        [$this->site, $this->siteArgs] = $this->route->getSite($this->method);

        $this->output->assign('site', $this);

        $callable = $this->site;
        if ($callable instanceof Closure) {
            $callable(...$this->siteArgs);
        } else {
            $callable = $callable[0];
            new $callable($this, $this->method, $this->site[1], $this->siteArgs);
        }
    }

    /**
     * @param bool $install
     *
     * @return Site
     */
    public static function build(bool $install = false) { return new self($install); }

    public function parseComment(string $text): string
    {
        foreach ($this->config->smilies as $smiley => $data) {
            $r = "<img src='" . Path::getBaseURL() . "/webSources/images/emoticons/{$data[0]}' alt='{$smiley}' title='{$data[1]}' />";
            $text = str_replace($smiley, $r, $text);
        }

        $text = nl2br($text);
        return $text;
    }

    public static function makeFormAuth($method = 'post')
    {
        if (strtolower($method) == 'get') {
            return '';
        }
        $_SESSION['TOKEN_V'] = uniqid();
        $_SESSION['TOKEN_T'] = time();
        $_SESSION['TOKEN_M'] = strtolower($method);

        $o = strtolower($method) == 'post' ? '' : "<input type='hidden' name='_method_' value='{$method}' />";
        return $o . "<input type='hidden' name='f_v_t' value='{$_SESSION['TOKEN_V']}' />";
    }

    public function validateFormAuth()
    {
        $t = $_SESSION['TOKEN_T'] ?? 0;
        if ((time() - $this->form) > $t) {
            return $this->destroyFormAuth();
        }
        $m = $_SESSION['TOKEN_M'];
        $v = $_SESSION['TOKEN_V'];
        $this->destroyFormAuth();
        return ($v == @$_POST['f_v_t'] && $this->method == $m);
    }

    protected function destroyFormAuth()
    {
        unset($_SESSION['TOKEN_T'], $_SESSION['TOKEN_M'], $_SESSION['TOKEN_V']);
        return false;
    }

    private function resolveMethod()
    {
        if (strtolower($_SERVER['REQUEST_METHOD']) == 'get') {
            return 'get';
        } elseif (strtolower($_SERVER['REQUEST_METHOD']) != 'post') {
            return strtolower($_SERVER['REQUEST_METHOD']);
        } else {
            return strtolower($_POST['_method_'] ?? 'post');
        }
    }
}