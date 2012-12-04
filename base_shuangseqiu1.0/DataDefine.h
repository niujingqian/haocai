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

#define QIU_COUNT 33
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

//29������
struct sData29
{
	CString     m_BianHao;       //���
	vector<int> m_WeiHong;       //Χ���
	vector<int> m_JueSha;        //��ɱ��
	vector<int> m_GuanLian;      //������
};

struct sShuangSeQiu
{
	DWORD   m_QiShuID;            //����ID�����Զ����� 
	CString m_QiShu;              //����
	int   m_HongQiu[QIU_XUN];         //����
	int   m_LanQiu;             //����
	int   m_HongQiuSum;         //����֮��
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
};

struct sEqualShuangSeQiu          //��Ⱥ������ṹ�嶨��
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
	DWORD m_HongQiuChaZhi[QIU_XUN];    //�����ֵ
	DWORD m_LanQiuChaZhi;        //�����ֵ
};

struct sHengXiangChaZhi          //�����ֵ
{
	CString m_QiShu;             //����
	DWORD m_HongQiuChaZhi[QIU_XUN];    //�����ֵ
	DWORD m_LanQiuChaZhi;        //�����ֵ
};


//������������
struct sWangYiData
{
	int  m_Data;          //����
	long m_Count;         //�������
};

/*********************������������************************/
enum eLoadDataType
{
	LOAD_ALL_DATA,        //������������
	LOAD_WANGYI_DATA,     //������������
	LOAD_ZHONGCAI_DATA,   //�����в�����
	LOAD_AOKE_DATA,       //����Ŀ�����
	LOAD_360_DATA,        //����360����
};

/*********************������������************************/
#define WANG_YI_FILE_NAME  "net_wangyi.txt"

enum eWangYiType
{
	TYPE_GAO_REN_QI,      //��������
	TYPE_DI_REN_QI,       //��������
	TYPE_RE_HAO,          //�Ⱥ�
	TYPE_LENG_HAO,        //���
};

//������������
struct sWangYiDataInfo
{
	__time32_t           m_GetTime;       //��ȡʱ��
	CString              m_QiShu;         //����
	eWangYiType          m_Type;          //����
	vector<sWangYiData>  m_WangYiData;    //��������

	//ת�����ַ���
public:
	CString ToString()
	{
		CString Temp;
		Temp.Format("#%d#%s#%d#",m_GetTime,m_QiShu,m_Type);
		for(int i=0; i < m_WangYiData.size(); i++)
		{
			CString Temp2;
			Temp2.Format("%02d#",m_WangYiData[i]);
			Temp+=Temp2;
		}
		return Temp;
	}
};


/*********************�в���������************************/
#define ZHONG_CAI_FILE_NAME  "net_zhongcai.txt"
//�в���������
enum eZhongCaiType
{
	TYPE_ZHONGCAI_HONG,
	TYPE_ZHONGCAI_LAN,
};

//�в���̨��������
struct sZhongCaiData
{
	int m_Data;            //������
	int m_DataCount;       //�����ݼ���
};

struct sZhongCaiDataInfo
{
	CString               m_QiShu;        //����
	int                   m_QiShuInt;     //������������
	eZhongCaiType         m_Type;         //��������
	vector<sZhongCaiData> m_DataList;     //�в������б�
	
	//ת�����ַ���
public:
	CString ToString()
	{
		CString Temp;
		Temp.Format("#%s#%d#%d#",m_QiShu,m_QiShuInt,m_Type);
		for(int i=0; i < m_DataList.size(); i++)
		{
			CString Temp2;
			Temp2.Format("%02d#",m_DataList[i].m_DataCount);
			Temp+=Temp2;
		}
		return Temp;
	}

};


/*********************������������************************/


/************************��ɫֵ����*********************/

#define YELOW   RGB(255,192,0)                 //��ɫ
#define ZISE    RGB(112,48,160)                //��ɫ
#define WRITE   RGB(255,255,255)               //��ɫ
#define RED     RGB(255,0,0)                   //��ɫ
