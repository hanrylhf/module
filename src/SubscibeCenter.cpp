#include "SubscibeCenter.h"


void wmp::module::SubscibeCenter::Release()
{

}

void wmp::module::SubscibeCenter::OnTimer( wmp::base::ui32 timer_id, wmp::base::ttime now )
{

}

bool wmp::module::SubscibeCenter::Subscibe( IObserver* observer, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index, const char* desc )
{
	return false;
}

bool wmp::module::SubscibeCenter::Subscibe( IVoter* voter, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index, const char* desc )
{
	return false;
}

bool wmp::module::SubscibeCenter::UnSubscibe( IObserver* observer, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index )
{
	return false;
}

bool wmp::module::SubscibeCenter::UnSubscibe( IVoter* voter, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index )
{
	return false;
}

void wmp::module::SubscibeCenter::PostEvent( wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len, wmp::base::ui32 delay_times )
{

}

bool wmp::module::SubscibeCenter::PostVote( wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len )
{
	return false;
}
