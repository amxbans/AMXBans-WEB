<?php


namespace Models;


use Exception;
use Rcon;
use Support\Model;

/**
 * Class Server
 *
 * @package Models
 *
 * @property int         $id
 * @property int|null    $timestamp
 * @property string|null $hostname
 * @property string|null $address
 * @property string|null $gametype
 * @property string|null $rcon
 * @property string|null $amxban_version
 * @property string|null $amxban_motd
 * @property int|null    $motd_delay
 * @property int         $amxban_menu
 * @property int|null    $reasons
 * @property int         $timezone_fixx
 */
class Server extends Model
{
    protected $table = 'serverinfo';
    protected const relations = [
        'bans' => [1, 'Models\Ban', 'address', 'server_ip'],
    ];
    private $liveInfo;

    public function liveInfo (string $what)
    {
        if (!$this->exists)
            return false;
        if (isset($this->liveInfo[$what]))
            return $this->liveInfo[$what];

        [$ip, $port] = explode(':', $this->address);
        $rcon           = new Rcon($ip, $port, $this->rcon);
        $this->liveInfo = $rcon->publicInfo();
        unset($rcon);
        return $this->liveInfo[$what];
    }

    public function testConnection (): bool
    {
        if (!$this->exists)
            return false;
        [$ip, $port] = explode(':', $this->address);
        try {
            new Rcon($ip, $port, $this->rcon);
            return true;
        } catch (Exception $e) {
            return false;
        }
    }
}