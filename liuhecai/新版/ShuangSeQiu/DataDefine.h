/************************************************************
*                                                           *
*���ļ��������ݵĶ��� 2012��02��22��         ̷����         *
*                                                           *
*                                                           *
*************************************************************/
#include <vector>
#include <map>
using std::vector;
using std::map;

#define QIU_COUNT 49
#define QIU_XUN   6

enum eSuanFaType                 //Ԥ���㷨����
{
	SUANFA_WEIZHI_YUCE,          //βֵԤ��
	SUANFA_LANJI_YUCE,           //����Ϊ��׼Ԥ��
	SUANFA_ACZHI_YUCE,           //ACֵԤ��
	SUANFA_HEZHI_YUCE2,          //��ֵԤ��2
	SUANFA_HEZHI_YUCE,           //��ֵԤ��
	SUANFA_YIDONG_JUN,           //�ƶ�ƽ��ֵ
	


};

struct sShuangSeQiu
{
	DWORD   m_QiShuID;            //����ID�����Զ����� 
	CString m_QiShu;              //����
	int   m_HongQiu[QIU_XUN];         //ƽ��
	int   m_LanQiu;             //����
	int   m_HongQiuSum;         //ƽ��֮��
	int   m_QuJian[3];          //����
	sShuangSeQiu()
	{
		m_QiShuID=0;
		m_QiShu=_T("δ֪");
		m_LanQiu = 0;
		m_HongQiuSum=0;
		memset(m_HongQiu,0,sizeof(DWORD)*QIU_XUN);
		memset(m_QuJian,0,sizeof(DWORD)*3);
	}

public:

	CString ToString()
	{
		int QiShu=atoi(m_QiShu.GetBuffer());
		m_QiShu.ReleaseBuffer();
		
		CString RetStr;
		RetStr.Format("%d",QiShu);
		for(int i=0; i < QIU_XUN; i++)
		{
			CString Str;
			Str.Format(" %02d",m_HongQiu[i]);
			RetStr+=Str;
		}

		CString Lan;
		Lan.Format("+%02d",m_LanQiu);
		RetStr=RetStr+Lan;
		return RetStr;
		
	}

	CString ToLanString()
	{
	
		int QiShu=atoi(m_QiShu.GetBuffer());
		m_QiShu.ReleaseBuffer();
		
		CString RetStr;
		RetStr.Format("%d",QiShu);
		CString Lan;
		Lan.Format(" %02d",m_LanQiu);
		RetStr=RetStr+Lan;
		return RetStr;
	}

	CString ToHongString()
	{

		int QiShu=atoi(m_QiShu.GetBuffer());
		m_QiShu.ReleaseBuffer();
		
		CString RetStr;
		RetStr.Format("%d",QiShu);
		for(int i=0; i < QIU_XUN; i++)
		{
			CString Str;
			Str.Format(" %02d",m_HongQiu[i]);
			RetStr+=Str;
		}

		return RetStr;
	}
};


struct sEqualShuangSeQiu          //���ƽ�����ṹ�嶨��
{
	vector<sShuangSeQiu>     m_ShuangSeQiuList;  //˫ɫ���б�
	vector<DWORD>            m_EqualData;        //˫ɫ����ȸ����б�
};

//Ԥ����ṹ��
struct sYuCeShuangSeQiu
{
	sShuangSeQiu                      m_ShuangSeQiu;      //ʵ��˫ɫ��
	map<eSuanFaType,sShuangSeQiu>     m_YuCeQiuMap;      //Ԥ�����б�
};
//
struct sZongXiangChaZhi          //�����ֵ
{
	CString m_QiShu;              //����
	DWORD m_HongQiuChaZhi[QIU_XUN];    //ƽ���ֵ
	DWORD m_LanQiuChaZhi;        //�����ֵ
};

struct sHengXiangChaZhi          //�����ֵ
{
	CString m_QiShu;             //����
	DWORD m_HongQiuChaZhi[QIU_XUN];    //ƽ���ֵ
	DWORD m_LanQiuChaZhi;        //�����ֵ
};

/************************��ɫֵ����*********************/

#define YELOW   RGB(255,192,0)                 //��ɫ
#define ZISE    RGB(112,48,160)                //��ɫ
#define WRITE   RGB(255,255,255)               //��ɫ
#define RED     RGB(255,0,0)                   //��ɫ



/*********************������������************************/

//��������
struct sDrawDataInfo
{
	bool            m_IsTrue;         //�Ƿ���ȷ
	CString         m_DrawText;       //�����ı�
	CString         m_Data;           //����
	vector<CString> m_InfoList;       //��������
};


//���������б�
struct sDrawInfoList
{
	CString m_QiShu;                              //����
	vector<sDrawDataInfo>      m_DrawDataList;    //�����б�
};


/*********************������������************************/