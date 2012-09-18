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

