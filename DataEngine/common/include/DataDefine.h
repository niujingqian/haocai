#pragma once
#include <vector>
#include <map>
using std::vector;
using std::map;

#define EXPORT_API   __declspec(dllexport)
#define EXPORT_CLASS __declspec(dllexport)


#define __WRITE_LOG__
#ifdef __WRITE_LOG__
#define  XWriteEventLog  WriteLog
#endif

/**********************************SOCKET�ص���������*************************************/
typedef void (*FunctionSocketCallBack)(CString& SocketStr);

/**********************************ö�ٶ���***********************************************/

//Ӧ�ó���·������
enum ePathType
{
	PATH_UNKOWN,
	PATH_SDCARD,
	PATH_PHONE,
};

//�ֻ�����ϵͳ����
enum ePhoneOSType
{
	PHONE_OS_ANDROID,
};

 //��������
enum eConnectMode 
{
	CONNECT_MODE_BY_USB,
	CONNECT_MODE_BY_WIFI
};

//��ϵ������ʽ
enum eContactSortType
{
	CONTACT_SORT_BY_NAME,  //����������   
	CONTACT_SORT_BY_TIME,  //��ʱ������
};

//����״̬
enum eSmsStaus
{
	SMS_IS_READ,            //�����Ѷ�
	SMS_NOT_READ,           //����δ��
};

//��������
enum eSmsBox
{
	SMSBOX_INBOX     = 1   ,     //�ռ���  
	SMSBOX_SENTBOX   = 2   ,     //�ѷ�����
	SMSBOX_DRAFT     = 3   ,     //�ݸ���
	SMSBOX_OUTBOX    = 4   ,     //������
	SMSBOX_DELETEBOX = 5   ,     //��ɾ������
};

//��������ʽ
enum eSmsSortType
{
	SMS_SORT_BY_TIME,                //��ʱ������
	SMS_SORT_BY_NAME,                //����������
	SMS_SORT_BY_READ,                //���Ƿ��Ѷ�����
};




/**********************************�ṹ�嶨��***********************************************/



/*********************************�ֻ���Ϣ�ṹ�嶨��****************************************/
//�ֻ���Ϣ
struct sPhoneInfo
{
	CString m_CompayName;         //�ֻ�����
	CString m_PhoneModel;         //�ֻ��ͺ�
	CString m_PhoneIMEI;          //�ֻ�IMEI
	CString m_PhoneIMSI;          //�ֻ�IMSI
	CString m_PhoneOS;            //�ֻ�����ϵͳ
	CString m_PhoneOSVer;         //�ֻ�����ϵͳ�汾
	CString m_InstallType;        //֧�ֵİ�װ����


	__int64 m_PhoneFreeMem;       //�ֻ��ڴ�����С
	__int64 m_PhoneTotalMem;      //�ֻ��ڴ��ܴ�С
	__int64 m_PhoneUsedMem;       //�ֻ��ڴ����ô�С

	__int64 m_SDFreeMem;          //SD�������С
	__int64 m_SDTotalMem;         //SD���ܴ�С
	__int64 m_SDUsedMem;          //SD�����ô�С

	__int64 m_PicMemInPhone;      //ͼƬ���ֻ�����ռ�ռ�
	__int64 m_PicMemInSD;         //ͼƬ��SD����ռ�ռ�

	__int64 m_VideoMemInPhone;    //��Ƶ���ֻ�����ռ�ռ�
	__int64 m_VideoMemInSD;       //��Ƶ��SD����ռ�Ŀռ�

	__int64 m_MusicMemInPhone;    //�������ֻ�����ռ�ռ�
	__int64 m_MusicMemInSD;       //������SD����ռ�ռ�

	__int64 m_AppSum;             //Ӧ�ó�������
	__int64 m_ContactSum;         //��ϵ������
	__int64 m_SmsSum;             //��������
	__int64 m_MusicSum;           //��������
	__int64 m_PicSum;             //ͼƬ����
	__int64 m_VideoSum;           //��Ƶ����
	__int64 m_DocSum;             //�ĵ�����


};

