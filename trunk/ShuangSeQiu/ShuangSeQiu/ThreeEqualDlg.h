#pragma once


// CThreeEqualDlg �Ի���

class CThreeEqualDlg : public CDialog
{
	DECLARE_DYNAMIC(CThreeEqualDlg)

public:
	CThreeEqualDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThreeEqualDlg();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();


	//��ʼ���б�ͷ
	void InitListHeader();

private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
};
