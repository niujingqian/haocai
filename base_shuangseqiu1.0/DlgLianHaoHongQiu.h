#pragma once
#include "afxwin.h"


//������������
struct sDataInfo
{
	int          m_Data;      //����
	CString      m_QiShu;     //����
	COLORREF     m_Color;     //��ɫֵ
};

//������������
enum eYanDataType
{
	TYPE_WEI_QIANSAN_HOUSAN,          //ǰ������β
	TYPE_HE_QIANSAN_HOUSAN,            //ǰ�������� 
	TYPE_CHA_QIANSAN_HOUSAN,          //ǰ��������
	TYPE_WEI_SHUANG_DAN,              //˫��β
	TYPE_HE_SHUANG_DAN,               //˫����
	TYPE_CHA_SHUANG_DAN,              //˫����
};

//��������������
enum eYanType
{
	TYPE_WEI,         //β
	TYPE_HE,          //��
	TYPE_CHA,         //��
};

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

	//��ʼ��Combox
	void InitCombox();

	//����β����
	int TransDataByInt(CString DataStr,int Data2 );

	//����β����
	int TransDataByInt(CString DataStr);

	//˫��β����
	int TransDataByInt(CString DataStr,int Data2 ,int Data3);

	CString TransData(CString DataStr,float Data);

	//�����ɫ
	void FillItemStyleColor(sItemStyle& Style,bool IsTrue1,bool IsTrue2);

private:

	//���˫��β����
	void FillShuangDanList(int FillType);

	//�������β����
	void FillSanDanList(int FillType);

	//�������
	void FillDataByType(int FillType,bool FillWay,int& List2Index);

	//�������β����
	void FillSanDanDataByType(int FillType,bool FillWay,int& List2Index);

	//�������
	void FillShuangDanListData(CListCtrlEx& ListCtrl,vector<sShuangSeQiu>* DataList,int Data,int Index, int& CololIndex);

	//�������
	void FillSanDanListData(CListCtrlEx& ListCtrl,vector<sShuangSeQiu>* DataList,int Data,int Index, int& CololIndex);

	//��ȡ���������
	sItemStyle GetSanDanItemStyle(int FillType,vector<sShuangSeQiu>* DataList,int Index,int Data);

private:
	CListCtrlEx m_ListCtrl;         //��ʾǰ������
	CListCtrlEx m_ListCtrl2;        //��ʾβ�� ���� ����
	CListCtrlEx m_ListCtrl3;        //��ʾ˫��
	BOOL      m_IsInitData;
	int       m_CompareShuangDanType; //˫���ȽϷ�ʽ
	int       m_CompareSanDanType;    //����β�ȽϷ�ʽ
	int       m_ParamData;            //����
	CComboBox m_ComboBox;

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
	afx_msg void OnBnClickedQianSanWeiBtn();
	afx_msg void OnBnClickedHouSanWeiBtn();
	afx_msg void OnBnClickedQianSanHeBtn();
	afx_msg void OnBnClickedHouSanHeBtn();
	afx_msg void OnBnClickedHouSanHeBtn2();
	afx_msg void OnBnClickedExecBtn();
	afx_msg void OnBnClickedJixianBtn();

public:
	
	//Ѱ�Ҽ��޻����߳�
	static DWORD WINAPI LookJiXianThread(LPVOID lpVoid);

	//��������
	void FillMapData(map<int,vector<sDataInfo>>& MapData,int StartPos,int OffsetPos,eYanType YanType,eYanDataType DataType,int Param);

	//�Ƿ�����Ҫ����������
	bool IsWantData(vector<sDataInfo>& VecData,eYanDataType DataType);

	//��伫������
	void FillJiXianDataList(eYanDataType DataType);

	//��ȡ������ɫֵ
	COLORREF GetDataColor(eYanDataType Type,sShuangSeQiu QiuData,int Data,bool IsV=false);

	//�����ظ�����
	void FilterMapData(map<int,map<int,vector<sDataInfo>>>& MapData);

	//�ж�����vector�������
	bool IsEqualVector(vector<sDataInfo>& Vec1,vector<sDataInfo>& Vec2);



private:
	map<int,map<int,vector<sDataInfo>>>  m_AllData;       //�Զ�������������
	int                                  m_Flag;            
};
