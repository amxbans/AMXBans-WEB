<?php
/** @noinspection PhpVoidFunctionResultUsedInspection */

/** @noinspection PhpUnhandledExceptionInspection */

if (!Auth::$logged) {
    header('HTTP/2.0 404 Not Found');
    exit;
}


Route::get('index/sys_info', 'IndexController@getSysInfo');

Route::get('index/ban_add', 'IndexController@getBanAdd');
Route::post('index/ban_add', 'IndexController@postBanAdd');

Route::get('index/online_ban', 'IndexController@getOnlineBan');
Route::get('index/servers/{id}', 'IndexController@ajaxServerPlayers');


Route::resource('web/users', 'WebAdminController');


Route::get('logout', 'LoginController@logout');
