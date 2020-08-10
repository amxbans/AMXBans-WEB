<?php


namespace Models;

/**
 * Class WebAdmin
 *
 * @package Models
 *
 * @property int $id
 * @property string $username
 * @property string $password
 * @property int $perm_level
 * @property string|null $passreset_code
 * @property \DateTime|null $passreset_until
 * @property string $email
 * @property \DateTime $last_action
 * @property int $try
 *
 * @property-read WebPermission $permissions
 */
class WebAdmin extends Model
{
    protected $table = 'webadmins';
    protected const relations = [
        'permissions' => [0, 'Models\WebPermission', 'perm_level', 'level'],
    ];

    protected $dates = ['passreset_until' => null, 'last_action' => '@1'];
}