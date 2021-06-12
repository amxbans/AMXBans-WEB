<?php


namespace Models;


use Support\Model;

/**
 * Class Comment
 *
 * @package Models
 *
 * @property-read int           $id
 * @property string             $name
 * @property string|null        $comment
 * @property string|null        $file
 * @property string             $email
 * @property string             $addr IP Address
 * @property \DateTime|string   $created_at
 * @property int                $bid
 * @property int                $admin_id
 * @property int                $hidden_by
 *
 * @property-read Ban           $ban
 * @property-read WebAdmin|null $admin
 */
class Comment extends Model
{
    public const ALL = 0;
    public const COMMENTS = 1;
    public const FILES = 2;
    public const BOTH = 3;

    protected const relations = [
        'ban' => [0, 'Models\Ban', 'bid', 'bid'],
    ];
    protected $table = 'comments';
    protected $dates = ['created_at'];

    public static function query(int $type = self::ALL)
    {
        if ($type == self::FILES) {
            return parent::query()->where('file', 'IS NOT');
        }
        if ($type == self::COMMENTS) {
            return parent::query()->where('comment', 'IS NOT');
        }
        if ($type == self::BOTH) {
            return parent::query()->where('file', 'IS NOT')->where('comment', 'IS NOT');
        }
        return parent::query();
    }

}