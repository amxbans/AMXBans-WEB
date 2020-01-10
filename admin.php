<?php
/**
 *    AMXBans v7
 * Copyright 2009, 2010 by SeToY & |PJ|ShOrTy, 2019 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

session_start();
require_once "include/class.Config.inc";
$config = new Config;

//TODO: if (!User::$logged)
//	header('Location: ' . Route::makeURL(Config::start_pages[$config->start_page], 'index.php'));

Site::build($config);