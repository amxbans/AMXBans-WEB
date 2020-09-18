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


use Models\DB;

class WebAdminController extends \Support\BaseController
{
    /**
     * Outputs the whole list of WebAdmins
     */
    public function index()
    {
        $perm_levels = DB::table('permissions')->orderBy('level')->select('level', \PDO::FETCH_COLUMN);
        $this->site->output->assign(compact('perm_levels'));

        $this->site->output->display('admin.web.admin_list.tpl');
    }

    /**
     * Shows the form of WebAdmin creation
     */
    public function create()
    {
    }

    /**
     * Saves newly created WebAdmin
     */
    public function store()
    {
    }

    /**
     * Show editing form of WebAdmin
     *
     * @param $admin
     */
    public function edit($admin)
    {
    }

    /**
     * Saves changes of WebAdmin
     *
     * @param $admin
     */
    public function update($admin)
    {
    }

    /**
     * Deletes WebAdmin
     *
     * @param $admin
     */
    public function delete($admin)
    {
    }
}