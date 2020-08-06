<?php
/**
 *    AMXBans v7
 * Copyright 2018 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

/**
 * Class Route
 */
class Route
{
    private static $getRoutes = [];
    private static $postRoutes = [];
    private static $putRoutes = [];
    private static $deleteRoutes = [];
    private const resourceTpl = [
        ['type' => 'get', 'key' => '', 'exec' => 'index'],
        ['type' => 'get', 'key' => '/create', 'exec' => 'create'],
        ['type' => 'get', 'key' => '/{id}', 'exec' => 'view'],
        ['type' => 'get', 'key' => '/{id}/edit', 'exec' => 'edit'],
        ['type' => 'post', 'key' => '', 'exec' => 'store'],
        ['type' => 'put', 'key' => '/{id}', 'exec' => 'update'],
        ['type' => 'delete', 'key' => '/{id}', 'exec' => 'delete'],
    ];

    /**
     * @param string         $url
     * @param Closure|string $executor
     *
     * @throws Exception
     */
    public static function get(string $url, $executor): void
    {
        self::$getRoutes[$url] = self::resolveExecutor($executor);
    }

    /**
     * @param string         $url
     * @param Closure|string $executor
     *
     * @throws Exception
     */
    public static function post(string $url, $executor): void
    {
        self::$postRoutes[$url] = self::resolveExecutor($executor);
    }

    /**
     * @param string         $url
     * @param Closure|string $executor
     *
     * @throws Exception
     */
    public static function put(string $url, $executor): void
    {
        self::$putRoutes[$url] = self::resolveExecutor($executor);
    }

    /**
     * @param string         $url
     * @param Closure|string $executor
     *
     * @throws Exception
     */
    public static function delete(string $url, $executor): void
    {
        self::$deleteRoutes[$url] = self::resolveExecutor($executor);
    }

    /**
     * @param string $url
     * @param        $executor
     * @param array  $exclude
     * @param bool   $include
     *
     * @throws Exception
     */
    public static function resource(string $url, $executor, $exclude = [], $include = false): void
    {
        foreach (self::resourceTpl as $item) {
            [$type, $key, $append] = array_values($item);
            if ((!$include && !in_array($append, $exclude)) || ($include && in_array($append, $exclude))) {
                self::$type($url . $key, $executor . '@' . $append);
            }
        }
    }

    /**
     * @param $input
     *
     * @return Closure|array
     * @throws Exception
     */
    private static function resolveExecutor($input)
    {
        if ($input instanceof Closure) {
            return $input;
        }
        $class_method    = explode('@', $input);
        $class_method[0] = "Controllers\\" . $class_method[0];
        return $class_method;
    }

    public function getSite(string $method)
    {
//        var_dump(self::$getRoutes, self::$postRoutes, self::$putRoutes, self::$deleteRoutes);
        $method .= 'Routes';
        $url    = \Support\Path::getFakePathArray();
        $routes = array_keys(self::$$method);
        foreach ($routes as $route) {
            $args  = [];
            $route = explode('/', $route);
            if (count($route) !== count($url)) {
                continue;
            }
            for ($i = 0; $i < count($url); $i++) {
                if ($url[$i] != preg_replace('/{(\w+)(\??)}/', $url[$i], $route[$i])) {
                    break;
                } elseif (preg_match('/{(\w+)(\??)}/', $route[$i], $matches, PREG_UNMATCHED_AS_NULL)) {
                    $args[] = $url[$i];
                }
                if ($i + 1 === count($url)) {
                    return [self::${$method}[implode('/', $route)], $args];
                }
            }
        }
        header('HTTP/2.0 404 Not Found');
        exit;
    }

    /** @noinspection PhpIncludeInspection */
    public function __construct(string $routing)
    {
        include_once \Support\Path::getRootPath() . '/routes/' . $routing;
    }
}