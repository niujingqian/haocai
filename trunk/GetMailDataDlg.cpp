
// GetMailDataDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GetMailData.h"
#include "GetMailDataDlg.h"

#include <afxinet.h>
#include <afxwin.h>
#include <atlrx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_PARSE_OVER_MSG WM_USER+1         //�������
#define WM_PARSE_GOING_MSG WM_USER+2        //������

//��ȡģ��·��
CString GetAppCurrentPath()
{
	CString server_ip;
	CString StrDes=_T("");
	::GetModuleFileName(NULL,StrDes.GetBuffer(MAX_PATH),MAX_PATH); 
	//::GetCurrentDirectory(MAX_PATH,StrDes.GetBuffer(MAX_PATH));
	StrDes.ReleaseBuffer();
	StrDes=StrDes.Left(StrDes.ReverseFind('\\'));
	if(StrDes.Right(1)!='\\')
		StrDes+=_T("\\");

	return StrDes;
}

extern char* UnicodeToUTF8(wchar_t* unicode);


wchar_t* ConvertToUnicodeFromUtf8(char *utf8)
{
	DWORD wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, utf8, -1, NULL, 0);
	wchar_t* unicode = new wchar_t[wcsLen];
	::MultiByteToWideChar(CP_ACP, NULL, utf8, -1, unicode, wcsLen);
	return unicode;
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


// CGetMailDataDlg �Ի���


//�̲߳���
struct sThreadParam
{
	HWND             m_hWnd;         //���ھ��
	vector<CString>  m_RequestUrl;   //����Url
	HANDLE           m_StopEvent;    //ֹͣ�¼�
	int              m_ParseType;    //��������
};

CGetMailDataDlg::CGetMailDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetMailDataDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_HtmlCtrl=NULL;
	m_StopEvent=::CreateEvent(NULL,true,false,_T(""));
	m_ThreadHandle = INVALID_HANDLE_VALUE;
}

void CGetMailDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl);
}

BEGIN_MESSAGE_MAP(CGetMailDataDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_PARSE_OVER_MSG,&CGetMailDataDlg::OnParseOverMsg)
	ON_MESSAGE(WM_PARSE_GOING_MSG,&CGetMailDataDlg::OnParseGoingMsg)
	ON_MESSAGE(WM_HTML_DOC_MSG,&CGetMailDataDlg::OnStartParseMsg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CGetMailDataDlg::OnBnClickedSearchBtn)

	ON_BN_CLICKED(IDC_STOP_BTN, &CGetMailDataDlg::OnBnClickedStopBtn)
END_MESSAGE_MAP()


// CGetMailDataDlg ��Ϣ�������

