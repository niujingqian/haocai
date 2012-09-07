#include "StdAfx.h"
#include "memorypool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int MAX_LIST_COUNT	=40;				//�����ڴ������
const int MAX_BLOCK_COUNT	=50;				//ÿ�������п���

const int MEM_DATUM_SIZE	=512;				//�ڴ��׼�ߴ�(�Ը�ֵ�ı��������ڴ����)
const int MAX_MEM_SIZE		=MAX_LIST_COUNT*MEM_DATUM_SIZE;	//�����������ߴ�

CMemoryPool::sMemoryStackList*	CMemoryPool::m_MemoryStackList=NULL;	//���ٻ����б�

//�����ڴ��
void CMemoryPool::CreateMemPool()
{
	if(m_MemoryStackList==NULL)
	{
		m_MemoryStackList=new sMemoryStackList[MAX_LIST_COUNT];
		if(m_MemoryStackList==NULL)
			return;

		for(int n=0;n<MAX_LIST_COUNT;n++)
		{
			m_MemoryStackList[n].m_Stack=new sMemoryInfo*[MAX_BLOCK_COUNT];
			memset(m_MemoryStackList[n].m_Stack,0,sizeof(sMemoryInfo*)*MAX_BLOCK_COUNT);
			m_MemoryStackList[n].m_StackTop=-1;
			InitializeCriticalSection(&m_MemoryStackList[n].m_StackLock);
		}
	}
}

//ɾ���ڴ��
void CMemoryPool::DeleteMemPool()
{
	if(m_MemoryStackList)
	{
		for(int n=0;n<MAX_LIST_COUNT;n++)
		{
			EnterCriticalSection(&m_MemoryStackList[n].m_StackLock);
			if(m_MemoryStackList[n].m_Stack)
			{
				for(int m=0;m<=m_MemoryStackList[n].m_StackTop;m++)
				{
					if(m_MemoryStackList[n].m_Stack[m])
					{
						if(m_MemoryStackList[n].m_Stack[m]->m_Memory.m_Buffer)
							delete[] m_MemoryStackList[n].m_Stack[m]->m_Memory.m_Buffer;
						delete m_MemoryStackList[n].m_Stack[m];
					}
				}
				delete[] m_MemoryStackList[n].m_Stack;
				m_MemoryStackList[n].m_Stack=NULL;
			}

			m_MemoryStackList[n].m_StackTop=-1;
			LeaveCriticalSection(&m_MemoryStackList[n].m_StackLock);

			DeleteCriticalSection(&m_MemoryStackList[n].m_StackLock);
		}
		delete[] m_MemoryStackList;
		m_MemoryStackList=NULL;
	}
}

//��ȡ�ڴ�
sMemory* CMemoryPool::GetMemory(DWORD Size)
{
	ASSERT(m_MemoryStackList!=NULL && Size>0);

	sMemoryInfo* MemoryInfo=NULL;
	if(Size>MAX_MEM_SIZE)
	{
		MemoryInfo=new sMemoryInfo;
		if(!MemoryInfo)
			return NULL;
		
		MemoryInfo->m_Memory.m_Buffer=new char[Size];
		if(!MemoryInfo->m_Memory.m_Buffer)
		{
			delete MemoryInfo;
			return NULL;
		}

		MemoryInfo->m_Size=Size;
	}
	else
	{
		int Index=(Size-1)/MEM_DATUM_SIZE;
		EnterCriticalSection(&m_MemoryStackList[Index].m_StackLock);
		if(m_MemoryStackList[Index].m_StackTop>=0)
		{
			MemoryInfo=m_MemoryStackList[Index].m_Stack[m_MemoryStackList[Index].m_StackTop];
			m_MemoryStackList[Index].m_StackTop--;
		}
		LeaveCriticalSection(&m_MemoryStackList[Index].m_StackLock);

		if(MemoryInfo==NULL)
		{
			MemoryInfo=new sMemoryInfo;
			if(!MemoryInfo)
				return NULL;

			MemoryInfo->m_Memory.m_Buffer=new char[(Index+1)*MEM_DATUM_SIZE];
			if(!MemoryInfo->m_Memory.m_Buffer)
			{
				delete MemoryInfo;
				return NULL;
			}

			MemoryInfo->m_Size=(Index+1)*MEM_DATUM_SIZE;
		}
	}

	MemoryInfo->m_Memory.m_Bytes=0;
	MemoryInfo->m_Reference=0;
	return &MemoryInfo->m_Memory;
}

//�ͷ��ڴ�
void CMemoryPool::FreeMemory(sMemory* Memory)
{
	ASSERT(m_MemoryStackList!=NULL && Memory!=NULL);

	sMemoryInfo *MemoryInfo=CONTAINING_RECORD(Memory,sMemoryInfo,m_Memory);
	if(InterlockedDecrement(&MemoryInfo->m_Reference)>0)
		return;	//��������δ�ͷ�ֱ���˳�

	if(MemoryInfo->m_Size>MAX_MEM_SIZE)
	{
		delete[] MemoryInfo->m_Memory.m_Buffer;
		MemoryInfo->m_Memory.m_Buffer=NULL;
		delete MemoryInfo;
		MemoryInfo=NULL;
	}
	else
	{
		int Index=(MemoryInfo->m_Size-1)/MEM_DATUM_SIZE;
		EnterCriticalSection(&m_MemoryStackList[Index].m_StackLock);
		if(m_MemoryStackList[Index].m_StackTop<MAX_BLOCK_COUNT-1)
		{
			m_MemoryStackList[Index].m_StackTop++;
			m_MemoryStackList[Index].m_Stack[m_MemoryStackList[Index].m_StackTop]=MemoryInfo;
			MemoryInfo=NULL;
		}
		LeaveCriticalSection(&m_MemoryStackList[Index].m_StackLock);
		
		if(MemoryInfo)
		{
			delete[] MemoryInfo->m_Memory.m_Buffer;
			MemoryInfo->m_Memory.m_Buffer=NULL;
			delete MemoryInfo;
			MemoryInfo=NULL;
		}
	}
}