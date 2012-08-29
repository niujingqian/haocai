#pragma once
#include "SkinHeaderCtrl.h"
#include <map>
#include <vector>
using std::vector;
using std::map;

/****************************************************************************
*  ����������ǿ���б�ؼ�                                                   *
*����������2011.6.20                                                        *
*  ���ߣ�  ̷����                                                           *
*                                                                           *
****************************************************************************/

//�Զ�����Ϣ
#define WM_LIST_BUTTON_CLICK WM_USER + 5000             //��ť�����Ϣ
#define WM_VIRTUAL_LIST_MSG  WM_USER + 5001             //��ģʽ����Ϣ : wParam ��ʾID , lParam ��ʾ�Ŀ�ʼ��
#define WM_LIST_CHECKBOX_CLICK  WM_USER + 5002				//��ѡ��ѡ���¼�

//������
enum eItemType
{
	TEXT_TYPE,                           //�ı�����
	BUTTON_TYPE,                         //��ť����               
	CHECK_BOX_TYPE,                      //��ϰѡ������
	IMGE_TYPE,                           //ͼƬ����
	CHECKBOX_IMAGE_AND_TEXT_TYPE,        //��ͼƬ�������֣��и�ѡ������
	IMAGE_AND_TEXT_TYPE,                  //��ͼƬ����������
	PROGRESS_AND_TEXT_TYPE					//������������
};

//���Ʒ��
enum eDrawStyle
{
	TEXT_LEFT_IMAGE_RIGHT,              //������ͼƬ�ұ�
	TEXT_RIGHT_IMAGE_LEFT,              //������ͼƬ��� 
	TEXT_UP_IMAGE_DOWN,                 //������ͼƬ�±�
	TEXT_DOWN_IMAGE_UP,                 //������ͼƬ�±�
	TEXT_ON_IMAGE                       //������ͼƬ�ϱ�
};

//���ģʽ
enum eFillMode {
	MODE_FILL_RGB,        //��RGB���
	MODE_FILL_IMG,        //��ͼƬ���
	MODE_FILE_NO          //�����
};

struct sItemBkData
{
	eFillMode m_BkFillMode;      //������䷽ʽ M
	COLORREF  m_BkColor;         //������ɫ
	Image*    m_Image;           //����ͼƬ
	eFillMode m_HeightFillMode; //�Ƿ���� MODE_FILL_NO �޸���
	COLORREF m_HeightColor;     //������ɫ
	Image*   m_HeightImage;     //����ͼƬ
	sItemBkData()
	{
		m_BkFillMode = MODE_FILE_NO;
		m_BkColor = RGB(255,255,255);
		m_Image   = NULL;

		m_HeightFillMode = MODE_FILE_NO;
		m_HeightColor = RGB(150,205,205);
		m_HeightImage = NULL;
	}
};

//Item �ض�������ݽṹ
struct sItemStyle
{
	struct sTextData                          //�ı�����
	{
		COLORREF   m_TextColor;                //�ı�
		BOOL       m_EnableEdit;               //�Ƿ�ɱ༭    //Ŀǰֻ���� TEXT_TYPE �¿ɱ༭
		CFont*     m_TextFont;                 //�ı�����
		UINT       m_TextFormat;               //�ı���ʾ��� ͬDrawText�е�Format
	};

	struct sButtonData                        //��ť����
	{
		BOOL      m_IsNormal;                 //�Ƿ�������״̬
		Image*    m_ButtonNormalImage;        //��ť����״̬ͼƬ
		Image*    m_ButtonActiveImage;        //��ť�״̬ͼƬ
		BOOL      m_HasText;                  //�Ƿ�����ı�
	    sTextData m_TextData;                 //��m_HasTextΪTRUEʱ�����ֶβ���Ч
	};

	struct sCheckBoxData                      //��ѡ������
	{
		BOOL   m_IsCheck;                     //�Ƿ���ѡ��״̬
		Image* m_CheckBoxUnSelectedImage;     //��ѡ��δѡ��״̬ͼƬ
		Image* m_CheckBoxSelectedImage;       //��ѡ��ѡ��״̬ͼƬ
		BOOL      m_HasText;                  //�Ƿ�����ı�
	    sTextData m_TextData;                 //��m_HasTextΪTRUEʱ�����ֶβ���Ч
		eDrawStyle m_DrawStyle;               //���Ʒ�񣬵�m_HasTextΪTRUEʱ,���ֶβ���Ч
	};

