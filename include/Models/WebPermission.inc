<?php


namespace Models;


class WebPermission extends Model
{
    protected $table = 'permissions';
    protected $primary = 'level';
    protected const relations = [
        'admin' => [0, 'Models\AMXAdmin', 'level', 'perm_level'],
    ];
}