BOOL CGetMailDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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


	//������HTML�ؼ�
	CreateNewHtmlCtrl(_T("http://www.baidu.com"),_T(""));
	GetDlgItem(IDC_TEST_STATIC)->SetWindowText(_T("׼��"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGetMailDataDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetMailDataDlg::OnPaint()
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
HCURSOR CGetMailDataDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGetMailDataDlg::OnBnClickedSearchBtn()
{
	CString Url;//=_T("http://www.google.com.hk/search?q=");
	CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	if(Text.IsEmpty())
	{
		AfxMessageBox(_T("����������!"));
		return;
	}

	//Url.Format(" http://www.google.com.hk/search?hl=zh-CN&newwindow=1&safe=strict&q="+Text+"&start=����ҳ�ű���&sa=N");

	//Url= _T("http://www.google.com.hk/search?hl=zh-CN&newwindow=1&safe=strict&q=")+Text+_T("&sa=N");
	Url=_T("http://www.baidu.com/s?wd=")+Text;
	//Url+=Text;
	
	sThreadParam* Param = new sThreadParam();
	Param->m_hWnd = this->GetSafeHwnd();
	Param->m_RequestUrl.push_back(Url);
	Param->m_StopEvent=m_StopEvent;
	Param->m_ParseType = 0;
	//= Url;

	this->m_ProgressCtrl.SetPos(0);
	::ResetEvent(m_StopEvent);
	m_ThreadHandle=::CreateThread(NULL,0,RequestDataInfoThread,(LPVOID)Param,0,0);

	CreateNewHtmlCtrl(Url,_T(""));
}


//������HTML�ؼ�
void CGetMailDataDlg::CreateNewHtmlCtrl(CString URL,CString PostData)
{

//#ifdef  __VS2008_SP1__

	if(m_HtmlCtrl)
	{
		m_HtmlCtrl->DestroyWindow();
		delete m_HtmlCtrl;
	}


	m_HtmlCtrl= new CHtmlCtrl(URL,PostData);
	m_HtmlCtrl->Create(CHtmlCtrl::IDD,this);
	
	m_HtmlCtrl->SetHostFlags(DOCHOSTUIFLAG_NO3DBORDER);


	CRect ClientRect;
	GetClientRect(ClientRect);
	CRect Rect;
	Rect.top = ClientRect.top+10;
	Rect.left = ClientRect.left + 10;
	Rect.bottom = ClientRect.bottom-60;
	Rect.right = ClientRect.right-3;
	m_HtmlCtrl->MoveWindow(Rect);
	m_HtmlCtrl->ShowWindow(SW_SHOW);
	
//#endif  //#ifdef  __VS2008_SP1__

}

//��������
void CGetMailDataDlg::PaseText(CString Text,vector<CString>& List)
{
	CString FindStartStr=_T("<a");
	CString FindEndStr=_T("/a");

	int StartPos= Text.Find(FindStartStr);
	int EndPos =Text.Find(FindEndStr,StartPos+1);

	if(StartPos == -1 )
	{
		FindStartStr=_T("<A");
		FindEndStr=_T("/A");
		StartPos= Text.Find(FindStartStr);
		EndPos =Text.Find(FindEndStr,StartPos+1);
	}

	while(true)
	{
		
		if(StartPos != -1&& EndPos != -1)
		{
			CString Temp = Text.Mid(StartPos+1,EndPos-StartPos-1);
			int TempPos=Temp.Find(_T("href"));
			if( TempPos != -1)
			{
				int TempPos1=Temp.Find(_T("\""),TempPos);
				int TempPos2=Temp.Find(_T("\""),TempPos1+1);
				CString Url = Temp.Mid(TempPos1+1,TempPos2-TempPos1-1);
				if(!Url.IsEmpty() && Url.GetLength() > 2 )
					List.push_back(Url);
			}

			StartPos= Text.Find(FindStartStr,EndPos+1);
			EndPos =Text.Find(FindEndStr,StartPos+1);


		}
		else
			break;
	}
}

//����email 
void CGetMailDataDlg::PaseEmail(CString Text,map<CString,int>& EmailMap)
{
	 CString strRegex=L"({[a-zA-Z0-9_]+@[a-zA-Z0-9]+[.][a-zA-Z0-9]+[.]?[a-zA-Z0-9]+})";
     CAtlRegExp<CAtlRECharTraitsW> reRule;
     wchar_t *wt = (wchar_t *)(LPCTSTR)strRegex;
     REParseError status = reRule.Parse((const ATL::CAtlRegExp<CAtlRECharTraitsW>::RECHAR *)wt);
     if (REPARSE_ERROR_OK != status)
     {
		 return;
     }

     CAtlREMatchContext<CAtlRECharTraitsW> mcRule;

     wt = (wchar_t *)(LPCTSTR)Text;

     if (!reRule.Match((const ATL::CAtlRegExp<CAtlRECharTraitsW>::RECHAR *)wt,&mcRule))
	 {
         return;

     }

     else
     {

         for (UINT nGroupIndex = 0; nGroupIndex < mcRule.m_uNumGroups; ++nGroupIndex)
         {

              const CAtlREMatchContext<>::RECHAR* szStart = 0;

              const CAtlREMatchContext<>::RECHAR* szEnd = 0;

              mcRule.GetMatch(nGroupIndex, &szStart, &szEnd);

              ptrdiff_t nLength = szEnd - szStart;

              CString strEmailAddress(szStart,  static_cast<int>(nLength));
			  EmailMap[strEmailAddress]++;
         }

     }
}

//�����ļ�
void CGetMailDataDlg::PaseEmailTxt(CString Text,map<CString,int>& EmailMap)
{
	int StartPos= 0;
	int EndPos =Text.Find(_T("\r\n"),StartPos);
	while(true)
	{
		
		if(StartPos != -1&& EndPos != -1)
		{
			CString Temp = Text.Mid(StartPos,EndPos-StartPos);
			Temp = Temp.Trim();
			EmailMap[Temp]++;

			StartPos= EndPos+2;
			EndPos =Text.Find(_T("\r\n"),StartPos);
		}
		else
			break;
	}

}

DWORD CGetMailDataDlg::RequestDataInfoThread(LPVOID lpVoid)
{
	sThreadParam* Param = (sThreadParam*)lpVoid;
	vector<CString> List;
	for(int Index=0; Index < Param->m_RequestUrl.size(); Index++)
	{

		if(WaitForSingleObject(Param->m_StopEvent,0) == 0)
			break;

	    CString Url = Param->m_RequestUrl[Index];
		CHttpFile* File= NULL;
		CString Txt;
		try
		{
			//��ȡ�������б��ļ�
			CInternetSession Session;
			File=(CHttpFile*)Session.OpenURL(Url);
			if(NULL == File) 
				return -1;

			DWORD Len=0;
			DWORD   Status; 
			DWORD   StatusSize   =   sizeof(Status); 
			DWORD   ContentLen=0,   ContentLenSize   =   sizeof(ContentLenSize); 
			if(File->QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_STATUS_CODE,  &Status,   &StatusSize,   NULL) &&   Status   ==   HTTP_STATUS_OK) 
				File-> QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_CONTENT_LENGTH,   &Len,   &ContentLenSize);	

			char Buffer[10*1024+1];
			memset(Buffer,0,10*1024+1);
			DWORD AllLen = 0;
			bool IsCompare=true;
			if(Len == 0)
			{
				File->Close();
		    	delete File; File = NULL;
				continue;
				IsCompare=false;
			}

			
			while(true)
			{
				char Buffer[1024*10+1]={0};
				memset(Buffer,0,1024*10+1);
				DWORD ReadLen= Len - AllLen > 10*1024 ? 10*1024 : Len - AllLen;
				
				DWORD ReadBytes=File->Read(Buffer,ReadLen);
				if(ReadBytes == -1 || ReadBytes == 0)
					break;
				AllLen += ReadBytes;

			///	wchar_t* Temp=ConvertToUnicodeFromUtf8(Buffer);
				CString TempTxt=CString(Buffer);
				//delete [] Temp;
				Txt+=TempTxt;

				if(AllLen == Len && IsCompare)
					break;
				
				if(!IsCompare && ReadLen < 10*1024)
					break;

			}


			if(Param->m_ParseType == 0)
			{
				
				PaseText(Txt,List);
			}

			if(Param->m_ParseType == 1)
			{
				map<CString,int> EmailMap;
				PaseEmail(Txt,EmailMap);
				if(!EmailMap.empty())
				{
				    CString FilePath = GetAppCurrentPath()+_T("\\email.tmp");
					SaveEmailToFile(FilePath,EmailMap);
				}
				
				if(::IsWindow(Param->m_hWnd))
					::PostMessage(Param->m_hWnd,WM_PARSE_GOING_MSG,Index,Param->m_RequestUrl.size());
				

			}
			
			File->Close();
			delete File; File = NULL;
		}catch(...)
		{
			if(File)
			{
				File->Close();
				delete File; File = NULL;
			}
		
		}
	}

	if(Param->m_ParseType == 0 && !List.empty())
	{
		sThreadParam* Param2 = new sThreadParam();
		Param2->m_hWnd = Param->m_hWnd;
		Param2->m_RequestUrl.insert(Param2->m_RequestUrl.end(),List.begin(),List.end());
		Param2->m_ParseType = 1;
		::CreateThread(NULL,0,RequestDataInfoThread,(LPVOID)Param2,0,0);

	}

	

	if(Param->m_ParseType == 1)
	{
		if(::IsWindow(Param->m_hWnd))
			::PostMessage(Param->m_hWnd,WM_PARSE_OVER_MSG,0,0);
	}

	delete Param;
	return 0;
}

