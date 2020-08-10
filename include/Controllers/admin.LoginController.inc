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
namespace Controllers;

use Support\BaseController;
use Support\Path;

/**
 * Class LoginController
 *
 * @package Controllers
 */
class LoginController extends BaseController
{
    public function logout()
    {
        $lang = $_SESSION['lang'];
        $this->site->user->logout();
        return header('Location: ' . Path::makeURL('', 'index.php'));
    }
}