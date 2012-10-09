// DlgTeZongHeFenXi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgTeZongHeFenXi.h"
#include "FormulaCenter.h"

// CDlgTeZongHeFenXi �Ի���

IMPLEMENT_DYNAMIC(CDlgTeZongHeFenXi, CDialog)

CDlgTeZongHeFenXi::CDlgTeZongHeFenXi(CWnd* pParent /*=NULL*/)
: CDialog(CDlgTeZongHeFenXi::IDD, pParent)
{
	m_IsInitData=false;
}

CDlgTeZongHeFenXi::~CDlgTeZongHeFenXi()
{
}

void CDlgTeZongHeFenXi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgTeZongHeFenXi, CDialog)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()





// ���ɵ���Ϣӳ�亯��
BOOL CDlgTeZongHeFenXi::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgTeZongHeFenXi::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgTeZongHeFenXi::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData=true;
		vector<sFormulaInfo> InfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_LAN);
		m_ListCtrl.DeleteAllItems();
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		int DataSize = DataList->size();
		int Offset=18;

		m_ListCtrl.InsertItem(0,_T(""));
		m_ListCtrl.SetItemText(0,1,_T("������һҳ��"));
		m_ListCtrl.SetItemText(0,2,_T("������һ ��ҳ��"));
		m_ListCtrl.SetItemText(0,3,_T("������һ ��ҳ��"));
		m_ListCtrl.SetItemText(0,4,_T("������һ �� ��ҳ��"));
		m_ListCtrl.SetItemText(0,5,_T("���벻��һ �� ��ҳ��"));
		m_ListCtrl.SetItemText(0,6,_T("�����ڶ�ҳ��"));
		m_ListCtrl.SetItemText(0,7,_T("�����ڶ� ��ҳ��"));
		m_ListCtrl.SetItemText(0,8,_T("��������ҳ��"));

		for(int Index = 0; Index < DataSize; Index++)
		{
			int TeArray1[50];
			int TeArray2[50];
			int TeArray3[50];
			int TeArray4[50];
			memset(TeArray1,0,sizeof(int)*50);
			memset(TeArray2,0,sizeof(int)*50);
			memset(TeArray3,0,sizeof(int)*50);
			memset(TeArray4,0,sizeof(int)*50);

			for(int i = 0 ; i <InfoList.size(); i++)
			{
				if(InfoList[i].m_DataList.empty())
					continue;

				int TempData=atoi(InfoList[i].m_DataList[Index].m_Data.GetBuffer());
				TeArray4[TempData]++;

				if(i < Offset)
				{
					TeArray1[TempData]++;
				}
				else if( i >= Offset && i < 2*Offset)
				{
					TeArray2[TempData]++;

				}
				else
					TeArray3[TempData]++;
			}


			int TempArray[8][50];
			memset(TempArray,0,8*50*sizeof(int));

			for(int j=0; j < 50; j++)
			{
				//����һ����
				if(TeArray1[j] && !TeArray2[j] && !TeArray3[j])
				{
					int TempData = j;
					TempArray[0][TempData]++;
				}

				//����һ ������
				if(TeArray1[j] && TeArray2[j] && !TeArray3[j])
				{
					int TempData = j;
					TempArray[1][TempData]++;
				}

				//����һ ������
				if(TeArray1[j] && !TeArray2[j] && TeArray3[j])
				{
					int TempData = j;
					TempArray[2][TempData]++;
				}

				//����һ �� �� ����
				if(TeArray1[j] && TeArray2[j] && TeArray3[j])
				{
					int TempData = j;
					TempArray[3][TempData]++;
				}

				//�ز�����һ �� �� ����
				if(!TeArray1[j] && !TeArray2[j] && !TeArray3[j])
				{
					int TempData = j;
					TempArray[4][TempData]++;
				}


				//���ڶ�����
				if(TeArray2[j] && !TeArray1[j] && !TeArray3[j])
				{
					int TempData = j;
					TempArray[5][TempData]++;
				}

				//���ڶ� �� ����
				if(TeArray2[j] && !TeArray1[j] && TeArray3[j])
				{
					int TempData = j;
					TempArray[6][TempData]++;
				}

				//������ ����
				if(TeArray2[j] && TeArray1[j] && TeArray3[j])
				{
					int TempData = j;
					TempArray[7][TempData]++;
				}
			}

			m_ListCtrl.InsertItem(Index+1,_T(""));
			CString Text;
			CString TeMa;

			if(Index+1 == DataSize)
				Text=_T("����Ԥ��");
			else
			{
				TeMa.Format("%02d",(*DataList)[Index+1].m_LanQiu);
				Text=(*DataList)[Index+1].m_QiShu +" "+ TeMa;
			}
			m_ListCtrl.SetItemText(Index+1,0,Text);

			CString TongJi;
			int TempTest[50];
			memset(TempTest,0,sizeof(int)*50);

			for(int i=0; i < 8; i++)
			{
				CString Str;
				for(int j=0; j < 50; j++)
				{
					CString Temp;
					if(TempArray[i][j])
					{
						Temp.Format("%02d ",j);
						Str+=Temp;
						TempTest[j]++;

					}
				}

			
				m_ListCtrl.SetItemText(Index+1,i+1,Str);
				if(TeMa.IsEmpty() || Str.Find(TeMa) == -1)
				{
					sItemStyle Style;
					Style.m_ItemType = TEXT_TYPE;
					Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
					Style.m_DrawData.m_TextData.m_TextFont = NULL;
					Style.m_DrawData.m_TextData.m_TextFormat=DT_LEFT |DT_WORDBREAK|DT_EDITCONTROL|DT_EDITCONTROL|DT_CENTER;
					m_ListCtrl.SetItemSpecialStyle(Index+1,i+1,Style);
				}

			}

			for(int i=0; i < 50; i++)
			{
				if(TempTest[i])
				{
					CString ss;
					ss.Format("%02d ",i);
					TongJi+=ss;
				}

			}

			m_ListCtrl.SetItemText(Index+1,9,TongJi);
			if(TeMa.IsEmpty() || TongJi.Find(TeMa) == -1)
			{
				sItemStyle Style;
				Style.m_ItemType = TEXT_TYPE;
				Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
				Style.m_DrawData.m_TextData.m_TextFont = NULL;
				Style.m_DrawData.m_TextData.m_TextFormat=DT_LEFT |DT_WORDBREAK|DT_EDITCONTROL|DT_EDITCONTROL|DT_CENTER;
				m_ListCtrl.SetItemSpecialStyle(Index+1,9,Style);
			}
		}	
	}
}



//��ʼ���б�ͷ
void CDlgTeZongHeFenXi::InitListHeader()
{
	CRect Rect;
	//��ʼ��Ӧ�ó����б�ؼ�
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/12;

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_LEFT |DT_WORDBREAK|DT_EDITCONTROL|DT_EDITCONTROL|DT_CENTER;;

	m_ListCtrl.InsertColumn(0,_TEXT("�ں�"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	int QingCount=9;

	for(int Index = 1; Index < QingCount; Index++)
	{
		CString Text;
		Text.Format("���_%d",Index);
		m_ListCtrl.InsertColumn(Index,Text,    LVCFMT_CENTER,	nWidth);
	}

	m_ListCtrl.InsertColumn(QingCount+1,"�ۺ�",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(QingCount+2,"ͳ��",    LVCFMT_CENTER,	nWidth);

	m_ListCtrl.SetRowHeight(100);

	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);
	m_ListCtrl.SetItemBkData(ItemBkData);
}