<?php


use Models\Ban;
use Models\DB;

class AdminController
{
    private $site;
    private $method;
    protected $config;

    /**
     * AdminController constructor.
     *
     * @param Site   $config
     * @param string $method
     * @param string $site
     *
     * @throws Exception
     */
    public function __construct (Site $config, string $method, string $site)
    {
        $this->config = $config;
        $this->method = $method;
        $this->site = $site;

        // If there's any extra action needed, it has to be placed here for all the 'admin' sites

        ////////////

        if (method_exists($this, $site))
            $this->$site();
        else
            throw new Exception('Site "' . $site . '" not found');
    }

    private function index ()
    {
        if ($this->method !== 'get')
            $this->navigateTo(AdminIndexController::class, Route::getFakePathWay(1));

        switch (Route::getFakePathWay(1)) {
            case 'sys_info':
                //optimize tables
                if (isset($_GET["optimize"])) {
                    $tables = DB::selectRaw("SHOW TABLES FROM `" . $this->config->config->getDb(TRUE) . "` LIKE ?", [$this->config->config->dbPrefix . '_%'], null, PDO::FETCH_COLUMN);
                    $tables = implode('`, `', $tables);

                    $tables = DB::rawSQL("OPTIMIZE TABLES `$tables`");
                    if (!$tables)
                        $this->config->config->output->append('messages', ['type' => 'warning', 'text' => __LANG__['admin']['sys_info']['tables_not_optimised']]);
                    else
                        $this->config->config->output->append('messages', ['type' => 'success', 'text' => __LANG__['admin']['sys_info']['tables_optimised']]);
                    db_log('Web config', 'Optimised tables ' . $tables ? 'successfully' : 'NOT successfully');
                }

                //prune db
                if (isset($_GET["prune"]) && User::hasPermission('prune_db')) {
                    $bans = Ban::query()->where('expired', 0)->select(['bid', 'ban_created', 'ban_length']);
                    $tables = $mysql->query("SELECT ba.bid,ba.ban_created,ba.ban_length,se.timezone_fixx FROM " . $config->db_prefix . "_bans as ba 
							LEFT JOIN " . $config->db_prefix . "_serverinfo AS se ON ba.server_ip=se.address WHERE ba.expired=0");
                    $pruned = 0;
                    foreach ($bans as $ban) {
                        //TODO: Get timezone-fix and do calculations as below
                            //prune expired bans
                            if (($result->ban_created + ($result->timezone_fixx * 60 * 60) + ($result->ban_length * 60)) < time() && $result->ban_length != "0") {
                                $pruned++;
                                $prune_query = $mysql->query("UPDATE `" . $config->db_prefix . "_bans` SET `expired`=1 WHERE `bid`=" . $result->bid);
                                $prune_query = $mysql->query("INSERT INTO `" . $config->db_prefix . "_bans_edit` (`bid`,`edit_time`,`admin_nick`,`edit_reason`) VALUES (
								'" . $result->bid . "','" . ($result->ban_created + ($result->timezone_fixx * 60 * 60) + ($result->ban_length * 60)) . "','amxbans','Bantime expired')");
                            }
                        $smarty->assign("prunecount", $pruned);
                        $user_msg = "_DBPRUNED";
                    }
                }

                @$gd = gd_info();
                $gd_version = $gd["GD Version"];
                $php_settings = array(
                    "display_errors" => (ini_get('display_errors') == "") ? "off" : ini_get('display_errors'),
                    "register_globals" => (ini_get('register_globals') == 1 || ini_get('register_globals') == "on") ? "_ON" : "_OFF",
                    "magic_quotes_gpc" => (get_magic_quotes_gpc() == true) ? "_ON" : "_OFF",
                    "safe_mode" => (ini_get('safe_mode') == 1 || ini_get('safe_mode') == "on") ? "_ON" : "_OFF",
                    "post_max_size" => ini_get('post_max_size') . " (" . return_bytes(ini_get('post_max_size')) . " bytes)",
                    "upload_max_filesize" => ini_get('upload_max_filesize') . " (" . return_bytes(ini_get('upload_max_filesize')) . " bytes)",
                    "max_execution_time" => ini_get('max_execution_time'),
                    "version_php" => phpversion(),
                    "version_amxbans_web" => $config->v_web,
                    "server_software" => $_SERVER["SERVER_SOFTWARE"],
                    "mysql_version" => mysqli_get_client_info(),
                    "bcmath" => (extension_loaded('bcmath') == "1") ? "_YES" : "_NO",
                    "gmp" => (extension_loaded('gmp') == "1") ? "_YES" : "_NO",
                    "gd" => (extension_loaded('gd') == "1") ? "_YES" : "_NO",
                    "version_gd" => $gd_version
                );
                $smarty->assign("php_settings", $php_settings);

                //clear smarty cache
                if (isset($_POST["clear"]) && $_SESSION["loggedin"]) {
                    //special function available from smarty
                    $smarty->clear_compiled_tpl();
                    $user_msg = "_CACHEDELETED";
                }
                //repair files db
                if (isset($_POST["file_repair"]) && $_SESSION["loggedin"]) {
                    $repaired = sql_get_files_count_fail(1);
                }
                //repair comments db
                if (isset($_POST["comment_repair"]) && $_SESSION["loggedin"]) {
                    $repaired = sql_get_comments_count_fail(1);
                }
                $smarty->assign("bans", array("count" => sql_get_bans_count(0), "activ" => sql_get_bans_count(1)));
                $smarty->assign("db_size", format_size(db_size()));
                $smarty->assign("auto_prune", $config->auto_prune);
                $smarty->assign("comment_count", array("count" => sql_get_comments_count(0), "fail" => sql_get_comments_count_fail(0)));
                $smarty->assign("file_count", array("count" => sql_get_files_count(0), "fail" => sql_get_files_count_fail(0)));
                $smarty->assign("msg", $user_msg);
                $this->config->config->output->assign('');
                break;
        }
    }

    private function navigateTo ($class, $site)
    {
        new $class($this->config, $this->method, $site);
    }
}