#ifndef __MODULE_SUBSCIBE_CENTER__
#define __MODULE_SUBSCIBE_CENTER__

#include <include/ISubscibeCenter.h>

namespace wmp
{
namespace module
{

class SubscibeCenter : public ISubscibeCenter
{
public:
	// �ͷ���Դ
	virtual void Release();

	//************************************
	// Method:    OnTimer
	// FullName:  ISubscibeCenter::OnTimer
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: ��������
	// Parameter: wmp::base::ui32 timer_id				��ʱ��id
	// Parameter: ttime now								��ǰʱ����
	//************************************
	virtual void OnTimer(wmp::base::ui32 timer_id, wmp::base::ttime now);

	//************************************
	// Method:    Subscibe
	// FullName:  ISubscibeCenter::Subscibe
	// Access:    virtual public 
	// Returns:   bool									���ĳɹ�����ture������false
	// Qualifier: �۲��߶����¼�
	// Parameter: IObserver * pObserver					�¼��Ĺ۲���
	// Parameter: wmp::base::ui16 event_id				�¼�id
	// Parameter: wmp::base::uid entity_id				ʵ��id,��ʵ����Ϊ0
	// Parameter: wmp::base::ui8 index					�ڸ��¼��лص���˳��
	// Parameter: const char * pDesc					������Ϣ����
	//************************************
	virtual bool Subscibe(IObserver* observer, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index, const char* desc);

	//************************************
	// Method:    UnSubscibe
	// FullName:  ISubscibeCenter::UnSubscibe
	// Access:    virtual public 
	// Returns:   bool									�˶��ɹ�����ture������false
	// Qualifier: ȡ���۲��߶����¼�
	// Parameter: IObserver * pObserver					�¼��Ĺ۲���	
	// Parameter: wmp::base::ui16 event_id				�¼�id
	// Parameter: wmp::base::uid entity_id				ʵ��id,��ʵ����Ϊ0
	// Parameter: wmp::base::ui8 index					�ڸ��¼��лص���˳��
	//************************************
	virtual bool UnSubscibe(IObserver* observer, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index);

	//************************************
	// Method:    Subscibe
	// FullName:  ISubscibeCenter::Subscibe
	// Access:    virtual public 
	// Returns:   bool									���ĳɹ�����ture������false
	// Qualifier: ͶƱ�߶����¼�
	// Parameter: IVoter * pVoter						ͶƱ��
	// Parameter: wmp::base::ui16 event_id				�¼�id
	// Parameter: wmp::base::uid entity_id				ʵ��id,��ʵ����Ϊ0
	// Parameter: wmp::base::ui8 index					�ڸ��¼��лص���˳��
	// Parameter: const char * pDesc
	//************************************
	virtual bool Subscibe(IVoter* voter, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index, const char* desc);

	//************************************
	// Method:    UnSubscibe
	// FullName:  ISubscibeCenter::UnSubscibe
	// Access:    virtual public 
	// Returns:   bool									�˶��ɹ�����ture������false
	// Qualifier: ȡ��ͶƱ�߶����¼�
	// Parameter: IVoter * voter						ͶƱ��
	// Parameter: wmp::base::ui16 event_id				�¼�id
	// Parameter: wmp::base::uid entity_id				ʵ��id,��ʵ����Ϊ0
	// Parameter: wmp::base::ui8 index					�ڸ��¼��лص���˳��
	//************************************
	virtual bool UnSubscibe(IVoter* voter, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index);

	//************************************
	// Method:    PostEvent
	// FullName:  ISubscibeCenter::PostEvent
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: Ͷ��һ���¼�
	// Parameter: wmp::base::ui16 event_id				�¼�id
	// Parameter: wmp::base::uid entity_id				ʵ��id,��ʵ����Ϊ0
	// Parameter: char * pData							Я��������
	// Parameter: wmp::base::ui32 len					Я�����ݵĳ���
	// Parameter: wmp::base::ui32 delay_times			Ͷ�����¼���delay_times�������ִ�С����delay_timesΪ0��������ִ�У�ע�⣺delay_times ����С��ISubscibeCenter::OnTimer������
	//************************************
	virtual void PostEvent(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len, wmp::base::ui32 delay_times);

	//************************************
	// Method:    PostVote
	// FullName:  ISubscibeCenter::PostVote
	// Access:    virtual public 
	// Returns:   bool									����ͶƱ�߶�ͬ����true����֮������ͶƱ���򷵻�false��������ִ�к����Ļص�
	// Qualifier: Ͷ��һ��ͶƱ�¼�
	// Parameter: wmp::base::ui16 event_id				�¼�id
	// Parameter: wmp::base::uid entity_id				ʵ��id,��ʵ����Ϊ0
	// Parameter: char * pData							Я��������
	// Parameter: wmp::base::ui32 len					Я�����ݵĳ���
	//************************************
	virtual bool PostVote(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len);
};

}
}


#endif // __MODULE_SUBSCIBE_CENTER__