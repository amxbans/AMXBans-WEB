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

require_once 'smarty/Smarty.class.php';

/**
 * Class Templating
 */
class Templating extends Smarty
{


    /**
     * Templating constructor.
     *
     * @param Config $config
     */
    public function __construct (Config $config)
    {
        parent::__construct();

        $this->setTemplateDir([
            Route::getRootPath() . '/include/templates',
            Route::getRootPath() . '/install/templates',
        ]);

        $this->setCompileDir(Route::getRootPath() . '/include/templates/compiled');
        $this->setForceCompile(FALSE);

        $this->assign('lang', __LANG__);
        $this->assign('availLangs', $this->getAvailableLanguages());
        $this->assign('app_name', 'AMXBans v' . Config::version);
        $this->assign('version', Config::version);
        $this->assign(compact('config'));

    }

    private function getAvailableLanguages ()
    {

        $langs = scandir('language');
        foreach ($langs as $file)
            if ($file != "." && $file != ".." && substr($file, 0, 4) != "lang")
                $lang[] = explode('.', $file)[0];

        return $lang;
    }

    public function display ($template = null, $cache_id = null, $compile_id = null, $parent = null)
    {
        if (!strpos($template, '.tpl', 1))
            $template .= '.tpl';
        parent::display($template, $cache_id, $compile_id, $parent);
    }
}