#pragma once


// CDlgLianHaoHongQiu �Ի���

class CDlgLianHaoHongQiu : public CDialog
{
	DECLARE_DYNAMIC(CDlgLianHaoHongQiu)

public:
	CDlgLianHaoHongQiu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLianHaoHongQiu();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG1 };

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
public:
	afx_msg void OnBnClickedSearchBtn();

	void AddFlag(CString& Str,bool IsTrue);
};
