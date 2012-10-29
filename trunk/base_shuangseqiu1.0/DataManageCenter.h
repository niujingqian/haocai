#pragma once
/************************************************************
*                                                           *
*���ļ��������ݵĹ��� 2012��02��22��         ̷����         *
*                                                           *
*                                                           *
*************************************************************/

#include "DataDefine.h"
#include <vector>
#include <map>
using std::map;
using std::vector;


class CDataManageCenter
{
public:

	//��ȡ���ݹ���ʵ��
	static CDataManageCenter* GetInstance();

	//��ȡ˫ɫ���б�
	vector<sShuangSeQiu>* GetDataList();

	//��ȡ������˳��˫ɫ���б� 
	vector<sShuangSeQiu>* GetDataListByChuHao();

	//��ȡ˫ɫ���б�
	vector<sShuangSeQiu> GetSpecialDataList(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str=_T(""));

	//��ȡ4��˫ɫ����ͬ���б�
	map<CString,sEqualShuangSeQiu> GetFourDataEqualList();

	//��ȡ3��˫ɫ����ͬ���б�
	map<CString,sEqualShuangSeQiu> GetThreeDataList();

    //Ԥ����㷽��
	map<CString,sYuCeShuangSeQiu> GetDataBySuanFa();

	//ͨ��������������
	vector<sShuangSeQiu> SearchDataLanQiu(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str=_T(""));

	//ͨ����ͷ��������
	vector<sShuangSeQiu> SearchDataLongTou(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str=_T(""));

	//ͨ��βֵ��������
	vector<sShuangSeQiu> SearchDataWeiZhi(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str=_T(""));

	//����Ԥ����
	map<CString,sYuCeShuangSeQiu> SearchDataBySuanFa(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString QiShu=_T(""));


	//��������
	vector<sShuangSeQiu> SearchHongQiu(DWORD HongQiu);

	//��������
	vector<sShuangSeQiu> SearchHongQiu(vector<sShuangSeQiu>& DataList,DWORD HongQiu);

	//��������
	vector<sShuangSeQiu> SearchLanQiu(DWORD LanQiu);
	
	//��ȡ�����ֵ
	vector<sZongXiangChaZhi>* GetZongXiangChaZhi();

	//��ȡ�����ֵ
	vector<sHengXiangChaZhi>* GetHengXiangChaZhi();

	//��ȡ���ź���
	vector<sShuangSeQiu>* GetLianHaoHongQiu();

	//��ȡ��������
	vector<sShuangSeQiu>* GetLianHaoLanQiu();

	//���������ֵ
	vector<sZongXiangChaZhi> SearchZongXiangChaZhi(DWORD Value);

	//���������ֵ
	vector<sHengXiangChaZhi> SearchHengXiangChaZhi(DWORD Value);

	//��ȡ���ź���
	vector<sShuangSeQiu> SearchLianHaoHongQiu(DWORD Value);

	//��ȡ��������
	vector<sShuangSeQiu> SearchLianHaoLanQiu(DWORD Value);

	//���ļ���������
	bool LoadDataFromFile(CString FilePath,bool IsChuHaoXunXu=false,bool IsClean=true);

	//���ļ���������
	bool LoadDataFromFile(CString FilePath,vector<sShuangSeQiu>& QiuList);

	//����Ԥ�����ݵ��ļ���
	void SaveDataToFile(sYuCeShuangSeQiu& Data);

	//����������־
	void SetSearchFlag(BOOL Flag) { m_SearchFlag = Flag;}

	//����ͳ�����ݵ�csv�ļ���
	void SaveDataToCSVFile();

	//����ͳ���������ں������������ݵ�txt�ļ���
	void SaveFiveDataToTxtFile();

	//����29��ͳ�����ݵ�txt�ļ���
	void Save29DataToTxtFile();

	//��ȡAC��ֵ
	int GetACCount(sShuangSeQiu& ShuangSeQiu);

	//��ȡ��������
	vector<map<int,CString>>* GetDanZuDataList();

public:
	
	//���Ƿ��ں�����
	static bool IsHongQiuInData(sShuangSeQiu QiuData,int Data,bool IsV=false);

	//���Ƿ���������
	static bool IsLanQiuInData(sShuangSeQiu QiuData,int Data,bool IsV=false);

	//�ж������Ƿ�Ϊ����
	static bool IsHeShuData(int Data);

	//��ȡ��������
	static int GetZhiShuCount(sShuangSeQiu QiuData);

	static CString GetDataStr(int Data,bool IsTrue=true,bool IsV=false);

	//// �жϵ�λ�Ƿ��ں�����
	//static bool IsDianHongQiuInData(sShuangSeQiu QiuData,int Data,int Offset=1);

	////��ȡ��λ�ַ���
	//static CString GetDianDataStr(int Data,bool IsTrue=true,int Offset=1);

private:

	//��������
	void ParseData(CString& StrData,vector<sShuangSeQiu>& VectorData);

	//�����ⲿ����
	void ParseWaiBuData(CString& StrData,vector<sShuangSeQiu>& VectorData);

	//ͨ���ַ�����ȡ˫ɫ��
	sShuangSeQiu GetShuangSeQiuByStr(CString& StrData);

	//��ʼ�������ֵ
	void InitHengXiangChaZhi(vector<sShuangSeQiu>& ShuangSeQiuList);

	//��ʼ�������ֵ
	void InitZongXiangChaZhi(vector<sShuangSeQiu>& ShuangSeQiuList);

	//��ʼ�����ź���
	void InitLianHaoHongQiu(vector<sShuangSeQiu>& ShuangSeQiuList);

	//��ʼ����������
	void InitLianHaoLanQiu(vector<sShuangSeQiu>& ShuangSeQiuList);


	
	//��ȡβ��Ԥ�����
	int GetWeiZhiParam(sShuangSeQiu& ShuangSeQiu);


	/////��ʼ29����/////////////

	//��ʼ��29������
	void Init29Data();

	//��ʼһ������
	void InitOneData(sData29 &Data);


	CDataManageCenter(void);

	~CDataManageCenter(void);

private:
	vector<sShuangSeQiu>        m_ShuangSeQiuList;        //˫ɫ��ֵ�б�
	vector<sShuangSeQiu>        m_ShuangSeQiuChuHaoList;  //˫ɫ�������˳���б�
	vector<sHengXiangChaZhi>    m_HengXiangChaZhiList;    //˫ɫ������ֵ�б�
	vector<sZongXiangChaZhi>    m_ZongXiangChaZhiList;    //˫ɫ�������ֵ�б�
	vector<sShuangSeQiu>        m_LianHaoHongQiu;         //˫ɫ�����ź�����ֵ
	vector<sShuangSeQiu>        m_LianHaoLanQiu;          //˫ɫ������������ֵ
	vector<sData29>             m_Data29;                 //29������
	BOOL                        m_SearchFlag;             //������־
	vector<map<int,CString>>    m_DanZu;                  //��������
};
