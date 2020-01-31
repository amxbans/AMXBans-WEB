<?php


namespace Models;

use PDO;

class DB
{
    protected $model;
    protected $table = '';
    protected $primary = 'id';

    /** @var array|null $wheres Variable storing all WHERE clauses */
    protected $wheres;
    /** @var string $limits Stores a string of LIMIT and OFFSET clauses */
    protected $limits;

    public static function table ($table, $model = null)
    {
        $c = new self();
        $c->table = $table;
        $c->model = $model;
        return $c;
    }

    /**
     * @param string|array $columns
     * @param int          $fetch_type
     *
     * @return static[]
     */
    public function select ($columns = '*', int $fetch_type = null): array
    {
        if ($columns != '*' OR is_array($columns))
            $columns = '`' . implode('`, `', is_array($columns) ? $columns : [$columns]) . '`';
        $q = "SELECT $columns FROM " . $this->getTableName() . " " . $this->processWhere() . ' ' . $this->processLimit();
        $q = $this->db($q);
        $q->execute($this->wheres);
        if ($this->model)
            return $q->fetchAll(PDO::FETCH_CLASS, $this->model);
        return $fetch_type? $q->fetchAll($fetch_type) : $q->fetchAll(PDO::FETCH_ASSOC);
    }

    /**
     * @param array $data
     *
     * @return bool
     */
    public function update (array $data = []): bool
    {
        if (empty($data))
            return FALSE;
        foreach ($data as $k => $datum)
            $pieces[] = "`$k` = ?";
        $q = "UPDATE `" . $this->getTableName() . "` SET " . implode(', ', $pieces) . ' ' . $this->processWhere() . ' ' . $this->processLimit();
        return $this->db($q)->execute(array_merge(array_values($data), $this->wheres ?? []));
    }

    /**
     * @param array $data
     *
     * @return bool
     */
    public function insert (array $data): bool
    {
        if (empty($data))
            return FALSE;
        if (func_num_args() > 1) {
            foreach (func_get_args() as $arg)
                $return[] = $this->insert((array)$arg);
            return in_array(false);
        }
        // TODO: FINISH INSERT METHOD -------------================---------------------==============------------------
        /*foreach ($data as $k => $datum)
            $pieces[] = "`$k` = ?";
        $q = "UPDATE `" . $this->getTableName() . "` SET " . implode(', ', $pieces) . ' ' . $this->processWhere() . ' ' . $this->processLimit();
        return $this->db($q)->execute(array_merge(array_values($data), $this->wheres ?? []));*/
    }

    /**
     * Handful method to get single column from SELECT type
     * @param string   $columns
     * @param int|null $fetch_type
     *
     * @return mixed|bool
     */
    public function selectOne ($columns = '*', int $fetch_type = null)
    {
        $q = $this->limit(1)->select($columns, $fetch_type);
        return $q[0] ?? false;
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
     * Adds WHERE clause to query
     *
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
     * Perform a raw SELECT SQL string with optional values and returning in wanted $fetch_style
     *
     * @param string     $sql
     * @param array|null $values
     * @param mixed|null $asModel
     * @param int|null   $fetch_style
     *
     * @return array
     */
    public static function selectRaw (string $sql, array $values = null, $asModel = null, $fetch_style = null)
    {
        $i = new self();
        $q = $i->db($sql);
        $q->execute($values);
        return $q->fetchAll($fetch_style ?? PDO::FETCH_CLASS, $asModel);
    }

    /**
     * Perform a raw SQL string with optional values and returning whether sql execution was success
     *
     * @param string     $sql
     * @param array|null $values
     *
     * @return bool
     */
    public static function rawSQL (string $sql, array $values = null)
    {
        return (new self())->db($sql)->execute($values);
    }

    private function processWhere ($wheres = NULL): string
    {
        if (!$wheres) {
            $wheres = $this->wheres;
            $this->wheres = NULL;
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

    public function getWheres (): array { return $this->wheres; }

    /**
     * Adds (if set), changes or removes (if not set) LIMIT and OFFSET clauses
     *
     * @param int|NULL $limit
     * @param int|NULL $offset
     *
     * @return $this
     */
    public function limit (int $limit = NULL, int $offset = NULL)
    {
        if (is_null($limit)) {
            global $config;
            $limit = $config->per_page;
        }
        $this->limits = !$limit? '' : "LIMIT $limit" . ($offset ? " OFFSET $offset" : '');
        return $this;
    }

    private function processLimit (): string { return $this->limits ?? ''; }
}