<?php
/**
 * Language: English (UK)
 * Author Notes:
 * *
 */
return [
    'locale'         => 'en',
    'html_direction' => 'ltr',

    'index' => [
        'titles' => [
            'ban'     => 'Ban details',
            'bans'    => 'Ban list',
            'servers' => 'Server list',
            'admins'  => 'Admin list',
            'search'  => 'Search',
            'login'   => 'Log in',
        ],
        'menu'   => [ 'bans', 'servers', 'admins', 'search' ],

        'login' => [
            'username' => 'Username',
            'email'    => 'Email',
            'pass'     => 'Password',
            'remember' => 'Remember my login',
            'blocked'  => 'Blocked login',

            'lost_pass' => 'Forgot password?',
            'pass_rec'  => 'Password recovery',

            'passcode_exist' => 'Account with this email already requested password change. Please check email for further instructions',

        ],
    ],

    'admin' => [
        'titles' => [
            'index'  => 'Admin area',
            'logout' => 'Log-Out',
            'server' => 'Server',
            'web'    => 'Website',
            'other'  => 'Others',
        ],
        'menu'   => [ 'index', 'server', 'web', 'other' ],

        'subtitles' => [
            'index'  => [
                'sys_info'   => 'System Information',
                'ban_add'    => 'Add Ban',
                'online_ban' => 'Ban on-line',
            ],
            'server' => [
                'server'         => 'Server list',
                'reasons'        => 'Ban reasons',
                'admins'         => 'Admins',
                'servers_admins' => 'Assign Admins',
            ],
            'web'    => [
                'users'    => 'Web Users',
                'groups'   => 'Permission levels',
                'settings' => 'Settings',
            ],
            'other'  => [
                'sys_upgade' => 'System update',
                'sys_logs'   => 'Action history (logs)',
            ],
        ],
    ],

    'back' => 'Back',
    'send' => 'Send',
];

