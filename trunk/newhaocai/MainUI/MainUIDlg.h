

#pragma once

#include "webbrowser2.h"
#include "Markup.h"
#include <vdmdbg.h>
#include <Dbt.h>
#include <SetupAPI.h>

#include <MSHTML.H>

class CMainUIDlg : public CDialog
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

protected:

	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDocumentCompleteExplorerMain(LPDISPATCH pDisp, VARIANT FAR* URL);

	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()	

private:

	IHTMLDocument2*  m_pIHTMLDoc;            //HTMLָ��
	CWebBrowser2	 m_wndWeb;               //Web�ں�
	
public:
	afx_msg void OnDestroy();
};