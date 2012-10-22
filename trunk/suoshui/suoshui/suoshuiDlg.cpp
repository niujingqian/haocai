// suoshuiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "suoshui.h"
#include "suoshuiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//��ȡģ��·��
CString GetAppCurrentPath()
{
	CString server_ip;
	CString StrDes=_T("");
	::GetModuleFileName(NULL,StrDes.GetBuffer(MAX_PATH),MAX_PATH); 
	StrDes.ReleaseBuffer();
	StrDes=StrDes.Left(StrDes.ReverseFind('\\'));
	if(StrDes.Right(1)!='\\')
		StrDes+="\\";

	return StrDes;
}


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CsuoshuiDlg �Ի���




CsuoshuiDlg::CsuoshuiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CsuoshuiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsuoshuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CsuoshuiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CsuoshuiDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CsuoshuiDlg ��Ϣ�������

BOOL CsuoshuiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CsuoshuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CsuoshuiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CsuoshuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CsuoshuiDlg::OnBnClickedOk()
{
	CString FilePath=GetAppCurrentPath()+"tiaojian.txt";
	DWORD Flag = OPEN_EXISTING;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return ;
	DWORD Size = ::GetFileSize(FileHandle,NULL);
	char* Buffer = new char[Size+1];
	memset(Buffer,'\0',Size+1);
	DWORD ReadBytes=0;
	::ReadFile(FileHandle,Buffer,Size,&ReadBytes,NULL);
	CString StrData=CString(Buffer);
	map<CString,vector<int>> MapData;
	ParseData(StrData,MapData);
	Combine(MapData);
	delete []Buffer;
	CloseHandle(FileHandle);

}


//��������
void CsuoshuiDlg::ParseData(CString& StrData,map<CString,vector<int>>& MapData)
{
	int StartPos=0;
	int EndPos=0;
	while(EndPos != -1)
	{
		EndPos=StrData.Find(";",StartPos);
		if(EndPos == -1)
			break;

		CString Temp=StrData.Mid(StartPos,EndPos-StartPos);
		StartPos = EndPos+1;
		
		int Pos=Temp.Find("=");
		if(Pos == -1)
			continue;

		CString Name = Temp.Left(Pos);
		if(Name.Find("\r\n") != -1)
			Name=Name.Mid(Name.Find("\r\n")+2);
		Name=Name.Trim();
		Temp=Temp.Mid(Pos+1);
		if(!Temp.IsEmpty())
		{
			vector<int> Data=this->GetDataList(Temp);
			MapData[Name]=Data;
		}
		
	}


	for(int i = 0; i < MapData["����"].size(); i++)
	{
		for(int Index = 0 ; Index < MapData["����"].size(); Index++)
		{
			if(MapData["����"][i] < MapData["����"][Index])
			{
				int Temp1 = MapData["����"][Index];
				MapData["����"][Index]=MapData["����"][i];
				MapData["����"][i] = Temp1;
			}	
		}
	}
}

