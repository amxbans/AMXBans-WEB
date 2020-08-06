<?php /** @noinspection PhpUnhandledExceptionInspection */

Route::get('', 'StartController@index');

Route::resource('bans', 'BansController', ['create', 'store']);
Route::get('bans/{id}/unban', 'BansController@unban');
Route::post('bans/{id}', 'BansController@comment');

Route::resource('login', 'LoginController', ['index', 'store', 'view'], true);
Route::get('login/lost_pass', 'LoginController@getLostPass');