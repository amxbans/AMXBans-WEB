<?php
/*
		AMXBans v7

	Copyright 2018 by indianiso1
	This file is part of AMXBans.
	AMXBans is free software, but it's licensed under the
	Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
	AMXBans is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	You should have received a copy of the cc-nC-SA along with AMXBans.
	If not, see <http://creativecommons.org/licenses/by-nc-sa/2.0/>.
*/
/**
 * Class Route
 *
 * Simplified tool of the most routing systems.
 */
class Route
{
	private static $routes = [];
	private static $module;
	private static $PATH;
	private static $strPATH;
	private static $URL;
	private static $baseURL;
	
	public static function init()
	{
		self::$URL = $_SERVER['SCRIPT_NAME'];
		self::$baseURL = str_replace("/index.php", "", self::getURL());
		
		$PATH = isset($_SERVER['PATH_INFO']) ? $_SERVER['PATH_INFO'] : '/';
		$PATH = substr($PATH, 1);
		self::$strPATH = $PATH;
		self::$PATH = explode('/', $PATH);
		
		self::$module = self::$PATH[0] ?: 'home';
		return self::moduleExec();
	}
	
	/**
	 * Example: https://example.com/realPath/index.php/this/is/path => this
	 * @return string
	 */
	public static function getModule()
	{
		return self::$module;
	}
	
	/**
	 * Example: https://example.com/realPath/index.php/this/is/path => array('this', 'is', 'path')
	 * @return array
	 */
	public static function getPATH()
	{
		return self::$PATH;
	}
	
	/**
	 * Example: https://example.com/realPath/index.php/this/is/path => this/is/path
	 * @return string
	 */
	public static function getStrPATH()
	{
		return self::$strPATH;
	}
	
	/**
	 * Example: https://example.com/realPath/index.php/this/is/path => /realPath/index.php
	 * @return string
	 */
	public static function getURL()
	{
		return self::$URL;
	}
	
	/**
	 * Example: https://example.com/realPath/index.php/this/is/path => /realPath
	 * @return string
	 */
	public static function getBaseURL()
	{
		return self::$baseURL;
	}
	
	/**
	 * @param string $route
	 * @param string $ext
	 */
	public static function setRoute($route, $ext = NULL)
	{
		self::$routes[$route] = $ext;
	}
	
	/**
	 * Executes pre-defined scripts when in section and returns template path+name to be shown.
	 * @return string
	 */
	private static function moduleExec()
	{
		// TODO: Create config class
		if (in_array(self::getStrPATH(), self::$routes))
		{
			if (file_exists(self::getBaseURL() .'/include/pages/' . self::getStrPATH() .'.php'))
				//TODO: Finish inclusion
			return self::getStrPATH() . '.tpl';
		}
		else
			return Config::getHomepage() .'.tpl';
	}
}