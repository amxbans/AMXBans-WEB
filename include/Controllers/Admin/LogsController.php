<?php

namespace Controllers\Admin;

use Support\BaseController;

class LogsController extends BaseController
{
    public function index()
    {
        return $this->site->output->display('admin.other.logs_list');
    }
}