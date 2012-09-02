#include "StdAfx.h"
#include "../Include/AndroidDataEngine.h"

//��ȡ��ϵ����������ID
DWORD GetContactCmdID()
{
	static DWORD ID=0;

	return ID++;
};

//��ȡ������������ID
DWORD GetSMSCmdID()
{
	static DWORD ID=0;

	return ID++;
};



CAndroidDataEngine::CAndroidDataEngine(void)
{
	//ע����Ϣ
	RegisterMessage();

	m_ConnectThread.StartThread();
	m_ContactThread.StartThread();
}

CAndroidDataEngine::~CAndroidDataEngine(void)
{
	//ע����Ϣ
	UnRegisterMessage();
	m_ConnectThread.StopThread();
	m_ContactThread.StopThread();
}


//�����ֻ�
void CAndroidDataEngine::ConnectPhone(CString PhoneDes)
{
	m_ConnectThread.StartConnectPhone(PhoneDes);
}

//�Ͽ������ֻ�
void CAndroidDataEngine::StopConnectPhone()
{
	m_ConnectThread.StopConnectPhone();
}

//�����ֻ���Ϣ
void CAndroidDataEngine::RequestPhoneInfo()
{

}

//��ȡ�ֻ���Ϣ
sPhoneInfo CAndroidDataEngine::GetPhoneInfo()
{
	return m_PhoneInfo;
}


/************��ϵ�˲����ӿ�*************/

