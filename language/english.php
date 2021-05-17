<?php

/**
 * Language: English (UK)
 * Author Notes:
 * *
 */
return [
//default

    'shortseconds'     => 'sec',
    'loadtime'         => 'Page generated in',
    'bansindb'         => 'Bans in database',
    'by'               => 'by',
    'or'               => 'or',
    'on'               => 'on',
    'off'              => 'off',
    'yes'              => 'yes',
    'no'               => 'no',
    'own'              => 'own',
    'clear'            => 'Reset',
    'opensteamcomsite' => 'Visit Steam Community page',
    'adminarea'        => 'Admin area',
    'nosite'           => 'Page not available!',
    'delete'          => 'Delete',
    'add'             => 'Add',
    'edit'            => 'Edit',
    'editing'         => 'Editing',
    'defaultlang'     => 'Default Language',
    'other'           => 'Others',
    'viewip'          => 'Show IP',
    'level'           => 'Level',
    'details'         => 'Show Details',
    'systemsettings'  => 'System',
    'viewsettings'    => 'View',
    'commentsettings' => 'Comments',
    'filesettings'    => 'Files',
    'banlistsettings' => 'Ban list',
    'configuration'   => 'Configuration',
    'repair'          => 'Repair',
    'auto'            => 'Automatic',
    'test'            => 'Test',
    'empty'           => 'Nothing in here...',
    'send'            => 'Send',
    // NEW IN v7.0
    'add_new'         => 'Add new',


//user menu

    'home'        => 'Main page',
    'menu'        => ['bans', 'servers', 'admins', 'search'],
    'menu_titles' => [
        'ban'     => 'Ban details',
        'bans'    => 'Ban list',
        'servers' => 'Server list',
        'admins'  => 'Admin list',
        'search'  => 'Search',
        'login'   => 'Log in',
    ],

//info amxaccess

    'info_access'       => 'Access info',
    'accessflags'       => 'Access Flags',
    'access_title'      => 'Access permissions',
    'access_flags'      => [
        'a - Immunity (cannot be kicked/banned etc.)',
        'b - Reserved slots (can use reserved slots)',
        'c - amx_kick command',
        'd - amx_ban and amx_unban commands',
        'e - amx_slay and amx_slap commands',
        'f - amx_map command',
        'g - amx_cvar command (not all CVARs available)',
        'h - amx_cfg command',
        'i - amx_chat and other chat commands',
        'j - amx_vote and other vote commands',
        'k - Access to sv_password cvar (through amx_cvar command)',
        'l - Access to amx_rcon command and rcon_password cvar (through amx_cvar command)',
        'm - User defined Level A (for other plugins)',
        'n - User defined Level B',
        'o - User defined Level C',
        'p - User defined Level D',
        'q - User defined Level E',
        'r - User defined Level F',
        's - User defined Level G',
        't - User defined Level H',
        'u - Menu access',
        'z - User (not admin)',
    ],
    'addadmintoservers' => 'Add admin to server',
    'withstaticbantime' => 'with static ban time',


//main header

    'logged'    => 'Logged in as',
    'notlogged' => 'Not logged in',
    'logout'    => 'Log out',
    'login'     => 'Log in',


//ban list

    'date'        => 'Date',
    'player'      => 'Player',
    'admin'       => 'Admin',
    'reason'      => 'Reason',
    'length'      => 'Length',
    'site'        => 'Page',
    'bans'        => 'Bans',
    'bl_comments' => 'Comments', // Useless?
    'files'       => 'Files',
    'bl_kicks'    => 'Kicks',
    'to'          => 'to',
    'year'        => 'Year',
    'years'       => 'Years',
    'month'       => 'Month',
    'months'      => 'Months',
    'week'        => 'Week',
    'weeks'       => 'Weeks',
    'day'         => 'Day',
    'days'        => 'Days',
    'hour'        => 'Hour',
    'hours'       => 'Hours',
    'min'         => 'Minute',
    'mins'        => 'Minutes',
    'of'          => 'of',
    'remaining'   => 'remaining',

//ban list details

    'permanent'           => 'Permanent',
    'bandetails'          => 'Ban details',
    // NEW IN v7.0
    'ban_types'           => [
        'S'  => 'SteamID',
        'I'  => 'IP',
        'SI' => 'SteamID & IP',
        'IS' => 'SteamID & IP',
        ''   => 'Not defined',
    ],
    'steamid'             => 'SteamID',
    'steamcomid'          => 'Steam Community ID',
    // NEW IN v7.0
    'server'              => 'Server',
    'notavailable'        => 'Not Available',
    'nosteamid'           => 'no SteamID',
    'hidden'              => 'hidden',
    'invoked'             => 'Invoked on',
    'banlenght'           => 'Ban length',
    'expires'             => 'Expires on',
    'notapplicable'       => 'Not applicable',
    'expired'             => 'expired',
    'ip'                  => 'IP address',
    'ban_type'            => 'Ban type',
    // NEW IN v7.0
    'times_banned'        => 'Times banned',
    'banby'               => 'Banned by',
    'banon'               => 'Banned on',
    'file_typenotallowed' => 'File type not allowed',
    'from'                => 'from',
    'download'            => 'Download',
    'downloads'           => 'Downloads',
    'file'                => 'File',
    'newfile'             => 'New File',
    'comment'             => 'Comment',
    'comments'            => 'Comments',
    // NEW IN v7.0
    'list_comment'        => 'made a comment',
    // NEW IN v7.0
    'list_file'           => 'uploaded a file',
    // NEW IN v7.0
    'list_comment_file'   => 'uploaded a file with comment',
    'newcomment'          => 'New comment',
    'no_comments'         => 'No comments',
    'back'                => 'Back',
    'tip_edit'            => 'Edit',
    'tip_del'             => 'Delete',
    'tip_download'        => 'Download',
    'tip_back'            => 'Back',
    'tip_sendmail'        => 'Send E-mail',
    'email'               => 'E-mail',
    'fileupload'          => 'Upload file',
    'upload'              => 'Upload',
    'entryedit'           => 'Edit entry',
    'editban'             => 'Edit ban',
    'totalexpbans'        => 'Total expired bans',
    'editcomment'         => 'Edit comment',
    'add_comment'         => 'Add comment',
    'nofiles'             => 'No files',
    'bandetailsedits'     => 'Changes in past',
    'edit_reason'         => 'Editing reason',
    'unban_player'        => 'Unban',
    'unbanned'            => 'Unbanned',
    'banhistory'          => 'Ban history',
    // NEW IN v7.0
    'edit_history'        => 'Edit history',
    // NEW IN v7.0
    'comments_files'      => 'Comments & Files',
    // NEW IN v7.0
    'captcha_placeholder' => 'Rewrite captcha here',
    // NEW IN v7.0
    'share_ban'           => 'Share ban details',


//Login

    'username'      => 'Username',
    'password'      => 'Password',
    'remember'      => 'Remember my login',
    'login_blocked' => 'Blocked login',
    'loginfailed'   => 'Login failed!',
    'logintry'      => 'Try',
    'sec'           => 'Second',
    'secs'          => 'Seconds',


//admins amxx

    'amxadminsettings' => 'AMX Mod X admin administration',
    'name'             => 'Name',
    'nickname'         => 'Nickname',
    'manageamxadmins'  => 'AMX Mod X admins',
    'addamxadmins'     => 'Add AMX Mod X admins',
    'access'           => 'Access',
    'flags'            => 'Flags',
    'settings'         => 'Settings',
    'save'             => 'Save',
    'ever'             => 'Infinite',
    'showinadminlist'  => 'Visible in admin list',
    'adminvalidity'    => 'Validity',
    'adminexpiration'  => 'Valid until',
    'created'          => 'Created',
    'extendwith'       => 'extend',
    'steamidipname'    => 'SteamID / IP / Name',


//server

    'serversettings'      => 'Server settings',
    'mod'                 => 'Mod',
    'rconpw'              => 'RCON password',
    'del'                 => 'Delete',
    'motdurl'             => 'motd URL',
    'motddelay'           => 'motd delay',
    'servermenu'          => 'Server menu',
    'reasonsset'          => 'Ban reason sets',
    'hostname'            => 'Server name',
    'version'             => 'Version',
    'lastseen'            => 'last seen',
    'timezonefixx'        => 'Time zone fix',
    'serverrcon'          => 'Send server commands (RCON)',
    'rcon_reloadadmins'   => 'Reload admins',
    'rcon_restartmap'     => 'Reload map/plugins',
    'rcon_status'         => 'Status command',
    'rcon_plugins'        => 'Show list of AMXX plugins',
    'rcon_modules'        => 'Show list of AMXX modules',
    'rcon_metalist'       => 'Show list of Metamods',
    'rcon_predefined'     => 'Predefined',
    'rcon_userdefined'    => 'User defined',
    'rcon_send'           => 'Send',
    'rcon_serverresponse' => 'Response from server:',
    'rcon_maprestarted'   => 'Map will be restarted (command: restart).',
    'rcon_timedout'       => 'No response from server!',
    'rcon_cmddenied'      => 'This RCON command is forbidden!',


//server admins

    'serveradminsettings' => 'Server admin settings',
    'admins'              => 'Admins',
    'active'              => 'Active',
    'customflags'         => 'custom flags',
    'staticbantime'       => 'static ban time',
    'editadmins'          => 'Edit admins',
    'specials'            => 'Server specials',


//reasons

    'reasonssettings' => 'Ban reason administration',
    'reasonssets'     => 'Ban reasons\' sets',
    'newreason'       => 'New reason',
    'saveset'         => 'Save set',
    'editset'         => 'Edit set',
    'reasons'         => 'Reasons',


//settings

    'sitesettings'                 => 'Site administration',
    'banner'                       => 'Banner',
    'bannerurl'                    => 'Banner URL',
    'design'                       => 'Design',
    'bansperpage'                  => 'Bans per page',
    'newset'                       => 'New set',
    'cookiename'                   => 'Cookie name',
    'startpage'                    => 'Start page',
    'showcommentscount'            => 'Show number of comments',
    'showfilescount'               => 'Show number of files',
    'showkickcount'                => 'Show number of kicks',
    'file_useruploadallowed'       => 'Users are allowed to upload files',
    'maxfilesize'                  => 'max. File size',
    'file_allowedtypes'            => 'Allowed file extensions',
    'commentuserallowedwrite'      => 'Users are allowed to write comments',
    'usecapture'                   => 'Use Captcha',
    'autoprune'                    => 'Automatic DB prune',
    'usecommentsystem'             => 'Use comments system',
    'usefilesystem'                => 'Use files system',
    'autoprune_maxoffences'        => 'Maximum expired bans before permanent ban',
    'autoprune_maxoffences_reason' => 'Ban reason for maximum expired bans',
    'mustbeon'                     => 'must be on!',


//admin list

    'admin_since' => 'Admin since',
    'admin_until' => 'Admin until',
    'unlimited'   => 'infinite',


//admins web

    'webadminadd'           => 'Add web admin',
    'webadminssettings'     => 'Web admin administration',
    'webadmins'             => 'Web admins',
    // NEW IN v7.0
    'last_seen'             => 'Last seen',
    'wadminaddedfailed'     => 'Adding failed. Are there duplicated values?',
    'never'                 => 'never',
    'yourpassword'          => 'For security reasons, you will be logged out after changing your own password!',
    'new_password'          => 'Enter new password:',
    'new_password_2'        => 'Re-type password',
    'newpassword'           => 'Change password',
    'passwordchanged'       => 'Password has been changed!',
    'passwordchangedfailed' => 'Password changing failed!',
    'emailsent'             => 'An email has been sent to the given address.',


//search

    'search_results'   => 'Search results',
    'searchwith'       => 'Search with',
    'searchfor'        => 'Search for',
    'do_search'        => 'Search',
    'search_with_bans' => 'Players with',
    'search_prev_bans' => 'or more previous bans',
    // NEW IN v7.0
    'active_admins'    => 'Active Admins',
    // NEW IN v7.0
    'other_admins'     => 'Other Admins',
    'active_bans'      => 'Active bans',
    'expiredbans'      => 'Expired bans',


//Admin list

    'admlist' => 'Admin list',


//captcha

    'scode'      => 'Security code:',
    'scodeenter' => 'Please enter the security code:',


//update

    'webversioninfo'           => 'Website Version Info',
    'pluginversioninfo'        => 'Plugin Version Info',
    'version_current'          => 'Current',
    'version_release'          => 'Latest Release',
    'version_beta'             => 'Latest Beta',
    'lastchangelog'            => 'Changelog',
    'web'                      => 'Website',
    'yourweb'                  => 'Your Website',
    'plugin'                   => 'AMX Mod X Plugin',
    'update_recommended'       => 'Update Recommended!',
    'update_notneeded'         => 'Update not necessary',
    'webupdate_recommended'    => 'Web Update recommended!',
    'pluginupdate_recommended' => 'AMX Mod X Plugin Update recommended!',


//admin menu

    'admin_menu'           => ['index', 'server', 'web', 'other'],
    // NEW IN v7.0
    'admin_menu_titles'    => [
        'index'  => 'Admin area',
        'logout' => 'Log-Out',
        'server' => 'Server',
        'web'    => 'Website',
        'other'  => 'Others',
    ],
    // NEW IN v7.0
    'admin_menu_subtitles' => [
        'index'  => [
            'sys_info'   => 'System Information', // menuhome
            'ban_add'    => 'Add Ban', // titlebanadd
            'online_ban' => 'Ban on-line', // titlebanaddonline
        ],
        'server' => [
            'server'         => 'Server list', // menuserver
            'reasons'        => 'Ban reasons', // menureasons
            'admins'         => 'Admins', // menuamxadmins
            'servers_admins' => 'Assign Admins', // menuserveradmins
        ],
        'web'    => [
            'users'    => 'Web Users', // menuwebadmins
            'groups'   => 'Permission levels', // menuuserlevel
            'settings' => 'Settings', // menuwebconfig
        ],
        'other'  => [
            'sys_upgade' => 'System update', // menuupdate
            'sys_logs'   => 'Action history (logs)', // menulogs
        ],
    ],


//admin user menu

    'usermenu'         => 'User Menu',
    'usermenusettings' => 'User Menu settings',
    'menuloggedin'     => 'User logged in',
    'menuloggedout'    => 'User logged out',
    'position'         => 'Position',
    'langkey1'         => 'Language key 1',
    'langkey2'         => 'Language key 2',
    'url1'             => 'URL 1',
    'url2'             => 'URL 2',
    'usermenuadd'      => 'New user menu',


//admin module

    'modulsettings'  => 'Module administration',
    'modulsettings2' => 'Module settings',
    'namelangkey'    => 'Language key for menu',
    'indexsite'      => 'Index page',
    'adminsite'      => 'Admin page',
    'template'       => 'Template',


//admin info

    'serverinfo'     => 'Server Information',
    'serversetup'    => 'Server setup',
    'phpmodules'     => 'PHP module',
    'otherfunctions' => 'Other Functions',
    'statistik'      => 'Statistic',
    'clearcache'     => 'Clear page cache',
    'db_size'        => 'Database size',
    'db_optimise'    => 'Optimize database',
    'optimize'       => 'Optimize',
    'prune_bans'     => 'Prune bans',
    'prune'          => 'Prune',


//user level

    'adminlevelsettings' => 'Web admin level administration',
    'amxadmins'          => 'AMX admins',
    'websettings'        => 'Web settings',
    'levelview'          => 'Show',
    'levelunban'         => 'Unban',
    'levelimport'        => 'Import',
    'levelexport'        => 'Export',
    'perm'               => 'User Levels',
    'dbprune'            => 'Prune DB',
    'serveredit'         => 'Edit server',
    'newlevel'           => 'New level',
    'yourlevel'          => 'Your Level: You will be logged out when saving',


// WebAdmin Groups // NEW IN v7.0

    'new_group'  => 'New Group',
    'edit_group' => 'Edit Group',
    'group_list' => 'Permission groups',
    'what_level' => 'Group %d', // Used in permission list,

    "bans_add"         => 'Add bans',
    "bans_edit"        => 'Edit bans',
    "bans_delete"      => 'Delete bans',
    "bans_unban"       => 'Unban',
    "amxadmins_view"   => 'View server admins',
    "amxadmins_edit"   => 'Edit server admins',
    "webadmins_view"   => 'View web users',
    "webadmins_edit"   => 'Edit web users',
    "websettings_view" => 'View web settings',
    "websettings_edit" => 'Edit web settings',
    "permissions_edit" => 'Edit user groups',
    "prune_db"         => 'Prune database',
    "servers_edit"     => 'Edit server data',
    "ip_view"          => 'View IPs',


//admin logs

    'logs'       => 'Website log',
    'filter'     => 'Filter',
    'all'        => 'all logs',
    'olderthen'  => 'Logs older than',
    'go'         => 'Go',
    'action'     => 'Action',
    'actionlogs' => 'Actions done',
    'remarks'    => 'Description',
    'user'       => 'User',


//add ban

    'addban'            => 'Add ban',
    'newban'            => 'Add new ban',
    'nobanname'         => 'No name entered!',
    // NEW IN v7.0
    'custom_reason'     => 'custom reason',
    'active_ban_exists' => 'There already is an active ban!',


//messages

    'bans_pruned'         => 'Bans pruned',
    'no_access'           => 'You are not authorized to view this page!',
    'err_wrong_pass'      => 'Password is not correct',
    //NEW IN v7.0
    'err_no_user'         => 'User with this username not found',
    // NEW IN v7.0
    'err_no_user_email'   => 'User with this email not found',
    // NEW IN v7.0
    'passcode_exist'      => 'Account with this email already requested password change. Please check email for further instructions',
    // NEW IN v7.0
    'passcode_sent'       => 'Password change instructions sent to :email. Please refer to it.',
    // NEW IN v7.0
    'passreset_nocode'    => 'Sorry but we couldn\'t find any user for this code.',
    // NEW IN v7.0
    'pass_changed'        => 'Password changed successfully! You can now try to login.',
    'banaddsuccess'       => 'Ban added successfully',
    'banedited'           => 'Ban saved',
    'amxadminsavesuccess' => 'AMX Mod X admin saved successfully',
    'amxadmindeleted'     => 'AMX Mod X admin deleted',
    'amxadminadded'       => 'AMX Mod X admin added',
    'noname'              => 'Name is missing!',
    'noflags'             => 'Flags are missing!',
    'nosteam'             => 'No SteamID entered!',
    'novalidtime'         => 'Validity time is missing!',
    'reasonsetadded'      => 'Reason set added',
    'reasonsetdeleted'    => 'Reason set deleted',
    'reasonssetsaved'     => 'Reason set saved',
    'reasonadded'         => 'Reason added',
    'reasondeleted'       => 'Reason deleted',
    'reasonsaved'         => 'Reason saved',
    'sadminsaved'         => 'Server admin saved',
    'serversaved'         => 'Server settings saved',
    'serverdeleted'       => 'Server deleted',
    'cachedeleted'        => 'Website cache cleared',
    'logdeleted'          => 'Logs deleted',
    'modulsaved'          => 'Module settings saved',
    'configsaved'         => 'Settings saved',
    'leveladded'          => 'Level created',
    'leveldelfailed'      => 'Error:<br /><br />Webadmin(s) with this level already exist(s)!<br />Level can not be deleted.',
    'leveldeleted'        => 'Level deleted',
    'levelsaved'          => 'Level saved',
    'usermenudeleted'     => 'User Menu deleted',
    'usermenuadded'       => 'User Menu added',
    'usermenupossaved'    => 'User Menu position saved',
    'usermenusaved'       => 'User Menu saved',
    'wadminsaved'         => 'Web admin saved',
    'wadmindeleted'       => 'Web admin deleted',
    'wadminadded'         => 'Web admin added',
    'comdeleted'          => 'Comment deleted',
    'comment_saved'       => 'Comment saved successfully',
    'comedited'           => 'Comment edited',
    // NEW IN v7.0
    'no_commenting'       => 'Commenting are not allowed from unregistered users.',
    'wrongcaptcha'        => 'Wrong security code!',
    'filedelfailed'       => 'File could not be deleted!',
    'filenotfound'        => 'File not found!',
    'error'               => 'Error',
    'saved'               => 'Entry saved',
    // NEW IN v7.0
    'deleted'             => 'Entry deleted',
    'filenofile'          => 'No file!',
    'file_not_type'       => 'Uploaded file was not allowed file type',
    'file_too_big'        => 'Uploaded file was too big. Try to reduce its size.',
    // NEW IN v7.0
    'file_not_uploaded'   => 'File was not uploaded nor saved',
    'fileuploadsuccess'   => 'File upload successful',
    'filenotavailable'    => 'File not available!',
    'filedelsuccess'      => 'File successfully deleted',
    'norequiredfields'    => 'Required fields are missing!',
    // NEW IN v7.0
    'db_not_optimised'    => 'Database was not optimised!',
    'db_optimised'        => 'Database optimised successfully!',
    // NEW IN v7.0
    'invalidCSRF'         => 'Form You provided was not submitted due to missing cross-site security token. Please try submitting it again.',
    // NEW IN v7.0
    'validation_errors'   => [
        'required'         => 'The :attribute field is required',
        'same'             => 'The :attribute field needs to be the same as :0',
        'min'              => 'The :attribute field needs to be at least :0',
        'max'              => 'The :attribute field cannot be more than :0',
        'later'            => 'The :attribute field needs to be later than now',
        'ip'               => 'The :attribute field needs to be an ip-compliant string (0.0.0.0-255.255.255.255)',
        'steamid'          => 'The :attribute field needs to be a valid SteamID (STEAM_0:[0 or 1]:[1-10 digits])',
        'email'            => 'The :attribute field needs to be a valid email',
        'captcha'          => 'Security (Captcha) code is not correct', // wrongcaptcha
        'required_without' => 'The :attribute field is required if :0 is not present', // wrongcaptcha
    ],


//live viewer

    'connect'               => 'Connect',
    'number'                => '#',
    'frags'                 => 'Frags',
    'online'                => 'Time',
    'address'               => 'Address',
    'map'                   => 'Map',
    'nextmap'               => 'Next map',
    'timeleft'              => 'Time left',
    'server_password'       => 'Password protected',
    'timelimit'             => 'Time limit',
    'friendly_fire'         => 'Friendly Fire',
    'gametype'              => 'Game',
    'anticheat'             => 'Anti-cheat tools',
    'addons'                => 'Addons',
    'protocol'              => 'Protocol',
    // NEW IN v7.0
    'servers'               => 'Servers',
    'server_not_found'      => 'Server not available',
    // NEW IN v7.0
    'total_bans'            => 'Total bans',
    // NEW IN v7.0
    'players_online'        => 'Players online',
    // NEW IN v7.0
    'server_cannot_connect' => 'Cannot connect live to server',
    'refresh'               => 'Refresh',
    'notimelimit'           => 'no time limit',
    'player_info'           => [
        'connecting' => 'Player connecting...', // playerconnecting
        'none'       => 'No Players', // noplayers
        'active'     => 'Real',
        'bots'       => 'Bots',
        'total'      => 'Total',
    ],


//live ban

    'addbanonline'      => 'Add online ban',
    'bansettings'       => 'Ban/kick settings',
    'show'              => 'Show',
    'userid'            => 'User ID',
    'statusname'        => 'Status name',
    'bot'               => 'Bot',
    'hltv'              => 'HLTV',
    'unknown'           => 'Unknown',
    'ban'               => 'Ban',
    'kick'              => 'Kick',
    'wrong_rcon'        => 'Wrong RCON password!',
    'playerkicked'      => 'Player kicked!',
    'addbansuccesskick' => 'Ban added. Player will be kicked!',
    'banandkick'        => 'Kick player after ban',
    'banplayer'         => 'Do you really want to ban this player?',
    'kickplayer'        => 'Do you really want to kick this player?',


//title

    'titleadmin'        => 'Assign Admins',
    'titleadminlist'    => 'Admin list',
    'titlebanlist'      => 'Ban list',
    'titlelogin'        => 'Log in',
    'titlesearch'       => 'Search',
    'titleview'         => 'Live server status',
    'titlebandetail'    => 'Details',
    'titlebanadd'       => 'Add ban',
    'titlebanaddonline' => 'Add online ban',
    'titleamxadmins'    => 'AMX Mod X admins',
    'titlereasons'      => 'Ban reasons',
    'titleserveradmins' => 'Server admins',
    'titleserver'       => 'Server',
    'titleinfo'         => 'Information',
    'titlelogs'         => 'Logs',
    'titlemodule'       => 'Module',
    'titleupdate'       => 'Version check',
    'titleuserlevel'    => 'User level',
    'titlesite'         => 'Page settings',
    'titleusermenu'     => 'User Menu',
    'titlewebadmin'     => 'Web admin',


//value check

    'nousername'       => 'No username entered!',
    'nopassword'       => 'No password entered!',
    'accessinvalid'    => 'Access invalid!',
    'flagsbcdmissing'  => 'Flag has to be either B, C or D!',
    'nonickname'       => 'No nickname entered!',
    'notag'            => 'No clan tag/name entered!',
    'emailinvalid'     => 'E-mail address not valid!',
    'steamidinvalid'   => 'SteamID not valid!',
    'ipinvalid'        => 'IP address not valid!',
    'flagsinvalid'     => 'Flags not valid!',
    'usernametoshort'  => 'Name too short!',
    'usernametolong'   => 'Name too long!',
    'nicknametoshort'  => 'Nickname too short!',
    'nicknametolong'   => 'Nickname too long!',
    'passwordtoshort'  => 'Password too short!',
    'passwordtolong'   => 'Password too long!',
    'noreasonset'      => 'No reason name entered!',
    'reasonsettoshort' => 'Reason group name too short!',
    'reasonsettolong'  => 'Reason group name too long!',
    'noreason'         => 'No ban reason entered!',
    'reasontoshort'    => 'Ban reason too short!',
    'reasontolong'     => 'Ban reason too long!',
    'passwordnotmatch' => 'The passwords entered do not match!',
    'nocomment'        => 'No comment entered!',
    'noeditreason'     => 'No Edit-Reason Entered!',
    'commenttoshort'   => 'Comment too short!',
    'commenttolong'    => 'Comment too long!',
    'steamtolong'      => 'SteamID too long!',
    'steamtoshort'     => 'SteamID too short!',
    'noip'             => 'No IP entered!',
    'iptolong'         => 'IP too long!',
    'iptoshort'        => 'IP too short!',


//alerts

    // NEW IN v7.0
    'confirm_message'  => 'Are You sure You want to do this action?',
    'saveedit'         => 'Save changes?',
    'delban'           => 'Do you really want to delete this ban?',
    'deldemo'          => 'Do you really want to delete this file?',
    'delcomment'       => 'Do you really want to delete this comment?',
    'deladmin'         => 'Do you really want to delete this admin?',
    'dellevel'         => 'Do you really want to delete this level?',
    'dellogsall'       => 'Do you really want to delete all logs?',
    'dellogs'          => 'Do you really want to delete these logs?',
    'savesettings'     => 'Save settings and apply?',
    'dataloss'         => '\nThe data can NOT be recovered!',
    'delserver'        => 'Do you really want to delete this server?',


//motd

    'noexpiredbans' => 'No expired bans',
    'youarebanned'  => 'You have been banned!!',


//upgrade system

    'step'             => 'Step',
    'step1'            => 'Let\'s check if it\'s possible to use the Auto Function',
    'step2'            => 'Download &amp; Unpack',
    // &amp; = & = and
    'step3'            => 'Run the Scripts',
    'finish'           => 'Finish',
    'web_outdated'     => 'Your website version is outdated.',
    'run_script'       => 'Please run this script to update your AMXBans Version.',
    'up_to_date'       => 'Your website version is up-to-date.',
    'fsf'              => 'File System Functions',
    'remote_dl'        => 'Remote Download',
    'unzip'            => 'Unpack ZIP',
    'crc32check'       => 'CRC32 Check',
    'rewind_func'      => 'Rewind Function',
    'if_manual'        => '<b>Note:</b> If you choose \'Manual\', step 2 isn\'t necessary.',
    'manual'           => 'Manual',
    'next'             => 'next',
    'rewind'           => 'rewind',
    'cl_last_release'  => 'Click here to view the changelog for the latest release',
    'nofilesunpack'    => 'No files to unpack!',
    'write_prot'       => 'Write protected',
    'dir_write_prot'   => 'Directory is write protected',
    'skip_dir'         => 'Skipping! Directory already exists',
    'skip_file'        => 'File doesn\'t need to be upgraded',
    'unknown_error'    => 'Unknown error!',
    'cannot_create'    => 'Can\'t create file / directory',
    'nothing_to_view'  => 'Nothing to view at the moment!',
    'nodbchanges'      => 'No database changes!',
    'upgrade_finished' => 'Your AMXBans Installation has been updated <b>successfully</b>.<br />Click \'Finish\' to continue to your Admin Contol Panel.',
    'backup_db_b4'     => 'Remember to backup your files and database before you run this update!',


//new design related

    'os'                 => 'OS',
    'vac'                => 'VAC',
    'vac_alt'            => 'Valve Anti-Cheat',
    'na'                 => 'N/A',
    'stats'              => 'Overall statistics',
    'perm_bans'          => 'Permanent Bans',
    'temp_bans'          => 'Temporary',
    'active_servers'     => 'Active Servers',
    'latest_ban'         => 'Latest Ban',
    'latest_kicks'       => 'Latest Kicks',
    'browse_all'         => 'Browse All',
    'powered_by'         => 'Powered by',
    'design_by'          => 'Design by',
    'no_bans'            => 'No Bans in Database',
    'first_page'         => 'First Page',
    'last_page'          => 'Last Page',
    'previous_page'      => 'Previous Page',
    'next_page'          => 'Next Page',
    'pick_date'          => 'Pick a Date',
    'web_version'        => 'Website Version',
    'webserver'          => 'Webserver',
    'modules'            => 'Modules',
    'min_or'             => 'minutes or',
    'size'               => 'Size',
    'upd_connect_error'  => 'No connection could be established to the Update-Server!',
    'upd_db_error'       => 'The Update-Database could not be found.',
    'upd_select_error'   => 'The Update-Database could not be selected.',
    'adminid'            => 'Admin\'s SteamID',
    'trackback'          => 'Trackback',
    'setup_exists'       => '<b>Security Alert!</b><br />setup.php still remains in your AMXBans Directory.<br /><br />You can still access the Admin Control Panel, but we strongly recommend you to remove it! ',
    'bytes'              => 'bytes',
    'mb'                 => 'MB',
    'success'            => 'No errors',
    'error_mysql'        => 'Please update your MySQL Version to MySQL 4.1 or higher.',
    'error_php'          => 'Please update your PHP Version to PHP 4.4.4 or higher.',
    'error_reg_globals'  => 'Please turn off your register_globals',
    'error_magic_quotes' => 'Please turn off your magic_quotes',
    'error_gmp'          => 'Please turn on bcmath and gmp',


// lost-pass

    // NEW IN v7.0
    'lost_pass'          => 'Forgot password',
    // NEW IN v7.0
    'pass_rec'           => 'Password recovery',
    // NEW IN v7.0
    'lost_pass_email'    => [
        'subject' => 'Password reset',
        'greet'   => 'Hello :username,',
        'intro'   => 'Somebody just tried to reset your accounts password. For security reasons we sent this email to ensure its You.<br />
 If you cannot remember your previous password - below there is link to change password to new one.
 Click on it and You will be prompted to provide new password.<br />
 Link and code is valid only for 24h counting from :now.
 If this was not You just sit back and relax, link will become invalid afterwards.',
        'site'    => 'Click below to change the password',


    ],
];