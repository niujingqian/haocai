#pragma once
#include "afxwin.h"
#include "FormulaCenter.h"

// CShiFaDingHong �Ի���

class CDlgShiFaDingHong : public CDialog
{
	DECLARE_DYNAMIC(CDlgShiFaDingHong)

public:
	CDlgShiFaDingHong(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShiFaDingHong();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnBnClickedSearchBtn();

	afx_msg void OnClose();
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	//��ʼ���б�ͷ
	void InitListHeader();

	void FillData(vector<sFormulaInfo>& FormulList);

private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
	CComboBox m_ComboBox;
	int       m_CurrentIndex;
	vector<sFormulaInfo> m_FormulaInfoList;
	
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedPrevBtn();
	afx_msg void OnBnClickedNextBtn();

	void UpdateBtnStatus();
};
