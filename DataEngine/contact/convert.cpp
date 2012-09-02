
#include "stdafx.h"
#include<stdlib.h>
#include"convert.h"
#include"fstream"
#include".\vocl\export.h"
#include"base64.h"
#include <time.h>
#include <atlenc.h>
#include"../CommonApi/common.h"
 
//�������Ϊ�ǵ������������ڸ����û�ָ���ı������ͣ�������������Ϊ����д����Ŀ��
//7IBTΪĬ�ϱ��룬����д��������ı��뷶Χ������ָ���ļ�>3��<0����Ĭ�ϵı���(7BIT)����
//���ڶ���Ĭ�ϵĹ���������������Ҳ��á����Ժ�������汾ʹ�á�
void mySetEncoding(VProperty* vp,int encoding)
{
	//if(encoding==0||encoding>3||encoding<0)
	//	;//vp->addParameter(L"ENCODING",L"7BIT");֮����д�ϣ�����Ϊ����������Ϊ����ʱ���ñ���QUOTED-PRINTABLE��������7BIT��������Ӣ���ַ���д���뷽ʽʱΪ��7BIT
	//else if(encoding==1)
	//	vp->addParameter(L"ENCODING",L"BASE64");
	//else if(encoding==2)
	//	vp->addParameter(L"ENCODING",L"QUOTED-PRINTABLE");
	//else
	//	vp->addParameter(L"ENCODING",L"8BIT");
}

//��������Ǵ������ҵģ���ʱ��úõ�ȥ�о�һ��,
// ���ڶ�QUOTED-PRINTABLE���н��룬ת���ɽ���qpencoding֮ǰ�ı�ʾ��ʽ
string Qp_decode(string src)
{
    // ������ַ�����     
    int i = 0;
    string dst;
    char tmp=0;
    while (i < src.size())
    {
        if (src[i] == '=')        // �Ǳ����ֽ�     
        {
            if(i<src.size()-2)
            {
                char ch1=src[i+1];
                char ch2=src[i+2];
                if ((src[i+1]=='\r')||(src[i+1]=='\n')) continue;
                tmp = ((ch1>'9')?(ch1-'A'+10):(ch1-'0'))*16+((ch2>'9')?(ch2-'A'+10):(ch2-'0'));
                dst+=tmp;
                i += 3;
            }
        }
        else        // �Ǳ����ֽ�       
        {
            dst += src[i];
            i++;
        }

    }       // ����Ӹ�������     
    dst += '\0';
    return dst;
}

//�����������Ǵ������ѵ��ġ�
//��char* ת��wchar_t*��ʵ�ֺ������£�  
char* w2c(char *pcstr,const wchar_t *pwstr, size_t len)  
{  
	int nlength=wcslen(pwstr);  
	//��ȡת����ĳ���  
	int nbytes = WideCharToMultiByte( 0, // specify the code page used to perform the conversion  
	0,         // no special flags to handle unmapped characters  
	pwstr,     // wide character string to convert  
	nlength,   // the number of wide characters in that string  
	NULL,      // no output buffer given, we just want to know how long it needs to be  
	0,  
	NULL,      // no replacement character given  
	NULL );    // we don't want to know if a character didn't make it through the translation  
	// make sure the buffer is big enough for this, making it larger if necessary  
	if(nbytes>len)   nbytes=len;  
	// ͨ�����ϵõ��Ľ����ת��unicode �ַ�Ϊascii �ַ�  
	WideCharToMultiByte( 0, // specify the code page used to perform the conversion  
	0,         // no special flags to handle unmapped characters  
	pwstr,   // wide character string to convert  
	nlength,   // the number of wide characters in that string  
	pcstr, // put the output ascii characters at the end of the buffer  
	nbytes,                           // there is at least this much space there  
	NULL,      // no replacement character given  
	NULL );  
	return pcstr ;  
} 

//���ǰ�asii�ַ�ת��Ϊunicode�ַ�����������ͬ��ԭ��  
void c2w(wchar_t *pwstr,size_t len,const char *str)  
{  
	if(str)  
    {  
      size_t nu = strlen(str);  
      size_t n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,NULL,0);  
      if(n>=len)n=len-1;  
      MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,pwstr,(int)n);  
      pwstr[n]=0;  
    }  
}  

//��Ϊ�绰�����Ͷ࣬������һ������ר��ʵ������ ��һ��������ֵ�ĺ��壺
//1 cell 2 cell home 3 cell work 4 tel 5 tel home 6 tel work 7tel fax
//���һ������encodingΪencoding��ʽ�����ڸ�����mySetEncoding(..)���ݲ�����
//�ڶ�������ΪҪ����TEL��Ŀд���VCARD���󣬵���������ΪTEL��ֵ�����绰���롣
bool AddTELToVObject(int type,VObject* vbp,const char telstr[TR_MAX_CONTACT_ID_LENGTH])
{
	bool ret=false;
	VProperty* vp=0;
	if(type>7||type<1||telstr[0]=='\0')//���tel��ֵΪ���򲻼���
		return false;

	wchar_t mywchar[200];//�ַ�����ʽת��
	 mywchar[0]='\0'; mywchar[1]='\0';
	mywchar[0]='\0';
	c2w(mywchar,200,telstr);

	vp=new VProperty(L"TEL");
	if(vp==0)
		return false;
	vp->setValue(mywchar);
	//mySetEncoding(vp,encoding);
   if(type==1)//cell
   {
		//vp->addParameter(L"TYPE",L"CELL");//�����ָ�ʽ�����ɵ���TEL;TYPE=CELL:telnum,��ȻҲ�ԣ���������ϰ�ߡ�
		vp->addParameter(L"CELL",NULL);
   }
   else if(type==2)
   {
		vp->addParameter(L"HOME",NULL);
		vp->addParameter(L"CELL",NULL);
   }
   else if(type==3)
   {
	   vp->addParameter(L"WORK",NULL);
	   vp->addParameter(L"CELL",NULL);

   }
   else if(type==4)
   {
   }
   else if(type==5)
   {
		vp->addParameter(L"HOME",NULL);
   }
   else if(type==6)
   {
		vp->addParameter(L"WORK",NULL);
   }
    else if(type==7)
   {
		vp->addParameter(L"FAX",NULL);
   }
   vbp->addProperty (vp);
   delete vp;
   return true;
}

//�����������һ�����������������һ����ַ��vcard��
//type  Ϊ������0ΪHOME
//[PostOfficeAddress]; [ExtendedAddress];[Street];[Locality];[Region];[Postalcode];[Country]
//���б����ǹ���ӵ�ַר�õġ�
char pos[65];	char ext[105];	char str[105];	char loc[55];	char reg[55];	char pcode[25];	char con[55];
void tostore(int begin,int end,const char homeaddress[],int ind)
{
	if(ind==0)//��postaddress��ֵ
	{
		int i=0;
		for(;i<end;i++)
			pos[i]=homeaddress[i];
		pos[i+1]='\0';
	}
	else if(ind==1)//extended address
	{
		int j=0;
		for(int h=begin;h<end;h++)
		{	ext[j]=homeaddress[h];	j++;	}
		ext[j+1]='\0';
	}
	else if(ind==2)//street
	{
		int j=0;
		for(int h=begin;h<end;h++)
		{	str[j]=homeaddress[h];	j++;	}
		str[j+1]='\0';
	}
	else if(ind==3)//locality
	{
		int j=0;
		for( int h=begin;h<end;h++)
		{	loc[j]=homeaddress[h];	j++;	}
		loc[j+1]='\0';
	}
	else if(ind==4)//region
	{
		int j=0;
		for( int h=begin;h<end;h++)
		{	reg[j]=homeaddress[h];	j++;	}
		reg[j+1]='\0';
	}
	else if(ind==5)//pcode
	{
		int j=0;
		for( int h=begin;h<end;h++)
		{	pcode[j]=homeaddress[h];	j++;	}
		pcode[j+1]='\0';
	}
	else if(ind==6)//contry
	{
		int j=0;
		for(int h=begin;h<end;h++)
		{	con[j]=homeaddress[h];	j++;	}
		con[j+1]='\0';
	}
}
void AddADRtoVObject(int type,VObject* vbp,const char homeaddress[TR_MAX_CONTACT_ID_LENGTH])
{
	pos[0]='\0';ext[0]='\0';str[0]='\0';loc[0]='\0';reg[0]='\0';pcode[0]='\0';con[0]='\0';
	//�����ÿһ���ֶ�
	int i=0,ind=0;// i���ڼ�����ind���ڱ�־�����Ǹ�������д����
	int begin=0,end=0;
	for(;homeaddress[i]!='\0'&&i<TR_MAX_CONTACT_ID_LENGTH;i++)
	{
		if(homeaddress[i]==';')
		{
			if(ind==0) end=i;// ���ڵ�һ�������ø���begin��ֵ
			else
			{
				begin=end+1; end=i; 
			}
			tostore(begin,end,homeaddress,ind);
			ind++;
		}
	}
	begin=end+1; end=i; 
	tostore(begin,end,homeaddress,ind);//�����һ������ֵ�ӵ����

	if(pos[0]=='\0'&&ext[0]=='\0'&&str[0]=='\0'&&loc[0]=='\0'&&reg[0]=='\0'&&pcode[0]=='\0'&&con[0]=='\0')
		return;
	else
	{
		//��ÿ���ֶκͲ����ӵ����
		VProperty* vp=0;
		wchar_t mywchar[107];//�ַ�����ʽת��
		mywchar[0]='\0';mywchar[1]='\0';
		vp=new VProperty(L"ADR");//��������
		if(vp!=0)
		{
			if(type==0)
				vp->addParameter(L"HOME",NULL);//�������

			//����ֵ		char pos[65],ext[105],str[105],loc[55],reg[55],pcode[25],con[55];
			c2w(mywchar,107,pos);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,ext);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,str);
			vp->setValue(mywchar);
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,loc);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,reg);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,pcode);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,con);
			vp->setValue(mywchar);

			vbp->addProperty (vp);
			delete vp;
		}
	}
}
//����������ڻ�ȡ��ǰʱ�䣬VCARD��ʽ��REV��Ŀ��Ҫ�õ���ʱ��Ļ�ȡ���ѣ�
//���ô������Ҫ������д��char�����У��Ƚ����׳���ʱ�亯����ȡ��ʱ��ĸ�ʽ
// ����Ҫ��ʱ���ʽ����һ������ʱ�䣬�·ݣ����ڶ�����λ�ģ����ȽϺñȽϺ�
//
void gettime(char ch[])
{//422T222 ��15��
	ch[0]='\0';
	char* temp=new char[30];
	temp[0]='\0';

	time_t now=time(&now); // �������� 
	temp=ctime(&now);//���ڻ�ȡ��ݣ�������������ȡ�����Ϊ��λ�����Ϲ淶��
	int i;
	for(i=0;temp[i]!='\0';i++) ;
    strcpy(ch,&temp[i-5]);

	temp[0]='\0';//��ȡ�·� ��
	now=time(&now);//temp format 12/27/10
	_strdate(temp);
	ch[4]=temp[0];
	ch[5]=temp[1];
	ch[6]=temp[3];
	ch[7]=temp[4];

	ch[8]='T';
	
	temp[0]='\0';//��ȡʱ��14:26:36
	_strtime(temp);
	ch[9]=temp[0];
	ch[10]=temp[1];
	ch[11]=temp[3];
	ch[12]=temp[4];
	ch[13]=temp[6];
	ch[14]=temp[7];
	ch[15]='\0';
}


