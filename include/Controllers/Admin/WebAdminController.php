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


use Auth;
use Lang;
use Models\WebAdmin;
use PDO;
use Support\BaseController;
use Support\DB;

class WebAdminController extends BaseController
{
    /**
     * Outputs the whole list of WebAdmins
     *
     * @throws \SmartyException
     */
    public function index()
    {
        $perms = DB::table('permissions')->orderBy('level')->select('level', PDO::FETCH_COLUMN);
        foreach ($perms as $perm) {
            $permissions[$perm] = sprintf(Lang::get('group_id'), $perm);
        }
        $users = WebAdmin::query()->select();
        $this->site->output->assign(compact('permissions', 'users'));

        $this->site->output->display('admin.web.admin_list.tpl');
    }

    /**
     * Saves newly created WebAdmin
     *
     * @todo 7.1: turn this method to just fill username and email and user password generation is done by password recovery
     */
    public function store()
    {
        if (!$this->checkPermission()) {
            return $this->index();
        }

        $admin             = new WebAdmin();
        $admin->username   = $_POST['new_username'];
        $admin->email      = $_POST['email'];
        $admin->password   = password_hash($_POST['new_password'], PASSWORD_DEFAULT);
        $admin->perm_level = $_POST['level'];
        $admin->save();
        $this->site->output->assign('message', ['type' => 'success', 'text' => Lang::get('saved')]);
        $this->index();
    }

    /**
     * Show editing form of WebAdmin
     *
     * @param $admin
     * @throws \SmartyException
     */
    public function edit($admin)
    {
        if (!$this->checkPermission()) {
            return $this->index();
        }

        $this->site->output->assign('admin', WebAdmin::find($admin));
        return $this->index();
    }

    /**
     * Saves changes of WebAdmin
     *
     * @param $admin
     * @throws \SmartyException
     */
    public function update($admin)
    {
        if (!$this->checkPermission()) {
            return $this->index();
        }

        $admin             = WebAdmin::find($admin);
        $admin->perm_level = $_POST['level'];
        $admin->save();
        $this->site->output->assign('message', ['type' => 'success', 'text' => Lang::get('saved')]);
        $this->index();
    }

    /**
     * Deletes WebAdmin
     *
     * @param $admin
     */
    public function delete($admin)
    {
        if (!$this->checkPermission()) {
            return $this->index();
        }

        if ($admin == 1) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => Lang::get('no_permission')]);
            return $this->index();
        }

        WebAdmin::query()->delete($admin);
        db_log('USERS', 'Deleted user ' . $admin);
        $this->site->output->assign('message', Lang::get('deleted'));
        $this->index();
    }

    private function checkPermission($permission = "webadmins_edit")
    {
        if (!Auth::hasPermission($permission)) {
            $this->site->output->assign('message', ['type' => 'warning', 'text' => Lang::get('no_permission')]);
            return false;
        }
        return true;
    }
}