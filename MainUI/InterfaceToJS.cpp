#include "stdafx.h"
#include "InterfaceToJS.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include "json.h"
#include "DataDefine.h"
#include "CommonFunction.h"

InterfaceToJS::InterfaceToJS(IDispatch* DisPath)
{
	m_DisPath = DisPath;
	m_DataEngine =  GetDataEngineInterface();
	RegisterMsg();
}

InterfaceToJS::~InterfaceToJS(void)
{
	LogoutMsg();
}
//ִ��JS�ű�
void InterfaceToJS::ExecJsScript(CString& JsStr)
{
	if(m_DisPath == NULL)
		return;
	IHTMLDocument2*		pIHTMLDoc=NULL;
	m_DisPath->QueryInterface(IID_IHTMLDocument2, (void**)&pIHTMLDoc);
	if(pIHTMLDoc != NULL)
	{
		IHTMLWindow2*			pIHTMLWindow	= NULL;
		HRESULT					hr				= NOERROR;
		VARIANT					pvarRet;
		pIHTMLDoc->get_parentWindow(&pIHTMLWindow);
		if(pIHTMLWindow)
		{
			hr = pIHTMLWindow->execScript(CComBSTR(JsStr), CComBSTR("JScript"), &pvarRet);
			pIHTMLWindow->Release();
			pIHTMLWindow = NULL;
		}
		pIHTMLDoc->Release();
	}
}

void InterfaceToJS::DoContactJsIntface(const CString&JsIntface, vector<sContactInfo>& ContactInfo)
{
	CString strJsonContact = L"" ;
	CString strResult = L"";
	CombinContactToJson(ContactInfo,strJsonContact);
	strResult = MakeStrJsIntface(JsIntface,strJsonContact);
	ExecJsScript(strResult);
}

void InterfaceToJS::DoSmsJsIntface(const CString&JsIntface, vector<sSmsInfo>& SmsInfo)
{
	CString strJsonSms = L"" ;
	CString strResult = L"";
	CombinSmsToJson(SmsInfo,strJsonSms);
	strResult = MakeStrJsIntface(JsIntface,strJsonSms);
	ExecJsScript(strResult);
}

CString InterfaceToJS::MakeStrJsIntface(const CString& JsIntface,const CString& JsParame )
{
	CString StrResult = _T("");
	StrResult.Format(_T("(\"%s\")"),JsParame);
	StrResult = JsIntface+StrResult;
	return StrResult;
}

void InterfaceToJS::SetDisPath(IDispatch* DisPath)
{
	this->m_DisPath = DisPath;
}

/******************************���Ի����������******************************************/

//�ƶ��Ի���
void InterfaceToJS::CPP_MoveMianDlg(int Xpoint, int Ypoint)					
{
	CMainUIDlg*	pDlg	= (CMainUIDlg*)theApp.m_pMainWnd;
	pDlg->MoveMainDlg(Xpoint,Ypoint);
}

//�رնԻ���
void InterfaceToJS::CPP_Close()												
{
	CMainUIDlg*	pDlg	= (CMainUIDlg*)theApp.m_pMainWnd;
	pDlg->IsAppRun(_T("adb.exe"));			//ǿ�ƽ������̣��ٹرնԻ���
	pDlg->IsAppRun(_T("MainUI.exe"));
	pDlg->EndDialog(0);
}

//��С���Ի���
void InterfaceToJS::CPP_MinDlg()											
{
	CMainUIDlg*	pDlg	= (CMainUIDlg*)theApp.m_pMainWnd;
	pDlg->ShowWindow(SW_MINIMIZE);
}

/******************************��ϵ��ģ��******************************************/

//��������ϵ������
void InterfaceToJS::CPP_OnRequestContactData()								 
{
	m_DataEngine->RequestContactInfo();
}

//ˢ����ϵ��ģ��
void InterfaceToJS::CPP_OnRequestRfreshContactData()
{
	vector<sContactInfo>* vctinfo = m_DataEngine->GetContactInfoList();
	DoContactJsIntface(_T("JS_OnRequestContactData"),*vctinfo);
}
//�����ϵ��
void InterfaceToJS::CPP_OnRequestAddContactData( const CString &contactDate )
{
	vector<sContactInfo> vctinfo;                              
	AnalyContactInfo(contactDate,vctinfo);
	if(vctinfo.empty())
		return ;

	int count = (int)vctinfo.size();
	if (count == 1 )
	{
		m_DataEngine->RequestAddContactInfo(vctinfo[0]);	//��ӵ�����ϵ��
	}
	else if (count > 1)
	{
		m_DataEngine->RequestBatchAddContactInfo(vctinfo);	//���������ϵ��
	}

}

