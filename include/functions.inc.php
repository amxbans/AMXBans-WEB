<?php
/**
 *    AMXBans v7
 * Copyright 2018 by SeToY & |PJ|ShOrTy, indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

/**
 * @param string $action
 * @param string $context
 * @param string|null   $user
 */
function db_log(string $action, string $context, $user = NULL): void
{
    global $config;
    $q = $config->getDb()->prepare("INSERT INTO `{$config->dbPrefix}_logs` (ip, username, action, remarks) VALUES (?, ?, ?, ?)");
    $q->execute([$_SERVER['REMOTE_ADDR'], $user ?? User::get('username'), $action, $context]);
}