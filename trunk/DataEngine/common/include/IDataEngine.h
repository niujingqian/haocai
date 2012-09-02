#pragma once

//��������ӿ�
#include "DataDefine.h"
#include <vector>
#include <map>
using std::vector;
using std::map;

class EXPORT_CLASS IDataEngine
{
public:

	//�����ֻ�
	virtual void ConnectPhone(CString PhoneDes)=0;

	//�Ͽ������ֻ�
	virtual void StopConnectPhone()=0;

	//�����ֻ���Ϣ
	virtual void RequestPhoneInfo()=0;

	//��ȡ�ֻ���Ϣ
	virtual sPhoneInfo GetPhoneInfo()=0;


	/************��ϵ�˲����ӿ�*************/

	//������ϵ������
	virtual void RequestContactInfo()=0;

	//����ɾ����ϵ��
	virtual void RequestDeleteContactInfo(CString ID)=0;

	//��������ɾ����ϵ��
	virtual void RequestBatchDeleteContactInfo(vector<CString>& ID)=0;

	//����ɾ��������ϵ��
	virtual void RequestDeleteAllContactInfo()=0;

	//���������ϵ��
	virtual void RequestAddContactInfo(sContactInfo& Info)=0;

	//�������������ϵ��
	virtual void RequestBatchAddContactInfo(vector<sContactInfo>& InfoList)=0;

	//����༭��ϵ��
	virtual void RequestEditContactInfo(sContactInfo& Info)=0;

	//������ϵ�˷���
	virtual void RequestContactGroupInfo()=0;

	//����ɾ����ϵ�˷���
	virtual void RequestDeleteContactGroupInfo(CString ID)=0;

	//��������ɾ����ϵ�˷���
	virtual void RequestBatchDeleteContactGroupInfo(vector<CString>& ID)=0;

	//����ɾ��������ϵ�˷���
	virtual void RequestDeleteAllContactGroupInfo()=0;

	//���������ϵ�˷���
	virtual void RequestAddContactGroupInfo(sGroupInfo& Info)=0;

	//�������������ϵ�˷���
	virtual void RequestBatchAddContactGroupInfo(vector<sGroupInfo>& InfoList)=0;
		
	//����༭��ϵ��
	virtual void RequestEditContactGroupInfo(sGroupInfo& Info)=0;

	//��ȡ��ϵ���б�
	virtual vector<sContactInfo>* GetContactInfoList()=0; 

	//��ȡ������ϵ��
	virtual bool  GetContactInfo(CString ID,sContactInfo& Info)=0;    

	//��ȡָ����ϵ�� 
	virtual void GetContactInfo(vector<CString>& IDList,vector<sContactInfo>& Info)=0;    

	//��ȡ��ϵ�˷����б�
	virtual vector<sGroupInfo>* GetContactGroupInfoList()=0;   

	//��ȡ��ϵ�˷���
	virtual bool  GetContactGroupInfo(CString ID,sGroupInfo& Info)=0;        

	//��ȡ��ϵ��ָ������
	virtual void GetContactGroupInfo(vector<CString>& IDList, vector<sGroupInfo>& InfoList)=0;          

	//��ȡͨ����¼�б�
	virtual vector<sCallLogInfo>* GetCallLogInfoList()=0;


	/************���Ų����ӿ�**************/

	//���������Ϣ
	virtual void ReqeustSmsInfo()=0; 

	//����ɾ������
	virtual void RequestDeleteSmsInfo(CString ID)=0;

	//��������ɾ������
	virtual void RequestBatchDeleteSmsInfo(vector<CString>& IDList)=0;

	//����ɾ�����ж��� 
	virtual void RequestDeletAllSmsInfo()=0;

	//�����Ͷ���
	virtual void RequestSendSmsInfo(sSendSmsInfo& Info)=0;

	//�����������Ͷ���
	virtual void RequestBatchSendSmsInfo(vector<sSendSmsInfo>& Info)=0;


	/************Ӧ�ò����ӿ�**************/

	virtual void RequestInstallApk(CString ApkPath,ePathType Type)=0;

	virtual void RequestBatchInstallApk(vector<CString> ApkPath,ePathType Type)=0;

	virtual void UninstallApk(CString ApkPackName)=0;

	virtual void BatchUninstallApk(vector<CString> ApkPackName)=0;
	

	/************�ļ������ӿ�**************/
	
	

};

//��ȡ��������ʵ��
extern EXPORT_API IDataEngine* GetDataEngineInterface(ePhoneOSType Type=PHONE_OS_ANDROID);