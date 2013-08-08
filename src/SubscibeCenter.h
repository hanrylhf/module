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
	// �ͷ���Դ
	virtual void Release();

	//************************************
	// Method:    OnTimer
	// FullName:  ISubscibeCenter::OnTimer
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: ��������
	// Parameter: wmp::base::ui32 timer_id              ��ʱ��id
	// Parameter: ttime now                             ��ǰʱ����
	//************************************
	virtual void OnTimer(wmp::base::ui32 timer_id, wmp::base::ttime now);

	//************************************
	// Method:    Subscibe
	// FullName:  ISubscibeCenter::Subscibe
	// Access:    virtual public 
	// Returns:   bool                                  ���ĳɹ�����ture������false
	// Qualifier: �۲��߶����¼�
	// Parameter: IObserver * pObserver                 �¼��Ĺ۲���
	// Parameter: wmp::base::ui16 event_id              �¼�id
	// Parameter: wmp::base::ui8 index                  �ڸ��¼��лص���˳��
	// Parameter: const char * pDesc                    ������Ϣ����
	//************************************
	virtual bool Subscibe(IObserver& observer, wmp::base::ui16 event_id, wmp::base::ui8 index, const char* desc);

	//************************************
	// Method:    UnSubscibe
	// FullName:  ISubscibeCenter::UnSubscibe
	// Access:    virtual public 
	// Returns:   bool                                  �˶��ɹ�����ture������false
	// Qualifier: ȡ���۲��߶����¼�
	// Parameter: IObserver * pObserver                 �¼��Ĺ۲���	
	// Parameter: wmp::base::ui16 event_id              �¼�id
	// Parameter: wmp::base::ui8 index                  �ڸ��¼��лص���˳��
	//************************************
	virtual bool UnSubscibe(IObserver& observer, wmp::base::ui16 event_id, wmp::base::ui8 index);

	//************************************
	// Method:    Subscibe
	// FullName:  ISubscibeCenter::Subscibe
	// Access:    virtual public 
	// Returns:   bool                                  ���ĳɹ�����ture������false
	// Qualifier: ͶƱ�߶����¼�
	// Parameter: IVoter * pVoter                       ͶƱ��
	// Parameter: wmp::base::ui16 event_id              �¼�id
	// Parameter: wmp::base::ui8 index                  �ڸ��¼��лص���˳��
	// Parameter: const char * pDesc
	//************************************
	virtual bool Subscibe(IVoter& voter, wmp::base::ui16 event_id, wmp::base::ui8 index, const char* desc);

	//************************************
	// Method:    UnSubscibe
	// FullName:  ISubscibeCenter::UnSubscibe
	// Access:    virtual public 
	// Returns:   bool                                  �˶��ɹ�����ture������false
	// Qualifier: ȡ��ͶƱ�߶����¼�
	// Parameter: IVoter * voter                        ͶƱ��
	// Parameter: wmp::base::ui16 event_id              �¼�id
	// Parameter: wmp::base::ui8 index                  �ڸ��¼��лص���˳��
	//************************************
	virtual bool UnSubscibe(IVoter& voter, wmp::base::ui16 event_id, wmp::base::ui8 index);

	//************************************
	// Method:    PostEvent
	// FullName:  ISubscibeCenter::PostEvent
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: Ͷ��һ���¼�
	// Parameter: wmp::base::ui16 event_id              �¼�id
	// Parameter: char * pData                          Я��������
	// Parameter: wmp::base::ui32 len                   Я�����ݵĳ���
	// Parameter: wmp::base::ui32 delay_times           Ͷ�����¼���delay_times�������ִ�С����delay_timesΪ0��������ִ�У�ע�⣺delay_times ����С��ISubscibeCenter::OnTimer������
	//************************************
	virtual void PostEvent(wmp::base::ui16 event_id, char* pData, wmp::base::ui32 len, wmp::base::ui32 delay_times);

	//************************************
	// Method:    PostVote
	// FullName:  ISubscibeCenter::PostVote
	// Access:    virtual public 
	// Returns:   bool                                  ����ͶƱ�߶�ͬ����true����֮������ͶƱ���򷵻�false��������ִ�к����Ļص�
	// Qualifier: Ͷ��һ��ͶƱ�¼�
	// Parameter: wmp::base::ui16 event_id              �¼�id
	// Parameter: char * pData                          Я��������
	// Parameter: wmp::base::ui32 len                   Я�����ݵĳ���
	//************************************
	virtual bool PostVote(wmp::base::ui16 event_id, char* pData, wmp::base::ui32 len);

private:
	void DoPostEvent(wmp::base::ui16 event_id, char* pData, wmp::base::ui32 len);

private:
	// �۲����б�
	tmap_evtid2observer		m_mapobserver;
	// �Ƿ���ѭ���۲����б�
	bool					m_loop_observer;
	// ͶƱ���б�
	tmap_evtid2voter		m_mapvoter;
	// �Ƿ���ѭ��ͶƱ���б�
	bool					m_loop_voter;
	// �ӳ�ִ���¼��б�
	tmap_tickcount2event	m_delay_event;
};

}
}


#endif // __MODULE_SUBSCIBE_CENTER__