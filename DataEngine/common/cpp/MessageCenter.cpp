#include "StdAfx.h"
#include "../Include/MessageCenter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const	WORD	HANDLELIST_ADD_STEP		=	5;	//����б���������

CMessageCenter::sMessageItem	CMessageCenter::m_MessageList[MRSSAGE_TYPE_COUNT];
CMessageCenter::sMsgRecord*		CMessageCenter::m_RecordHead=NULL;	
CMessageCenter::sMsgRecord*		CMessageCenter::m_RecordEnd=NULL;	
CMessageCenter::sMsgRecord*		CMessageCenter::m_FreeHead=NULL;		
CRITICAL_SECTION				CMessageCenter::m_RecordLock;
HWND							CMessageCenter::m_MsgWnd=NULL;

//��ʼ��
void CMessageCenter::Init()
{
	if(m_MsgWnd==NULL)
	{
		WNDCLASSEX   WndClass;
		WndClass.cbSize  = sizeof(WNDCLASSEX);     
		WndClass.style = 0;   
		WndClass.lpfnWndProc = (WNDPROC)MsgWinProc;   
		WndClass.cbClsExtra = 0;   
		WndClass.cbWndExtra = 0;   
		WndClass.hInstance = (HINSTANCE)GetModuleHandle(0);   
		WndClass.hIcon = 0;   
		WndClass.hCursor = 0; 
		WndClass.hbrBackground = 0;   
		WndClass.lpszMenuName = 0;   
		WndClass.lpszClassName = _T("ThreadMsgWnd");   
		WndClass.hIconSm = 0;   

		RegisterClassEx(&WndClass);
		m_MsgWnd =CreateWindow(_T("ThreadMsgWnd"),NULL,WS_OVERLAPPEDWINDOW,0,0,0,0,NULL,0,(HINSTANCE)GetModuleHandle(0),0);   
	  

		InitializeCriticalSection(&m_RecordLock);
		memset(m_MessageList,0,sizeof(sMessageItem)*MRSSAGE_TYPE_COUNT);
	}
}

//ɾ��
void CMessageCenter::Delete()
{
	if(m_MsgWnd!=NULL)
	{
		for(int n=0;n<MRSSAGE_TYPE_COUNT;n++)
		{
			m_MessageList[n].m_HandleCount=0;
			if(m_MessageList[n].m_HandleList)
			{
				delete[] m_MessageList[n].m_HandleList;
				m_MessageList[n].m_HandleList=NULL;
			}
		}

		EnterCriticalSection(&m_RecordLock);
		
		while(m_RecordHead)
		{
			sMsgRecord* Temp=m_RecordHead->m_Next;
			CMemoryPool::FreeMemory(m_RecordHead->m_Param);
			delete m_RecordHead;
			m_RecordHead=Temp;
		}

		while(m_FreeHead)
		{
			sMsgRecord* Temp=m_FreeHead->m_Next;
			delete m_FreeHead;
			m_FreeHead=Temp;
		}

		LeaveCriticalSection(&m_RecordLock);
		DeleteCriticalSection(&m_RecordLock);
		
		UnregisterClass(_T("ThreadMsgWnd"),(HINSTANCE)GetModuleHandle(0));
		DestroyWindow(m_MsgWnd);
		m_MsgWnd=NULL;
	}
}

//ע����Ϣ������
void CMessageCenter::RegisterMsgHandle(IMessageHandle* Handle,eMessage Message)
{
	ASSERT(Handle!=NULL);

	//����Ƿ��ظ�ע��
	for(int n=0;n<m_MessageList[Message].m_HandleCount;n++)
	{
		if(m_MessageList[Message].m_HandleList[n]==Handle)
			return;
	}

	//�������б�ռ�
	if(m_MessageList[Message].m_HandleCount%HANDLELIST_ADD_STEP==0)
	{
		IMessageHandle** NewList=new IMessageHandle*[m_MessageList[Message].m_HandleCount+HANDLELIST_ADD_STEP];
		if(NewList==NULL)
			return;
		if(m_MessageList[Message].m_HandleList)
		{
			memcpy(NewList,m_MessageList[Message].m_HandleList,sizeof(IMessageHandle*)*m_MessageList[Message].m_HandleCount);
			delete[] m_MessageList[Message].m_HandleList;
		}
		memset(NewList+m_MessageList[Message].m_HandleCount,0,sizeof(IMessageHandle*)*HANDLELIST_ADD_STEP);
		m_MessageList[Message].m_HandleList=NewList;
	}

	//ע��
	m_MessageList[Message].m_HandleList[m_MessageList[Message].m_HandleCount]=Handle;
	m_MessageList[Message].m_HandleCount++;
}

//ע����Ϣ������
void CMessageCenter::LogoutMsgHandle(IMessageHandle* Handle,eMessage Message)
{
	ASSERT(Handle!=NULL);

	for(int n=0;n<m_MessageList[Message].m_HandleCount;n++)
	{
		if(m_MessageList[Message].m_HandleList[n]==Handle)
		{
			if(n<m_MessageList[Message].m_HandleCount-1)
				memcpy(m_MessageList[Message].m_HandleList+n,m_MessageList[Message].m_HandleList+n+1,sizeof(IMessageHandle*)*(m_MessageList[Message].m_HandleCount-n-1));
			m_MessageList[Message].m_HandleCount--;
		}
	}
}