//���������Ϣ
LRESULT CGetMailDataDlg::OnParseOverMsg(WPARAM wParam,LPARAM lParam)
{
	CString FilePath = GetAppCurrentPath()+_T("\\email.tmp");
	DWORD Flag = OPEN_EXISTING;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return 0;
	DWORD Size = ::GetFileSize(FileHandle,NULL);
	char* Buffer = new char[Size+1];
	memset(Buffer,'\0',Size+1);
	DWORD ReadBytes=0;
	::ReadFile(FileHandle,Buffer,Size,&ReadBytes,NULL);
	CString StrData=CString(Buffer);
	map<CString,int> EmailMap;
	PaseEmailTxt(StrData,EmailMap);
	if(!EmailMap.empty())
	{
		CString Name = GetAppCurrentPath()+_T("\\email.txt");
		SaveEmailToFile(Name,EmailMap);
	}
	delete []Buffer;
	CloseHandle(FileHandle);

	::DeleteFile(FilePath);

	GetDlgItem(IDC_TEST_STATIC)->SetWindowText(_T("���"));
	return 0;

}

//������������Ϣ
LRESULT CGetMailDataDlg::OnParseGoingMsg(WPARAM wParam,LPARAM lParam)
{
	int Pos = wParam;
	int AllPos=lParam;
	if(AllPos != 0)
	{
		int TempPos=100*Pos/AllPos;
		m_ProgressCtrl.SetPos(TempPos);
		CString Text;
		Text.Format(_T("%d/%d"),wParam,lParam);
		GetDlgItem(IDC_TEST_STATIC)->SetWindowText(Text);
	}
	return 0;
}

