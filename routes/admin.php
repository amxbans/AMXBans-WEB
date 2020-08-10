<?php /** @noinspection PhpVoidFunctionResultUsedInspection */
/** @noinspection PhpUnhandledExceptionInspection */

if (!Auth::$logged) {
    header('HTTP/2.0 404 Not Found');
    exit;
}


Route::get('index/sys_info', function () {
    return Site::$instance->output->display('master.tpl');
});
Route::get('logout', 'LoginController@logout');
