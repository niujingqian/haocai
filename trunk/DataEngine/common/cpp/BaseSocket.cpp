// MySocket.cpp: implementation of the CBaseSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../Include/BaseSocket.h"
#include "../Include/CommonFunction.h"
#define XWriteEventLog TRACE

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
////static int addlen;
////static sockaddr_in ServerAddress;
////static SOCKET Server_Socket[MAXCOUNT];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

////CBaseSocket* CBaseSocket::m_pInstance = 0;
////
////CBaseSocket* CBaseSocket::GetInstance()
////{
////	if( m_pInstance == 0)
////	{
////			m_pInstance = new CBaseSocket();
////	}
////
////	return m_pInstance ;
////}

////void  CBaseSocket::DesInstance()
////{
////
////	if( m_pInstance != NULL)
////	{
////		delete m_pInstance;
////		m_pInstance = NULL;
////
////	}
////}


CBaseSocket::CBaseSocket()
{

	////WORD wVersionRequested;
	////WSADATA wsaData;
	////int err;

	////wVersionRequested=MAKEWORD(1,1);  // for mobile it 1.1 C Sock
	////err=WSAStartup(wVersionRequested,&wsaData);
	////if (LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	////{
	////	WSACleanup();
	////}
	
		//  ��ʼ�� Socket ����
	////for (int Loop = 0;Loop < MAXCOUNT;Loop++)
	////	Server_Socket[Loop] = NULL;

	m_strCallFuncName = _T("");
}

CBaseSocket::~CBaseSocket()
{
		///WSACleanup();
		//m_pInstance = NULL;
}

/***********************************************************
*  ���ܣ���ʼ�������� Socket
*  ���� 0 ��Socket
*  ����ֵ�������� 0 �ɹ�
*                 1 ��ʼ�������� Socket ʱ�������쳣
*                 2 ���� Socket ʧ��
*				 -1 ����װ�� Windows Sockets DLL
*                -2 ��ȡ������ʧ��
************************************************************/
	/*  ����WSAStartup(WORD wVersionRequested,LPWSADATA lpWSAData)������ʼ�� Winsock
	
	������   
	wVersionRequested	��ʾ��ʹ�õ�Windows Sockets API �汾
	lpWSAData				ָ���WSADATA ���ϵ�ָ��
	  
	����ֵ�� �ɹ����� 0 ��
		
	ʧ�ܷ�������ֵ��
	WSASYSNOTREADY��     ��ʾ�����豸û��׼����
	WSAVERNOTSUPPORTED�� Winsock  �İ汾��Ϣ�Ų�֧��
	WSAEINPROGRESS��     һ������ʽ��Winsock1.1 �����ڽ�����
	WSAEPROCLIM��        �Ѿ��ﵽ Winsock ʹ����������
    WSAEFAULT:           lpWSAData ����һ����Ч��ָ��*/

int CBaseSocket::InitializeAndCreateSocket(SOCKET* SocketIn,bool IsSetWaitOutTime)
{
	WSADATA wsaData;
	char chLocalInfo[64];
	
	try
	{

		if (gethostname(chLocalInfo, sizeof(chLocalInfo)))
		{
			int iR = WSAGetLastError();
			return -2;
		}

		//  ���� socket
		*SocketIn = socket(PF_INET,SOCK_STREAM,0);
			
		if (*SocketIn == INVALID_SOCKET)
		{
			return -3;
		}

		int nRet = 0x00;
		int nTimeOut = 10*1000;
		if(IsSetWaitOutTime)
		{
			nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
			if( SOCKET_ERROR== nRet)
			{
				return -4;
			}
			nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
			if( SOCKET_ERROR ==  nRet)
			{
				return -5;
			}	

		}
		else
		{
			nTimeOut = 40*1000;
			
			nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
			if( SOCKET_ERROR== nRet)
			{
				return -4;
			}
			nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
			if( SOCKET_ERROR ==  nRet)
			{
				return -5;
			}	
		}

	
		//IPPROTO_TCP;
		BOOL nCloseNagle = TRUE;
		nRet = ::setsockopt(*SocketIn, IPPROTO_TCP, TCP_NODELAY, (char*)&nCloseNagle, sizeof(nCloseNagle) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -6;
		}	

		///// SO_DONTLINER
		//BOOL nNoDelay = TRUE;
		//nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_DONTLINGER, (char*)&nNoDelay, sizeof(nNoDelay) );
		//if( SOCKET_ERROR ==  nRet)
		//{
		//	return -7;
		//}	
		
		linger m_sLinger;
		m_sLinger.l_onoff = 1;  // (��closesocket()����,���ǻ�������û������ϵ�ʱ��������)
		m_sLinger.l_linger = 3; // (��������ʱ��Ϊ3��)
		nRet = setsockopt(*SocketIn,SOL_SOCKET,SO_LINGER, (const char*)&m_sLinger,sizeof(linger)); 
		if( SOCKET_ERROR ==  nRet)
		{
			return -7;
		}

		/// SO_REUSEADDR
		BOOL nReUseAddress = TRUE;
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_REUSEADDR, (char*)&nReUseAddress, sizeof(nReUseAddress) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -8;
		}	

	}  //  End_try
	catch (...)
	{
		return 1;
	}

