// DlgLianHaoLanQiu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgLianHaoLanQiu.h"
#include "FormulaCenter.h"
#include "Markup.h"

// CDlgLianHaoLanQiu �Ի���

#define FORMULA_COUNT 24
#define PAGE_COUNT 22

//��ȡģ��·��
CString GetAppCurrentPath3()
{
	CString server_ip;
	CString StrDes=_T("");
	::GetModuleFileName(NULL,StrDes.GetBuffer(MAX_PATH),MAX_PATH); 
	//::GetCurrentDirectory(MAX_PATH,StrDes.GetBuffer(MAX_PATH));
	StrDes.ReleaseBuffer();
	StrDes=StrDes.Left(StrDes.ReverseFind('\\'));
	if(StrDes.Right(1)!='\\')
		StrDes+="\\";

	return StrDes;
}

extern CString GetAppCurrentPath();


IMPLEMENT_DYNAMIC(CDlgLianHaoLanQiu, CDialog)

CDlgLianHaoLanQiu::CDlgLianHaoLanQiu(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLianHaoLanQiu::IDD, pParent)
{
	m_IsInitData = false;
	m_CurrentIndex=0;
    m_FormulaType=FORMULA_SHA_LAN;
	bool                 m_ReLoadData=false;
}

CDlgLianHaoLanQiu::~CDlgLianHaoLanQiu()
{
}

void CDlgLianHaoLanQiu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
}


BEGIN_MESSAGE_MAP(CDlgLianHaoLanQiu, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CDlgLianHaoLanQiu::OnBnClickedSearchBtn)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_PREV_BTN, &CDlgLianHaoLanQiu::OnBnClickedPrevBtn)
	ON_BN_CLICKED(IDC_NEXT_BTN, &CDlgLianHaoLanQiu::OnBnClickedNextBtn)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgLianHaoLanQiu::OnBnClickedButton5)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgLianHaoLanQiu::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_JINGXUAN_BTN, &CDlgLianHaoLanQiu::OnBnClickedJingxuanBtn)
	ON_BN_CLICKED(IDC_ZIDONG_BTN, &CDlgLianHaoLanQiu::OnBnClickedZidongBtn)
END_MESSAGE_MAP()


// CDlgLianHaoLanQiu ��Ϣ�������

