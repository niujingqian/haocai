
// ShuangSeQiuDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "RedBallDlg.h"
#include "DlgLianHaoHongQiu.h"
#include "DlgLianHaoLanQiu.h"
#include "DlgHengXiangChaZhi.h"
#include "DlgZongXiangChaZhi.h"
#include "DlgTongJiJieGuo.h"
#include "DlgFourEqual.h"
#include "ThreeEqualDlg.h"
#include "DlgShiFaDingHong.h"
#include "DlgZiDongFenXi.h"
#include "DlgTeZongHeFenXi.h"
#include "afxwin.h"

class CShuangSeQiuDlg : public CDialog
{
// ����
public:
	CShuangSeQiuDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedLoadDataBtn();
	afx_msg void OnBnClickedRedBallBtn();
	afx_msg void OnBnClickedSearchBtn();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBlueBallBtn2();
	afx_msg void OnBnClickedBlueBallBtn4();
	afx_msg void OnBnClickedBlueBallBtn3();
	afx_msg void OnBnClickedBlueBallBtn6();
	afx_msg void OnBnClickedSearchBtn2();
	afx_msg void OnBnClickedSearchBtn3();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton12();
		
	afx_msg void OnCbnSelchangeCombo1();

	//����������ı�
	void InsertAndSetText(int Row,sShuangSeQiu& ShuangSeQiu);
	afx_msg void OnBnClickedButton11();

private:

	//��ʼ���б�ͷ
	void InitListHeader();

private:

	CListCtrlEx m_ListCtrl;
	CRedBallDlg m_RedBallDlg;

	CDlgLianHaoHongQiu   m_DlgLianHaoHongQiu;
	CDlgLianHaoLanQiu    m_DlgLianHaoLanQiu;
	
	CDlgHengXiangChaZhi  m_DlgHengXiangChaZhi;
	CDlgZongXiangChaZhi  m_DlgZongXiangChaZhi;

	CDlgTongJiJieGuo     m_DlgTongJiJieGuo;

	CDlgFourEqual        m_DlgFourEqual;
	CThreeEqualDlg       m_DlgThreeEqual;
	CDlgShiFaDingHong    m_DlgShiFaDingHong;
	CDlgZiDongFenXi      m_DlgZiDongFenXi;
	CDlgTeZongHeFenXi    m_DlgTeZongHeFenXi;

	vector<sShuangSeQiu> m_ResultDataList;

	CButton m_CheckBtn;
	CComboBox m_ComboBox;
	bool      m_IsShowByChuQiu;
public:
	afx_msg void OnBnClickedBlueBallBtn();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedBlueBallBtn5();
};