//�������
void CsuoshuiDlg::Combine(map<CString,vector<int>> MapData)
{
	int n=0,m=0;

	n=MapData["����"].size();
	m=MapData["��ѡ"][0];
	m = m > n ? n : m;

	int* order = new int[m+1];    
	for(int i=0; i<=m; i++)
	  order[i] = i-1;            // ע������order[0]=-1������Ϊѭ���жϱ�ʶ
	 

	 CString WriteStr;
	 int count = 0;   
	 int AllCount=0;
	 int k = m;
	 bool flag = true;           // ��־�ҵ�һ����Ч���
	 while(order[0] == -1)
	 {
		  if(flag)                   // �������Ҫ������
		  {   
			  flag = false;
			  CString OutStr;

			  map<CString,vector<int>>::iterator it=MapData.begin();

			  int WantCount=0;
			  int RealWantCount=0;
			  for(; it != MapData.end(); it++)
			  {
				  if(it->first == "��ͷ")
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[1]];
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData == it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first == "��β")
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[m]];
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData == it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;
					  continue;
				  }

				  if(it->first == "��V��")
				  {
					  WantCount++;
					  bool IsWant=false;
					  for(int i=1; i<=m; i++)      
					  {
						  int TempData=MapData["����"][order[i]]%10;
						  for(int j=0; j < it->second.size();j++)
						  {
							  if(TempData == it->second[j])
							  {
								  IsWant=true;
								  break;
							  }
						  }

						  if(IsWant)
							  break;
					  }

					  if(IsWant)
						RealWantCount++;
					  continue;
				  }

				  if(it->first == "��V��")
				  {
					  WantCount++;
					  int Array[10];
					  memset(Array,0,sizeof(int)*10);
					  for(int i=1; i<=m; i++)      
					  {
						  int TempData=MapData["����"][order[i]]%10;
						  for(int j=0; j < it->second.size();j++)
						  {
							  if(TempData == it->second[j])
							  {
								  Array[TempData]++;
								 break;
							  }
						  }
					  }

					  int QieCount=0;
					  for(int f=0; f < 10; f++)
					  {
						  if(Array[f])
							  QieCount++;
					  }
					  if(QieCount >= it->second.size() )
						RealWantCount++;
					  continue;
				  }


				  if(it->first == "����")
				  {
					  WantCount++;
					  int QieCount=0;
					  for(int i=1; i<=m; i++)      
					  {
						  int TempData=MapData["����"][order[i]];
						  for(int j=0; j < it->second.size();j++)
						  {
							  if(TempData == it->second[j])
							  {
								 QieCount++;
								 break;
							  }
						  }
					  }

					  if(QieCount >= it->second.size() )
						RealWantCount++;
					  continue;
				  }
				  
				  if(it->first.Find("ɱ��") != -1)
				  {
					  WantCount++;
					  int QieCount=0;
					  for(int i=1; i<=m; i++)      
					  {
						  int TempData=MapData["����"][order[i]];
						  for(int j=0; j < it->second.size();j++)
						  {
							  if(TempData == it->second[j])
							  {
								 QieCount++;
								 break;
							  }
						  }
					  }

					  if(QieCount < it->second.size() )
						RealWantCount++;
					  continue;
				  }


				  if(it->first.Find("��һ����") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[1]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("��һС��") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[1]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				    if(it->first.Find("�������") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[2]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("���С��") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[2]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }



				    if(it->first.Find("��������") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[3]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("����С��") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[3]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }



				    if(it->first.Find("���Ĵ���") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[4]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("����С��") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[4]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }



				    if(it->first.Find("�������") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[5]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("����С��") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[5]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }



				    if(it->first.Find("��������") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[6]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("����С��") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["����"][order[6]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }






			  }

			  if(RealWantCount == WantCount)
			  {
					for(int i=1; i<=m; i++)      
					{
						int TempData=MapData["����"][order[i]];	
						CString Temp;
						Temp.Format("%02d ",TempData);
						OutStr+=Temp;
					}

				   OutStr+="\r\n";
				   WriteStr+=OutStr;
				   count++;
			  }

			  AllCount++;
			 
		  }

		  order[k]++;                // �ڵ�ǰλ��ѡ���µ�����
		  if(order[k] == n)          // ��ǰλ���������ֿ�ѡ������
		  {
		   order[k--] = 0;
		   continue;
		  }     
		  
		  if(k < m)                  // ���µ�ǰλ�õ���һλ�õ�����          
		  {
		   order[++k] = order[k-1];
		   continue;
		  }
		  
		  if(k == m)
		   flag = true;
	 }

	 delete[] order;

	 CString Header;
	 Header.Format("��ע����%02d ��ˮ��%02d\r\n",AllCount,count);
	 WriteStr=Header+WriteStr;


	 CString FilePath = GetAppCurrentPath()+_T("\\suoshui.txt");
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("���ļ�ʧ�ܣ�"));
		return;
	}
		
	DWORD WriteBytes=0;
	::WriteFile(FileHandle,WriteStr.GetBuffer(),WriteStr.GetLength(),&WriteBytes,NULL);
	CloseHandle(FileHandle);
	ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);

}

//��ȡ����
vector<int> CsuoshuiDlg::GetDataList(CString& StrData)
{
	int StartPos = 0;
	int EndPos   = 0;
	int Index = 0;
	int Count=0;
	vector<int> DataList;

	while(EndPos != -1)
	{
		EndPos=StrData.Find(_T(" "),StartPos);
		if(EndPos == -1)
			break;

		CString Temp = StrData.Mid(StartPos,EndPos-StartPos);
		int TempData = atoi(Temp.GetBuffer());
		Temp.ReleaseBuffer();
		if(TempData != 0)
			DataList.push_back(TempData);
		StartPos = EndPos+1;
	}

	return DataList;
}

