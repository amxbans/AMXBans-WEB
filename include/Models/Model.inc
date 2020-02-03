<?php


namespace Models;

class Model
{
    protected $table = '';
    protected $primary = 'id';

    protected const relations = [];

    protected $original = [];
    private $attributes = [];

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
            foreach ($this->original as $key => $value) {
                $method = snakeToCamel('get_' . $key);
                if (method_exists($this, $method))
                    $this->attributes[$key] = $this->$method($value);
            }
            $this->exists = true;

            if (!empty($with)) {
                $with = array_filter($with, function ($value) {
                    return in_array($value, array_keys(static::relations));
                });
                foreach ($with as $rel_key => $rel_val) {
                    //TODO MULTIPLE RELATIONS: Make to adjust for more than one column
                    /** @var Model $instance */
                    [$multiple, $instance, $local_col, $foreign_col] = $rel_val;

                    $q = $instance::query()->where($foreign_col, $this->$local_col);
                    $this->$rel_key = !$multiple ? $q->selectOne() : $q->select();
                }
            }
        }
    }

    public function save ()
    {
        $diff = array_filter($this->attributes, function (&$v, $k) {
            $method = snakeToCamel('set_' . $v);
            if (method_exists($this, $method))
                $v = $this->$method($v);
            return $v != $this->original[$k];
        }, ARRAY_FILTER_USE_BOTH);
/* TODO:
        var_dump($diff);
        die;*/
        if (!isset($this->{$this->primary})) {
            static::query()->insert($diff);
            return static::find(DB::lastInsertId());
        }
        static::query()->where($this->primary, $this->original[$this->primary])->update($diff);
    }

    public function __get ($name)
    {
        //TODO: Check if exists and then provide relation item
        return $this->attributes[$name];
    }

    public function __set (string $name, $value)
    {
        $this->attributes[$name] = $value;
    }

    /**
     * Get single instance of called model
     * @param          $id
     * @param string|array   $columns
     * @param int|null $fetch_type
     *
     * @return bool|mixed
     */
    public static function find ($id, $columns = '*', int $fetch_type = null)
    {
        return static::query()->where((new static())->primary, $id)->selectOne($columns, $fetch_type);
    }
}