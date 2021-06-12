<?php


namespace Models;


use Support\Model;

/**
 * Class Log
 *
 * @package Models
 *
 * @property int         $id
 * @property \DateTime   $created_at
 * @property string|null $ip
 * @property string|null $username
 * @property string|null $action
 * @property string|null $remarks
 */
class Log extends Model
{
    protected $table = 'logs';
    protected $dates = ['created_at'];
}