//�༭��ϵ��
void InterfaceToJS::CPP_OnRequestEditContactData( const CString & strConnect )
{
	vector<sContactInfo> vctinfo;                               //һ��ֻ��һ������
	AnalyContactInfo(strConnect,vctinfo);
	for (int count=0; count<(int)vctinfo.size(); count++)
	{
		m_DataEngine->RequestEditContactInfo(vctinfo[count]);
	}
}


//�����ϵ���ļ�
void InterfaceToJS::CPP_OnRequestAddContactFile( const CString & FilePath )
{
	CString strPath;  
	CommonAnalyPath(FilePath, strPath);         //����·��
}

//ɾ����ϵ��
void InterfaceToJS::CPP_OnRequestDeleteContactData( const CString &  ID )
{
	vector<CString> vecStrId;
	eTypeID etypID = ECONTACTID;
	int deleType = CommonAnalyInfo(ID, vecStrId, etypID);
	switch (deleType)
	{
	case 0:          //ɾ��ʧ����ϵ��
		break;
	case 1:			 //ɾ��ȫ����ϵ��
		m_DataEngine->RequestDeleteAllContactInfo();
		break;
	case 2:			 //ɾ��������ϵ��
		m_DataEngine->RequestDeleteContactInfo(vecStrId[0]);
		break;
	case 3:			 //ɾ��������ϵ��
		m_DataEngine->RequestBatchDeleteContactInfo(vecStrId);
		break;
	}
}

//��ϵ�˱���
void InterfaceToJS::CPP_OnRequestBackUpContactData( const CString & ID )
{

}

//�����������
void InterfaceToJS::CPP_OnRequestGroupData()
{
	m_DataEngine->RequestContactGroupInfo();
}

//��ӷ���
void InterfaceToJS::CPP_OnRequestAddGroupData( const CString & strGroupInfo )
{
	vector<sGroupInfo> vctInfo;
	AnalyContactGroupinfo(strGroupInfo, vctInfo);
	int count  = (int)vctInfo.size();
	if (count == 1)
		m_DataEngine->RequestAddContactGroupInfo(vctInfo[0]);
	else if (count > 1)
		m_DataEngine->RequestBatchAddContactGroupInfo(vctInfo);
}

//ɾ������
void InterfaceToJS::CPP_OnRequestDeleteGroupData( const CString & ID)
{
	vector<CString> vecStrId;
	eTypeID etypID = EGROUPID;
	int deleType = CommonAnalyInfo(ID, vecStrId, etypID);
	switch (deleType)
	{
	case 0:          //ɾ��ʧ�ܷ���
		break;
	case 1:			 //ɾ��ȫ������
		m_DataEngine->RequestDeleteAllContactGroupInfo();
		break;
	case 2:			 //ɾ����������
		m_DataEngine->RequestDeleteContactGroupInfo(vecStrId[0]);
		break;
	case 3:			 //ɾ����������
		m_DataEngine->RequestBatchDeleteContactGroupInfo(vecStrId);
		break;
	}
}
//�༭����
void InterfaceToJS::CPP_OnRequestEditGroupData( const CString & strGroupInfo)
{
	vector<sGroupInfo> vctInfo;
	AnalyContactGroupinfo(strGroupInfo, vctInfo);
	m_DataEngine->RequestEditContactGroupInfo(vctInfo[0]);
}

/*******************************����ģ��****************************************************/

//�������
void InterfaceToJS::CPP_OnRequestSmsData()
{
	m_DataEngine->ReqeustSmsInfo();
}

//���Ͷ���
void InterfaceToJS::CPP_OnRequestSendSms( const CString & strSMS )
{
	vector<sSendSmsInfo> vctSmsInfo;
	AnalySendSmsInfo(strSMS, vctSmsInfo);
	int count = (int)vctSmsInfo.size();
	if (count == 1)
		m_DataEngine->RequestSendSmsInfo(vctSmsInfo[0]);
	else if (count >1)
		m_DataEngine->RequestBatchSendSmsInfo(vctSmsInfo);
}

//ɾ������
void InterfaceToJS::CPP_OnRequestDeleteSmsData( const CString & ID )
{
	vector<CString> vecStrId;
	eTypeID etypID = ESMSID;
	int deleType = CommonAnalyInfo(ID, vecStrId, etypID);
	switch (deleType)
	{
	case 0:          //ɾ��ʧ�ܶ���
		break;
	case 1:			 //ɾ��ȫ������
		m_DataEngine->RequestDeletAllSmsInfo();
		break;
	case 2:			 //ɾ����������
		m_DataEngine->RequestDeleteSmsInfo(vecStrId[0]);
		break;
	case 3:			 //ɾ����������
		m_DataEngine->RequestBatchDeleteSmsInfo(vecStrId);
		break;
	}
}

