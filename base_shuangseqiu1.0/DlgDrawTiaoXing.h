#pragma once


// CDlgDrawTiaoXing �Ի���

class CDlgDrawTiaoXing : public CDialog
{
	DECLARE_DYNAMIC(CDlgDrawTiaoXing)

public:
	CDlgDrawTiaoXing(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDrawTiaoXing();

// �Ի�������
	enum { IDD = IDD_DRAW_TIAO_XING_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
