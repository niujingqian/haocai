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

	FORMULA_WEI_BU_TONG_CHU     ,    //β��ͬ��

	FORMUAL_SHA_NEW_DI_YI_HONG,      //ɱ��һλ��        
	FORMUAL_SHA_NEW_DI_ER_HONG,      //ɱ�ڶ�λ��
	FORMUAL_SHA_NEW_DI_SAN_HONG,     //ɱ����λ��
	FORMUAL_SHA_NEW_DI_SI_HONG,      //ɱ����λ��
	FORMUAL_SHA_NEW_DI_WU_HONG,      //ɱ����λ��
	FORMUAL_SHA_NEW_DI_LIU_HONG,     //ɱ����λ��

	FORMUAL_SHA_JI_JU,               //ɱ����
	FORMUAL_SHA_DI_YI_HONG,          //ɱ��һλ��
	FORMUAL_SHA_DI_ER_HONG,          //ɱ�ڶ�λ��
	FORMUAL_SHA_DI_SAN_HONG,         //ɱ����λ��
	FORMUAL_SHA_DI_SI_HONG,          //ɱ����λ��
	FORMUAL_SHA_DI_WU_HONG,          //ɱ����λ��
	FORMUAL_SHA_DI_LIU_HONG,         //ɱ����λ��

	FORMUAL_SHA_DI_YI_HONG_V,        //ɱ��һλ��β
	FORMUAL_SHA_DI_ER_HONG_V,        //ɱ�ڶ�λ��β
	FORMUAL_SHA_DI_SAN_HONG_V,       //ɱ����λ��β
	FORMUAL_SHA_DI_SI_HONG_V,        //ɱ����λ��β
	FORMUAL_SHA_DI_WU_HONG_V,        //ɱ����λ��β
	FORMUAL_SHA_DI_LIU_HONG_V,       //ɱ����λ��β

	FORMUAL_SHA_DI_YI_HONG_HE,        //ɱ��һλ���
	FORMUAL_SHA_DI_ER_HONG_HE,        //ɱ�ڶ�λ���
	FORMUAL_SHA_DI_SAN_HONG_HE,       //ɱ����λ���
	FORMUAL_SHA_DI_SI_HONG_HE,        //ɱ����λ���
	FORMUAL_SHA_DI_WU_HONG_HE,        //ɱ����λ���
	FORMUAL_SHA_DI_LIU_HONG_HE,       //ɱ����λ���

	FORMUAL_SHA_DI_YI_HONG_CHA,        //ɱ��һλ���
	FORMUAL_SHA_DI_ER_HONG_CHA,        //ɱ�ڶ�λ���
	FORMUAL_SHA_DI_SAN_HONG_CHA,       //ɱ����λ���
	FORMUAL_SHA_DI_SI_HONG_CHA,        //ɱ����λ���
	FORMUAL_SHA_DI_WU_HONG_CHA,        //ɱ����λ���
	FORMUAL_SHA_DI_LIU_HONG_CHA,       //ɱ����λ���

	FORMUAL_SHA_NEW_LAN_V,             //ɱ��β

	FORMUAL_SHA_QUAN_HONG,
	FORMUAL_SHA_NEW_JIXIAN_LAN,          //�¼���ɱ��

	
	FORMUAL_DI_YI_HONG_QU_JIAN,         //��һ�첨������
	FORMUAL_DI_ER_HONG_QU_JIAN,         //�ڶ��첨������
	FORMUAL_DI_SAN_HONG_QU_JIAN,        //�����첨������
	FORMUAL_DI_SI_HONG_QU_JIAN,         //���ĺ첨������
	FORMUAL_DI_WU_HONG_QU_JIAN,         //����첨������
	FORMUAL_DI_LIU_HONG_QU_JIAN,        //�����첨������

};

//��ʽ��������
struct sFormulaData
{
	CString m_Data;            //��������
	bool    m_IsTrue;          //�Ƿ���ȷ
	CString m_QiShu;           //����
	CString m_TrueBaiFenBi;    //��ȷ�ٷֱ�

	sFormulaData()
	{
		m_IsTrue = true;
	}
};

//��ʽ��������
struct sFormulaInfo
{
	CString                m_FormulaName;          //��ʽ����
	CString                m_QiShu;                //����
	eFormulaType           m_FormulaType;          //��ʽ����
	vector<sFormulaData>   m_DataList;             //����
	int                    m_MaxLianCuoCount;      //����������
	int                    m_MaxLianDuiCount;      //������Դ���
	int                    m_MinLianCuoCount;      //��С�������
	int                    m_MinLianDuiCount;      //��С���Դ��� 
	int                    m_ErrorCount;           //�������
	int                    m_TrueCount;            //��ȷ����
	map<CString,int>       m_MapErrorInfo;         //������Ϣ
	bool                   m_LastStatus;           //���һ�ι�ʽ״̬

	sFormulaInfo()
	{
		 m_MaxLianCuoCount = 0;
		 m_MaxLianDuiCount = 0;
		 m_MinLianCuoCount = 0;
		 m_MinLianDuiCount = 0;

		 m_ErrorCount      = 0;
		 m_TrueCount       = 0;
		 m_LastStatus      = true;
		 m_FormulaType     = FORMULA_NULL;
	}
};

