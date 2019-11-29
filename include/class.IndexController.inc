<?php
/**
 *    AMXBans v7
 * Copyright 2019 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */


class IndexController
{
    private $site;
    private $method;
    protected $config;

    /**
     * IndexController constructor.
     *
     * @param Site   $config
     * @param string $method
     * @param string $site
     */
    public function __construct (Site $config, string $method, string $site) {
        $this->config = $config;
        $this->method = $method;
        $this->site = $site;

        // If there's any extra action needed, it has to be placed here for all the 'index' sites


        $m = $method . ucfirst($site);
        if (method_exists($this, $m))
            $this->$m();
    }

    private function getLogin () {
        $remaining = @$_SESSION['login_block'] ? time() - $_SESSION['login_block'] : NULL;
        $this->config->config->output->assign('blocked', $remaining);

        $this->config->config->output->assign('messages', new FormErrors([], [])); // TODO: This point unfinished

        $this->config->config->output->display($this->config->getTplFile());
    }
}