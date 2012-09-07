/***********************************************************************************
* ˵��      ��  CMessageCenterΪ��Ϣ�������ģ����ù۲���ģʽ                       *
* ������    ��  ̷����                                                             *
* ��������  ��  2011-9-8                                                           *
***********************************************************************************/

#pragma once
#include "memorypool.h"
#include "messageDefine.h"

const	int		WM_SUB_THREAD_MSG	=	WM_USER+100;	//���߳���Ϣ(ͨ��PostMsg���͵���Ϣ)
const	int		WM_SUB_THREAD_DATA	=	WM_USER+101;	//���߳�����(ͨ��PostData���͵���Ϣ)

#define EXPORT_CLASS __declspec(dllexport)


//��Ϣ����ӿ�
interface EXPORT_CLASS IMessageHandle
{
	virtual void OnMessage(eMessage Message,DWORD SystemMsg=0,WPARAM wParam=0,LPARAM lParam=0)=0;
};

//��Ϣ����
class EXPORT_CLASS CMessageCenter
{
public:

	static void Init();

	static void Delete();

	//ע����Ϣ������
	static void RegisterMsgHandle(IMessageHandle* Handle,eMessage Message);

	//ע����Ϣ������
	static void LogoutMsgHandle(IMessageHandle* Handle,eMessage Message);

	//ת��ϵͳ��Ϣ(���û����Ϣ�����ߣ�����FALSE�����򷵻�TRUE)
	static BOOL SendSystemMsg(DWORD Message,WPARAM wParam,LPARAM lParam);

	//������Ϣ(���û����Ϣ�����ߣ�����FALSE�����򷵻�TRUE�����߳���ʹ��)
	static BOOL SendMsg(eMessage Message,WPARAM wParam=0,LPARAM lParam=0);

	//��������(���û����Ϣ�����ߣ�����FALSE�����򷵻�TRUE�����߳���ʹ��)
	static BOOL SendData(eMessage Message,sMemory* Param,BOOL Racord=FALSE);
	
	//Ͷ����Ϣ(���߳���ʹ��)
	static void PostMsg(eMessage Message,WPARAM Param=0);

	//Ͷ������(���߳���ʹ��)
	static void PostData(eMessage Message,sMemory* Param);

private:

	//��Ϣ���ڵĹ���
	static LRESULT WINAPI MsgWinProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);

	//��¼ָ��
	static void RecordMsg(sMemory* Param);

	//ɾ����¼
	static void DeleteRecord(sMemory* Param);

	//��Ϣ�������ṹ
	struct sMessageItem
	{
		int					m_HandleCount;	//�����
		IMessageHandle**	m_HandleList;	//���ָ���б�
	};

	//��Ϣ��¼�ṹ
	struct sMsgRecord
	{
		sMemory*	m_Param;
		sMsgRecord*	m_Next;
	};

	static sMsgRecord*			m_RecordHead;	//��¼ͷ
	static sMsgRecord*			m_RecordEnd;	//��¼β
	static sMsgRecord*			m_FreeHead;		//����ͷ
	static CRITICAL_SECTION		m_RecordLock;	//��¼��

	static	sMessageItem		m_MessageList[MRSSAGE_TYPE_COUNT];	//��Ϣ�б�
	static	HWND				m_MsgWnd;		//���ڽ������߳���Ϣ�Ĵ���
};
