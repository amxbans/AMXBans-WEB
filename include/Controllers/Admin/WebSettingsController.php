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
use Config;
use Lang;
use Site;
use Support\BaseController;
use Support\Path;

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
        $this->site->output->assign('smilies', $settings['smilies']);
        $this->site->output->assign('settings', array_diff_key($settings, ['smilies' => null]));

        return $this->site->output->display('admin.web.settings_list');
    }

    public function edit()
    {
        $this->site->output->assign([
            'arrays'   => Config::VARS_ARRAYS,
            'appends'  => ['prune_bans' => Lang::get('days'), 'uploaded_file_size' => Lang::get('bytes')],
            'integers' => Config::VARS_INTEGERS,
            'booleans' => Config::VARS_BOOLEANS,
            'nullable' => Config::VARS_NULLABLE,
            'bool'     => [1 => ucfirst(Lang::get('yes')), 0 => ucfirst(Lang::get('no'))],
        ]);

        $settings = $this->site->config->getVariables();
        $this->site->output->assign('settings', array_diff_key($settings, ['smilies' => null]));
        return $this->site->output->display('admin.web.settings_edit');
    }

    /**
     * TODO TEST!!
     * @throws \Exception
     */
    public function update()
    {
        $variables = $this->site->config->getVariables();
        $var_keys  = array_keys($variables);
        foreach ($var_keys as $var_key) {
            if ($var_key == "smilies") {
                continue;
            }
            if ($this->site->config->changeValueIfDifferent($var_key, $_POST[$var_key])) {
                $changed[] = $var_key;
            }
        }


        db_log("Web config", "Modified settings: " . implode(", ",
                $changed ?? ['nothing'])); // TODO MIGRATION: action "Websetting config" -> "Web config"
        return header("Location: " . Path::makeURL("web/settings"));
    }
}