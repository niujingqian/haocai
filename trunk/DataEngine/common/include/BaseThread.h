#pragma once
#include "DataDefine.h"
#include "Markup.h"

/***********************************************************************************
* ˵��      ��  �̻߳�����                                                         *
* ������    ��  ̷����                                                             *
* ��������  ��  2012-2-24                                                          *
***********************************************************************************/

typedef DWORD (*CallBackFunction)(WPARAM wParam,LPARAM lParam);

class EXPORT_CLASS CBaseThread
{
public:
	CBaseThread(void);

	~CBaseThread(void);

	//�����߳�
	virtual bool StartThread();

	//��ֹ�߳�
	virtual bool StopThread();

	//���ûص�����
	virtual void SetCallBackFunction(CallBackFunction CallBack);

protected:

	HANDLE              m_StopEvent;                //�߳�ֹͣ�¼�
	HANDLE              m_ThreadHandle;             //�߳̾��
	CallBackFunction    m_CallBackFuntion;          //�ص�����

};
