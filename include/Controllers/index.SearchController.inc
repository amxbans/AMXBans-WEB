<?php
/**
 *    AMXBans v7
 * Copyright 2020 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

/**  */

namespace Controllers;

use Models\AMXAdmin;
use Models\Ban;

/**
 * Class SearchController
 *
 * @package Controllers
 */
class SearchController extends \Support\BaseController
{
    public function index()
    {
        $this->site->output->assign([
            'amxadmins' => Ban::query()->select(['admin_id', 'admin_nick']),
        ]);
        return $this->site->output->display('index.search.tpl');
    }
}