//��ʼ���б�ͷ
void CDlgLianHaoLanQiu::InitListHeader()
{
	CRect Rect;
	//��ʼ��Ӧ�ó����б�ؼ�
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/(FORMULA_COUNT+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("����"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	for(int Index = 1; Index <= PAGE_COUNT; Index++)
	{
		CString Str;
		Str.Format("%02d",Index);
		m_ListCtrl.InsertColumn(Index,Str,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}

	m_ListCtrl.InsertColumn(PAGE_COUNT+1,"ͳ��",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(PAGE_COUNT+1,Style);
	m_ListCtrl.InsertColumn(PAGE_COUNT+2,"�Դ�",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(PAGE_COUNT+2,Style);

	
	m_ListCtrl.SetRowHeight(30);
	m_ListCtrl.ShowHeader(true);

	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);
	m_ListCtrl.SetItemBkData(ItemBkData);

}

void CDlgLianHaoLanQiu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData = true;
		sItemStyle Style;
		Style.m_ItemType = TEXT_TYPE;
		Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
		Style.m_DrawData.m_TextData.m_TextFont = NULL;
		Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

		m_ListCtrl.DeleteAllItems();
		OnBnClickedJingxuanBtn();
	
	}
			
}

// ���ɵ���Ϣӳ�亯��
BOOL CDlgLianHaoLanQiu::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();

	m_ComboBox.InsertString(0,"��ȷ�ʴ���");
	m_ComboBox.InsertString(1,"��ȷ�ʵ���");
	m_ComboBox.InsertString(2,"��ȷ��С��");
	m_ComboBox.InsertString(3,"��ȷ������");

	m_ComboBox.InsertString(4,"��βС��");
	m_ComboBox.InsertString(5,"��β����");
	m_ComboBox.InsertString(6,"��β����");
	m_ComboBox.InsertString(7,"��β����");
	m_ComboBox.InsertString(8,"���һ�δ�");

	m_ComboBox.InsertString(9,"�����");
	m_ComboBox.InsertString(10,"�����");
	m_ComboBox.InsertString(11,"��С��");
	m_ComboBox.InsertString(12,"������");

	m_ComboBox.SetCurSel(0);
	CenterWindow();
	return true;
}

void CDlgLianHaoLanQiu::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgLianHaoLanQiu::OnBnClickedSearchBtn()
{
	int Cursel=m_ComboBox.GetCurSel();
	int Data=-1;
	int Data1=-1;
	CString Text;
	GetDlgItemText(IDC_EDIT1,Text);
	if(!Text.IsEmpty())
		Data = atoi(Text.GetBuffer());
	Text.Empty();
	GetDlgItemText(IDC_EDIT6,Text);
	if(!Text.IsEmpty())
		Data1=atoi(Text.GetBuffer());
	m_CurrentIndex=0;
	m_FormulaInfoList=CFormulaCenter::GetInstance()->SearchFormulaInfoByType(m_FormulaType,eSearchVType(Cursel),Data,Data1);
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}

BOOL CDlgLianHaoLanQiu::OnEraseBkgnd(CDC* pDC)
{

	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgLianHaoLanQiu::FillData(vector<sFormulaInfo>& FormulList)
{
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.DeleteAllItems();

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	int DataSize = DataList->size();
	for(int Index = 0; Index < DataSize; Index++)
	{
		m_ListCtrl.InsertItem(Index,_T(""));	
	}

	m_ListCtrl.InsertItem(DataSize+1,_T(""));

	int EndIndex = FormulList.size() > PAGE_COUNT ? PAGE_COUNT:FormulList.size();
	if(FormulList.empty())
		return;

	for(int Index =0; Index < EndIndex; Index++)
	{
		m_ListCtrl.SetItemText(0,Index+1,FormulList[Index].m_FormulaName);
	}

	m_ListCtrl.SetItemText(0,PAGE_COUNT+1,_T("ͳ��"));
	m_ListCtrl.SetItemText(0,PAGE_COUNT+2,_T("�Դ�"));

	
	for(int Index = 0; Index < EndIndex;Index++)
	{
		for(int i = 0; i < FormulList[Index].m_DataList.size(); i++)
		{
			int TempIndex = Index;
			if(TempIndex ==0)
			{
				CString QiShu=FormulList[Index].m_DataList[i].m_QiShu;
				if(i+1 < DataList->size())
				{
					CString TempStr;
					TempStr.Format(" %02d",(*DataList)[i+1].m_LanQiu);
					QiShu=(*DataList)[i+1].m_QiShu+TempStr;
				}
				m_ListCtrl.SetItemText(i+1,0,QiShu);
			}
			m_ListCtrl.SetItemText(i+1,TempIndex+1,FormulList[Index].m_DataList[i].m_Data);
			if(FormulList[Index].m_DataList[i].m_IsTrue)
			{
				if(Index %2 == 0)
					Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
				else
					Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);

				Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
				m_ListCtrl.SetItemSpecialStyle(i+1,TempIndex+1,Style);
			}
			else
			{

				Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
				Style.m_DrawData.m_TextData.m_BGColor = RGB(248,183,173);
				m_ListCtrl.SetItemSpecialStyle(i+1,TempIndex+1,Style);
			}
		
		}
	}

	int AllErrorCount=0;
	int AllTrueCount=0;

	for(int Index = 0; Index < FormulList[0].m_DataList.size(); Index++)
	{
		int ErrorCount=0;
		
		int Array[50];
		memset(Array,0,50*sizeof(int));
		for(int i=0; i < EndIndex; i++)
		{
			int Data=abs(atoi(FormulList[i].m_DataList[Index].m_Data.GetBuffer()));
			if(!FormulList[i].m_DataList[Index].m_IsTrue)
				ErrorCount++;

			if(Index == FormulList[0].m_DataList.size()-1)
				Array[Data]++;

		}


		CString Str2;

		if(ErrorCount)
		{
			Str2="��";
			AllErrorCount++;
		}
		else
		{
			Str2="��";
			AllTrueCount++;
		}

		CString Temp;
		Temp.Format("%02d",ErrorCount);

		m_ListCtrl.SetItemText(Index+1,PAGE_COUNT+1,Temp);
		m_ListCtrl.SetItemText(Index+1,PAGE_COUNT+2,Str2);

		if(!ErrorCount)
		{
			Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
			m_ListCtrl.SetItemSpecialStyle(Index+1,PAGE_COUNT+1,Style);
			m_ListCtrl.SetItemSpecialStyle(Index+1,PAGE_COUNT+2,Style);
		}
		else
		{
			Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
			m_ListCtrl.SetItemSpecialStyle(Index+1,PAGE_COUNT+1,Style);
			m_ListCtrl.SetItemSpecialStyle(Index+1,PAGE_COUNT+2,Style);
		}


		CString Str;
		int TempCount=0;
		for(int k= 0; k < 50; k++)
		{
			if(Array[k])
			{
				CString TempStr;
				TempStr.Format("%02d ",k);
				Str+=TempStr;
				TempCount++;
			}

		}

		CString TempStr2;
		TempStr2.Format("ɱ�Ÿ���=%02d ɱ��= ",TempCount);
		Str=TempStr2+Str;
		 
		//SetDlgItemText(IDC_RESULT2,Str);
		GetDlgItem(IDC_RESULT2)->SetWindowText(Str);

	}




	m_ListCtrl.InsertItem(DataSize+2,_T(""));
	m_ListCtrl.SetItemText(DataSize+2,0,_T("��ȷ��"));
	for(int Index = 0; Index < EndIndex; Index++)
	{
		int TempIndex = Index ;
		CString Str;
		if(FormulList[Index].m_ErrorCount+FormulList[Index].m_TrueCount != 0)
			Str.Format(_T("%d%%"),FormulList[Index].m_TrueCount*100/(FormulList[Index].m_ErrorCount+FormulList[Index].m_TrueCount));
		m_ListCtrl.SetItemText(DataSize+1,TempIndex+1,Str);
		Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
		m_ListCtrl.SetItemSpecialStyle(DataSize,TempIndex+1,Style);
	}

	if(AllErrorCount+AllTrueCount)
	{
		CString TempStr;
		TempStr.Format(_T("%d%%"),AllTrueCount*100/(AllErrorCount+AllTrueCount));
		m_ListCtrl.SetItemText(DataSize+1,PAGE_COUNT+2,TempStr);
		Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
		m_ListCtrl.SetItemSpecialStyle(DataSize+1,18,Style);
	}
}

void CDlgLianHaoLanQiu::OnBnClickedPrevBtn()
{
	if(m_FormulaInfoList.empty())
		return;

	int Count=0;
	m_CurrentIndex-=PAGE_COUNT;
	if(m_CurrentIndex < 0)
		m_CurrentIndex=0;

	Count=m_CurrentIndex+PAGE_COUNT;
	if(Count > m_FormulaInfoList.size())
		Count=m_FormulaInfoList.size()-1;

	UpdateBtnStatus();




	vector<sFormulaInfo>::iterator it = m_FormulaInfoList.begin();
	vector<sFormulaInfo> Temp;
	Temp.insert(Temp.begin(),it+m_CurrentIndex,it+Count);
	FillData(Temp);
}

void CDlgLianHaoLanQiu::OnBnClickedNextBtn()
{
	if(m_FormulaInfoList.empty())
		return;

		m_CurrentIndex+=PAGE_COUNT;
	if(m_CurrentIndex >= m_FormulaInfoList.size())
		m_CurrentIndex=m_FormulaInfoList.size()-1;

	int Count = m_CurrentIndex+PAGE_COUNT;
	if(Count >= m_FormulaInfoList.size()-1)
		Count=m_FormulaInfoList.size()-1;


	vector<sFormulaInfo>::iterator it = m_FormulaInfoList.begin();
	vector<sFormulaInfo> Temp;
	Temp.insert(Temp.begin(),it+m_CurrentIndex,it+Count);
	FillData(Temp);
	UpdateBtnStatus();
}

void CDlgLianHaoLanQiu::OnBnClickedButton5()
{
	m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(m_FormulaType);
	m_CurrentIndex=0;
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}

void CDlgLianHaoLanQiu::UpdateBtnStatus()
{
	if(m_CurrentIndex + PAGE_COUNT < m_FormulaInfoList.size())
		GetDlgItem(IDC_NEXT_BTN)->EnableWindow(true);
	else
		GetDlgItem(IDC_NEXT_BTN)->EnableWindow(false);

	if(m_CurrentIndex - PAGE_COUNT < 0)
		GetDlgItem(IDC_PREV_BTN)->EnableWindow(false);
	else
		GetDlgItem(IDC_PREV_BTN)->EnableWindow(true);

}
void CDlgLianHaoLanQiu::OnCbnSelchangeCombo1()
{
		OnBnClickedSearchBtn();
}

void CDlgLianHaoLanQiu::OnBnClickedJingxuanBtn()
{
	CMarkup Xml;
	CString FormulaName=GetAppCurrentPath()+"FormulaNameList.xml";
	Xml.Load(FormulaName.GetBuffer());
	FormulaName.ReleaseBuffer();

	vector<CString> NameList;

	while(Xml.FindChildElem("FormulaInfo"))
	{
		Xml.IntoElem();
		Xml.FindChildElem("FormulaName");
		CString Name=Xml.GetChildData().c_str();

		Xml.FindChildElem("FormulaType");
		CString StrType=Xml.GetChildData().c_str();
		
		int Type = atoi(StrType.GetBuffer());
		StrType.ReleaseBuffer();

		if(Type == m_FormulaType && !Name.IsEmpty())
			NameList.push_back(Name);
			
		Xml.OutOfElem();
	}

	if(NameList.empty())
	{
		m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(m_FormulaType);
	}
	else
		m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByName(m_FormulaType,NameList);

	m_CurrentIndex=0;
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}

void CDlgLianHaoLanQiu::OnBnClickedZidongBtn()
{
	
		//CString FilePath2 = GetAppCurrentPath()+_T("\\zidongfenxi.txt");

		//HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		//if(FileHandle2 == INVALID_HANDLE_VALUE)
		//{
		//	AfxMessageBox(_T("���ļ�ʧ�ܣ�"));
		//	return;
		//}
		//	
		//vector<sFormulaInfo> InfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_LAN);
		//vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		//int DataSize = DataList->size();
		//int Offset=18;

		//CString StrArray[9]={"����        һҳ�",
		//	"����        ��ҳ�",
		//	"����        ��ҳ�",
		//	"����     һ ��ҳ�",
		//	"����     һ ��ҳ�",
		//	"����     �� ��ҳ�",
		//	"����  һ �� ��ҳ�",
		//	"����һ �� ��ҳ�",
		//	"�ۺ�"};
		//for(int Index = 0; Index < DataSize; Index++)
		//{
		//	int TeArray1[50];
		//	int TeArray2[50];
		//	int TeArray3[50];
		//	int TeArray4[50];
		//	memset(TeArray1,0,sizeof(int)*50);
		//	memset(TeArray2,0,sizeof(int)*50);
		//	memset(TeArray3,0,sizeof(int)*50);
		//	memset(TeArray4,0,sizeof(int)*50);

		//	for(int i = 0 ; i <InfoList.size(); i++)
		//	{
		//		if(InfoList[i].m_DataList.empty())
		//			continue;

		//		int TempData=atoi(InfoList[i].m_DataList[Index].m_Data.GetBuffer());
		//		TeArray4[TempData]++;

		//		if(i < Offset)
		//		{
		//			TeArray1[TempData]++;
		//		}
		//		else if( i >= Offset && i < 2*Offset)
		//		{
		//			TeArray2[TempData]++;

		//		}
		//		else
		//			TeArray3[TempData]++;
		//	}


		//	int TempArray[8][50];
		//	memset(TempArray,0,8*50*sizeof(int));

		//	for(int j=0; j < 50; j++)
		//	{
		//		//����һ����
		//		if(TeArray1[j] && !TeArray2[j] && !TeArray3[j])
		//		{
		//			int TempData = j;
		//			TempArray[0][TempData]++;
		//		}

		//		//���ڶ�����
		//		if(TeArray2[j] && !TeArray1[j] && !TeArray3[j])
		//		{
		//			int TempData = j;
		//			TempArray[1][TempData]++;
		//		}

		//		//������ ����
		//		if(TeArray2[j] && TeArray1[j] && TeArray3[j])
		//		{
		//			int TempData = j;
		//			TempArray[2][TempData]++;
		//		}


		//		//����һ ������
		//		if(TeArray1[j] && TeArray2[j] && !TeArray3[j])
		//		{
		//			int TempData = j;
		//			TempArray[3][TempData]++;
		//		}

		//		//����һ ������
		//		if(TeArray1[j] && !TeArray2[j] && TeArray3[j])
		//		{
		//			int TempData = j;
		//			TempArray[4][TempData]++;
		//		}

		//		//���ڶ� �� ����
		//		if(TeArray2[j] && !TeArray1[j] && TeArray3[j])
		//		{
		//			int TempData = j;
		//			TempArray[5][TempData]++;
		//		}

		//		//����һ �� �� ����
		//		if(TeArray1[j] && TeArray2[j] && TeArray3[j])
		//		{
		//			int TempData = j;
		//			TempArray[6][TempData]++;
		//		}

		//		//�ز�����һ �� �� ����
		//		if(!TeArray1[j] && !TeArray2[j] && !TeArray3[j])
		//		{
		//			int TempData = j;
		//			TempArray[7][TempData]++;
		//		}

		//	}


		//	CString TongJi;
		//	int TempTest[50];
		//	memset(TempTest,0,sizeof(int)*50);
		//	CString WriteStr;
		//	if(Index == DataSize-1)
		//	{
		//		WriteStr="����Ԥ�⣺\r\n";
		//	}
		//	else
		//	{
		//		CString TeStr;
		//		TeStr.Format(" ���� %02d",(*DataList)[Index+1].m_LanQiu);
		//		WriteStr=(*DataList)[Index+1].m_QiShu+"��"+TeStr+"��\r\n";
		//	}

		//	for(int i=0; i < 8; i++)
		//	{
		//		int Count=0;
		//		CString Str;
		//		for(int j=0; j < 50; j++)
		//		{
		//			CString Temp;
		//			if(TempArray[i][j])
		//			{
		//				Temp.Format("%02d ",j);
		//				Str+=Temp;
		//				TempTest[j]++;
		//				Count++;

		//			}
		//		}

		//		CString CountStr;
		//		CountStr.Format("���� %02d��",Count);

		//		CString TempStr=StrArray[i]+CountStr+Str+"\r\n";
		//		WriteStr+=TempStr;
		//	}

		//	WriteStr+="\r\n\r\n";
		//	DWORD WriteBytes=0;
		//	::WriteFile(FileHandle2,WriteStr.GetBuffer(),WriteStr.GetLength(),&WriteBytes,NULL);

		//}	
		//
		//CloseHandle(FileHandle2);
		//ShellExecute(NULL, "open",FilePath2, NULL, NULL, SW_SHOWNORMAL);
}

//���ô��ڱ���
void CDlgLianHaoLanQiu::SetWondowsTitle(CString Title,eFormulaType Type)
{
	if(Type != m_FormulaType)
	{
		m_FormulaType=Type;
		SetWindowText(Title);
		m_ListCtrl.DeleteAllItems();
		OnBnClickedJingxuanBtn();

	}
}