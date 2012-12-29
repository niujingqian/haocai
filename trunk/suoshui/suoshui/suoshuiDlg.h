// suoshuiDlg.h : ͷ�ļ�
//

#pragma once
#include <map>
#include <vector>
using namespace std;

// CsuoshuiDlg �Ի���
class CsuoshuiDlg : public CDialog
{
// ����
public:
	CsuoshuiDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SUOSHUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	//��������
	void ParseData(CString& StrData,map<CString,vector<int>>& MapData);

	//��ȡ����
	vector<int> GetDataList(CString& StrData);

	//�������
	void Combine(map<CString,vector<int>> MapData);

	//�������
	void Combine3D(map<CString,vector<int>> MapData);

	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk5();
};
