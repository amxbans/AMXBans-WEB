<?php

namespace Controllers\Admin;

use Auth;
use DateInterval;
use DateTime;
use Lang;
use Models\Log;
use Support\BaseController;
use Support\Path;

class LogsController extends BaseController
{
    public function index()
    {
        $_GET['search_user']   = (int)($_GET['search_user'] ?? 0);
        $_GET['search_action'] = (int)($_GET['search_action'] ?? 0);
        $logs                  = Log::query()->orderBy("created_at", true)->select();
        $this->site->output->assign('logs_count', count($logs));

        // 0 values will be all users and actions
        $users["--" . Lang::get('all') . "--"]   = true;
        $actions["--" . Lang::get('all') . "--"] = true;
        // looping through all logs to get unique usernames and actions
        foreach ($logs as $log) {
            $users[$log->username] = true;
            $actions[$log->action] = true;
        }
        $users   = array_keys($users);
        $actions = array_keys($actions);

        if ($_GET['search_user'] || $_GET['search_action']) {
            $logs = array_filter(
                $logs,
                function ($log) use ($users, $actions) {
                    if ($_GET['search_user'] && $users[$_GET['search_user']] != $log->username) {
                        return false;
                    }
                    if ($_GET['search_action'] && $actions[$_GET['search_action']] != $log->action) {
                        return false;
                    }
                    return true;/*
                    return (!( // Reverse - we need to exclude not matching elements
                        ($_GET['search_user'] && $users[$_GET['search_user']] != $log->username)
                        || ($_GET['search_action'] && $actions[$_GET['search_action']] != $log->username)
                    ));*/
                }
            );
        }

        $this->site->output->assign(compact('logs'));
        $this->site->output->assign([
            'search_users'   => $users,
            'search_actions' => $actions,
        ]);
        return $this->site->output->display('admin.other.logs_list');
    }

    public function delete()
    {
        if (!Auth::hasPermission('websettings_edit')) {
            header('HTTP/2.0 403 Forbidden');
            die;
        }

        if (!isset($_POST['wipe_data'])) {
            return;
        }

        $days = max((int)$_POST['wipe_data'], 0);
        if ($days) {
            $date = new DateTime('today');
            $date->sub(new DateInterval("P{$days}D"));
            Log::query()->where('created_at', '<', $date->format("Y-m-d"))->delete();
        } else {
            Log::query()->delete();
        }

        header("Location: " . Path::makeURL('other/sys_logs'));
        exit;
    }
}