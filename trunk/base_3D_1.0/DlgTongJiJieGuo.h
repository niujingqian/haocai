#pragma once

class CDlgTongJiJieGuo : public CDialog
{
	DECLARE_DYNAMIC(CDlgTongJiJieGuo)

public:
	CDlgTongJiJieGuo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTongJiJieGuo();

	virtual BOOL OnInitDialog();

	afx_msg void OnClose();

	void SetTongJieData(vector<sShuangSeQiu>& DataList);

	//ͳ��
	void TongJi();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

private:
	vector<sShuangSeQiu> m_TongJiDataList;
	int                  m_JiShuQi[QIU_COUNT];
	bool                 m_IsInitData;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	
};
