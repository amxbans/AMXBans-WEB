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

namespace Support;

/**
 * Class Route
 *
 * Simplified tool of the most routing systems.
 */
class Path
{
    /**
     * Example: https://example.com/realPath/index.php/this/is/path => array('this', 'is', 'path')
     *
     * @return array
     */
    public static function getFakePathArray(): array { return explode('/', self::getFakePath()); }

    /**
     * Makes an internal URL with given parameters for fake path.
     *
     * @param string      $fakePath
     * @param string|null $php
     * @param string|null $real_path
     *
     * @return string
     */
    public static function makeURL(string $fakePath, string $php = null, string $real_path = null): string
    {
        if ($real_path || $php) {
            $php = $php ?? array_pop(explode('/', self::getURL()));
            return str_replace(DIRECTORY_SEPARATOR . '/', '/',
                Path::getBaseURL() . $real_path . '/' . $php . '/' . $fakePath);
        }
        return self::getURL() . '/' . $fakePath;
    }

    /**
     * @param int $index
     *
     * @return string
     */
    public static function getFakePathWay(int $index = 0) { return @self::getFakePathArray()[$index]; }

    /**
     * Example: https://example.com/realPath/index.php/this/is/path => this/is/path
     *
     * @return string
     */
    public static function getFakePath(): string { return substr($_SERVER['PATH_INFO'] ?? '/', 1); }

    /**
     * Example: /var/www/amxbans/include => /var/www/amxbans
     *
     * @return string
     */
    public static function getRootPath(): string { return dirname(__DIR__, 2); }

    /**
     * Example: https://example.com/realPath/index.php/this/is/path => /realPath/index.php
     *
     * @return string
     */
    public static function getURL(): string { return $_SERVER['SCRIPT_NAME']; }

    /**
     * Example: https://example.com/realPath/index.php/this/is/path => /realPath
     *
     * @return string
     */
    public static function getBaseURL(): string { return dirname(self::getURL()); }
}