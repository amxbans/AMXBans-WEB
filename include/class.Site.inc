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
    /** @var Config */
    public $config;
    /** @var array */
    protected $routes = [
        'index' => [ 'bans', 'ban', 'servers', 'admins', 'search', 'login' ],
        'admin' => [ '', 'logout' ],
    ];
    /** @var string */
    private $tpl = '';
    private $method;

    protected $form = 600; // 10 minutes


    public static function build (Config $config) {
        $s = new self();
        $s->config = $config;
        $s->method = $method = $s->resolveMethod();

        if (!Route::getFakePathWay())
            $s->tpl = 'index.' . Config::start_pages[$config->start_page];
        else {
            $php = substr(explode('.', substr(Route::getURL(), strlen(Route::getBaseURL())))[0], 1);
            $s->tpl = in_array(Route::getFakePathWay(), $s->routes[$php] ?? []) ?
                $php . '.' . Route::getFakePathWay() :
                'index.' . Config::start_pages[$config->start_page];
        }

        $config->output->assign('site', $s);

        $controller = ucfirst($s->getGroup()) . 'Controller';
        $cMethod = $s->getSite();
        new $controller($s, $method, $cMethod);
    }

    public function parseComment (string $text): string {
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
    public function getTpl () { return $this->tpl; }

    /** Get the file of template
     *
     * @return mixed
     */
    public function getTplFile () { return $this->tpl . '.tpl'; }

    /** Get the site name
     *
     * @return mixed
     */
    public function getSite () { return explode('.', $this->tpl)[1]; }

    /** Get the site group
     *
     * @return mixed
     */
    public function getGroup () { return explode('.', $this->tpl)[0]; }

    public static function hasCookie ($what = 'unID'): bool {
        if (!is_array($what))
            $what = [ $what ];

        foreach ($what as $value) {
            if (!isset($_COOKIE[$value]))
                return FALSE;
        }
        return TRUE;
    }

    public function makeFormAuth ($method = 'post') {
        if (strtolower($method) == 'get')
            return '';
        $_SESSION['TOKEN_V'] = uniqid();
        $_SESSION['TOKEN_T'] = time();
        $_SESSION['TOKEN_M'] = $method;

        $o = strtolower($method) == 'post' ? '' : "<input type='hidden' name='_method_' value='{$method}' />";
        return $o . "<input type='hidden' name='f_v_t' value='{$_SESSION['TOKEN_V']}' />";
    }

    public function validateFormAuth () {
        $t = $_SESSION['TOKEN_T'];
        if ((time() - $this->form) > $t)
            return $this->destroyFormAuth();
        $m = $_SESSION['TOKEN_M'];
        $v = $_SESSION['TOKEN_V'];
        $this->destroyFormAuth();
        return ($v == $_POST['f_v_t'] && $this->method == $m);
    }

    protected function destroyFormAuth () {
        unset($_SESSION['TOKEN_T'], $_SESSION['TOKEN_M'], $_SESSION['TOKEN_V']);
        return FALSE;
    }

    private function resolveMethod () {
        if (strtolower($_SERVER['REQUEST_METHOD']) == 'get')
            return 'get';
        else
            return $_POST['_method_'] ?: 'post';
    }
}