#pragma once


//����������Ϣ����
struct sDrawLineInfo
{
	CPoint m_StartPoint;
	CPoint m_EndPoint;
};

class CDlgDrawTiaoXing : public CDialog
{
	DECLARE_DYNAMIC(CDlgDrawTiaoXing)

public:
	CDlgDrawTiaoXing(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDrawTiaoXing();

	enum { IDD = IDD_DRAW_TIAO_XING_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedPrevBtn();
	afx_msg void OnBnClickedNextBtn();
	afx_msg void OnBnClickedFirstBtn();
	afx_msg void OnBnClickedCleanBtn();
	void UpdateBtnStatus();

public:

	//���û�������
	void SetDrawData(vector<sDrawInfoList>& DrawAllInfo,CString Title,int TiaoXingCount);

private:

	//��������
	void DrawTiaoXing(CDC* pDC,CRect Rect,int DataIndex);

	//���Ʒ���
	void DrawFrame(CDC* pDC,CRect TempRect,COLORREF Color,int FrameWidth=1);

	//��ʼ����������
	void InitRect();

	//��ȡ��������
	vector<CRect> GetTiaoXingRect(CRect Rect);

	//ͨ��λ�û�ȡ�ı�
	CString GetTextByPoint(CPoint Point);

	//ͨ��λ�û�ȡ����
	int GetIndexByPoint(CPoint Point);

	//�����ڴ��豸����
	void CreateMemDC();

	//����ͼ��
	void Draw();

	


private:

	vector<sDrawInfoList>  m_DrawData;          //��������
	int                    m_DrawIndex;         //��������
	int                    m_TiaoXingHeight;    //���ε������߶�

	vector<CRect>          m_RectList;          //Rect ���������б�
	vector<sDrawLineInfo>  m_DrawLineInfoList; //����������Ϣ
	sDrawLineInfo          m_CurrentDrawLine;  //��ǰ����

	CString                m_DrawText;     //�����ı���Ϣ
	CPoint                 m_TextPoint;    //�����ı�λ��
	int                    m_TiaoXingCount; //������

	bool                   m_IsDrawSingle;
	int                    m_SingleDrawIndex; //���Ƶ�������
	CRect                  m_SingleRect;      //�����ľ��λ�������


	CDC MemDC;
	CBitmap Bmp;
	
};
