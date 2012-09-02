#include "StdAfx.h"
#include "SmsThread.h"


CSmsThread::CSmsThread(void)
{
	m_WorkEvent = ::CreateEvent(NULL,true,false,NULL);
}

CSmsThread::~CSmsThread(void)
{
	if(m_WorkEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_WorkEvent);
	}
}


//�����߳�
bool CSmsThread::StartThread()
{
	CBaseThread::StartThread();

	m_ThreadHandle = ::CreateThread(NULL,0,SmsWorkThread,this,0,NULL);
	if(m_ThreadHandle != INVALID_HANDLE_VALUE)
		return true;

	return false;
}

//���Ŵ����߳�
DWORD CSmsThread::SmsWorkThread(LPVOID lpVoid)
{
	CSmsThread* Self=(CSmsThread*)lpVoid;
	HANDLE EventArray[2]={Self->m_WorkEvent,Self->m_StopEvent};
	while(true)
	{
		DWORD Ret=::WaitForMultipleObjects(2,EventArray,false,INFINITE);
		if(Ret != 0)
			break;

		::ResetEvent(Self->m_WorkEvent);
		sSmsCmd Cmd;
		vector<sSmsCmd>::iterator it = Self->m_SmsCmd.begin();
		if(it == Self->m_SmsCmd.end())
			continue;

		Cmd=*it;
		Self->m_SmsCmd.erase(it);
		CString CmdStr=Self->GetCmdStr(Cmd);
		CString CmdRetStr;
		CCommunication::SendXmlToPhone(CmdStr,CmdRetStr);
		Self->ParseCmdRetStr(Cmd,CmdRetStr);
	}
	return 0;
}


