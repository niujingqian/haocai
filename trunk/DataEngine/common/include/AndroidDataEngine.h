#pragma once
#include "idataengine.h"
#include "MessageCenter.h"
#include "../../connect/ConnectThread.h"
#include "../../contact/ContactThread.h"
#include "../../sms/SmsThread.h"

class EXPORT_CLASS CAndroidDataEngine :public IDataEngine,public IMessageHandle
{
public:
	CAndroidDataEngine(void);

	~CAndroidDataEngine(void);

public:

	//ע����Ϣ
	void RegisterMessage();

	//ע����Ϣ
	void UnRegisterMessage();

	//��Ӧ��Ϣ
	virtual void OnMessage(eMessage Message,DWORD SystemMsg=0,WPARAM wParam=0,LPARAM lParam=0);

	//�����ֻ�
	void ConnectPhone(CString ConnectInfo);

	//�Ͽ������ֻ�
	void StopConnectPhone();

	//�����ֻ���Ϣ
	void RequestPhoneInfo();

	//��ȡ�ֻ���Ϣ
	sPhoneInfo GetPhoneInfo();


	/************��ϵ�˲����ӿ�*************/

	//������ϵ������
	void RequestContactInfo();

	//����ɾ����ϵ��
	void RequestDeleteContactInfo(CString ID);

	//��������ɾ����ϵ��
	void RequestBatchDeleteContactInfo(vector<CString>& IDList);

	//����ɾ��������ϵ��
	void RequestDeleteAllContactInfo();

	//���������ϵ��
	void RequestAddContactInfo(sContactInfo& Info);

	//�������������ϵ��
	void RequestBatchAddContactInfo(vector<sContactInfo>& InfoList);

	//����༭��ϵ��
	void RequestEditContactInfo(sContactInfo& Info);

	//������ϵ�˷���
	void RequestContactGroupInfo();

	//����ɾ����ϵ�˷���
	void RequestDeleteContactGroupInfo(CString ID);

	//��������ɾ����ϵ�˷���
	void RequestBatchDeleteContactGroupInfo(vector<CString>& IDList);

	//����ɾ��������ϵ�˷���
	void RequestDeleteAllContactGroupInfo();

	//���������ϵ�˷���
	void RequestAddContactGroupInfo(sGroupInfo& Info);

	//�������������ϵ�˷���
	void RequestBatchAddContactGroupInfo(vector<sGroupInfo>& InfoList);
		
	//����༭��ϵ�˷���
	void RequestEditContactGroupInfo(sGroupInfo& Info);

	//��ȡ��ϵ���б�
	vector<sContactInfo>* GetContactInfoList(); 

	//��ȡ������ϵ��
	bool GetContactInfo(CString ID,sContactInfo& Info);

	//��ȡָ����ϵ�� 
	void GetContactInfo(vector<CString>& IDList,vector<sContactInfo>& InfoList);    

	//��ȡ��ϵ�˷����б�
	vector<sGroupInfo>* GetContactGroupInfoList();   

	//��ȡ��ϵ�˷���
	bool GetContactGroupInfo(CString ID,sGroupInfo& Info);        

	//��ȡ��ϵ��ָ������
	void GetContactGroupInfo(vector<CString>& IDList,vector<sGroupInfo>& InfoList);       

	//��ȡͨ����¼�б�
	vector<sCallLogInfo>* GetCallLogInfoList();


	/************���Ų����ӿ�**************/

	//���������Ϣ
	void ReqeustSmsInfo(); 

	//����ɾ������
	void RequestDeleteSmsInfo(CString ID);

	//��������ɾ������
	void RequestBatchDeleteSmsInfo(vector<CString>& IDList);

	//����ɾ�����ж��� 
	void RequestDeletAllSmsInfo();

	//�����Ͷ���
	void RequestSendSmsInfo(sSendSmsInfo& Info);

	//�����������Ͷ���
	void RequestBatchSendSmsInfo(vector<sSendSmsInfo>& Info);

	/************Ӧ�ò����ӿ�**************/

	void RequestInstallApk(CString ApkPath,ePathType Type);

	void RequestBatchInstallApk(vector<CString> ApkPath,ePathType Type);

	void UninstallApk(CString ApkPackName);

	void BatchUninstallApk(vector<CString> ApkPackName);
	

	/************�ļ������ӿ�**************/

private:

	//��ϵ������
	void SortContactInfo(vector<sContactInfo>&SortData,eContactSortType Type=CONTACT_SORT_BY_NAME);

	//������ϵ����Ϣ
	void DoContactMsg(WPARAM wParam,LPARAM lParam);

	//���������Ϣ
	void DoSmsMsg(WPARAM wParam,LPARAM lParam);

	//������ϵ�˷�����Ϣ
	void DoContactGroupMsg(WPARAM wParam,LPARAM lParam);

	//��������ϵ��ƥ��
	void SmsMatchContact(vector<sSmsInfo>*);


private:
	vector<sContactInfo>            m_ContactInfoList;         //��ϵ�������б�
	vector<sGroupInfo>              m_GroupInfoList;           //��ϵ�˷��������б�
	vector<sCallLogInfo>            m_CallLogInfoList;         //ͨ����¼�б�
	map<CString,vector<sSmsInfo>>   m_SmsInfoList;             //�����б�
	sPhoneInfo                      m_PhoneInfo;               //�ֻ���Ϣ

private:

	CConnectThread                  m_ConnectThread;           //���ӹ����߳�
	CContactThread                  m_ContactThread;           //��ϵ�˹����߳�

	CSmsThread						m_SmsThread;			   //���Ź����߳�
};