//��Ϣ���ڵĹ���
LRESULT WINAPI CMessageCenter::MsgWinProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	switch(Msg)
	{
	case WM_SUB_THREAD_MSG:
		SendMsg((eMessage)wParam,lParam);
		break;
	case WM_SUB_THREAD_DATA:
		SendData((eMessage)wParam,(sMemory*)lParam,TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,Msg,wParam,lParam);
}

//ת��ϵͳ��Ϣ
BOOL CMessageCenter::SendSystemMsg(DWORD Message,WPARAM wParam,LPARAM lParam)
{
	BOOL	Send=FALSE;
	for(int n=0;n<m_MessageList[MSG_SYSTEM].m_HandleCount;n++)
	{
		if(m_MessageList[MSG_SYSTEM].m_HandleList[n]!=NULL)
		{
			m_MessageList[MSG_SYSTEM].m_HandleList[n]->OnMessage(MSG_SYSTEM,Message,wParam,lParam);
			Send=TRUE;
		}
	}	
	return Send;
}

//������Ϣ
BOOL CMessageCenter::SendMsg(eMessage Message,WPARAM wParam,LPARAM lParam)
{
	BOOL	Send=FALSE;
	for(int n=0;n<m_MessageList[Message].m_HandleCount;n++)
	{
		if(m_MessageList[Message].m_HandleList[n]!=NULL)
		{
			m_MessageList[Message].m_HandleList[n]->OnMessage(Message,0,wParam,lParam);
			Send=TRUE;
		}
	}
	return Send;
}

//������Ϣ
BOOL CMessageCenter::SendData(eMessage Message,sMemory* Param,BOOL Racord)
{
	ASSERT(Param!=NULL);

	//�������Ϣ����¼������ôɾ����¼
	if(Racord && Param)
		DeleteRecord(Param);

	//��ֹ���类ɾ��
	if(Param)
		CMemoryPool::IncReference(Param);	
	
	//��Ϣ�ɷ�
	BOOL	Send=FALSE;
	for(int n=0;n<m_MessageList[Message].m_HandleCount;n++)
	{
		if(m_MessageList[Message].m_HandleList[n]!=NULL)
		{
			if(Param)
				CMemoryPool::IncReference(Param);
			m_MessageList[Message].m_HandleList[n]->OnMessage(Message,0,(WPARAM)Param);
			Send=TRUE;
		}
	}
	
	if(Param)
		CMemoryPool::FreeMemory(Param);

	return Send;
}

//Ͷ������(���߳���ʹ��)
void CMessageCenter::PostData(eMessage Message,sMemory* Param)
{
	ASSERT(Param!=NULL);

	RecordMsg(Param);
	::PostMessage(m_MsgWnd,WM_SUB_THREAD_DATA,(WPARAM)Message,(LPARAM)Param);
}

//Ͷ����Ϣ(���߳���ʹ��)
void CMessageCenter::PostMsg(eMessage Message,WPARAM Param)
{
	::PostMessage(m_MsgWnd,WM_SUB_THREAD_MSG,(WPARAM)Message,(LPARAM)Param);
}

//��¼��Ϣ
void CMessageCenter::RecordMsg(sMemory* Param)
{
	ASSERT(Param!=NULL);

	EnterCriticalSection(&m_RecordLock);
	
	sMsgRecord* Temp=NULL;
	if(m_FreeHead)
	{
		Temp=m_FreeHead;
		m_FreeHead=Temp->m_Next;
	}
	else
	{
		Temp=new sMsgRecord;
		if(Temp==NULL)
		{
			LeaveCriticalSection(&m_RecordLock);
			return;
		}
	}

	Temp->m_Param=Param;
	Temp->m_Next=NULL;
	if(m_RecordEnd)
	{
		m_RecordEnd->m_Next=Temp;
		m_RecordEnd=Temp;
	}
	else
		m_RecordEnd=Temp;
	if(m_RecordHead==NULL)
		m_RecordHead=m_RecordEnd;

	LeaveCriticalSection(&m_RecordLock);
}

//ɾ����¼
void CMessageCenter::DeleteRecord(sMemory* Param)
{
	EnterCriticalSection(&m_RecordLock);

	sMsgRecord* Pre=m_RecordHead;
	sMsgRecord* Cur=m_RecordHead;
	while(Cur)
	{
		if(Cur->m_Param==Param)
		{
			if(Pre==m_RecordHead)
			{
				m_RecordHead=Cur->m_Next;
				if(m_RecordHead==NULL)
					m_RecordEnd=NULL;
			}
			else
				Pre->m_Next=Cur->m_Next;

			Cur->m_Next=m_FreeHead;
			m_FreeHead=Cur;
			break;
		}
		else
		{
			Pre=Cur;
			Cur=Cur->m_Next;
		}
	}
	LeaveCriticalSection(&m_RecordLock);	
}