//m_ComboBox.InsertString(0,"��ȷ�ʴ���");
//	m_ComboBox.InsertString(1,"��ȷ�ʵ���");
//	m_ComboBox.InsertString(2,"��ȷ��С��");
//	m_ComboBox.InsertString(3,"��ȷ������");
//	m_ComboBox.InsertString(4,"��ȷ�ʵ���");
//	m_ComboBox.InsertString(5,"����βС��");
//	m_ComboBox.InsertString(6,"����β����");
//	m_ComboBox.InsertString(7,"����β����");
//	m_ComboBox.InsertString(8,"����β����");
//	m_ComboBox.InsertString(9,"���һ�δ�");


enum eSearchVType
{
	TYPE_DA_YU,
	TYPE_DENG_YU,
	TYPE_XIAO_YU,
	TYPE_QU_JIAN,
	TYPE_V_DA_YU,
	TYPE_V_DENG_YU,
	TYPE_V_XIAO_YU,
	TYPE_V_QU_JIAN,
	TYPE_LAST_ERROR,
	TYPE_TE_DA_YU,
	TYPE_TE_DENG_YU,
	TYPE_TE_XIAO_YU,
	TYPE_TE_QU_JIAN,
};


class CFormulaCenter
{

public:

	//��ȡ���ݹ���ʵ��
	static  CFormulaCenter* GetInstance();

	//��ȡ��ʽ��Ϣ
	vector<sFormulaInfo> GetFormulaInfoByType(eFormulaType Type);

	//������ʽ��Ϣ
	vector<sFormulaInfo> SearchFormulaInfoByType(eFormulaType Type,eSearchVType SearchType,int Data,int Data2);

	//ͨ���㷨��ȡ��ʽ��Ϣ
	vector<sFormulaInfo> GetFormulaInfoByName(eFormulaType Type,vector<CString>& NameList);
	
	//��ȡ�㷨����
	int GetFormulaCount(eFormulaType Type);

private:

	//����ɱ�칫ʽ
	void ExecShaHongFormula();

	//���ж��칫ʽ
	void ExecDingHongFormula();

	//���ж���V��ʽ
	void ExecDingHongVFormula();

	//����ɱ����ʽ
	void ExecShaLanFormula();

	//����ɱ��V��ʽ
	void ExecShaLanVFormula();

	//����ɱ��ͷ��ʽ
	void ExecShaLongTouFormula();

	//����ɱ��β��ʽ
	void ExecShaFengWeiFormula();

	//����β��ͬ����ʽ
	void ExecWeiBuTongChuFormula();

 //   FORMUAL_SHA_JI_JU,               //ɱ����
	//FORMUAL_SHA_DI_ER_HONG,          //ɱ�ڶ�λ��
	//FORMUAL_SHA_DI_SAN_HONG,         //ɱ����λ��
	//FORMUAL_SHA_DI_SI_HONG,          //ɱ����λ��
	//FORMUAL_SHA_DI_WU_WHONG,         //ɱ����λ��

	//ɱ����
	void ExecShaJiJu();

	//��λɱβ
	void ExecShaWeiV(int Wei);

	//ɱ��β
	void ExeShaLanV();

	//��λɱ��
	void ExecShaWeiHe(int Wei);

	//��λɱ��
	void ExecShaWeiCha(int Wei);

	//ɱ��һλ
	void ExecShaDiYiWei();

	//ɱ�ڶ�λ
	void ExecShaDiErWei();

	//ɱ����λ
	void ExecShaDiSanWei();

	//ɱ����λ
	void ExecShaDiSiWei();

	//ɱ����λ
	void ExecShaDiWuWei();

	//ɱ����λ
	void ExecShaDiLiuWei();

	//ɱȫλ
	void ExecShaQuanWei();


	//�¼���ɱ��
	void ExecNewShaLan();


	//��һλ��������
	void ExecDiYiBoDongQuJian();

	//�ڶ�λ��������
	void ExecDiErBoDongQuJian();

	//����λ��������
	void ExecDiSanBoDongQuJian();

	//����λ��������
	void ExecDiSiBoDongQuJian();

	//����λ��������
	void ExecDiWuBoDongQuJian();

	//����λ��������
	void ExecDiLiuBoDongQuJian();



private:

	//����ת�����ַ���
	CString DataToStr(int Data);

	//����ת�����ַ���
	CString DataToStr(vector<int> Data);

	//�ַ���ת��������
	int StrToData(CString DataStr);

	//ͳ�ƹ�ʽ��Ϣ
	void ToJiFormulaInfo(sFormulaInfo& Formula);

	//��ȡβֵ��
	int GetWeiZhiCount(int DataList[],int Count);

	//�������乫ʽ
	void RunQuJianFormula(eFormulaType FormulaType);

	//��¼����
	void RecordDataToFile();

	CFormulaCenter(void);

	~CFormulaCenter(void);

	//��ʽ����
	void RunFormula();

private:

	map<eFormulaType,vector<sFormulaInfo>> m_MapFormulaInfo;   //��ʽ���ݻ���
};