//��ʼ����
LRESULT CGetMailDataDlg::OnStartParseMsg(WPARAM wParam,LPARAM lParam)
{
	static int StartFlag=0;
	if(StartFlag == 0)
	{
		StartFlag=1;
		return 0;
	}

	BSTR b=(BSTR)wParam;
	CString Text=CString(b);
	vector<CString> List;
	map<CString,int> EmailMap;
	PaseText(Text,List);
	PaseEmail(Text,EmailMap);
	if(!EmailMap.empty())
	{
	    CString FilePath = GetAppCurrentPath()+_T("\\email.tmp");
		SaveEmailToFile(FilePath,EmailMap);
	}

	if(List.empty())
	{
		GetDlgItem(IDC_TEST_STATIC)->SetWindowText(_T("���"));
		return 0;
	}
		

	CString Text2;
	Text.Format(_T("0/%d"),List.size());
	GetDlgItem(IDC_TEST_STATIC)->SetWindowText(Text2);


	m_ProgressCtrl.SetPos(0);
	sThreadParam* Param2 = new sThreadParam();
	Param2->m_hWnd =m_hWnd;
	Param2->m_RequestUrl.insert(Param2->m_RequestUrl.end(),List.begin(),List.end());
	Param2->m_ParseType = 1;
	if(m_ThreadHandle != INVALID_HANDLE_VALUE)
	{
		::SetEvent(m_StopEvent);
		if(0 != ::WaitForSingleObject(m_ThreadHandle,1000))
			::TerminateThread(m_ThreadHandle,0);
		::ResetEvent(m_StopEvent);
	}
	m_ThreadHandle=::CreateThread(NULL,0,RequestDataInfoThread,(LPVOID)Param2,0,0);

	return 0;
}


void CGetMailDataDlg::OnBnClickedStopBtn()
{
	if(m_ThreadHandle != INVALID_HANDLE_VALUE)
	{
		::SetEvent(m_StopEvent);
		if(0 != ::WaitForSingleObject(m_ThreadHandle,1000))
			::TerminateThread(m_ThreadHandle,0);
		::ResetEvent(m_StopEvent);
	}
}

//����email���ļ���
void CGetMailDataDlg::SaveEmailToFile(CString FilePath,map<CString,int>& EmailMap)
{
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
	{
		FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,CREATE_ALWAYS ,FILE_ATTRIBUTE_NORMAL,NULL);
	}

	::SetFilePointer(FileHandle,0,0,FILE_END);
	map<CString,int>::iterator it=EmailMap.begin();
	CString WriteStr;
	for(; it != EmailMap.end(); it++)
	{
		WriteStr +=it->first+_T("\r\n");
	}
	
	char* Byte=UnicodeToUTF8(WriteStr.GetBuffer());
	int ByteLen=strlen(Byte);
	DWORD WriteBytes=0;
	::WriteFile(FileHandle,Byte,ByteLen,&WriteBytes,NULL);
	delete []Byte;
	WriteStr.ReleaseBuffer();
	CloseHandle(FileHandle);
}