//��sContactInfo�е�����ת����card2.1��ʽ���ַ����� 
//��b��ֵΪtrueʱ��дversion���ԣ�Ϊfalse��д��
int innerConvertsContactInfotoVcard21(const sContactInfo& trPbItem, wstring & myvcard21str, bool bIsWriteVersion)
{
	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");
	if (pMyVcard == NULL)
	{
		return FAILNEW_VCARDOBJECT;
	}

	//
	VProperty* pVProperty = NULL;//c2w(wchar_t *pwstr,size_t len,const char *str)
	wchar_t wchTemp[500];

	//------------------------------------------
	// ���ͷ
	pVProperty = new VProperty(L"BEGIN", L"VCARD");//Ϊ��Ҫ����д�����Բο�WinContact::toString() ��������vocl��Ŀ�С�
	if(pVProperty != NULL)
	{
		pMyVcard->addProperty(pVProperty);
		delete pVProperty;
		pVProperty = NULL;
	}
	else
	{
		if (pMyVcard)
		{
			delete pMyVcard;
			pMyVcard = NULL;
		}
		return ALLO_FAIL;
	}

	// ��Ӱ汾
	if(bIsWriteVersion)
	{
		pVProperty = new VProperty(L"VERSION", L"2.1");
		if(pVProperty != NULL)
		{
			pMyVcard->addProperty(pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}
 
	//����
	if(trPbItem.)
	{
		memset(wchTemp, 0, 500);
		wchar_t* pwch = ConvertToAnsiFromUtf8(trPbItem.name);
		//c2w(wchTemp, 500, trPbItem.name);
		wcscpy(wchTemp, pwch);
		if (pwch)
		{
			delete pwch;
			pwch = NULL;
		}
		pVProperty = new VProperty(L"N", wchTemp);
		if(pVProperty != NULL)
		{
			pMyVcard->addProperty(pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}


		pVProperty = new VProperty(L"FN", wchTemp);
		if(pVProperty != NULL)
		{
			pMyVcard->addProperty(pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	//TEL
	AddTELToVObject(1, pMyVcard, trPbItem.mobilenumber);
	AddTELToVObject(2, pMyVcard, trPbItem.mobilehome);
	AddTELToVObject(3 ,pMyVcard, trPbItem.mobilework);
	AddTELToVObject(4 ,pMyVcard, trPbItem.phonenumber);
	AddTELToVObject(5, pMyVcard, trPbItem.phonehome);
	AddTELToVObject(6, pMyVcard, trPbItem.phonework);
	AddTELToVObject(7, pMyVcard, trPbItem.fax);

	// ����
	if(trPbItem.email[0]!='\0')
	{
		pVProperty = new VProperty(L"EMAIL");
		if(pVProperty != NULL)
		{
			memset(wchTemp, 0, 500);
			c2w(wchTemp, 500, trPbItem.email);
			pVProperty->setValue (wchTemp);
			pMyVcard->addProperty(pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	//�����ͥ��ַ make by kjb for android
	//if(trPbItem.homeaddress[0]!='\0')
	//{
	//	VProperty* vp=new VProperty(L"LABEL");//��ͥ��ַ
	//	if(vp!=0)
	//	{
	//		wchar_t mywchar[200];
	//		mywchar[0]='\0';
	//		mywchar[1]='\0';
	//		c2w(mywchar,200,trPbItem.homeaddress);
	//		vp->setValue (mywchar);
	//		vp->addParameter(L"HOME",NULL);
	//		//vp->addParameter(L"TYPE",L"HOME");
	//		//mySetEncoding(vp,enchset.homeaddressEn);
	//		pMyVcard->addProperty (vp);
	//		delete vp;
	//		vp=0;
	//	}
	//	else
	//		return ALLO_FAIL;
	//}
	AddADRtoVObject(0, pMyVcard, trPbItem.homeaddress);

	

	//��˾������
	if(trPbItem.company[0]!='\0'||trPbItem.departments [0]!='\0')
	{
		pVProperty = new VProperty(L"ORG");
		if(pVProperty != NULL)
		{
			// �������м��빫˾
			if(trPbItem.company[0]!='\0')
			{
				memset(wchTemp, 0, 500);
				c2w(wchTemp, 500, trPbItem.company);
				pVProperty->setValue (wchTemp);
			}
			else
			{
				pVProperty->setValue(L"");
			}

			// �������в��벿��
			if(trPbItem.departments [0]!='\0')
			{
				memset(wchTemp, 0, 500);
				c2w(wchTemp, 500, trPbItem.departments);
				pVProperty->setValue (wchTemp);
			}

			// ���
			pMyVcard->addProperty (pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	//����
	if(trPbItem.birthday[0]!='\0')
	{
		pVProperty = new VProperty(L"BDAY");
		if(pVProperty != NULL)
		{
			memset(wchTemp, 0, 500);
			c2w(wchTemp, 500, trPbItem.birthday);
			pVProperty->setValue (wchTemp);

			// ���
			pMyVcard->addProperty (pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	// ְ�� title
	if(trPbItem.duties[0] !=  '\0')
	{
		pVProperty = new VProperty(L"TITLE");
		if(pVProperty != NULL)
		{
			memset(wchTemp, 0, 500);
			c2w(wchTemp,500,trPbItem.duties);
			pVProperty->setValue (wchTemp);

			// ���
			pMyVcard->addProperty (pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	// ��ID��
	if(trPbItem.GroupIDs[0] !=  '\0')
	{
		pVProperty = new VProperty(L"GROUP");
		if(pVProperty != NULL)
		{
			//ѭ�������
			memset(wchTemp, 0, 500);
			c2w(wchTemp, 500, trPbItem.GroupIDs);

			wstring wstrGroupID;
			wstring wstrTemp(wchTemp);
			wstring::size_type pos = wstrTemp.find(L";");

			while (pos != wstring::npos)
			{
				wstrGroupID = wstrTemp.substr(0, pos);
				wstrTemp = wstrTemp.substr(pos+1);

				if (!wstrGroupID.empty())
				{
					pVProperty->setValue(wstrGroupID.c_str());
				}

				pos = wstrTemp.find(L";");
			}

			if (wstrTemp.length() != 0)	//û���ԡ�;����β
			{
				pVProperty->setValue(wstrTemp.c_str());
			}

			// ���
			pMyVcard->addProperty (pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	// ��������޸ĵ�ʱ��
	pVProperty = new VProperty(L"REV");
	if(pVProperty != NULL)
	{
		char chTime[22];
		memset(chTime, 0, 22);
		gettime(chTime);
		memset(wchTemp, 0, 500);
		c2w(wchTemp, 500, chTime);
		pVProperty->setValue (wchTemp);

		// ���
		pMyVcard->addProperty(pVProperty);
		delete pVProperty;
		pVProperty = NULL;
	}
	else
	{
		if (pMyVcard)
		{
			delete pMyVcard;
			pMyVcard = NULL;
		}
		return ALLO_FAIL;
	}

	//
	pVProperty = new VProperty(L"END", L"VCARD");
	if(pVProperty != NULL)
	{
		// ���
		pMyVcard->addProperty (pVProperty);
		delete pVProperty;
		pVProperty = NULL;
	}

	//
	WCHAR* wchar1=pMyVcard->toString();
	myvcard21str.empty ();
	myvcard21str+=wchar1;
	if (wchar1)
	{
		delete[] wchar1;
		wchar1 = NULL;
	}
	//delete wchar1;//���������Ǹ�����Ҫ���

	if (pMyVcard)
	{
		delete pMyVcard;
		pMyVcard = NULL;
	}
	return 0;
}
 


int ConverTrpbItemToVcard21Str(const sContactInfo& trPbItem, wstring & myvcard21str, bool bIsWriteVersion)
{

	return innerConvertsContactInfotoVcard21(trPbItem, myvcard21str, bIsWriteVersion);
}


/*******************************************************************************************************************************
* ��sContactInfo��ʽ������ת����VCard2.1��ʽ������浽ָ�����ļ��С�
********************************************************************************************************************************/
int ConvertsContactInfotoVcard21andWriteToFile(const sContactInfo& trPbItem, WCHAR* pwchPath)
{
	// ����������
	wstring str=L"\0";
	int rv = innerConvertsContactInfotoVcard21(trPbItem, str, true);
	if (rv != 0)
	{
		return -1;
	}

/*	// д��
	FILE* fpFile = NULL;

	// to Utf-8 path
	int nLen = WideCharToMultiByte( CP_ACP, 0, pwchPath, -1, 0, 0, 0, 0 );
	char* pBuffer8Path = new char[nLen+1];
	WideCharToMultiByte( CP_ACP, 0, pwchPath, -1, pBuffer8Path, nLen, 0, 0 );
	pBuffer8Path[nLen] = '\0';

	// ���ļ�
	fpFile = fopen(pBuffer8Path, "wb");
	if ( fpFile == NULL )
	{
		if (pBuffer8Path)
		{
			delete[] pBuffer8Path;
			pBuffer8Path = NULL;
		}
		return FALSE;
	}

	// to Utf-8
	nLen = WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, 0, 0, 0, 0 );
	char* pBuffer8 = new char[nLen+1];
	WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, pBuffer8, nLen, 0, 0 );
	pBuffer8[nLen] = '\0';

	//д��
	fwrite(pBuffer8, nLen, 1, fpFile);
	fclose(fpFile);

	//
	if (pBuffer8Path)
	{
		delete[] pBuffer8Path;
		pBuffer8Path = NULL;
	}*/


	// д���ļ�
	wofstream fout;//=ofstream(L"d:\my.txt",wios::app);
	fout.open (pwchPath, ios_base::binary );
	const wchar_t * pch = str.c_str ();
	fout<<str;
	return 0;
}

/*******************************************************************************************************************************
* ��������sContactInfo��ʽ������ת����VCard2.1��ʽ������浽ָ�����ļ��С�
********************************************************************************************************************************/
int ConvertsContactInfotoVcard21andWriteToOneFile(const vector< sContactInfo> &m_PbContactsMgr, WCHAR* path)
{
	wstring str=L"\0";
	wofstream fout;//=ofstream(L"d:\my.txt",wios::app);
	fout.open (path);
	fout<<L"BEGIN:VCARD\nVERSION:2.1\n";
	int num=m_PbContactsMgr.size();
	for(int i=0;i<num;i++)
	{
		int j=innerConvertsContactInfotoVcard21(m_PbContactsMgr[i],str,false);
		if (j!=0)
			return j;
		const wchar_t * pch=str.c_str ();
		fout<<str<<L"\n";
		str.clear();
	}

	fout<<L"END:VCARD";
	return 0;
}

/*******************************************************************************************************************************
* ��sContactInfo��ʽ������ת����VCard3.0��ʽ������浽ָ�����ļ��С�
********************************************************************************************************************************/
int ConvertsContactInfotoVcard30andWriteToFile(const sContactInfo& trPbItem,WCHAR* path)
{
	wstring str=L"\0";
	ConvertsContactInfotoVcard30(trPbItem, str);
	wofstream fout;//=ofstream(L"d:\my.txt",wios::app);
	fout.open (path);
	const wchar_t * pch=str.c_str ();
	fout<<str;
	return 1;
}

int innerConvertsContactInfotoVcard30(const sContactInfo& pbitem,wstring& myvcard30str,bool b)
{
	myvcard30str.empty();
	VObject* myVcard=VObjectFactory::createInstance(L"VCARD",L"3.0");
	if (myVcard==0)
		return FAILNEW_VCARDOBJECT;

	VProperty* vp=0;//c2w(wchar_t *pwstr,size_t len,const char *str)
	wchar_t mywchar[200];

	vp = new VProperty(L"BEGIN", L"VCARD");//Ϊ��Ҫ����д�����Բο�WinContact::toString() ��������vocl��Ŀ�С�
	if(vp!=0)
	{
		myVcard->addProperty(vp);
		delete vp;
	}

	if(b==true)
	{
		vp=0;
		vp = new VProperty(L"VERSION", L"3.0");
		if(vp!=0)
		{
			myVcard->addProperty(vp);
			delete vp;
		}
	}
	vp=0;

	if(pbitem.name[0]!='\0')//����
	{
		vp=new VProperty(L"FN");
		if(vp!=0)
		{
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,200,pbitem.name);
			vp->setValue (mywchar);
			myVcard->addProperty (vp);
	WCHAR* pnew=vp->toString(L"3.0");
	WCHAR* p;
	p=vp->getValue();
	delete pnew;
			delete vp;
		}
		else
			return ALLO_FAIL;
	}
	
	//TEL
	AddTELToVObject(1,myVcard,pbitem.mobilenumber);
	AddTELToVObject(2,myVcard,pbitem.mobilehome);
	AddTELToVObject(3,myVcard,pbitem.mobilework);
	AddTELToVObject(4,myVcard,pbitem.phonenumber);
	AddTELToVObject(5,myVcard,pbitem.phonehome);
	AddTELToVObject(6,myVcard,pbitem.phonework);
	AddTELToVObject(7,myVcard,pbitem.fax);

	if(pbitem.email[0]!='\0')//����
	{
		vp=new VProperty(L"EMAIL");
		if(vp!=0)
		{
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,200,pbitem.email);
			vp->setValue (mywchar);
			//mySetEncoding(vp,enchset.emailEn);
			myVcard->addProperty (vp);
			delete vp;
		}
		else
			return ALLO_FAIL;
	}

	AddADRtoVObject(0,myVcard,pbitem.homeaddress);//�����ͥ��ַ

	if(pbitem.company[0]!='\0'||pbitem.departments [0]!='\0')//��˾������
	{
		vp=new VProperty(L"ORG");
		if(vp!=0)
		{
			if(pbitem.company[0]!='\0')//�������м��빫˾
			{
				mywchar[0]='\0';mywchar[1]='\0';
				c2w(mywchar,200,pbitem.company);
				vp->setValue (mywchar);
				//mySetEncoding(vp,enchset.companyEn);
			}
			else
				vp->setValue(L"");
			if(pbitem.departments [0]!='\0')//�������в��벿��
			{
				mywchar[0]='\0';mywchar[1]='\0';
				c2w(mywchar,200,pbitem.departments);
				vp->setValue (mywchar);
				//mySetEncoding(vp,enchset.companyEn);
			}
			myVcard->addProperty (vp);
			delete vp;
			vp=0;
		}
		else
			return ALLO_FAIL;
	}

	if(pbitem.birthday[0]!='\0')//����
	{
		vp=new VProperty(L"BDAY");
		if(vp!=0)
		{
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,200,pbitem.birthday);
			vp->setValue (mywchar);
			//mySetEncoding(vp,enchset.birthdayEn);
			myVcard->addProperty (vp);
			delete vp;
			vp=0;
		}
		else
			return ALLO_FAIL;
	}

	if(pbitem.duties[0]!='\0')//ְ�� title
	{
		vp=new VProperty(L"TITLE");
		if(vp!=0)
		{
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,200,pbitem.duties);
			vp->setValue (mywchar);
			//mySetEncoding(vp,enchset.birthdayEn);
			myVcard->addProperty (vp);
			delete vp;
			vp=0;
		}
		else
			return ALLO_FAIL;
	}


	char ch[20];//��������޸ĵ�ʱ��
	ch[0]='\0';
	gettime(ch);
	mywchar[0]='\0';mywchar[1]='\0';
	c2w(mywchar,200,ch);
	//vp->setValue (mywchar);
	vp= new VProperty(L"REV", mywchar);
	if(vp!=0)
	{
		myVcard->addProperty(vp);
		delete vp;
		vp=0;
	}
	
	vp = new VProperty(L"END", L"VCARD");
	if(vp!=0)
	{
		myVcard->addProperty(vp);
		delete vp;
		vp=0;
	}

	WCHAR* tempstr=myVcard->toString();
	myvcard30str.empty();
	myvcard30str=tempstr;
	delete tempstr;
	return 1;
}

/*******************************************************************************************************************************
* ��sContactInfo��ʽ������ת����VCard2.1��ʽ���ַ�����
********************************************************************************************************************************/
int ConvertsContactInfotoVcard30(const sContactInfo& pbitem,wstring& myvcard30str)
{
	return innerConvertsContactInfotoVcard30(pbitem,myvcard30str,false);
}

/*******************************************************************************************************************************
* ��������sContactInfo��ʽ������ת����VCard3.0��ʽ������浽ָ�����ļ��С�
********************************************************************************************************************************/
int ConvertsContactInfotoVcard30andWriteToOneFile(const sContactInfo pbitem[],WCHAR* path,int num)
{
	wstring str=L"\0";
	wofstream fout;//=ofstream(L"d:\my.txt",wios::app);
	fout.open (path);
	fout<<L"BEGIN:VCARD\nVERSION:2.1\n";

	for(int i=0;i<num;i++)
	{
		int j=innerConvertsContactInfotoVcard30(pbitem[i],str,false);
		if (j!=1)
			return j;
		const wchar_t * pch=str.c_str ();
		fout<<str<<L"\n";
		str.clear();
	}

	fout<<L"END:VCARD";
	return 1;
}

//UTF8���뵽Unicodeת��
void unicodeToUTF8(const wstring &src, string& result)
{
	int n = WideCharToMultiByte( CP_UTF8, 0, src.c_str(), -1, 0, 0, 0, 0 );
	 result.resize(n);
	::WideCharToMultiByte( CP_UTF8, 0, src.c_str(), -1, (char*)result.c_str(), result.length(), 0, 0 );
}

//��utf8����ת����Unicode
WCHAR des[300];
wchar_t* ConvertUtf8ToUnicode(char* putf8)
{
	des[0]='\0';
	MultiByteToWideChar(CP_UTF8,0,putf8,-1,des,300);
	return des;
}

wchar_t* ConvertUnicodeFromUtf8(char *utf8)
{
	DWORD wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, utf8, -1, NULL, 0);//CP_UTF8
	wchar_t* unicode = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, utf8, -1, unicode, wcsLen);//CP_UTF8
	unicode[wcsLen]=0;
	return unicode;
}

//�������ר���ڵ���������Ϊbase64��һ����vcard3.0�У�ʱ����ÿһ�����ʵ�ֵ�ӵ�����
void addvaluetoprop(VProperty* vp,WCHAR* wch)
{
	char ch[1500];ch[0]='\0';char temp[100];temp[0]='\0';
	size_t len1=wcslen(wch);
	int nbytes = WideCharToMultiByte( 0, 0,wch,len1,   NULL, 0,  NULL,   NULL ); 
	w2c(ch,wch,1500);//
	ch[nbytes]='\0';
	int end=0,i=0,ind=0,j=0;//ind���ڱ�־�ǵڼ�������ֵ
	for(;ch[i]!='\0';i++,j++)
	{
		if(ch[i]==';')
		{
			temp[j]='\0';j=-1;//�˳�ѭ����ͻ��1 �������Ǵ�0��ʼ����
			end=i;
			//��temp�ӵ�������ȥ
			WCHAR my1[512];my1[0]='\0';my1[1]='\0';
			c2w(my1,512,temp);
			if(vp!=0)
				vp->setValue (my1);
		}
		else
			temp[j]=ch[i];
	}
	temp[j]='\0';//�������һ������ֵ
	//��temp�ӵ�������ȥ
	WCHAR my1[512];my1[0]='\0';my1[1]='\0';
	c2w(my1,512,temp);
	if(vp!=0)
		vp->setValue (my1);
}

//���ڽ���vcard�ж�����һ������ת��vObject��Ķ�����ȥ��֮����������(������ַ������ж�������
//�����ֽ���ŵ�vObject�ж�����ֱ�ӷ���������),����ֱ�ӽ��������
//��Ϊ�˷�ֹ�Ժ�����һЩ���Դ��������
//
//��ȡÿһ�У�����ÿһ�мӵ�һ��������ȥ��
void deal(VObject* myVcard,char curchar[])
{
	bool isbase64=false, isutf8=false,isqp=false; //���ڱ�־�Ƿ���base64����
	VProperty* vp=0;
	char my[1025];my[0]='\0';
	WCHAR my1[512];my1[0]='\0';my1[1]='\0';
	int j=0;
	bool isname=true,ispara=false,isvalue=false;
	for(int i=0;curchar[i]!='\0';i++)
	{
		if(curchar[i]!=';'&&curchar[i]!=':')
		{
			my[j]=curchar[i];
			j++;
		}
		else
		{
			if(curchar[i-1]=='\\')//Ϊ�ֺŻ�ð��ʱ�������Ƿ���ת���ַ�������ǣ���i��1���ɡ�
			{
				my[j]=curchar[i];
				j++;
			}
			else//Ϊ��ת���ַ�����Ϊһ���ֶ�
			{
				if(isname==true)
				{
					isname=false;	
					if(curchar[i]==':')//���Ϊð�ţ���ʼ��������ֵ������
					{
						ispara=false;isvalue=true;
					}
					else
						ispara=true;//�������ð�ţ�����һ��Ϊ����
					my[j]='\0';my[j+1]=='\0';j=0;
					for(int i=0;i<j;++i) 
					{ 
						if(my[i]>='a'&&my[i]<='z')//Сд��ĸת�ɴ�д
							my[i] = my[i]-32;//   ����д��a[i]   =   a[i]-( 'a '- 'A '); 
					}
					c2w(my1,512,my);
					vp=new VProperty(my1);//�½�һ�����ʡ�
					//vp->addParameter(L"CHARSET",L"UTF-8");

					my1[0]='\0';my1[1]='\0';
				}
				else if(ispara==true)//��Ӳ���
				{
					if(curchar[i]==':')//���Ϊð�ţ���ʼ��������ֵ������
					{
						ispara=false;isvalue=true;
					}
					my[j]='\0';my[j+1]=='\0';

					//���Ҳ������Ƿ��еȺţ��еĻ����д���
					int jjj=0;//���ڱ�־�����������ֵ֮��Ľ��޼��Ⱥŵ�λ�á�
					char paravalue[100];//����ʢ�Ų�����ֵ��
					WCHAR paravalue1[100];
					paravalue[0]='\0'; paravalue[1]='\0';
					for(;jjj<j;jjj++)//������������Ͳ���ֵ
					{ 
						if(my[jjj]=='=')
						{
							int k=0;
							int kkk=jjj;
							jjj++;
							while(jjj<=j+1)
							{
								paravalue[k]=my[jjj];//paravalue��Ϊ����ȡֵ���Ұ�\0Ҳд��ȥ��
								jjj++;k++;
							}
							jjj=kkk;
							my[jjj]='\0';;my[jjj+1]='\0';// jjj++;//my��Ϊ������ paravalue[0]=my[jjj+1]
							break;
						}
						//jjj++;
					}
					if(vp!=0)//���½���һ�����ʵĻ����ϣ��Ѳ����ӵ�������
					{
						for(int i=0;i<j;++i) 
						{ 
							if(my[i]>='a'&&my[i]<='z')//Сд��ĸת�ɴ�д,���ں���Ĵ���
								my[i] = my[i]-32;//   ����д��a[i]   =   a[i]-( 'a '- 'A '); 
						}
						for(int i=0;i<j;++i) 
						{ 
							if(paravalue[i]>='a'&&paravalue[i]<='z')//Сд��ĸת�ɴ�д
								paravalue[i] = paravalue[i]-32;//   ����д��a[i]   =   a[i]-( 'a '- 'A '); 
						}
						if(strcmp(my,"CHARSET") == 0)
						{
							if(strcmp(paravalue,"UTF-8") == 0)
								isutf8;
						}
						c2w(my1,512,my);
						c2w(paravalue1,100,paravalue);
						vp->addParameter(my1,paravalue1);
						my1[0]='\0';my1[1]='\0';
						paravalue1[0]='\0'; paravalue1[1]='\0';
					}
					j=0;
				}
				else//������ֵ�Ĵ���
				{
					if(vp!=0)
					{
						my[j]='\0';my[j+1]=='\0';
						int len=1024;
						//if(isbase64==true)//���������������
						//{
						//	char curmy[1025];curmy[0]='\0';
						//	strcpy(curmy,my);
						//	Base64Decode(curmy,j,(BYTE*)my,&len);
						//}
						char temp[1024];temp[0]='\0';
						strcpy(temp,my);
						if(isqp==true)
						{
							string des=Qp_decode(temp);//qp��char*
							des.copy(my,1024);
						}
						if(isutf8==true)
						{
							//WCHAR* wchar2=ConvertUtf8ToUnicode(my);//utf8��Unicode
// 							WCHAR* wchar2=ConvertUnicodeFromUtf8(my);//utf8��Unicode
// 							char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
// 							my[0]='\0';
// 							strcpy(my,curp);
// 							delete curp;
						}
						j=0;
						my1[0]='\0';my1[1]='\0';
						c2w(my1,512,my);
						vp->setValue (my1);
						my1[0]='\0';my1[1]='\0';my[0]='\0';
					}
				}
			}
			if(curchar[i]==':')//���Ϊð�ţ��ж�һ�����õı�������
			{
				if(vp!=0)
				{
					bool bb=vp->containsParameter(L"CHARSET")||vp->containsParameter(L"charset");//�����������ȡ����������
					if(bb==true)
					{
						WCHAR*pvp= vp->getParameterValue(L"CHARSET");
						if(wcscmp(pvp,L"UTF-8")==0||wcscmp(pvp,L"utf-8")==0||wcscmp(pvp,L"Utf-8")==0)
							isutf8=true;
					}
					bool b=vp->containsParameter(L"ENCODING");
					if(b==true)
					{
						WCHAR*pvp= vp->getParameterValue(L"ENCODING");
						if(wcscmp(pvp,L"QP")==0||wcscmp(pvp,L"qp")==0||wcscmp(pvp,L"QUOTED-PRINTABLE")==0||wcscmp(pvp,L"Qp")==0||wcscmp(pvp,L"quoted-printable")==0)
							isqp=true;
						if(wcscmp(pvp,L"b")==0||wcscmp(pvp,L"B")==0||wcscmp(pvp,L"BASE64")==0||wcscmp(pvp,L"BASE64")==0)
							isbase64=true;
					}
				}
			}
		}
	}
	if(vp!=0)
	{
		my[j]='\0';my[j+1]=='\0';//�������һ������ֵ����Ϊ���һ������ֵ��û�зֺŻ�ð�š�
		int len=1024;
		if(isbase64==true)//ת���ɴ��ֱ���󣬸�������ֵ�����ԷֺŸ�����
		{
			char curmy[1025];curmy[0]='\0';
			strcpy(curmy,my);my[0]='\0';
			int len=b64_decode(my,curmy);
			my[len]='\0';
			WCHAR* wchar2=0;
			// �������ԣ���Ϊbase64ʱ ����charsetΪutf8
			wchar2=ConvertUtf8ToUnicode(my);//utf8��Unicode wchar2�з��ľ�������ֵ����Ҫ�����ʷ��ֶη�������
			addvaluetoprop(vp,wchar2);
		}
		else
		{
			char temp[1024];temp[0]='\0';
			strcpy(temp,my);
			if(isqp==true)
			{
				string des=Qp_decode(temp);//qp��char*
				des.copy(my,1024);
			}
			if(isutf8==true)
			{
// 				WCHAR* wchar2=ConvertUtf8ToUnicode(my);//utf8��Unicode
// 				char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
// 				my[0]='\0';
// 				strcpy(my,curp);
// 				delete curp;
			}
			j=0;
			my1[0]='\0';my1[1]='\0';
			c2w(my1,512,my);
			vp->setValue (my1);
			my1[0]='\0';my1[1]='\0';my[0]='\0';
		}
		myVcard->addProperty (vp);//�����ʲ嵽vcard������
		delete vp;
	}
}

/*
*�����//���������������ĳ��ԣ���......
* //�õ���QP���ɴ�ӡ�����룬��getValue����ʱ�������Զ�ת��Ϊԭ���ı��룬�ʣ�������ת��һ�¡�
* //��������toString��������������Ҳ����ȥ���жϵ�ǰ�ַ����������͵��鷳
* //��toString����ת������������ں���û���õ���
*
*���������������ȡ��ָ����ֵ
*/
void getvalue(char mych[],int ind,VProperty* vp)
{
	WCHAR* wch=vp->toString(L"3.0");
	char ch[1024];
	ch[0]='\0';mych[0]='\0';
	size_t len1=wcslen(wch);
	int bytes = WideCharToMultiByte( 0, 0,wch,len1,NULL,0,NULL,NULL ); 
	w2c(ch,wch,1024);
	ch[bytes]='\0';
	bool beginvalue=false;
	int begin=0,end=0,order=0,curend=0;//begin��end���ڱ�־��Ҫ��ֵ�Ŀ�ʼ����λ�ã�order���ڱ�־��ǰ���������ǵڼ���������ֵ
	int i;
	for(i=0;ch[i]!='\0';i++)
	{
		if(ch[i]==':')
		{
			beginvalue=true;
			if(ind==order)
				begin=i;//����ǵ�0�������ڴ˴���־��
		}
		else if(beginvalue==true&&ch[i]==';')
		{
			if(ind==order)
			{	end=i-1;	i=len1;}//���ڽ���ѭ��
			else
				order++;//���ǵ�ǰ�����ı�����������������
			if(ind==order+1)
				begin=i+1;
			curend=i+1;
		}
	}
	if(ind>order||ind==0)//�������һ������Ϊ��β�����Ƿֺţ�����\0,����Ҫ��������
	{
		begin=curend; end=i-1;
	}
	int aa=0;
	for(int j=begin;j<=end&&aa<1023;j++,aa++)
		mych[aa]=ch[j];
	mych[aa+1]='\0';

}

/*******************************************************************************************************************************
* �Ӻ���vcard2.1�ṹ���ݵ���������ȡ����Ϣ���洢��pbitem��
********************************************************************************************************************************/
int ConvertVcard21tosContactInfo(const wstring & myvcard21str, sContactInfo* psContactInfo)
{
	//���� 
	int nLen = myvcard21str.length();
	if(nLen == 0)
	{
		return STRING_NULL;
	}

	//
	WCHAR* pwchVcard = new WCHAR[nLen+1];
	memset(pwchVcard, 0, (nLen+1)*sizeof(WCHAR));
	myvcard21str.copy (pwchVcard, nLen);//���ַ����еĶ���ȡ�������ŵ������С�

	//
	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");//����һ��vcard����,ֱ�ӵ���vObject�Ĺ��캯����ʼ����ʧ��
	if (pMyVcard == 0)
	{
		delete[] pwchVcard;
		pwchVcard = NULL;
		return FAILNEW_VCARDOBJECT;
	}

	//------------------------------------------
	WCHAR wchCurLine[2048];//���ڴ洢vcard�е�ÿһ�У���һ������
	memset(wchCurLine, 0, 2048*sizeof(WCHAR));
	char chCurLine[5000];

	//
	int j = 0;
	for (int i= 0 ; i< nLen; i++)
	{
		if(pwchVcard[i] != '\n')
		{
			wchCurLine[j] = pwchVcard[i];
			j++;
		}
		else
		{
			memset(chCurLine, 0, 5000*sizeof(char));
			w2c(chCurLine, wchCurLine,5000);
			//strcpy(chCurLine,ConvertFromUnicodeToUtf8(wchCurLine));
			deal( pMyVcard, chCurLine);//����һ�����ʷ�������д�뵽vcard������
			memset(wchCurLine, 0, 2048*sizeof(WCHAR));
			j=0;
		}
	}

	//����ʱ�����е����ʶ��Ѿ��ŵ�vcard��������
	delete[] pwchVcard;
	pwchVcard = NULL; 


	//------------------------------------------
	VProperty* pVProperty = NULL;
	WCHAR* pwchar2 = NULL;	
	char ch[1024], temp[200],value[1500]; 
	memset(ch, 0, 1024);
	memset(temp, 0, 200);
	memset(value, 0, 1500);
 
	// 
	size_t len1=0;
	pVProperty = pMyVcard->getProperty(L"N");//��ȡ����
	//bool fname=false,name1=false;//��־�����ֶε���,���Ƿ�Ϊ��
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);//��
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			memset(value, 0, 1500);
			strcat(value,curp);
			delete[] curp;
			curp = NULL;
		}
		temp[0]='\0';
		pwchar2=0;
		pwchar2=pVProperty->getValue(1);//��
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			strcat(value,curp);
			delete[] curp; curp = NULL;
		}
		strcpy(psContactInfo->name,value);
	}
	else
	{
		pVProperty=pMyVcard->getProperty(L"FN");//���û��N���������������ֵ
		if(pVProperty!=0)
		{
			pwchar2=pVProperty->getValue(0);//ȡ������
			if(pwchar2!=0)
			{//wchar_t* ConvertToUnicodeFromUtf8(const char *utf8)//Ҫ�Լ��ͷ��ڴ潫char*��Unicode
				//char* ConvertFromAnsiToUtf8(wchar_t *unicode)//Unicode��char*
				char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
				strcpy(psContactInfo->name,curp);
				delete[] curp; curp = NULL;
			}
		}
	}

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"EMAIL");//��ȡemail
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			memset(value, 0, 1500);
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	strcpy(psContactInfo->email,value);

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"ORG");//��ȡorg
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);//company
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
		strcpy(psContactInfo->company,value);

		memset(value, 0, 1500);pwchar2=0;
		pwchar2=pVProperty->getValue(1);//departments
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*

			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
		strcpy(psContactInfo->departments,value);
	}

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"BDAY");//��ȡ����
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	strcpy(psContactInfo->birthday,value);

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"TITLE");//��ȡְ��
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	strcpy(psContactInfo->duties,value);

	//��
	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"GROUP");//��ȡְ��
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	psContactInfo->nGroupID = atoi(value);
	//strcpy(psContactInfo->cGroupName,value);


	//����绰
	bool tel=false;//����Ѱ��TEL:123 ��һ���Ϊ��ʱ ����ܻ��в�����voice�ȣ�������һ��Ϊ0��
	int num=pMyVcard->propertiesCount();//�õ�������Ŀ����Ŀ
	int numpara=0;//�����ĸ���;
	WCHAR* name=0;
	int equals=-1;
	for(int i=0;i<num;i++)//�������ʣ����tel����
	{
		name=0;
		pwchar2=0;pVProperty=0;memset(value, 0, 1500);
		pVProperty=pMyVcard->getProperty(i);//�õ�һ������
		if(pVProperty!=0)
		{
			name=pVProperty->getName();
			if(name!=0)
			{
				equals=wcscmp(name,L"TEL");
				if(equals!=0)
					equals=wcscmp(name,L"tel");
				name=0;
				if(equals==0)//�����һ����TEL
				{
					equals=-1;
					numpara=pVProperty->parameterCount();//��ȡ��������
					if(numpara==0)		//-----phonenumber
					{
						pwchar2=pVProperty->getValue(0);
						if(pwchar2!=0)
						{
							char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
							string des=Qp_decode(curp);//qp��char*
							delete[] curp; curp = NULL;
							des.copy(value,1500);
							WCHAR* pwchar2=ConvertUtf8ToUnicode(value);//utf8��Unicode
							curp=ConvertFromAnsiToUtf8(pwchar2);//Unicode��char*
							memset(value, 0, 1500);
							strcpy(value,curp);
							delete[] curp; curp = NULL;

							strcpy(psContactInfo->phonenumber,value);
							tel=true;
						}
					}
					else//��������>0ʱ����ȥ����
					{
						bool hashome=false,haswork=false,hascell=false,hasfax=false;//�Ƿ����������
						hashome=pVProperty->containsParameter(L"HOME");
						haswork=pVProperty->containsParameter(L"WORK");
						hascell=pVProperty->containsParameter(L"CELL");
						hasfax=pVProperty->containsParameter(L"FAX");
						if(hasfax)//-----phonehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->fax,value);
							}
						}
						if(hascell==false&&hashome==true)//-----phonehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->phonehome,value);
							}
						}
						else if(hascell==false&&haswork==true)//----phonework
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->phonework,value);
							}
						}
						else if(hascell==true&&haswork==false&&hashome==false)//----mobilehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->mobilenumber,value);
							}
						}
						if(hascell==true&&hashome==true)//----mobilehomeΪ����ֹ��TEL;HOME;WORK;CELL����ʽ
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->mobilehome,value);
							}
						}
						if(hascell==true&&haswork==true)//----mobilehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->mobilework,value);
							}
						}
						if(tel==false&&hascell==false&&haswork==false&&hashome==false&&hasfax==false)//----tel
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->phonenumber,value);
							}
						}
					}
				}
			}
		}
	}

	//��ȡ��ͥסַ
	bool hashomeaddr=false;
	num=0;	name=0;	equals=-1;
	num=pMyVcard->propertiesCount();//�õ�������Ŀ����Ŀ
	for(int i=0;i<num;i++)//�������ʣ����LABEL����
	{
		numpara=0;	name=0;	pwchar2=0;	pVProperty=0;	memset(value, 0, 1500);
		pVProperty=pMyVcard->getProperty(i);//�õ�һ������
		if(pVProperty!=0)
		{
			name=pVProperty->getName();
			if(name!=0)
			{
				equals=wcscmp(name,L"LABEL");
				if(equals==0)//�����һ����LABEL
				{
					equals=-1;
					numpara=pVProperty->parameterCount();//��ȡ��������
					if(numpara>0)
					{
						bool hashome=false;
						hashome=pVProperty->containsParameter(L"HOME");
						if(hashome==true)
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;
								strcpy(psContactInfo->homeaddress,value);
								hashomeaddr=true;
								i=num;//ֹͣѭ��
								//hashomeaddr=true;
							}
						}
					}
				}
			}
		}
	}
	
	if(hashomeaddr==false)
	{
		num=0;	name=0;	equals=-1;
		num=pMyVcard->propertiesCount();//�õ�������Ŀ����Ŀ
		for(int i=0;i<num;i++)//�������ʣ����ADR����
		{
			numpara=0;	name=0;	pwchar2=0;	pVProperty=0;	memset(value, 0, 1500);
			pVProperty=pMyVcard->getProperty(i);//�õ�һ������
			if(pVProperty!=0)
			{
				name=pVProperty->getName();
				if(name!=0)
				{
					equals=wcscmp(name,L"ADR");
					if(equals==0)//�����һ����ADR
					{
						equals=-1;
						numpara=pVProperty->parameterCount();//��ȡ��������
						if(numpara>0)
						{
							bool hashome=false;
							hashome=pVProperty->containsParameter(L"HOME");
							if(hashome==true)
							{
								temp[0]='\0';
								equals=-1;
								for(int addrnum=0;addrnum<=6;addrnum++)//�����ʰ���ʽд��homeaddress��
								{
									len1=0;
									pwchar2=pVProperty->getValue(addrnum);
									if(pwchar2!=0)
									{
										char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
										temp[0]='\0';
										strcpy(temp,curp);
										delete[] curp; curp = NULL;
										strcat(value,temp);
										temp[0]='\0';
										pwchar2=0;
									}
									strcat(value,";");
								}
								strcpy(psContactInfo->homeaddress,value);
								i=num;//ֹͣѭ��
								//hashomeaddr=true;
							}
						}
					}
				}
			}
		}
		
	}
	return 1;
}
 
