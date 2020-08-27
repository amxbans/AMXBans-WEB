<?php /** @noinspection PhpUnhandledExceptionInspection */

Route::get('', 'StartController@index');

Route::resource('bans', 'BansController', ['create', 'store']);
Route::get('bans/{id}/unban', 'BansController@unban');
Route::post('bans/{id}', 'BansController@comment');

Route::get('servers', 'ServersController@index');
Route::get('servers/{id}', 'ServersController@ajaxServerInfo');

Route::resource('login', 'LoginController', ['index', 'store'], true);
Route::get('login/pass_rec', 'LoginController@lostPassForm');
Route::post('login/pass_rec', 'LoginController@lostPassSend');
Route::get('login/pass_rec/{id}', 'LoginController@passwordRecovery');
Route::put('login/pass_rec/{id}', 'LoginController@updatePassword');