# XBT Tracker documentation
The original documentation is on sourceforge: [link](http://xbtt.sourceforge.net/tracker/)

## Overview

XBT Tracker is a BitTorrent tracker written in C++. It's designed to offer high performance while consuming little resources (CPU and RAM). It's a pure tracker, so it doesn't offer a frontend. You can use any (PHP) frontend you want.

XBT Tracker listens on port 2710\. The announce URL is http://...:2710/announce. The debug URL is http://...:2710/debug. The scrape URL is http://...:2710/scrape. The statistics URL is http://...:2710/statistics. An experimental UDP tracker extension is also supported via announce URL udp://...:2710.

* * *

## MySQL

The tracker stores stats in a MySQL database/table. Version >= 5 is required. Create a database (xbt) and a user (xbt) with password for the tracker and use these in the next step. Create the tables defined in xbt_tracker.sql.

* * *

## Installing under Windows

1.  Download XBT Tracker from [http://sourceforge.net/project/showfiles.php?group_id=94951&package_id=113737](http://sourceforge.net/project/showfiles.php?group_id=94951&package_id=113737).
2.  Run the executable.
3.  Update xbt_tracker.conf with the database, host, user and pass of your MySQL setup.

There are two ways to run the tracker under Windows (NT, 2000, XP and 2003). The first way is to run the tracker manually, like every other application. The second way is to run the tracker as service. The advantage of this way is that it also runs when no user is logged in.

1.  Open a command window (Start - Run - cmd).
2.  Run net start "XBT Tracker"

* * *

## Starting under Windows

Just start the executable. An empty DOS window should appear.

* * *

## Installing under Linux

The following commands can be used to install the dependencies on Debian. The g++ version should be at least 3.4.

<pre>apt-get install cmake g++ libboost-date-time-dev libboost-dev libboost-filesystem-dev libboost-program-options-dev libboost-regex-dev libboost-serialization-dev libmysqlclient15-dev make subversion zlib1g-dev
</pre>

The following commands can be used to install some of the dependencies on CentOS, Fedora Core and Red Hat. The g++ version should be at least 3.4.

<pre>yum install boost-devel gcc-c++ mysql-devel subversion
</pre>

Enter the following commands in a terminal. Be patient while g++ is running, it'll take a few minutes.

<pre>svn co http://xbt.googlecode.com/svn/trunk/xbt/misc xbt/misc
svn co http://xbt.googlecode.com/svn/trunk/xbt/Tracker xbt/Tracker
cd xbt/Tracker
./make.sh
cp xbt_tracker.conf.default xbt_tracker.conf
</pre>

* * *

## Starting under Linux

Enter the following commands in a terminal.

<pre>./xbt_tracker
</pre>

* * *

## Stopping under Linux

Enter the following commands in a terminal.

<pre>killall xbt_tracker
</pre>

* * *

## Configuration

The tracker reads it's configuration from the file xbt_tracker.conf and the SQL table xbt_config. There is no need to insert default values into this table.

<table>

<tbody>

<tr>

<th align="left">name</th>

<th align="right">default value</th>

</tr>

<tr>

<td>announce_interval</td>

<td align="right">1800</td>

</tr>

<tr>

<td>anonymous_connect</td>

<td align="right">1</td>

</tr>

<tr>

<td>anonymous_announce</td>

<td align="right">1</td>

</tr>

<tr>

<td>anonymous_scrape</td>

<td align="right">1</td>

</tr>

<tr>

<td>auto_register</td>

<td align="right">1</td>

</tr>

<tr>

<td>clean_up_interval</td>

<td align="right">60</td>

</tr>

<tr>

<td>daemon</td>

<td align="right">1</td>

</tr>

<tr>

<td>debug</td>

<td align="right">0</td>

</tr>

<tr>

<td>full_scrape</td>

<td align="right">0</td>

</tr>

<tr>

<td>gzip_debug</td>

<td align="right">1</td>

</tr>

<tr>

<td>gzip_scrape</td>

<td align="right">1</td>

</tr>

<tr>

<td>listen_ipa</td>

<td align="right">*</td>

</tr>

<tr>

<td>listen_port</td>

<td align="right">2710</td>

</tr>

<tr>

<td>log_access</td>

<td align="right">0</td>

</tr>

<tr>

<td>log_announce</td>

<td align="right">0</td>

</tr>

<tr>

<td>log_scrape</td>

<td align="right">0</td>

</tr>

<tr>

<td>offline_message</td>

</tr>

<tr>

<td>pid_file</td>

<td>xbt_tracker.pid</td>

</tr>

<tr>

<td>read_config_interval</td>

<td align="right">60</td>

</tr>

<tr>

<td>read_db_interval</td>

<td align="right">60</td>

</tr>

<tr>

<td>redirect_url</td>

</tr>

<tr>

<td>scrape_interval</td>

<td align="right">0</td>

</tr>

<tr>

<td>table_announce_log</td>

<td>xbt_announce_log</td>

</tr>

<tr>

<td>table_files</td>

<td>xbt_files</td>

</tr>

<tr>

<td>table_files_users</td>

<td>xbt_files_users</td>

</tr>

<tr>

<td>table_scrape_log</td>

<td>xbt_scrape_log</td>

</tr>

<tr>

<td>table_users</td>

<td>xbt_users</td>

</tr>

<tr>

<td>write_db_interval</td>

<td align="right">15</td>

</tr>

</tbody>

</table>

* * *

## Auto Register

If auto_register is on, the tracker will track any torrent. If it's off, the tracker will only track torrents (identified by info_hash) that are in the xbt_files table.

<pre>insert into xbt_files (info_hash, mtime, ctime) values ('<info_hash>', unix_timestamp(), unix_timestamp()); // insert
update xbt_files set flags = 1 where info_hash = '<info_hash>'; // delete
</pre>

* * *

## Anonymous Announce

If anonymous_announce is on, the tracker will serve any user. If it's off, the tracker will only serve users (identified by torrent_pass) that are in the xbt_users table.

The torrent_pass field in xbt_users contains the 32 char torrent_pass. The announce URL contains the same torrent_pass: /<torrent_pass>/announce

## Tables

[Table Documentation](http://visigod.com/xbt-tracker/table-documentation)

This document will try to describe the SQL tables that XBT uses. You can jump directly to the table you're interested by clicking in it's name on the list below:

*   [xbt_announce_log](/xbt-tracker/table-documentation?xbt-table-documentation=&catid=8#xbt_announce_log "xbt_announce_log")
*   [xbt_config](/xbt-tracker/table-documentation?xbt-table-documentation=&catid=8#xbt_config "xbt_config")
*   [xbt_deny_from_clients](/xbt-tracker/table-documentation?xbt-table-documentation=&catid=8#xbt_deny_from_clients "xbt_deny_from_hosts")
*   [xbt_deny_from_hosts](/xbt-tracker/table-documentation?xbt-table-documentation=&catid=8#xbt_deny_from_hosts "xbt_deny_from_hosts")
*   [xbt_files](/xbt-tracker/table-documentation?xbt-table-documentation=&catid=8#xbt_files "xbt_files")
*   [xbt_files_users](/xbt-tracker/table-documentation?xbt-table-documentation=&catid=8#xbt_files_users "xbt_files_users")
*   [xbt_scrape_log](/xbt-tracker/table-documentation?xbt-table-documentation=&catid=8#xbt_scrape_log "xbt_scrape_log")
*   [xbt_users](/xbt-tracker/table-documentation?xbt-table-documentation=&catid=8#xbt_users "xbt_users")

* * *

#### **<a name="xbt_announce_log"></a> xbt_announce_log**

<pre class="brush: sql">create table if not exists xbt_announce_log (
id int not null auto_increment,
ipa int unsigned not null,
port int not null,
event int not null,
info_hash binary(20) not null,
peer_id binary(20) not null,
downloaded bigint unsigned not null,
left0 bigint unsigned not null,
uploaded bigint unsigned not null,
int not null,
mtime int not null,
primary key (id)
);
</pre>

This table is used by the clients when they announce to the tracker. The fields are:

**id** - The record id. Each announce will generate an incremental record.

**ipa** - The client IP address.

**port** - The client source port. Usually defined in the client torrent program. This field can be used to check if the client is connectable or firewalled.

**event** - The torrent event. Can be Start [2], Stop [3], Completed [1] or None [0]

**info_hash** - The torrent hash identifier.

**peer_id** - The client identifier. In this we can see which program the client is using. See the peer id specifications in [theory.org](http://wiki.theory.org/BitTorrentSpecification#peer_id "Theory")

**downloaded** - How much has the client has downloaded.

**left0** - How much the client needs to complete the torrent (how much is left to download).

**uploaded** - How much has the client uploaded

**uid** - The user id (related to the xbt_users table)

**mtime** - The time (Unix timestamp) of the announce

* * *

#### <a name="xbt_config"></a> **xbt_config**

<pre class="brush: sql">create table if not exists xbt_config (
name varchar(255) not null,
value varchar(255) not null
);
</pre>

The xbt_config is where XBT keeps his configuration values. Please see the XBT Configuration page for more details about the available options. The fields are:

**name** - The name of the option.

**value** - The value of the option.

* * *

#### <a name="xbt_deny_from_clients"></a> **xbt_deny_from_clients**

<pre class="brush: sql">create table if not exists xbt_deny_from_clients (
peer_id char(20)notnull,
);
</pre>

The xbt_deny_from_clients is where XBT checks for banned torrent clients. The fields are:

**peer_id** - The identification of the peer. You can check for a more detailed description of the clients in this [link](https://wiki.theory.org/BitTorrentSpecification#peer_id)

* * *

#### <a name="xbt_deny_from_hosts"></a> **xbt_deny_from_hosts**

<pre class="brush: sql">create table if not exists xbt_deny_from_hosts (
begin int unsigned not null,
end int unsigned not null
);
</pre>

The xbt_deny_from_hosts is where XBT checks for banned IP's and/or networks. The fields are:

**begin** - The first IP address to be banned if specifying a network. The IP to be banned if specifying a host.

**end** - The last IP address to be banned if specifying a network. The same IP as in the begin field to be banned if specifying a host.

* * *

#### <a name="xbt_files"></a> **xbt_files**

<pre class="brush: sql">create table if not exists xbt_files (
fid int not null auto_increment,
info_hash binary(20) not null,
leechers int not null default 0,
seeders int not null default 0,
completed int not null default 0,
flags int not null default 0,
mtime int not null,
ctime int not null,
primary key (fid),
unique key (info_hash)
);
</pre>

The xbt_files is where it's stored the information about the torrent files. The fields are:

**fid** - The torrent id (file id).

**info_hash** - The torrent identifier (torrent hash).

**leechers** - The current number of leechers for this torrent.

**seeders** - The current number of seeders for this torrent.

**completed** - The number of times the torrent was fully downloaded (completed download).

**flags** - This field is used to communicate with the tracker. **Usable values**: 0 - No changes. 1 - Torrent should be deleted. 2 - Torrent was updated.

**mtime** - Modification time (unix timestamp). Time of last seeders/leechers/completed status update (Updated by Tracker). - Thanks to rmlr for this tip

**ctime** - Creation time (unix timestamp). Timestamp from when the hash/torrent was added (Created by the frontend).- Thanks to rmlr for this tip

* * *

#### <a name="xbt_files_users"></a> **xbt_files_users**

<pre class="brush: sql">create table if not exists xbt_files_users (
fid int not null,
uid int not null,
active tinyint not null,
announced int not null,
completed int not null,
downloaded bigint unsigned not null,
`left` bigint unsigned not null,
uploaded bigint unsigned not null,
mtime int not null,
unique key (fid, uid),
key (uid)
);
</pre>

The xbt_files_users table is the "connection" between the torrent and the user. Each torrent that is downloaded or uploaded by a user will create a record here. The fields are:

**fid** - The torrent identifier (torrent id).

**uid** - The user identifier (user id).

**active** - 0 if the user is not active on this torrent. 1 if it's active.

**announced** - The number of times the user announced this torrent.

**completed** - 0 if the user hasn't completed the torrent. 1 if the user has completed (has downloaded the torrent completely)

**downloaded** - How many bytes has the user downloaded from this torrent.

**left** - How many bytes are left to download.

**uploaded** - How many bytes has the user uploaded for this torrent.

**mtime** - The last time (Unix timestamp) the record was updated (usually when the user announces the torrent)

* * *

#### <a name="xbt_scrape_log"></a> **xbt_scrape_log**

<pre class="brush: sql">create table if not exists xbt_scrape_log (
id int not null auto_increment,
ipa int unsigned not null,
info_hash binary(20),
uid int not null,
mtime int not null,
primary key (id)
);
</pre>

The xbt_scrape_log is used when the user scrapes the torrent. It's basically the same as the xbt_announce_log but for scrape. The fields are:

**id** - The record id. It's an auto incremental value for every record that is added to the table.

**ipa** - The user IP address.

**info_hash** - The torrent hash (torrent identifier).

**uid** - The user ID (user identifier).

**mtime** -  The last time (Unix timestamp) the torrent was scraped. Usually updated when the user scrapes.

* * *

#### **<a name="xbt_users"></a> xbt_users**

<pre class="brush: sql">create table if not exists xbt_users (
uid int not null auto_increment,
can_leech tinyint not null default 1,
wait_time int not null default 0,
peers_limit int not null default 0,
torrents_limit int not null default 0,
torrent_pass char(32) not null,
torrent_pass_version int not null default 0,
downloaded bigint unsigned not null default 0,
uploaded bigint unsigned not null default 0,
primary key (uid)
);
</pre>

**uid** - The user id (user identifier).The xbt_users is the user table. It keeps updated records for the users. The fields are:

**can_leech** - 0 if the user can't leech (download the files inside the torrent). 1 if the user can. _Optional field._

**wait_time** - The time the user must wait between the date of the torrent and the download. Value in seconds. The default is 0 (no wait time). _Optional field._

**peers_limit** - The number of different computers the user is allowed to use simultaneously. The default is 0 (unlimited). _Optional field._

**torrents_limit** - The number of simultaneous torrents the user is allowed to leech at the same time. The default is 0 (unlimited). _Optional field._

**torrent_pass** - A unique identifier for the user. Each torrent that the user downloads will have the torrent_pass in the announce URL. The user will have the same torrent_pass in every torrent he/she downloads. This is deprecated and replaced by the torrent_pass_version. _Optional field._

**torrent_pass_version** - The new unique identifier for the user. Each time a user downloads a torrent a new key is generated and added to the tracker announce URL (in the torrent). This value is also increased. This way each torrent will have it's own torrent_pass and can't be reused on other torrents.

**downloaded** - The value of downloaded bytes by the user. A sum of all the "download" values the user has in the xbt_files_users.

**uploaded** - The value of uploaded bytes by the user. A sum of all the "upload" values the user has in the xbt_files_users.

Another changes in the xbt database are:

For the peer speed modification:

<pre class="brush: sql">alter table xbt_files_users add down_rate int unsigned not null;
alter table xbt_files_users add up_rate int unsigned not null;
</pre>

To delete the files inside each torrent when we delete the torrent from the table:

<pre class="brush: sql">alter table xbt_files_users add foreign key (fid) references xbt_files (fid) on delete cascade;
alter table xbt_files_users add foreign key (uid) references xbt_users (uid) on delete cascade;
</pre>