//  ���ɹ����� 0
return 0;
}


int CBaseSocket::NoNagleCreateSocket(SOCKET* SocketIn)
{
	WSADATA wsaData;
	char chLocalInfo[64];
	
	try
	{

		if (gethostname(chLocalInfo, sizeof(chLocalInfo)))
		{
			int iR = WSAGetLastError();
			return -2;
		}

		//  ���� socket
		*SocketIn = socket(PF_INET,SOCK_STREAM,0);
			
		if (*SocketIn == INVALID_SOCKET)
		{
			return -3;
		}

		int nTimeOut = 30*1000;
		int nRet = 0x00;
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
		if( SOCKET_ERROR== nRet)
		{
			return -4;
		}
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -5;
		}		

		//IPPROTO_TCP;
		BOOL nCloseNagle = TRUE;
		nRet = ::setsockopt(*SocketIn, IPPROTO_TCP, TCP_NODELAY, (char*)&nCloseNagle, sizeof(nCloseNagle) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -6;
		}		
		///// SO_DONTLINER
		//BOOL nNoDelay = TRUE;
		//nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_DONTLINGER, (char*)&nNoDelay, sizeof(nNoDelay) );
		//if( SOCKET_ERROR ==  nRet)
		//{
		//	return -7;
		//}		

		linger m_sLinger;
		m_sLinger.l_onoff = 1;  // (��closesocket()����,���ǻ�������û������ϵ�ʱ��������)
		m_sLinger.l_linger = 3; // (��������ʱ��Ϊ3��)
		nRet = setsockopt(*SocketIn,SOL_SOCKET,SO_LINGER, (const char*)&m_sLinger,sizeof(linger)); 
		if( SOCKET_ERROR ==  nRet)
		{
			return -7;
		}


		/// SO_REUSEADDR
		BOOL nReUseAddress = TRUE;
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_REUSEADDR, (char*)&nReUseAddress, sizeof(nReUseAddress) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -8;
		}

		BOOL nDebug = TRUE;
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_DEBUG, (char*)&nDebug, sizeof(nDebug) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -9;
		}	

		/////��������ģʽ
		//u_long iMode = 1;
		//ioctlsocket(*SocketIn, FIONBIO, &iMode);


	}  //  End_try
	catch (...)
	{
		return 1;
	}

//  ���ɹ����� 0
return 0;
}

/***********************************************************
*  ���ܣ����� Socket �����ӵ�������
*  ���� 0 ���ͻ��� Socket
*  ���� 1 ���˿ں�
*  ���� 2 ��IP ��ַ
*  ����ֵ�������� 0 �ɹ�
*                 1 ���ӷ�����ʱ�������쳣
*				 -1 �Ƿ� IP ��ַ
*                -2 ϵͳ���ӷ�����ʧ��
************************************************************/
int CBaseSocket::ConnectToServer(SOCKET* Socket_Client,int nProt, CString  sIPAddress)
{
	DWORD dwIPAddr;
	SOCKADDR_IN sockAddr;
	CString strLogMsg;

	try
	{
		char * TempIP= TransUncodeWcharToUtf8Char(sIPAddress.GetBuffer());

		//  ��֤IP ��ַ����������Ϣ��ʾ����ֹ	
		if((dwIPAddr = inet_addr(TempIP)) == INADDR_NONE)
		{
			delete []TempIP;
			return -1;
		}
		delete []TempIP;
		
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(nProt);
		sockAddr.sin_addr.S_un.S_addr = dwIPAddr;
		
		//  ���� connect(m_hSocket,(LPSOCKADDR)&sockAddr,sizeof(sockAddr)) ��������ͨ�Ŷ���
		/// ������ʧ��ʱ����SOCKET_ERROR
		int nConnect = connect(*Socket_Client,(LPSOCKADDR)&sockAddr,sizeof(sockAddr));

		if(nConnect)
		{
			int nRet = GetLastError();
			////strLogMsg.Format(_T("[CBaseSocket::ConnectToServer] ϵͳ���ӷ�����ʧ�� [%d]\r\n"), nRet);
			////XWriteEventLog(m_strCallFuncName + strLogMsg );

			return -2;
		}
	}  //  End_try
	catch (...) 
	{
			strLogMsg.Format(_T("[CBaseSocket::ConnectToServer] ���ӷ�����ʱ�������쳣 [%d]\r\n"),GetLastError());
			XWriteEventLog(m_strCallFuncName + strLogMsg);
		return 1;
	}
return 0;
}

