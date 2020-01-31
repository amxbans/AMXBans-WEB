<?php


namespace Models;


/**
 * Class Server
 *
 * @package Models
 *
 * @property int         $id
 * @property int|null    $timestamp
 * @property string|null $hostname
 * @property string|null $address
 * @property string|null $gametype
 * @property string|null $rcon
 * @property string|null $amxban_version
 * @property string|null $amxban_motd
 * @property int|null    $motd_delay
 * @property int         $amxban_menu
 * @property int|null    $reasons
 * @property int         $timezone_fixx
 */
class Server extends Model
{
    protected $table = 'serverinfo';
    protected const relations = [
        'bans' => [1, 'Models\Ban', 'address', 'server_ip'],
    ];
}