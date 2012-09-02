/* ------------------------------------------------------------------------- 
//  FileName    :   GenFirstPYLetter.h 
//  Creator     :   debehe 
//  Date        :   2009/9/28 17:40:24 
//  Brief       :   ��Ҫ��MultiByte������ȷת�� 
//                  Unicodeת��MultiByteʱ��Ҫ��W2A 
// 
//  $Id: $ 
// -----------------------------------------------------------------------*/  
// How to use:  
//   
// std::wstring strA = L"WPS���ӱ��";  
// std::wstring strOutput;  
// BOOL bRet = GenFirstPYLetter(strA, strOutput);  
//   
// ���Ӧ����:  
// strOutput == L"WPSDZBG";  
// bRet == TRUE; // ����ĸ��ͷ  
  
// -------------------------------------------------------------------------  
  
#ifndef __GETFIRSTLETTER_H__  
#define __GETFIRSTLETTER_H__  
  
#include <Windows.h>  
#include <string>  
using std::string;
// -------------------------------------------------------------------------  
  
/* 
@ Function  : GenFirstPYLetter 
@ brief     : ת������Ϊƴ������ĸ 
@ parameter : [in]strName 
@ parameter : [out]strResult 
@ return    : �Ƿ�����ĸ��ͷ 
@ remark    :  
@ Date      : 2009/9/28 20:37:19 linyehui 
@*/  
BOOL GenFirstPYLetter(std::string strName, std::string&strResult );  
  
BOOL GenFirstPYLetter(std::wstring strName, std::wstring&strResult);  

string GetPinYinLetter(int nCode); 
// -------------------------------------------------------------------------  
// $Log: $  
  
#endif /* __GETFIRSTLETTER_H__ */