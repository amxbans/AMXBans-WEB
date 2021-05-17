<?php


class DB extends PDO
{
    /** @var stdClass */
    protected $credentials;

    /** @var string */
    public $prefix = '';

    public function __construct($dsn = null, $username = null, $passwd = null, $options = null)
    {
        $this->credentials = require "db.Config.inc";
        $this->prefix = (string)$this->credentials->prefix;
        try {
            parent::__construct("mysql:dbname={$this->credentials->name};host={$this->credentials->host}",
                $this->credentials->user, $this->credentials->pass);
            $this->exec("SET CHARSET utf8");
        } catch (PDOException $e) {
            trigger_error($e->getMessage());
        }
    }

    public function getDbName()
    {
        return $this->credentials->name;
    }

    public function getSize()
    {
        $q = $this->prepare("SHOW TABLE STATUS FROM `{$this->credentials->name}` LIKE '{$this->prefix}_%'");
        if (!$q->execute()) {
            return false;
        }

        $db_size = 0;
        while ($value = $q->fetch(parent::FETCH_ASSOC)) {
            $db_size += $value["Data_length"] + $value['Index_length'];
        }
        return $db_size;
    }
}