// ShiFaDingHong.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgShiFaDingHong.h"


// CShiFaDingHong �Ի���

IMPLEMENT_DYNAMIC(CDlgShiFaDingHong, CDialog)

CDlgShiFaDingHong::CDlgShiFaDingHong(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShiFaDingHong::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgShiFaDingHong::~CDlgShiFaDingHong()
{
}

void CDlgShiFaDingHong::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgShiFaDingHong, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


//��ʼ���б�ͷ
void CDlgShiFaDingHong::InitListHeader()
{
	CRect Rect;
	//��ʼ��Ӧ�ó����б�ؼ�
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/15;
	m_ListCtrl.InsertColumn(0,_TEXT("������"),  LVCFMT_CENTER,	nWidth);
	for(int Index = 1; Index <= 13; Index++)
	{
		CString Str;
		Str.Format("ɱ����%02d",Index);
		m_ListCtrl.InsertColumn(Index,Str,	LVCFMT_CENTER,	nWidth); 
	}

	m_ListCtrl.InsertColumn(14,_TEXT("ͳ��ɱV"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(15,_TEXT("ͳ�ƴ���"),	LVCFMT_CENTER,	nWidth);

}

/*
����1��[��19�����ں�ֵ��β��+-1]        
              ���磺19-4=15��λ14 15 16�� 14
����2�������ڵ����������ڵ����š�
               ���磺��46-10=3  6��βȫ�� 26  QIU_COUNT
����3����Ģ���Ķ�����ʽ��С˳�򣺺�5λ*5��ǰ���ȡһ�루����33��33��
               ���磺31*5=155-99=23��λ22 23 24�� 22
����4���ͺϵ�λ��ʽ������6���ֵ�������Ǻ��λ������114=6��λ05 06 07���ڳ� 07
����5�����ϺͿ�������ڶ��������й�ϵ�����ϼӼ��ڶ��죨��С�򣩴󲿷ֳ������룬��ʱֱ�������ɱȽ����ԣ��� 
               ���գ���Ԥ�⵨���кô������磺�ڶ���08�����32-07=25����7+8=15��λ14 15 16 ���ڳ� 14
����6�����ں�1λ�������ں����ľ���ֵ����1�ǵ�λһ�㻯!
               ���磺146�ں�1λ+-144�ں�1λ07+02=9��λ08 09 10���ڳ� 08
����7���������³�����������5λ-��1λ+-�̶�2=��λ���ڳ����룡�����ã�
               ���磺32-07+2=27��λ26 27 28�� 26         32-07-2=23��λ22 23 24�� 22
����8����ʽ:���ţ�����������16�ͼ�33��������ȡ��������---������! 
               ����10����=40-33=7��λ06 07 08���ڳ� 07  08
����9����β+����λβ=��β�����ڽ�β----�����ã�
               ����0+8=8β��ȷ�� 08
����10�����ڵ����죭����죡 ����ȡ��λ�� ɱ����β
                ����126�� 31��26��05  127��ɱ5β  ��ȷ
                     127�� 28��24��04  128��ɱ4β  ��ȷ
                     128�� 31��27��04  129��ɱ4β  ��ȷ
*/

void CDlgShiFaDingHong::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData=true;

		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		for(int Index = 1; Index <= DataList->size(); Index++)
		{
			m_ListCtrl.InsertItem(Index,"");
			
			int ShaV[100];
			int Count=0;
			int ErrorCount=0;

			memset(ShaV,0,sizeof(int)*10);

			if(Index !=  DataList->size())
			{
			CString Str;
			Str.Format("%s ����=%02d",(*DataList)[Index].m_QiShu,(*DataList)[Index].m_LanQiu);
			m_ListCtrl.SetItemText(Index,0,Str);
			}
		/*	for(int i =0; i < QIU_XUN; i++)
			{
				CString Temp;
				Temp.Format("%02d ",(*DataList)[Index].m_HongQiu[i]);
				Str+=Temp;
			}

			CString TempLan;
			TempLan.Format("+%02d",(*DataList)[Index].m_LanQiu);
			Str+=TempLan;
			m_ListCtrl.SetItemText(Index,0,Str);
			}*/

/*
			int DingHong1 = 19-(*DataList)[Index-1].m_HongQiuSum % 10;
			CString StrDing1;
			StrDing1.Format("%02d %02d %02d",DingHong1-1,DingHong1,DingHong1+1);
			m_ListCtrl.SetItemText(Index,1, StrDing1);
			
*/
			CString ShaTeV;

			CString StrDing;
			if(Index > 1)
			{
	    		int Data = atoi((*DataList)[Index-2].m_QiShu)-2012000;

				Data = abs(Data - (*DataList)[Index-1].m_LanQiu);
				bool IsTrue=false;
				int Temp = Data/10;
				Temp=Temp%10;
				
				IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			   ShaTeV+="ɱ "+CDataManageCenter::GetDataStr(Temp,IsTrue,true)+" ";
				//m_ListCtrl.SetItemText(Index,1, StrDing2);
				StrDing2.Empty();
				ShaV[Temp]++;
				Count++;
				if(!IsTrue)
					ErrorCount++;

				Temp = Data%10;
		    	IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			    ShaTeV++="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true)+" ";
			//	m_ListCtrl.SetItemText(Index,2, StrDing2);
				ShaV[Temp]++;
				Count++;
				if(!IsTrue)
					ErrorCount++;

				
			}
			
			
			int Temp=0;
			bool IsTrue=false;
			
			CString StrDing8;
			int DingHong8 = (*DataList)[Index-1].m_LanQiu%10 +(*DataList)[Index-1].m_HongQiu[2]%10;
			//StrDing8.Format("%dV",DingHong8);
			Temp = DingHong8%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			 ShaTeV+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true)+" ";

		   // m_ListCtrl.SetItemText(Index,3, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;


			CString StrDing9;
			int DingHong9 = (*DataList)[Index-1].m_HongQiu[5] - (*DataList)[Index-1].m_HongQiu[4];
			Temp = DingHong9%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			ShaTeV+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true)+" ";
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;

		    m_ListCtrl.SetItemText(Index,4, StrDing9);
			if( Index >= 2)
			{
				Temp = 	abs((*DataList)[Index-1].m_LanQiu - (*DataList)[Index-2].m_LanQiu);
				Temp = Temp%10;
				IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
				StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
				m_ListCtrl.SetItemText(Index,5, StrDing8);
				StrDing8.Empty();
				ShaV[Temp]++;
				Count++;
				if(!IsTrue)
					ErrorCount++;
			}

			
			Temp = (*DataList)[Index-1].m_HongQiu[1]%10+1;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
			m_ListCtrl.SetItemText(Index,6, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;

			Temp = (*DataList)[Index-1].m_LanQiu%10*2;
			Temp =Temp%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
			m_ListCtrl.SetItemText(Index,7, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;

			int MinData = (*DataList)[Index-1].m_HongQiu[0];
			int MaxData = (*DataList)[Index-1].m_HongQiu[5];
			if(MinData > (*DataList)[Index-1].m_LanQiu)
				MinData = (*DataList)[Index-1].m_LanQiu;

			if(MaxData < (*DataList)[Index-1].m_LanQiu)
				MaxData = (*DataList)[Index-1].m_LanQiu;

			Temp = MaxData +(*DataList)[Index-1].m_HongQiu[4];
			Temp =Temp%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
			m_ListCtrl.SetItemText(Index,8, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;

			Temp = (*DataList)[Index-1].m_LanQiu + (*DataList)[Index-1].m_HongQiu[2];
			Temp =Temp%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
			m_ListCtrl.SetItemText(Index,9, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;


			Temp = abs((*DataList)[Index-1].m_LanQiu - (*DataList)[Index-1].m_HongQiu[5]);
			Temp =Temp%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
			m_ListCtrl.SetItemText(Index,9, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;

			Temp = (*DataList)[Index-1].m_HongQiu[5]/10+(*DataList)[Index-1].m_HongQiu[5]%10 +(*DataList)[Index-1].m_HongQiu[4]/10+(*DataList)[Index-1].m_HongQiu[4]%10;
			Temp =Temp%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
			m_ListCtrl.SetItemText(Index,10, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;

			Temp = (*DataList)[Index-1].m_HongQiu[0]/10+(*DataList)[Index-1].m_HongQiu[0]%10 +(*DataList)[Index-1].m_HongQiu[1]/10+(*DataList)[Index-1].m_HongQiu[1]%10;
			Temp =Temp%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
			m_ListCtrl.SetItemText(Index,11, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;

			Temp = atoi((*DataList)[Index-1].m_QiShu.GetBuffer());
			Temp =Temp%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
			m_ListCtrl.SetItemText(Index,12, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;

			Temp = atoi((*DataList)[Index-1].m_QiShu.GetBuffer());
			Temp =Temp%100+Temp%10;
			Temp=Temp%10;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
			m_ListCtrl.SetItemText(Index,13, StrDing8);
			StrDing8.Empty();
			ShaV[Temp]++;
			Count++;
			if(!IsTrue)
				ErrorCount++;

		   
			for(int i=0; i < 10; i++)
			{
				CString TempStr;
				if(ShaV[i])
				{
					TempStr.Format("%d",i);
					StrDing8+=TempStr;
				}
			}

			StrDing8="ɱ"+StrDing8+"V";
			m_ListCtrl.SetItemText(Index,14, StrDing8);
			StrDing8.Empty();

			StrDing8.Format("ɱ:%02d ��:%02d",Count,ErrorCount);
			m_ListCtrl.SetItemText(Index,15, StrDing8);
			StrDing8.Empty();


	/*		if(Index > 2)
			{
				Temp = (*DataList)[Index-2].m_LanQiu%10 +(*DataList)[Index-2].m_LanQiu/10;
				Temp =Temp%10;
				IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
				StrDing8+="ɱ"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
				m_ListCtrl.SetItemText(Index,8, StrDing8);
				StrDing8.Empty();
			}*/


	/*		CString StrDing3;
		    int DingHong3 = (*DataList)[Index-1].m_HongQiu[4]*5;
			DingHong3 = DingHong3%QIU_COUNT;
			StrDing3.Format("%02d %02d %02d",DingHong3-1,DingHong3,DingHong3+1);
			m_ListCtrl.SetItemText(Index,3, StrDing3);

			CString StrDing4;
			int DingHong4 = (*DataList)[Index-1].m_HongQiuSum/100 + ((*DataList)[Index-1].m_HongQiuSum/10)%10 +(*DataList)[Index-1].m_HongQiuSum%10;
			StrDing4.Format("%02d %02d %02d",DingHong4-1,DingHong4,DingHong4+1);
			m_ListCtrl.SetItemText(Index,4, StrDing4);*/

		/*	CString StrDing5;
			int DingHong5 = (*DataList)[Index-1].m_HongQiu[0];
			if(Index > 2)
			{
				DingHong5 =abs(DingHong5-(*DataList)[Index-2].m_HongQiu[0]);
			    StrDing5.Format("%02d %02d %02d",DingHong5-1,DingHong5,DingHong5+1);
			    m_ListCtrl.SetItemText(Index,5, StrDing5);
			}*/

			
			//int DingHong6=(*DataList)[Index-1].m_HongQiuSum;// + CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			//int HeSum=0;
			//int WeiSum=0;
			//for(int i = 0; i < QIU_XUN; i++)
			//{
			//	WeiSum=HeSum+(*DataList)[Index-1].m_HongQiu[i]%10;
			//	if(CDataManageCenter::IsHeShuData((*DataList)[Index-1].m_HongQiu[i]))
			//		HeSum+=(*DataList)[Index-1].m_HongQiu[i];

			//}

			//CString StrDing6;
			//DingHong6 +=WeiSum;
			//int QuYu = DingHong6%QIU_COUNT;
			//int QuShang = DingHong6/QIU_COUNT;
			//int Temp = abs(QuYu-QuShang);

			//bool IsTrue = Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp);
			//StrDing6+=CDataManageCenter::GetDataStr(Temp,IsTrue);

		 //   Temp = QuYu+QuShang;
			//IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp);
			//StrDing6+=" "+CDataManageCenter::GetDataStr(Temp,IsTrue);
		 //   m_ListCtrl.SetItemText(Index,6, StrDing6);


			//CString StrDing7;
			//int DingHong7=(*DataList)[Index-1].m_HongQiuSum;
			//DingHong7 +=HeSum;
			//QuYu = DingHong7%QIU_COUNT;
			//QuShang = DingHong7/QIU_COUNT;
			//Temp = abs(QuYu-QuShang);

			//IsTrue = Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp);
			//StrDing7+=CDataManageCenter::GetDataStr(Temp,IsTrue);

		 //   Temp = QuYu+QuShang;
			//if(Temp > QIU_COUNT)
			//	Temp-=QIU_COUNT;

			//IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp);
			//StrDing7+=" "+CDataManageCenter::GetDataStr(Temp,IsTrue);
		 //   m_ListCtrl.SetItemText(Index,7, StrDing7);

		//	StrDing6.Format("%02d %02d",,QuYu+QuShang);
		 
		/*	CString StrDing6;
			int DingHong6 = (*DataList)[Index-1].m_HongQiu[4]-(*DataList)[Index-1].m_HongQiu[1];
			int Temp=DingHong6+2;
			int Temp2=DingHong6-2;
			StrDing6.Format("+2=%02d %02d %02d;-2=%02d %02d %02d",Temp-1,Temp,Temp+1,Temp2-1,Temp2,Temp2+1);
		    m_ListCtrl.SetItemText(Index,6, StrDing6);

			*/
		/*	CString StrDing7;
			int DingHong7 = (*DataList)[Index-1].m_LanQiu*4;
			if(DingHong7 > QIU_COUNT)
				DingHong7 = DingHong7%QIU_COUNT;
			StrDing7.Format("%02d %02d %02d",DingHong7-1,DingHong7,DingHong7+1);
		    m_ListCtrl.SetItemText(Index,7, StrDing7);*/



		}

		/*for(int Index = 0; Index < (int)DataList->size(); Index++)
		{
		
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
		}

		if(!DataList->empty())
			m_IsInitData = true;
			*/
}

}

// ���ɵ���Ϣӳ�亯��
BOOL CDlgShiFaDingHong::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgShiFaDingHong::OnClose()
{
	ShowWindow(SW_HIDE);
}