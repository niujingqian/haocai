// suoshui.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CsuoshuiApp:
// �йش����ʵ�֣������ suoshui.cpp
//

class CsuoshuiApp : public CWinApp
{
public:
	CsuoshuiApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CsuoshuiApp theApp;