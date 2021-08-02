<?php

namespace Controllers\Admin;

use Support\BaseController;

class EmojiController extends BaseController
{
    public function create()
    {
    }

    public function store()
    {
    }

    public function delete()
    {
        htmlspecialchars_decode($_POST['code']);
    }
}