//��ӹ�������
void CSmsThread::AddWorkCmd(sSmsCmd& Cmd)
{
	XWriteEventLog(_T("[CSmsThread::AddWorkCmd] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);

	m_SmsCmd.push_back(Cmd);
	SetEvent(m_WorkEvent);
}

//�Ƴ���������
void CSmsThread::DeleteWorkCmd(sSmsCmd& Cmd)
{
	XWriteEventLog(_T("[CSmsThread::DeleteWorkCmd] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);
	vector<sSmsCmd>::iterator it= m_SmsCmd.begin();
	for(;it != m_SmsCmd.end(); it++)
	{
		if(it->m_CmdId == Cmd.m_CmdId && it->m_CmdType == Cmd.m_CmdType)
		{
			switch(Cmd.m_CmdType)
			{
				
			case SMS_REQUEST_CMD:
				break;
			case SMS_ADD_CMD:
			case SMS_EDIT_CMD:
				{
					vector<sSmsInfo>* pVector = (vector<sSmsInfo>*)Cmd.m_CmdParam;
					if(pVector != NULL)
					{
						pVector->clear();
						delete pVector;
					}
				}
				break;
			case SMS_DELTE_CMD:
			
			case SMS_BACKUP_CMD:
				break;

			}
			it=m_SmsCmd.erase(it);
		}
	}
}

//��ȡ�����ַ���
CString CSmsThread::GetCmdStr(sSmsCmd& Cmd)
{
	XWriteEventLog(_T("[CSmsThread::GetCmdStr] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);

	CString CmdStr;
	switch(Cmd.m_CmdType)
	{
	case SMS_REQUEST_CMD:
		{
			CmdStr = L"<?xml version='1.0'?>"
				L"<req>"
				L"<fun>GetSms</fun>"
				L"<ps count='2'>"
				L"<p>"
				L"<name>id</name>"
				L"<value>all</value>"
				L"</p>"
				L"<p>"
				L"<name>type</name>"
				L"<value>normal</value>"
				L"</p>"									
				L"</ps>\n"
				L"</req>\n";
		}
		break;

	case SMS_DELTE_CMD:
		{
			CString strType = L"sendbox";
			CString *strID = (CString*)Cmd.m_CmdParam;
			CmdStr.Format(L"<?xml version='1.0'?>"
				L"<req>"
				L"<fun>DelSms</fun>"
				L"<ps count='2'>"
				L"<p>"
				L"<name>smsbox</name>"
				L"<value>%s</value>"
				L"</p>"
				L"<name>id</name>"
				L"<value>%s</value>"
				L"</ps>\n"
				L"</req>\n", strType, strID);
		}
		break;

	case SMS_SEND_CMD:
		{
			vector<CString> tempPhone = (vector<CString>)Cmd.m_CmdParam;
			CString pchPhoneNumber = tempPhone[0];
			CString pchSmsBody = tempPhone[1];
			CmdStr.Format(L"<?xml version='1.0'?>"
				L"<req>"
				L"<fun>SendSms</fun>"
				L"<ps count='2'>"
				L"<p>"
				L"<name>phoneNum</name>"
				L"<value>%s</value>"
				L"</p>"
				L"<p>"
				L"<name>text</name>"
				L"<value>%s</value>"
				L"</p>"
				L"</ps>\n"
				L"</req>\n", pchPhoneNumber, pchSmsBody);
		}
		break;
	case SMS_ADD_CMD:
		{
			sSmsInfo *tempSmsInfo = (sSmsInfo*)Cmd.m_CmdParam;
			CString BoxStr;
			BoxStr.Format(L"%d",tempSmsInfo->m_SmsBox);
			int State=(int)tempSmsInfo->m_SmsStaus;
	
			CString strID = tempSmsInfo->m_SmsID;
			CString StrValue;
			CString TempData;
			TempData.Format(_T("add:%s\ndata:%s\n"),tempSmsInfo->m_SmsCaller,tempSmsInfo->m_SmsBody);
			StrValue.Format(_T("date:%s\nstate:%d\ntype:%d\n"),tempSmsInfo->m_TimeStamp,State,tempSmsInfo->m_SmsBox);
			StrValue=TempData+StrValue;
			CmdStr.Format(L"<?xml version='1.0'?>"
				L"<req>"									
				L"<fun>RestoreSms</fun>"					
				L"<ps count='2'>"						
				L"<p>"									
				L"<name>smsbox</name>"					
				L"<value>%s</value>"					
				L"</p>"									
				L"<p>"									
				L"<name>%s</name>"						
				L"<value>%s</value>"						
				L"</p>"									
				L"</ps>\n"								
				L"</req>\n",BoxStr,strID,StrValue);
		}
		break;
	case SMS_DELTE_ALL_CMD:
		{
			CmdStr.Format(L"<?xml version='1.0'?>"
				L"<req>"
				L"<fun>DelSms</fun>"
				L"<ps count='2'>"
				// 		"<p>"
				// 		"<name>smsbox</name>"
				// 		"<value>%s</value>"
				// 		"</p>"
				L"<p>"
				L"<name>id</name>"
				L"<value>all</value>"
				L"</p>"
				L"</ps>\n"
				L"</req>\n");
		}
		break;
	case SMS_EDIT_CMD:
		{
		}
		break;
	case SMS_BACKUP_CMD:
		{
		}
		break;
	}

	return CmdStr;
}

//����������ַ���
void CSmsThread::ParseCmdRetStr(sSmsCmd& Cmd,CString CmdRetStr)
{
	switch(Cmd.m_CmdType)
	{
	case SMS_SEND_CMD:
		{
			ParseSmsSendCmd(CmdRetStr,Cmd);
		}
		break;
	case SMS_DELTE_ALL_CMD:
		{
			ParseSmsDeleteAllCmdRet(CmdRetStr,Cmd);
		}
		break;
	case SMS_REQUEST_CMD:
		{
			ParseSmsRequestCmdRet(CmdRetStr,Cmd);
		}
		break;
	case SMS_ADD_CMD:
		{
			ParseSmsAddCmdRet(CmdRetStr,Cmd);
		}
		break;

	case SMS_DELTE_CMD:
		{
			ParseSmsDeleteCmdRet(CmdRetStr,Cmd);
		}
		break;
	case SMS_EDIT_CMD:
		{
			ParseSmsEditCmdRet(CmdRetStr,Cmd);
		}
		break;
	case SMS_BACKUP_CMD:
		{
			ParseSmsBackupCmdRet(CmdRetStr,Cmd);
		}
		break;
	}
}

//����������Ӧ�����ֵ  ��������
void CSmsThread::ParseSmsRequestCmdRet(CString&  CmdRetStr,sSmsCmd cmd)
{
	CMarkup xml;
	if (xml.SetDoc(CmdRetStr) )
	{			
		CString strData;
		xml.ResetMainPos();
		xml.FindChildElem(L"ps");
		if (xml.IntoElem())
		{
			CString strAdd;
			CString strData;
			CString strRead;
			CString strDate;
			CString strXmlName;

		
			int iTick = 0;
			vector<sSmsInfo> vctSmsInfo;
			while ( xml.FindChildElem(L"p") )
			{
				sSmsInfo SmsInfo;
				CString strMsg;
				xml.IntoElem();
				xml.FindChildElem(L"name");
				strXmlName = xml.GetChildData().c_str();
				CString StrID = strXmlName;
				if (strXmlName == L"msg")
				{
					xml.FindChildElem(L"value");							
					strMsg = xml.GetChildData().c_str();

					if (strMsg != L"0")
					{
						return ;
					}
				}
				else if(strXmlName ==L"flag")
				{
					xml.FindChildElem(L"value");							
					strMsg = xml.GetChildData().c_str();
					if(strMsg == L"end")
						return;
				}
				else
				{
					//�����������
					xml.FindChildElem(L"value");
					xml.IntoElem();
					if (xml.FindChildElem(L"state"))
					{
						//����״̬
						xml.FindChildElem(L"state");
						strRead = xml.GetChildData().c_str();
						if (strRead == L"1")
							SmsInfo.m_SmsStaus = SMS_IS_READ;
						else
							SmsInfo.m_SmsStaus = SMS_NOT_READ;
						//��������
						xml.FindChildElem(L"data");
						strData = xml.GetChildData().c_str();
						if(strData == L"")	
							SmsInfo.m_SmsBody = L"��";
						else
							SmsInfo.m_SmsBody = xml.GetChildData().c_str();
						//����������Ϣ����
						xml.FindChildElem(L"type");
						strRead = xml.GetChildData().c_str();
						if (strRead == L"1")	//�ռ�
						{
							SmsInfo.m_SmsBox = SMSBOX_INBOX;
						}
						else if (strRead == L"2")	//����
						{
							SmsInfo.m_SmsBox = SMSBOX_SENTBOX;
						}
						else
						{
							xml.OutOfElem();
							xml.OutOfElem();
							continue;
						}
						//����ʱ��
						xml.FindChildElem(L"date");
						SmsInfo.m_TimeStamp = xml.GetChildData().c_str();
						//���ŵ�ַ
						xml.FindChildElem(_T("add"));
						strAdd = xml.GetChildData().c_str();
						if(strAdd == _T(""))
						{
							SmsInfo.m_SmsCaller =_T("");
							SmsInfo.m_ContactName = _T("");
						}

					xml.OutOfElem();
					}
				xml.OutOfElem();
				}
			vctSmsInfo.push_back(SmsInfo);
			}
			CMessageCenter::SendMsg(MSG_SMS_INFO_TO_DATA_ENGINE,SMS_REQUEST_CMD,(WPARAM)&vctSmsInfo);
		}
	}
}

void CSmsThread::ParseSmsAddCmdRet(CString&      CmdRetStr,sSmsCmd cmd)
{
}

//ɾ������
void CSmsThread::ParseSmsDeleteCmdRet(CString&   CmdRetStr,sSmsCmd cmd)  
{
	//����ɾ�����ŷ��ص�XML����    �ɹ�����0��ʧ�ܷ���-1
	if (CmdRetStr != L"")
	{
		CMarkup xml;
		if (xml.SetDoc(CmdRetStr) )
		{			
			CString strData;
			xml.ResetMainPos();
			xml.FindChildElem(L"ps");
			if (xml.IntoElem())
			{
				int iTick = 0;
				while ( xml.FindChildElem(L"p") )
				{
					CString strMsg;
					xml.IntoElem();
					xml.FindChildElem(L"name");
					strData = xml.GetChildData().c_str();
					strData.MakeLower();
					if (strData == L"msg")
					{
						xml.FindChildElem(L"value");							
						strMsg = xml.GetChildData().c_str();
						if (strMsg != L"0")
						{
							cmd.m_CmdParam = -1;
						}
					}
					else
					{
						cmd.m_CmdParam = -1;
					}
					xml.OutOfElem();
				}
			}
		}
	}
	CMessageCenter::SendMsg(MSG_SMS_INFO_TO_DATA_ENGINE,SMS_DELTE_CMD,(WPARAM)cmd.m_CmdParam);
}

void CSmsThread::ParseSmsEditCmdRet(CString&     CmdRetStr,sSmsCmd cmd)
{
}
void CSmsThread::ParseSmsBackupCmdRet(CString&   CmdRetStr,sSmsCmd cmd)
{
}

//ɾ�����ж���
void CSmsThread::ParseSmsDeleteAllCmdRet(CString &CmdRetStr,sSmsCmd cmd)
{
	if(CmdRetStr.Find(L"<value>0</value>") == -1)
		cmd.m_CmdParam = -1;//�ֻ�������Ϣʧ��
	else
		cmd.m_CmdParam = 0;

		CMessageCenter::SendMsg(MSG_SMS_INFO_TO_DATA_ENGINE,SMS_DELTE_ALL_CMD,(WPARAM)cmd.m_CmdParam);
}

//���Ͷ���
void CSmsThread::ParseSmsSendCmd(CString& CmdRetStr,sSmsCmd cmd)
{
	bool regFlag; //���ͺ󷵻��Ƿ�ɹ�
	sSmsInfo* pOneSms = new sSmsInfo();
// 	strcpy(pOneSms->szSmsCallerID, pchPhoneNumber);
// 	strcpy(pOneSms->szSmsBody, pchSmsBody);	
// 	strcpy(pOneSms->szSmsStatus, "�Ѷ�");
// 	pOneSms->wBoxNumber = 2; // ������

	//������ֵ
	//�������ص�XML����
	if (CmdRetStr != L"")
	{		
		CMarkup xml;
		if (xml.SetDoc(CmdRetStr) )
		{			
			CString strData;
			xml.ResetMainPos();
			xml.FindChildElem(L"ps");
			if (xml.IntoElem())
			{
				int iTick = 0;
				while ( xml.FindChildElem(L"p") )
				{
					CString strMsg;
					xml.IntoElem();
					xml.FindChildElem(L"name");
					strData = xml.GetChildData().c_str();
					strData.MakeLower();
					if (strData == L"msg")
					{
						xml.FindChildElem(L"value");							
						strMsg = xml.GetChildData().c_str();
						if (strMsg != L"0")
						{
							delete pOneSms;
							pOneSms = NULL;
							return;
						}
					}
					else
					{						
						pOneSms->m_SmsID = (char*)(LPCTSTR)strData;
						xml.FindChildElem(L"value");
						xml.IntoElem();
						//���ŷ��ͽ��
						xml.FindChildElem(L"result");	//���ؽ�� 2 �ɹ� 5 ʧ��
						strData = xml.GetChildData().c_str();
						int nResult = _wtoi(strData);
						//pOneSms->bSuccess = (nResult == 2) ? true : false;
					    regFlag = (nResult == 2) ? true : false;  //���Ͷ��ź󣬷��سɹ���ʧ��
						//ʱ��
						xml.FindChildElem(L"time");
						strData = xml.GetChildData().c_str();						
						pOneSms->m_TimeStamp = strData;					
					}
					xml.OutOfElem();					
				}
			}
		}
	}
	else
		regFlag = false;
	CMessageCenter::SendMsg(MSG_SMS_INFO_TO_DATA_ENGINE,SMS_SEND_CMD,(WPARAM)pOneSms);
}