	struct sImageData                         //ͼƬ����
	{
		BOOL   m_IsNormal;                    //�Ƿ�������״̬
		Image* m_NormalImage;                 //����״̬ͼƬ
		Image* m_ActiveImage;                 //�״̬ͼƬ
		BOOL   m_IsTouchClickMsg;             //�Ƿ񴥷������Ϣ    
		BOOL   m_IsDeleteNormalImage;         //�Ƿ�ɾ��ͼƬ
		BOOL   m_IsDeleteActiveImage;         //�Ƿ�ɾ��ͼƬ
		
	};
	struct sCheckBoxImageAndTextData          //��ѡ��ͼƬ����������
	{
		sCheckBoxData m_BoxData;              //��ѡ������
		sTextData     m_TextData;             //�ı�����
		sImageData    m_ImageData;            //ͼƬ����
		eDrawStyle    m_DrawStyle;            //���Ʒ��
	};

	struct sImageAndTextData
	{
		eDrawStyle   m_DrawStyle;             //���Ʒ��
		sTextData    m_TextData;              //�ı�����
		sImageData   m_ImageData;             //ͼƬ����
	};

	union uDrawData
	{
		sTextData                    m_TextData;
		sButtonData                  m_ButtonData;
		sCheckBoxData                m_CheckBoxData;
		sImageData                   m_ImageData;
		sCheckBoxImageAndTextData    m_CheckBoxImageAndTextData;
		sImageAndTextData            m_ImageAndTextData;
	};

	struct sItemPos
	{
		int m_RowIndex;
		int m_ColoumIndex;
	};
	
	

	eItemType   m_ItemType;         //Item����
	uDrawData   m_DrawData;         //Item��ͼ����

	sItemStyle()
	{
		memset(&m_DrawData,0,sizeof(uDrawData));
		m_ItemType = TEXT_TYPE;
		m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
		m_DrawData.m_TextData.m_EnableEdit = false;
		m_DrawData.m_TextData.m_TextFont = NULL;
		m_DrawData.m_TextData.m_TextFormat = DT_SINGLELINE | DT_CENTER| DT_VCENTER | DT_END_ELLIPSIS;
	}
};

