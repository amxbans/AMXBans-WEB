<?php
/**
 *    AMXBans v7
 * Copyright 2018 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

namespace Models;

/**
 * Class Ban
 *
 * @package Models
 *
 * @property-read int       $bid
 * @property string|null    $player_ip
 * @property string|null    $player_id
 * @property string|null    $player_nick
 * @property string|null    $admin_ip
 * @property string|null    $admin_id
 * @property string|null    $admin_nick
 * @property string|null    $ban_type
 * @property string|null    $ban_reason
 * @property int|null       $ban_created
 * @property int|null       $ban_length
 * @property string|null    $server_ip
 * @property string|null    $server_name
 * @property int            $ban_kicks
 * @property bool|int       $expired
 * @property bool|int       $imported
 *
 * @property AMXAdmin|null  $admin
 * @property Server|null    $server
 * @property BansLog[]|null $logs
 */
class Ban extends Model
{
    protected $table = 'bans';
    protected $primary = 'bid';
    protected const relations = [
        'server'   => [0, 'Models\Server', 'server_ip', 'address'],
        'admin'    => [0, 'Models\AMXAdmin', 'admin_id', 'steamid'],
        'logs'     => [1, 'Models\BansLog', 'bid', 'bid'],
        'comments' => [1, 'Models\Comment', 'bid', 'bid'],
    ];
}