/*********************************Ӧ�ó���ṹ�嶨��****************************************/
//����Ӧ�ó�����Ϣ
struct sAppInfo
{
	CString m_AppName;         //Ӧ�ó�������
	CString m_ApkName;         //Ӧ�ó���APK������
	CString m_AppType;         //Ӧ�ó�������
	CString m_AppSize;         //Ӧ�ó����С
	CString m_AppVersion;      //Ӧ�ó���汾
	CString m_AppPackName;     //Ӧ�ó���װ����
	ePathType m_PathType;      //Ӧ�ó���·��
	
	sAppInfo()
	{
		m_PathType = PATH_UNKOWN;
	}
};


/*********************************��ϵ�˽ṹ�嶨��****************************************/
//������ϵ����Ϣ
struct sContactInfo
{
	CString m_ID;                        //���ݿ�ID
	vector<CString> m_GroupIDs;          //��������ID��


	CString m_Name;                      //����
	CString m_MobileNumber;              //�ֻ�����(�ƶ�)  TEL;CELLCELL   
	CString m_MobileHome;                //�ֻ�����(��ͥ)  TEL;CELL;HOME
	CString m_MobileWork;                //�ֻ�����(�칫)  TEL;CELL;WORK
	CString m_PhoneNumber;               //�绰����        TEL
	CString m_PhoneHome;                 //�绰����(��ͥ)  TEL;HOME
	CString m_PhoneWork;                 //�绰����(�칫)  TEL;WORK
	CString m_Email;                     //˽������  EMAIL
	CString m_HomeAddress;               //��ͥ��ַ  ADR
	CString m_Company;                   //��˾����  ORG1 ORG��һ����
	CString m_Birthday;                  //��������  BDAY	
	CString m_Fax;                       //���� TEL;FAX 
	CString m_Departments;               //����  ORG2 ORG�ڶ�����  
	CString m_Duties;                    //ְ��  TITLE 

	ePathType m_PathType;                //��ϵ��λ��

	sContactInfo()
	{
		m_PathType = PATH_UNKOWN;
	}
};


/*********************************��ϵ�˲��������****************************************/
enum eContactCmdType
{
	CONTACT_REQUEST_CMD,                  //������ϵ��������������
	CONTACT_ADD_CMD,                      //�����ϵ������
	CONTACT_DELTE_CMD,                    //ɾ����ϵ������
	CONTACT_DELTE_ALL_CMD,                //ɾ��������ϵ��
	CONTACT_EDIT_CMD,                     //�༭��ϵ������
	CONTACT_BACKUP_CMD,                   //��ϵ�˱���

	CONTACTGROUP_REQUEST_CMD,             //������ϵ�˷���
	CONTACTGROUP_ADD_CMD,                 //�����ϵ�˷���
	CONTACTGROUP_DELETE_CMD,              //ɾ����ϵ�˷���
	CONTACTGROUP_DELETE_ALL_CMD,              //ɾ��������ϵ�˷���
	CONTACTGROUP_EDIT_CMD,                //�༭��ϵ�˷���
};

struct sContactCmd                        //��ϵ����������
{
	eContactCmdType    m_CmdType;         //��������
	DWORD              m_CmdId;           //����ID
	WPARAM             m_CmdParam;        //�������
	LPARAM             m_CmdParamCount;   //�����������
};



//���������Ϣ
struct sGroupInfo
{
	CString m_GroupID;          //����ID
	CString m_GroupName;        //��������
	int     m_ContactCount;     //��ϵ����
	bool    m_IsSystem;         //�Ƿ�����ϵͳ����

	sGroupInfo()
	{
		m_ContactCount = 0;
		m_IsSystem     = false;
	}
};

//����ͨ����¼
struct sCallLogInfo
{
	CString m_LogName;          //��¼�� ����_ʱ��
	CString m_PhoneNumber;      //�绰����
	CString m_CallName;         //������
	CString m_CallType;         //��������  receivedcall/outgoing/incoming/missed
	CString m_Date;             //����
	CString m_DurationTime;     //ͨ��ʱ��
};

