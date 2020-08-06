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
 */
class WebAdmin extends Model
{
    protected $table = 'webadmins';


    public function getPassresetUntil($original)
    {
        return $original? new \DateTime($original) : null;
    }

    public function setPassresetUntil($original)
    {
        return $original? $original->format('Y-m-d H:i:s') : null;
    }
}