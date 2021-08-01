<?php


namespace Models;

use Support\Model;

/**
 * Class WebSetting
 *
 * @package Models
 *
 * @property-read int $id
 * @property string   $name
 * @property string   $value
 */
class WebSetting extends Model
{
    protected $table = 'webconfig';
}