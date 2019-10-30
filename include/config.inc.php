<?php
/*
		AMXBans v7
	Copyright 2018 by indianiso1
	This file is part of AMXBans.

	AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
	AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	You should have received a copy of the cc-nC-SA along with AMXBans.
	If not, see <http://creativecommons.org/licenses/by-nc-sa/2.0/>.
*/




//load smilies to global array
if (empty($smilies))
{
	$sql = $mysql->query("SELECT code, url, name FROM " . $config->db_prefix . "_smilies ORDER BY id");
	while (list($code, $url, $name) = $sql->fetch_array())
	{
		$name = stripslashes($name);
		$name = htmlentities($name);
		$smilies[] = [$code, $url, $name];
	}
}

//load bbcode tags to global array
if (empty($bbcodes))
{
	$sql = $mysql->query("SELECT open_tag, close_tag, url, name FROM " . $config->db_prefix . "_bbcode ORDER BY id");
	while (list($open_tag, $close_tag, $url, $name) = $sql->fetch_array())
	{
		$name = stripslashes($name);
		$name = htmlentities($name);
		$bbcodes[] = [$open_tag, $close_tag, $url, $name];
	}
}

/* Smarty settings */
define("SMARTY_DIR", $config->path_root . "/include/smarty/");

require_once(SMARTY_DIR . "Smarty.class.php");

class dynamicPage extends Smarty
{
	function __construct()
	{
		
		global $config;
		parent::__construct();
		
		$this->template_dir = $config->templatedir;
		$this->compile_dir = SMARTY_DIR . "templates_c/";
		$this->config_dir = SMARTY_DIR . "configs/";
		$this->cache_dir = SMARTY_DIR . "cache/";
		$this->caching = FALSE;
		
		//for editing templates it's better "true", but slow down site load
		$this->force_compile = FALSE;
		
		$this->assign("app_name", "dynamicPage");
	}
}