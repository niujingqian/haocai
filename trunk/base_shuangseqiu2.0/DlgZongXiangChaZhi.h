#pragma once


// CDlgZongXiangChaZhi �Ի���

class CDlgZongXiangChaZhi : public CDialog
{
	DECLARE_DYNAMIC(CDlgZongXiangChaZhi)

public:
	CDlgZongXiangChaZhi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgZongXiangChaZhi();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	afx_msg void OnClose();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	//��ʼ���б�ͷ
	void InitListHeader();


	//�����������
	void FillQuData(sShuangSeQiu Data,int* DataArray,int DataCount);

	//�����������
	void FillQuData(sShuangSeQiu Data,map<int,CString> MapData,int* DataArray,int DataCount);

	DECLARE_MESSAGE_MAP()

	//��ȡ��������
	CString GetQuDataStr(int QuHao);


private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
	BOOL      m_IsLiShan;
	
public:
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};
