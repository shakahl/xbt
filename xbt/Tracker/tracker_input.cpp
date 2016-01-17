#include "stdafx.h"
#include "tracker_input.h"

#include "bt_misc.h"
#include <boost/algorithm/string.hpp>

using namespace boost;

Ctracker_input::Ctracker_input()
{
	m_downloaded = 0;
	m_event = e_none;
	m_ipa = 0;
	m_left = 0;
	m_port = 0;
	m_uploaded = 0;
	m_num_want = -1;
	m_compact = false;
	m_no_peer_id = false;
	m_agent = "---";
}

void Ctracker_input::set(const string& name, const string& value)
{
	if (name.empty())
		return;
	switch (name[0])
	{
	case 'c':
		if (name == "compact")
			m_compact = atoi(value.c_str());
		break;
	case 'd':
		if (name == "downloaded")
			m_downloaded = atoll(value.c_str());
		break;
	case 'e':
		if (name == "event")
		{
			if (value == "completed")
				m_event = e_completed;
			else if (value == "started")
				m_event = e_started;
			else if (value == "stopped")
				m_event = e_stopped;
			else
				m_event = e_none;
		}
		break;
	case 'i':
		if (name == "info_hash" && value.length() == 20)
			m_info_hash = value;
		else if (name == "ip")
			m_ipa = inet_addr(value.c_str());
		break;
	case 'k':
		if (name == "key")
			m_key = value.substr(0, 8);
		break;
	case 'l':
		if (name == "left")
			m_left = atoll(value.c_str());
		break;
	case 'n':
		if (name == "no_peer_id")
			m_no_peer_id = atoi(value.c_str());
		else if (name == "numwant")
			m_num_want = atoi(value.c_str());
		break;
	case 'p':
		if (name == "peer_id" && value.length() == 20)
			m_peer_id = value;
		else if (name == "port")
			m_port = htons(atoi(value.c_str()));
		break;
	case 'u':
		if (name == "uploaded")
			m_uploaded = atoll(value.c_str());
		break;
	}
}

bool Ctracker_input::valid() const
{
	return m_downloaded >= 0
		&& (m_event != e_completed || !m_left)
		&& m_info_hash.length() == 20
		&& m_left >= -1
		&& m_peer_id.length() == 20
		&& m_port >= 0
		&& m_uploaded >= 0;
}

bool Ctracker_input::banned() const
{
	if (m_agent[0] == '*')
		return true;
	if (m_peer_id[7] == '-')
		// standard id
		switch (m_peer_id[0])
		{
		case '-':
			switch (m_peer_id[1])
			{
			case 'A': // -AZ* > Azureus
				return starts_with(m_peer_id, "-AZ2304")
					|| starts_with(m_peer_id, "-AZ2302")
					|| starts_with(m_peer_id, "-AZ2300")
					|| starts_with(m_peer_id, "-AZ2206")
					|| starts_with(m_peer_id, "-AZ2205")
					|| starts_with(m_peer_id, "-AZ2204")
					|| starts_with(m_peer_id, "-AZ2203")
					|| starts_with(m_peer_id, "-AZ2202")
					|| starts_with(m_peer_id, "-AZ2201");
			case 'B': // -BC* > BitComet, -BB* > ?
				return starts_with(m_peer_id, "-BB")
					|| starts_with(m_peer_id, "-BC0060");
			case 'U': // -UT* > uTorrent
				return starts_with(m_peer_id, "-UT11")
					|| starts_with(m_peer_id, "-UT11");
			case 'T': // -TS* > TorrentStorm
				return starts_with(m_peer_id, "-TS");
			default:
				return false;
			}
		//case 'A': // A* > ABC
		//case 'M': // M* > Mainline
		//case 'S': // S* > Shadow
		//case 'T': // T* > BitTornado
		//case 'X': // XBT* > XBT
		default:
			return false;
		}
	else
		switch (m_peer_id[0])
		{
		case '-':
			switch (m_peer_id[1])
			{
			//case 'G': // -G3* > G3
			case 'S': // -SZ* > ?
				return starts_with(m_peer_id, "-SZ");
			default:
				return false;
			}
		case 'e': // exbc* > BitComet/BitLord
			return starts_with(m_peer_id, "exbc0L")
				|| starts_with(m_peer_id, "exbcL")
				|| starts_with(m_peer_id, "exbcLORD")
				|| starts_with(m_peer_id, "exbc\08")
				|| starts_with(m_peer_id, "exbc\09")
				|| starts_with(m_peer_id, "exbc\0:");
		//case 'S': // S57* > Shadow 57
		default:
			return starts_with(m_peer_id, "BS")
				|| starts_with(m_peer_id, "FUTB")
				|| starts_with(m_peer_id, "TO038")
				|| starts_with(m_peer_id, "turbo");
		}
	return false;
}
