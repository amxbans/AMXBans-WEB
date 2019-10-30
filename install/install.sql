DROP TABLE if exists PREFIX_admins_servers, PREFIX_amxadmins,
  PREFIX_bans, PREFIX_bans_edit,
  PREFIX_comments,
  PREFIX_flagged,
  PREFIX_logs,
  PREFIX_permissions,
  PREFIX_reasons, PREFIX_reasons_set, PREFIX_reasons_to_set,
  PREFIX_serverinfo, PREFIX_smilies,
  PREFIX_usermenu,
  PREFIX_webadmins, PREFIX_webconfig;


CREATE TABLE PREFIX_admins_servers
(
  admin_id           SMALLINT UNSIGNED NOT NULL,
  server_id          SMALLINT UNSIGNED NOT NULL,
  custom_flags       varchar(32)       NOT NULL,
  use_static_bantime enum ('yes','no') NOT NULL DEFAULT 'yes'
);

CREATE TABLE PREFIX_amxadmins
(
  id       SMALLINT    NOT NULL AUTO_INCREMENT,
  username varchar(32) NULL,
  password varchar(32) NULL,
  access   varchar(32) NULL,
  flags    varchar(32) NULL,
  steamid  varchar(32) NULL,
  nickname varchar(32) NULL,
  ashow    INT         NULL,
  created  INT         NULL,
  expired  INT         NULL,
  days     INT         NULL,
  PRIMARY KEY (id),
  KEY steamid (steamid)
);

