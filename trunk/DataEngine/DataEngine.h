// DataEngine.h : DataEngine DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDataEngineApp
// �йش���ʵ�ֵ���Ϣ������� DataEngine.cpp
//

class CDataEngineApp : public CWinApp
{
public:
	CDataEngineApp();

// ��д
public:
	virtual BOOL InitInstance();

	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
};


