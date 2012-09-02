
#pragma once
#include "../common/Include/basethread.h"
#include "../common/Include/CommonFunction.h"
#include "../common/Include/Communication.h"
#include "../common/Include/MessageCenter.h"

/***********************************************************************************
* ˵��      ��  �����˴����߳�                                                    *
* ������    ��  ������                                                             *
* ��������  ��  2012-5-14                                                          *
***********************************************************************************/

class EXPORT_CLASS CSmsThread : public CBaseThread
{
public:

	CSmsThread(void);

	~CSmsThread(void);

	//�����߳�
	virtual bool StartThread();

	//��ϵ�˴����߳�
	static DWORD WINAPI SmsWorkThread(LPVOID lpVoid);

	//��ӹ�������
	void AddWorkCmd(sSmsCmd& Cmd);

	//�Ƴ���������
	void DeleteWorkCmd(sSmsCmd& Cmd);

	//��ȡ�����ַ���
	CString GetCmdStr(sSmsCmd& Cmd);

	/*****************************����������Ӧ�����ֵ*************************************/
	//����������ַ���
	void ParseCmdRetStr(sSmsCmd& Cmd,CString CmdRetStr);

	//�����������
	void ParseSmsRequestCmdRet(CString&   CmdRetStr,sSmsCmd);

	//��Ӷ���
	void ParseSmsAddCmdRet(CString&       CmdRetStr,sSmsCmd);

	//ɾ������
	void ParseSmsDeleteCmdRet(CString&    CmdRetStr,sSmsCmd);

	//ɾ�����ж���
	void ParseSmsDeleteAllCmdRet(CString& CmdRetStr,sSmsCmd);

	//�༭����
	void ParseSmsEditCmdRet(CString&     CmdRetStr,sSmsCmd);

	//���ݶ���
	void ParseSmsBackupCmdRet(CString&   CmdRetStr,sSmsCmd);

	//���Ͷ���
	void ParseSmsSendCmd(CString&        CmdRetStr,sSmsCmd);

private:

	HANDLE                     m_WorkEvent;       //�����¼�
	vector<sSmsCmd>			   m_SmsCmd;          //���Ŵ�������
	vector<DWORD>              m_ExecCmdIdList;   //�����Ѵ����������ID

};
