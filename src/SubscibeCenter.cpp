#include "SubscibeCenter.h"

#include <Windows.h>
#include <list>

namespace wmp
{
namespace module
{
// 订阅函数重入最大数
#define SUBSCIBE_REENTRY_NUM		20
// 回调函数重入最大数
#define CALLBACK_REENTRY_NUM		5

void SubscibeCenter::Release()
{
	delete this;
}

void SubscibeCenter::OnTimer( wmp::base::ui32 timer_id, wmp::base::ttime now )
{
	wmp::base::ui64 tick_count = ::GetTickCount();
	
	std::list<wmp::base::ui64> lstremove;
	for(tmap_tickcount2event::iterator it = m_delay_event.begin(); it != m_delay_event.end(); ++it)
	{
		if ( it->first < tick_count )
		{
			break;
		}
		tvecevent& rvecenent = it->second;
		for(tvecevent::iterator itevt = rvecenent.begin(); itevt != rvecenent.end(); ++itevt)
		{
			DoPostEvent((*itevt).event_id, (*itevt).pData, (*itevt).len);
		}
		lstremove.push_back(it->first);
	}
	for(std::list<wmp::base::ui64>::iterator it = lstremove.begin(); it != lstremove.end(); ++it)
	{
		m_delay_event.erase(*it);
	}
}

bool SubscibeCenter::Subscibe( IObserver& observer, wmp::base::ui16 event_id, wmp::base::ui8 index, const char* desc )
{
	tvecobserver& rvecobserver = m_mapobserver[event_id];
	if (rvecobserver.empty())
	{
		rvecobserver.resize(0xFF);
	}
	tlstsubscibe_observer& rlstobserver = rvecobserver[index-1];
	tsubscibe_observer obj(&observer,desc);
	rlstobserver.push_back(obj);
	return false;
}

bool SubscibeCenter::Subscibe( IVoter& voter, wmp::base::ui16 event_id, wmp::base::ui8 index, const char* desc )
{
	tvecvoter& rvecvoter = m_mapvoter[event_id];
	if (rvecvoter.empty())
	{
		rvecvoter.resize(0xFF);
	}
	tmap_voter2desc& rvoter2desc = rvecvoter[index-1];
	if (rvoter2desc.find(&voter) == rvoter2desc.end())
	{
		rvoter2desc.insert(std::make_pair(&voter,desc));
		return true;
	}
	return false;
}

bool SubscibeCenter::UnSubscibe( IObserver& observer, wmp::base::ui16 event_id, wmp::base::ui8 index )
{
	tvecobserver& rvecobserver = m_mapobserver[event_id];
	if (rvecobserver.size() >= index )
	{
		tlstsubscibe_observer& rlstobserver = rvecobserver[index-1];
		for(tlstsubscibe_observer::iterator it = rlstobserver.begin(); it != rlstobserver.end(); ++it)
		{
			tsubscibe_observer& robserver = *it;
			if (robserver.obj == &observer)
			{
				if (robserver.counter)
				{
					robserver.remove_flag = true;
				}
				else
				{
					rlstobserver.erase(it);
				}
				break;
			}
		}
	}
	return true;
}

bool SubscibeCenter::UnSubscibe( IVoter& voter, wmp::base::ui16 event_id, wmp::base::ui8 index )
{
	tvecvoter& rvecvoter = m_mapvoter[event_id];
	if (rvecvoter.size() >= index )
	{
		tmap_voter2desc& rvoter2desc = rvecvoter[index-1];
		rvoter2desc.erase(&voter);
	}
	return true;
}

void SubscibeCenter::PostEvent( wmp::base::ui16 event_id, char* pData, wmp::base::ui32 len, wmp::base::ui32 delay_times )
{
	if (!delay_times)
	{
		DoPostEvent(event_id, pData, len);
	}
	else
	{
		wmp::base::ui64 tick_count = ::GetTickCount() + delay_times;
		tvecevent& rvecevent = m_delay_event[tick_count];
		rvecevent.push_back(tdelay_event(event_id,pData,len));
	}
}

bool SubscibeCenter::PostVote( wmp::base::ui16 event_id, char* pData, wmp::base::ui32 len )
{
	tvecvoter& rvecvoter = m_mapvoter[event_id];
	m_loop_voter = true;
	for (tvecvoter::iterator it = rvecvoter.begin(); it != rvecvoter.end(); ++it)
	{
		tmap_voter2desc& voter2desc = *it;
		for(tmap_voter2desc::iterator it_voter = voter2desc.begin(); it_voter != voter2desc.end(); ++it_voter)
		{
			if (!(it_voter->first)->OnVoter(event_id, pData, len))
			{
				return false;
			}
		}
	}
	m_loop_voter = false;
	return true;
}

void SubscibeCenter::DoPostEvent( wmp::base::ui16 event_id, char* pData, wmp::base::ui32 len )
{
	tvecobserver& rvecobserver = m_mapobserver[event_id];
	m_loop_observer = true;
	for (tvecobserver::iterator it = rvecobserver.begin(); it != rvecobserver.end(); ++it)
	{
		tlstsubscibe_observer& rlstobserver = *it;
		for(tlstsubscibe_observer::iterator itvalue = rlstobserver.begin(); itvalue != rlstobserver.end(); )
		{
			tsubscibe_observer& robserver = *itvalue;
			if (!robserver.remove_flag)
			{
				robserver.Add();
				robserver.obj->OnEvent(event_id, pData, len);
				robserver.Sub();
				if (robserver.remove_flag && !robserver.counter)
				{
					itvalue = rlstobserver.erase(itvalue);
				}
				else
				{
					++itvalue;
				}
			}
			else
			{
				if (!robserver.counter)
				{
					itvalue = rlstobserver.erase(itvalue);
				}
				else
				{
					++itvalue;
				}
			}
		}
	}
	m_loop_observer = false;
}

}
}