/*******************************************************************************************************************************
* �Ӻ���vcard3.0�ṹ���ݵ���������ȡ����Ϣ���洢��pbitem��
********************************************************************************************************************************/
int ConvertVcard30tosContactInfo(const wstring & myvcard30str,sContactInfo& pbitem)
{
//	//����������ճ�ʼ��
//	pbitem.birthday[0]='\0';	pbitem.company[0]='\0';		pbitem.departments[0]='\0';
//	pbitem.duties[0]='\0';	pbitem.email[0]='\0';	pbitem.fax[0]='\0';	pbitem.homeaddress[0]='\0';	
//	pbitem.mobilehome[0]='\0';	pbitem.mobilenumber[0]='\0';	pbitem.mobilework[0]='\0';
//	pbitem.name[0]='\0';	pbitem.phonehome[0]='\0';	pbitem.phonenumber[0]='\0';	pbitem.phonework[0]='\0';
//
//	int len=myvcard30str.length();
//	if(len==0) return STRING_NULL;
//	WCHAR* pvcardwchar=new WCHAR[len+1];
//	myvcard30str.copy (pvcardwchar,len);//���ַ����еĶ���ȡ�������ŵ������С�
//
//	VObject* myVcard=VObjectFactory::createInstance(L"VCARD",L"3.0");//����һ��vcard����,ֱ�ӵ���vObject�Ĺ��캯����ʼ����ʧ��
//	if (myVcard==0)
//		return FAILNEW_VCARDOBJECT;
//
//	WCHAR curchar[2048];//���ڴ洢vcard�е�ÿһ�У���һ������
//	curchar[0]='\0';curchar[1]='\0';//˫�ֽڣ�����������ʼ�������������
//	int j=0;
//	for (int i=0;i<len;i++)
//	{
//		if(pvcardwchar[i]!='\n')
//		{
//			curchar[j]=pvcardwchar[i];
//			j++;
//		}
//		else
//		{
//			curchar[j]='\0';curchar[j+1]='\0';//��������ȡ��ÿһ�С�
//			char* curp=ConvertFromAnsiToUtf8(curchar);//ת��char*
//			deal( myVcard,curp);//����һ�����ʷ�������д�뵽vcard������
//			curchar[0]='\0';curchar[1]='\0';//�ַ�������
//			j=0;
//		}
//	}
//	delete pvcardwchar;//����ʱ�����е����ʶ��Ѿ��ŵ�vcard�������ˡ�
//
//WCHAR* chh=myVcard->toString();
//delete chh;
//
//	VProperty* vp=0;WCHAR* wchar2;	char ch[1024];ch[0]='\0';
//	char temp[200],value[1500];//����ֵΪ���ֶεģ������ݴ���temp�У������ڽ���ŵ�value��
//	
//	temp[0]='\0';value[0]='\0';wchar2=0;
//	size_t len1=0;
//	vp=myVcard->getProperty(L"N");//��ȡ����
//	//bool fname=false,name1=false;//��־�����ֶε���,���Ƿ�Ϊ��
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);//��
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//			value[0]='\0';
//			strcat(value,curp);
//			delete curp;curp=0;
//			//fname=true;
//		}
//		temp[0]='\0';
//		wchar2=0;
//		wchar2=vp->getValue(1);//��
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//			strcat(value,curp);
//			delete curp;curp=0;
//		}
//		strcpy(pbitem.name,value);
//	}
//	else
//	{
//		vp=myVcard->getProperty(L"FN");//���û��N���������������ֵ
//		if(vp!=0)
//		{
//			wchar2=vp->getValue(0);//ȡ������
//			if(wchar2!=0)
//			{//wchar_t* ConvertToUnicodeFromUtf8(const char *utf8)//Ҫ�Լ��ͷ��ڴ潫char*��Unicode
//				//char* ConvertFromAnsiToUtf8(wchar_t *unicode)//Unicode��char*
//				char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//				strcpy(pbitem.name,curp);
//				delete curp;curp=0;
//			}
//		}
//	}
//
//	vp=0;
//	value[0]='\0';wchar2=0;
//	vp=myVcard->getProperty(L"EMAIL");//��ȡemail
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//	}
//	strcpy(pbitem.email,value);
//
//	vp=0;
//	value[0]='\0';wchar2=0;
//	vp=myVcard->getProperty(L"ORG");//��ȡorg
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);//company
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//		strcpy(pbitem.company,value);
//		
//		value[0]='\0';wchar2=0;
//		wchar2=vp->getValue(1);//departments
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//		strcpy(pbitem.departments,value);
//	}
//
//	vp=0;
//	value[0]='\0';wchar2=0;
//	vp=myVcard->getProperty(L"BDAY");//��ȡ����
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//	}
//	strcpy(pbitem.birthday,value);
//
//	vp=0;
//	value[0]='\0';wchar2=0;
//	vp=myVcard->getProperty(L"TITLE");//��ȡְ��
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//	}
//	strcpy(pbitem.duties,value);
//
//	//����绰
//	bool tel=false;//����Ѱ��TEL:123 ��һ���Ϊ��ʱ ����ܻ��в�����voice�ȣ�������һ��Ϊ0��
//	int num=myVcard->propertiesCount();//�õ�������Ŀ����Ŀ
//	int numpara=0;//�����ĸ���;
//	WCHAR* name=0;
//	int equals=-1;
//	for(int i=0;i<num;i++)//�������ʣ����tel����
//	{
//		name=0;
//		wchar2=0;vp=0;value[0]='\0';
//		vp=myVcard->getProperty(i);//�õ�һ������
//		if(vp!=0)
//		{
//			name=vp->getName();
//			if(name!=0)
//			{
//				equals=wcscmp(name,L"TEL");
//				if(equals!=0)
//					equals=wcscmp(name,L"tel");
//				name=0;
//				if(equals==0)//�����һ����TEL
//				{
//					equals=-1;
//					numpara=vp->parameterCount();//��ȡ��������
//					if(numpara==0)		//-----phonenumber
//					{
//						wchar2=vp->getValue(0);
//						if(wchar2!=0)
//						{
//							char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//							value[0]='\0';
//							strcpy(value,curp);
//							delete curp;curp=0;
//
//							strcpy(pbitem.phonenumber,value);
//							tel=true;
//						}
//					}
//					else//��������>0ʱ����ȥ����
//					{
//						bool hashome=false,haswork=false,hascell=false,hasfax=false;//�Ƿ����������
//						hashome=vp->containsParameter(L"HOME");
//						haswork=vp->containsParameter(L"WORK");
//						hascell=vp->containsParameter(L"CELL");
//						hasfax=vp->containsParameter(L"FAX");
//						if(hasfax)//-----phonehome
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.fax,value);
//							}
//						}
//						if(hascell==false&&hashome==true)//-----phonehome
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.phonehome,value);
//							}
//						}
//						else if(hascell==false&&haswork==true)//----phonework
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.phonework,value);
//							}
//						}
//						else if(hascell==true&&haswork==false&&hashome==false)//----mobilehome
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.mobilenumber,value);
//							}
//						}
//						if(hascell==true&&hashome==true)//----mobilehomeΪ����ֹ��TEL;HOME;WORK;CELL����ʽ
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.mobilehome,value);
//							}
//						}
//						if(hascell==true&&haswork==true)//----mobilehome
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.mobilework,value);
//							}
//						}
//						if(tel==false&&hascell==false&&haswork==false&&hashome==false&&hasfax==false)//----tel
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.phonenumber,value);
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	//��ȡ��ͥסַ
//	num=0;	name=0;	equals=-1;
//	num=myVcard->propertiesCount();//�õ�������Ŀ����Ŀ
//	bool hashomeaddr=false;
//	for(int i=0;i<num;i++)//�������ʣ����ADR����
//	{
//		numpara=0;	name=0;	wchar2=0;	vp=0;	value[0]='\0';
//		vp=myVcard->getProperty(i);//�õ�һ������
//		if(vp!=0)
//		{
//			name=vp->getName();
//			if(name!=0)
//			{
//				equals=wcscmp(name,L"ADR");
//				if(equals==0)//�����һ����ADR
//				{
//					equals=-1;
//					numpara=vp->parameterCount();//��ȡ��������
//					if(numpara>0)
//					{
//						bool hashome=false;
//						hashome=vp->containsParameter(L"HOME");
//						if(hashome==true)
//						{
//							temp[0]='\0';
//							equals=-1;
//							for(int addrnum=0;addrnum<=6;addrnum++)//�����ʰ���ʽд��homeaddress��
//							{
//								len1=0;
//								wchar2=vp->getValue(addrnum);
//								if(wchar2!=0)
//								{
//									char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//									temp[0]='\0';
//									strcpy(temp,curp);
//									delete curp;curp=0;
//
//									strcat(value,temp);
//									temp[0]='\0';
//									wchar2=0;
//								}
//								strcat(value,";");
//							}
//							strcpy(pbitem.homeaddress,value);
//							i=num;//ֹͣѭ��
//							hashomeaddr=true;
//						}
//					}
//				}
//			}
//		}
//	}
//	if(hashomeaddr==false)
//	{
//		num=0;	name=0;	equals=-1;
//		num=myVcard->propertiesCount();//�õ�������Ŀ����Ŀ
//		for(int i=0;i<num;i++)//�������ʣ����LABEL����
//		{
//			numpara=0;	name=0;	wchar2=0;	vp=0;	value[0]='\0';
//			vp=myVcard->getProperty(i);//�õ�һ������
//			if(vp!=0)
//			{
//				name=vp->getName();
//				if(name!=0)
//				{
//					equals=wcscmp(name,L"LABEL");
//					if(equals==0)//�����һ����LABEL
//					{
//						equals=-1;
//						numpara=vp->parameterCount();//��ȡ��������
//						if(numpara>0)
//						{
//							bool hashome=false;
//							hashome=vp->containsParameter(L"HOME");
//							if(hashome==true)
//							{
//								wchar2=vp->getValue(0);
//								if(wchar2!=0)
//								{
//									char* curp=ConvertFromAnsiToUtf8(wchar2);//ת��char*
//									value[0]='\0';
//									strcpy(value,curp);
//									delete curp;curp=0;
//
//									strcpy(pbitem.homeaddress,value);
//									i=num;//ֹͣѭ��
//									hashomeaddr=true;
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
	return 1;
}

