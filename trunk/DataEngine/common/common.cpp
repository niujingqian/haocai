#include "stdafx.h"
#include "common.h"


void AsyncReadPipe(HANDLE hReadHandle, CString& argResult) ;
void SyncReadPipe(HANDLE hReadHandle, CString& argResult) ;

void ConvertGBKToUtf8(CString&  strGBK)    
{   
	int len=MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, NULL,0);   
	unsigned short * wszUtf8 = new unsigned short[len+1];   
	memset(wszUtf8, 0, len * 2 + 2);   
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1,(LPWSTR) wszUtf8, len);   
	len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);   
	char *szUtf8=new char[len + 1];   
	memset(szUtf8, 0, len + 1);   
	WideCharToMultiByte (CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, szUtf8, len, NULL,NULL);   
	strGBK = szUtf8;   
	delete[] szUtf8;   
	delete[] wszUtf8;   
}

void Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage)
{
	int len=lstrlen(strIn);
	int unicodeLen=MultiByteToWideChar(sourceCodepage,0,strIn,-1,NULL,0);
	wchar_t* pUnicode;
	pUnicode=new wchar_t[unicodeLen+1];
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));
	MultiByteToWideChar(sourceCodepage,0,strIn,-1,(LPWSTR)pUnicode,unicodeLen);
	BYTE * pTargetData = NULL;
	int targetLen=WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,0,NULL,NULL);
	pTargetData=new BYTE[targetLen+1];
	memset(pTargetData,0,targetLen+1);
	WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,targetLen,NULL,NULL);
	lstrcpy(strOut,(char*)pTargetData);
	delete pUnicode;
	delete pTargetData;
}




void ConvertUtf8ToGBK(CString&  strUtf8)    
{   
	int len=MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0);   
	unsigned short * wszGBK = new unsigned short[len+1];   
	memset(wszGBK, 0, len * 2 + 2);   
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, (LPWSTR)wszGBK, len);   
	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);   
	char *szGBK=new char[len + 1];   
	memset(szGBK, 0, len + 1);   
	WideCharToMultiByte (CP_ACP, 0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL,NULL);   
	strUtf8 = szGBK;   
	delete[] szGBK;   
	delete[] wszGBK;   
} 


int ConvertUtf8ToUnicode(CString&  strUtf8, char * pBuf)    
{   
	int len=MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0);   
	unsigned short * wszGBK = new unsigned short[len+1];   
	memset(wszGBK, 0, len * 2 + 2);   
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, (LPWSTR)wszGBK, len);   

	memcpy(pBuf,wszGBK,len * 2 + 2);   

	delete[] wszGBK;   
	return len * 2 ;   
} 

int ConvertGBKToUnicode(CString&  strGBK,char * pBuf)    
{   
	int len=MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, NULL,0);   
	unsigned short * wszUtf8 = new unsigned short[len+1];   
	memset(wszUtf8, 0, len * 2 + 2);   
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1,(LPWSTR) wszUtf8, len);   

	memcpy(pBuf,wszUtf8,len * 2 + 2);   

	delete[] wszUtf8;   

	return len * 2 ;   
} 

CString ConvertUnicodeToGBK(unsigned short * pUcs,int nNum)    
{   
	int len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pUcs, -1, NULL, 0, NULL, NULL);   
	char *szGBK=new char[len + 1];   
	memset(szGBK, 0, len + 1);   
	WideCharToMultiByte (CP_ACP, 0, (LPCWSTR)pUcs, -1, szGBK, len, NULL,NULL);   
	CString strUcs = szGBK;   
	delete []szGBK;   
	return strUcs;   
}  

//************************************************************************
/// <summary>
/// ����:ConvertToUnicodeFromUtf8
/// ����: Utf8 to Unicode 
/// </summary>
//************************************************************************
wchar_t* ConvertToUnicodeFromUtf8(char *utf8)
{
	DWORD wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, utf8, -1, NULL, 0);//CP_UTF8
	wchar_t* unicode = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(CP_ACP, NULL, utf8, -1, unicode, wcsLen);//CP_UTF8
	//unicode[wcsLen+1]=0;
	return unicode;
}

