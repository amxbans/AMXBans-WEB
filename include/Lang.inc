<?php


use Support\Path;

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

    public static function init(bool $install = false, string $default = 'english'): void
    {
        self::$supported = require Path::getRootPath() . DIRECTORY_SEPARATOR . ($install ? 'install/' : '') . 'language/languages.php';

        //save current language to session
        if (!isset($_SESSION["lang"])) {
            $_SESSION["lang"] = $install ? 'english' : ($_COOKIE['lang'] ?? $default);
        }
        if (isset($_GET['lang'])) {
            setcookie('lang', $_SESSION['lang'] = $_GET['lang'], 3600 * 24 * 7, Path::getBaseURL());
        }
        self::$lang       = $_SESSION['lang'];
        self::$properties = self::$supported[self::$lang];

        $file = Path::getRootPath() . ($install ? '/install' : '') . '/language/' . $_SESSION['lang'] . '.php';
        if (file_exists($file) && basename($file) != 'languages.php') {
            self::$library = require $file;
        } else {
            self::$library = require __DIR__ . '/../language/english.php';
        }
        self::$default = require __DIR__ . '/../language/english.php';
    }

    /**
     * Gets a localised data (string or array)
     * Allows dot (.) notation
     *
     * @param string $key
     *
     * @return string|array
     */
    public static function get(string $key)
    {
        //TODO: remove when all v7.0 done
        if ($key[0] == '_') {
            return $key;
        }

        // TODO: remove when all v7.0 done
        // For a testing purposes - check which strings are not being used
        static::registerKey($key);
        //


        if (strpos($key, ".")) {
            $parts = explode(".", $key);
            $last  = array_pop($parts);
            return static::get(implode(".", $parts))[$last];
        }

        return @self::$library[$key] ?: self::$default[$key];
    }

    private static function registerKey($key)
    {
        $fileName = Path::getRootPath() . DIRECTORY_SEPARATOR . 'language' . DIRECTORY_SEPARATOR . 'stringUsage.json';
        if (!file_exists($fileName)) {
            self::makeLangRegistry($fileName);
        }
        $data = json_decode(file_get_contents($fileName), true);
        self::registerLeveledKey($key, $data);
        file_put_contents($fileName, json_encode($data, JSON_PRETTY_PRINT));
    }

    private static function makeLangRegistry($file)
    {
        $data = self::getValueForRegistry(static::$default);
        $data = json_encode($data, JSON_PRETTY_PRINT);
        file_put_contents($file, $data, LOCK_EX);
    }

    private static function getValueForRegistry($item)
    {
        if (is_array($item)) {
            foreach ($item as $key => $subItem) {
                $output[$key] = self::getValueForRegistry($subItem);
            }
            return $output ?? false;
        }

        return false;
    }

    private static function registerLeveledKey($key, &$data)
    {
        if (strpos($key, ".")) {
            $parts = explode(".", $key);
            $first = array_shift($parts);
            if (!array_key_exists($first, $data)) {
                if (count($parts) < 2) {
                    $data[$first] = "registered, no key in registry";
                    return;
                }
                $data[$first] = [];
            }
            static::registerLeveledKey(implode(".", $parts), $data[$first]);
            return;
        }

        if (is_bool($data[$key])) {
            $data[$key] = true;
        }
    }
}