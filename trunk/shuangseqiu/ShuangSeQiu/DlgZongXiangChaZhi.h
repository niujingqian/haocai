#pragma once


// CDlgZongXiangChaZhi �Ի���

class CDlgZongXiangChaZhi : public CDialog
{
	DECLARE_DYNAMIC(CDlgZongXiangChaZhi)

public:
	CDlgZongXiangChaZhi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgZongXiangChaZhi();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	afx_msg void OnClose();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	//��ʼ���б�ͷ
	void InitListHeader();


	DECLARE_MESSAGE_MAP()



private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
	
public:
	afx_msg void OnBnClickedSearchBtn();
};
