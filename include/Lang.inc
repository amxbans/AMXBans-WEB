<?php


class Lang
{
    public static $supported = [];
    public static $lang = 'english';
    public static $properties = [
        'name'           => '',
        'locale'         => '',
        'html_direction' => '',
        'date_format'    => '',
    ];

    private static $library = [];
    private static $default = [];

    public static function init(bool $install = false, string $default = 'english')
    {
        self::$supported = require __DIR__ . '/../' . ($install ? 'install/' : '') .
            'language/languages.php';

        //save current language to session
        if (!isset($_SESSION["lang"])) {
            $_SESSION["lang"] = $install ? 'english' : ($_COOKIE['lang'] ?? $default);
        }
        if (isset($_GET['lang'])) {
            setcookie('lang', $_SESSION['lang'] = $_GET['lang'], 3600 * 24 * 7, \Support\Path::getBaseURL());
        }
        self::$lang = $_SESSION['lang'];
        self::$properties = self::$supported[self::$lang];

        $file = \Support\Path::getRootPath() . ($install ? '/install' : '') . '/language/' . $_SESSION['lang'] . '.php';
        if (file_exists($file) && basename($file) != 'languages.php') {
            self::$library = require $file;
        } else {
            self::$library = require __DIR__ . '/../language/english.php';
        }
        self::$default = require __DIR__ . '/../language/english.php';
    }

    public static function get(string $key)
    {
        //TODO: remove when all v7.0 done
        if ($key[0] == '_') {
            return $key;
        }
        return @self::$library[$key] ?: self::$default[$key];
    }
}