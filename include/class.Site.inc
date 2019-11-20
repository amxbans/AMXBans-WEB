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
    /** @var array  */
    protected $routes = [
        'index' => ['bans', 'ban', 'servers', 'admins', 'search', 'login', 'logout'],
        'admin' => [''],
    ];
    /** @var string  */
    private $tpl = '';
    /** @var Config */
    protected $config;


    public static function init(Config $config)
    {
        $s = new self();
        $s->config = $config;
        if (!Route::getFakePathWay())
            $s->tpl = 'index.' . Config::start_pages[$config->default_page];
        else {
            $php = explode('.', substr(Route::getURL(), strlen(Route::getBaseURL()) - 1))[0];
            $s->tpl = in_array(Route::getFakePathWay(), $s->routes[$php] ?? []) ?
                $php . '.' . Route::getFakePathWay() :
                'index.' . Config::start_pages[$config->default_page];
        }
        return $s;
    }

    public function parseComment(string $text): string
    {
        $s = $this->config->smilies;
        foreach ($s as $smiley => $data) {
            $r = "<img src='" . Route::getBaseURL() . "/webSources/images/emoticons/{$data[0]}' alt='{$data[0]}' title='{$data[1]}' />";
            $text = str_replace($smiley, $r, $text);
        }

        $text = nl2br($text);
        return $text;
    }

    /** Get the name of template
     * @return mixed
     */
    public function getTpl() { return $this->tpl; }

    public static function hasCookie($what = 'unID'): bool
    {
        if (!is_array($what))
            $what = func_get_args();

        foreach ($what as $value)
            if (!isset($_COOKIE[$value]))
                return FALSE;
        return TRUE;
    }
}