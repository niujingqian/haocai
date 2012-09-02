#pragma once
#include "..\common\include\basethread.h"

/***********************************************************************************
* ˵��      ��  �����̹߳���                                                       *
* ������    ��  ̷����                                                             *
* ��������  ��  2012-2-24                                                          *
***********************************************************************************/

class EXPORT_CLASS CConnectThread :public CBaseThread
{
public:

	CConnectThread(void);

	~CConnectThread(void);

	//�����߳�
	virtual bool StartThread();
	
	//���Ӵ����߳�
	static DWORD WINAPI ConnectWorkThread(LPVOID lpVoid);

	//��ʼ����
	virtual bool StartConnectPhone(CString PhoneDes);

	//�ж�����
	virtual void StopConnectPhone();

	//�����ֻ�����
	virtual void StartPhoneServer();

	//��װ�ֻ�����
	virtual bool InstallPhoneServer();

	//��ȡ�ֻ���Ϣ
	virtual bool GetPhoneInfo(sPhoneInfo& Info);

protected:
	
	//��ȡ�ֻ�ϵͳ��Ϣ
	virtual bool GetPhoneSystemInfo(sPhoneInfo& Info);

	//��ȡ�ֻ��ڴ���Ϣ
	virtual bool GetPhoneMemInfo(sPhoneInfo& Info);

	//��ȡ�ֻ�ͳ����Ϣ
	virtual bool GetPhoneCountInfo(sPhoneInfo& Info);

	//�ض���˿�
	virtual bool ForwardAdbPort();

private:

	HANDLE    m_StartConnectEvent;         //��ʼ�����¼�
	HANDLE    m_StopConnectEvent;          //�ж������¼�
	CString   m_PhoneDes;                  //�ֻ�Ψһ������
};
