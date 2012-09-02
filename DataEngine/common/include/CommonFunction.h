#pragma once

#include "DataDefine.h"



// Input: strSrc,ԭʼ�ַ��� abc&defg&123
// strEsc ��Ҫת����ַ���������"&"
// strReplaceEsc ����ת����ַ���������"&amp;"
// Output: abc&amp;def&amp;123
// ��ԭʼ�ַ����������ַ���ת����ת���ַ���
CString ReplaceStr( CString strSrc, CString strSub, CString strReplace ); // ת���ַ�����


/*****************************************ת�뺯��****************************************/
//��GBK��ת�뵽��UTF8
void TransGBKToUtf8(CString&  strGBK);

//��Utf8��ת�뵽��GBK
void TransUtf8ToGBK(CString&  strUtf8);

//��GBK��ת�뵽��Unicode
void TransGBKToUnicode(CString&  strGBK);

//��UTF8 ת�뵽 UNICODE
void TransUtf8ToUnicode(CString&  strUtf8);

//��Uincode ת�뵽UTF8
void TransUnicodeToUtf8(CString& strUnicode);

//��UTF8 ת�뵽 URLCODE
void TransUtf8ToURLCode(CString& strUtf8);

//��UNICODE ת�뵽��URLCODE
void TransUnicodeToURLCode(CString& strUnicode);

//��UNICODE ת�뵽��BASE64
void TransUnicodeToBase64(CString& strUnicode);

//��Base64 ת�뵽��Unicode
void TransBase64ToUnicode(CString& strBase64);

//���ַ���ת��Ϊunicode
wchar_t* TransUtf8CharToUncodeWchar(char *utf8);

//���ַ���ת��Ϊutf-8
char* TransUncodeWcharToUtf8Char(const wchar_t *unicode);


/*****************************************ִ��adb����****************************************/
//ִ��adb����
bool ExecAdbCmd(CString CmdStr,CString& CmdRetStr);



/*****************************************��������****************************************/
//��ȡӦ�ó���·��
CString GetAppPath(void);

//��ȡӦ�ó���·��
CString GetAppPath2(CString Temp);

//�ж��ļ��Ƿ����
bool IsFilesExit(CString FileName);

//��ȡ����ĸ ���� 1 ����ĸ 0 ȫ��ĸ
CString GetFirstLetter(CString Name, int Type=1);

//��װ�ֻ�Ӧ�ó���
bool InstallPhoneApp(CString PhoneDes,CString AppName,bool IsReInstall,ePathType Type=PATH_PHONE);


//��ȡAndroid�豸�б�
void GetAndroidDeviceList(vector<sPhoneStatus>& DeviceList);

//��ȡAndroid�豸�б�
void GetApplicationPath(CString& Path);





//д�˲�����־�ļ�
void WriteLog(const char* Format,...);

//д�˲�����־�ļ�
void WriteLog(const wchar_t* Format,...);