//************************************************************************
/// <summary>
/// ����:ConvertFromUnicodeToUtf8
/// ����: Unicode To Utf8
/// </summary>
//************************************************************************
char* ConvertFromUnicodeToUtf8(const wchar_t *unicode)
{
	int len = WideCharToMultiByte( CP_ACP, 0, unicode, -1, 0, 0, 0, 0 );
	char* buffer = new char[len+1];
	WideCharToMultiByte( CP_ACP, 0, unicode, -1, buffer,len, 0, 0 );
	// buffer[len] = '\0';
	return buffer;
}


//************************************************************************
/// <summary>
/// ����:EnCodeFileTimeToSystemTime
/// ����: ���ļ�ʱ�����Ϊϵͳʱ���ʽ:yyyy-mm-dd   ��Ҫ���ⲿ�ͷ�
/// </summary>
//************************************************************************
char* EnCodeFileTimeToSystemTime(FILETIME argFiletime)
{
	SYSTEMTIME systim;
	memset(&systim,0,sizeof(SYSTEMTIME));
	FileTimeToSystemTime(&argFiletime,&systim);
	char* tmpStr = new char[30];
	char tmp[4];
	sprintf_s(tmpStr,30,"%d",systim.wYear);	 
	strcat_s(tmpStr,30,"-");
	sprintf_s(tmp,4,"%d",systim.wMonth);
	strcat_s(tmpStr,30,tmp);
	strcat_s(tmpStr,30,"-");
	sprintf_s(tmp,4,"%d",systim.wDay);
	strcat_s(tmpStr,30,tmp);
	return tmpStr;
}

//************************************************************************
/// <summary>
/// ����:EnCodeFileTimeToSystemTime
/// ����: �ı���ʽ��ϵͳʱ�����Ϊ�ļ�ʱ��    ϵͳʱ���ʽΪ:yyyy-mm-dd
/// </summary>
//************************************************************************
FILETIME DeCodeSystemTimeToFileTime(char* argSystime)
{
	SYSTEMTIME systim;
	FILETIME filetime;
	memset(&filetime,0,sizeof(FILETIME));
	memset(&systim,0,sizeof(SYSTEMTIME));
	char* ptmp =argSystime;
	char* stryear  = new char[5];
	char* strmonth = new char[3];
	char* strday   = new char[3];
	memset(stryear,0,sizeof(char)*5);
	memset(strmonth,0,sizeof(char)*3);
	memset(strday,0,sizeof(char)*3);

	strncpy_s(stryear,5,ptmp,4);
	systim.wYear = atoi(stryear);
	ptmp+=5;
	if (*(ptmp+1)=='-')
	{
		strncpy_s(strmonth,5,ptmp,1);
		systim.wMonth = atoi(strmonth);
		ptmp+=2;
	}
	else if (*(ptmp+2)=='-')
	{
		strncpy_s(strmonth,5,ptmp,2);
		systim.wMonth = atoi(strmonth);
		ptmp+=3;
	}else
	{
		return filetime;
	}
	//strcpy_s(strday,3,ptmp);
	strncpy(strday, ptmp, 3);

	systim.wDay = atoi(strday);

	systim.wHour = 12;
	systim.wDayOfWeek = 1;
	systim.wMinute = 12;
	SystemTimeToFileTime(&systim,&filetime);
	delete []stryear;
	delete []strmonth;
	delete []strday;

	return filetime;	
}

