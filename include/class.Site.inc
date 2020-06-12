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

    /** @var array */
    protected $routes = [
        'index' => ['bans', 'ban', 'servers', 'admins', 'search', 'login'],
        'admin' => ['index', 'server', 'web', 'other', 'logout'],
    ];

    /** @var string */
    private $tpl = '';
    private $method;

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

        $this->method = $method = $this->resolveMethod();

        if (!Route::getFakePathWay()) {
            $this->tpl = 'index.' . Config::start_pages[$this->config->start_page];
        } else {
            $php = explode('.', substr(Route::getURL(), strlen(Route::getBaseURL())))[0];
            $php = substr($php, is_numeric(strpos($php, '/')) ? strpos($php, '/') + 1 : 0);
            $this->tpl = in_array(Route::getFakePathWay(), $this->routes[$php] ?? []) ?
                $php . '.' . Route::getFakePathWay() :
                'index.' . Config::start_pages[$this->config->start_page];
        }

        $this->output->assign('site', $this);

        $controller = ucfirst($this->getGroup()) . 'Controller';
        $cMethod = $this->getSite();
        new $controller($this, $method, $cMethod);
    }

    /**
     * @param bool $install
     *
     * @return Site
     */
    public static function build(bool $install = false) { return new self($install); }

    public function parseComment(string $text): string
    {
        $s = $this->config->smilies;
        foreach ($s as $smiley => $data) {
            $r = "<img src='" . Route::getBaseURL() . "/webSources/images/emoticons/{$data[0]}' alt='{$smiley}' title='{$data[1]}' />";
            $text = str_replace($smiley, $r, $text);
        }

        $text = nl2br($text);
        return $text;
    }

    /** Get the name of template
     *
     * @return mixed
     */
    public function getTpl() { return $this->tpl; }

    /** Get the file of template
     *
     * @return mixed
     */
    public function getTplFile() { return $this->tpl . '.tpl'; }

    /** Get the site name
     *
     * @return mixed
     */
    public function getSite() { return explode('.', $this->tpl)[1]; }

    /** Get the site group
     *
     * @return mixed
     */
    public function getGroup() { return explode('.', $this->tpl)[0]; }

    public static function hasCookie($what = 'unID'): bool
    {
        if (!is_array($what)) {
            $what = [$what];
        }

        foreach ($what as $value) {
            if (!isset($_COOKIE[$value])) {
                return false;
            }
        }
        return true;
    }

    public static function makeFormAuth($method = 'post')
    {
        if (strtolower($method) == 'get') {
            return '';
        }
        $_SESSION['TOKEN_V'] = uniqid();
        $_SESSION['TOKEN_T'] = time();
        $_SESSION['TOKEN_M'] = $method;

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
        return ($v == $_POST['f_v_t'] && $this->method == $m);
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
        } else {
            return strtolower($_POST['_method_'] ?? 'post');
        }
    }
}