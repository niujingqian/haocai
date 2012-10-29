// DlgLianHaoHongQiu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgLianHaoHongQiu.h"


extern CString GetAppCurrentPath();
// CDlgLianHaoHongQiu �Ի���

IMPLEMENT_DYNAMIC(CDlgLianHaoHongQiu, CDialog)

CDlgLianHaoHongQiu::CDlgLianHaoHongQiu(CWnd* pParent /*=NULL*/)
: CDialog(CDlgLianHaoHongQiu::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgLianHaoHongQiu::~CDlgLianHaoHongQiu()
{
}

void CDlgLianHaoHongQiu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgLianHaoHongQiu, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()

	ON_BN_CLICKED(IDC_BUTTON1, &CDlgLianHaoHongQiu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgLianHaoHongQiu::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgLianHaoHongQiu ��Ϣ�������

//��ʼ���б�ͷ
void CDlgLianHaoHongQiu::InitListHeader()
{
    CRect Rect;
	//��ʼ��Ӧ�ó����б�ؼ�
	m_ListCtrl.GetWindowRect(&Rect);
	int ColoCount=10;
	int nWidth = Rect.Width()/(ColoCount+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("����"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	for(int Index = 1; Index <= ColoCount; Index++)
	{
		CString Str;
		Str.Format("%02d",Index);
		m_ListCtrl.InsertColumn(Index,Str,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}

	m_ListCtrl.InsertColumn(ColoCount+1,"ͳ��",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(ColoCount+1,Style);
	m_ListCtrl.InsertColumn(ColoCount+2,"�Դ�",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(ColoCount+2,Style);

	
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

void CDlgLianHaoHongQiu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData = true;
		OnBnClickedButton1();
		
	}
}

// ���ɵ���Ϣӳ�亯��
BOOL CDlgLianHaoHongQiu::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgLianHaoHongQiu::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgLianHaoHongQiu::OnBnClickedSearchBtn()
{
	CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	DWORD Data=::atoi(Text.GetBuffer());
	m_ListCtrl.DeleteAllItems();
	vector<sShuangSeQiu>* DataList = NULL;
	vector<sShuangSeQiu> Temp;
	if(Data == 0)
	{
		DataList=CDataManageCenter::GetInstance()->GetLianHaoHongQiu();
	}
	else
	{
		Temp=CDataManageCenter::GetInstance()->SearchLianHaoHongQiu(Data);
		DataList=&Temp;
	}

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl.InsertItem(Index,"");
		m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
		for(int HongQiu=0; HongQiu < 6; HongQiu++)
		{
			CString Temp;
			Temp.Format("%d",(*DataList)[Index].m_HongQiu[HongQiu]);
			m_ListCtrl.SetItemText(Index,HongQiu+1,Temp);
		}

		CString HongQiuSum;
		HongQiuSum.Format("%d",(*DataList)[Index].m_HongQiuSum);
		m_ListCtrl.SetItemText(Index,7,HongQiuSum);

		CString LanQiu;
		LanQiu.Format("%d",(*DataList)[Index].m_LanQiu);
		m_ListCtrl.SetItemText(Index,8,LanQiu);
	}
}

void CDlgLianHaoHongQiu::AddFlag(CString& Str,bool IsTrue)
{
	if(IsTrue)
		Str+="S";
	else
		Str+="F";
}

CString CDlgLianHaoHongQiu::TransData(CString DataStr,float Data)
{
	int TempData = atoi(DataStr.GetBuffer());
	if(TempData == 0)
		return "";

	CString RetStr;

	float TempData2=(float)TempData*Data;
	RetStr.Format("%f",TempData2);
	RetStr=RetStr.Mid(RetStr.Find(".")+1,3);
	return RetStr;
}

void CDlgLianHaoHongQiu::OnBnClickedButton1()
{
	m_ListCtrl.DeleteAllItems();
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();


		m_ListCtrl.SetItemText(0,0,"����");
		m_ListCtrl.SetItemText(0,1,"��˳ǰ��V");
		m_ListCtrl.SetItemText(0,2,"��˳����V");
		m_ListCtrl.SetItemText(0,3,"��ǰ��V");
		m_ListCtrl.SetItemText(0,4,"�����V");
		m_ListCtrl.SetItemText(0,5,"���");
		m_ListCtrl.SetItemText(0,6,"��β");

		CString FilePath = GetAppCurrentPath()+_T("\\yaner.csv");
		HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(FileHandle == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox(_T("���ļ�ʧ�ܣ�"));
			return;
		}

		CString WriteCSV="����,��˳ǰ��V, , ,��˳����V, , ,��ǰ��V, , ,�����V, , ,���,��β,��˳ǰ��*3.14,��˳ǰ��*6.18,��˳����V*3.14,��˳����V*6.18,��ǰ��V*3.14,��ǰ��V*6.18,�����V*3.14,�����V*6.18\n";
		for(int Index = 0; Index < (int)DataList->size(); Index++)
		{
			int InsertItemPos=Index+1;
			m_ListCtrl.InsertItem(InsertItemPos,"");

			CString ShunV;
			CString HouV;
			CString QiuV;
			CString QiuHouV;
			CString KuaDu;
			CString HeV;

			int VCount=0;

			CString ShunVCSV;
			CString HouVCSV;
			CString QiuVCSV;
			CString QiuHouVCSV;

			for(int i=0; i < 6; i++)
			{
				int V=(*DataList)[Index].m_HongQiu[i]%10;
				int V2=(*QiuShun)[Index].m_HongQiu[i]%10;
				VCount+=V;

				CString StrV;
				StrV.Format("%d",V);
				CString StrV2;
				StrV2.Format("%d",V2);
				if(i < 3)
				{
					QiuV+=StrV;
					ShunV+=StrV2;
					if(QiuVCSV.IsEmpty())
						QiuVCSV+=StrV;
					else 
						QiuVCSV+=","+StrV;
					if(ShunVCSV.IsEmpty())
						ShunVCSV+=StrV2;
					else
						ShunVCSV+=","+StrV2;
				}
				else
				{
					QiuHouV+=StrV;
					HouV+=StrV2;

					if(QiuHouVCSV.IsEmpty())
						QiuHouVCSV+=StrV;
					else 
						QiuHouVCSV+=","+StrV;
					if(HouVCSV.IsEmpty())
						HouVCSV+=StrV2;
					else
						HouVCSV+=","+StrV2;

				}
			}

			HeV.Format("%d",VCount);
			KuaDu.Format("%d",(*DataList)[Index].m_HongQiu[5]-(*DataList)[Index].m_HongQiu[0]);

			CString TempCSV;
			CString QiShu=(*DataList)[Index].m_QiShu;
			if(QiShu.Find("\n")!=-1)
				QiShu=QiShu.Left(QiShu.Find("\n")-1);
			TempCSV=QiShu+","+ShunVCSV+","+HouVCSV+","+QiuVCSV+","+QiuHouVCSV+","+KuaDu+","+HeV;


			CString Temp=TransData(ShunV,3.14);
			TempCSV+=","+Temp;
			Temp=TransData(ShunV,6.18);
			TempCSV+=","+Temp;

			Temp=TransData(HouV,3.14);
			TempCSV+=","+Temp;

			Temp=TransData(HouV,6.18);
			TempCSV+=","+Temp;

			Temp=TransData(QiuV,3.14);
			TempCSV+=","+Temp;
			
			Temp=TransData(QiuV,6.18);
			TempCSV+=","+Temp;

			
			Temp=TransData(QiuHouV,3.14);
			TempCSV+=","+Temp;
			
			Temp=TransData(QiuHouV,6.18);
			TempCSV+=","+Temp;
			TempCSV+="\n";


			WriteCSV+=TempCSV;
			m_ListCtrl.SetItemText(InsertItemPos,0,(*DataList)[Index].m_QiShu);
			m_ListCtrl.SetItemText(InsertItemPos,1,ShunV);
			m_ListCtrl.SetItemText(InsertItemPos,2,HouV);
			m_ListCtrl.SetItemText(InsertItemPos,3,QiuV);
			m_ListCtrl.SetItemText(InsertItemPos,4,QiuHouV);
			m_ListCtrl.SetItemText(InsertItemPos,5,KuaDu);
			m_ListCtrl.SetItemText(InsertItemPos,6,HeV);
		
		}

		
		DWORD WriteBytes=0;
		::WriteFile(FileHandle,WriteCSV.GetBuffer(),WriteCSV.GetLength(),&WriteBytes,NULL);
		WriteCSV.ReleaseBuffer();
		CloseHandle(FileHandle);
}

void CDlgLianHaoHongQiu::OnBnClickedButton2()
{
m_ListCtrl.DeleteAllItems();
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();


		m_ListCtrl.SetItemText(0,0,"����");
		m_ListCtrl.SetItemText(0,1,"��˳ǰ����");
		m_ListCtrl.SetItemText(0,2,"��˳������");
		m_ListCtrl.SetItemText(0,3,"��ǰ����");
		m_ListCtrl.SetItemText(0,4,"�������");
		m_ListCtrl.SetItemText(0,5,"���");
		m_ListCtrl.SetItemText(0,6,"�ͺ�");

		CString FilePath = GetAppCurrentPath()+_T("\\yaner_he.csv");
		HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(FileHandle == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox(_T("���ļ�ʧ�ܣ�"));
			return;
		}

		CString WriteCSV="����,��˳ǰ����, , ,��˳������, , ,��ǰ����, , ,�������, , ,���,��β,��˳ǰ��*3.14,��˳ǰ��*6.18,��˳������*3.14,��˳������*6.18,��ǰ����*3.14,��ǰ����*6.18,�������*3.14,�������*6.18\n";
		for(int Index = 0; Index < (int)DataList->size(); Index++)
		{
			int InsertItemPos=Index+1;
			m_ListCtrl.InsertItem(InsertItemPos,"");

			CString ShunV;
			CString HouV;
			CString QiuV;
			CString QiuHouV;
			CString KuaDu;
			CString HeV;

			int VCount=0;

			CString ShunVCSV;
			CString HouVCSV;
			CString QiuVCSV;
			CString QiuHouVCSV;

			for(int i=0; i < 6; i++)
			{
				int V=(*DataList)[Index].m_HongQiu[i]%10+(*DataList)[Index].m_HongQiu[i]/10;
				V=V%10;
				int V2=(*QiuShun)[Index].m_HongQiu[i]%10+(*QiuShun)[Index].m_HongQiu[i]/10;
				V2=V2%10;
				VCount+=V;

				CString StrV;
				StrV.Format("%d",V);
				CString StrV2;
				StrV2.Format("%d",V2);
				if(i < 3)
				{
					QiuV+=StrV;
					ShunV+=StrV2;
					if(QiuVCSV.IsEmpty())
						QiuVCSV+=StrV;
					else 
						QiuVCSV+=","+StrV;
					if(ShunVCSV.IsEmpty())
						ShunVCSV+=StrV2;
					else
						ShunVCSV+=","+StrV2;
				}
				else
				{
					QiuHouV+=StrV;
					HouV+=StrV2;

					if(QiuHouVCSV.IsEmpty())
						QiuHouVCSV+=StrV;
					else 
						QiuHouVCSV+=","+StrV;
					if(HouVCSV.IsEmpty())
						HouVCSV+=StrV2;
					else
						HouVCSV+=","+StrV2;

				}
			}

			HeV.Format("%d",VCount);
			KuaDu.Format("%d",(*DataList)[Index].m_HongQiu[5]-(*DataList)[Index].m_HongQiu[0]);

			CString TempCSV;
			CString QiShu=(*DataList)[Index].m_QiShu;
			if(QiShu.Find("\n")!=-1)
				QiShu=QiShu.Left(QiShu.Find("\n")-1);
			TempCSV=QiShu+","+ShunVCSV+","+HouVCSV+","+QiuVCSV+","+QiuHouVCSV+","+KuaDu+","+HeV;

			CString Temp=TransData(ShunV,3.14);
			TempCSV+=","+Temp;
			Temp=TransData(ShunV,6.18);
			TempCSV+=","+Temp;

			Temp=TransData(HouV,3.14);
			TempCSV+=","+Temp;

			Temp=TransData(HouV,6.18);
			TempCSV+=","+Temp;

			Temp=TransData(QiuV,3.14);
			TempCSV+=","+Temp;
			
			Temp=TransData(QiuV,6.18);
			TempCSV+=","+Temp;

			
			Temp=TransData(QiuHouV,3.14);
			TempCSV+=","+Temp;
			
			Temp=TransData(QiuHouV,6.18);
			TempCSV+=","+Temp;
			TempCSV+="\n";



			WriteCSV+=TempCSV;
			m_ListCtrl.SetItemText(InsertItemPos,0,(*DataList)[Index].m_QiShu);
			m_ListCtrl.SetItemText(InsertItemPos,1,ShunV);
			m_ListCtrl.SetItemText(InsertItemPos,2,HouV);
			m_ListCtrl.SetItemText(InsertItemPos,3,QiuV);
			m_ListCtrl.SetItemText(InsertItemPos,4,QiuHouV);
			m_ListCtrl.SetItemText(InsertItemPos,5,KuaDu);
			m_ListCtrl.SetItemText(InsertItemPos,6,HeV);
		
		}

		
		DWORD WriteBytes=0;
		::WriteFile(FileHandle,WriteCSV.GetBuffer(),WriteCSV.GetLength(),&WriteBytes,NULL);
		WriteCSV.ReleaseBuffer();
		CloseHandle(FileHandle);
}