char* GetSmsState(unsigned short state)
{
	char *tmp = new char [10];
	memset(tmp,0,sizeof(char)*10);
	switch(state)
	{
	case 0x1:
		//strcpy_s(tmp,10,"�Ѷ�");
		strncpy(tmp, "�Ѷ�", 10);
		break;
	case 0x0:
		//strcpy_s(tmp,10,"δ��");
		strncpy(tmp, "δ��", 10);
		break;

	case 0x28:
		//strcpy_s(tmp,10,"δ��");
		strncpy(tmp, "δ��", 10);
		break;
	case 0x21:
		//strcpy_s(tmp,10,"�ѷ���");
		strncpy(tmp, "�ѷ���", 10);

		break;
		/*case 0x5:
		strcpy_s(tmp,"unread");
		break;
		case 0x6:
		strcpy_s(tmp,"unread");
		break;*/
	default:
		//strcpy_s(tmp,10,"�Ѷ�");
		strncpy(tmp, "�Ѷ�", 10);
		break;
	}

	return tmp;

} 

void runCmdAndResult(LPSTR argCmd, CString& argResult, bool IsReadResult)
{
	/// �鿴������
	argResult.Empty();

	CString  strShowInfo;
	strShowInfo.Format(_T("runCmdAndResult begin argCmd=%s\r\n"),  argCmd);
	XWriteEventLog(strShowInfo);

	CString strPath, strPath2;

	int nTimeOut = 6; // һ�������6��
	DWORD WaitTime = nTimeOut * 1000;
	CString argCmdStr = argCmd;
	
	if(argCmdStr.Find(_T("install")) != -1)
	{		
		nTimeOut = 60; // �ƶ�Ӧ�ó���ʱ��2��������60�롣2�����ϰ� y = x*1000 + 40*1000�Ĺ�˾����TimeOut�ĺ�����������x = z/1024*1024 + 
		WaitTime = nTimeOut * 1000;

		CString TempPath = argCmdStr.Mid(argCmdStr.Find(_T("install"))+8);
		int Pos = 0;
		if( TempPath.Find( _T("-r")) != -1 )
		{
			TempPath = TempPath.Mid( TempPath.Find("-r") + 2 );			
		}
		TempPath.TrimLeft();
		TempPath.TrimRight();
		if( TempPath.Find("\"") != -1 )
		{
			TempPath=TempPath.Mid(TempPath.Find("\"")+1);
			TempPath=TempPath.Left(TempPath.Find("\""));
		}
		XWriteEventLog(_T("[runCmdAndResult] intall Apk path=[%s]"),TempPath);
		HANDLE FileHandle = CreateFile(TempPath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(FileHandle == INVALID_HANDLE_VALUE)
		{
			WaitTime = nTimeOut*1000;
		}

		DWORD Size = GetFileSize(FileHandle,NULL);
		DWORD Time = Size / (1024*1024) + 1;
		if( Time > 2 )
		{
			WaitTime = Time * 2000 + 40 * 1000;
		}
		CloseHandle(FileHandle);
	}
	else if(argCmdStr.Find(_T("pull")) != -1)
	{
		WaitTime = 20 * 1000;
	}
	else if(argCmdStr.Find(_T("forward")) != -1 || argCmdStr.Find(_T("shell am broadcast")) != -1)
	{
		WaitTime = 2 * 1000;
	}	

	strPath2 = _T("\"");
	::GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH); 
	strPath.ReleaseBuffer();
	strPath=strPath.Left(strPath.ReverseFind('\\'));

	if(strPath.Right(1)!='\\')
	{
		strPath+="\\";
		strPath += "adb\\adb.exe";

		strPath2 += strPath;
		strPath2 +=  _T("\"");

		strPath = strPath2;

	}else{

		strShowInfo.Format(_T("runCmdAndResult Failed strPath=%s\r\n"),  strPath);
		XWriteEventLog(strShowInfo);

		return;
	}

	// TODO: Add extra validation here
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);    
	sa.lpSecurityDescriptor = NULL; //ʹ��ϵͳĬ�ϵİ�ȫ������    
	sa.bInheritHandle = TRUE; //�����Ľ��̼̳о��

	if (!CreatePipe(&hRead,&hWrite,&sa,0)) //���������ܵ�
	{        
		XWriteEventLog(_T("runCmdAndResult CreatePipe Failed \r\n"));
		return ;
	}

	STARTUPINFO si;    
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES  ai;

	ZeroMemory(&ai,sizeof(SECURITY_ATTRIBUTES));
	ai.nLength  = sizeof(ai);
	ai.bInheritHandle = TRUE;
	DWORD nFlag = PROCESS_TERMINATE ;
	ai.lpSecurityDescriptor =  NULL;

	ZeroMemory(&si,sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);    
	GetStartupInfo(&si);    
	si.hStdError = hWrite;    
	si.hStdOutput = hWrite;				  //�´������̵ı�׼�������д�ܵ�һ��
	si.wShowWindow = SW_HIDE;		//���ش���    
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	CString strCmd = argCmd;
	strCmd.Mid(3,strCmd.GetLength()-3);

	int Pos=strCmd.Find(_T("adb"));
	if(Pos!= -1)
		strCmd=strCmd.Mid(Pos+3);

	strPath += strCmd;

	//tmp.Format("cmd /C %s",argCmd); //"adb devices"
	char cmdline[512] = {0}; 
	sprintf(cmdline,"%s",strPath);


	HANDLE  hOpenProcess ;
	if (!CreateProcess(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) //�����ӽ���
	{
		XWriteEventLog(_T("runCmdAndResult CreateProcess Failed \r\n"));
		return ;
	}
    CloseHandle(hWrite); //�رչܵ����

	DWORD dwExitCode;
	DWORD dwRet = WaitForSingleObject(pi.hProcess, WaitTime);
	AsyncReadPipe(hRead, argResult) ;
	
	if(argResult.Find(_T("daemon not running")) != -1)
	{
		dwRet = WaitForSingleObject(pi.hProcess, WaitTime);
		AsyncReadPipe(hRead, argResult) ;
	}
	//if(dwRet != WAIT_OBJECT_0 && !GetExitCodeProcess(pi.hProcess, &dwExitCode))
	{
		if(dwRet == WAIT_TIMEOUT)
		{
			XWriteEventLog(_T("runCmdAndResult WaitForSingleObject TimeOut \r\n"));
			::TerminateProcess(pi.hProcess,1);
		//	KillAdb();
		}else
		{
			XWriteEventLog(_T("runCmdAndResult WaitForSingleObject Others Error To KillAdb\r\n"));
		}
	
	}
	
	
	if(!IsReadResult)
	{
		CloseHandle(hRead);
		XWriteEventLog(_T("runCmdAndResult CloseHandle(hRead) and return \r\n"));
		return;
	}

	
	// SyncReadPipe(hRead, argResult) ;
	//  XWriteEventLog(_T("runCmdAndResult  return  OK\n"));
	 CloseHandle(hRead);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}
