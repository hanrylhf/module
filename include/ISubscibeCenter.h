/********************************************************************
	created:	2013/08/03	17:14
	filename: 	.\module\include\ISubscibeCenter.h
	author:		hanry.liao
	purpose:	通知机制实现（Observer模式）

	基本要求:	1)支持回调指定回调顺序
				2)支持投票方式(即遇到返回false的回调后，终止后续的回调)回调
*********************************************************************/

#ifndef __MODULE_ISUBSCIBE_CENTER__
#define __MODULE_ISUBSCIBE_CENTER__

#include "BaseDefine.h"

namespace wmp
{
namespace module
{
// 执行事件sink
struct IObserver  
{
	virtual void OnEvent(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len) = 0;
};

// 投票者接口
struct IVoter
{
	virtual bool OnVoter(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len) = 0;
};

// 订阅中心接口
struct ISubscibeCenter
{
	// 释放资源
	virtual void Release() = 0;

	//************************************
	// Method:    OnTimer
	// FullName:  ISubscibeCenter::OnTimer
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: 订阅中心
	// Parameter: wmp::base::ui32 timer_id				定时器id
	// Parameter: ttime now								当前时间秒
	//************************************
	virtual void OnTimer(wmp::base::ui32 timer_id, wmp::base::ttime now) = 0;

	//************************************
	// Method:    Subscibe
	// FullName:  ISubscibeCenter::Subscibe
	// Access:    virtual public 
	// Returns:   bool									订阅成功返回ture，否则false
	// Qualifier: 观察者订阅事件
	// Parameter: IObserver * pObserver					事件的观察者
	// Parameter: wmp::base::ui16 event_id				事件id
	// Parameter: wmp::base::uid entity_id				实体id,非实体则为0
	// Parameter: wmp::base::ui8 index					在该事件中回调的顺序
	// Parameter: const char * pDesc					订阅信息描述
	//************************************
	virtual bool Subscibe(IObserver* observer, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index, const char* desc) = 0;

	//************************************
	// Method:    UnSubscibe
	// FullName:  ISubscibeCenter::UnSubscibe
	// Access:    virtual public 
	// Returns:   bool									退订成功返回ture，否则false
	// Qualifier: 取消观察者订阅事件
	// Parameter: IObserver * pObserver					事件的观察者	
	// Parameter: wmp::base::ui16 event_id				事件id
	// Parameter: wmp::base::uid entity_id				实体id,非实体则为0
	// Parameter: wmp::base::ui8 index					在该事件中回调的顺序
	//************************************
	virtual bool UnSubscibe(IObserver* observer, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index) = 0;

	//************************************
	// Method:    Subscibe
	// FullName:  ISubscibeCenter::Subscibe
	// Access:    virtual public 
	// Returns:   bool									订阅成功返回ture，否则false
	// Qualifier: 投票者订阅事件
	// Parameter: IVoter * pVoter						投票者
	// Parameter: wmp::base::ui16 event_id				事件id
	// Parameter: wmp::base::uid entity_id				实体id,非实体则为0
	// Parameter: wmp::base::ui8 index					在该事件中回调的顺序
	// Parameter: const char * pDesc
	//************************************
	virtual bool Subscibe(IVoter* voter, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index, const char* desc) = 0;

	//************************************
	// Method:    UnSubscibe
	// FullName:  ISubscibeCenter::UnSubscibe
	// Access:    virtual public 
	// Returns:   bool									退订成功返回ture，否则false
	// Qualifier: 取消投票者订阅事件
	// Parameter: IVoter * voter						投票者
	// Parameter: wmp::base::ui16 event_id				事件id
	// Parameter: wmp::base::uid entity_id				实体id,非实体则为0
	// Parameter: wmp::base::ui8 index					在该事件中回调的顺序
	//************************************
	virtual bool UnSubscibe(IVoter* voter, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index) = 0;

	//************************************
	// Method:    PostEvent
	// FullName:  ISubscibeCenter::PostEvent
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: 投掷一个事件
	// Parameter: wmp::base::ui16 event_id				事件id
	// Parameter: wmp::base::uid entity_id				实体id,非实体则为0
	// Parameter: char * pData							携带的数据
	// Parameter: wmp::base::ui32 len					携带数据的长度
	// Parameter: wmp::base::ui32 delay_times			投掷的事件在delay_times毫秒后再执行。如果delay_times为0，则立即执行；注意：delay_times 不能小于ISubscibeCenter::OnTimer的周期
	//************************************
	virtual void PostEvent(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len, wmp::base::ui32 delay_times) = 0;

	//************************************
	// Method:    PostVote
	// FullName:  ISubscibeCenter::PostVote
	// Access:    virtual public 
	// Returns:   bool									所有投票者都同意者true，反之遇到不投票者则返回false，不继续执行后续的回调
	// Qualifier: 投递一个投票事件
	// Parameter: wmp::base::ui16 event_id				事件id
	// Parameter: wmp::base::uid entity_id				实体id,非实体则为0
	// Parameter: char * pData							携带的数据
	// Parameter: wmp::base::ui32 len					携带数据的长度
	//************************************
	virtual bool PostVote(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len) = 0;
};

}
}
#endif // __MODULE_ISUBSCIBE_CENTER__
