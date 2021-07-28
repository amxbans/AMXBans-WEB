<?php


namespace Models;

use Support\Model;

/**
 * Class WebPermission
 *
 * @property-read int $level
 * @property int      $bans_add
 * @property int      $bans_edit
 * @property int      $bans_delete
 * @property int      $bans_unban
 * @property bool     $amxadmins_view
 * @property bool     $amxadmins_edit
 * @property bool     $webadmins_view
 * @property bool     $webadmins_edit
 * @property bool     $websettings_view
 * @property bool     $websettings_edit
 * @property bool     $permissions_edit
 * @property bool     $prune_db
 * @property bool     $servers_edit
 * @property bool     $ip_view
 *
 * @package Models
 */
class WebPermission extends Model
{
    protected $table = 'permissions';
    protected $primary = 'level';
    protected const relations = [
        'admin' => [0, 'Models\AMXAdmin', 'level', 'perm_level'],
    ];
}