/***********************************************************************************
* ˵��      ��  CDataManageCenter���ݹ������ģ�������������ݣ����õ���ģʽ      *
* ������    ��  ̷����                                                             *
* ��������  ��  2011-9-8                                                           *
***********************************************************************************/
#pragma once

#include "DataDefine.h"

class CDataManageCenter
{
public:

	//��ʼʵ��
	static CDataManageCenter* Init();

	//ɾ��ʵ��
	static void Delete();

	//��ȡ������Ϣ
	sUsbConnectInfo* GetUsbConnectInfo(CString DesId);

	//��ȡ��ǰWifi������Ϣ
	sWifiConnectInfo GetWifiInfo(CString WifiId);

	//��������ֻ���Ϣ
	void AddUsbConnectInfo(CString DesId,sUsbConnectInfo* UsbConnectInfo);

	//ɾ�������ֻ���Ϣ
	void DeleteUsbConnectInfo(CString DesId);

	//ɾ�����������ֻ���Ϣ
	void DeleteAllUsbConnectInfo();

	//ɾ����ǰWIFI������Ϣ
	void DeleteWifiInfo(CString WifiId);

	//���õ�ǰ���ӵ��ֻ�ID
	void SetCurrentConnectPhoneDesId(CString DesId) { if(!DesId.IsEmpty()) m_PhoneDesId = DesId; m_WifiInfoId.Empty(); }

	//���õ�ǰWIFI���ӵ��ֻ�ID
	void SetCurrentConnectWifiId(CString Id) { if(!Id.IsEmpty()) m_WifiInfoId = Id; m_PhoneDesId.Empty();}

	//��ȡ��ǰ���ӵ��ֻ�ID
	CString GetCurrentConnectPhoneDesId() { return m_PhoneDesId; }

	//��ȡ��ǰ���ӵ��ֻ�ID
	CString GetCurrentConnectWifiId() { return m_WifiInfoId; }

	//��ȡUSB��ǰ�����ֻ���Ϣ
	sUsbConnectInfo* GetCurrentConnectUsbConnectInfo() { return GetUsbConnectInfo(m_PhoneDesId);}

	//��ȡ��USB�������ֻ���Ϣ
	map<CString,sUsbConnectInfo*>* GetAllConnectPhoneList() { return &m_UsbConnectInfoList; }

	//��ȡWIFIģʽ�������ֻ�������Ϣ
	map<CString,sWifiConnectInfo>* GetAllWifiConenctInfoList();

	//��ȡ��ǰWifi������Ϣ
	sWifiConnectInfo GetCurrentConenctWifiInfo() { return GetWifiInfo(m_WifiInfoId); }

	//���õ�ǰ�����汾��
	void SetDriveVersion(CString Version) { if(!Version.IsEmpty()) m_DriveVersion = Version; }

	//��ȡ�����汾
	CString GetDrivVersion() { return m_DriveVersion; }

	//��������������Ϣ����·��
	void SetDriveURL(CString Url) { if(!Url.IsEmpty()) m_DriveUrl = Url; }

	//����������Ϣ����·��
	CString GetDriveURL() { return m_DriveUrl;}

	//����MM���ص�URL
	void SetMMUrl(CString Url) { if(!Url.IsEmpty()) m_MMUrl = Url; }

	//��ȡMM���ص�URL
	CString GetMMUrl() { return m_MMUrl; }

	//�����Ƿ���ʶ���־
	void SetIsIdentify(BOOL IsIdentify){ m_IsIdentify = IsIdentify; }

	//��ȡ�Ƿ���ʶ���־
	BOOL GetIsIdentify() { return m_IsIdentify; }

	//����Ӧ�ó���汾��
	void SetCurrentProgramVersion(CString Version){  if(!Version.IsEmpty()) m_ProgramVersion= Version; }
	
	//��ȡӦ�ó���汾��
	CString GetCurrentProgramVersion() { return m_ProgramVersion;}

	//��ȡ��ǰ��������
	eConnectMode GetCurrentConnectMode(){ return m_ConnectMode;}

	//���õ�ǰ��������
	void SetCurrentConenctMode(eConnectMode Mode){ m_ConnectMode = Mode;}
private:

	CDataManageCenter(void);

	~CDataManageCenter(void);


private:
	static CDataManageCenter*      m_Self;                   
	map<CString,sUsbConnectInfo*>       m_UsbConnectInfoList;          //�����ֻ���Ϣ�б�  
	map<CString,sWifiConnectInfo>  m_WifiConenctInfoList;    //�ֻ���WIFIģʽ�����ӵ��б�
	CString                        m_PhoneDesId;             //��ǰ�ֻ����ӵ�ID
	CString                        m_MMUrl;                  //MM���ص�URL
	CString                        m_DriveVersion;           //�����汾
	CString                        m_DriveUrl;               //����������Ϣ����·��
	CString                        m_ProgramVersion;         //����汾��Ϣ
	CString                        m_WifiInfoList;           //WIFIģʽ���ֻ������б�
	CString                        m_WifiInfoId;             //��ǰWIFI�ֻ�����ID
	BOOL                           m_IsIdentify;             //�ֻ��Ƿ�����ʶ���־
	eConnectMode                   m_ConnectMode;            //��ǰ����ģʽ
};