/*******************************************************************************************************************************
* �Ӻ���vcard2.1�ṹ���ݵ��ļ�����ȡ����Ϣ���洢��pbitem��
********************************************************************************************************************************/
int ConvertVcard21tosContactInfoandReadFromFile(const WCHAR* path, sContactInfo* psContactInfo)
{
	//wstring str=L"\0";
	//ifstream fin;
	//fin.open (path);
	//if (!fin.is_open())
	//{ 
	//	return -1;
	//}

	//char ch[2000];
	//WCHAR wch[2000];
	//while(!fin.eof())
	//{
	//	//
	//	memset(ch, 0, 2000*sizeof(char));
	//	memset(wch, 0, 2000*sizeof(WCHAR));

	//	//
	//	fin.getline(ch,2000);
	//	size_t len=strlen(ch);
	//	if(ch[len-1]==0x0d)
	//		ch[len-1]='\0';
	//	c2w(wch, 2000, ch);
	//	str+=wch;
	//	str+=L"\n";
	//}
	//return	ConvertVcard21tosContactInfo(str, psContactInfo);
	return 0;
}

/*******************************************************************************************************************************
* �õ�һ���ļ��к��еĵ���ϵ�ˣ�vcard�������壩�ĸ�����
********************************************************************************************************************************/
int GetVcardObjectNum(const WCHAR* path)
{
	//int MynumofObj=0;bool hasallbegin=false,hasbegin=false,hasend=false;
	////ǰһ��bool�������ڱ�־�Ƿ�������������һ���beginvcard endvcard������ı�־һ���Ӷ���Ŀ�ʼ�ͽ���
	//wstring str=L"\0";
	//ifstream fin;
	//fin.open (path);
	//if (!fin.is_open())
	//{ 
	//	return -1;
	//}
	//char ch[600]; 
	//WCHAR wch[600];
	//ch[0]='\0';
	//fin.getline(ch,600);
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))
	//	hasallbegin=true;
	//while(!fin.eof())
	//{
	//	ch[0]='\0';
	//	fin.getline(ch,600);
	//	while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//	if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))
	//		hasbegin=true;
	//	if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))//������ֻ��һ��vcard����������
	//	{
	//		hasbegin=false;	MynumofObj++;//���еĶ�������1������hasbegin��Ϊfalse����־��������Ѿ�������
	//	}
	//	if(hasbegin==false&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//		hasend=true;
	//}
	//if(MynumofObj>0)
	//	return MynumofObj;
	//if(MynumofObj==0&&hasend==true&&hasallbegin==true)
	//	return 1;
	return 0;//�������
}