CREATE TABLE PREFIX_bans
(
  bid         INT                 NOT NULL AUTO_INCREMENT,
  player_ip   varchar(32)         NULL,
  player_id   varchar(35)         NULL,
  player_nick varchar(100)        NULL     DEFAULT 'Unknown',
  admin_ip    varchar(32)         NULL,
  admin_id    varchar(35)         NULL,
  admin_nick  varchar(100)        NULL     DEFAULT 'Unknown',
  ban_type    varchar(10)         NULL     DEFAULT 'S',
  ban_reason  varchar(100)        NULL,
  ban_created int                 NULL,
  ban_length  int                 NULL,
  server_ip   varchar(32)         NULL,
  server_name varchar(100)        NULL     DEFAULT 'Unknown',
  ban_kicks   int                 NOT NULL DEFAULT '0',
  expired     TINYINT(1) UNSIGNED NOT NULL DEFAULT 0,
  imported    TINYINT(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (bid),
  KEY player_id (player_id)
);

CREATE TABLE PREFIX_bans_edit
(
  `id`          int          NOT NULL AUTO_INCREMENT,
  `bid`         int          NOT NULL,
  `created_at`  TIMESTAMP    NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `admin_nick`  varchar(32)  NOT NULL DEFAULT 'unknown',
  `edit_reason` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE PREFIX_comments
(
  id         int          NOT NULL AUTO_INCREMENT,
  name       varchar(35)  NOT NULL,
  comment    text         NULL,
  file       VARCHAR(255) NULL,
  email      varchar(100) NOT NULL,
  addr       varchar(32)  NULL,
  created_at TIMESTAMP    NOT NULL DEFAULT CURRENT_TIMESTAMP,
  bid        int          NOT NULL,
  admin_id   int UNSIGNED NULL,
  hidden_by  INT UNSIGNED NULL,
  PRIMARY KEY (id)
);

CREATE TABLE PREFIX_flagged
(
  `fid`         int UNSIGNED NOT NULL auto_increment,
  `player_ip`   varchar(32)  default NULL,
  `player_id`   varchar(35)  default NULL,
  `player_nick` varchar(100) default 'Unknown',
  `admin_ip`    varchar(32)  default NULL,
  `admin_id`    varchar(35)  default NULL,
  `admin_nick`  varchar(100) default 'Unknown',
  `reason`      varchar(100) default NULL,
  `created`     int UNSIGNED default NULL,
  `length`      int UNSIGNED default NULL,
  `server_ip`   varchar(100) default NULL,
  PRIMARY KEY (`fid`),
  KEY `player_id` (`player_id`)
);

CREATE TABLE PREFIX_logs
(
  id         BIGINT      NOT NULL AUTO_INCREMENT,
  created_at TIMESTAMP   NOT NULL DEFAULT CURRENT_TIMESTAMP,
  ip         varchar(32) NULL,
  username   varchar(32) NULL,
  action     varchar(64) NULL,
  remarks    TEXT        NULL,
  PRIMARY KEY (id)
);

CREATE TABLE PREFIX_permissions
(
  level            SMALLINT   NOT NULL,
  bans_add         TINYINT(1) NOT NULL DEFAULT 0,
  bans_edit        TINYINT(1) NOT NULL DEFAULT 0 COMMENT '0=none;1=own;2=all',
  bans_delete      TINYINT(1) NOT NULL DEFAULT 0 COMMENT '0=none;1=own;2=all',
  bans_unban       TINYINT(1) NOT NULL DEFAULT 0 COMMENT '0=none;1=own;2=all',
  amxadmins_view   TINYINT(1) NOT NULL DEFAULT 0,
  amxadmins_edit   TINYINT(1) NOT NULL DEFAULT 0,
  webadmins_view   TINYINT(1) NOT NULL DEFAULT 0,
  webadmins_edit   TINYINT(1) NOT NULL DEFAULT 0,
  websettings_view TINYINT(1) NOT NULL DEFAULT 0,
  websettings_edit TINYINT(1) NOT NULL DEFAULT 0,
  permissions_edit TINYINT(1) NOT NULL DEFAULT 0,
  prune_db         TINYINT(1) NOT NULL DEFAULT 0,
  servers_edit     TINYINT(1) NOT NULL DEFAULT 0,
  ip_view          TINYINT(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (level)
);

CREATE TABLE PREFIX_reasons
(
  id             int          NOT NULL AUTO_INCREMENT,
  reason         varchar(100) NULL,
  static_bantime int          NOT NULL DEFAULT '0',
  PRIMARY KEY (id)
);

CREATE TABLE PREFIX_reasons_set
(
  id      SMALLINT    NOT NULL AUTO_INCREMENT,
  setname varchar(32) NULL,
  PRIMARY KEY (id)
);

CREATE TABLE PREFIX_reasons_to_set
(
  setid    SMALLINT NOT NULL,
  reasonid int      NOT NULL
);

CREATE TABLE PREFIX_serverinfo
(
  id             SMALLINT     NOT NULL AUTO_INCREMENT,
  timestamp      int(11)      NULL,
  hostname       varchar(100) NULL     DEFAULT 'Unknown',
  address        varchar(100) NULL,
  gametype       varchar(32)  NULL,
  rcon           varchar(32)  NULL,
  amxban_version varchar(32)  NULL,
  amxban_motd    varchar(250) NULL,
  motd_delay     int          NULL     DEFAULT '10',
  amxban_menu    int          NOT NULL DEFAULT '1',
  reasons        int          NULL,
  timezone_fixx  int          NOT NULL DEFAULT '0',
  PRIMARY KEY (id)
);

CREATE TABLE PREFIX_smilies
(
  id   SMALLINT    NOT NULL AUTO_INCREMENT,
  code varchar(10) NOT NULL,
  url  varchar(50) NOT NULL,
  name varchar(25) NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE PREFIX_webadmins
(
  id              INT          NOT NULL AUTO_INCREMENT,
  username        varchar(32)  NOT NULL,
  password        varchar(255) NOT NULL,
  perm_level      SMALLINT     NOT NULL DEFAULT '99',
  passreset_code  VARCHAR(50)  NULL,
  passreset_until TIMESTAMP    NULL,
  email           varchar(100) NULL,
  last_action     TIMESTAMP    NULL,
  try             TINYINT(1)   NOT NULL default 0,
  PRIMARY KEY (id),
  UNIQUE (username, email)
);

CREATE TABLE PREFIX_webconfig
(
  id    int(11)      NOT NULL auto_increment,
  name  VARCHAR(255) NOT NULL,
  value TEXT         NULL,
  PRIMARY KEY (id)
);