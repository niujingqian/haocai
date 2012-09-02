

#pragma once

#include "webbrowser2.h"
#include "IDataEngine.h"
#include "MessageCenter.h"
#include "Markup.h"
#include <vdmdbg.h>
#include <Dbt.h>
#include <SetupAPI.h>

#include <MSHTML.H>

class CMainUIDlg : public CDialog,public IMessageHandle
{
public:

	CMainUIDlg(CWnd* pParent = NULL);							// standard constructor
	enum { IDD = IDD_PCSUITE_DIALOG };
protected:

	virtual void DoDataExchange(CDataExchange* pDX);			// DDX/DDV support

public:

	void	SetRoundWindows(int Width, int Height, int round);  //���öԻ���Բ��
	void	MoveMainDlg(int iArg1 , int iArg2);					//�ƶ����Ի���
	BOOL	IsAppRun(CString   AppName);						//��������
	DWORD   GetProcessIdFromName(LPCTSTR   name);				//��ý����е�IDͨ��������
	const char* CStrToChar(CString strSrc);						//��Cstring ת���� const char *

public:
	
	afx_msg LRESULT UsbStateChange ( WPARAM wParam, LPARAM lParam );

protected:

	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDocumentCompleteExplorerMain(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()	


public:

	//��Ӧ��Ϣ
	virtual void OnMessage(eMessage Message,DWORD SystemMsg=0,WPARAM wParam=0,LPARAM lParam=0);

	//�Ƿ��������ֻ�
	BOOL IsConnectedPhone();

	//

protected:

	//��ȡ�������豸ID
	void GetClassNameAndDevId(CString DesStr,CString& ClassName,CString& DevId,CString& PhoneDes);

	//��ȡ����ID�Ͳ�ƷID
	void GetVidAndPid(CString DevId,CString& Vid,CString& Pid);
	void GetVidAndPid(CString DevId,CString& Vid,CString& Pid,CString& PhoneDes);


	//�ж��Ƿ�Ϊƥ���е��ֻ�
	BOOL IsMatchPhone(CString VidPid,CString PhoneDes);

	//����������Ϣ
	void LoadDriveInfo();

	//��ʼ���ֻ���Ϣ
	void InitUsbConnectInfo();

	//����û�а�װ�������豸
	void FilterNotInstallDriveDevice(map<CString,CString>& DesMap);

	//��ȡ����USB�˿ڵ�Ӳ��VID��PID
	void GetConnectUsbPortDes(vector<CString>& DesList);

	//ע��USB�����¼�
	void RegisterUsbListenEvent();


private:

	IDataEngine*     m_DataEngine;           //��������ӿ�
	IHTMLDocument2*  m_pIHTMLDoc;            //HTMLָ��
	CWebBrowser2	 m_wndWeb;               //Web�ں�
	
	BOOL             m_IsUsbEnable;          //�Ƿ�����USB��ʶ
	BOOL             m_IsConnecting;		 //����������
	CMarkup          m_DriveInfoXml;         //���������ļ�
	
public:
	afx_msg void OnDestroy();
};

static const GUID GUID_DEVINTERFACE_LIST[] = 
{
	// GUID_DEVINTERFACE_USB_DEVICE
	{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },

	// GUID_DEVINTERFACE_DISK
//	{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },

	// GUID_DEVINTERFACE_HID, 
//	{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },

	// GUID_NDIS_LAN_CLASS
//	{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }

	//// GUID_DEVINTERFACE_COMPORT
	//{ 0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },

	//// GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR
	//{ 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } },

	//// GUID_DEVINTERFACE_PARALLEL
	//{ 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } },

	//// GUID_DEVINTERFACE_PARCLASS
	//{ 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } }
};