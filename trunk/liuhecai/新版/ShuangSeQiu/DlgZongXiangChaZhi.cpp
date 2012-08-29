// DlgZongXiangChaZhi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgZongXiangChaZhi.h"

CString GetAppCurrentPath4()
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


// CDlgZongXiangChaZhi �Ի���

IMPLEMENT_DYNAMIC(CDlgZongXiangChaZhi, CDialog)

CDlgZongXiangChaZhi::CDlgZongXiangChaZhi(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZongXiangChaZhi::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgZongXiangChaZhi::~CDlgZongXiangChaZhi()
{
}

void CDlgZongXiangChaZhi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgZongXiangChaZhi, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()

END_MESSAGE_MAP()


// CDlgZongXiangChaZhi ��Ϣ�������
//��ʼ���б�ͷ
void CDlgZongXiangChaZhi::InitListHeader()
{
	CRect Rect;
	//��ʼ��Ӧ�ó����б�ؼ�
	
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/10;
	m_ListCtrl.InsertColumn(0,_TEXT("����"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.InsertColumn(1,_TEXT("��ɱ����"),	LVCFMT_CENTER,	7*nWidth);
	m_ListCtrl.InsertColumn(2,_TEXT("��ɱͳ��"),	LVCFMT_CENTER,	2*nWidth);
}

void CDlgZongXiangChaZhi::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData = true;
	    m_ListCtrl.DeleteAllItems();
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();
		int Sum[6];
		memset(Sum,0,sizeof(int)*6);

		
		CString FilePath = GetAppCurrentPath4()+_T("\\shahao2.txt");
		HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

		for(int Index = 1; Index < (int)DataList->size()+1; Index++)
		{
			int ShaArray[QIU_COUNT+1];
	    	memset(ShaArray,0,sizeof(int)*(QIU_COUNT+1));
			m_ListCtrl.InsertItem(Index,"");
			if(Index == DataList->size())
			{
				m_ListCtrl.SetItemText(Index,0,"Ԥ��");
			}
			else
			{
				CString Str;
				Str.Format("%s ����=%02d",(*DataList)[Index].m_QiShu,(*DataList)[Index].m_LanQiu);
				/*for(int i =0; i < 6; i++)
				{
					CString Temp;
					Temp.Format("%02d ",(*DataList)[Index].m_HongQiu[i]);
					Str+=Temp;
				}

				CString TempLan;
				TempLan.Format("+%02d",(*DataList)[Index].m_LanQiu);
				Str+=TempLan;
				*/

				m_ListCtrl.SetItemText(Index,0,Str);

			}

	
			CString ShaHongList;
			int TempData =0;
			CString ShaHong;

			
			//������˳��ɱ�ŷ�
		//	if( ShunXuDataList->size() == DataList->size())
		{
				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[1]-(*ShunXuDataList)[Index-1].m_HongQiu[2]);
				if(TempData > QIU_COUNT)
					TempData = TempData%QIU_COUNT;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[2]-(*ShunXuDataList)[Index-1].m_HongQiu[4]);
				if(TempData > QIU_COUNT)
					TempData = TempData%QIU_COUNT;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;


				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[5]) +(*ShunXuDataList)[Index-1].m_LanQiu-3;
				if(TempData > QIU_COUNT)
					TempData = TempData%QIU_COUNT;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[2]) +(*ShunXuDataList)[Index-1].m_LanQiu+2;
				if(TempData > QIU_COUNT)
					TempData = TempData%QIU_COUNT;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				
				TempData = (*ShunXuDataList)[Index-1].m_HongQiu[0]+(*ShunXuDataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] +(*ShunXuDataList)[Index-1].m_LanQiu-1;
				if(TempData > QIU_COUNT)
					TempData = TempData%QIU_COUNT;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;


			}

			//��ACֵɱ��
			TempData = CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+ CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			
			TempData =0;
			for(int i=0; i < 6; i++)
				TempData+=(*DataList)[Index-1].m_HongQiu[i]%10;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData += (*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData*CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =abs(TempData - (*DataList)[Index-1].m_HongQiu[5]);
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1])+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =TempData + (*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =(*DataList)[Index-1].m_HongQiu[4] +(*DataList)[Index-1].m_HongQiu[5]; 
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =(*DataList)[Index-1].m_HongQiu[2] +(*DataList)[Index-1].m_HongQiu[5]; 
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			for(int i=0; i < 6; i++)
			{
				float TempF = (float)(*DataList)[Index-1].m_HongQiu[i];
				TempF=TempF*0.88;
				TempData =(int)TempF;
				if(TempData > QIU_COUNT)
					TempData = TempData%QIU_COUNT;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;
			}

			TempData =abs((*DataList)[Index-1].m_LanQiu+16-(*DataList)[Index-1].m_HongQiu[0]);
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			//���ڿ���˳��h2+�����ڴ�С����H3-2
			TempData =(*DataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] -2;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			//���ڿ���˳��h2+�����ڴ�С����H2-2
			if(Index > 1)
			{
				TempData =(*DataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-2].m_HongQiu[1] -2;
				if(TempData > QIU_COUNT)
					TempData = TempData%QIU_COUNT;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				TempData =(*DataList)[Index-1].m_HongQiu[3]-(*DataList)[Index-1].m_HongQiu[1];
				if(TempData > QIU_COUNT)
					TempData = TempData%QIU_COUNT;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;
			}


			TempData =(*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =(*DataList)[Index-1].m_HongQiu[3]+(*DataList)[Index-1].m_HongQiu[4]-(*DataList)[Index-1].m_HongQiu[1];
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[1])*4;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			m_ListCtrl.SetItemText(Index,1,ShaHongList);


			CString ErrorStr;

			CString LuShuStr0 ="·��0��\r\n";
			CString LuShuStr1 ="·��1��\r\n";
			CString LuShuStr2 ="·��2��\r\n";
		
			if(FileHandle!= INVALID_HANDLE_VALUE)
			{
				int ShaCount=0;
				int ErrorCount=0;
				CString TempStr;
				for(int i=1; i < QIU_COUNT+1;i++)
				{
					if(ShaArray[i])
					{
						CString Temp;
						Temp.Format("%02d ",i);
						TempStr+=Temp;
						ShaCount++;

						switch(i%3)
						{
						case 0:
							LuShuStr0 +=Temp;
							break;
						case 1:
							LuShuStr1 +=Temp;
							break;
						case 2:
							LuShuStr2 +=Temp;
							break;
						}
						
						if(Index != DataList->size())
						{
							if((*DataList)[Index].m_LanQiu == i)
							{
								ErrorCount=ShaArray[i];
							}
						}
					}

				}

				if(Index != DataList->size())
				{
					CString Temp;
					Temp.Format("  ɱ�Ÿ���:%02d,�������:%02d\r\n",ShaCount,ErrorCount);
					ErrorStr.Format("ɱ:%02d,��:%02d",ShaCount,ErrorCount);
					TempStr=(*DataList)[Index].m_QiShu+Temp+TempStr+"\r\n";
				}
				else
				{
					CString Temp;
					Temp.Format("  ɱ�Ÿ���:%02d\r\n",ShaCount);
					TempStr="����ɱ��"+Temp+TempStr+"\r\n";

					ErrorStr.Format("ɱ:%02d",ShaCount);
				}


				
				LuShuStr0 +="\r\n";
				LuShuStr1 +="\r\n";
				LuShuStr2 +="\r\n";

				m_ListCtrl.SetItemText(Index,2,ErrorStr);

				DWORD WriteBytes=0;
				::WriteFile(FileHandle,TempStr.GetBuffer(),TempStr.GetLength(),&WriteBytes,NULL);
				::WriteFile(FileHandle,LuShuStr0.GetBuffer(),LuShuStr0.GetLength(),&WriteBytes,NULL);
				::WriteFile(FileHandle,LuShuStr1.GetBuffer(),LuShuStr1.GetLength(),&WriteBytes,NULL);
				::WriteFile(FileHandle,LuShuStr2.GetBuffer(),LuShuStr2.GetLength(),&WriteBytes,NULL);
			}
		}

		if(FileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(FileHandle);
			//ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);
		}

	}
	

}

// ���ɵ���Ϣӳ�亯��
BOOL CDlgZongXiangChaZhi::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgZongXiangChaZhi::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgZongXiangChaZhi::OnBnClickedSearchBtn()
{
	/*CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	DWORD Data=::atoi(Text.GetBuffer());
	m_ListCtrl.DeleteAllItems();
	vector<sZongXiangChaZhi>* DataList = NULL;
	vector<sZongXiangChaZhi> Temp;
	if(Data == 0)
	{
		DataList=CDataManageCenter::GetInstance()->GetZongXiangChaZhi();
	}
	else
	{
		Temp=CDataManageCenter::GetInstance()->SearchZongXiangChaZhi(Data);
		DataList=&Temp;
	}

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl.InsertItem(Index,"");
		m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
		for(int HongQiu=0; HongQiu < 6; HongQiu++)
		{
			CString Temp;
			Temp.Format("%d",(*DataList)[Index].m_HongQiuChaZhi[HongQiu]);
			m_ListCtrl.SetItemText(Index,HongQiu+1,Temp);
		}

		CString LanQiu;
		LanQiu.Format("%d",(*DataList)[Index].m_LanQiuChaZhi);
		m_ListCtrl.SetItemText(Index,7,LanQiu);
	}*/
}
