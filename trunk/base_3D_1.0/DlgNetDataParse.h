#pragma once


// CDlgNetDataParse �Ի���

//�������ݷ���

class CDlgNetDataParse : public CDialog
{
	DECLARE_DYNAMIC(CDlgNetDataParse)

public:
	CDlgNetDataParse(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgNetDataParse();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_NET_PARSE };

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	

	//��ʼ���б�ͷ
	void InitListHeader();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedZhongcaiHongBtn();
	afx_msg void OnBnClickedZhongcailanBtn();
	afx_msg void OnBnClickedAoke360Btn();
	afx_msg void OnBnClickedWangyiBtn();


private:

	//��ȡ��ɫֵ
	COLORREF GetColor(int Data,bool IsDefault=false);

private:

	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
};
