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
}