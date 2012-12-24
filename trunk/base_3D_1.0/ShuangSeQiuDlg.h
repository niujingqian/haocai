
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
#include "DlgDingHongWei.h"
#include "DlgNetDataParse.h"
#include "DlgJiXianWeiLan.h"
#include "afxwin.h"


struct sShuangSeQiuInfo
{
	CString m_QiHao;
	CString m_KaiJiangHao;
	CString m_ChuQiuShuanXu;
	CString m_BenQiXiaoLiang;
	CString m_JiangChiGunCun;
	CString m_OtherInfo;
};


//��ʾɱ������
enum eShowShaType
{
	TYPE_SHOW_NULL,                  //��
	TYPE_SHA_BAI_WEI,                //ɱ��λͼ
	TYPE_SHA_SHI_WEI,                //ɱʮλͼ
	TYPE_SHA_GE_WEI,                 //ɱ��λͼ
	TYPE_SHA_HE_WEI,                 //ɱ��βͼ
	TYPE_SHA_KUA_WEI,                //ɱ��λͼ
	TYPE_YI_CHUAN_DING_YI_DAN,       //�Ŵ���һ��
	TYPE_YI_CHUAN_DING_ER_DAN,       //�Ŵ�������
	TYPE_YI_CHUAN_DING_SAN_DAN,      //�Ŵ�������
	
};


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

	//����������ı�
	void InsertAndSetText2(int Row,sShuangSeQiu& ShuangSeQiu,int* pCount=NULL);
	
	//����������ı�
	void InsertAndSetText3(int Row,sShuangSeQiu& ShuangSeQiu,int* pCount=NULL);


	//�������
	void FillShowData(eShowShaType Type,bool LastError=false);

	//����Ŵ�����
	void FillYiChuanDataList(eShowShaType Type,bool LastError=false);


	afx_msg void OnBnClickedButton11();

private:

	//��ʼ���б�ͷ
	void InitListHeader();

	//��ʼ��ɱ����
	void InitShaMap();

	//���������������
	void LoadNetData();

	//��ʾ�б�
	void ShowListCtrl(int ShowIndex);

private:

	CListCtrlEx m_ListCtrl;
	CListCtrlEx m_ListCtrl2;
	CListCtrlEx m_ListCtrl3;
	CRedBallDlg m_RedBallDlg;

	CDlgLianHaoHongQiu   m_DlgLianHaoHongQiu;
	CDlgLianHaoLanQiu    m_DlgLianHaoLanQiu;
	CDlgDingHongWei      m_DlgDingHongWei;
	
	CDlgHengXiangChaZhi  m_DlgHengXiangChaZhi;
	CDlgZongXiangChaZhi  m_DlgZongXiangChaZhi;

	CDlgTongJiJieGuo     m_DlgTongJiJieGuo;

	CDlgFourEqual        m_DlgFourEqual;
	CThreeEqualDlg       m_DlgThreeEqual;
	CDlgShiFaDingHong    m_DlgShiFaDingHong;
	CDlgZiDongFenXi      m_DlgZiDongFenXi;
	CDlgTeZongHeFenXi    m_DlgTeZongHeFenXi;
	CDlgNetDataParse     m_DlgNetDataParse;
	CDlgJiXianWeiLan     m_DlgJiXianWeiLan;

	vector<sShuangSeQiu> m_ResultDataList;

	CButton m_CheckBtn;
	CComboBox m_ComboBox;
	bool      m_IsShowByChuQiu;
	CComboBox m_ShaComboBox;
	map<CString,int> m_MapList;
	CComboBox m_YiComboBox;

	int          m_StartPageCount;

	eShowShaType m_ShowShaType;


public:
	afx_msg void OnBnClickedBlueBallBtn();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedBlueBallBtn5();
	afx_msg void OnBnClickedLoadDataBtn2();

	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedPrevBtn();
	afx_msg void OnBnClickedNextBtn();
	afx_msg void OnBnClickedFirstBtn();
	afx_msg void OnBnClickedAutoBtn();


	static DWORD WINAPI RequestDataInfoThread(LPVOID lpVoid);

    //��ȡ��������
	static DWORD WINAPI RequestDataWangYiThread(LPVOID lpVoid);

	 //��ȡ�в���̨����
	static DWORD WINAPI RequestDataZhongCaiThread(LPVOID lpVoid);

	//��ȡ�Ŀ�����
	static DWORD WINAPI RequestDataAoKeThread(LPVOID lpVoid);
	
	//��ȡ360����
	static DWORD WINAPI RequestData360Thread(LPVOID lpVoid);


	//��ȡHTTP����
	static CString GetHttpData(CString Url);

	static DWORD WINAPI CombineDataThread(LPVOID lpVoid);


	//��������
	static bool PaseInfo(CString& Txt,sShuangSeQiuInfo& Info);

	//������ҳ����
	static bool PaseWangYiInfo(CString& Txt,sWangYiDataInfo& Info);
	static bool PaseWangYiInfo(CString& Txt,sWangYiDataInfo& Info,CString ParseFlag);

	//������ҳ3D����
	static bool ParseWangYi3DInfo(CString& Txt,vector<sWangYi3DInfo>& DataList);

	//�����в���̨����
	static bool PaseZhongCaiInfo(CString& Txt,vector<sZhongCaiDataInfo>& Info,int QiShuInt);
	static bool PaseZhongCaiInfo(CString& Txt,sZhongCaiDataInfo& Info,CString ParseFlag);

	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedYiChuanDingDan();

	//��������
	static void ParseData(CString& StrData,map<CString,vector<int>>& MapData);

	//��ȡ����
	static vector<int> GetDataList(CString& StrData);

	//�������
	static void Combine(map<CString,vector<int>> MapData);


public:



	//���ǰ���㷨����
	void FillQianSanData();

	
};
