#pragma once


// CShiFaDingHong �Ի���

class CDlgShiFaDingHong : public CDialog
{
	DECLARE_DYNAMIC(CDlgShiFaDingHong)

public:
	CDlgShiFaDingHong(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShiFaDingHong();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG7 };

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
	CListCtrl m_ListCtrl;
	BOOL      m_IsInitData;
};
