#pragma once
#include <stdio.h>
#include <tlhelp32.h>
#include <winnls.h>
#include <windows.h>
#include <dbt.h> 
#include <vector>
#include <string>

using std::vector;

#define   WINVER   0x0500 

char *  Time2String(char * szDT, time_t time);
void  KillAdb(void );

/// �鿴������
int  PSAdb(void);

/// �鿴������
vector<DWORD>  SearchAdb(void);

const DWORD PIPE_TIME_OUT  = 30*1000;   // 30 seconds

void ConvertGBKToUtf8(CString&  strGBK);
void ConvertUtf8ToGBK(CString&  strUtf8);
int ConvertGBKToUnicode(CString&  strGBK,char * pBuf);
int ConvertUtf8ToUnicode(CString&  strUtf8, char * pBuf);
void Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage);
CString ConvertUnicodeToGBK(unsigned short * pUcs,int nNum);


// �ַ���ת������
wchar_t* ConvertToUnicodeFromUtf8(char *utf8);
char* ConvertFromUnicodeToUtf8(const wchar_t *unicode);

// ���ļ�ʱ�����Ϊϵͳʱ���ʽ:yyyy-mm-dd
char* EnCodeFileTimeToSystemTime(FILETIME);

// �ı���ʽ��ϵͳʱ�����Ϊ�ļ�ʱ��   ϵͳʱ���ʽΪ:yyyy-mm-dd
FILETIME DeCodeSystemTimeToFileTime(char*);

// ת������״̬
char* GetSmsState(unsigned short);


//������Ǹ�ɶ�����Ǹ�ɶ
 void runCmdAndResult(LPSTR argCmd, CString& argResult,bool IsReadResult=true);

 // ��װӦ�ó���ר��
 //void runAdbInstallApp(LPSTR argCmd, CString& argResult,bool IsReadResult=true);

 //��ȡ��ǰִ���ļ�Ŀ¼
 CString GetCurrentDir();

  //��ȡ��ǰʱ��
char *  Time2String(char * szDT, time_t time);


// Input: strSrc,ԭʼ�ַ��� abc&defg&123
// strEsc ��Ҫת����ַ���������"&"
// strReplaceEsc ����ת����ַ���������"&amp;"
// Output: abc&amp;def&amp;123
// ��ԭʼ�ַ����������ַ���ת����ת���ַ���
CString ReplaceStr( CString strSrc, CString strSub, CString strReplace ); // ת���ַ�����
/*
// ��������Ҫת����ַ���ȫ��ת��
CString GetEscChar( CString strSrc );
*/
/**
* @brief   ʵ���ַ����滻
* @param   orignStr Դ��
* @param   oldStr  ���ҵĴ�
* @param   newStr  �滻���´�
* @return  �����޸ĺ�Ĵ�
*/
wstring ReplaceWstr(const wstring& orignStr, const wstring& oldStr, const wstring& newStr);
