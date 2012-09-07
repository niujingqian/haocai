
/***********************************************************************************
* ˵��      ��  ���������к�JS�����Ľӿ���                                         *
* ������    ��  ������                                                             *
* ��������  ��  2012-5-13                                                          *
***********************************************************************************/

#pragma once

#include "webbrowser2.h"
#include "MessageCenter.h"
#include "DataDefine.h"


#include <MSHTML.H>
#include <atlbase.h>
#include <vector>
#include <map>
using std::vector;
using std::map;
using std::string;
#include <atlbase.h>
#include "FormulaCenter.h"

class InterfaceToJS: public IMessageHandle
{
public:
	InterfaceToJS(IDispatch* DisPath);

	virtual ~InterfaceToJS(void);

	enum eTypeID{ECONTACTID, ESMSID, EGROUPID};

	// �ײ���Ϣ��Ӧ
	virtual void OnMessage(eMessage Message,DWORD SystemMsg=0,WPARAM wParam=0,LPARAM lParam=0);

	// ע����Ϣ
	void RegisterMsg();

	// ע����Ϣ
	void LogoutMsg();

	// ����DisPath	
	virtual void SetDisPath(IDispatch* DisPath); 
 
public:
/****************���Ի����������************/

	// �ر����Ի���
	virtual void CPP_Close(); 

	// ��С���Ի���
	virtual void CPP_MinDlg();

	// �϶����Ի���
	virtual void CPP_MoveMianDlg(int Xpoint, int Ypoint);

	/*******************************ɱ��ģ��*****************************************/
	//��ȡɱ������
	virtual void CPP_OnRequestShaHongData();

	//ɱ������ת����json����
	void ShaHongDataToJson(vector<sFormulaInfo>& FormulaInfo,CString& Str);

/*******************************��ϵ��ģ��*****************************************/
//	// �л�ģ��ʱ��ˢ��
//	virtual void CPP_OnRequestRfreshContactData();
//
//	// ��Ӧ ��ϵ�� ���� ����
//	virtual void CPP_OnRequestContactData(); 
//
//	// �����ϵ��
//	virtual void CPP_OnRequestAddContactData( const CString &contactDate );
//
//	// �����ϵ���ļ�
//	virtual void CPP_OnRequestAddContactFile( const CString & FilePath );
//
//	// ɾ����ϵ��
//	virtual void CPP_OnRequestDeleteContactData( const CString &  ID );
//
//	// �༭��ϵ��
//	virtual void CPP_OnRequestEditContactData( const CString & strConnect );
//
//	// ��ϵ�˱���
//	virtual void CPP_OnRequestBackUpContactData( const CString &  ID );
//
//	// �����������
//	virtual void CPP_OnRequestGroupData();
//
//	// ��ӷ���
//	virtual void CPP_OnRequestAddGroupData( const CString & str );
//
//	// ɾ������
//	virtual void CPP_OnRequestDeleteGroupData( const CString & str);
//	// �༭����
//	virtual void CPP_OnRequestEditGroupData( const CString & str);
//
///******************************����ģ��*****************************************/
//
//	// ����������ݣ�
//	virtual void CPP_OnRequestSmsData();
//
//	//	��Ӷ���
//	virtual void CPP_OnRequestAddSmsData( const CString & contactDate ){}
//
//	//	��Ӷ����ļ�
//	virtual void CPP_OnRequestAddSmsFile( const CString & FilePath ){}
//
//	//	ɾ������
//	virtual void CPP_OnRequestDeleteSmsData( const CString &  ID );
//
//	//	�༭����
//	virtual void CPP_OnRequestEditSmsData( const CString & str ){}
//
//	//	���Ͷ���
//	virtual void CPP_OnRequestSendSms( const CString & str );
//
//	//	���յ��¶���
//	virtual void CPP_OnRequestAcceptSms(){}    				//��
//
///******************************�ļ�����ģ��**************************************/
//
//	// ����װAPK
//	virtual void CPP_OnRequestInstallApk( const CString & ){}
//
//	// ����������װAPK
//	virtual void CPP_OnRequestBatchInstallApk( const CString & ){}
//
//	// ����ж��APK
//	virtual void CPP_OnRequestUninstallApk(const CString & ){}
//
//	// ��������ж��APK
//	virtual void CPP_OnRequestBatchUninstallApk(const CString &){}
//
//private:	    
///********************************���ݽ�������װ����************************************/
//
//	//// ������ϵ������ 
//	//void AnalyContactInfo( const CString& JsonConatct, vector<sContactInfo>&);
//
//	//// ������������ 
//	//void AnalySmsInfo( const CString& JsonSms, vector<sSmsInfo>&);
//
//	//// ������ϵ�� ���� ����
//	//void AnalyContactGroupinfo(const CString& JsonConatct, vector<sGroupInfo>&);
//
//	//// �������Ͷ�������
//	//void AnalySendSmsInfo(const CString& JsonSendSms, vector<sSendSmsInfo>&);
//
//	//// ������ϵ�˻��߶��ŵ�ID 
//	//int CommonAnalyInfo(const CString& JsonData, vector<CString>& vctinfo, eTypeID etype);
//
//	//// ����JS��������·��
//	//void CommonAnalyPath(const CString& JsonData, CString& filePath);
//
//	//// ��� �ṹ�� ��ϵ�� �� JSON��ʽ
//	//void CombinContactToJson(const vector<sContactInfo>& , CString&);
//
//	//// ��� �ṹ�� ���� ��� JSON��ʽ
//	//void CombinGroupInfo(const vector<sGroupInfo>&, CString&);
//
//	//// ��� �ṹ�� ���� ��� JSON��ʽ
//	//void CombinSmsToJson(const vector<sSmsInfo>&, CString&);
//
//	// Cstring ת string �ַ� 
//	const string CstringtoString( const CString &Cstr ); 
//
//private:

	// ִ��JS�ű� ����
	virtual void ExecJsScript(CString& JsStr); 

	//// JS�ӿ�+������CString��ʽ
	CString MakeStrJsIntface(const CString& JsIntface,const CString& JsParame );

	//// ִ����ϵ��JS�ӿ�+����
	//void DoContactJsIntface(const CString&JsIntface, vector<sContactInfo>& ContactInfo);

	//// ִ�ж���JS�ӿ�+����
	//void DoSmsJsIntface(const CString&JsIntface, vector<sSmsInfo>& ContactInfo);

	 

	//// ������ϵ����Ϣ
	//void ContacReturnWeb(eMessage Message,WPARAM wParam, LPARAM lParam);

	//// ������ϵ����Ϣ
	//void SmsReturnWeb(eMessage Message,WPARAM wParam, LPARAM lParam);

private:
	IDispatch*   m_DisPath;
	
};
