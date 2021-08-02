<?php
/**
 *    AMXBans v7
 * Copyright 2009, 2010 by SeToY & |PJ|ShOrTy; 2021 by indianiso1
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
use Support\BaseController;

class WebSettingsController extends BaseController
{
    public function index()
    {
        if (!Auth::hasPermission('websettings_view')) {
            return $this->site->output->display('admin.web.settings_list');
        }

        $this->site->output->assign([
            'arrays'   => ['uploaded_file_types'],
            'booleans' => ['bans_show_kicks', 'bans_show_comments', 'allow_unregistered_comments'],
            'bool'     => [ucfirst(Lang::get('no')), ucfirst(Lang::get('yes'))],
        ]);

        $settings = $this->site->config->getVariables();
        $this->site->output->assign('smilies', array_pop($settings));
        $this->site->output->assign('settings', $settings);
        $this->site->output->display('admin.web.settings_list');
    }

    public function edit()
    {
    }

    public function update()
    {
    }
}