// DlgDrawTiaoXing.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgDrawTiaoXing.h"


// CDlgDrawTiaoXing �Ի���

IMPLEMENT_DYNAMIC(CDlgDrawTiaoXing, CDialog)

CDlgDrawTiaoXing::CDlgDrawTiaoXing(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDrawTiaoXing::IDD, pParent)
{

}

CDlgDrawTiaoXing::~CDlgDrawTiaoXing()
{
}

void CDlgDrawTiaoXing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDrawTiaoXing, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgDrawTiaoXing ��Ϣ�������

BOOL CDlgDrawTiaoXing::OnEraseBkgnd(CDC* pDC)
{
	CDialog::OnEraseBkgnd(pDC);

	//CRect Rect;
	//GetClientRect(Rect);

	//for(
	return true;
	//return 
}
