<?php


namespace Models;


class Ban extends DB
{
 protected $table = 'bans';
 protected $primary = 'bid';
 public $relations = [
     'server' => [0, 'Models\Server', 'server_ip', 'address'],
     'admin' => [0, 'Models\AMXAdmin', ['admin_nick', 'admin_ip', 'admin_id'], 'steamid'], //TODO: make AMXAdmins model
 ];
}