/***********************************************************
*  ���ܣ��󶨲����� Socket
*  ���� 0 ���������� Socket
*  ���� 1 ���˿ں�
*  ����ֵ�������� 0 �ɹ�
*                 1 �󶨲����� Socket ʱ�������쳣
*				 -1 �� Socket ʧ��
*                -2 ����������ʧ��
************************************************************/
int CBaseSocket::BindAndListenSocket(SOCKET* Socket_Server, unsigned short nProt)
{
    u_long  ul = 1;  


	//  ���ض˿ں���Ϊ 8802
	try
	{
		//  ���÷������˵�ַ
		m_oServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);   
		m_oServerAddress.sin_family = AF_INET;
		m_oServerAddress.sin_port = htons(nProt);
		m_addlen = sizeof(m_oServerAddress);
		
		//  ��
		if(bind(*Socket_Server, (sockaddr*)&m_oServerAddress, m_addlen) == SOCKET_ERROR)
		{
		    //CReadOrWriteInfo::WriteInfoToiniFile("SOCKET","�� Socket ʧ��!",2);
			return -1;
			
		}
		
		//���÷�������ʽ����   
		//ioctlsocket(*Socket_Server,FIONBIO, (u_long*)&ul);  
		
		//  ���� socket
		if (listen(*Socket_Server, QUEUE_SIZE) == SOCKET_ERROR)
		{
			//  ������ͼ���е���ʾ������ MO ��Ϣ���������
		    //CReadOrWriteInfo::WriteInfoToiniFile("SOCKET","����������ʧ��!",2);
			return -2;
		}
		
		else
		{    
			AfxMessageBox(_T("ϵͳ��ʼ����!"));
			//  �����������߳�
            //AfxBeginThread(&ServerThread,Socket_Server,NULL);
			return 0;

		}

	}  //  End_try
	catch (...) 
	{
		//CReadOrWriteInfo::WriteInfoToiniFile("SOCKET","�󶨼��� Socket ʱ�������쳣!",1);
		return 1;
	}

}

/***********************************************************
*  ���ܣ�������Ϣ
*  ���� 0 ������ Socket
*  ���� 1 �����͵���Ϣ
*  ����ֵ�������� 0 �ɹ�
*                 1 ������Ϣʱ�������쳣
*				 -1 ������Ϣʱ����
************************************************************/
int CBaseSocket::SendMsg(SOCKET *Socket_Send, CString  Sendstr)
{
	// TODO: Add your control notification handler code here
	char buffer[65536] = {0};    ///64K        
	int Len;
	CString  strLogMsg;
	int nRet = 0x00;
	char* TempData = NULL;

	try
	{
		
		TempData =TransUncodeWcharToUtf8Char(Sendstr.GetBuffer());
		Sendstr.ReleaseBuffer();
		Len=strlen(TempData);
		
		if(send(*Socket_Send,TempData,Len,0) == SOCKET_ERROR)
		{
			delete []TempData;
			return -1;
		}
	
		delete [] TempData;

		//  ��������Ϣ��ȷʱ���� 0
		return 0;
	}
	catch (...) 
	{
		if(TempData != NULL)
			delete [] TempData;
		return -1;
	}
			
}