/*******************************************************************************************************************************
* �Ӻ���vcard2.1�ṹ���ݵ��ļ�����ȡ����Ϣ���洢��pbitem������
********************************************************************************************************************************/
int ConvertVcard21tosContactInfoandReadFromFile(const WCHAR* path,vector< sContactInfo> &m_PbContactsMgr,int n)
{
	//wstring str=L"\0";	ifstream fin;	fin.open (path);
	//if (!fin.is_open())
	//{ 
	//	return -1;
	//}
	//char ch[600];	WCHAR wch[600],version[50];
	//bool hasbegin=true,issub=false;

	//fin.getline(ch,600);//�õ���һ��
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))
	//{
	//	c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//	hasbegin=true;
	//}
	//else
	//	return -7;//�ļ���ʽ����
	//
	//fin.getline(ch,600);//�õ��ڶ���	
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"VERSION:2.1")||!strcmp(ch,"VERSION:3.0")||!strcmp(ch,"VERSION:2.1\r")||!strcmp(ch,"VERSION:3.0\r"))
	//{
	//	c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//	wcscpy(version,wch);
	//}
	//else
	//	return -7;//�ļ���ʽ����

	//fin.getline(ch,600);
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))//Ѱ�ҵ������Ƿ�Ϊһ������
	//	issub=true;
	//else
	//{	c2w(wch,600,ch);	str+=wch;	str+=L"\n";		}

	//int ind=0;
	//while(!fin.eof())
	//{
	//	fin.getline(ch,600);
	//	while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//		fin.getline(ch,600);
	//	if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//	{
	//		c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//		if(ind<n)
	//		{	
	//			sContactInfo pbitem=sContactInfo();
	//			ConvertVcard21tosContactInfo(str, &pbitem);
	//			m_PbContactsMgr.insert(m_PbContactsMgr.begin(),pbitem);
	//			ind++;	
	//			hasbegin=false;
	//		}
	//		else return 3;//�ɹ����أ����������Ŀռ䲻��
	//		str=L"";
	//	}
	//	else if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//	{
	//		c2w(wch,600,ch);
	//		fin.getline(ch,600);
	//		while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//			fin.getline(ch,600);
	//		if(fin.eof())// �������ļ���β
	//			continue;//
	//		else
	//			return -7;
	//		//ʲô�������������������Ǹ�end:vcard
	//	}
	//	else if(issub==true&&(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r")))//һ�������Ѿ��������µĶ����Ѿ���ʼ
	//	{	
	//		if(hasbegin==true) return -7;//�ļ���ʽ����
	//		c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//		str+=version;	str+=L"\n";	hasbegin=true;
	//	}
	//	else
	//	{	c2w(wch,600,ch);	str+=wch;	str+=L"\n";		}
	//}
	return 1;
}

