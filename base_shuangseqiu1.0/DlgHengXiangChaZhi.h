#pragma once


// CDlgHengXiangChaZhi �Ի���

class CDlgHengXiangChaZhi : public CDialog
{
	DECLARE_DYNAMIC(CDlgHengXiangChaZhi)

public:
	CDlgHengXiangChaZhi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHengXiangChaZhi();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	//��ʼ���б�ͷ
	void InitListHeader();


	//��ȡ��ɫֵ
	COLORREF GetColor(int Data);

	//��ȡ·��
	int GetLuShu(int Data);


	CString GetDataStr(int LuShu);

private:
	CListCtrlEx m_ListCtrl;
	BOOL        m_IsInitData;
public:
	afx_msg void OnBnClickedSearchBtn();
};
