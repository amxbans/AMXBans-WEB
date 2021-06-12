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

namespace Controllers\Admin;


use Models\DB;
use Models\WebAdmin;
use PDO;
use Support\BaseController;

class WebAdminController extends BaseController
{
    /**
     * Outputs the whole list of WebAdmins
     *
     * @throws \SmartyException
     */
    public function index()
    {
        $perm_levels = DB::table('permissions')->orderBy('level')->select('level', PDO::FETCH_COLUMN);
        $users       = WebAdmin::query()->select();
        $this->site->output->assign(compact('perm_levels', 'users'));

        $this->site->output->display('admin.web.admin_list.tpl');
    }

    /**
     * Saves newly created WebAdmin
     */
    public function store()
    {
        //TODO: write 'store' method for web-admins
    }

    /**
     * Show editing form of WebAdmin
     *
     * @param $admin
     */
    public function edit($admin)
    {
        //TODO: write 'edit' method for web-admins
    }

    /**
     * Saves changes of WebAdmin
     *
     * @param $admin
     */
    public function update($admin)
    {
        //TODO: write 'update' method for web-admins
    }

    /**
     * Deletes WebAdmin
     *
     * @param $admin
     */
    public function delete($admin)
    {
        //TODO: write 'delete' method for web-admins
    }
}