<?php


namespace Models;


use Support\Model;

/**
 * Class AMXAdmin
 *
 * @package Models
 *
 * @property-read int       $id
 * @property string|null    $username
 * @property string|null    $password
 * @property string|null    $access
 * @property string|null    $flags
 * @property string|null    $steamid
 * @property string|null    $nickname
 * @property int|null       $ashow
 * @property \DateTime|null $created
 * @property int|null       $expired
 * @property int|null       $days
 */
class AMXAdmin extends Model
{
    protected $table = 'amxadmins';
}