/*
void runAdbInstallApp(LPSTR argCmd, CString& argResult, bool IsReadResult)
{
	/// �鿴������
	argResult.Empty();

	CString  strShowInfo;
	strShowInfo.Format( _T("runCmdAndResult begin argCmd=%s\r\n"), argCmd );
	XWriteEventLog( strShowInfo );

	CString strPath, strPath2;

	int nTimeOut = 6; // һ�������6��
	CString argCmdStr = argCmd;

	if( argCmdStr.Find( _T("install")) != -1 )
	{
		nTimeOut = 60; // �ƶ�Ӧ�ó�����60��

		CString TempPath=argCmdStr.Mid( argCmdStr.Find(_T("install")) + 8 );
		int Pos = 0;
		if(TempPath.Find( _T("-r")) != -1 )
		{
			TempPath = TempPath.Mid( TempPath.Find("-r") + 2 );			
		}

		TempPath.TrimLeft();
		TempPath.TrimRight();
		if( TempPath.Find("\"") != -1 )
		{
			TempPath = TempPath.Mid( TempPath.Find("\"") + 1 );
			TempPath = TempPath.Left( TempPath.Find("\"") );
		}
		XWriteEventLog( _T("[runCmdAndResult] intall Apk path=[%s]"), TempPath );
		HANDLE FileHandle = CreateFile(TempPath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if( FileHandle == INVALID_HANDLE_VALUE )
		{
			WaitTime = nTimeOut*1000;
		}

		DWORD Size = GetFileSize( FileHandle, NULL );
		DWORD Time = Size / (1024*1024) + 1;
		if( Time > 2 )
		{		
			nTimeOut += Time*10;
		}

		CloseHandle(FileHandle);
	}
	else if( argCmdStr.Find( _T("pull") ) != -1 ) // ����������ģ��Ĵ���
	{	
		nTimeOut = 20;
	}
	else if( argCmdStr.Find( _T("forward") ) != -1 || argCmdStr.Find(_T("shell am broadcast")) != -1 ) // ����������ģ��Ĵ���
	{	
		nTimeOut = 2;
	}

	DWORD WaitTime = nTimeOut * 1000;

	strPath2 = _T("\"");
	::GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH); 
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\'));

	if( strPath.Right(1) !=' \\' )
	{
		strPath+="\\";
		strPath += "adb\\adb.exe";

		strPath2 += strPath;
		strPath2 +=  _T("\"");

		strPath = strPath2;
	}
	else
	{
		strShowInfo.Format(_T("runCmdAndResult Failed strPath=%s\r\n"),  strPath);
		XWriteEventLog(strShowInfo);

		return;
	}

	// TODO: Add extra validation here
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);    
	sa.lpSecurityDescriptor = NULL; // ʹ��ϵͳĬ�ϵİ�ȫ������    
	sa.bInheritHandle = TRUE; // �����Ľ��̼̳о��

	if ( !CreatePipe( &hRead, &hWrite, &sa, 0 ) ) // ���������ܵ�
	{        
		XWriteEventLog(_T("runCmdAndResult CreatePipe Failed \r\n"));
		return ;
	}

	STARTUPINFO si;    
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES  ai;

	ZeroMemory(&ai,sizeof(SECURITY_ATTRIBUTES));
	ai.nLength  = sizeof(ai);
	ai.bInheritHandle = TRUE;
	DWORD nFlag = PROCESS_TERMINATE ;
	ai.lpSecurityDescriptor =  NULL;

	ZeroMemory(&si,sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);    
	GetStartupInfo(&si);    
	si.hStdError = hWrite;    
	si.hStdOutput = hWrite;				  //�´������̵ı�׼�������д�ܵ�һ��
	si.wShowWindow = SW_HIDE;		//���ش���    
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	CString strCmd = argCmd;
	strCmd.Mid( 3, strCmd.GetLength() - 3 );

	int Pos = strCmd.Find(_T("adb"));
	if( Pos != -1 )
	{
		strCmd = strCmd.Mid( Pos + 3 );
	}

	strPath += strCmd;

	//  tmp.Format("cmd /C %s",argCmd); //"adb devices"
	char cmdline[512] = {0}; 
	sprintf(cmdline,"%s",strPath);


	HANDLE  hOpenProcess ;
	if ( !CreateProcess(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi) ) //�����ӽ���
	{
		XWriteEventLog(_T("runCmdAndResult CreateProcess Failed \r\n"));
		return ;
	}
	CloseHandle(hWrite); //�رչܵ����

	DWORD dwExitCode;
	DWORD dwRet = WaitForSingleObject(pi.hProcess, WaitTime);
	AsyncReadPipe(hRead, argResult) ;

	if(argResult.Find(_T("daemon not running")) != -1)
	{
		dwRet = WaitForSingleObject(pi.hProcess, WaitTime);
		AsyncReadPipe(hRead, argResult) ;
	}
	//if(dwRet != WAIT_OBJECT_0 && !GetExitCodeProcess(pi.hProcess, &dwExitCode))
	{
		if(dwRet == WAIT_TIMEOUT)
		{
			XWriteEventLog(_T("runCmdAndResult WaitForSingleObject TimeOut \r\n"));
			::TerminateProcess(pi.hProcess,1);
			//	KillAdb();
		}else
		{
			XWriteEventLog(_T("runCmdAndResult WaitForSingleObject Others Error To KillAdb\r\n"));
		}	
	}	

	if( !IsReadResult )
	{
		CloseHandle(hRead);
		XWriteEventLog(_T("runCmdAndResult CloseHandle(hRead) and return \r\n"));
		return;
	}

	//  SyncReadPipe(hRead, argResult) ;
	//  XWriteEventLog(_T("runCmdAndResult  return  OK\n"));
	CloseHandle(hRead);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}
*/
//��ȡ��ǰʱ��
char *  Time2String(char * szDT, time_t time)
{
	struct tm *pTm;
	pTm = localtime(&time);
	if (pTm != NULL)
	{
		memset(szDT, 0x00, strlen(szDT));

		sprintf(szDT, "%04d/%02d/%02d %02d:%02d:%02d",
			pTm->tm_year+1900,pTm->tm_mon+1,pTm->tm_mday,pTm->tm_hour,pTm->tm_min,pTm->tm_sec);
	}else{
		szDT[0]='\0';
		return NULL;
	}
	return szDT;
}

