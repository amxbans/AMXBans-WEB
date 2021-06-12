<?php


namespace Models;


use Support\Model;

/**
 * Class BansLog
 *
 * @package Models
 *
 * @property-read int    $id
 * @property int         $bid
 * @property             $created_at
 * @property string      $admin_nick
 * @property string|null $edit_reason
 */
class BansLog extends Model
{
    protected $table = 'bans_edit';
    protected $dates = ['created_at'];
    protected const relations = [
        'ban' => [0, 'Models\Ban', 'bid', 'bid'],
    ];
}