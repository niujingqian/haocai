#pragma once


//����V�Ի���

class CDlgDingHongWei : public CDialog
{
	DECLARE_DYNAMIC(CDlgDingHongWei)

public:
	CDlgDingHongWei(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDingHongWei();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG10 };

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

private:
	CListCtrlEx m_ListCtrl;
	BOOL        m_IsInitData;
};
