<?php


namespace Models;


/**
 * Class Ban
 * @package Models
 *
 * @property-read int    $bid
 * @property string|null $player_ip
 * @property string|null $player_id
 * @property string|null $player_nick
 * @property string|null $admin_ip
 * @property string|null $admin_id
 * @property string|null $admin_nick
 * @property string|null $ban_type
 * @property string|null $ban_reason
 * @property int|null    $ban_created
 * @property int|null    $ban_length
 * @property string|null $server_ip
 * @property string|null $server_name
 * @property int         $ban_kicks
 * @property bool|int    $expired
 * @property bool|int    $imported
 */
class Ban extends DB
{
 protected $table = 'bans';
 protected $primary = 'bid';
 public $relations = [
     'server' => [0, 'Models\Server', 'server_ip', 'address'],
     'admin' => [0, 'Models\AMXAdmin', ['admin_nick', 'admin_ip', 'admin_id'], 'steamid'], //TODO: make AMXAdmins model
 ];
}