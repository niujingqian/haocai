#pragma once


// CDlgZiDongFenXi �Ի���

class CDlgZiDongFenXi : public CDialog
{
	DECLARE_DYNAMIC(CDlgZiDongFenXi)

public:
	CDlgZiDongFenXi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgZiDongFenXi();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG8 };

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	//��ʼ���б�ͷ
	void InitListHeader();

	void OnClose();

	void OnShowWindow(BOOL bShow, UINT nStatus);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private :

	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
};
