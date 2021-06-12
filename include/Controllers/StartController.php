<?php
/**
 *    AMXBans v7
 * Copyright 2018 by SeToY & |PJ|ShOrTy, indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

/**  */

namespace Controllers;

use Config;
use Support\BaseController;
use Support\Path;

class StartController extends BaseController
{
    public function index()
    {
        header('Location: ' . Path::makeURL(Config::start_pages[$this->site->config->start_page]));
    }
}