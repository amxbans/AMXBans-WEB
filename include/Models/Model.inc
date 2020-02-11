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

    public function __construct ()
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
        /*
        // TODO Model: process and remove relations from $this->attributes when saving
                echo "<b>" . get_called_class() . "::save() :</b><br /> <pre>";
                var_dump($diff);
                die;*/

        if (!isset($this->{$this->primary})) {
            static::query()->insert($diff);
            return static::find(DB::lastInsertId());
        }
        static::query()->where($this->primary, $this->original[$this->primary])->update($diff);
        return static::find($this->{$this->primary});
    }

    public function __get ($name)
    {
        if (array_key_exists($name, $this->attributes))
            return $this->attributes[$name];
        if (!array_key_exists($name, static::relations))
            return method_exists($this, snakeToCamel('get_' . $name)) ? $this->{snakeToCamel('get_' . $name)} : null;
        $this->loadRelation($name);
        return $this->attributes[$name];
    }

    public function __set (string $name, $value)
    {
        $this->attributes[$name] = $value;
    }

    /**
     * Get single instance of called model
     *
     * @param              $id
     * @param string|array $columns
     * @param int|null     $fetch_type
     *
     * @return bool|mixed
     */
    public static function find ($id, $columns = '*', int $fetch_type = null)
    {
        return static::query()->where((new static())->primary, $id)->selectOne($columns, $fetch_type);
    }

    protected function loadRelation ($name): void
    {
        //TODO MULTIPLE RELATIONS: Make to adjust for more than one column
        /** @var Model $instance */
        [$multiple, $instance, $local_col, $foreign_col] = static::relations[$name];

        $q = $instance::query()->where($foreign_col, $this->$local_col);
        $this->$name = !$multiple ? $q->selectOne() : $q->select();
    }
}