/*******************************************************************************************************************************
* �Ӻ���vcard3.0�ṹ���ݵ��ļ�����ȡ����Ϣ���洢��pbitem��
********************************************************************************************************************************/
int ConvertVcard30tosContactInfoandReadFromFile(const WCHAR* path,sContactInfo& pbitem)
{
	/*wstring str=L"\0";
	ifstream fin;
	fin.open (path);
	if (!fin.is_open())
	{ 
		return -1;
	}

	char ch[600];
	WCHAR wch[600];
	while(!fin.eof())
	{
		fin.getline(ch,600);
		c2w(wch,600,ch);
		str+=wch;
		str+=L"\n";
	}
	return	ConvertVcard30tosContactInfo(str,pbitem);*/
	return 0;
}

/*******************************************************************************************************************************
* �Ӻ���vcard2.1�ṹ���ݵ��ļ�����ȡ����Ϣ���洢��pbitem������
********************************************************************************************************************************/
int ConvertVcard30tosContactInfoandReadFromFile(const WCHAR* path,sContactInfo pbitem[],int n)
{
	//wstring str=L"\0";	ifstream fin;	fin.open (path);
	//if (!fin.is_open())
	//{ 
	//	return -1;
	//}
	//char ch[600];	WCHAR wch[600],version[50];
	//bool hasbegin=true,issub=false;

	//fin.getline(ch,600);//�õ���һ��
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))
	//{
	//	c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//	hasbegin=true;
	//}
	//else
	//	return -7;//�ļ���ʽ����
	//
	//fin.getline(ch,600);//�õ��ڶ���	
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"VERSION:2.1")||!strcmp(ch,"VERSION:3.0")||!strcmp(ch,"VERSION:2.1\r")||!strcmp(ch,"VERSION:3.0\r"))
	//{
	//	c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//	wcscpy(version,wch);
	//}
	//else
	//	return -7;//�ļ���ʽ����

	//fin.getline(ch,600);
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))//Ѱ�ҵ������Ƿ�Ϊһ������
	//	issub=true;
	//else
	//{	c2w(wch,600,ch);	str+=wch;	str+=L"\n";		}

	//int ind=0;
	//while(!fin.eof())
	//{
	//	fin.getline(ch,600);
	//	while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//		fin.getline(ch,600);
	//	if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//	{
	//		c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//		if(ind<n)
	//		{	ConvertVcard21tosContactInfo(str,&pbitem[ind]);	ind++;	hasbegin=false;	}
	//		else return 3;//�ɹ����أ����������Ŀռ䲻��
	//		str=L"";
	//	}
	//	else if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//	{
	//		c2w(wch,600,ch);
	//		fin.getline(ch,600);
	//		while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//			fin.getline(ch,600);
	//		if(fin.eof())// �������ļ���β
	//			continue;//
	//		else
	//			return -7;
	//		//ʲô�������������������Ǹ�endvcard
	//	}
	//	else if(issub==true&&(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r")))//һ�������Ѿ��������µĶ����Ѿ���ʼ
	//	{	
	//		if(hasbegin==true) return -7;//�ļ���ʽ����
	//		c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//		str+=version;	str+=L"\n";	hasbegin=true;
	//	}
	//	else
	//	{	c2w(wch,600,ch);	str+=wch;	str+=L"\n";		}
	//}

	return 0;
}

