#pragma once

#include "BaseThread.h"

/*****************************************************************
* ˵��        :  ���Ŵ����߳�                                   *
* ������      :  ������                                         *
* ��������    :  2012/5/9                                       *
*****************************************************************/


class CSmsThread :	public CBaseThread
{
public:

	CSmsThread(void);

	~CSmsThread(void);
	
	//�̲߳���
	//�����߳�
	virtual BOOL StartThread();

	//���Ŵ����߳�
	static DWORD WINAPI SmsWorkThread(LPVOID lpVoid);

	//�����
	//��ӹ�������
	void AddWorkCmd(sSmsCmd& Cmd);

	//�Ƴ���������
	void DeleteWorkCmd(sSmsCmd& Cmd);

	//��ȡ�����ַ���
	CString GetCmdStr(sSmsCmd& Cmd);

	//����������ַ���
	void ParseCmdRetStr(sSmsCmd& Cmd,CString CmdRetStr);

private:

	HANDLE                     m_WorkEvent;       //�����¼�
	vector<sSmsCmd>        m_SmsCmd;      //���Ŵ�������

};
