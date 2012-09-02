// MySocket.h: interface for the CBaseSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSOCKET_H__B3A51A96_FEC5_4473_B9FA_AF7902C946D6__INCLUDED_)
#define AFX_MYSOCKET_H__B3A51A96_FEC5_4473_B9FA_AF7902C946D6__INCLUDED_
//#include "ReadOrWriteInfo.h"

//#include "StdAfx.h"

#if _MSC_VER > 1000

#pragma once
#endif // _MSC_VER > 1000

#define MAXCOUNT 100
#define QUEUE_SIZE 5

#include "../Include/DataDefine.h"

//const int WINSOCK_VERSION = 0x0101;	

class CBaseSocket  
{
private:
	///static void DesInstance();
////	/*static*/ int addlen;
/////*static*/ sockaddr_in  m_oServerAddress;

	int m_addlen;
	sockaddr_in  m_oServerAddress;

public:
	////static CBaseSocket * GetInstance();


	//  ��ȡ��δʹ�õ� Socket �����
	//int GetCount();

	//  �ر� Socket ����
	int CloseSocket(SOCKET* SocketIn);

	//  ������Ϣ����
	int RecvMsg(SOCKET *Socket_Recv,BYTE* Recvstr,long RecvstrLegth);
	int RecvMsg(SOCKET *Socket_Recv,CString& Recvstr,FunctionSocketCallBack CallBack=NULL);

	//  ������Ϣ����
	int SendMsg(SOCKET* Socket_Send,CString  Sendstr);


	//  �󶨲����� Socket ����
	int BindAndListenSocket(SOCKET* Socket_Server,unsigned short nProt);

	//  ���� Socket �����ӵ�����������
	int ConnectToServer(SOCKET* Socket_Client,int nProt,CString  sIPAddress);

	//  ��ʼ�������� Socket ����
	int InitializeAndCreateSocket(SOCKET* SocketIn,bool IsSetWaitOutTime=true);
	
	int NoNagleCreateSocket(SOCKET* SocketIn);

	CBaseSocket();
	virtual ~CBaseSocket();

	protected:
	// CUserSocketMain �ľ�̬�����
	////static CBaseSocket * m_pInstance;
	 CString   m_strCallFuncName;

public:
	 int SetCallFuncName(CString strCallFuncName);

};

//  �������߳�
//UINT ServerThread(LPVOID P);

#endif // !defined(AFX_MYSOCKET_H__B3A51A96_FEC5_4473_B9FA_AF7902C946D6__INCLUDED_)
