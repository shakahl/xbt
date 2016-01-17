CREATE TABLE xbt_announce_log
(
  id int NOT NULL auto_increment,
  ipa int unsigned NOT NULL,
  port int NOT NULL,
  event int NOT NULL,
  info_hash blob NOT NULL,
  peer_id blob NOT NULL,
  downloaded bigint NOT NULL,
  left0 bigint NOT NULL,
  uploaded bigint NOT NULL,
  uid int NOT NULL,
  mtime int NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE xbt_config
(
  name varchar(255) NOT NULL,
  value varchar(255) NOT NULL
);

CREATE TABLE xbt_deny_from_hosts
(
  begin int NOT NULL,
  end int NOT NULL
);

CREATE TABLE xbt_files
(
  fid int NOT NULL auto_increment,
  info_hash blob NOT NULL,
  leechers int NOT NULL,
  seeders int NOT NULL,
  completed int NOT NULL,
  announced_http int(11) NOT NULL,
  announced_http_compact int(11) NOT NULL,
  announced_http_no_peer_id int(11) NOT NULL,
  announced_udp int(11) NOT NULL,
  scraped_http int(11) NOT NULL,
  scraped_udp int(11) NOT NULL,
  started int(11) NOT NULL,
  stopped int(11) NOT NULL,
  flags int(11) NOT NULL,
  mtime int(11) NOT NULL,
  ctime int(11) NOT NULL,
  balance int(11) NOT NULL,
  freetorrent int(11) NOT NULL default '0',
  PRIMARY KEY (fid),
  UNIQUE KEY (info_hash(20))
);

CREATE TABLE `xbt_files_users` (
  `uid` int(11) NOT NULL,
  `active` tinyint(4) NOT NULL,
  `announced` int(11) NOT NULL,
  `completed` int(11) NOT NULL,
  `downloaded` bigint(20) NOT NULL,
  `left` bigint(20) NOT NULL,
  `uploaded` bigint(20) NOT NULL,
  `upspeed` bigint(20) NOT NULL,
  `downspeed` bigint(20) NOT NULL,
  `timespent` bigint(20) NOT NULL,
  `useragent` varchar(51) NOT NULL,
  `connectable` tinyint(4) NOT NULL default '1',
  `peer_id` varchar(8) NOT NULL,
  `fid` int(11) NOT NULL,
  `ipa` int(11) NOT NULL,
  `mtime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
UNIQUE KEY `uid_2` (`uid`,`fid`,`ipa`),
KEY `uid` (`uid`)
);
				
CREATE TABLE xbt_scrape_log
(
  id int NOT NULL auto_increment,
  ipa int NOT NULL,
  info_hash blob,
  uid int NOT NULL,
  mtime int NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE xbt_users
(
  uid int NOT NULL auto_increment,
  name char(8) NOT NULL,
  pass blob NOT NULL,
  can_leech tinyint NOT NULL default 1,
  wait_time int NOT NULL,
  peers_limit int NOT NULL,
  torrents_limit int NOT NULL,
  torrent_pass char(32) NOT NULL,
  torrent_pass_secret bigint NOT NULL,
  downloaded bigint NOT NULL,
  uploaded bigint NOT NULL,
  fid_end int(11) NOT NULL,
  PRIMARY KEY (uid)
);

CREATE TABLE `xbt_cheat` (
  `id` int(11) NOT NULL auto_increment,
  `uid` int(11) NOT NULL,
  `ipa` int(10) unsigned NOT NULL,
  `upspeed` bigint(20) NOT NULL,
  `tstamp` int(11) NOT NULL,
  `uploaded` bigint(20) NOT NULL,
PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

CREATE TABLE `xbt_snatched` (
  `uid` int(11) NOT NULL default '0',
  `tstamp` int(11) NOT NULL,
  `fid` int(11) NOT NULL
) ENGINE=MyISAM;