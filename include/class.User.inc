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

class User
{
	public $data;
	public $logged = FALSE;
	public $banned = FALSE;

	protected $db;

	/**
	 * User constructor.
	 * @param PDO $PDO
	 */
	public function __construct(PDO $PDO)
	{
		$this->db = $PDO;

		// CHECK LOGIN
		if (isSet ($_SESSION['unID']))
			$id = (int)$_SESSION['unID'];
		else if (self::hasCookie())
			$id = (int)$_COOKIE['unID'];

		$user = $this->db->prepare("SELECT * FROM table WHERE unique_id=?");
		$user->execute([@$id]);

		if ($user->rowCount() === 1)
		{
			$this->data = $user->fetch(PDO::FETCH_ASSOC);
			$this->logged = TRUE;
			if ($this->data['banned'] === 0 OR $this->data['banned'] > time())
				$this->banned = TRUE;
		}
	}

	/**
	 * @param string $name Username
	 * @param string $pass Password
	 * @param bool   $rem  Remember (as cookie) or not
	 * @param string $from Send back user to place they came from (by default - homepage)
	 * @return string
	 */
	public function loginInternal($name, $pass, bool $rem = FALSE, string $from = '')
	{
		$user = "SELECT * FROM userTable WHERE";
		if (CONFIG['login_type'] == 1)
			$user .= " `email=:name`";
		elseif (CONFIG['login_type'] == 2)
			$user .= " `name`=:name OR email=:name";
		else
			$user .= " `name=:name`";

		try
		{
			$user = $this->db->prepare($user);
			$user->execute(['name' => $name]);
		} catch (PDOException $e)
		{
			return msg::error();
		}

		if ($user->rowCount() === 1 AND password_verify($pass, $user->fetch()['pass']))
		{
			if ($rem)
				setcookie('unID', $user->fetch()['unique_id'], CONFIG['login_remember_time'], '', '', FALSE, TRUE);
			else
				$_SESSION['unID'] = $user->fetch()['unique_id'];
			header('Location: ' . CONFIG['HOME_URL'] . $from);
		}
		else
			return msg::warn(lang('LOGIN_FAILED', 'ERRORS'));
	}

	public static function hasCookie(string $what = 'unID'): bool
	{
		if (is_array($what))
		{
			foreach ($what as $value)
			{
				if (!isset($_COOKIE[$value]))
					return FALSE;
			}
			return TRUE;
		}
		else
			return isset($_COOKIE[$what]);
	}
}