//��ȡ��ǰִ���ļ�Ŀ¼
CString GetCurrentDir(void)
{
	TCHAR Path[MAX_PATH];
	GetModuleFileName(NULL,Path,MAX_PATH);
	CString FilePath=Path;
	FilePath=FilePath.Mid(0,FilePath.ReverseFind('\\'));
	FilePath+=_T("\\");

	return FilePath;
}


/// ɱ������
void  KillAdb(void )
{
	HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32* processInfo=new PROCESSENTRY32;        
	processInfo->dwSize=sizeof(PROCESSENTRY32);      

	//�������ǽ����վ����PROCESSENTRY32�ṹ����Process32Next()��   
	//ִ��֮��PROCESSENTRY32 �ṹ����ý��̵���Ϣ������ѭ��������ֱ����������FALSE��       
	int index=0;    
	int ID = 0;   
	while(Process32Next(hSnapShot,processInfo)!=FALSE)  
	{        
		index++;        

		char * ch = processInfo->szExeFile;

		{			
			if(strstr(ch,"adb.exe"))//ʹ����δ����ʱ��ֻ��Ҫ�ı�"cmd.exe".����ĳ���Ҫ�����Ľ������Ϳ����ˡ� 
			{                 
				ID = processInfo->th32ProcessID;           			             
				HANDLE hProcess;                 
				// ���������ú��� TerminateProcess()��ֹ���̣�           
				// ����������PROCESS_ALL_ACCESS              
				hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE,ID);                 
				if(hProcess==NULL)                  
				{                      
					printf("Unable to get handle of process: ");                 
					printf("Error is: %d",GetLastError());              
				}                  
				BOOL bIsOK = TerminateProcess(hProcess,0);             
				CloseHandle(hProcess);         

				if(bIsOK )
				{
					XWriteEventLog("Kill  adb.exe  OK \r\n");
				}else
				{
					XWriteEventLog("Kill  adb.exe ~OK \r\n");
				}
			}  
		}      
	}       
	CloseHandle(hSnapShot);    
	delete processInfo;    
}

