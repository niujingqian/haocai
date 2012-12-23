#include "StdAfx.h"
#include "FormulaCenter.h"
#include "DataManageCenter.h"

//����ɱλ�㷨
void CFormulaCenter::ExecYanShaWei(int Wei)
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<map<int,vector<int>>> ResultData;
	for(int Index = 2; Index < (int)DataList->size()-4; Index++)
	{
	    map<int,vector<int>> MapData;   
		TongJiYiChuan(TYPE_TONG_JI_WEI,Wei,Index,MapData);
		ResultData.push_back(MapData);

	}

	m_YanMapFormulaInfo[eYanFormulaType(FORMUAL_YAN_SHA_DI_YI_HONG+Wei)]=ResultData;
}

//����ɱλβ�㷨
void CFormulaCenter::ExecYanShaWeiV(int Wei)
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<map<int,vector<int>>> ResultData;
	for(int Index = 2; Index < (int)DataList->size()-4; Index++)
	{
	    map<int,vector<int>> MapData;   
		TongJiYiChuan(TYPE_TONG_JI_WEI_V,Wei,Index,MapData);
		ResultData.push_back(MapData);

	}

	m_YanMapFormulaInfo[eYanFormulaType(FORMUAL_YAN_SHA_DI_YI_HONG_V+Wei)]=ResultData;
}

//����ɱλ���㷨
void CFormulaCenter::ExecYanShaWeiHe(int Wei)
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<map<int,vector<int>>> ResultData;
	for(int Index = 2; Index < (int)DataList->size()-4; Index++)
	{
	    map<int,vector<int>> MapData;   
		TongJiYiChuan(TYPE_TONG_JI_HE,Wei,Index,MapData);
		ResultData.push_back(MapData);

	}

	m_YanMapFormulaInfo[eYanFormulaType(FORMUAL_YAN_SHA_DI_YI_HONG_HE+Wei)]=ResultData;
}

//����ɱλ���㷨
void CFormulaCenter::ExecYanShaWeiCha(int Wei)
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<map<int,vector<int>>> ResultData;
	for(int Index = 2; Index < (int)DataList->size()-4; Index++)
	{
	    map<int,vector<int>> MapData;   
		TongJiYiChuan(TYPE_TONG_JI_CHA,Wei,Index,MapData);
		ResultData.push_back(MapData);

	}

	m_YanMapFormulaInfo[eYanFormulaType(FORMUAL_YAN_SHA_DI_YI_HONG_CHA+Wei)]=ResultData;
}

//����ɱ���㷨
void CFormulaCenter::ExecYanShaLan()
{

}


//ͳ���Ŵ�
void CFormulaCenter::TongJiYiChuan(eYiChuanTongJiType Type,int Wei,int Offset,map<int,vector<int>>& MapData)
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	for(int Index=1; Index < DataList->size(); Index++)
	{
		int OffsetCount=1;
		int TempCount=0;
		while(true)
		{
			int TempIndex=Index-TempCount-Offset;
			if(TempIndex < 0)
				break;

			int TempData=(*DataList)[Index-TempCount].m_HongQiu[Wei];
			bool IsTrue=false;
			TempCount++;

			switch(Type)
			{
			case TYPE_TONG_JI_WEI:
				IsTrue=CDataManageCenter::IsHongQiuInData((*DataList)[TempIndex],TempData);
				break;
			case TYPE_TONG_JI_WEI_V:
				IsTrue=CDataManageCenter::IsHongQiuInData((*DataList)[TempIndex],TempData,true);
				break;
			case TYPE_TONG_JI_HE:
				IsTrue=CDataManageCenter::IsHongQiuInHeData((*DataList)[TempIndex],TempData,true);
				break;
			case TYPE_TONG_JI_CHA:
				IsTrue=CDataManageCenter::IsHongQiuInChaData((*DataList)[TempIndex],TempData,true);
				break;
			}
			
			if(IsTrue)
				MapData[Index].push_back(1);
			else
				MapData[Index].push_back(0);

			
		}
	}
}


//��ȡ������
vector<map<int,vector<int>>> CFormulaCenter::GetYanFormulaInfoByType(eYanFormulaType Type)
{
	vector<map<int,vector<int>>> InfoList;
	map<eYanFormulaType,vector<map<int,vector<int>>>>::iterator it = m_YanMapFormulaInfo.find(Type);
	if(it != m_YanMapFormulaInfo.end())
		InfoList=it->second;
	return InfoList;
}

//�������㷨
void CFormulaCenter::RunYanFormula()
{
	for(int i=0; i < QIU_XUN; i++)
	{
		//��ɱλ
		ExecYanShaWei(i);

		//����ɱλβ�㷨
		ExecYanShaWeiV(i);
		
		//����ɱλ���㷨
	    ExecYanShaWeiHe(i);

	    //����ɱλ���㷨
	    ExecYanShaWeiCha(i);
	
	}
}