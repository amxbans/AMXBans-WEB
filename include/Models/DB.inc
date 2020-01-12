<?php


namespace Models;


use PDO;

class DB
{
    protected $table = '';
    protected $primary = 'id';

    protected $wheres = [];
    protected $limits;

    /**
     * @return static
     */
    public static function query () {
        return new static();
    }


    /**
     * @param string|array $columns
     * @param int|null     $type
     * @return array
     */
    public static function all ($columns = '*', $type = NULL): array {
        return static::query()->get($columns, $type);
    }

    /**
     * @param string|array $columns
     * @param int|null     $type
     * @return array
     */
    public function get ($columns = '*', $type = NULL): array {
        if (is_null($type))
            $type = PDO::FETCH_CLASS;
        if ($columns != '*' OR is_array($columns))
            $columns = '`' . implode('`, `', is_array($columns) ? $columns : [ $columns ]) . '`';

        $sql = "SELECT $columns FROM " . $this->getTableName() . " " . $this->processWhere() . ' ' . $this->processLimit();
        var_dump($sql);
        $sql = $this->db($sql);
        $sql->execute(empty($this->wheres) ? NULL : $this->wheres);

        return $sql->fetchAll($type, static::class);
    }

    /**
     * @param        $id
     * @param string $columns
     * @param null   $type
     * @return mixed
     */
    public static function find ($id, $columns = '*', $type = NULL) {
        $q = new static();
        $qq = $q->where($q->primary, $id)->limit(1)->get($columns, $type);
        return $qq[0] ?? new static();
    }

    private function getTableName () {
        global $config;
        return $config->dbPrefix . '_' . $this->table;
    }

    protected function db ($query) {
        global $config;
        return $config->getDb()->prepare($query);
    }


    /**
     * @param callable|string $field
     * @param string|null     $operator
     * @param string|null     $value
     * @param string          $pre
     * @return $this
     */
    public function where ($field, $operator = NULL, $value = NULL, $pre = 'AND'): self {
        $pre = strtoupper($pre);
        if (is_callable($field)) {
            $this->wheres[] = [ $pre, $field(new DB())->getWheres() ];
            return $this;
        }
        if (!in_array($operator, sql_operators()))
            [ $value, $operator ] = [ $operator, '=' ];
        if (is_null($value) && in_array($operator, sql_operators()) && !in_array($operator, [ '=', '<>', '!=' ]))
            $operator = $operator == '=' ? 'IS' : 'IS NOT';
        $this->wheres[] = [ $pre, $field, $operator, $value ];
        return $this;
    }

    /**
     * @param array|null $wheres
     * @return string
     */
    private function processWhere ($wheres = NULL): string {
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
            if (is_null($where[3]))
                $w .= "$where[0] `$where[1]` $where[2] $where[3]";
            else {
                $this->wheres[$word = 'w_' . substr(uniqid(), -3)] = $where[3];
                $w .= "$where[0] `$where[1]` $where[2] :$word";
            }
        }
        var_dump($this->wheres);
        return "WHERE" . substr($w, strpos($w, ' '));
    }

    /**
     * @return array
     */
    public function getWheres (): array {
        return $this->wheres;
    }

    public function limit (int $limit, int $offset = NULL) {
        $this->limits = "LIMIT $limit" . ($offset ? " OFFSET $offset" : '');
        return $this;
    }

    private function processLimit (): string {
        return $this->limits;
    }
}