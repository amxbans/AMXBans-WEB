<?php

namespace Controllers\Admin;

use Auth;
use DateInterval;
use DateTime;
use Models\Log;
use Support\BaseController;
use Support\Path;

class LogsController extends BaseController
{
    public function index()
    {
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