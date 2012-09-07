#include "StdAfx.h"
#include "SmsThread.h"

CSmsThread::CSmsThread(void)
{
	m_WorkEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}

CSmsThread::~CSmsThread(void)
{
	if (m_WorkEvent == INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_WorkEvent);
	}
}

bool CSmsThread::StartThread()
{
	CBaseThread::StartThread();
	m_ThreadHandle = ::CreateThread(NULL, 0, SmsWorkThread, this, 0, NULL);
}

//���Ŵ����߳�
DWORD CSmsThread::SmsWorkThread(LPVOID lpVoid)
{
	CSmsThread *Self = (CSmsThread*)lpVoid;
	HANDLE EventArray[2] = {Self->m_WorkEvent, Self->m_StopEvent};
	while (true)
	{
		DWORD Ret = ::WaitForMultipleObjects(2,EventArray,false,INFINITE);
		if (Ret != 0)
			 break;
		CString CmdStr = Self->GetCmdStr(Cmd);
		CString CmdRetStr;

		Self->ParseCmdRetStr(CMD, CmdRetStr);
		::ResetEvent(Self->m_WorkEvent);
	}
}

//��ӹ�������
void CSmsThread::AddWorkCmd(sSmsCmd& Cmd)
{
	XWriteEventLog(_T("[CContactThread::AddWorkCmd] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);
	m_SmsCmd.push_back(Cmd);
	SetEvent(m_WorkEvent);
}

//�Ƴ���������
void CSmsThread::DeleteWorkCmd(sSmsCmd& Cmd)
{
	XWriteEventLog(_T("[CContactThread::DeleteWorkCmd] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);
	vector<sSmsCmd>::iterator it = m_SmsCmd.begin();
	for (; it!= m_SmsCmd.end(); it++)
	{
		if (it->m_CmdId == Cmd.m_CmdId && it->m_CmdType == Cmd.m_CmdType)
		{
			switch(Cmd.m_CmdType)
			{

			case SMS_REQUEST_CMD:
				break;
			case SMS_DELTE_CMD:
				break;
			case SMS_ADD_CMD:
				break;
			case SMS_EDIT_CMD:
				break;
			default:
				break;
			}
			it = m_SmsCmd.erase(it);
		}
	}
}

//��ȡ�����ַ���
CString CSmsThread::GetCmdStr(sSmsCmd& Cmd)
{
	XWriteEventLog(_T("[CContactThread::GetCmdStr] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);
	CString CmdStr;
	switch(Cmd.m_CmdType)
	{
	case SMS_REQUEST_CMD:
		{
			CmdStr=	_T("<?xml version=\"1.0\"?>"
				"<req>"
				"<cmd>1</cmd>"
				"<fun>GetSmsList</fun>"
				"<ps count='1'>"
				"<p>"
				"<name>position</name>"
				"<value>phone</value>"
				"</p>"
				"</ps>\n"
				"</req>\n");
		}
		break;
	case SMS_ADD_CMD:
		{
		}
		break;
	case SMS_DELTE_CMD:
		{
		}
		break;
	case SMS_EDIT_CMD:
		{
		}
		break;
	}
	return CmdStr;
}

//����������ַ���
void CSmsThread::ParseCmdRetStr(sSmsCmd& Cmd,CString CmdRetStr)
{
	switch (Cmd.m_CmdType)
	{
	case SMS_REQUEST_CMD:
		{
			ParseSmsRequestCmdRet(CmdRetStr);
		}
		break;
	case SMS_ADD_CMD:
			
		break;
	case SMS_DELTE_CMD:

		break;
	case  SMS_EDIT_CMD:

		break;
	}
}

//����������Ӧ�����ֵ
void CSmsThread::ParseSmsRequestCmdRet(CString &CmdRetStr)
{
}