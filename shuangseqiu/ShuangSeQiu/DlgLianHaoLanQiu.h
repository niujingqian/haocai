#pragma once


// CDlgLianHaoLanQiu �Ի���

class CDlgLianHaoLanQiu : public CDialog
{
	DECLARE_DYNAMIC(CDlgLianHaoLanQiu)

public:
	CDlgLianHaoLanQiu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLianHaoLanQiu();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG2 };

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

public:
	afx_msg void OnBnClickedSearchBtn();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);


};
