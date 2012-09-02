#include "stdafx.h"
#include "InterfaceToJS.h"

/***********************************************************************************
* ˵��      ��  CPP_JS��Ϣ����                                                     *
* ������    ��  ������                                                             *
* ��������  ��  2012-5-10                                                          *
***********************************************************************************/

//ע����Ϣ
void InterfaceToJS::RegisterMsg()
{
	//��ϵ��
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_CONTACT_REQUEST_CMD);
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_CONTACT_ADD_CMD);
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_CONTACTGROUP_REQUEST_CMD);

	//����
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_SMS_REQUEST_CMD);

	//�ļ�����
}
//ע����Ϣ
void InterfaceToJS::LogoutMsg()
{
	//��ϵ��
	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_CONTACT_REQUEST_CMD);
	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_CONTACT_ADD_CMD);
	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_CONTACTGROUP_REQUEST_CMD);

	//����
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_SMS_REQUEST_CMD);

	//�ļ�����
}
//�ײ���Ϣ��Ӧ
void InterfaceToJS::OnMessage(eMessage Message,DWORD SystemMsg,WPARAM wParam,LPARAM lParam)
{
//�����ֻ���Ϣ����
	SmsReturnWeb(Message,wParam, lParam);
	
//��ϵ���ֻ���Ϣ����
	ContacReturnWeb(Message,wParam,lParam);
}

//������ϵ����Ϣ
void InterfaceToJS::ContacReturnWeb(eMessage Message,WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case MSG_CONTACT_REQUEST_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
		}
		break;
	case MSG_CONTACT_ADD_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
			//		RetPhoMsg(L"JS_OnRequestAddContactData",1);
		}
		break;
	case MSG_CONTACT_DELTE_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
			//		RetPhoMsg(L"JS_OnRequestDeleteContactData",1);
		}

		break;
	case MSG_CONTACT_DELTE_ALL_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
			//		RetPhoMsg(L"JS_OnRequestDeleteAllContactData",1);
		}
		break;
	case MSG_CONTACT_EDIT_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
			//		RetPhoMsg(L"JS_OnRequestEditContactData",1);
		}
		break;
	case MSG_CONTACT_BACKUP_CMD:
	//	RetPhoMsg(L"JS_OnRequestBackUpContactData",1);
		break;
	case MSG_CONTACTGROUP_REQUEST_CMD:
		{
			vector<sGroupInfo>* tmpVctGroup = (vector<sGroupInfo>*)wParam;
			CString strJsonSms = L"" ;
			CString strResult = L"";
			CombinGroupInfo(*tmpVctGroup,strJsonSms);
			strResult = MakeStrJsIntface(_T("JS_OnRequestGroupData"),strJsonSms);
			ExecJsScript(strResult);
		}
		break;
	case MSG_CONTACTGROUP_ADD_CMD:
	//	RetPhoMsg(L"JS_OnRequestAddGroup",1);
		break;
	case MSG_CONTACTGROUP_DELETE_CMD:
	//	RetPhoMsg(L"JS_OnRequestDeleteGroupData",1);
		break;
	case MSG_CONTACTGROUP_DELETE_ALL_CMD:
	//	RetPhoMsg(L"JS_OnRequestDeleteAllGroupData",1);
		break;
	case MSG_CONTACTGROUP_EDIT_CMD:
		//RetPhoMsg(L"JS_OnRequestEditGroupData",1);
		break;
	}
}

//���������Ϣ
void InterfaceToJS::SmsReturnWeb(eMessage Message,WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case MSG_SMS_REQUEST_CMD:
		{
			vector<sSmsInfo>* tmpVctContact = (vector<sSmsInfo>*)wParam;
			DoSmsJsIntface(_T("JS_OnRequestSmsData"),*tmpVctContact);
		}
		break;
	case MSG_SMS_ADD_CMD:
		//RetPhoMsg(L"JS_OnRequestAddSmsData",(int)lParam);
		break;
	case MSG_SMS_DELTE_CMD:
		//RetPhoMsg(L"JS_OnRequestDeleteSmsData",(int)lParam);
		break;
	case MSG_SMS_DELTE_ALL_CMD:
		//RetPhoMsg(L"",(int)lParam);
		break;
	case MSG_SMS_EDIT_CMD:
		//RetPhoMsg(L"",(int)lParam);
		break;
	case MSG_SMS_BACKUP_CMD:
		//RetPhoMsg(L"",(int)lParam);
		break;
	case MSG_SMS_SEND_CMD:
		//RetPhoMsg(L"JS_OnRequestSendSms",(int)lParam);
		break;
	}
}