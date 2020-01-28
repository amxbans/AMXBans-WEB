<?php


namespace Models;

use PDO;

class DB //TODO: restructure simpler
{
    protected $model;
    protected $table = '';
    protected $primary = 'id';

    protected $wheres = [];
    protected $limits;

    public static function asModel ($model)
    {
        $t = new self();
        $t->model = $model;
        return $t;
    }

    public static function table ($table)
    {
        $c = new self();
        $c->table = $table;
        return $c;
    }


    /**
     * @param string|array $columns
     * @param int|null     $type
     *
     * @return static[]
     */
    public function select ($columns = '*'): array
    {
        if ($columns != '*' OR is_array($columns))
            $columns = '`' . implode('`, `', is_array($columns) ? $columns : [$columns]) . '`';
        $q = "SELECT $columns FROM `" . $this->getTableName() . "` ";
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


        $sql = "SELECT $columns FROM " . $this->getTableName() . " " . $this->processWhere() . ' ' . $this->processLimit();
        $sql = $this->db($sql);
        var_dump($sql);
        $sql->execute(empty($this->wheres) ? NULL : $this->wheres);

        $out = $sql->fetchAll($type, !isset($type_argument) ? static::class : $type_argument);
        if (!empty($this->with)) {
            $column_indexes = array_flip(array_keys($out[0]));
            $with = array_filter($this->relations, function ($key) {
                return in_array($key, $this->with);
            }, ARRAY_FILTER_USE_KEY);

            foreach ($with as $prop => $item) {
                /** @var DB $instance */
                [$multiple, $instance, $local_cols, $foreign_cols] = $item;
                $local_cols = is_array($local_cols) ? $local_cols : [$local_cols];
                $foreign_cols = is_array($foreign_cols) ? $foreign_cols : [$foreign_cols];
                $instance = $instance::query();
                if (!$multiple)
                    $instance->limit(1);

                foreach ($local_cols as $value)
                    $local_vals[] = array_keys($sql->fetchAll(PDO::FETCH_COLUMN | PDO::FETCH_GROUP, $column_indexes[$value]));

                foreach ($foreign_cols as $value)
                    $instance->where(function (DB $DB) use ($local_vals, $value) {
                        foreach ($local_vals as $val)
                            $DB->where($value, 'IN', $val);
                        return $DB;
                    });

                $instances = $instance->get();
                foreach ($out as $value) {
                    $a = array_filter($instances, function (DB $val) use ($foreign_cols) {
                        //TODO: $values un $item[3] jāmēģina izvilkt
                        foreach ($foreign_cols as $col) {

                        }
                    });
                    if (is_array($value))
                        $value[$prop] = $a;
                    else
                        $value->$prop = $a;
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
    public function find ($id, $columns = '*')
    {
        $qq = $this->where($this->primary, $id)->limit(1)->get($columns, $type);
        return $qq[0] ?? $this;
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

    public static function rawSQL (string $sql, array $values = null, $asModel = null, $fetch_style = null)
    {
        $i = new self();
        $q = $i->db($sql);
        $q->execute($values);
        return $q->fetchAll($fetch_style ?? PDO::FETCH_CLASS, $asModel);
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
        return $this->limits ?? '';
    }
}