/********************************���ݽ�������װ����****************************************************/

//��ϣ� vector ��ϵ�� ת���� JSON String
void InterfaceToJS::CombinContactToJson(const vector<sContactInfo> &vectContact, CString& ContactStrJson)
{
	int countContact = (int)vectContact.size();
	if (countContact == 0)
		return ;

	CString LastNamePos;

	for (int i=0; i<countContact; i++)
	{
		CString tempItem = L"";
		CString tempGrpstr = L"";

		sContactInfo tempInfo = vectContact[i];
		for (int count=0; count<(int)vectContact[i].m_GroupIDs.size(); count++)
		{			
			CString tempGrpItemStr = L"";
			tempGrpItemStr.Format(L"{group:\'%s\'}",tempInfo.m_GroupIDs[count]);
			if (count == 0)
				tempGrpstr =  tempGrpItemStr;
			else
				tempGrpstr =tempGrpstr + L"," +tempGrpItemStr;
		}
		CString NamePos=::GetFirstLetter(tempInfo.m_Name);
		if(LastNamePos != NamePos)
			LastNamePos = NamePos;
		else
			NamePos.Empty();
		tempGrpstr = L"groupid:[" +tempGrpstr+L"],";
		CString pathType = _T("");
		switch (tempInfo.m_PathType)
		{
		case PATH_UNKOWN:
			pathType = _T("0");
			break;
		case PATH_PHONE:
			pathType = _T("1");
			break;
		case PATH_SDCARD:
			pathType = _T("2");
			break;
		}
		
		tempItem.Format(_T("position:\'%s\',id:\'%s\',name:\'%s\',mobilenumber:\'%s\',\
						 mobilehome:\'%s\',mobilework:\'%s\',phoneNumber:\'%s\',\
						 phonehome:\'%s\',phonework:\'%s\',email:\'%s\',homeaddress:\'%s\',\
						 company:\'%s\',birthday:\'%s\',fax:\'%s\',departtment:\'%s\',duties:\'%s\',pathtype:%s")\
						 ,NamePos,tempInfo.m_ID,tempInfo.m_Name,tempInfo.m_MobileNumber,tempInfo.m_MobileHome,tempInfo.m_MobileWork,tempInfo.m_PhoneNumber \
						 ,tempInfo.m_PhoneHome,tempInfo.m_PhoneWork,tempInfo.m_Email,tempInfo.m_HomeAddress,tempInfo.m_Company \
						 ,tempInfo.m_Birthday,tempInfo.m_Fax,tempInfo.m_Departments,tempInfo.m_Duties,pathType);
		tempItem = L"{" + tempGrpstr + tempItem +L"}";
		if (i == 0)
			ContactStrJson = tempItem;
		else
			ContactStrJson = ContactStrJson + L"," + tempItem;
	}
	ContactStrJson = L"{person:["+ContactStrJson+L"]}";
}

//��ϣ� vector ���� ת���� JSON String
void InterfaceToJS::CombinSmsToJson(const vector<sSmsInfo> &vectSms, CString& SmsStrJson)
{
	int countSms = (int)vectSms.size();
	if (countSms == 0)
		return;

	Json::Value SmsRoot;
	Json::Value SmsItem;
	Json::Value SmsArray;
	
	for (int i=0; i<countSms; i++)
	{
		CString strTempItemSms;
		sSmsInfo temSmsInfo = vectSms[i];
		strTempItemSms.Format(_T("{smsid:\'%s\',contactname:\'%s\',smscaller:\'%s\',smsbody:\'%s\', \
								 timestamp:\'%s\',smsstaus:%d,smsbox:%d}"), \
								 temSmsInfo.m_SmsID,temSmsInfo.m_ContactName,temSmsInfo.m_SmsCaller, \
								 temSmsInfo.m_SmsBody,temSmsInfo.m_TimeStamp,(int)temSmsInfo.m_SmsStaus,(int)temSmsInfo.m_SmsBox);
		if (i == 0)
			SmsStrJson = strTempItemSms;
		else
			SmsStrJson = SmsStrJson + L"," + strTempItemSms;
	}
	SmsStrJson = L"{sms:["+SmsStrJson+L"]}";
}

