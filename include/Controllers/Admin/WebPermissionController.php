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
use Models\WebPermission;
use Support\BaseController;
use Support\DB;

class WebPermissionController extends BaseController
{
    /**
     * Shows the list of permissions
     */
    public function index()
    {
        $permissions = WebPermission::query()->orderBy('level')->select();
        $this->site->output->assign('perm_list', $permissions);
        $this->site->output->assign('spec_options', [Lang::get('no'), Lang::get('own'), Lang::get('yes'),]);
        $this->site->output->assign('options', [Lang::get('no'), Lang::get('yes'),]);
        if ($this->site->output->getTemplateVars('level') === null) {
            $this->site->output->assign('level', array_merge(['level' => 0], array_fill_keys(Auth::PERMISSIONS, 0)));
        }
        $this->site->output->display('admin.web.permission_list.tpl');
    }

    /**
     * Stores newly made permission level
     */
    public function store()
    {
        WebPermission::query()->insert(
            [
                'bans_add'         => $_POST['bans_add'],
                'bans_edit'        => $_POST['bans_edit'],
                'bans_delete'      => $_POST['bans_delete'],
                'bans_unban'       => $_POST['bans_unban'],
                'amxadmins_view'   => $_POST['amxadmins_view'],
                'amxadmins_edit'   => $_POST['amxadmins_edit'],
                'webadmins_view'   => $_POST['webadmins_view'],
                'webadmins_edit'   => $_POST['webadmins_edit'],
                'websettings_view' => $_POST['websettings_view'],
                'websettings_edit' => $_POST['websettings_edit'],
                'permissions_edit' => $_POST['permissions_edit'],
                'prune_db'         => $_POST['prune_db'],
                'servers_edit'     => $_POST['servers_edit'],
                'ip_view'          => $_POST['ip_view'],
            ]
        );

        db_log('USER LEVELS', 'Created level ' . DB::lastInsertId());
        $this->site->output->assign('message', Lang::get('saved'));
        $this->index();
    }

    /**
     * Shows the form for editing permission level
     *
     * @param $permission
     */
    public function edit($permission)
    {
        $permission = WebPermission::find($permission);
        $this->site->output->assign('level', $permission);
        $this->index();
    }

    /**
     * Saves changes to permission
     *
     * @param $permission
     */
    public function update($permission)
    {
        $permission                   = WebPermission::find($permission);
        $permission->bans_add         = $_POST['bans_add'];
        $permission->bans_edit        = $_POST['bans_edit'];
        $permission->bans_delete      = $_POST['bans_delete'];
        $permission->bans_unban       = $_POST['bans_unban'];
        $permission->amxadmins_view   = $_POST['amxadmins_view'];
        $permission->amxadmins_edit   = $_POST['amxadmins_edit'];
        $permission->webadmins_view   = $_POST['webadmins_view'];
        $permission->webadmins_edit   = $_POST['webadmins_edit'];
        $permission->websettings_view = $_POST['websettings_view'];
        $permission->websettings_edit = $_POST['websettings_edit'];
        $permission->permissions_edit = $_POST['permissions_edit'];
        $permission->prune_db         = $_POST['prune_db'];
        $permission->servers_edit     = $_POST['servers_edit'];
        $permission->ip_view          = $_POST['ip_view'];
        $permission->save();


        db_log('USER LEVELS', 'Edited level ' . $permission->level);
        $this->site->output->assign('message', Lang::get('saved'));
        $this->edit($permission);
    }

    /**
     * Deletes permission
     *
     * @param $permission
     */
    public function delete($permission)
    {
        WebPermission::query()->delete($permission);

        db_log('USER LEVELS', 'Deleted level ' . $permission);
        $this->site->output->assign('message', Lang::get('deleted'));
        $this->index();
    }
}