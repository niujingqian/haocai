#pragma once

//����Χ��

class CDlgJiXianWeiLan : public CDialog
{
	DECLARE_DYNAMIC(CDlgJiXianWeiLan)

public:
	CDlgJiXianWeiLan(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgJiXianWeiLan();

// �Ի�������
	enum { IDD = IDD_DLG_WEI_LAN };


	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	//��ʼ���б�ͷ
	void InitListHeader();


	//��ȡ��ɫֵ
	COLORREF GetColor(int Data);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


private:
	CListCtrlEx m_ListCtrl;
	BOOL        m_IsInitData;
};
