<?php

namespace Controllers\Admin;

use Support\BaseController;

class EmojiController extends BaseController
{
    public function create()
    {
        // TODO: implement create method (emoji creation in ACP web/settings)
    }

    public function store()
    {
        // TODO: implement store method (emoji creation in ACP web/settings)
    }

    public function delete()
    {
        // TODO: implement delete method (emoji list in ACP web/settings)
        htmlspecialchars_decode($_POST['code']);
    }
}