//���ڽ�sContactInfo�ṹת��ΪCSVʱ���Ը�ֵ�к��е�˫���ţ����Ž��д���
//���ڴ���sContactInfo�ṹ�и���char���������ж��Ŵ���ʱ���������ʱ����ת�������� ���ţ���������ţ�����ת�����������ŵ���ʽд���ļ�
wchar_t* ConverCharToCsvData(wchar_t* wchSrcBuffur)
{
	////
	//if (wchSrcBuffur == NULL)
	//{
	//	return NULL;
	//}

	//// ����ؼ� 
	//int nLen = wcslen(wchSrcBuffur);
	//if (nLen == 0)
	//{
	//	return NULL;
	//}
	//wchar_t* pwchReBuff = new wchar_t[nLen*2];
	//memset(pwchReBuff, 0, sizeof(wchar_t)*nLen*2);

	//// ����
	//int nReBufferPos = 0;	
	//for(int i = 0; i < nLen; i++)
	//{
	//	// �ж�
	//	if(wchSrcBuffur[i]==',')
	//	{
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//		pwchReBuff[nReBufferPos] = ',';
	//		nReBufferPos++;
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//	}
	//	else if(wchSrcBuffur[i]=='"')// ������ʱ���˫����
	//	{
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//	}
	//	else
	//	{
	//		pwchReBuff[nReBufferPos] = wchSrcBuffur[i];
	//		nReBufferPos++;
	//	}
	//}
	// 
    //
	//return pwchReBuff;
	return NULL;
}


 
/*******************************************************************************************************************************
* ��sContactInfo�ṹ�е�����ת����CSV�ṹ���������ַ�����
********************************************************************************************************************************/
int ConvertsContactInfotoCSV(const vector< sContactInfo*>* pVectorContacts, wstring& CSVstr)
{
	////
	//CSVstr.empty();
	//wchar_t wchBuffer[TR_MAX_CONTACT_ID_LENGTH];
	//wchar_t* pwchBuffer = NULL;
	//CSVstr += L"����,�ֻ�����(�ƶ�),�ֻ�����(��ͥ),�ֻ�����(�칫),�绰����,�绰����(��ͥ),�绰����(�칫),˽������,��ͥ��ַ,��˾����,��������,����,����,ְ��\n";

	//// ����

	//int num = pVectorContacts->size();
	//for(int i = 0;i<num; i++) 
	//{
	//	sContactInfo* psContactInfo = pVectorContacts->at(i);
	//	if (psContactInfo == NULL)
	//	{
	//		continue;
	//	}
 //

	//	// ����
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->name);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);


	//	// �ֻ�����(�ƶ�)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->mobilenumber);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// �ֻ�����(��ͥ)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->mobilehome);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// �ֻ�����(�칫)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->mobilework);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// �绰����
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->phonenumber);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// �绰����(��ͥ)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->phonehome);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// �绰����(�칫)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->phonework);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);
	//	// ˽������
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->email);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// ��ͥ��ַ
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->homeaddress);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// ��˾����
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->company);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// ��������
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->birthday);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// ����
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->fax);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// ����
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->departments);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// ְ��
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->duties);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// ������
	//	CSVstr+=L"\n";
	//}
	//return num;
     
    return 0;
}
 
//
void ConverCsvToCharData(char* chDesBuffur, char* chSrcBuffur)
{
	////
	//if (chSrcBuffur == NULL || chDesBuffur == NULL)
	//{
	//	return;
	//}

	//// ����ؼ� 
	//int nLen = strlen(chSrcBuffur);
	//if (nLen == 0)
	//{
	//	return;
	//}

	//// ����
	//int nReBufferPos = 0;	
	//for(int i = 0; i < nLen; i++)
	//{
	//	// �ж�
	//	if(chSrcBuffur[i]=='"')
	//	{
	//		i++;
	//		chDesBuffur[nReBufferPos] = chSrcBuffur[i];
	//		nReBufferPos++;
	//		i++;
	//	}
	//	else
	//	{
	//		chDesBuffur[nReBufferPos] = chSrcBuffur[i];
	//		nReBufferPos++;
	//	}
	//}

	////
	//return;
}


/*******************************************************************************************************************************
* �Ӻ���CSV�ṹ���ݵ���������ȡ����Ϣ���洢��pbitem��
********************************************************************************************************************************/
int ConvertCSVtosContactInfo(char* pchLineText, sContactInfo* pContactInfo)
{
	//int rv = 0;
	//if (pchLineText == NULL || psContactInfo == NULL)
	//{
	//	return -1;
	//}
 //
	//// ����
	//int nTextLen = strlen(pchLineText);
	//if (nTextLen == 0)
	//{
	//	return -1;
	//}
	//
 //   // ����
	//int nItemNum = 0;
	//int i = 0, j = 0;
	//int nDataPosBegin = 0, nDataPosEnd = 0;    // ����λ��
	//char chDataBuffer[TR_MAX_CONTACT_ID_LENGTH];        // ����
	//while(i != nTextLen)
	//{
	//	// ���ҷָ
	//	nDataPosBegin = i;
	//	for (j = nDataPosBegin; j < nTextLen; j++)
	//	{
	//		// �жϣ��ָ�
	//		if(pchLineText[j]== ',' && j == 0)
	//		{
	//			nDataPosEnd = j;
	//			break;
	//		}
	//		else if(pchLineText[j]== ',' && pchLineText[j-1] != '"')
	//		{
	//			nDataPosEnd = j;
	//			break;
	//		}
	//	}
	//	if (j == nTextLen)
	//	{
	//		nDataPosEnd = nTextLen-1;
	//	}
	//	i = nDataPosEnd;
	//	i++;

	//	// ȡֵ
	//	memset(chDataBuffer, 0, TR_MAX_CONTACT_ID_LENGTH);
	//	memcpy(chDataBuffer, pchLineText+nDataPosBegin, nDataPosEnd-nDataPosBegin);

	//	// ȡֵ
	//	switch(nItemNum)
	//	{
	//	case 0: // ����
	//		ConverCsvToCharData(psContactInfo->name, chDataBuffer);
	//		break;
	//	case 1: // �ֻ�����(�ƶ�)
	//		ConverCsvToCharData(psContactInfo->mobilenumber, chDataBuffer);
	//		break;
	//	case 2: // �ֻ�����(��ͥ)
	//		ConverCsvToCharData(psContactInfo->mobilehome, chDataBuffer);
	//	    break;
	//	case 3: // �ֻ�����(�칫)
	//		ConverCsvToCharData(psContactInfo->mobilework, chDataBuffer);
	//	    break;
	//	case 4: // �绰����
	//		ConverCsvToCharData(psContactInfo->phonenumber, chDataBuffer);
	//		break;
	//	case 5: // �绰����(��ͥ)
	//		ConverCsvToCharData(psContactInfo->phonehome, chDataBuffer);
	//		break;
	//	case 6: // �绰����(�칫) 
	//		ConverCsvToCharData(psContactInfo->phonework, chDataBuffer);
	//	    break;
	//	case 7: // ˽������
	//		ConverCsvToCharData(psContactInfo->email, chDataBuffer);
	//		break;
	//	case 8: // ��ͥ��ַ
	//		ConverCsvToCharData(psContactInfo->homeaddress, chDataBuffer);
	//	    break;
	//	case 9: // ��˾����
	//		ConverCsvToCharData(psContactInfo->company, chDataBuffer);
	//		break;
	//	case 10: // �������� 
	//		ConverCsvToCharData(psContactInfo->birthday, chDataBuffer);
	//		break;
	//	case 11: // ����
	//		ConverCsvToCharData(psContactInfo->fax, chDataBuffer);
	//		break;
	//	case 12: // ����
	//		ConverCsvToCharData(psContactInfo->departments, chDataBuffer);
	//		break;
	//	case 13: // ְ��
	//		ConverCsvToCharData(pContactInfo->m_Duties, chDataBuffer);
	//		break;
	//	default:
	//	    break;
	//	}

	//	//
	//	nItemNum++;
	//} 

	return 0;
}


