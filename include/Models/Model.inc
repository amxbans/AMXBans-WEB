<?php


namespace Models;

use ArrayAccess;

class Model implements ArrayAccess
{
    protected $table = '';
    protected $primary = 'id';

    protected const relations = [];

    protected $original = [];
    protected $attributes = [];

    public $exists = false;

    public static function query()
    {
        return DB::table((new static())->table, static::class);
    }

    public function __construct()
    {
        if ($this->{$this->primary}) {
            $func           = function ($c) {
                return get_object_vars($c);
            };
            $this->original = $this->attributes;
            foreach ($this->original as $key => $value) {
                $method = snakeToCamel('get_' . $key);
                if (method_exists($this, $method)) {
                    $this->attributes[$key] = $this->$method($value);
                }
            }
            $this->exists = true;
        }
    }

    public function save()
    {
        $diff = $this->filterChanged();
        /*
        // TODO Model: process and remove relations from $this->attributes when saving
                echo "<b>" . get_called_class() . "::save() :</b><br /> <pre>";
                var_dump($diff);
                die;*/
        if (!$this->{$this->primary}) {
            static::query()->insert($diff);
            $this->{$this->primary} = DB::lastInsertId();
        } else {
            static::query()->where($this->primary, $this->original[$this->primary])->update($diff);
        }
        $this->attributes = static::find($this->{$this->primary})->original;
        $this->__construct();
        return $this;
    }

    public function __get($name)
    {
        if (array_key_exists($name, $this->attributes)) {
            return $this->attributes[$name];
        }
        if (!array_key_exists($name, static::relations)) {
            return method_exists($this, snakeToCamel('get_' . $name)) ? $this->{snakeToCamel('get_' . $name)} : null;
        }
        $this->loadRelation($name);
        return $this->attributes[$name];
    }

    public function __set(string $name, $value)
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
     * @return bool|static
     */
    public static function find($id, $columns = '*', int $fetch_type = null)
    {
        return static::query()->where((new static())->primary, $id)->selectOne($columns, $fetch_type);
    }

    protected function loadRelation($name): void
    {
        //TODO MULTIPLE RELATIONS: Make to adjust for more than one column
        /** @var self $instance */
        [$multiple, $instance, $local_col, $foreign_col] = static::relations[$name];

        $q           = $instance::query()->where($foreign_col, $this->$local_col);
        $this->$name = !$multiple ? $q->selectOne() : $q->select();
    }

    /**
     * @inheritDoc
     */
    public function offsetExists($offset)
    {
        return isset($this->$offset);
    }

    /**
     * @inheritDoc
     */
    public function offsetGet($offset)
    {
        return $this->$offset;
    }

    /**
     * @inheritDoc
     */
    public function offsetSet($offset, $value)
    {
        // TODO: Implement offsetSet() method.
    }

    /**
     * @inheritDoc
     */
    public function offsetUnset($offset)
    {
        // TODO: Implement offsetUnset() method.
    }

    private function filterChanged(): array
    {
        foreach ($this->attributes as $k => $v) {
            $method = snakeToCamel('set_' . $k);
            if (method_exists($this, $method)) {
                $v = $this->$method($v);
            }
            if ($v != @$this->original[$k]) {
                $return[$k] = $v;
            }
        }
        return $return ?? [];
    }
}