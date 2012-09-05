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
#define QIU_XUAN  6

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
	int   m_HongQiu[6];         //����
	int   m_LanQiu;             //����
	int   m_HongQiuSum;         //����֮��
	int   m_QuJian[3];          //����
	sShuangSeQiu()
	{
		m_QiShuID=0;
		m_QiShu=_T("δ֪");
		m_LanQiu = 0;
		m_HongQiuSum=0;
		memset(m_HongQiu,0,sizeof(DWORD)*6);
		memset(m_QuJian,0,sizeof(DWORD)*3);
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
	DWORD m_HongQiuChaZhi[6];    //�����ֵ
	DWORD m_LanQiuChaZhi;        //�����ֵ
};

struct sHengXiangChaZhi          //�����ֵ
{
	CString m_QiShu;             //����
	DWORD m_HongQiuChaZhi[6];    //�����ֵ
	DWORD m_LanQiuChaZhi;        //�����ֵ
};

//29������
struct sData29
{
	CString     m_BianHao;       //���
	vector<int> m_WeiHong;       //Χ���
	vector<int> m_JueSha;        //��ɱ��
	vector<int> m_GuanLian;      //������
};

//����29����������
enum eSearch29Type
{
	SEARCH_JUESHA_QIE_JUESHA,      //����ɱ�Ҿ�ɱ������ʽ
	SEARCH_JUESHA_HUO_JUESHA,      //����ɱ���ɱ������ʽ
	SEARCH_DINGDAN_QIE_DINGDAN,    //�������Ҷ���������ʽ
	SEARCH_DINGDAN_HUO_DINGDAN,    //�������򶨵�������ʽ     
	SEARCH_JUESHA_QIE_DINGDAN,     //����ɱ�붨����ʽ����
	SEARCH_JUESHA_HUO_DINGDAN      //����ɱ�򶨵���ʽ����
};

//����29������
struct sSearchData29
{
	sData29           m_Data29;            //����29������
	int               m_GroupID;           //���
};

