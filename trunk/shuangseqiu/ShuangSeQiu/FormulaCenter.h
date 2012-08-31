#pragma once

#include <vector>
#include <map>
using std::vector;
using std::map;

//��ʽ��������

//��ʽ����
enum eFormulaType
{
	FORMULA_NULL                ,     //������

	//�����������
	FORMULA_SHA_LAN             ,     //ɱ����
	FORMULA_SHA_LAN_WEI         ,     //ɱ��β
	FORMULA_SHA_LAN_LUSHU       ,     //ɱ����·��
	FORMULA_SHA_LAN_FANWEI      ,     //ɱ����Χ 

	FORMULA_DING_LAN            ,     //������
	FORMULA_DING_LAN_WEI        ,     //������β
	FORMULA_DING_LAN_FANWEI     ,     //������Χ
	FORMULA_DING_LAN_LUSHU      ,     //������·��

	//��ͷ�������
	FORMULA_SHA_LONG_TOU        ,     //ɱ��ͷ
	FORMULA_SHA_LONG_TOU_WEI    ,     //ɱ��ͷV
	FORMULA_SHA_LONG_TOU_LUSHU  ,     //ɱ��ͷ·��

	FORMULA_DING_LONG_TOU       ,     //����ͷ��Χ

	//��β�������
	FORMULA_SHA_FENG_WEI        ,     //ɱ��β
	FORMULA_SHA_FENG_WEI_WEI    ,     //ɱ��βV
	FORMULA_SHA_FENG_WEI_LUSHU  ,     //ɱ��β·��

	FORMULA_DING_FENG_WEI       ,     //����β��Χ

	//�����������
	FORMULA_SHA_HONG            ,    //ɱ����
	FORMULA_SHA_HONG_WEI        ,    //ɱ����V

	FORMULA_DING_HONG_DIAN      ,    //�����λ
	FORMULA_DING_HONG_WEI       ,    //������V
};

//��ʽ��������
struct sFormulaData
{
	CString m_Data;            //��������
	bool    m_IsTrue;          //�Ƿ���ȷ
};

//��ʽ��������
struct sFormulaInfo
{
	CString                m_FormulaName;          //��ʽ����
	eFormulaType           m_FormulaType;          //��ʽ����
	vector<sFormulaData>   m_DataList;             //����
	int                    m_MaxLianCuoCount;      //����������
	int                    m_MaxLianDuiCount;      //������Դ���
	int                    m_MinLianCuoCount;      //��С�������
	int                    m_MinLianDuiCount;      //��С���Դ��� 
	int                    m_ErrorCount;           //�������
	map<CString,int>       m_MapErrorInfo;         //������Ϣ
	bool                   m_LastStatus;           //���һ�ι�ʽ״̬

	sFormulaInfo()
	{
		 m_MaxLianCuoCount = 0;
		 m_MaxLianDuiCount = 0;
		 m_MinLianCuoCount = 0;
		 m_MinLianDuiCount = 0;

		 m_ErrorCount      = 0;
		 m_LastStatus      = true;
		 m_FormulaType     = FORMULA_NULL;
	}
};


class CFormulaCenter
{

public:

	CFormulaCenter(void);

	~CFormulaCenter(void);

	//��ȡ��ʽ��Ϣ
	vector<sFormulaInfo> GetFormulaInfoByType(eFormulaType Type);

	//��ʽ����
	void RunFormula();

private:

	//����ɱ�칫ʽ
	void ExecShaHongFormula();

private:

	map<CString,vector<sFormulaInfo>> m_MapFormulaInfo;   //��ʽ���ݻ���
};
