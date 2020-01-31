<?php


namespace Models;

use http\Exception\BadMethodCallException;

class Model
{
    protected $table = '';
    protected $primary = 'id';

    protected const relations = [];

    protected $original = [];

    public $exists = false;

    public static function query ()
    {
        return DB::table((new static())->table, static::class);
    }

    public function __construct ($with = [])
    {
        if (isset($this->{$this->primary})) {
            $func = function ($c) {
                return get_object_vars($c);
            };
            $this->original = array_diff_key($func($this), ['exists' => false]);
            $this->exists = true;

            if (!empty($with)) {
                $with = array_filter($with, function ($value) { return in_array($value, array_keys(static::relations)); });
                foreach ($with as $rel_key => $rel_val) {
                    //TODO MULTIPLE RELATIONS: Make to adjust for more than one column
                    /** @var Model $instance */
                    [$multiple, $instance, $local_col, $foreign_col] = $rel_val;

                    $q = $instance::query()->where($foreign_col, $this->$local_col);
                    $this->$rel_key = !$multiple? $q->selectOne() : $q->select();
                }
            }
        }
    }

    public function save ()
    {
        if (!isset($this->{$this->primary}))
            throw new BadMethodCallException('Model');
    }
}