//��ϣ� vecttor���� ת����JSON String
void InterfaceToJS::CombinGroupInfo(const vector<sGroupInfo>&groupInfo, CString&StrGroupJson)
{
	int countGroup = (int)groupInfo.size();
	if (countGroup == 0)
		return;

	Json::Value GroupRoot;
	Json::Value GroupItem;
	Json::Value GroupArray;

	for (int i=0; i<countGroup; i++)
	{
		CString strTempItemGroup;
		sGroupInfo temGroupInfo = groupInfo[i];
		strTempItemGroup.Format(_T("{id:\'%s\',name:\'%s\',count:\'%s\',issystem:\'%s\'}"), \
								 temGroupInfo.m_GroupID,temGroupInfo.m_GroupName,temGroupInfo.m_ContactCount, \
								 temGroupInfo.m_IsSystem);
		if (i == 0)
			StrGroupJson = strTempItemGroup;
		else
			StrGroupJson = StrGroupJson + L"," + strTempItemGroup;
	}
	StrGroupJson = L"{group:["+StrGroupJson+L"]}";
}

//������ϵ�˷�����Ϣ    JSONת����vector
//_T("{\"group\":[{\"id\":\"123456\",\"name\":\"123456\",\"count\":\"123456\",\"issystem\":\"123456\"}]}");
void InterfaceToJS::AnalyContactGroupinfo(const CString& JsonGroup, vector<sGroupInfo>& vctGroupInfo)
{
	Json::Reader GroupReader;
	Json::Value  GroupValue;
	if (GroupReader.parse(CstringtoString(JsonGroup), GroupValue))
	{
		Json::Value arrayObj = GroupValue["group"];
		int i_size = arrayObj.size();
		for (int i = 0; i < i_size; i++)
		{
			sGroupInfo tempGroupInfo;
			CString cContactCount, cIsSystem;
			cContactCount = arrayObj[i]["count"].asCString();
			cIsSystem	  = arrayObj[i]["issystem"].asCString();
			tempGroupInfo.m_ContactCount = _ttoi(cContactCount);
			if (_ttoi(cIsSystem) == 1)
				tempGroupInfo.m_IsSystem = true;
			else if (_ttoi(cIsSystem) == 0)
				tempGroupInfo.m_IsSystem = false;

			tempGroupInfo.m_GroupID		 = arrayObj[i]["id"].asCString();
			tempGroupInfo.m_GroupName	 = arrayObj[i]["name"].asCString();
			vctGroupInfo.push_back(tempGroupInfo);
		}
	}
}

//���� JSON��ʽ����ϵ������  JSONת����vector
void InterfaceToJS::AnalyContactInfo(const CString& JsonConatct, vector<sContactInfo>& vectContactInfo)
{
	Json::Reader ContactReader;
	Json::Value  ContactValue;
	if (ContactReader.parse(CstringtoString(JsonConatct),ContactValue))
	{
		Json::Value arrayObj = ContactValue["person"];
		int i_size = arrayObj.size();
		for (int i=0; i<i_size; i++)
		{
			sContactInfo tempContactInfo;
			Json::Value GroupIdArra = arrayObj[i]["groupid"];
			for (int count=0; count<(int)GroupIdArra.size(); count++)
			{
				CString strGroup;
				strGroup = GroupIdArra[count]["group"].asCString();
				tempContactInfo.m_GroupIDs.push_back(strGroup);
			}
			tempContactInfo.m_Name = arrayObj[i]["name"].asCString();
			tempContactInfo.m_MobileNumber = arrayObj[i]["mobilenumber"].asCString();
			tempContactInfo.m_ID = arrayObj[i]["id"].asCString();
			tempContactInfo.m_MobileHome = arrayObj[i]["mobilehome"].asCString(); 
			tempContactInfo.m_MobileWork = arrayObj[i]["mobilework"].asCString(); 
			tempContactInfo.m_PhoneNumber = arrayObj[i]["phoneNumber"].asCString(); 
			tempContactInfo.m_PhoneHome = arrayObj[i]["phonehome"].asCString(); 
			tempContactInfo.m_PhoneWork = arrayObj[i]["phonework"].asCString(); 
			tempContactInfo.m_Email = arrayObj[i]["email"].asCString(); 
			tempContactInfo.m_HomeAddress = arrayObj[i]["homeaddress"].asCString(); 
			tempContactInfo.m_Company = arrayObj[i]["company"].asCString(); 
			tempContactInfo.m_Birthday = arrayObj[i]["birthday"].asCString(); 
			tempContactInfo.m_Fax = arrayObj[i]["fax"].asCString(); 
			tempContactInfo.m_Departments = arrayObj[i]["departtment"].asCString(); 
			tempContactInfo.m_Duties = arrayObj[i]["duties"].asCString();
			CString pathType = _T("");
			pathType = arrayObj[i]["pathtype"].asCString();
			tempContactInfo.m_PathType = (ePathType)_ttoi(pathType);
			vectContactInfo.push_back(tempContactInfo);
		}
	}
}

