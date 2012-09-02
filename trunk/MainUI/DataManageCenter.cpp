#include "StdAfx.h"
#include "DataManageCenter.h"

CDataManageCenter* CDataManageCenter::m_Self = NULL;
CDataManageCenter::CDataManageCenter(void)
{
	m_IsIdentify = FALSE;
	m_MMUrl=_T("http://pcmm.shequ.10086.cn:9090/");

//	m_ConnectMode = CONNECT_MODE_NULL;
	m_ConnectMode = CONNECT_MODE_BY_USB;
}

CDataManageCenter::~CDataManageCenter(void)
{
}


//��ʼʵ��
CDataManageCenter* CDataManageCenter::Init()
{
	if(m_Self==NULL)
		m_Self=new CDataManageCenter();
	return m_Self;
}

//ɾ��ʵ��
void CDataManageCenter::Delete()
{
	if(m_Self != NULL)
	{
		delete m_Self;
		m_Self = NULL;
	}
}


//��ȡ������Ϣ
sUsbConnectInfo* CDataManageCenter::GetUsbConnectInfo(CString DesId)
{
	if(DesId.IsEmpty())
		return NULL;
	DesId.MakeUpper();
	map<CString,sUsbConnectInfo*>::iterator it=m_UsbConnectInfoList.find(DesId);
	if(it == m_UsbConnectInfoList.end())
		return NULL;

	return it->second;
}

//��ȡ��ǰWifi������Ϣ
sWifiConnectInfo CDataManageCenter::GetWifiInfo(CString WifiId)
{
	sWifiConnectInfo Temp;
	if(WifiId.IsEmpty())
		return Temp;
	
	map<CString,sWifiConnectInfo>::iterator it=m_WifiConenctInfoList.find(WifiId);
	if(it == m_WifiConenctInfoList.end())
		return Temp;

	return it->second;
}

//��������ֻ���Ϣ
void CDataManageCenter::AddUsbConnectInfo(CString DesId,sUsbConnectInfo* UsbConnectInfo)
{
	if(DesId.IsEmpty())
		return;

	DesId.MakeUpper();
	map<CString,sUsbConnectInfo*>::iterator it=m_UsbConnectInfoList.find(DesId);
	if(it != m_UsbConnectInfoList.end() && it->second)
		delete it->second;
	m_UsbConnectInfoList[DesId] = UsbConnectInfo;
}

//ɾ�������ֻ���Ϣ
void CDataManageCenter::DeleteUsbConnectInfo(CString DesId)
{
	if(DesId.IsEmpty())
		return ;

	DesId.MakeUpper();
	map<CString,sUsbConnectInfo*>::iterator it=m_UsbConnectInfoList.find(DesId);
	if(it == m_UsbConnectInfoList.end())
		return ;

	if(it->second)	
	{
		delete it->second;
		it->second = NULL;
	}

	m_UsbConnectInfoList.erase(it);
}

void CDataManageCenter::DeleteAllUsbConnectInfo()
{
	map<CString,sUsbConnectInfo*>::iterator it = m_UsbConnectInfoList.begin();
	while(it != m_UsbConnectInfoList.end())
	{
		if(it->second)	
		{
			delete it->second;
			it->second = NULL;
		}

		it++;
	}
	m_UsbConnectInfoList.clear();
}


//��ȡWIFIģʽ�������ֻ�������Ϣ
map<CString,sWifiConnectInfo>* CDataManageCenter::GetAllWifiConenctInfoList()
{
	m_WifiConenctInfoList.clear();
	//m_WifiConenctInfoList=CBroadServer::GetWifiConenctInfoList();
	return &m_WifiConenctInfoList;
}

//ɾ����ǰWIFI������Ϣ
void CDataManageCenter::DeleteWifiInfo(CString WifiId)
{
	/*if(!WifiId.IsEmpty())
		CBroadServer::DeleteWifiConnectInfo(WifiId);*/
}