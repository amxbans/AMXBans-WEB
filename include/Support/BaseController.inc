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

/**  */

namespace Support;

use Exception;
use Site;

class BaseController
{
    private $method;
    protected $site;

    /**
     * Controller constructor.
     *
     * @param Site   $site
     * @param string $method
     * @param string $callable
     * @param array  $arguments
     *
     * @throws Exception
     */
    public function __construct(Site $site, string $method, string $callable, array $arguments = [])
    {
        $this->site   = $site;
        $this->method = $method;

        // If there's any extra action needed, it has to be placed here for all the sites

        if (method_exists($this, $callable)) {
            $this->$callable(...$arguments);
        } else {
            throw new Exception("Site \"" . $callable . "\" not found");
        }
    }
}