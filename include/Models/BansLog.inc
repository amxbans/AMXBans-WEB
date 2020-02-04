<?php


namespace Models;


/**
 * Class BansLog
 * @package Models
 *
 * @property-read int $id
 * @property int $bid
 * @property $created_at
 * @property string $admin_nick
 * @property string|null $edit_reason
 */
class BansLog extends Model
{
    protected const relations = [
        'ban' => [0, 'Models\Ban', 'bid', 'bid'],
    ];

    /**
     * @return mixed
     */
    public function getCreatedAt ()
    {
        var_dump($this->created_at);
        return $this->created_at;
    }
}