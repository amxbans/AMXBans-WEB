<?php


namespace Models;


/**
 * Class Log
 *
 * @package Models
 *
 * @property int $id
 * @property \DateTime $created_at
 * @property string|null $ip
 * @property string|null $username
 * @property string|null $action
 * @property string|null $remarks
 */
class Log extends Model
{
    protected $table = 'logs';


    public function getCreatedAt($original)
    {
        return new \DateTime($original);
    }
    public function setCreatedAt(\DateTime $original)
    {
        return $original->format('Y-m-d H:i:s');
    }
}