/*********************************���Žṹ�嶨��****************************************/
struct sSmsInfo
{
	CString   m_SmsID;                    //����ID   ���ŵ�Ψһ��־
	CString   m_ContactName;              //��ϵ������
	CString   m_SmsBody;                  //��������
	CString   m_SmsCaller;                //���ź���
	CString   m_TimeStamp;                //����ʱ���
	eSmsStaus m_SmsStaus;                 //����״̬
	eSmsBox   m_SmsBox;                   //���ű�־

	sSmsInfo()
	{
		m_SmsBox = SMSBOX_INBOX;
		m_SmsStaus = SMS_NOT_READ;
	}
};

//���Ͷ���
struct sSendSmsInfo
{
	CString m_PhoneNumber;                //�ֻ�����
	CString m_Text;                       //�ı���Ϣ
};

/*********************************���Ų��������******************************************/
enum eSmsCmdType
{
	SMS_REQUEST_CMD,                  //�������������������
	SMS_ADD_CMD,                      //��Ӷ�������
	SMS_DELTE_CMD,                    //ɾ����������
	SMS_DELTE_ALL_CMD,                //ɾ�����ж���
	SMS_EDIT_CMD,                     //�༭��������
	SMS_BACKUP_CMD,                   //���ű���
	SMS_SEND_CMD,					  //���Ͷ���
};

struct sSmsCmd                        //������������
{
	eSmsCmdType        m_CmdType;         //��������
	DWORD              m_CmdId;           //����ID
	WPARAM             m_CmdParam;        //�������
	LPARAM             m_CmdParamCount;   //�����������
};


/*********************************�ļ��ṹ�嶨��****************************************/
struct sFileInfo
{
	CString m_FileName;                    //�ļ������ļ��е�����
	CString m_FileAuthority;               //�ļ�Ȩ�ޣ�'R'������Զ�ȡ��'W'�������д�룬'D'�������ɾ��
	CString m_FileSize;                    //�ļ���С
	CString m_FileCreateTime;              //�ļ�����ʱ��
	bool    m_IsFileDir;                   //�Ƿ����ļ���
	ePathType m_PathType;                  //�ļ������ļ�λ��

	CString m_FileTime;                    //�ļ�ʱ�� ��Ƶ ��Ƶ��Ҫ
	CString m_FileTile;                    //�ļ�����
	CString m_Format;                      //�ļ���ʽ
	CString m_Special;                     //�ļ�ר��
	CString m_Artist;                      //������
	CString m_ThumbPath;                   //����ͼ·��
};


/*********************************�ֻ����ӽṹ�嶨��****************************************/

//����USB���ӽṹ��
struct sUsbConnectInfo
{
	CString m_PhoneName;              //�ֻ�����
	CString m_DeviceId;               //�豸ID ���ص�ʹ��
	CString m_DriveUrl;               //��������·��
	CString m_PhoneImageUrl;          //�ֻ�ͼƬ
	CString m_PhoneScreenInfo;        //�ֻ�������Ϣ
	CString m_PhoneVidPid;            //�ֻ��ĳ���ID�Ͳ�ƷID
	BOOL    m_IsInstallDrive;         //�Ƿ��Ѿ���װ������
};

//����wifi���ӽṹ��
struct sWifiConnectInfo
{
	CString m_WiFiIp;             //IP��ַ
	CString m_SecurityCode;       //��֤��
	CString m_PhoneName;          //�ֻ�����
	CString m_ID;                 //�ֻ�Ψһ��ʶ

	DWORD   m_WiFiPort;           //�˿�
	DWORD   m_WiFiFlag;           //WIFI��ʶ
	DWORD   m_IsAddFlag;          //�Ƿ���ӱ�ʶ
};

 //�ֻ�״̬
 struct sPhoneStatus                     
 {
	 CString m_PhoneDesId;                //�ֻ�����id
	 BOOL    m_IsOffLine;                 //�ֻ��Ƿ���offline��
 };