//default
define("_SHORTSECONDS","sec");
define("_NOACCESS","You are not authorized to view this page!");
define("_LOADTIME","Page generated in");
define("_BANSINDB","Bans in database");
define("_BY","by");
define("_OR","or");
define("_ON","on");
define("_OFF","off");
define("_YES","yes");
define("_NO","no");
define("_OWN","own");
define("_CLEAR","Reset");
define("_OPENSTEAMCOMSITE","Visit Steam Community page");
define("_ADMINAREA","Admin area");
define("_NOSITE","Page not available!");
define("_DELETE","Delete");
define("_ADD","Add");
define("_EDIT","Edit");
define("_DEFAULTLANG","Default Language");
define("_OTHER","Others");
define("_VIEWIP","Show IP");
define("_LEVEL","Level");
define("_DETAILS","Show Details");
define("_SYSTEMSETTINGS","System");
define("_VIEWSETTINGS","View");
define("_COMMENTSETTINGS","Comments");
define("_FILESETTINGS","Files");
define("_BANLISTSETTINGS","Ban list");
define("_CONFIGURATION","Configuration");
define("_REPAIR","Repair");
define("_AUTO","Automatic");
define("_TEST","Test");
//user menu
define("_HOME","Main page");
define("_BANLIST","Ban list");
define("_SEARCH","Search");
define("_SERVER","Server");
//info amxaccess
define("_INFO_ACCESS","Access info");
define("_ACCESSFLAGS","Access Flags");
define("_ACCESSPERMS","Access permissions");
define("_ACCESS_FLAGS","a - Immunity (can't be kicked/banned etc.)<br />b - Reserved slots (can use reserved slots)<br />c - amx_kick command<br />d - amx_ban and amx_unban commands<br />e - amx_slay and amx_slap commands<br />f - amx_map command<br />g - amx_cvar command (not all CVARs available)<br />h - amx_cfg command<br />i - amx_chat and other chat commands<br />j - amx_vote and other vote commands<br />k - Access to sv_password cvar (through amx_cvar command)<br />l - Access to amx_rcon command and rcon_password cvar (through amx_cvar command)<br />m - User defined Level A (for other plugins)<br />n - User defined Level B<br />o - User defined Level C<br />p - User defined Level D<br />q - User defined Level E<br />r - User defined Level F<br />s - User defined Level G<br />t - User defined Level H<br />u - Menu access<br />z - User (not admin)");
define("_FLAG_FLAGS","a - kick a player on wrong password<br />b - Clan tag<br />c - that's the SteamID<br />d - that's the IP<br />e - no password (only SteamID/IP necessary)<br />k - Name or tag (CaSe SenSiTiVe!).");
define("_ADDADMINTOSERVERS","Add admin to server");
define("_WITHSTATICBANTIME","with static ban time");
//main header
define("_LOGGED","Logged in as");
define("_NOTLOGGED","Not logged in");
define("_LOGOUT","Log out");
define("_LOGIN","Log in");
define("_MENU","Menu");
//ban list
define("_DATE","Date");
define("_PLAYER","Player");
define("_ADMIN","Admin");
define("_REASON","Reason");
define("_LENGHT","Length");
define("_SITE","Page");
define("_BANS","Bans");
define("_BL_COMMENTS","Comments");
define("_BL_FILES","Files");
define("_BL_KICKS","Kicks");
define("_TO","to");
define("_YEAR","Year");
define("_YEARS","Years");
define("_MONTH","Month");
define("_MONTHS","Months");
define("_WEEK","Week");
define("_WEEKS","Weeks");
define("_DAY","Day");
define("_DAYS","Days");
define("_HOUR","Hour");
define("_HOURS","Hours");
define("_MIN","Minute");
define("_MINS","Minutes");
define("_OF","of");
define("_REMAINING","remaining");
//ban list details
define("_PERMANENT","Permanent");
define("_BANDETAILS","Ban details");
define("_STEAMID","SteamID");
define("_STEAMCOMID","Steam Community ID");
define("_NOTAVAILABLE","Not Available");
define("_NOSTEAMID","no SteamID");
define("_STEAMID&IP","SteamID and/or IP");
define("_HIDDEN","hidden");
define("_INVOKED","Invoked on");
define("_BANLENGHT","Ban length");
define("_EXPIRES","Expires on");
define("_NOTAPPLICABLE","Not applicable");
define("_ALREADYEXP","already expired");
define("_IP","IP address");
define("_BANTYPE","Ban type");
define("_BANBY","Banned by");
define("_BANON","Banned on");
define("_FILE_TOBIG","File is too big");
define("_FILE_TYPENOTALLOWED","File type not allowed");
define("_FROM","from");
define("_DOWNLOAD","Download");
define("_DOWNLOADS","Downloads");
define("_FILE","File");
define("_NEWFILE","New File");
define("_COMMENT","Comment");
define("_COMMENTS","Comments");
define("_NEWCOMMENT","New comment");
define("_NOCOMMENTS","No comments");
define("_BACK","back");
define("_TIP_EDIT","Edit");
define("_TIP_DEL","Delete");
define("_TIP_DOWNLOAD","Download");
define("_TIP_BACK","Back");
define("_TIP_SENDMAIL","Send E-mail");
define("_EMAIL","E-mail");
define("_FILEUPLOAD","Upload file");
define("_UPLOAD","Upload");
define("_ENTRYEDIT","Edit entry");
define("_EDITBAN","Edit ban");
define("_TOTALEXPBANS","Total expired bans");
define("_EDITCOMMENT","Edit comment");
define("_ADDCOMMENT","Add comment");
define("_NOFILES","No files");
define("_BANDETAILSEDITS","Changes in past");
define("_EDITREASON","Reason for editing");
define("_UNBANPLAYER","Unban");
define("_UNBANNED","Unbanned");
define("_BANHISTORY","Ban history");
//Login
define("_USERNAME","Username");
define("_PASSWORD","Password");
define("_REMEMBERME","Remember me");
define("_LOGINBLOCKED","Login blocked!");
define("_LOGINFAILEDPW","Check password!");
define("_LOGINFAILED","Login failed!");
define("_LOGINTRY","Try");
define("_SEC","Second");
define("_SECS","Seconds");
//admins amxx
define("_AMXADMINSETTINGS","AMX Mod X admin administration");
define("_NAME","Name");
define("_NICKNAME","Nickname");
define("_MANAGEAMXADMINS","AMX Mod X admins");
define("_ADDAMXADMINS","Add AMX Mod X admins");
define("_ACCESS","Access");
define("_FLAGS","Flags");
define("_SETTINGS","Settings");
define("_SAVE","Save");
define("_EVER","Infinite");
define("_SHOWINADMINLIST","Visible in admin list");
define("_ADMINVALIDITY","Validity");
define("_ADMINEXPIRATION","Valid until");
define("_CREATED","Created");
define("_EXTENDWITH","extend");
define("_STEAMIDIPNAME","SteamID / IP / Name");
//server
define("_SERVERSETTINGS","Server settings");
define("_MOD","Mod");
define("_RCONPW","RCON password");
define("_DEL","Delete");
define("_MOTDURL","motd URL");
define("_MOTDDELAY","motd delay");
define("_SERVERMENU","Server menu");
define("_REASONSSET","Ban reason sets");
define("_HOSTNAME","Server name");
define("_VERSION","Version");
define("_LASTSEEN","last seen");
define("_TIMEZONEFIXX","Time zone fix");
define("_SERVERRCON","Send server commands (RCON)");
define("_RCON_RELOADADMINS","Reload admins");
define("_RCON_RESTARTMAP","Reload map/plugins");
define("_RCON_STATUS","Status command");
define("_RCON_PLUGINS","Show list of AMXX plugins");
define("_RCON_MODULES","Show list of AMXX modules");
define("_RCON_METALIST","Show list of Metamods");
define("_RCON_PREDEFINED","Predefined");
define("_RCON_USERDEFINED","User defined");
define("_RCON_SEND","Send");
define("_RCON_SERVERRESPONSE","Response from server:");
define("_RCON_MAPRESTARTED","Map will be restarted (command: restart).");
define("_RCON_TIMEDOUT","No response from server!");
define("_RCON_CMDDENIED","This RCON command is forbidden!");
//server admins
define("_SERVERADMINSETTINGS","Server admin settings");
define("_ADMINS","Admins");
define("_ACTIV","active");
define("_CUSTOMFLAGS","custom flags");
define("_STATICBANTIME","static ban time");
define("_EDITADMINS","Edit admins");
define("_SPECIALS","Server specials");
//reasons
define("_REASONSSETTINGS","Ban reason administration");
define("_REASONSSETS","Ban reasons' sets");
define("_NEWREASON","New reason");
define("_SAVESET","Save set");
define("_EDITSET","Edit set");
define("_REASONS","Reasons");
//settings
define("_SITESETTINGS","Site administration");
define("_BANNER","Banner");
define("_BANNERURL","Banner URL");
define("_DESIGN","Design");
define("_BANSPERPAGE","Bans per page");
define("_NEWSET","New set");
define("_COOKIENAME","Cookie name");
define("_STARTPAGE","Start page");
define("_SHOWCOMMENTSCOUNT","Show number of comments");
define("_SHOWFILESCOUNT","Show number of files");
define("_SHOWKICKCOUNT","Show number of kicks");
define("_FILE_USERUPLOADALLOWED","Users are allowed to upload files");
define("_MAXFILESIZE","max. File size");
define("_FILE_ALLOWEDTYPES","Allowed file extensions");
define("_COMMENTUSERALLOWEDWRITE","Users are allowed to write comments");
define("_USECAPTURE","Use Captcha");
define("_AUTOPRUNE","Automatic DB prune");
define("_USECOMMENTSYSTEM","Use comments system");
define("_USEFILESYSTEM","Use files system");
define("_AUTOPRUNE_MAXOFFENCES","Maximum expired bans before permanent ban");
define("_AUTOPRUNE_MAXOFFENCES_REASON","Ban reason for maximum expired bans");
define("_MUSTBEON","must be on!");
//admin list
define("_ADMINSINCE","Admin since");
define("_ADMINTO","Admin until");
define("_UNLIMITED","infinite");
//admins web
define("_WEBADMINADD","Add web admin");
define("_WEBADMINSSETTINGS","Web admin administration");
define("_WEBADMINS","Web admins");
define("_LASTLOGIN","last login");
define("_WADMINADDEDFAILED","Adding failed. Are there duplicated values?");
define("_NEVER","never");
define("_YOURPASSWORD","For security reasons, you will be logged out after changing your own password!");
define("_ENTERPASSWORD","Enter new password:");
define("_PASSWORD2","Re-type password");
define("_NEWPASSWORD","Change password");
define("_PASSWORDCHANGED","Password has been changed!");
define("_PASSWORDCHANGEDFAILED","Password changing failed!");
define("_EMAILSENT","An email has been sent to the given address.");
//search
define("_SEARCHRESULT","Search results");
define("_SEARCHWITH","Search with");
define("_SEARCHFOR","Search for");
define("_PLAYERSWITH","Players with");
define("_MOREBANSHIS","or more previous bans");
define("_ACTIVEBANS","Active bans");
define("_EXPIREDBANS","Expired bans");
//Admin list
define("_ADMLIST","Admin list");
//captcha
define("_SCODE","Security code:");
define("_SCODEENTER","Please enter the security code:");
//update
define("_WEBVERSIONINFO","Website Version Info");
define("_PLUGINVERSIONINFO","Plugin Version Info");
define("_VERSION_CURRENT","Current");
define("_VERSION_RELEASE","Latest Release");
define("_VERSION_BETA","Latest Beta");
define("_LASTCHANGELOG","Changelog");
define("_WEB","Website");
define("_YOURWEB","Your Website");
define("_PLUGIN","AMX Mod X Plugin");
define("_UPDATE_RECOMMENDED","Update Recommended!");
define("_UPDATE_NOTNEEDED","Update not necessary");
define("_WEBUPDATE_RECOMMENDED","Web Update recommended!");
define("_PLUGINUPDATE_RECOMMENDED","AMX Mod X Plugin Update recommended!");
//admin menu
define("_MENUHOME","Admin home");
define("_MENUMAINSERVER","Server");
define("_MENUMAINWEB","Website");
define("_MENUMAINOTHER","others");
define("_MENUMAINMODULE","Module");
define("_MENUSERVER","Server");
define("_MENUAMXADMINS","AMX admins");
define("_MENUSERVERADMINS","Assign AMX admins");
define("_MENUREASONS","Ban reasons");
define("_MENUWEBCONFIG","Settings");
define("_MENUUSERLEVEL","User level");
define("_MENUWEBADMINS","Web admins");
define("_MENUUSERMENU","User Menu");
define("_MENUMODULE","Module");
define("_MENUUPDATE","Update");
define("_MENUINFO","System Information");
define("_MENULOGS","Logs");
//admin user menu
define("_USERMENU","User Menu");
define("_USERMENUSETTINGS","User Menu settings");
define("_MENULOGGEDIN","User logged in");
define("_MENULOGGEDOUT","User logged out");
define("_POSITION","Position");
define("_LANGKEY1","Language key 1");
define("_LANGKEY2","Language key 2");
define("_URL1","URL 1");
define("_URL2","URL 2");
define("_USERMENUADD","New user menu");
//admin module
define("_MODULSETTINGS","Module administration");
define("_MODULSETTINGS2","Module settings");
define("_NAMELANGKEY","Language key for menu");
define("_INDEXSITE","Index page");
define("_ADMINSITE","Admin page");
define("_TEMPLATE","Template");
//admin info
define("_SERVERINFO","Server Information");
define("_SERVERSETUP","Server setup");
define("_PHPMODULES","PHP module");
define("_OTHERFUNCTIONS","Other Functions");
define("_STATISTIK","Statistic");
define("_CLEARCACHE","Clear page cache");
define("_DBSIZE","Database size");
define("_DBOPTIMIZE","Optimize database");
define("_OPTIMIZE","Optimize");
define("_PRUNEDB","Prune bans");
define("_PRUNE","Prune");
define("_DBPRUNED","Bans pruned");
//user level
define("_ADMINLEVELSETTINGS","Web admin level administration");
define("_AMXADMINS","AMX admins");
define("_WEBSETTINGS","Web settings");
define("_LEVELVIEW","Show");
define("_LEVELUNBAN","Unban");
define("_LEVELIMPORT","Import");
define("_LEVELEXPORT","Export");
define("_PERM","User Levels");
define("_DBPRUNE","Prune DB");
define("_SERVEREDIT","Edit server");
define("_NEWLEVEL","New level");
define("_YOURLEVEL","Your Level: You will be logged out when saving");
//admin logs
define("_LOGS","Website log");
define("_FILTER","Filter");
define("_ALL","all logs");
define("_OLDERTHEN","Logs older than");
define("_GO","Go");
define("_ACTION","Action");
define("_ACTIONLOGS","Actions done");
define("_REMARKS","Description");
define("_USER","User");
//add ban
define("_ADDBAN","Add ban");
define("_NEWBAN","Add new ban");
define("_NOBANNAME","No name entered!");
define("_ACTIVBANEXISTS","There already is an active ban!");
//messages
define("_BANADDSUCCESS","Ban added successfully");
define("_BANEDITED","Ban saved");
define("_AMXADMINSAVESUCCESS","AMX Mod X admin saved successfully");
define("_AMXADMINDELETED","AMX Mod X admin deleted");
define("_AMXADMINADDED","AMX Mod X admin added");
define("_NONAME","Name is missing!");
define("_NOFLAGS","Flags are missing!");
define("_NOSTEAM","No SteamID entered!");
define("_NOVALIDTIME","Validity time is missing!");
define("_REASONSETADDED","Reason set added");
define("_REASONSETDELETED","Reason set deleted");
define("_REASONSSETSAVED","Reason set saved");
define("_REASONADDED","Reason added");
define("_REASONDELETED","Reason deleted");
define("_REASONSAVED","Reason saved");
define("_SADMINSAVED","Server admin saved");
define("_SERVERSAVED","Server settings saved");
define("_SERVERDELETED","Server deleted");
define("_CACHEDELETED","Website cache cleared");
define("_LOGDELETED","Logs deleted");
define("_MODULSAVED","Module settings saved");
define("_CONFIGSAVED","Settings saved");
define("_LEVELADDED","Level created");
define("_LEVELDELFAILED","Error:<br /><br />Webadmin(s) with this level already exist(s)!<br />Level can not be deleted.");
define("_LEVELDELETED","Level deleted");
define("_LEVELSAVED","Level saved");
define("_USERMENUDELETED","User Menu deleted");
define("_USERMENUADDED","User Menu added");
define("_USERMENUPOSSAVED","User Menu position saved");
define("_USERMENUSAVED","User Menu saved");
define("_WADMINSAVED","Web admin saved");
define("_WADMINDELETED","Web admin deleted");
define("_WADMINADDED","Web admin added");
define("_COMDELETED","Comment deleted");
define("_COMADDED","Comment added");
define("_COMEDITED","Comment edited");
define("_WRONGCAPTCHA","Wrong security code!");
define("_FILEDELFAILED","File could not be deleted!");
define("_FILENOTFOUND","File not found!");
define("_ERROR","Error");
define("_FILEEDITED","Entry saved");
define("_FILENOFILE","No file!");
define("_FILETYPENOTALLOWED","Filetype not allowed!");
define("_FILETOBIG","File is too big!");
define("_FILEUPLOADFAIL","Upload error!");
define("_FILEUPLOADSUCCESS","File upload successful");
define("_FILENOTAVAILABLE","File not available!");
define("_FILEDELSUCCESS","File successfully deleted");
define("_NOREQUIREDFIELDS","Required fields are missing!");
define("_DBOPTIMIZED","Database optimized");
//live viewer
define("_SELECTSERVER","Select server");
define("_ADDHLSW","Add to HLSW");
define("_CONNECT","Connect");
define("_NUMBER","#");
define("_FRAGS","Frags");
define("_ONLINE","Time");
define("_ADDRESS","Address");
define("_MAP","Map");
define("_NEXTMAP","Next map");
define("_TIMELEFT","Time left");
define("_TIMELIMIT","Time limit");
define("_FRIENDLYFIRE","Friendly Fire");
define("_GAMETYPE","Game");
define("_ANTICHEAT","Anti-cheat tools");
define("_ADDONS","Addons");
define("_PROTOCOL","Protocol");
define("_NOPLAYERS","No Players");
define("_PLAYERCONNECTING","Player connecting...");
define("_SERVEROFFLINE","Server not available");
define("_REFRESH","Refresh");
define("_NOTIMELIMIT","no time limit");
//live ban
define("_ADDBANONLINE","Add online ban");
define("_BANSETTINGS","Ban/kick settings");
define("_SHOW","Show");
define("_USERID","User ID");
define("_STATUSNAME","Status name");
define("_BOT","Bot");
define("_PLAYER","Player");
define("_HLTV","HLTV");
define("_UNKNOWN","Unknown");
define("_BAN","Ban");
define("_KICK","Kick");
define("_WRONGRCON","Wrong RCON password!");
define("_PLAYERKICKED","Player kicked!");
define("_ADDBANSUCCESSKICK","Ban added. Player will be kicked!");
define("_BANANDKICK","Kick player after ban");
define("_BANPLAYER","Do you really want to ban this player?");
define("_KICKPLAYER","Do you really want to kick this player?");
//title
define("_TITLEADMIN","Assign Admins");
define("_TITLEADMINLIST","Admin list");
define("_TITLEBANLIST","Ban list");
define("_TITLELOGIN","Log in");
define("_TITLESEARCH","Search");
define("_TITLEVIEW","Live server status");
define("_TITLEBANDETAIL","Details");
define("_TITLEBANADD","Add ban");
define("_TITLEBANADDONLINE","Add online ban");
define("_TITLEAMXADMINS","AMX Mod X admins");
define("_TITLEREASONS","Ban reasons");
define("_TITLESERVERADMINS","Server admins");
define("_TITLESERVER","Server");
define("_TITLEINFO","Information");
define("_TITLELOGS","Logs");
define("_TITLEMODULE","Module");
define("_TITLEUPDATE","Version check");
define("_TITLEUSERLEVEL","User level");
define("_TITLESITE","Page settings");
define("_TITLEUSERMENU","User Menu");
define("_TITLEWEBADMIN","Web admin");
//value check
define("_NOUSERNAME","No username entered!");
define("_NOPASSWORD","No password entered!");
define("_ACCESSINVALID","Access invalid!");
define("_FLAGSBCDMISSING","Flag has to be either B, C or D!");
define("_NONICKNAME","No nickname entered!");
define("_NOTAG","No clan tag/name entered!");
define("_EMAILINVALID","E-mail address not valid!");
define("_STEAMIDINVALID","SteamID not valid!");
define("_IPINVALID","IP address not valid!");
define("_FLAGSINVALID","Flags not valid!");
define("_USERNAMETOSHORT","Name too short!");
define("_USERNAMETOLONG","Name too long!");
define("_NICKNAMETOSHORT","Nickname too short!");
define("_NICKNAMETOLONG","Nickname too long!");
define("_PASSWORDTOSHORT","Password too short!");
define("_PASSWORDTOLONG","Password too long!");
define("_NOREASONSET","No reason name entered!");
define("_REASONSETTOSHORT","Reason group name too short!");
define("_REASONSETTOLONG","Reason group name too long!");
define("_NOREASON","No ban reason entered!");
define("_REASONTOSHORT","Ban reason too short!");
define("_REASONTOLONG","Ban reason too long!");
define("_PASSWORDNOTMATCH","The passwords entered do not match!");
define("_NOCOMMENT","No comment entered!");
define("_NOEDITREASON","No Edit-Reason Entered!");
define("_COMMENTTOSHORT","Comment too short!");
define("_COMMENTTOLONG","Comment too long!");
define("_STEAMTOLONG","SteamID too long!");
define("_STEAMTOSHORT","SteamID too short!");
define("_NOIP","No IP entered!");
define("_IPTOLONG","IP too long!");
define("_IPTOSHORT","IP too short!");
//alerts
define("_SAVEEDIT","Save changes?");
define("_DELBAN","Do you really want to delete this ban?");
define("_DELDEMO","Do you really want to delete this file?");
define("_DELCOMMENT","Do you really want to delete this comment?");
define("_DELADMIN","Do you really want to delete this admin?");
define("_DELLEVEL","Do you really want to delete this level?");
define("_DELLOGSALL","Do you really want to delete all logs?");
define("_DELLOGS","Do you really want to delete these logs?");
define("_SAVESETTINGS","Save settings and apply?");
define("_DATALOSS","\nThe data can NOT be recovered!");
define("_DELSERVER","Do you really want to delete this server?");
//motd
define("_NOEXPIREDBANS","No expired bans");
define("_YOUAREBANNED","You have been banned!!");
//upgrade system
define("_STEP", "Step");
define("_STEP1", "Let's check if it's possible to use the Auto Function");
define("_STEP2", "Download &amp; Unpack"); // &amp; = & = and
define("_STEP3", "Run the Scripts");
define("_FINISH", "Finish");
define("_WEB_OUTDATED", "Your website version is outdated.");
define("_RUN_SCRIPT", "Please run this script to update your AMXBans Version.");
define("_UP_TO_DATE", "Your website version is up-to-date.");
define("_FSF", "File System Functions");
define("_REMOTE_DL", "Remote Download");
define("_UNZIP", "Unpack ZIP");
define("_CRC32CHECK", "CRC32 Check");
define("_REWIND_FUNC", "Rewind Function");
define("_IF_MANUAL", "<b>Note:</b> If you choose 'Manual', step 2 isn't necessary.");
define("_MANUAL", "Manual");
define("_NEXT", "next");
define("_REWIND", "rewind");
define("_CL_LAST_RELEASE", "Click here to view the changelog for the latest release");
define("_NOFILESUNPACK", "No files to unpack!");
define("_WRITE_PROT", "Write protected");
define("_DIR_WRITE_PROT", "Directory is write protected");
define("_SKIP_DIR", "Skipping! Directory already exists");
define("_SKIP_FILE", "File doesn't need to be upgraded");
define("_UNKNOWN_ERROR", "Unknown error!");
define("_CANNOT_CREATE", "Can't create file / directory");
define("_NOTHING_TO_VIEW", "Nothing to view at the moment!");
define("_NODBCHANGES", "No database changes!");
define("_UPGRADE_FINISHED", "Your AMXBans Installation has been updated <b>successfully</b>.<br />Click 'Finish' to continue to your Admin Contol Panel.");
define("_BACKUP_DB_B4", "Remember to backup your files and database before you run this update!");
//new design related
define("_OS", "OS");
define("_VAC", "VAC");
define("_VAC_ALT", "Valve Anti-Cheat");
define("_NA", "N/A");
define("_STATS", "Statistics");
define("_PERM_BANS", "Permanent Bans");
define("_TEMP_BANS", "Temporary Bans");
define("_ACTIVE_SERVERS", "Active Servers");
define("_LATEST_BAN", "Latest Ban");
define("_LATEST_KICKS", "Latest Kicks");
define("_BROWSE_ALL", "Browse All");
define("_POWERED_BY", "Powered by");
define("_DESIGN_BY", "Design by");
define("_NO_BANS", "No Bans in Database");
define("_FIRST_PAGE", "First Page");
define("_LAST_PAGE", "Last Page");
define("_PREVIOUS_PAGE", "Previous Page");
define("_NEXT_PAGE", "Next Page");
define("_PICK_DATE", "Pick a Date");
define("_WEB_VERSION", "Website Version");
define("_WEBSERVER", "Webserver");
define("_MODULES", "Modules");
define("_MIN_OR", "minutes or");
define("_SIZE", "Size");
define("_UPD_CONNECT_ERROR", "No connection could be established to the Update-Server!");
define("_UPD_DB_ERROR", "The Update-Database could not be found.");
define("_UPD_SELECT_ERROR", "The Update-Database could not be selected.");
define("_ADMINID", "Admin's SteamID");
define("_TRACKBACK", "Trackback");
define("_SETUP_EXISTS", "<b>Security Alert!</b><br />setup.php still remains in your AMXBans Directory.<br /><br />You can still access the Admin Control Panel, but we strongly recommend you to remove it! ");
define("_BYTES", "bytes");
define("_MB", "MB");
define("_SUCCESS", "No errors");
define("_ERROR_MYSQL", "Please update your MySQL Version to MySQL 4.1 or higher.");
define("_ERROR_PHP", "Please update your PHP Version to PHP 4.4.4 or higher.");
define("_ERROR_REG_GLOBALS", "Please turn off your register_globals");
define("_ERROR_MAGIC_QUOTES", "Please turn off your magic_quotes");
define("_ERROR_GMP", "Please turn on bcmath and gmp");
?>