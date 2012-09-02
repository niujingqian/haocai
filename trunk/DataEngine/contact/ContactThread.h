#pragma once
#include "../common/Include/basethread.h"



/***********************************************************************************
* ˵��      ��  ��ϵ�˴����߳�                                                     *
* ������    ��  ̷����                                                             *
* ��������  ��  2012-2-24                                                          *
***********************************************************************************/

class EXPORT_CLASS CContactThread : public CBaseThread
{
public:

	CContactThread(void);

	~CContactThread(void);

	//�����߳�
	virtual bool StartThread();
	
	//��ϵ�˴����߳�
	static DWORD WINAPI ContactWorkThread(LPVOID lpVoid);

	//��ӹ�������
	void AddWorkCmd(sContactCmd& Cmd);

	//�Ƴ���������
	void DeleteWorkCmd(sContactCmd& Cmd);

	//��ȡ�����ַ���
	CString GetCmdStr(sContactCmd& Cmd);

	//����������ַ���
	void ParseCmdRetStr(sContactCmd& Cmd,CString CmdRetStr);

	//������ϵ����Ӧ�����ֵ
	static void ParseContactRequestCmdRet(CString&      CmdRetStr);
	void ParseContactAddCmdRet(sContactCmd&            Cmd,CString&       CmdRetStr);
	void ParseContactDeleteCmdRet(sContactCmd&         Cmd,CString&       CmdRetStr);
	void ParseContactEditCmdRet(sContactCmd&           Cmd,CString&       CmdRetStr);
	void ParseContactBackupCmdRet(sContactCmd&         Cmd,CString&       CmdRetStr);
	void ParseContactGroupRequestCmdRet(sContactCmd&   Cmd,CString&       CmdRetStr);
	void ParseContactGroupAddCmdRet(sContactCmd&       Cmd,CString&       CmdRetStr);
	void ParseContactGroupDeleteCmdRet(sContactCmd&    Cmd,CString&       CmdRetStr);
	void ParseContactGroupEditCmdRet(sContactCmd&      Cmd,CString&       CmdRetStr);


private:

	HANDLE                     m_WorkEvent;       //�����¼�
	vector<sContactCmd>        m_ContactCmd;      //��ϵ�˴�������
	vector<DWORD>              m_ExecCmdIdList;   //��ϵ���Ѵ����������ID

};
