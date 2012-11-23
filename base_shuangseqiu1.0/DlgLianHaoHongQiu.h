#pragma once


// CDlgLianHaoHongQiu �Ի���

class CDlgLianHaoHongQiu : public CDialog
{
	DECLARE_DYNAMIC(CDlgLianHaoHongQiu)

public:
	CDlgLianHaoHongQiu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLianHaoHongQiu();

// �Ի�������
	enum { IDD = IDD_SHUANGSEQIU_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	//��ʼ���б�ͷ
	void InitListHeader();

	//����β����
	int TransDataByInt(CString DataStr,int Data2 );

	//˫��β����
	int TransDataByInt(CString DataStr,int Data2 ,int Data3);

	CString TransData(CString DataStr,float Data);

	//�����ɫ
	void FillItemStyleColor(sItemStyle& Style,bool IsTrue1,bool IsTrue2);

private:

	//���˫��β����
	void FillShuangDanList(int FillType);

	//�������
	void FillDataByType(int FillType,bool FillWay,int& List2Index);

	//�������
	void FillShuangDanListData(CListCtrlEx& ListCtrl,vector<sShuangSeQiu>* DataList,int Data,int Index, int& CololIndex);

private:
	CListCtrlEx m_ListCtrl;         //��ʾǰ������
	CListCtrlEx m_ListCtrl2;        //��ʾβ�� ���� ����
	CListCtrlEx m_ListCtrl3;        //��ʾ˫��
	BOOL      m_IsInitData;
	int       m_CompareShuangDanType; //˫���ȽϷ�ʽ
public:
	afx_msg void OnBnClickedSearchBtn();

	void AddFlag(CString& Str,bool IsTrue);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedWeiFenBtn();
	afx_msg void OnBnClickedHeFenBtn();


	
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedWeishuShuangdanBtn();
	afx_msg void OnBnClickedHeshuShuangdanBtn();
	afx_msg void OnBnClickedChashuShuangdanBtn();
};
