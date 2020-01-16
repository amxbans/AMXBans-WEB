<?php


namespace Models;


use PDO;

class DB
{
    protected $table = '';
    protected $primary = 'id';
    public $relations = [];

    protected $wheres = [];
    protected $limits;
    protected $with = [];

    /**
     * @return static
     */
    public static function query ()
    {
        return new static();
    }

    public static function with ($relations)
    {
        /** @var static $this */
        $m = $this ?? new static();
        $m->relations = is_array($relations) ? $relations : func_get_args();
        return $m;
    }


    /**
     * @param string|array $columns
     * @param int|null     $type
     *
     * @return array
     */
    public static function all ($columns = '*', $type = NULL): array
    {
        return static::query()->get($columns, $type);
    }

    /**
     * @param string|array $columns
     * @param int|null     $type
     * @param mixed        $type_argument
     *
     * @return static[]
     */
    public function get ($columns = '*', $type = NULL, $type_argument = NULL): array
    {
        if (is_null($type))
            $type = PDO::FETCH_CLASS;
        if ($columns != '*' OR is_array($columns))
            $columns = '`' . implode('`, `', is_array($columns) ? $columns : [$columns]) . '`';

        $sql = "SELECT $columns FROM " . $this->getTableName() . " " . $this->processWhere() . ' ' . $this->processLimit();
        $sql = $this->db($sql);
        $sql->execute(empty($this->wheres) ? NULL : $this->wheres);

        $out = $sql->fetchAll($type, !isset($type_argument) ? static::class : $type_argument);
        if (!empty($this->with)) {
            $keys = array_flip(array_keys($out[0]));
            foreach ($this->with as $prop => $item) {
                /** @var DB $instance */
                $instance = $item[1];
                $instance = $instance::query();
                if (!$item[0])
                    $instance->limit(1);

                foreach (is_array($item[2]) ? $item[2] : [$item[2]] as $value)
                    $values[] = array_keys($sql->fetchAll(PDO::FETCH_COLUMN | PDO::FETCH_GROUP, $keys[$value]));

                foreach (is_array($item[3]) ? $item[3] : [$item[3]] as $value)
                    $instance->where(function (DB $DB) use ($values, $value) {
                        foreach ($values as $val)
                            $DB->where($value, 'IN', $val);
                        return $DB;
                    });

                $instance = $instance->get();
                foreach ($out as $value) {
                    $a = array_filter($instance, function ($vel) use ($item) {
                        //TODO: $values un $item[3] jāmēģina izvilkt
                    });
                    $value->$prop = 0; //TOOD: Finish this
                }
            }
        }
        return $out;
    }

    /**
     * @param        $id
     * @param string $columns
     * @param null   $type
     *
     * @return mixed
     */
    public static function find ($id, $columns = '*', $type = NULL)
    { // TODO: restructure static fn-s to __callStatic method
        $q = new static();
        $qq = $q->where($q->primary, $id)->limit(1)->get($columns, $type);
        return $qq[0] ?? new static();
    }

    private function getTableName ()
    {
        global $config;
        return $config->dbPrefix . '_' . $this->table;
    }

    protected function db ($query)
    {
        global $config;
        return $config->getDb()->prepare($query);
    }


    /**
     * @param callable|string $field
     * @param string|null     $operator
     * @param string|null     $value
     * @param string          $pre
     *
     * @return $this
     */
    public function where ($field, $operator = NULL, $value = NULL, $pre = 'AND'): self
    {
        $pre = strtoupper($pre);
        if (is_callable($field)) {
            $this->wheres[] = [$pre, $field(new DB())->getWheres()];
            return $this;
        }
        if (!in_array($operator, sql_operators()))
            [$value, $operator] = [$operator, '='];
        if (is_null($value) && in_array($operator, sql_operators()) && !in_array($operator, ['=', '<>', '!=']))
            $operator = $operator == '=' ? 'IS' : 'IS NOT';
        $this->wheres[] = [$pre, $field, $operator, $value];
        return $this;
    }

    /**
     * @param array|null $wheres
     *
     * @return string
     */
    private function processWhere ($wheres = NULL): string
    {
        if (!$wheres) {
            $wheres = $this->wheres;
            $this->wheres = [];
        }
        if (empty($wheres))
            return '';

        $w = '';
        foreach ($wheres as $where) {
            if (is_array($where[1]))
                $w .= "$where[0] (" . substr($this->processWhere($where[1]), 6) . ')';
            elseif (is_null($where[3]))
                $w .= "$where[0] `$where[1]` $where[2] $where[3]";
            elseif (strpos('IN', $where[2]) !== FALSE) {
                foreach ($where[3] as $value) {
                    $word = 'w_' . substr(uniqid(), -3);
                    $this->wheres[$word] = $value;
                    $words[] = ":$word";
                }
                $w .= "$where[0] `$where[1]` $where[2] (" . implode(', ', $words) . ")";
            } else {
                $this->wheres[$word = 'w_' . substr(uniqid(), -3)] = $where[3];
                $w .= "$where[0] `$where[1]` $where[2] :$word";
            }
        }
        return "WHERE" . substr($w, strpos($w, ' '));
    }

    /**
     * @return array
     */
    public function getWheres (): array
    {
        return $this->wheres;
    }

    public function limit (int $limit, int $offset = NULL)
    {
        $this->limits = "LIMIT $limit" . ($offset ? " OFFSET $offset" : '');
        return $this;
    }

    private function processLimit (): string
    {
        return $this->limits;
    }
}