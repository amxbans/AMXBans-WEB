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
use Models\WebSetting;
use Site;
use Support\BaseController;

class WebSettingsController extends BaseController
{
    public function __construct(Site $site, string $method, string $callable, array $arguments = [])
    {
        if (
            ($callable == 'index' && !Auth::hasPermission('websettings_view')) ||
            (in_array($callable, ['edit', 'update']) && !Auth::hasPermission('websettings_edit'))
        ) {
            header('HTTP/2.0 403 Forbidden');
            die;
        }

        parent::__construct($site, $method, $callable, $arguments);
    }

    public function index()
    {
        $this->site->output->assign([
            'arrays'   => ['uploaded_file_types'],
            'booleans' => ['bans_show_kicks', 'bans_show_comments', 'allow_unregistered_comments'],
            'bool'     => [ucfirst(Lang::get('no')), ucfirst(Lang::get('yes'))],
        ]);

        $settings = $this->site->config->getVariables();
        $this->site->output->assign('smilies', array_pop($settings));
        $this->site->output->assign('settings', $settings);
        return $this->site->output->display('admin.web.settings_list');
    }

    public function edit()
    {
        $this->site->output->assign([
            'arrays'   => ['uploaded_file_types'],
            'appends'  => ['prune_bans' => Lang::get('days'), 'uploaded_file_size' => Lang::get('bytes')],
            'integers' => ['per_page', 'uploaded_file_size', 'prune_bans', 'max_login_tries'],
            'selects'  => ['banner_src', 'default_lang', 'start_page'],
            'booleans' => ['bans_show_kicks', 'bans_show_comments', 'allow_unregistered_comments'],
            'bool'     => [1 => ucfirst(Lang::get('yes')), 0 => ucfirst(Lang::get('no'))],
        ]);

        $settings = $this->site->config->getVariables();
        array_pop($settings);
        $this->site->output->assign('settings', $settings);
        return $this->site->output->display('admin.web.settings_edit');
    }

    /**
     * @throws \Exception
     */
    public function update()
    {
        $variables = $this->site->config->getVariables();
        $var_keys  = array_keys($variables);
        foreach ($var_keys as $var_key) {
            WebSetting::query()
                ->where('name', $var_key)
                ->update([
                    'value' => $_POST[$var_key]
                ]);
        }

        db_log("Web config", "Modified settings"); // TODO MIGRATION: action "Websetting config" -> "Web config"
        return $this->index();
    }
}