class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();

	virtual ~CListCtrlEx();

	//ɾ������
	BOOL DeleteAllItems();

	//ɾ��������
	BOOL DeleteAllColumn();

	//ɾ�������з��
	void DeleteAllColumnStyle();

	//ɾ�������з��
	void DeleteAllItemStyle();

	//ɾ����
	BOOL DeleteColumnStyle(int ColumIndex);
 
	//ɾ����
	BOOL DeleteItemStyle(int RowIndex);
	
	//���ø��Ͽ�״̬
	BOOL SetCheck(int RowIndex, BOOL Check = TRUE);

	//��ȡ�Ƿ�ѡ��
	BOOL GetCheck(int RowIndex,int ColumIndex=0);

	//��ȡ��������ʾ���
	 bool GetColumStyle(int ColumIndex,sItemStyle& Style);

	//��ȡ�ض���Ԫ��ʾ���
	bool GetItemSpeialStyle(int RowIndex, int ColumIndex, sItemStyle& Style);

	//������������ʾ���
	void SetColumStyle(int ColumIndex, sItemStyle& Style);

	//���õ�Ԫ�ض����
	void SetItemSpecialStyle(int RowIndex,int ColoumIndex,sItemStyle& ItemStyle);

	//�����и�
	void SetRowHeight(int RowHeight);

	//��ȡ������
	int GetRowCount(){ return m_RowCount; }

	//��ȡ������
	int GetColmnCount() { return m_ColumnCount; }

	//������
	int InsertColumn(int nCol,LPCTSTR HeaderStr,int Format=LVCFMT_LEFT,int Width=-1,int Height=-1);

	//��������
	int InsertItem(int Item, LPCTSTR Str);

	//ɾ������
	BOOL DeleteItem(int Item);

	//ɾ����
	BOOL DeleteColumn(int Col);

	//�Ի溯��
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//��������
	virtual void DrawSubItem(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem);

	//��Ӧ��ť������Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//���ð�ť��Ӧ����
	void SetButtonClickHwnd(HWND hWnd){ m_ButtonHwnd = hWnd;};
	
	//�����и�
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	
	//�Ƿ�������ƴ�ֱ�������
	void EnableVecLine(BOOL DrawLine) { m_VecDrawLine = DrawLine;}

	//�Ƿ�������ƺ��������
	void EnableHorLine(BOOL DrawLine) { m_HorDrawLine = DrawLine;}

	virtual void PreSubclassWindow();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	//����ͷ�������ɫ
	void SetHeaderAndLineColor(COLORREF Color,COLORREF LineColor) { m_HeaderCtrl.m_DrawRGB = true;m_HeaderCtrl.m_BkColor = Color; m_HeaderCtrl.m_LineColor = LineColor;}

	//����ͷ��λͼ�ͷָ���λͼ
	void SetHeaderAndLineImage(Image* HeaderIamge,Image* LineImage){ m_HeaderCtrl.m_DrawRGB= true;m_HeaderCtrl.m_pImageBg; m_HeaderCtrl.m_pImageLine = LineImage;}

	//�Ƿ���ʾͷ��
	void ShowHeader(BOOL Show) {m_HeaderCtrl.m_HeaderShow = Show;}

	//���ñ�����ѡ��������
	void SetItemBkData(sItemBkData BkData) {m_BkData = BkData; }

	//������ģʽ
	void SetVirtualMode(int VirtualID,BOOL IsVirtual){  m_VirtualID = VirtualID;m_IsVirtualMode = IsVirtual;}

	//������ǰλ�ã������ģʽ
	void TouchCurrentScrollPos();

	//���õ�ǰѡ����
	void SetCurrentSelectRow(int Row);
	//����ȫѡ
	void SetAllLineSelected(int iRow);
	//����ѡ������
	void SetSelProperty(int iRow);

	//�Ƿ���Ҫ��ɾ��
	bool bNeedDelete;

	//���õ�ǰ��ʾ�Ƿ�Ϊ��Ƶ
	void SetShowVideo(bool showVedio){m_ShowVedio = showVedio;};

	//
	void SetShowOther(bool showOther){m_ShowOther = showOther;};

	//�����б�ͷ�ƶ��¼�
	afx_msg BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	DECLARE_MESSAGE_MAP()

	//���Ʊ���
	virtual void DrawBkItem(CDC* pDC, int RowIndex,CRect Rect);

	//����
	virtual void DrawByStyle(CDC* pDC,int nItem,int nSubItem,CRect& rSubItem,sItemStyle* pStyle);

	//������Ƶ
	virtual void DrawShowVedio(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem, sItemStyle *pStyle);
	
	//��ȡͼƬ��������
	CRect GetImageDrawRect(Image* pImage,CRect Rect);

	//��ȡ�ı���������
    CRect GetTextDrawRect(Image* pImage,CRect Rect,eDrawStyle Style);
	
	//��ȡ�ı���ͼƬ��������
	void GetTextAndImageDrawRect(Image* pImage,CRect Rect,CRect& ImageRect,CRect& TextRect,eDrawStyle Style);

	//��ȡ��Ƶ�Ļ�ͼ��ʽ
	void GetVedioImageTextRect(Image* pImage,CRect Rect,CRect& ImageRect,CRect& TextRect,eDrawStyle Style);

	//��ȡͼƬ���Ƶ�
	CPoint GetImageDrawPoint(Image* pImage,CRect Rect);

	//Rect �� RectF ��ת��
	RectF RectToRectF(CRect Rect);

	//ͨ������ҵ�ǰλ��
	bool FindRowAndColumnPos(CPoint Point,int& RowIndex,int& ColumnIndex,CRect& SubItemRect);

	//ͨ��ItemId��ѯ��ǰλ��
	bool FindRowAndColumnPos(int ItemId,int& RowIndex,int& ColumnIndex);

	//��ʾ�༭��
	void ShowEdit(CRect Rect,CString Str,CFont* Font);

	//����
	bool OnButtonDownAction(sItemStyle* pStyle);

	//��������
	void FillRectByImage(CDC* pDC,Image* pImage,CRect Rect);

	//ɾ��ͼƬ
	void DeleteImage(Image* pImage);

	//������
	void CleanStyle(int ColumnIndex,sItemStyle* pStyle);

	struct sItemIndex
	{
		int  m_Index;
		bool m_IsDeleteFlag;
	};

	int                  m_RowCount;          //������
	int                  m_ColumnCount;       //����
	map<long,sItemStyle> m_ItemStyleMap;      //�ض���Ԫ���ӳ���
	map<int,sItemStyle>  m_ColumnStyleMap;    //�����з���
	CEdit                m_Edit;              //�༭��
	COLORREF             m_LineColor;         //��������ɫ
	sItemBkData          m_BkData;            //�����͸�������
	int                  m_CurrentSelectRow;  //��ǰѡ����
	int					 m_OldSelectRow;	  //֮ǰѡ����
	HWND                 m_ButtonHwnd;        //��ť��Ϣ���մ��ھ��
	int                  m_RowHeight;         //�и�
	BOOL                 m_VecDrawLine;       //�Ƿ�������ƴ�ֱ�������
	BOOL                 m_HorDrawLine;       //�Ƿ�������ƺ��������
	BOOL                 m_IsVirtualMode;     //�Ƿ�Ϊ��ģʽ
	int                  m_VirtualID;         //��ģʽID
	CSkinHeaderCtrl      m_HeaderCtrl;        //ͷ���ؼ�
	
	vector<sItemIndex>   m_RowIndex;          //������
	vector<sItemIndex>   m_ColumnIndex;       //������

	bool     m_ShowVedio;
	bool     m_ShowOther;
	//listCtrl�ؼ�ͷ
	//CSkinHeadCtrl m_skinHead;

	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