////////////////////////////////////////////////////////////////////////
int ConvertVcard211tosContactInfo(CString cStrTmp, sContactInfo* pContactInfo)
{
	//���� 
	int nLen = cStrTmp.GetLength();
	if(nLen == 0)
	{
		return STRING_NULL;
	}

	//
	//char* pwchVcard = new char[nLen];
	//memset(pwchVcard, 0, (nLen)*sizeof(char));
	//pwchVcard = cStrTmp.GetBuffer();//���ַ����еĶ���ȡ�������ŵ������С�

	char* pwchVcard = cStrTmp.GetBuffer();
	//
	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");//����һ��vcard����,ֱ�ӵ���vObject�Ĺ��캯����ʼ����ʧ��
	if (pMyVcard == 0)
	{
		delete[] pwchVcard;
		pwchVcard = NULL;
		return FAILNEW_VCARDOBJECT;
	}

	//------------------------------------------
	char wchCurLine[5000];//���ڴ洢vcard�е�ÿһ�У���һ������
	memset(wchCurLine, 0, 2048*sizeof(char));
	//char chCurLine[5000];

	//
	int j = 0;
	for (int i= 0 ; i< nLen; i++)
	{
		if(pwchVcard[i] != '\n')
		{
			wchCurLine[j] = pwchVcard[i];
			j++;
		}
		else
		{
			//memset(chCurLine, 0, 5000*sizeof(char));
			//w2c(chCurLine, wchCurLine,5000);
			//strcpy(chCurLine,ConvertFromUnicodeToUtf8(wchCurLine));
			deal( pMyVcard, wchCurLine);//����һ�����ʷ�������д�뵽vcard������
			memset(wchCurLine, 0, 5000*sizeof(char));
			j=0;
		}
	}

	//����ʱ�����е����ʶ��Ѿ��ŵ�vcard��������
	//delete[] pwchVcard;
	pwchVcard = NULL; 


	//------------------------------------------
	VProperty* pVProperty = NULL;
	WCHAR* pwchar2 = NULL;	
	char ch[1024], temp[200],value[1500]; 
	memset(ch, 0, 1024);
	memset(temp, 0, 200);
	memset(value, 0, 1500);

	CString csValue; 
	// 
	size_t len1=0; 
	{
		pVProperty=pMyVcard->getProperty(L"FN");//���û��N���������������ֵ
		if(pVProperty!=0)
		{
			pwchar2=pVProperty->getValue(0);//ȡ������
			if(pwchar2!=0)
			{
				char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
				//strcpy(psContactInfo->name,curp);
				memset(value, 0, 1500);
				strcpy(value,curp);
				delete[] curp; curp = NULL;
				
				csValue = CString(value);				
				csValue.Replace(_T("\\;"), _T(";"));
				csValue.Replace(_T("\\:"), _T(":"));
				csValue.Replace(_T("\\\\"), _T("\\"));
				pContactInfo->m_Name = csValue;
			
			}
		}
	}

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"EMAIL");//��ȡemail
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			memset(value, 0, 1500);
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}

	csValue = CString(value);	
	csValue.Replace(_T("\\;"), _T(";"));
	csValue.Replace(_T("\\:"), _T(":"));
	csValue.Replace(_T("\\\\"), _T("\\"));
	pContactInfo->m_Email = csValue;
	csValue.ReleaseBuffer();

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"ORG");//��ȡorg
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);//company
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	
		csValue = CString(value);
		csValue.Replace(_T("\\;"), _T(";"));
		csValue.Replace(_T("\\:"), _T(":"));
		csValue.Replace(_T("\\\\"), _T("\\"));
		pContactInfo->m_Company=csValue;
		
		memset(value, 0, 1500);pwchar2=0;
		pwchar2=pVProperty->getValue(1);//departments
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*

			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	
		csValue = CString(value);
		csValue.Replace(_T("\\;"), _T(";"));
		csValue.Replace(_T("\\:"), _T(":"));
		csValue.Replace(_T("\\\\"), _T("\\"));
		pContactInfo->m_Departments=csValue
	}

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"BDAY");//��ȡ����
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	pContactInfo->m_Birthday = CString(value);


	//------------- ��ȡ����ID--------------
	psContactInfo->nGroupID = 0;
	pVProperty=0;
	memset(value, 0, 1500);
	pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"GROUP");//��ȡ�����
	if(pVProperty!=0)
	{
		int nSum = pVProperty->valueCount();
		for (int i=0; i< nSum; i++)
		{
			pwchar2=pVProperty->getValue(i);
			if(pwchar2!=0)
			{
				char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
				strcpy(value,curp);
				delete[] curp; curp = NULL;

				csValue = CString(value);
				csValue.Replace(_T("\\;"), _T(";"));
				csValue.Replace(_T("\\:"), _T(":"));
				csValue.Replace(_T("\\\\"), _T("\\"));
				pContactInfo->m_GroupIDs.push_back(csValue);
			}
		}
	}
	//---------------------------------------

	pVProperty=0;
	memset(value, 0, 1500);
	pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"TITLE");//��ȡְ��
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}


	csValue = CString(value);
	csValue.Replace(_T("\\;"), _T(";"));
	csValue.Replace(_T("\\:"), _T(":"));
	csValue.Replace(_T("\\\\"), _T("\\"));
	pContactInfo->m_Duties = csValue;
	
	//����绰
	bool tel=false;//����Ѱ��TEL:123 ��һ���Ϊ��ʱ ����ܻ��в�����voice�ȣ�������һ��Ϊ0��
	int num=pMyVcard->propertiesCount();//�õ�������Ŀ����Ŀ
	int numpara=0;//�����ĸ���;
	WCHAR* name=0;
	int equals=-1;
	for(int i=0;i<num;i++)//�������ʣ����tel����
	{
		name=0;
		pwchar2=0;pVProperty=0;memset(value, 0, 1500);
		pVProperty=pMyVcard->getProperty(i);//�õ�һ������
		if(pVProperty!=0)
		{
			name=pVProperty->getName();
			if(name!=0)
			{
				equals=wcscmp(name,L"TEL");
				if(equals!=0)
					equals=wcscmp(name,L"tel");
				name=0;
				if(equals==0)//�����һ����TEL
				{
					equals=-1;
					numpara=pVProperty->parameterCount();//��ȡ��������
					if(numpara==0)		//-----phonenumber
					{
						pwchar2=pVProperty->getValue(0);
						if(pwchar2!=0)
						{
							char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
							string des=Qp_decode(curp);//qp��char*
							delete[] curp; curp = NULL;
							des.copy(value,1500);
							WCHAR* pwchar2=ConvertUtf8ToUnicode(value);//utf8��Unicode
							curp=ConvertFromAnsiToUtf8(pwchar2);//Unicode��char*
							memset(value, 0, 1500);
							strcpy(value,curp);
							delete[] curp; curp = NULL;

							pContactInfo->m_Phonenumber=CString(value);
							tel=true;
						}
					}
					else//��������>0ʱ����ȥ����
					{
						bool hashome=false,haswork=false,hascell=false,hasfax=false;//�Ƿ����������
						hashome=pVProperty->containsParameter(L"HOME");
						haswork=pVProperty->containsParameter(L"WORK");
						hascell=pVProperty->containsParameter(L"CELL");
						hasfax=pVProperty->containsParameter(L"FAX");
						if(hasfax)//-----phonehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								pContactInfo->m_Fax=CString(curp);
								delete[] curp; curp = NULL;

								
							}
						}
						if(hascell==false&&hashome==true)//-----phonehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								pContactInfo->m_PhoneHome=CString(curp);
								delete[] curp; curp = NULL;

								
							}
						}
						else if(hascell==false&&haswork==true)//----phonework
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								pContactInfo->m_PhoneWork=CString(curp);
								delete[] curp; curp = NULL;
							}
						}
						else if(hascell==true&&haswork==false&&hashome==false)//----mobilehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								pContactInfo->m_MobileNumber=CString(curp);
								delete[] curp; curp = NULL;
							}
						}
						if(hascell==true&&hashome==true)//----mobilehomeΪ����ֹ��TEL;HOME;WORK;CELL����ʽ
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								pContactInfo->m_MobileHome = CString(curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->mobilehome,value);
							}
						}
						if(hascell==true&&haswork==true)//----mobilehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								pContactInfo->m_MobileWork = CString(curp);
								delete[] curp; curp = NULL;
							}
						}
						if(tel==false&&hascell==false&&haswork==false&&hashome==false&&hasfax==false)//----tel
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								pContactInfo->m_PhoneNumber = CString(curp);
								delete[] curp; curp = NULL;
							}
						}
					}
				}
			}
		}
	}

	//��ȡ��ͥסַ
	bool hashomeaddr=false;
	num=0;	name=0;	equals=-1;
	num=pMyVcard->propertiesCount();//�õ�������Ŀ����Ŀ
	for(int i=0;i<num;i++)//�������ʣ����LABEL����
	{
		numpara=0;	name=0;	pwchar2=0;	pVProperty=0;	memset(value, 0, 1500);
		pVProperty=pMyVcard->getProperty(i);//�õ�һ������
		if(pVProperty!=0)
		{
			name=pVProperty->getName();
			if(name!=0)
			{
				equals=wcscmp(name,L"LABEL");
				if(equals==0)//�����һ����LABEL
				{
					equals=-1;
					numpara=pVProperty->parameterCount();//��ȡ��������
					if(numpara>0)
					{
						bool hashome=false;
						hashome=pVProperty->containsParameter(L"HOME");
						if(hashome==true)
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;
								//strcpy(psContactInfo->homeaddress,value);

								csValue = CString(value);
								csValue.Replace(_T("\\;"), _T(";"));
								csValue.Replace(_T("\\:"), _T(":"));
								csValue.Replace(_T("\\\\"), _T("\\"));
								pContactInfo->m_HomeAddress=csValue;
								hashomeaddr=true;
								i=num;//ֹͣѭ��
								//hashomeaddr=true;
							}
						}
					}
				}
			}
		}
	}
	
	if(hashomeaddr==false)
	{
		num=0;	name=0;	equals=-1;
		num=pMyVcard->propertiesCount();//�õ�������Ŀ����Ŀ
		for(int i=0;i<num;i++)//�������ʣ����ADR����
		{
			numpara=0;	name=0;	pwchar2=0;	pVProperty=0;	memset(value, 0, 1500);
			pVProperty=pMyVcard->getProperty(i);//�õ�һ������
			if(pVProperty!=0)
			{
				name=pVProperty->getName();
				if(name!=0)
				{
					equals=wcscmp(name,L"ADR");
					if(equals==0)//�����һ����ADR
					{
						equals=-1;
						numpara=pVProperty->parameterCount();//��ȡ��������
						if(numpara>0)
						{
							bool hashome=false;
							hashome=pVProperty->containsParameter(L"HOME");
							if(hashome==true)
							{
								temp[0]='\0';
								equals=-1;
								for(int addrnum=0;addrnum<=6;addrnum++)//�����ʰ���ʽд��homeaddress��//
								{
									len1=0;
									pwchar2=pVProperty->getValue(addrnum);
									if(pwchar2!=0)
									{
										char* curp=ConvertFromAnsiToUtf8(pwchar2);//ת��char*
										temp[0]='\0';
										strcpy(temp,curp);
										delete[] curp; curp = NULL;
										strcat(value,temp);
										if(temp[0]!='\0')
										strcat(value," ");//;
										temp[0]='\0';
										pwchar2=0;
									}
								}
								csValue = CString(value);
								csValue.Replace(_T("\\;"), _T(";"));
								csValue.Replace(_T("\\:"), _T(":"));
								csValue.Replace(_T("\\\\"), _T("\\"));
								pContactInfo->m_HomeAddress=csValue;
								i=num;//ֹͣѭ��
								//hashomeaddr=true;
							}
						}
					}
				}
			}
		}
		
	}
	return 1;
}