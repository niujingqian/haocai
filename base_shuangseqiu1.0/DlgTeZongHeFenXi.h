#pragma once


// CDlgTeZongHeFenXi �Ի���

class CDlgTeZongHeFenXi : public CDialog
{
	DECLARE_DYNAMIC(CDlgTeZongHeFenXi)

public:
	CDlgTeZongHeFenXi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTeZongHeFenXi();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

		// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	//��ʼ���б�ͷ
	void InitListHeader();

	void OnClose();

	void OnShowWindow(BOOL bShow, UINT nStatus);


private :

	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
};