/// �鿴������
int  PSAdb(void)
{
	HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 oProcessInfo;
	oProcessInfo.dwSize=sizeof(PROCESSENTRY32);      

	//�������ǽ����վ����PROCESSENTRY32�ṹ����Process32Next()��   
	//ִ��֮��PROCESSENTRY32 �ṹ����ý��̵���Ϣ������ѭ��������ֱ����������FALSE��       
	int nCounter =0;    
	while(Process32Next(hSnapShot, & oProcessInfo)!=FALSE)  
	{        
		char * ch = oProcessInfo.szExeFile;
		{			
			if(strstr(ch,"adb.exe"))//ʹ����δ����ʱ��ֻ��Ҫ�ı�"cmd.exe".����ĳ���Ҫ�����Ľ������Ϳ����ˡ� 
			{                 
				nCounter++;
			}  
		}      
	}       
	CloseHandle(hSnapShot);    

	return nCounter;
}

/// �鿴������
vector<DWORD>  SearchAdb(void)
{
	vector<DWORD> AdbProcessId;
	HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 oProcessInfo;
	oProcessInfo.dwSize=sizeof(PROCESSENTRY32);      

	//�������ǽ����վ����PROCESSENTRY32�ṹ����Process32Next()��   
	//ִ��֮��PROCESSENTRY32 �ṹ����ý��̵���Ϣ������ѭ��������ֱ����������FALSE��       
	int nCounter =0;    
	while(Process32Next(hSnapShot, & oProcessInfo)!=FALSE)  
	{        
		char * ch = oProcessInfo.szExeFile;
		{			
			if(strstr(ch,"adb.exe"))//ʹ����δ����ʱ��ֻ��Ҫ�ı�"cmd.exe".����ĳ���Ҫ�����Ľ������Ϳ����ˡ� 
			{         
				AdbProcessId.push_back(oProcessInfo.th32ProcessID);
			}  
		}      
	}       
	CloseHandle(hSnapShot);    

	return AdbProcessId;
}

