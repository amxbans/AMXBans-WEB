<?php

namespace Controllers\Admin;

use Auth;
use FormErrors;
use Lang;
use Site;
use Support\BaseController;
use Support\DB;
use Support\Path;

class EmojiController extends BaseController
{
    public function __construct(Site $site, string $method, string $callable, array $arguments = [])
    {
        if (!Auth::hasPermission('websettings_edit')) {
            header('HTTP/2.0 403 Forbidden');
            die;
        }

        parent::__construct($site, $method, $callable, $arguments);
    }

    public function create()
    {
        return $this->site->output->display('admin.web.emoticons_add');
    }

    public function store()
    {
        $fe = new FormErrors($_POST, Lang::get('validation_errors'));
        $fe->validate([
            'symbol' => "required",
            'title'  => "required",
            'file'   => "required",
        ]);
        if (!file_exists(Path::getRootPath() . PATH_SEPARATOR . "webSources/images/emoticons" . PATH_SEPARATOR . $_POST['file'])) {
            $fe->addError(Lang::get('file_not_found'));
        }

        if ($fe->has()) {
            return $this->create();
        }

        $emoticons                   = $this->site->config->smilies;
        $emoticons[$_POST['symbol']] = [$_POST['file'], $_POST['title']];
        $emoticons                   = json_encode($emoticons);
        DB::table("webconfig")->where("name", "smilies")->update(['value' => $emoticons]);
        return header("Location: " . Path::makeURL("web/settings"));
    }

    public function delete()
    {
        $emoticons = $this->site->config->smilies;
        unset($emoticons[$_POST['code']]);
        $emoticons = json_encode($emoticons);
        DB::table("webconfig")->where("name", "smilies")->update(['value' => $emoticons]);
        header("Location: " . Path::makeURL("web/settings"));
    }
}