//���� JSON��ʽ�Ķ�������
void InterfaceToJS::AnalySmsInfo(const CString& JsonSms, vector<sSmsInfo>& vecSmsInfo)
{	
	Json::Reader SmsReader;
	Json::Value  SmsValue;
	if (SmsReader.parse(CstringtoString(JsonSms),SmsValue))
	{
		Json::Value arrayObj = SmsValue["sms"];
		int i_size = arrayObj.size();
		for (int i=0; i<i_size; i++)
		{
			sSmsInfo tempSmsInfo;
			tempSmsInfo.m_SmsID = arrayObj[i]["smsid"].asCString();
			tempSmsInfo.m_ContactName = arrayObj[i]["contactname"].asCString();
			tempSmsInfo.m_SmsBody = arrayObj[i]["smsbody"].asCString();
			tempSmsInfo.m_SmsCaller = arrayObj[i]["smscaller"].asCString();
			tempSmsInfo.m_TimeStamp = arrayObj[i]["timestamp"].asCString();
			tempSmsInfo.m_SmsStaus = (eSmsStaus)arrayObj[i]["smsstaus"].asInt();
			tempSmsInfo.m_SmsBox = (eSmsBox)arrayObj[i]["smsbox"].asInt();
			vecSmsInfo.push_back(tempSmsInfo);
		}
	}
}

//�������Ͷ��Žṹ
//_T("{\"sendsms\":[{\"phone\":\"123456\",\"text\":\"123456\"}]}");
void InterfaceToJS::AnalySendSmsInfo(const CString& JsonSendSms, vector<sSendSmsInfo>& vctSmsSendInfo)
{
	Json::Reader SmsSendReader;
	Json::Value  SmsSenValue;
	if (SmsSendReader.parse(CstringtoString(JsonSendSms),SmsSenValue))
	{
		Json::Value arrayObj = SmsSenValue["sendsms"];
		int i_size = arrayObj.size();
		for (int i=0; i<i_size; i++)
		{
			sSendSmsInfo tempInfo;
			tempInfo.m_PhoneNumber = arrayObj[i]["phone"].asCString();
			tempInfo.m_Text = arrayObj[i]["text"].asCString();
			vctSmsSendInfo.push_back(tempInfo);
		}
	}
}

//������ϵ�˻��߶��ŵ�ID   
//_T("{\"type\":3,\"contactid\":[{\"id\":\"123456\"},{\"id\":\"2354\"}]}");
int InterfaceToJS::CommonAnalyInfo(const CString& JsonData, vector<CString>& vecStrData, eTypeID etype)
{
	Json::Reader RedData;
	Json::Value ValuDate;
	Json::Value ItemData;

	if (RedData.parse(CstringtoString(JsonData), ValuDate))
	{
		Json::Value arrayData;
		switch (etype)
		{
		case ECONTACTID:
			arrayData = ValuDate["contactid"];
			break;
		case ESMSID:
			arrayData = ValuDate["smsid"];
			break;
		case EGROUPID:
			arrayData = ValuDate["groupid"];
			break;
		}
		CString cType;
		cType= ValuDate["type"].asCString();				//0ɾ��ʧ�� 1ɾ��ȫ�� 2ɾ������ 3ɾ������   ��ϵ��
		int iTpey = _ttoi(cType);
		if (iTpey == 1)
			return iTpey;
		int i_size = (int)arrayData.size();
		for (int i=0; i<i_size; i++)
		{
			CString tempStrID;
			tempStrID = arrayData[i]["id"].asCString();
			vecStrData.push_back(tempStrID);
		}
		return iTpey;
	}
	return 0;
}

//����JS��������·��
void InterfaceToJS::CommonAnalyPath(const CString& JsonData, CString& filePath)
{
	Json::Reader ReadDate;
	Json::Value  ValuDate;
	if (ReadDate.parse(CstringtoString(JsonData), ValuDate))
		filePath = ValuDate["path"].asCString();
}

//Cstring ת��Ϊstring��ʽ 
const string InterfaceToJS::CstringtoString(const CString &Cstr )
{
	CStringA tempCstrA(Cstr);
	return (string)tempCstrA.GetString();
}
