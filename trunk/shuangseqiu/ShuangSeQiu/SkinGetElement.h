/**************************************************************
*  ˵��: ���ڹ���������������Ƥ��Ԫ�ص���  ���õ�ʵ��ģʽ   *
*  ����: ����                                               *
*  ʱ��: 2011-09-14                                           *
***************************************************************/

#pragma once

class CSkinGetElement
{
public:
	static CSkinGetElement *InitSkinInstance();
	
	static void DeleteSkinInstance();

	CFont *GetSpecialFont(int size, int weight=700);

	//��ȡ���»��ߵ�����
	CFont *GetUnlineFont(int size, int weight=700);

private:
	CSkinGetElement();
	~CSkinGetElement();

	 CString GetCompatibleFontName(bool HasFont=false);

	 //���ݲ���ϵͳ�任�����С�������źڴ�С���룬���ݲ���ϵͳ������С�������ֺ�=�ź��ֺ�-5
	 int	 GetCompatibleFontSize(int orgFontSize,bool fontByOs=true);

protected:

private:
	map<long, CFont *> m_FontMap;
	map<long, CFont* > m_UnlineFontMap;
	static CSkinGetElement *SkinInstance;

};
