#pragma once


// CDlgFourEqual �Ի���

class CDlgFourEqual : public CDialog
{
	DECLARE_DYNAMIC(CDlgFourEqual)

public:
	CDlgFourEqual(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFourEqual();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();


	//��ʼ���б�ͷ
	void InitListHeader();

	//��ȡ��ȵ�ƽ��
	vector<int> GetEqualData(vector<sShuangSeQiu>& DataList);

private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
};
