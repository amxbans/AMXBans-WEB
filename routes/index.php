<?php /** @noinspection PhpUnhandledExceptionInspection */

Route::get('', 'StartController@index');

Route::resource('bans', 'BansController', ['create', 'store']);
Route::get('/bans/{id}/unban', 'BansController@unban');