//������ϵ������
void CAndroidDataEngine::RequestContactInfo()
{
	m_ContactInfoList.clear();
//	m_GroupInfoList.clear();
	sContactCmd Cmd;
	/*Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACTGROUP_REQUEST_CMD;*/
	//m_ContactThread.AddWorkCmd(Cmd);

	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACT_REQUEST_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//����ɾ����ϵ��
void CAndroidDataEngine::RequestDeleteContactInfo(CString ID)
{
	vector<CString>* pVector=new vector<CString>;
	pVector->push_back(ID);

	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACT_DELTE_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//��������ɾ����ϵ��
void CAndroidDataEngine::RequestBatchDeleteContactInfo(vector<CString>& IDList)
{
	vector<CString>* pVector=new vector<CString>;
	*pVector=IDList;
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = IDList.size();
	Cmd.m_CmdType = CONTACT_DELTE_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//����ɾ��������ϵ��
void CAndroidDataEngine::RequestDeleteAllContactInfo()
{
	sContactCmd Cmd;
	Cmd.m_CmdId =GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACT_DELTE_ALL_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//���������ϵ��
void CAndroidDataEngine::RequestAddContactInfo(sContactInfo& Info)
{
	vector<sContactInfo>* pVector=new vector<sContactInfo>;
	pVector->push_back(Info);

	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACT_ADD_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//�������������ϵ��
void CAndroidDataEngine::RequestBatchAddContactInfo(vector<sContactInfo>& InfoList)
{
	vector<sContactInfo>* pVector=new vector<sContactInfo>;
	*pVector = InfoList;

	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = InfoList.size();
	Cmd.m_CmdType = CONTACT_ADD_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//����༭��ϵ��
void CAndroidDataEngine::RequestEditContactInfo(sContactInfo& Info)
{
	vector<sContactInfo>* pVector=new vector<sContactInfo>;
	pVector->push_back(Info);
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACT_EDIT_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//������ϵ�˷���
void CAndroidDataEngine::RequestContactGroupInfo()
{
	sContactCmd Cmd;
	m_GroupInfoList.clear();
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACTGROUP_REQUEST_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//����ɾ����ϵ�˷���
void CAndroidDataEngine::RequestDeleteContactGroupInfo(CString ID)
{
	vector<CString>* pVector=new vector<CString>;
	pVector->push_back(ID);
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACTGROUP_DELETE_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//��������ɾ����ϵ�˷���
void CAndroidDataEngine::RequestBatchDeleteContactGroupInfo(vector<CString>& IDList)
{
	vector<CString>* pVector=new vector<CString>;
	*pVector = IDList;
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = IDList.size();
	Cmd.m_CmdType = CONTACTGROUP_DELETE_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//����ɾ��������ϵ�˷���
void CAndroidDataEngine::RequestDeleteAllContactGroupInfo()
{
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACTGROUP_DELETE_ALL_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//���������ϵ�˷���
void CAndroidDataEngine::RequestAddContactGroupInfo(sGroupInfo& Info)
{
	vector<sGroupInfo>* pVector=new vector<sGroupInfo>;
	pVector->push_back(Info);
	sContactCmd Cmd;
	Cmd.m_CmdId =GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACTGROUP_ADD_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//�������������ϵ�˷���
void CAndroidDataEngine::RequestBatchAddContactGroupInfo(vector<sGroupInfo>& InfoList)
{
	vector<sGroupInfo>* pVector=new vector<sGroupInfo>;
	*pVector = InfoList;
	sContactCmd Cmd;
	Cmd.m_CmdId =GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACTGROUP_ADD_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}
	
//����༭��ϵ�˷���
void CAndroidDataEngine::RequestEditContactGroupInfo(sGroupInfo& Info)
{
	vector<sGroupInfo>* pVector=new vector<sGroupInfo>;
	pVector->push_back(Info);
	sContactCmd Cmd;
	Cmd.m_CmdId =GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACTGROUP_EDIT_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//��ȡ��ϵ���б�
vector<sContactInfo>* CAndroidDataEngine::GetContactInfoList()
{
	return &m_ContactInfoList;
}

//��ȡ������ϵ��
bool  CAndroidDataEngine::GetContactInfo(CString ID,sContactInfo& Info)
{
	for(int Index = 0; Index < (int)m_ContactInfoList.size(); Index++)
	{
		if(m_ContactInfoList[Index].m_ID == ID)
		{
			Info = m_ContactInfoList[Index];
			return true;
		}
	}
	return false;
}

//��ȡָ����ϵ�� 
void CAndroidDataEngine::GetContactInfo(vector<CString>& IDList,vector<sContactInfo>& InfoList)
{
	for(int Index = 0; Index < (int)m_ContactInfoList.size(); Index++)
	{
		for(int IDIndex=0; IDIndex < IDList.size(); IDIndex++)
		{
			if(m_ContactInfoList[Index].m_ID == IDList[IDIndex])
			{
				InfoList.push_back(m_ContactInfoList[Index]);
				break;
			}
		}
	}
}

//��ȡ��ϵ�˷����б�
vector<sGroupInfo>* CAndroidDataEngine::GetContactGroupInfoList()
{
	return &m_GroupInfoList;
}

//��ȡ��ϵ�˷���
bool CAndroidDataEngine::GetContactGroupInfo(CString ID,sGroupInfo& Info)
{
	
	for(int Index = 0; Index < (int)m_GroupInfoList.size(); Index++)
	{
		if(m_GroupInfoList[Index].m_GroupID == ID)
		{
			Info = m_GroupInfoList[Index];
			return true;
		}
	}
	return false;
}

//��ȡ��ϵ��ָ������
void CAndroidDataEngine::GetContactGroupInfo(vector<CString>& IDList,vector<sGroupInfo>& InfoList)
{
	for(int Index = 0; Index < (int)m_GroupInfoList.size(); Index++)
	{
		for(int IDIndex=0; IDIndex < IDList.size(); IDIndex++)
		{
			if(m_GroupInfoList[Index].m_GroupID == IDList[IDIndex])
			{
				InfoList.push_back(m_GroupInfoList[Index]);
				break;
			}
		}
	}
}

//��ȡͨ����¼�б�
vector<sCallLogInfo>* CAndroidDataEngine::GetCallLogInfoList()
{
	return &m_CallLogInfoList;
}

      

/************************************���Ų����ӿ�***********************************s************/

//���������Ϣ
void CAndroidDataEngine::ReqeustSmsInfo()
{
	m_SmsInfoList.clear();
	sSmsCmd Cmd;

	Cmd.m_CmdId = GetSMSCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = SMS_REQUEST_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//����ɾ������
void CAndroidDataEngine::RequestDeleteSmsInfo(CString ID)
{
	vector<CString>* pVector=new vector<CString>;
	pVector->push_back(ID);

	sSmsCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = SMS_DELTE_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//��������ɾ������
void CAndroidDataEngine::RequestBatchDeleteSmsInfo(vector<CString>& IDList)
{
	vector<CString> *pVector = new vector<CString>;
	*pVector = IDList;
	sSmsCmd Cmd;
	Cmd.m_CmdId = GetSMSCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = IDList.size();
	Cmd.m_CmdType = SMS_DELTE_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//����ɾ�����ж��� 
void CAndroidDataEngine::RequestDeletAllSmsInfo()
{
	sSmsCmd Cmd;
	Cmd.m_CmdId =GetSMSCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = SMS_DELTE_ALL_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//�����Ͷ���
void CAndroidDataEngine::RequestSendSmsInfo(sSendSmsInfo& Info)
{
	vector<sSendSmsInfo> *pvect = new vector<sSendSmsInfo>;
	pvect->push_back(Info);
	sSmsCmd Cmd;
	Cmd.m_CmdId =GetSMSCmdID();
	Cmd.m_CmdParam = (WPARAM)pvect;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = SMS_SEND_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//�����������Ͷ���
void CAndroidDataEngine::RequestBatchSendSmsInfo(vector<sSendSmsInfo>& InfoList)
{
	vector<sSendSmsInfo> *pvect = new vector<sSendSmsInfo>;
	*pvect = InfoList;
	sSmsCmd Cmd;
	Cmd.m_CmdId =GetSMSCmdID();
	Cmd.m_CmdParam = (WPARAM)pvect;
	Cmd.m_CmdParamCount = pvect->size();
	Cmd.m_CmdType = SMS_DELTE_ALL_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}


/************Ӧ�ò����ӿ�**************/

void CAndroidDataEngine::RequestInstallApk(CString ApkPath,ePathType Type)
{
}

void CAndroidDataEngine::RequestBatchInstallApk(vector<CString> ApkPath,ePathType Type)
{
}

void CAndroidDataEngine::UninstallApk(CString ApkPackName)
{
}

void CAndroidDataEngine::BatchUninstallApk(vector<CString> ApkPackName)
{

}


/************�ļ������ӿ�**************/

// ��ȡAndroid��������ʵ��
IDataEngine* GetAndroidDataEngineInterface()
{
	static CAndroidDataEngine DataEngine;
	IDataEngine* pDataEngine=(IDataEngine*)&DataEngine;
	return pDataEngine;
}

//��ȡ��������ʵ��
EXPORT_API IDataEngine* GetDataEngineInterface(ePhoneOSType Type)
{
	if(Type == PHONE_OS_ANDROID)
		return GetAndroidDataEngineInterface();
	return NULL;
}
