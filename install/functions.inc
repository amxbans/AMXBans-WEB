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

function toBool($value): bool
{
	if ($value === 'on' OR $value === 'On' OR $value == 'Yes' OR $value == 'yes' OR $value > 0 or $value == TRUE)
		return TRUE;

	return FALSE;
}

function sql_has_all_privileges(PDO $db): bool
{
	//global privileges
	$query = $db->prepare("SHOW GRANTS FOR CURRENT_USER()");
	$query->execute();
	$db_db = $_SESSION["db_name"];
	foreach ($query->fetchAll() as $v)
	{
	    $v = $v[0];
		if (stristr($v, $db_db) || stristr($v, "*.*"))
		{
			if (stristr($v, "ALL PRIVILEGES"))
				return TRUE;
			elseif (stristr($v, "SELECT") && stristr($v, "INSERT") && stristr($v, "UPDATE") &&
				stristr($v, "DELETE") && stristr($v, "CREATE"))
				return TRUE;
		}
	}

	return FALSE;
}