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

    public static function table($table, $model = null)
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
     * @return mixed|static|bool
     */
    public function select($columns = '*', int $fetch_type = null): array
    {
        if ($columns != '*') {
            $columns = '`' . implode('`, `', (array)$columns) . '`';
        }
        $q = "SELECT $columns FROM " . $this->getTableName() . " " . $this->processWhere() . ' ' . $this->processLimit();
        $q = $this->db($q);
        $q->execute($this->wheres);
        if ($this->model) {
            return $q->fetchAll(PDO::FETCH_CLASS, $this->model);
        }
        return $fetch_type ? $q->fetchAll($fetch_type) : $q->fetchAll(PDO::FETCH_ASSOC);
    }

    /**
     * @param array $data
     *
     * @return bool
     */
    public function update(array $data = []): bool
    {
        if (empty($data)) {
            return false;
        }
        foreach ($data as $k => $datum) {
            $data[$str = 'u_' . substr(uniqid(), -3)] = is_bool($datum) ? (int)$datum : $datum;
            $pieces[] = "`$k` = :$str";
            unset($data[$k]);
        }
        $q = "UPDATE `" . $this->getTableName() . "` SET " . implode(', ',
                $pieces) . ' ' . $this->processWhere() . ' ' . $this->processLimit();
        return $this->db($q)->execute(array_merge($data, $this->wheres ?? []));
    }

    /**
     * @param array $data
     *
     * @return bool
     */
    public function insert(array $data): bool
    {
        if (empty($data)) {
            return false;
        }
        if (func_num_args() > 1) {
            foreach (func_get_args() as $arg) {
                $return[] = $this->insert((array)$arg);
            }
            return in_array(false, $return);
        }
        $pieces = array_fill(0, count($data), '?');
        $q = 'INSERT INTO `' . $this->getTableName() . '` (`' . implode('`, `',
                array_keys($data)) . '`) VALUES (' . implode(',', $pieces) . ')';

        return $this->db($q)->execute(array_values($data));
    }

    /**
     * Handful method to get single column from SELECT type
     *
     * @param string|array $columns
     * @param int|null     $fetch_type
     *
     * @return mixed|bool|static
     */
    public function selectOne($columns = '*', int $fetch_type = null)
    {
        $q = $this->limit(1)->select($columns, $fetch_type);
        return $q[0] ?? ($this->model ? new $this->model : false);
    }

    private function getTableName() { return \Site::$instance->config->getDb()->prefix . '_' . $this->table; }

    protected function db($query) { return \Site::$instance->config->getDb()->prepare($query); }

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
    public function where($field, $operator = null, $value = null, $pre = 'AND'): self
    {
        $pre = strtoupper($pre);
        if ($field instanceof \Closure) {
            $this->wheres[] = [
                $pre,
                $field(new DB())->getWheres(),
            ];
            return $this;
        }
        if (!in_array((string)$operator, sql_operators())) {
            [$value, $operator] = [$operator, (is_null($operator) ? 'IS' : '=')];
        }

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
    public static function selectRaw(string $sql, array $values = null, $asModel = null, $fetch_style = null)
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
    public static function rawSQL(string $sql, array $values = null)
    {
        return (new self())->db($sql)->execute($values);
    }

    private function processWhere($wheres = null): string
    {
        if (!$wheres) {
            $wheres = $this->wheres;
            $this->wheres = null;
        }
        if (empty($wheres)) {
            return '';
        }

        $w = '';
        foreach ($wheres as $where) {
            if (is_array($where[1])) {
                $w .= "$where[0] (" . substr($this->processWhere($where[1]), 6) . ')';
            } elseif (is_null($where[3])) {
                $w .= "$where[0] `$where[1]` $where[2] NULL";
            } elseif (strpos('IN', $where[2]) !== false) {
                foreach ($where[3] as $value) {
                    $word = 'w_' . substr(uniqid(), -3);
                    $this->wheres[$word] = is_bool($value) ? (int)$value : $value;
                    $words[] = ":$word";
                }
                $w .= "$where[0] `$where[1]` $where[2] (" . implode(', ', $words) . ")";
            } else {
                $this->wheres[$word = 'w_' . substr(uniqid(), -3)] = is_bool($where[3]) ? (int)$where[3] : $where[3];
                $w .= "$where[0] `$where[1]` $where[2] :$word";
            }
        }
        return "WHERE" . substr($w, strpos($w, ' '));
    }

    public function getWheres(): array { return $this->wheres; }

    /**
     * Adds (if not set), changes or removes LIMIT and OFFSET clauses
     *
     * @param int|NULL $limit
     * @param int|NULL $offset
     *
     * @return $this
     */
    public function limit(int $limit = null, int $offset = null)
    {
        $limit = is_null($limit)? \Site::$instance->config->per_page : $limit;
        $this->limits = !$limit ? '' : "LIMIT $limit" . ($offset ? " OFFSET $offset" : '');
        return $this;
    }

    private function processLimit(): string { return $this->limits ?? ''; }

    public static function lastInsertId() { return \Site::$instance->config->getDb()->lastInsertId(); }

    public function count(string $column, $distinct = false)
    {
        $column = $distinct ? "DISTINCT `$column`" : "`$column`";
        $q = "SELECT COUNT($column) FROM " . $this->getTableName() . " " . $this->processWhere();
        $q = $this->db($q);
        $q->execute($this->wheres);
        return $q->fetchColumn()[0];
    }

    public function delete($ids = [])
    {
        if (!empty($ids)) {
            $this->where($this->primary, 'IN', $ids);
        }
        $q = "DELETE FROM `{$this->getTableName()}` {$this->processWhere()}";
        return $this->db($q)->execute($this->wheres);
    }
}