#pragma once
#include "afxwin.h"


// CDlgWeiHong �Ի���

class CDlgWeiHong : public CDialog
{
	DECLARE_DYNAMIC(CDlgWeiHong)

public:
	CDlgWeiHong(CWnd* pParent = NULL);   // ��׼���캯��

	virtual ~CDlgWeiHong();

// �Ի�������
	enum { IDD = IDD_WEIHONG_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	//��ʼ���б�ͷ
	void InitListHeader();

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelchangeCombo1();

private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
	CComboBox m_ComboBox;
	vector<sData29> m_Result;

public:
	afx_msg void OnBnClickedButton1();

	void InsertTextToList(int InsertIndex,sData29& Data);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
};
