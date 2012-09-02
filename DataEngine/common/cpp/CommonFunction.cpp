#include "StdAfx.h"
#include "../Include/CommonFunction.h"
#include "../Include/GenFirstPYLette.h"

/*****************************************�ַ��滻����****************************************/

//wstring ReplaceWstr( const wstring& orignStr, const wstring& oldStr, const wstring& newStr )
//{
//	size_t pos = 0;
//	wstring tempStr = orignStr;
//	wstring::size_type newStrLen = newStr.length();
//	wstring::size_type oldStrLen = oldStr.length();
//	while(true)
//	{
//		pos = tempStr.find(oldStr, pos);
//		if (pos == wstring::npos) break;
//
//		tempStr.replace(pos, oldStrLen, newStr);        
//		pos += newStrLen;
//
//	}
//
//	return tempStr;
//}

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




/*****************************************ת�뺯��****************************************/

//��GBK��ת�뵽��UTF8
void TransGBKToUtf8(CString&  strGBK)
{
	/*int len=MultiByteToWideChar(CP_ACP, 0,LPCSTR, -1, NULL,0);   
	unsigned short * wszUtf8 = new unsigned short[len+1];   
	memset(wszUtf8, 0, len * 2 + 2);   
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1,(LPWSTR) wszUtf8, len);   
	len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);   
	char *szUtf8=new char[len + 1];   
	memset(szUtf8, 0, len + 1);   
	WideCharToMultiByte (CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, szUtf8, len, NULL,NULL);   
	strGBK = szUtf8;   
	delete[] szUtf8;   
	delete[] wszUtf8;   */
}

//��Utf8��ת�뵽��GBK
void TransUtf8ToGBK(CString&  strUtf8)
{
	int len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)strUtf8, -1, NULL, 0, NULL, NULL);   
	char *szGBK=new char[len + 1];   
	memset(szGBK, 0, len + 1);   
	WideCharToMultiByte (CP_ACP, 0, (LPCWSTR)strUtf8, -1, szGBK, len, NULL,NULL);   
	strUtf8 = szGBK;   
	delete[] szGBK;   
}

//��GBK��ת�뵽��Unicode
void TransGBKToUnicode(CString&  strGBK)
{
	/*int len=MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0);   
	unsigned short * wszGBK = new unsigned short[len+1];   
	memset(wszGBK, 0, len * 2 + 2);   
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, (LPWSTR)wszGBK, len);   
	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);   
	char *szGBK=new char[len + 1];   
	memset(szGBK, 0, len + 1);   
	WideCharToMultiByte (CP_ACP, 0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL,NULL);   
	strUtf8 = szGBK;   
	delete[] szGBK;   
	delete[] wszGBK;   */
}

//��UTF8ת�뵽UNICODE
void TransUtf8ToUnicode(CString&  strUtf8)
{
	//int len=MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0);   
	//unsigned short * wszGBK = new unsigned short[len+1];   
	//memset(wszGBK, 0, len * 2 + 2);   
	//MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, (LPWSTR)wszGBK, len);   

	//memcpy(pBuf,wszGBK,len * 2 + 2);   

	//delete[] wszGBK;   
	//return len * 2 ;   
}

//��Uincode ת�뵽UTF8
void TransUnicodeToUtf8(CString& strUnicode)
{
	 int len = WideCharToMultiByte( CP_UTF8, 0,(LPCTSTR)strUnicode, -1, 0, 0, 0, 0 );
	 char* buffer = new char[len+1];
	 memset(buffer,0,sizeof(char)*(len+1));
	 WideCharToMultiByte( CP_UTF8, 0, (LPCTSTR)strUnicode, -1, buffer,len, 0, 0 );
	 strUnicode=CString(buffer);
	 delete []buffer;
}

//��UTF8 ת�뵽 URLCODE
void TransUtf8ToURLCode(CString& strUtf8)
{
	/*int len=MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0);   
	wchar_t* wszGBK=new wchar_t[len+1];
	memset(wszGBK,0,sizeof(wchar_t)*(len+1));
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, (LPWSTR)wszGBK, len);   
	strUtf8 = CString(wszGBK);
	delete[] wszGBK;   */

}

//��UNICODE ת�뵽��URLCODE
void TransUnicodeToURLCode(CString& strUnicode)
{
}

//��UNICODE ת�뵽��BASE64
void TransUnicodeToBase64(CString& strUnicode)
{
}

