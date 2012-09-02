// DataEngine.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "DataEngine.h"
#include "./common/Include/MessageCenter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CDataEngineApp

BEGIN_MESSAGE_MAP(CDataEngineApp, CWinApp)
END_MESSAGE_MAP()


// CDataEngineApp ����

CDataEngineApp::CDataEngineApp()
{
	
}


// Ψһ��һ�� CDataEngineApp ����

CDataEngineApp theApp;



BOOL CDataEngineApp::InitInstance()
{
	CWinApp::InitInstance();

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested=MAKEWORD(1,1);  // for mobile it 1.1 C Sock
	err=WSAStartup(wVersionRequested,&wsaData);
	if (LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();
	}

	CMemoryPool::CreateMemPool();
	CMessageCenter::Init();
	
	return TRUE;
}

int CDataEngineApp::ExitInstance()
{
	WSACleanup();
	CMemoryPool::DeleteMemPool();
	CMessageCenter::Delete();
	return CWinApp::ExitInstance();
}
