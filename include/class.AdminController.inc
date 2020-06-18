<?php


use Models\Ban;
use Models\DB;
use Support\Path;

class AdminController
{
    private $section;
    private $method;
    protected $site;

    /**
     * AdminController constructor.
     *
     * @param Site   $site
     * @param string $method
     * @param string $section
     *
     * @throws Exception
     */
    public function __construct(Site $site, string $method, string $section)
    {
        $this->site = $site;
        $this->method = $method;
        $this->section = $section;

        // If there's any extra action needed, it has to be placed here for all the 'admin' sites

        ////////////

        if (method_exists($this, $section)) {
            $this->$section();
        } else {
            throw new Exception('Site "' . $section . '" not found');
        }
    }

    private function index()
    {
        if ($this->method !== 'get') {
            $this->navigateTo(AdminIndexController::class, Path::getFakePathWay(1));
        }

        switch (Path::getFakePathWay(1)) {
            case 'sys_info':
                //optimise tables
                if (isset($_GET["optimise"])) {
                    $tables = DB::selectRaw("SHOW TABLES FROM `" . $this->site->config->getDb(true) . "` LIKE ?",
                        [$this->site->config->dbPrefix . '_%'], null, PDO::FETCH_COLUMN);
                    $tables = implode('`, `', $tables);

                    $tables = DB::rawSQL("OPTIMIZE TABLES `$tables`");
                    if (!$tables) {
                        $this->site->config->output->append('messages',
                            ['type' => 'warning', 'text' => __LANG__['admin']['sys_info']['tables_not_optimised']]);
                    } else {
                        $this->site->config->output->append('messages',
                            ['type' => 'success', 'text' => __LANG__['admin']['sys_info']['tables_optimised']]);
                    }
                    db_log('Web config', 'Optimised tables ' . $tables ? 'successfully' : 'NOT successfully');
                }

                //prune db
                if (isset($_GET["prune"]) && Auth::hasPermission('prune_db')) {
                    /** @var Ban[] $bans */
                    $bans = Ban::query()->where('expired', 0)->select(['bid', 'ban_created', 'ban_length']);
                    $pruned = 0;
                    foreach ($bans as $ban) {
                        $tz = $ban->server->timezone_fixx * 3600;
                        $bl = $ban->ban_length * 60;
                        //prune expired bans
                        if ($ban->ban_created + $tz + $bl < time() && $bl) {
                            $pruned++;
                            $ban->expired = true;
                            $ban->save();

                            db_bans_log($ban, '--SYSTEM--', 'Bantime expired', $ban->ban_created + $tz + $bl);
                        }
                    }
                    $this->site->config->output->assign(compact('pruned'));
                    $this->site->config->output->append('messages',
                        ['type' => 'success', 'text' => __LANG__['admin']['sys_info']['bans_pruned']]);
                    db_log('Web config', 'Pruned bans');
                }

                $php = [
                    "display_errors"      => toBool(ini_get('display_errors')),
                    "post_max_size"       => ini_get('post_max_size') . " (" . return_bytes(ini_get('post_max_size')) . " bytes)",
                    "upload_max_filesize" => ini_get('upload_max_filesize') . " (" . return_bytes(ini_get('upload_max_filesize')) . " B)",
                    "max_execution_time"  => ini_get('max_execution_time'),
                    "version_php"         => phpversion(),
                    'version_mysql'       => DB::selectRaw('SELECT VERSION();', null, null, PDO::FETCH_COLUMN)[0],
                    "server_software"     => $_SERVER["SERVER_SOFTWARE"],
                    "bc-gmp"              => (extension_loaded('bcmath') OR extension_loaded('gmp')) ? __LANG__['yes'] : __LANG__['no'],
                    "gd"                  => extension_loaded('gd') ? gd_info()['GD Version'] : false,
                ];
                $this->site->config->output->assign(compact('php'));

                /* TODO WEBSITE SETTINGS (web/settings): move this action to there
                        //clear smarty cache
                        if (isset($_POST["clear"]) && $_SESSION["loggedin"]) {
                            //special function available from smarty
                            $smarty->clear_compiled_tpl();
                            $user_msg = "_CACHEDELETED";
                        }*/
                /* TODO: v7.1
                        //repair files db
                        if (isset($_POST["file_repair"]) && $_SESSION["loggedin"]) {
                            $repaired = sql_get_files_count_fail(1);
                        }
                        //repair comments db
                        if (isset($_POST["comment_repair"]) && $_SESSION["loggedin"]) {
                            $repaired = sql_get_comments_count_fail(1);
                        }*/

                $this->site->config->output->assign([
                    'bans'          => [
                        'total'  => Ban::query()->count('bid'),
                        'active' => Ban::query()->where('expired', false)->count('bid'),
                    ],
                    'db_size'       => format_size(db_size()),
                    'prune'         => $this->site->config->prune_bans,
                    'comment_count' => \Models\Comment::query(\Models\Comment::COMMENTS)->count('id'),
                    'file_count'    => \Models\Comment::query(\Models\Comment::FILES)->count('id'),
                ]);
                $this->site->config->output->display('admin.index.sys_info');
                break;
            case 'ban_add':
                $this->site->config->output->assign('reasons',
                    Models\DB::table('reasons')->select(['id', 'reason'], PDO::FETCH_KEY_PAIR));
                $this->site->config->output->display('admin.index.ban_add');
                break;
        }
    }

    private function navigateTo($class, $site)
    {
        new $class($this->site, $this->method, $site);
    }
}