//��Base64 ת�뵽��Unicode
void TransBase64ToUnicode(CString& strBase64)
{
}


//ִ��adb����
bool ExecAdbCmd(CString CmdStr,CString& CmdRetStr)
{
	int Pos=CmdStr.Find(_T("adb"));
	if(Pos!= -1)
		CmdStr=CmdStr.Mid(Pos+3);
	CmdStr.TrimLeft();

	CString AdbPath=GetAppPath()+_T("adb\\adb.exe");
	
    HANDLE hPipeInputRead, hPipeInputWrite, hPipeOutputRead, hPipeOutputWrite;  

    //���������ܵ� ��ֹ����
    SECURITY_ATTRIBUTES sa;    
    sa.nLength              = sizeof(SECURITY_ATTRIBUTES);  
    sa.lpSecurityDescriptor = NULL;  
    sa.bInheritHandle       = TRUE; 

    //��������ܵ�  
    CreatePipe(&hPipeInputRead, &hPipeInputWrite, &sa, 0);  

    //��������ܵ�  
    CreatePipe(&hPipeOutputRead, &hPipeOutputWrite, &sa, 0);  

	/*DWORD WriteBytes=0;
	WriteFile(hPipeInputWrite,CmdStr.GetBuffer(),CmdStr.GetLength(),&WriteBytes,NULL); */
    CloseHandle(hPipeInputWrite);  


    //����ʾ��������Ϊ�ӽ���  
    STARTUPINFO si;  
    si.cb = sizeof(STARTUPINFO);  
    GetStartupInfo(&si);   
    si.hStdInput   = hPipeInputRead;   //�����ɱ�׼���� -> �ӹܵ��ж�ȡ  
    si.hStdOutput  = hPipeOutputWrite; //����ɱ�׼��� -> ������ܵ�  
    si.wShowWindow = SW_HIDE;    
    si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;    
    PROCESS_INFORMATION pi;   

	CmdStr=AdbPath+_T(" ")+CmdStr;
    CreateProcess(NULL,CmdStr.GetBuffer(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi);  
    WaitForSingleObject(pi.hProcess, INFINITE);  
	CmdStr.ReleaseBuffer();
  
    //�ر��������ݹܵ�  
    CloseHandle(hPipeInputRead);  
    CloseHandle(hPipeOutputWrite); 

    while (true)  
    {   
		char Buffer[1024*10+1];
		memset(Buffer,0,1024*10+1);
		DWORD ReadBytes=0;

        //�ӹܵ��ж�ȡ  
        BOOL IsSuccess = ReadFile(hPipeOutputRead,Buffer,1024*10, &ReadBytes, NULL);  
        if( !IsSuccess || ReadBytes == 0)   
            break;   
		CmdRetStr += CString(Buffer);

    }  
    //�ر�������ݹܵ�  
    CloseHandle(hPipeOutputRead);  
	CloseHandle(pi.hProcess);
	return true;
}

//��ȡӦ�ó���·��
CString GetAppPath()
{
	CString Path;
	::GetModuleFileName(NULL,Path.GetBuffer(MAX_PATH),MAX_PATH); 
	Path.ReleaseBuffer();
	Path=Path.Left(Path.ReverseFind('\\'));
	if(Path.Right(1)!='\\')
		Path+= _T("\\");

	return Path;
}

//��ȡӦ�ó���·��
CString GetAppPath2(CString Temp)
{
	return Temp;
}

//�ж��ļ��Ƿ����
bool IsFilesExit(CString FileName)
{
	 WIN32_FIND_DATA FindFileData;   
	 HANDLE hFind = INVALID_HANDLE_VALUE;

	 // �жϲ����ļ��Ƿ����   
	 hFind =  FindFirstFile(FileName,&FindFileData);   
	 if(hFind == INVALID_HANDLE_VALUE)   
		 return false;  

	 CloseHandle(hFind);
	 return true;      
}

//��װ�ֻ�Ӧ�ó���
bool InstallPhoneApp(CString PhoneDes,CString AppName,bool IsReInstall,ePathType Type)
{
	CString StrPath;
	GetTempPath(MAX_PATH,StrPath.GetBuffer(MAX_PATH));
	StrPath.ReleaseBuffer();
	CString TempApp;
	TempApp.Format(_T("Temp_%d.apk"),GetTickCount());
	StrPath += TempApp;
	DeleteFile(StrPath);
	
	BOOL b = CopyFile( AppName, StrPath, false );
	if( !b )
		return false;		

	CString InstallCmd;
	if( Type == PATH_PHONE || Type ==PATH_UNKOWN)
		InstallCmd.Format(_T("adb %s shell  pm setInstallLocation 1"),PhoneDes);
	else
		InstallCmd.Format(_T("adb %s shell  pm setInstallLocation 2"),PhoneDes);

	CString StrOrder;
	if( IsReInstall)
		StrOrder.Format(_T("adb %s install -r \"%s\""),PhoneDes,StrPath);
	else
		StrOrder.Format(_T("adb %s install \"%s\""),PhoneDes,StrPath);
	
	
	//����Ӧ�ð�װ��ʲôλ��
	CString CmdRetStr;
	::ExecAdbCmd(InstallCmd,CmdRetStr);
	::ExecAdbCmd(StrOrder,CmdRetStr);

	::DeleteFile( StrPath ); // ɾ����ʱapk�ļ�

	if(CmdRetStr.Find(_T("Success")) != -1 )
		return true;
	else
		return false;

	
}



//��ȡAndroid �豸�б�
void GetAndroidDeviceList(vector<sPhoneStatus>& DeviceList)
{
	int StartPos=0;
	int EndPos=0;
	
	CString Cmd=_T("adb devices list");
	CString CmdRetStr;
	ExecAdbCmd(Cmd,CmdRetStr);
	
	StartPos=0;
	EndPos=0;

	//// ����Ret���
	while(true)
	{
		EndPos = CmdRetStr.Find(_T("\r\n"),StartPos);
		if(EndPos != -1)
		{
			CString Temp=CmdRetStr.Mid(StartPos,EndPos);
			StartPos=EndPos+2;
			if(Temp.Find(_T("daemon")) != -1 || Temp.Find(_T("List of devices attached")) != -1)
				continue;

			sPhoneStatus Status;
			Status.m_IsOffLine = FALSE;
			if(Temp.Find(_T("offline")) != -1 )
				Status.m_IsOffLine = TRUE;

			int TempPos = Temp.Find(_T("\t"));
			if(TempPos != -1)
			{
				Temp=Temp.Left(TempPos);
				Status.m_PhoneDesId = Temp;
				DeviceList.push_back(Status);
			}
		}
		else
			break;
	}
	
	CString strTmp;
	strTmp.Format(_T("[CMainDlg::GetAndroidDeviceList]  Get Adb DeviceListOK[%d]\r\n"), DeviceList.size());
	XWriteEventLog(strTmp);
}

//��ȡAndroid�豸�б�
void GetApplicationPath(CString& Path)
{
}


//д�˲�����־�ļ�
void WriteLog(const char* Format,...)
{
}

//д�˲�����־�ļ�
void WriteLog(const wchar_t* Format,...)
{
}

//���ַ���ת��Ϊunicode
wchar_t* TransUtf8CharToUncodeWchar(char *utf8)
{
	int len=MultiByteToWideChar(CP_UTF8, 0,utf8, -1, NULL,0);   
	wchar_t* buffer = new wchar_t[len+1];
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, buffer, len);
	buffer[len]='\0';
	return buffer;
}

//���ַ���ת��Ϊutf-8
char* TransUncodeWcharToUtf8Char(const wchar_t *unicode)
{
	 int len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, 0, 0, 0, 0 );
	 char* buffer = new char[len+1];
	 WideCharToMultiByte(CP_UTF8, 0, unicode, -1, buffer,len, 0, 0 );
	 buffer[len] = '\0';
	 return buffer;
}



//��ȡ����ĸ ���� 1 ����ĸ 0 ȫ��ĸ
CString GetFirstLetter(CString Name, int nType /*= 1*/)
{
	std::wstring TempName = std::wstring(Name.GetBuffer());
	std::wstring Result;
	Name.ReleaseBuffer();

	//��CString ת��Ϊ string

	GenFirstPYLetter(TempName,Result);

	//���������ַ�
	if (Name == _T("��"))
		Result = _T("YUN");

	CString FirstLetter;
	FirstLetter = CString(Result.c_str());
	if (nType == 1 && FirstLetter.GetLength() > 1)
	{
		FirstLetter = FirstLetter.Left(1);		
	}
	FirstLetter.MakeUpper();

	return FirstLetter;

}
