
// GetMailDataDlg.h : ͷ�ļ�
//

#pragma once

#include "HtmlCtrl.h"
#include <map>
#include "afxcmn.h"
using std::map;

// CGetMailDataDlg �Ի���
class CGetMailDataDlg : public CDialog
{
// ����
public:
	CGetMailDataDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GETMAILDATA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//������HTML�ؼ�
	void CreateNewHtmlCtrl(CString URL,CString PostData);

	//���������߳�
	static DWORD WINAPI RequestDataInfoThread(LPVOID lpVoid);

	//��������
	static void PaseText(CString Text, vector<CString>& List);

	//����A
	static void ParseHref(CString Text,vector<CString>& List,bool IsA=false);

	//����email 
	static void PaseEmail(CString Text,map<CString,int>& EmailMap);

	//�����ļ�
	static void PaseEmailTxt(CString Text,map<CString,int>& EmailMap);

	//���������Ϣ
	LRESULT OnParseOverMsg(WPARAM wParam,LPARAM lParam);

	//������������Ϣ
	LRESULT OnParseGoingMsg(WPARAM wParam,LPARAM lParam);

	//��ʼ����
	LRESULT OnStartParseMsg(WPARAM wParam,LPARAM lParam);

    //����email���ļ���
	static void SaveEmailToFile(CString Name,map<CString,int>& EmailMap);

public:
	afx_msg void OnBnClickedSearchBtn();


private:
	CHtmlCtrl* m_HtmlCtrl;
	HANDLE m_StopEvent;
	HANDLE m_ThreadHandle;
	CProgressCtrl m_ProgressCtrl;
public:
	afx_msg void OnBnClickedStopBtn();
};
