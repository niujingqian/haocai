#pragma once
#include "FormulaCenter.h"
#include "afxwin.h"

// CDlgLianHaoLanQiu �Ի���

class CDlgLianHaoLanQiu : public CDialog
{
	DECLARE_DYNAMIC(CDlgLianHaoLanQiu)

public:
	CDlgLianHaoLanQiu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLianHaoLanQiu();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG2 };

	//���ô��ڱ���
	void SetWondowsTitle(CString Title,eFormulaType Type);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	

	//��ʼ���б�ͷ
	void InitListHeader();

	void FillData(vector<sFormulaInfo>& FormulList);

	//��ȡ��ɫֵ
	COLORREF GetColor(int Data);
private:

	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
	CComboBox m_ComboBox;
	int       m_CurrentIndex;
	vector<sFormulaInfo> m_FormulaInfoList;
	eFormulaType         m_FormulaType;
	bool                 m_ReLoadData;

public:
	afx_msg void OnBnClickedSearchBtn();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);


	afx_msg void OnBnClickedPrevBtn();
	afx_msg void OnBnClickedNextBtn();
	afx_msg void OnBnClickedButton5();
	void UpdateBtnStatus();
	afx_msg void OnCbnSelchangeCombo1();

	afx_msg void OnBnClickedJingxuanBtn();
	afx_msg void OnBnClickedZidongBtn();
};