/***********************************************************
*  ���ܣ�������Ϣ
*  ���� 0 ������ Socket
*  ���� 1 �����͵���Ϣ
*  ����ֵ�������� 0 �ɹ�
*                 1 ������Ϣʱ�������쳣
*				 -1 ������Ϣʱ����
************************************************************/
int CBaseSocket::RecvMsg(SOCKET *Socket_Recv, BYTE* Recvstr,long RecvstrLegth)
{
	int nRet = 0x00;
	long ReveLength = 0;
	CString  strLogMsg;
	try
	{

		ReveLength = recv(*Socket_Recv,(LPSTR)Recvstr,RecvstrLegth,0);
		
		//����recv������������
		if(ReveLength == SOCKET_ERROR)
		{
			//nRet  = GetLastError();
			//strLogMsg.Format(_T("[CBaseSocket::RecvMsg]  ������Ϣʱ����[%d]\r\n"), nRet);
			//XWriteEventLog(m_strCallFuncName + strLogMsg);

			return SOCKET_ERROR;
		}
		return ReveLength;
	}
	catch (...)
	{
		nRet  = GetLastError();
		strLogMsg.Format(_T("[CBaseSocket::RecvMsg]  ������Ϣʱ�������쳣[%d]\r\n"), nRet);
		XWriteEventLog(m_strCallFuncName + strLogMsg);

		return SOCKET_ERROR;
	}
}

int CBaseSocket::RecvMsg(SOCKET *Socket_Recv,CString& Recvstr,FunctionSocketCallBack CallBack)
{
	while(true)
	{
		char buffer[1024*10+1];
		memset(buffer,'\0',1024*10+1);
		int RecvByte = recv(*Socket_Recv,buffer,1024*10,0);
		if(RecvByte != -1 && RecvByte != 0)
		{
		
			wchar_t* Temp=TransUtf8CharToUncodeWchar(buffer);
			Recvstr+=CString(Temp);
			delete []Temp;
			if(Recvstr.Find(_T("</res>")) == -1)
				continue;

			if(CallBack != NULL)
			{
				CallBack(Recvstr);
				if(Recvstr.Find(_T("<value>end</value>")) != -1 && Recvstr.Find(_T("<name>flag</name>")) != -1 || Recvstr.Find(_T("<name>error</name>")) != -1 )
					break;

				Sleep(1000);
				Recvstr.Empty();
				char ContinueChar='R';
				send(*Socket_Recv,&ContinueChar,1,0);
		
			}
		}

		else
			break;
	}

	if(Recvstr.IsEmpty())
		return 0;
	return 1;
}

/***********************************************************
*  ���ܣ��ر� Socket �̿�����
*  ����0��
*  ����ֵ��0  �ر� Socket �ɹ�
*		  -1  �ر� Socket ʱ�������쳣
************************************************************/
int CBaseSocket::CloseSocket(SOCKET *SocketIn)
{
	CString strLogMsg;
	int nRet  = -1;
	try
	{
		//  �ر� Socket �̿�����
		nRet = closesocket(*SocketIn);

		//strLogMsg.Format(_T("[CBaseSocket::CloseSocket]  CloseSocket[%d]\r\n"), nRet);
		//XWriteEventLog(strLogMsg);
		return nRet;
	}
	catch (...)
	{
		nRet = ::GetLastError();
		strLogMsg.Format(_T("[CBaseSocket::CloseSocket]  �ر� Socket ʱ�������쳣[%d]\r\n"), nRet);
		XWriteEventLog(m_strCallFuncName + strLogMsg);
		return -1;
	}
}

/***********************************************************
*  ���ܣ���û�û��ʹ�õ� Socket�����
*  ����ֵ��������δʹ�õ� Socket �����
*		   -1  û�п��е� Socket �����
************************************************************/
////int CBaseSocket::GetCount()
////{
////	for (int Loop = 0;Loop < MAXCOUNT;Loop++)
////	{
////		if (Server_Socket[Loop] == NULL)
////			return Loop;
////	}
////	return -1;
////}


/*
 ����FormatMessage�����õ����������ı���ʾ����������������GetLastError()��á���_WINDOWS��
 */
//char * ErrorToString()
//{
//	DWORD nErrorNo = GetLastError ( ); // �õ��������
//	 LPSTR lpBuffer;    
//	 FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER  |
//	 FORMAT_MESSAGE_IGNORE_INSERTS  |
//	 FORMAT_MESSAGE_FROM_SYSTEM,
//	 NULL,
//	nErrorNo, // ���˴�����룬ͨ���ڳ����п��� GetLastError()��֮
//	LANG_NEUTRAL,
//	 (LPTSTR) & lpBuffer,
//	0 ,
//	NULL );
//	CString strErrorCause  =  lpBuffer  ?  _T(lpBuffer) : _T( " Sorry, cannot find this error info. " );
//	UpdateData (FALSE);
//	//  Free the buffer.
//	LocalFree (lpBuffer); 
//}


int CBaseSocket::SetCallFuncName(CString strCallFuncName)
{
		m_strCallFuncName = strCallFuncName;
		return 0;
 }