void AsyncReadPipe(HANDLE hReadHandle, CString& argResult) 
{
	char buffer[4096 +1] = {0x00};
	 DWORD dwRead, dwLength;
	 OVERLAPPED ov;
	 memset(&ov, 0x00, sizeof(ov));

	 ov.Offset = 0;
	 ov.OffsetHigh = 0;
	 ov.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	
	 CString  strShowInfo;
	 BOOL bReadOK = FALSE;
	 while(true)
	 {
			 bReadOK  = ReadFile(hReadHandle,buffer,4096,&dwRead,&ov);

		 	 if(! bReadOK)
			 {
				 DWORD nRet = GetLastError();
				 strShowInfo.Format(_T("AsyncReadPipe ReadFile Error %d\r\n"), nRet );
				 XWriteEventLog(strShowInfo);

				  if (nRet == ERROR_IO_PENDING)
				  {
					 strShowInfo.Format(_T("AsyncReadPipe ERROR_IO_PENDING\r\n"));
					 XWriteEventLog(strShowInfo);
					 while(!GetOverlappedResult( hReadHandle , &ov, &dwLength, TRUE ))
					   {
							DWORD dwError = GetLastError();
							strShowInfo.Format(_T("AsyncReadPipe GetOverlappedResult Error %d\r\n"), dwError );
							 XWriteEventLog(strShowInfo);
							if(dwError == ERROR_IO_INCOMPLETE)   
							{
								 strShowInfo.Format(_T("AsyncReadPipe ERROR_IO_INCOMPLETE\r\n"));
								 XWriteEventLog(strShowInfo);
								 Sleep(200);
								 continue;
							}else
							{
								break;
							}
					   }
				  }//#if nRet 
				  else //if(ERROR_BROKEN_PIPE == nRet)
				  {
						break;
				  }
			 } //#if ReadFile
			 else
			 {
				 break;
			 }

	 }

	 strShowInfo.Format(_T("AsyncReadPipe Over"));
	 XWriteEventLog(strShowInfo);

	 argResult += buffer;
	 CloseHandle(ov.hEvent);
}


