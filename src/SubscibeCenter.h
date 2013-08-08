#ifndef __MODULE_SUBSCIBE_CENTER__
#define __MODULE_SUBSCIBE_CENTER__

#include <include/ISubscibeCenter.h>

#include <map>
#include <vector>
#include <list>

namespace wmp
{
namespace module
{

class SubscibeCenter : public ISubscibeCenter
{
	struct tdelay_event
	{
		wmp::base::ui32 len;		
		wmp::base::ui16 event_id;
		char* pData;
		tdelay_event() { memset(this,0,sizeof(this)); }
		tdelay_event(wmp::base::ui16 id, char* data, wmp::base::ui32 len_): len(len_),event_id(id),pData(data){}
	};
	typedef std::vector<tdelay_event>				tvecevent;
	typedef std::map<wmp::base::ui64,tvecevent>		tmap_tickcount2event;

	template<typename T>
	struct tsubscibe_info
	{
		T* obj;
		std::string desc;
		bool remove_flag;
		wmp::base::ui8 counter;
		tsubscibe_info( T* obj_, const char* desc_):obj(obj_),desc(desc_),remove_flag(false),counter(0){}
		void Add(){ ++counter;}
		void Sub(){ counter > 0 ? --counter : 0;}
	};

	typedef tsubscibe_info<IObserver>				tsubscibe_observer;
	typedef std::list<tsubscibe_observer>			tlstsubscibe_observer;
	typedef std::vector<tlstsubscibe_observer>		tvecobserver;
	// key : event_id
	typedef std::map<wmp::base::ui16,tvecobserver>	tmap_evtid2observer;	

	typedef tsubscibe_info<IVoter>					tsubscibe_vote;
	typedef std::list<tsubscibe_vote>				tlstsubscibe_vote;
	typedef std::vector<tlstsubscibe_vote>			tvecvoter;
	// key : event_id
	typedef std::map<wmp::base::ui16,tvecvoter>		tmap_evtid2voter;	
public:
	// 释放资源
	virtual void Release();

	//************************************
	// Method:    OnTimer
	// FullName:  ISubscibeCenter::OnTimer
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: 订阅中心
	// Parameter: wmp::base::ui32 timer_id              定时器id
	// Parameter: ttime now                             当前时间秒
	//************************************
	virtual void OnTimer(wmp::base::ui32 timer_id, wmp::base::ttime now);

	//************************************
	// Method:    Subscibe
	// FullName:  ISubscibeCenter::Subscibe
	// Access:    virtual public 
	// Returns:   bool                                  订阅成功返回ture，否则false
	// Qualifier: 观察者订阅事件
	// Parameter: IObserver * pObserver                 事件的观察者
	// Parameter: wmp::base::ui16 event_id              事件id
	// Parameter: wmp::base::ui8 index                  在该事件中回调的顺序
	// Parameter: const char * pDesc                    订阅信息描述
	//************************************
	virtual bool Subscibe(IObserver& observer, wmp::base::ui16 event_id, wmp::base::ui8 index, const char* desc);

	//************************************
	// Method:    UnSubscibe
	// FullName:  ISubscibeCenter::UnSubscibe
	// Access:    virtual public 
	// Returns:   bool                                  退订成功返回ture，否则false
	// Qualifier: 取消观察者订阅事件
	// Parameter: IObserver * pObserver                 事件的观察者	
	// Parameter: wmp::base::ui16 event_id              事件id
	// Parameter: wmp::base::ui8 index                  在该事件中回调的顺序
	//************************************
	virtual bool UnSubscibe(IObserver& observer, wmp::base::ui16 event_id, wmp::base::ui8 index);

	//************************************
	// Method:    Subscibe
	// FullName:  ISubscibeCenter::Subscibe
	// Access:    virtual public 
	// Returns:   bool                                  订阅成功返回ture，否则false
	// Qualifier: 投票者订阅事件
	// Parameter: IVoter * pVoter                       投票者
	// Parameter: wmp::base::ui16 event_id              事件id
	// Parameter: wmp::base::ui8 index                  在该事件中回调的顺序
	// Parameter: const char * pDesc
	//************************************
	virtual bool Subscibe(IVoter& voter, wmp::base::ui16 event_id, wmp::base::ui8 index, const char* desc);

	//************************************
	// Method:    UnSubscibe
	// FullName:  ISubscibeCenter::UnSubscibe
	// Access:    virtual public 
	// Returns:   bool                                  退订成功返回ture，否则false
	// Qualifier: 取消投票者订阅事件
	// Parameter: IVoter * voter                        投票者
	// Parameter: wmp::base::ui16 event_id              事件id
	// Parameter: wmp::base::ui8 index                  在该事件中回调的顺序
	//************************************
	virtual bool UnSubscibe(IVoter& voter, wmp::base::ui16 event_id, wmp::base::ui8 index);

	//************************************
	// Method:    PostEvent
	// FullName:  ISubscibeCenter::PostEvent
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: 投掷一个事件
	// Parameter: wmp::base::ui16 event_id              事件id
	// Parameter: char * pData                          携带的数据
	// Parameter: wmp::base::ui32 len                   携带数据的长度
	// Parameter: wmp::base::ui32 delay_times           投掷的事件在delay_times毫秒后再执行。如果delay_times为0，则立即执行；注意：delay_times 不能小于ISubscibeCenter::OnTimer的周期
	//************************************
	virtual void PostEvent(wmp::base::ui16 event_id, char* pData, wmp::base::ui32 len, wmp::base::ui32 delay_times);

	//************************************
	// Method:    PostVote
	// FullName:  ISubscibeCenter::PostVote
	// Access:    virtual public 
	// Returns:   bool                                  所有投票者都同意者true，反之遇到不投票者则返回false，不继续执行后续的回调
	// Qualifier: 投递一个投票事件
	// Parameter: wmp::base::ui16 event_id              事件id
	// Parameter: char * pData                          携带的数据
	// Parameter: wmp::base::ui32 len                   携带数据的长度
	//************************************
	virtual bool PostVote(wmp::base::ui16 event_id, char* pData, wmp::base::ui32 len);

private:
	void DoPostEvent(wmp::base::ui16 event_id, char* pData, wmp::base::ui32 len);

private:
	// 观察者列表
	tmap_evtid2observer		m_mapobserver;
	// 是否在循环观察者列表
	bool					m_loop_observer;
	// 投票者列表
	tmap_evtid2voter		m_mapvoter;
	// 是否在循环投票者列表
	bool					m_loop_voter;
	// 延迟执行事件列表
	tmap_tickcount2event	m_delay_event;
};

}
}


#endif // __MODULE_SUBSCIBE_CENTER__