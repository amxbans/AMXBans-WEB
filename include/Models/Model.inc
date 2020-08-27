<?php


namespace Models;

use ArrayAccess;

class Model implements ArrayAccess
{
    protected $table = '';
    protected $primary = 'id';
    /**
     * Dates to be translated automatically when receiving from and saving to database.
     *      If field is as key, it's considered as <i>nullable</i> and
     *          at saving will be checked whether null;
     *          when receiving, value of key will be inserted to DateTime.
     *      If field is as value, than regular translation will be performed.
     */
    protected $dates = [];

    protected const relations = [];

    protected $original = [];
    protected $attributes = [];

    public $exists = false;

    /**
     * @return DB|static
     */
    public static function query()
    {
        return DB::table((new static())->table, static::class);
    }

    public function __construct()
    {
        if ($this->{$this->primary}) {
            $this->original = $this->attributes;
            foreach ($this->original as $key => $value) {
                $method = snakeToCamel('get_' . $key);
                if (method_exists($this, $method)) {
                    $this->attributes[$key] = $this->$method($value);
                }
            }
            foreach ($this->dates as $key => $date) {
                if (is_numeric($key)) {
                    $this->attributes[$date] = new \DateTime($this->original[$date]);
                } elseif (is_null($date)) {
                    $this->attributes[$key] = $this->original[$key] ? new \DateTime($this->original[$key]) : null;
                } else {
                    $this->attributes[$key] = new \DateTime($this->original[$key] ?? $date);
                }
            }
            $this->exists = true;
        }
    }

    public function save()
    {
        $this->dropRelations();
        $diff = $this->filterChanged();
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
        foreach ($this->dates as $key => $date) {
            if (!isset($this->attributes[$date]) && !isset($this->attributes[$key])) {
                continue;
            }
            if (is_numeric($key)) {
                $this->attributes[$date] = $this->attributes[$date]->format('Y-m-d H:i:s');
            } elseif (is_null($date)) {
                $this->attributes[$key] = $this->attributes[$key] ? $this->attributes[$key]->format('Y-m-d H:i:s') : null;
            } else {
                $this->attributes[$key] = @new \DateTime($date) == $this->attributes[$key] ? null : $this->attributes[$key]->format('Y-m-d H:i:s');
            }
        }
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

    public function dropRelations(): void
    {
        foreach (static::relations as $relation => $data) {
            unset($this->attributes[$relation]);
        }
    }
}