void SyncReadPipe(HANDLE hReadHandle, CString& argResult) 
{
	char buffer[4096 +1] = {0};
	DWORD bytesRead = 0x00;
	DWORD nDiffTime= 0x00, nEndTime = 0x00,  nBeginTime = ::GetTickCount();
	int nRead = 0x00;

	CString strShowInfo;
	while (true) 
	{
		strShowInfo.Format(_T("runCmdAndResult Begin Read Pipe nReadIndex=%d\r\n"), nRead ++);
		XWriteEventLog(strShowInfo);
		
		BOOL bReadOK  = ReadFile(hReadHandle,buffer,4096,&bytesRead, NULL);
		//if (ReadFile(hReadHandle,buffer,4096,&bytesRead,NULL) == NULL) //��ȡ�ܵ�
		if( ! bReadOK)
		{
			strShowInfo.Format(_T("runCmdAndResult Read Pipe Break && Buffer=\r\n%s\r\n"),  buffer);
			XWriteEventLog(strShowInfo);
			break;
		}

		argResult += buffer;
		nEndTime  = ::GetTickCount(); 

		nDiffTime  = nEndTime  - nBeginTime; 
		if( nDiffTime > PIPE_TIME_OUT )
		{
			strShowInfo.Format(_T("runCmdAndResult Read Pipe Time out =%d\r\n"),  PIPE_TIME_OUT);
			XWriteEventLog(strShowInfo);
			break;
		}
		Sleep(100);
	}

}

/*
CString ReplaceStr( CString strSrc, CString strSub, CString strReplace )
{	
	CString strDst;
	vector<HIGH_LIGHT_INFO> VectHiLtInfo;
	GetSubStrInfoInPrimaryStr( strSrc, strSub, &VectHiLtInfo, TRUE );
	int iSize = VectHiLtInfo.size();

	int iPos = 0;
	for( int i = 0; i < iSize; i++ )
	{
		HIGH_LIGHT_INFO HiLtCur = VectHiLtInfo[i];
		int iEscPos = HiLtCur.iIndex;
		int iEscLen = HiLtCur.iLen;

		strDst += strSrc.Mid(iPos,iEscPos-iPos);
		strDst += strReplace;
		iPos = iEscPos + iEscLen;
	}

	strDst += strSrc.Mid(iPos);

	return strDst;
}

CString GetEscChar( CString strSrc )
{
	CString strDst;

	strDst = ReplaceStr( strSrc, _T("&"), _T("&amp;"));

	strDst = ReplaceStr( strDst, _T("<"), _T("&lt;") );

	strDst = ReplaceStr( strDst, _T(">"), _T("&gt;") );

	strDst = ReplaceStr( strDst, _T("\'"), _T("&apos;") );

	strDst = ReplaceStr( strDst, _T("\""), _T("&quot;") );

	return strDst;
}
*/
CString ReplaceStr( CString strSrc, CString strSub, CString strReplace )
{
	CString strDst;

	int iLenMatch = strSub.GetLength();
	CString strToken = strSrc;

	int iCurPos = 0;

	int iToken = strToken.Find( strSub );
	while( ( iToken = strToken.Find( strSub ) ) != -1 )
	{
		strDst += strToken.Mid( 0, iToken );
		strDst += strReplace;

		iCurPos += iToken + iLenMatch;
		strToken = strSrc.Mid( iCurPos );		
	}

	strDst += strSrc.Mid( iCurPos );

	return strDst;
}

std::wstring ReplaceWstr( const wstring& orignStr, const wstring& oldStr, const wstring& newStr )
{
	size_t pos = 0;
	wstring tempStr = orignStr;
	wstring::size_type newStrLen = newStr.length();
	wstring::size_type oldStrLen = oldStr.length();
	while(true)
	{
		pos = tempStr.find(oldStr, pos);
		if (pos == wstring::npos) break;

		tempStr.replace(pos, oldStrLen, newStr);        
		pos += newStrLen;

	}

	return tempStr;
}


