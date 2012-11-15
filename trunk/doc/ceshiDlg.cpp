// ceshiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ceshi.h"
#include "ceshiDlg.h"
#include <atlrx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CceshiDlg �Ի���




CceshiDlg::CceshiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CceshiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CceshiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CceshiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CceshiDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CceshiDlg ��Ϣ�������

BOOL CceshiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CceshiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CceshiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CceshiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CceshiDlg::OnBnClickedOk()
{
// TODO: �ڴ���ӿؼ�֪ͨ����������
//	OnOK();

	 CString strRegex=L"({[a-zA-Z0-9_]+@[a-zA-Z0-9]+[.][a-zA-Z0-9]+[.]?[a-zA-Z0-9]+})";

     CString strInput;

     strInput=L"bae123@domain.com";

 

     CAtlRegExp<CAtlRECharTraitsW> reRule;

     wchar_t *wt = (wchar_t *)(LPCTSTR)strRegex;

     REParseError status = reRule.Parse((const ATL::CAtlRegExp<CAtlRECharTraitsW>::RECHAR *)wt);

 

     if (REPARSE_ERROR_OK != status)

     {

        // return 0;

     }

     CAtlREMatchContext<CAtlRECharTraitsW> mcRule;

     wt = (wchar_t *)(LPCTSTR)strInput;

     if (!reRule.Match((const ATL::CAtlRegExp<CAtlRECharTraitsW>::RECHAR *)wt,&mcRule))

     {

         AfxMessageBox(L"��������ʼ���ַ���Ϸ���");

     }

     else
     {

         for (UINT nGroupIndex = 0; nGroupIndex < mcRule.m_uNumGroups; ++nGroupIndex)

         {

              const CAtlREMatchContext<>::RECHAR* szStart = 0;

              const CAtlREMatchContext<>::RECHAR* szEnd = 0;

              mcRule.GetMatch(nGroupIndex, &szStart, &szEnd);

              ptrdiff_t nLength = szEnd - szStart;

              CString strEmailAddress(szStart,  static_cast<int>(nLength));

 

              if(strEmailAddress.Compare(strInput)!=0)

              {

              CString strPrompt;

              strPrompt.Format(L"��������ʼ���ַ���Ϸ�����Ҫ����%s ��",strEmailAddress);

              AfxMessageBox(strPrompt);

              }

              else

              {

                   AfxMessageBox(L"������ʼ���ַ��ȷ��");

              }

 

         }

     }



}
