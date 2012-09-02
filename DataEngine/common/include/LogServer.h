#pragma once
/***********************************************************************************
* ˵��      ��  CLogServerΪ��־�������ڴ�����־�ϴ���д�ļ�                     *
* ������    ��  ̷����                                                             *
* ��������  ��  2012-1-10                                                          *
***********************************************************************************/

#include <map>
#include <vector>

using namespace::std;

class CLogServer
{
public:

	//��־�ļ�����
	enum eLogFileType{ MAIN_LOG_FILE_TYPE, //��־�����ļ�
                 };


	//������־����
	static void StartLogServer();

	//�ر���־����
	static void StopLogServer();

	//���ö���ϴ�һ����־
	static void SetUpLogTime(long TimeLog);                     //TimeLog ����Ϊ��λ
	
	//���ö��д��־���ļ���
	static void SetWriteLogTime(long TimeLog);                  //TimeLog ����Ϊ��λ

	//������־�ļ���С 
	static void SetLogSize(long LogSize);                       //LogSize ��־�ļ���С ��MΪ��λ

	//д�˲�����־�ļ�
	static void WriteLog(CString LogStr,eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);  //LogStr ��־,LogFileType ��־�ļ����ͣ���ǰֻ֧�ֲ�����־

	//д�˲�����־�ļ�
	static void WriteLog(const char* Format,...);

	//д�˲�����־�ļ�
	static void WriteLog(const wchar_t* Format,...);

private:
	
	//��־�����߳�
	static DWORD WINAPI ManageLogThread(LPVOID lpVoid);

	//��־�ϴ��߳�
	static DWORD WINAPI UpLogThread(LPVOID lpVoid);

	//��ȡ��־ͷ��
	static CString GetLogHeader(eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);

	//��ȡ��־�ļ���
	static CString GetLogFileName(eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);
	
	//������־�ļ���
	static vector<CString> GetLogFileNameList(BOOL IsGetTempLog=FALSE,eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);

	//��ȡ��־�ļ�·��
	static CString GetLogFileDir(eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);

	//�رվ��
	static void CloseEventHandle();

	//��ȡ��ǰʱ��
	static CString GetLocalTime();

	//��������
	static void InsertData(CString StrData,eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);

	CLogServer(void);

	~CLogServer(void);

private:
	static long                                m_UpLogTime;              //��־�ϴ�ʱ����
	static long                                m_WriteLogTime;           //��־����ʱ����
	static long                                m_LogFileSize;
	static HANDLE                              m_StopEvent;              //�����߳�ֹͣ�¼�
	static HANDLE                              m_StopUpEvent;            //��־�ϴ�ֹͣ�¼�
	static HANDLE                              m_WriteLogEvent;          //д��־�¼�
	static HANDLE                              m_UpLogEvent;             //��־�ϴ��¼�
	static HANDLE                              m_LogThread;              //Log�����߳̾��
	static HANDLE                              m_UpLogThread;            //�ϴ���־�߳̾��
	static CRITICAL_SECTION                    m_CriticalSection;        //�ٽ���
	static map<eLogFileType,vector<CString>>   m_CaheLog;                //��־������Ϣ

//	static CString m_strDiskSerial; // Ӳ�����к�
//	static CString m_strMacAddress; // ������ַ
//	static CString m_strDerivation; // Ӧ�ó���������ʶ
};
