/********************************************************************
	created:	2013/08/03	17:14
	filename: 	.\module\include\ISubscibeCenter.h
	author:		hanry.liao
	purpose:	֪ͨ����ʵ�֣�Observerģʽ��

	����Ҫ��:	1)֧�ֻص�ָ���ص�˳��
				2)֧��ͶƱ��ʽ(����������false�Ļص�����ֹ�����Ļص�)�ص�
*********************************************************************/

#ifndef __MODULE_ISUBSCIBE_CENTER__
#define __MODULE_ISUBSCIBE_CENTER__

#include "BaseDefine.h"

namespace wmp
{
namespace module
{
// ִ���¼�sink
struct IObserver  
{
	virtual void OnEvent(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len) = 0;
};

// ͶƱ�߽ӿ�
struct IVoter
{
	virtual bool OnVoter(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len) = 0;
};

// �������Ľӿ�
struct ISubscibeCenter
{
	// �ͷ���Դ
	virtual void Release() = 0;

	//************************************
	// Method:    OnTimer
	// FullName:  ISubscibeCenter::OnTimer
	// Access:    virtual public 
	// Returns:   void
	// Qualifier: ��������
	// Parameter: wmp::base::ui32 timer_id				��ʱ��id
	// Parameter: ttime now								��ǰʱ����
	//************************************
	virtual void OnTimer(wmp::base::ui32 timer_id, wmp::base::ttime now) = 0;

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
	virtual bool Subscibe(IObserver* observer, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index, const char* desc) = 0;

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
	virtual bool UnSubscibe(IObserver* observer, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index) = 0;

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
	virtual bool Subscibe(IVoter* voter, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index, const char* desc) = 0;

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
	virtual bool UnSubscibe(IVoter* voter, wmp::base::ui16 event_id, wmp::base::uid entity_id, wmp::base::ui8 index) = 0;

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
	virtual void PostEvent(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len, wmp::base::ui32 delay_times) = 0;

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
	virtual bool PostVote(wmp::base::ui16 event_id, wmp::base::uid entity_id, char* pData, wmp::base::ui32 len) = 0;
};

}
}
#endif // __MODULE_ISUBSCIBE_CENTER__
