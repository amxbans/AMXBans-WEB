<?php
/** @noinspection PhpVoidFunctionResultUsedInspection */

/** @noinspection PhpUnhandledExceptionInspection */

if (!Auth::$logged) {
    header('HTTP/2.0 404 Not Found');
    exit;
}


Route::get('index/sys_info', 'Admin\IndexController@getSysInfo');

Route::get('index/ban_add', 'Admin\IndexController@getBanAdd');
Route::post('index/ban_add', 'Admin\IndexController@postBanAdd');

Route::get('index/online_ban', 'Admin\IndexController@getOnlineBan');
Route::get('index/servers/{id}', 'Admin\IndexController@ajaxServerPlayers');


Route::resource('web/users', 'Admin\WebAdminController', ['create', 'view']);
Route::resource('web/groups', 'Admin\WebPermissionController', ['create', 'view']);


Route::get('logout', 'LoginController@logout');
