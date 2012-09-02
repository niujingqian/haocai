/***********************************************************************************
* ˵��      ��  CMemoryPoolΪ�ڴ�أ������ڴ�ķ���                                *
* ������    ��  ̷����                                                             *
* ��������  ��  2011-9-8                                                           *
***********************************************************************************/

#pragma once
//���ٻ������ṹ
struct sMemory
{
	char*		m_Buffer;	//������
	DWORD		m_Bytes;	//���������ݵ��ֽ���
};

//���ٻ�����������Ϣ�ṹ
struct sMemoryInfo
{
	sMemory			m_Memory;	//������
	DWORD			m_Size;		//��������С
	volatile long	m_Reference;//���ü�����
};

/********************************************************************
						�����ڴ��
********************************************************************/
class CMemoryPool
{
public:
	
	//�����ڴ��
	static void CreateMemPool();

	//ɾ���ڴ��
	static void DeleteMemPool();

	//��ȡ������
	static sMemory* GetMemory(DWORD Size);

	//�ͷŻ�����
	static void FreeMemory(sMemory* Memory);

	//��ȡ��������С
	static DWORD GetMemorySize(sMemory* Memory)
	{ 
		if(Memory==NULL) return 0;
		sMemoryInfo *MemoryInfo=CONTAINING_RECORD(Memory,sMemoryInfo,m_Memory);
		return MemoryInfo->m_Size;									
	};

	//���ü�����+1
	static void IncReference(sMemory* Memory)
	{ 
		InterlockedIncrement(&((sMemoryInfo*)Memory)->m_Reference);
	};

private:

	//�ڴ��ջ�ṹ
	struct sMemoryStackList
	{
		sMemoryInfo			**m_Stack;		//�ڴ��ջ
		volatile int		m_StackTop;		//��ջ��
		CRITICAL_SECTION	m_StackLock;	//ջ��
	};

	//����
	CMemoryPool(void){};

	//����
	~CMemoryPool(void){};

	static sMemoryStackList		*m_MemoryStackList;	//�ڴ��ջ�б�
};
