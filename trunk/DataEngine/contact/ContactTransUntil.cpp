#include "StdAfx.h"
#include "../common/Include/DataDefine.h"
#include "../common/Include/base64.h"
#include "export.h"
#include "ContactTransUntil.h"

void deal(VObject* myVcard,char curchar[]);

//charת��Ϊwchar_t
 wchar_t* TransCharToWchar(char *utf8)
{
	DWORD wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, utf8, -1, NULL, 0);
	wchar_t* unicode = new wchar_t[wcsLen];
	::MultiByteToWideChar(CP_ACP, NULL, utf8, -1, unicode, wcsLen);
	return unicode;
}

 //wchar_tת��Ϊchar
char* TransWcharToChar(const wchar_t *unicode)
{
	int len = WideCharToMultiByte( CP_ACP, 0, unicode, -1, 0, 0, 0, 0 );
	char* buffer = new char[len+1];
	WideCharToMultiByte( CP_ACP, 0, unicode, -1, buffer,len, 0, 0 );
	buffer[len] = '\0';
	return buffer;
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

//�������ר���ڵ���������Ϊbase64��һ����vcard3.0�У�ʱ����ÿһ�����ʵ�ֵ�ӵ�����
void addvaluetoprop(VProperty* vp,WCHAR* wch)
{
	char* ch=TransWcharToChar(wch);
	int len=strlen(ch);
	char* temp = new char[len+1];
	memset(temp,0,sizeof(char)*(len+1));

	int end=0,i=0,ind=0,j=0;//ind���ڱ�־�ǵڼ�������ֵ
	for(;ch[i]!='\0';i++,j++)
	{
		if(ch[i]==';')
		{
			temp[j]='\0';j=-1;//�˳�ѭ����ͻ��1 �������Ǵ�0��ʼ����
			end=i;
			//��temp�ӵ�������ȥ
			if(vp!=0)
			{
				CString Value=CString(temp);
				vp->setValue (Value.GetBuffer());
				Value.ReleaseBuffer();
			}
		}
		else
			temp[j]=ch[i];
	}
	temp[j]='\0';//�������һ������ֵ
	//��temp�ӵ�������ȥ
	if(vp!=0)
	{
		CString Value=CString(temp);
		vp->setValue (Value.GetBuffer());
		Value.ReleaseBuffer();
	}

	delete []ch;
	delete []temp;
}

//���ַ���ת��ΪVCARD
int TransStrToVcardObject(CString& VcardStr,VObject* pVcard)
{
	char* pwchVcard  =TransWcharToChar(VcardStr.GetBuffer());
	int   nLen       =strlen(pwchVcard);
	char* wchCurLine = new char[nLen];
	memset(wchCurLine,0,sizeof(char)*nLen);

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
			deal( pVcard, wchCurLine);//����һ�����ʷ�������д�뵽vcard������
			memset(wchCurLine, 0, nLen*sizeof(char));
			j=0;
		}
	}

	delete [] wchCurLine;
	delete [] pwchVcard;
	return TRANS_OK;
}


//��Vcard211�ַ���ת��Ϊ��ϵ����Ϣ
int TransVcard211ToContactInfo(CString& VcardStr,sContactInfo& Info)
{
	if(VcardStr.IsEmpty())
		return STRING_NULL;

	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");//����һ��vcard����,ֱ�ӵ���vObject�Ĺ��캯����ʼ����ʧ��
	if (pMyVcard == NULL)
		return FAILNEW_VCARDOBJECT;
	

	TransStrToVcardObject(VcardStr,pMyVcard);
	
	//------------------------------------------
	VProperty* pVProperty = NULL;	

	//ȡ������
	pVProperty=pMyVcard->getProperty(L"FN");//���û��N���������������ֵ
	if(pVProperty != NULL)
	{
		WCHAR* pValue = pVProperty->getValue(0);
		if(pValue != NULL)
		{
			Info.m_Name = CString(pValue);			
			Info.m_Name.Replace(_T("\\;"), _T(";"));
			Info.m_Name.Replace(_T("\\:"), _T(":"));
			Info.m_Name.Replace(_T("\\\\"), _T("\\"));
		}
	}
	
	//��ȡemail
	pVProperty=NULL;
	pVProperty=pMyVcard->getProperty(L"EMAIL");
	if(pVProperty != NULL)
	{
		WCHAR* pValue = pVProperty->getValue(0);
		if(pValue != NULL)
		{
			Info.m_Email=CString(pValue);
			Info.m_Email.Replace(_T("\\;"), _T(";"));
			Info.m_Email.Replace(_T("\\:"), _T(":"));
			Info.m_Email.Replace(_T("\\\\"), _T("\\"));
		}
	}


    //��ȡOrg
	pVProperty=NULL;
	pVProperty=pMyVcard->getProperty(L"ORG");//��ȡorg
	if(pVProperty != NULL)
	{
		//��ȡcompany
		WCHAR* pValue=pVProperty->getValue(0);
		if(pValue != NULL)
		{
			Info.m_Company = CString(pValue);
			Info.m_Company.Replace(_T("\\;"), _T(";"));
			Info.m_Company.Replace(_T("\\:"), _T(":"));
			Info.m_Company.Replace(_T("\\\\"), _T("\\"));
		}
	
		//��ȡdepartments
		pValue=NULL;
		pValue=pVProperty->getValue(1);
		if(pValue != NULL)
		{
			Info.m_Departments = CString(pValue);
			Info.m_Departments.Replace(_T("\\;"), _T(";"));
		    Info.m_Departments.Replace(_T("\\:"), _T(":"));
		    Info.m_Departments.Replace(_T("\\\\"), _T("\\"));

		}
	}

	//��ȡ����
	pVProperty = NULL;
	pVProperty=pMyVcard->getProperty(L"BDAY");
	if(pVProperty!=0)
	{
		WCHAR* pValue=pVProperty->getValue(0);
		if(pValue != NULL)
			Info.m_Birthday = CString(pValue);
		
	}
	
	//------------- ��ȡ����ID--------------
	pVProperty=NULL;
	pVProperty=pMyVcard->getProperty(L"GROUP");//��ȡ�����
	if(pVProperty!=0)
	{
		int nSum = pVProperty->valueCount();
		for (int i=0; i< nSum; i++)
		{
			WCHAR* pValue=pVProperty->getValue(i);
			if(pValue != NULL)
			{
				CString GroupStr=CString(pValue);
				GroupStr.Replace(_T("\\;"), _T(";"));
				GroupStr.Replace(_T("\\:"), _T(":"));
				GroupStr.Replace(_T("\\"),_T(" "));
				GroupStr.TrimLeft();
				GroupStr.TrimRight();
				Info.m_GroupIDs.push_back(GroupStr);
			}
		}
	}
	
	//��ȡְ��
	pVProperty=0;
	pVProperty=pMyVcard->getProperty(L"TITLE");
	if(pVProperty!=0)
	{
		WCHAR* pValue=pVProperty->getValue(0);
		if( pValue != NULL)
		{
			Info.m_Duties = CString(pValue);
			Info.m_Duties.Replace(_T("\\;"), _T(";"));
			Info.m_Duties.Replace(_T("\\:"), _T(":"));
			Info.m_Duties.Replace(_T("\\\\"), _T("\\"));

		}
	}
	

	//����绰
	bool tel=false;//����Ѱ��TEL:123 ��һ���Ϊ��ʱ ����ܻ��в�����voice�ȣ�������һ��Ϊ0��
	int num=pMyVcard->propertiesCount();//�õ�������Ŀ����Ŀ
	for(int i=0;i<num;i++)//�������ʣ����tel����
	{
		pVProperty=NULL;
		pVProperty=pMyVcard->getProperty(i);//�õ�һ������

		if(pVProperty!=0)
		{
			WCHAR* name=pVProperty->getName();
			if(name!= NULL)
			{
				CString NameStr=CString(name);
				NameStr.MakeLower();
				if(NameStr == _T("tel"))
				{
					int numpara=pVProperty->parameterCount();//��ȡ��������
					if(numpara==0)		//-----phonenumber
					{
						WCHAR* pValue=pVProperty->getValue(0);
						if(pValue != NULL)
						{
							//string des=Qp_decode(curp);//qp��char*
							Info.m_PhoneNumber = CString(pValue);
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
							WCHAR* pValue=pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_Fax = CString(pValue);
						}
						if(hascell==false&&hashome==true)//-----phonehome
						{
							WCHAR* pValue = pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_PhoneHome = CString(pValue);
							
						}
						else if(hascell==false&&haswork==true)//----phonework
						{
							WCHAR* pValue =pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_PhoneWork = CString(pValue);
						}
						else if(hascell==true&&haswork==false&&hashome==false)//----mobilehome
						{
							WCHAR* pValue = pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_MobileNumber = CString(pValue);
						}
						if(hascell==true&&hashome==true)//----mobilehomeΪ����ֹ��TEL;HOME;WORK;CELL����ʽ
						{
							WCHAR* pValue=pVProperty->getValue(0);
							if( pValue != NULL)
								Info.m_MobileHome = CString(pValue);

						}
						if(hascell==true&&haswork==true)//----mobilehome
						{
							WCHAR* pValue=pVProperty->getValue(0);
							if(pValue != NULL )
								Info.m_MobileWork = CString(pValue);
						}
						if(tel==false&&hascell==false&&haswork==false&&hashome==false&&hasfax==false)//----tel
						{
							WCHAR* pValue=pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_PhoneNumber = CString(pValue);

						}
					}
				}
			}
		}
	}

	//��ȡ��ͥסַ
	bool hashomeaddr=false;
	num=0;
	num=pMyVcard->propertiesCount();//�õ�������Ŀ����Ŀ
	for(int i=0;i<num;i++)//�������ʣ����LABEL����
	{
		pVProperty = NULL;
		pVProperty=pMyVcard->getProperty(i);//�õ�һ������
		if(pVProperty!=0)
		{
			WCHAR* Name=pVProperty->getName();
			if(Name!= NULL)
			{
				CString NameStr=CString(Name);
				NameStr.MakeLower();
				if(NameStr == _T("label"))//�����һ����LABEL
				{
					int numpara=pVProperty->parameterCount();//��ȡ��������
					if(numpara>0)
					{
						bool hashome=false;
						hashome=pVProperty->containsParameter(L"HOME");
						if(hashome==true)
						{
							WCHAR* pValue=pVProperty->getValue(0);
							if(pValue != NULL)
							{
								Info.m_HomeAddress = CString(pValue);
								Info.m_HomeAddress.Replace(_T("\\;"), _T(";"));
								Info.m_HomeAddress.Replace(_T("\\:"), _T(":"));
								Info.m_HomeAddress.Replace(_T("\\\\"), _T("\\"));
								hashomeaddr=true;
								i=num;//ֹͣѭ��
							}
						}
					}
				}
			}
		}
	}
	
	if(hashomeaddr==false)
	{
		num=pMyVcard->propertiesCount();//�õ�������Ŀ����Ŀ
		for(int i=0;i<num;i++)//�������ʣ����ADR����
		{
			pVProperty=0;
			pVProperty=pMyVcard->getProperty(i);//�õ�һ������
			if(pVProperty!=0)
			{
				WCHAR* Name=pVProperty->getName();
				if(Name != NULL)
				{
					CString NameStr=CString(Name);
					NameStr.MakeLower();
					if(NameStr == _T("adr"))
					{
						int numpara=pVProperty->parameterCount();//��ȡ��������
						if(numpara>0)
						{
							bool hashome=false;
							hashome=pVProperty->containsParameter(L"HOME");
							if(hashome==true)
							{
								CString HomeStr;
								for(int addrnum=0;addrnum<=6;addrnum++)//�����ʰ���ʽд��homeaddress��//
								{
									WCHAR* pValue=pVProperty->getValue(addrnum);
									if(pValue != NULL)
									{
										HomeStr+=CString(pValue);
									}
								}
								HomeStr.Replace(_T("\\;"), _T(";"));
								HomeStr.Replace(_T("\\:"), _T(":"));
								HomeStr.Replace(_T("\\\\"), _T("\\"));
								Info.m_HomeAddress = HomeStr;
								i=num;//ֹͣѭ��
							
							}
						}
					}
				}
			}
		}
		
	}

	delete pMyVcard;
	return TRANS_OK;
}


//��Ϊ�绰�����Ͷ࣬������һ������ר��ʵ������ ��һ��������ֵ�ĺ��壺
//1 cell 2 cell home 3 cell work 4 tel 5 tel home 6 tel work 7tel fax
//���һ������encodingΪencoding��ʽ�����ڸ�����mySetEncoding(..)���ݲ�����
//�ڶ�������ΪҪ����TEL��Ŀд���VCARD���󣬵���������ΪTEL��ֵ�����绰���롣
bool AddTELToVObject(int type,VObject* vbp,CString& Number)
{
	bool ret=false;
	VProperty* vp=0;
	if(type>7||type<1||Number.IsEmpty())//���tel��ֵΪ���򲻼���
		return false;

	vp=new VProperty(L"TEL");
	if(vp==0)
		return false;
	vp->setValue(Number.GetBuffer());
	Number.ReleaseBuffer();

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

//��ӵ�ַ
void AddADRtoVObject(int type,VObject* vbp,CString& HomeAddress)
{
	int StartPos=0;
	int EndPos = 0;
	vector<CString> AddressList;
	EndPos=HomeAddress.Find(_T(";"),StartPos);
	while( EndPos != -1)
	{
		CString TempStr = HomeAddress.Mid(StartPos,EndPos-StartPos-1);
		AddressList.push_back(TempStr);
		StartPos=EndPos+1;
	}

	CString LastStr = HomeAddress.Mid(StartPos);
	if( !LastStr.IsEmpty() )
	{
		AddressList.push_back(LastStr);
	}

	if(!AddressList.empty())
	{
		//��ÿ���ֶκͲ����ӵ����
		VProperty* vp=NULL;
		vp=new VProperty(L"ADR");//��������
		if(vp!= NULL)
		{
			if(type==0)
				vp->addParameter(L"HOME",NULL);//�������

			for(int Index =0; Index < (int)AddressList.size(); Index++)
			{
				vp->setValue(AddressList[Index].GetBuffer());
				AddressList[Index].ReleaseBuffer();
				
			}
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


//����ϵ����Ϣת��ΪVcard211�ַ���
int TransContactInfoToVard211(sContactInfo& Info,CString& VcardStr)
{
	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");
	if (pMyVcard == NULL)
		return FAILNEW_VCARDOBJECT;
	
	VProperty* pVProperty = NULL;
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

	//��Ӱ汾
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
	
 
	//����
	if(!Info.m_Name.IsEmpty())
	{
		pVProperty = new VProperty(L"N", Info.m_Name.GetBuffer());
		Info.m_Name.ReleaseBuffer();

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

		pVProperty = new VProperty(L"FN", Info.m_Name.GetBuffer());
		Info.m_Name.ReleaseBuffer();
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
	AddTELToVObject(1, pMyVcard, Info.m_MobileNumber);
	AddTELToVObject(2, pMyVcard, Info.m_MobileHome);
	AddTELToVObject(3 ,pMyVcard, Info.m_MobileWork);
	AddTELToVObject(4 ,pMyVcard, Info.m_PhoneNumber);
	AddTELToVObject(5, pMyVcard, Info.m_PhoneHome);
	AddTELToVObject(6, pMyVcard, Info.m_PhoneWork);
	AddTELToVObject(7, pMyVcard, Info.m_Fax);

	// ����
	if(!Info.m_Email.IsEmpty())
	{
		pVProperty = new VProperty(L"EMAIL");
		if(pVProperty != NULL)
		{
			pVProperty->setValue (Info.m_Email.GetBuffer());
			Info.m_Email.ReleaseBuffer();
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

	AddADRtoVObject(0, pMyVcard,Info.m_HomeAddress);
	
	//��˾������
	if( !Info.m_Company.IsEmpty() || !Info.m_Departments.IsEmpty())
	{
		pVProperty = new VProperty(L"ORG");
		if(pVProperty != NULL)
		{
			// �������м��빫˾
			if(!Info.m_Company.IsEmpty())
			{
				pVProperty->setValue(Info.m_Company.GetBuffer());
				Info.m_Company.ReleaseBuffer();
			}
			else
			{
				pVProperty->setValue(L"");
			}

			// �������в��벿��
			if(!Info.m_Departments.IsEmpty())
			{
				pVProperty->setValue(Info.m_Departments.GetBuffer());
				Info.m_Departments.ReleaseBuffer();
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
	if(!Info.m_Birthday.IsEmpty())
	{
		pVProperty = new VProperty(L"BDAY");
		if(pVProperty != NULL)
		{
			pVProperty->setValue (Info.m_Birthday.GetBuffer());
			Info.m_Birthday.ReleaseBuffer();

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
	if(!Info.m_Duties.IsEmpty())
	{
		pVProperty = new VProperty(L"TITLE");
		if(pVProperty != NULL)
		{
			pVProperty->setValue (Info.m_Duties.GetBuffer());
			Info.m_Duties.ReleaseBuffer();

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
	if(!Info.m_GroupIDs.empty())
	{
		pVProperty = new VProperty(L"GROUP");
		if(pVProperty != NULL)
		{
			for(int Index =0; Index < (int)Info.m_GroupIDs.size(); Index++)
			{
				pVProperty->setValue(Info.m_GroupIDs[Index].GetBuffer());
				Info.m_GroupIDs[Index].ReleaseBuffer();

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
		CString TimeStr=CString(chTime);
		pVProperty->setValue (TimeStr.GetBuffer());
		TimeStr.ReleaseBuffer();

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
	VcardStr=CString(wchar1);

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

//��Vcard30�ַ���ת��Ϊ��ϵ����Ϣ
int TransVcard30ToContactInfo(CString& VcardStr,sContactInfo& Info)
{
	return TRANS_OK;

}

//����ϵ����Ϣת��ΪVcard30
int TransContactInfoToVcard30(sContactInfo& Info,CString& VcardStr)
{
	return TRANS_OK;
}

//��CSV��ʽת��Ϊ��ϵ����Ϣ
int TransCSVToContactInfo(CString& CSVStr,sContactInfo& Info)
{
	return TRANS_OK;
}

//����ϵ����Ϣת��ΪCSV��ʽ�ַ���
int TransContactInfoToCSV(sContactInfo& Info,CString& CSVStr)
{
	return TRANS_OK;
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
					my[j]='\0';my[j+1]='\0';j=0;
					for(int i=0;i<j;++i) 
					{ 
						if(my[i]>='a'&&my[i]<='z')//Сд��ĸת�ɴ�д
							my[i] = my[i]-32;//   ����д��a[i]   =   a[i]-( 'a '- 'A '); 
					}
					CString Value=CString(my);
					vp=new VProperty(Value.GetBuffer());//�½�һ�����ʡ�
					Value.ReleaseBuffer();
					
				}
				else if(ispara==true)//��Ӳ���
				{
					if(curchar[i]==':')//���Ϊð�ţ���ʼ��������ֵ������
					{
						ispara=false;isvalue=true;
					}
					my[j]='\0';my[j+1]='\0';

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
					
						CString Name=CString(my);
						CString Value=CString(paravalue);
						vp->addParameter(Name.GetBuffer(),Value.GetBuffer());
						Value.ReleaseBuffer();
						Name.ReleaseBuffer();
					}
					j=0;
				}
				else//������ֵ�Ĵ���
				{
					if(vp!=0)
					{
						my[j]='\0';my[j+1]='\0';
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
						CString Value=CString(my);
						vp->setValue (Value.GetBuffer());
						Value.ReleaseBuffer();
					
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
		my[j]='\0';my[j+1]='\0';//�������һ������ֵ����Ϊ���һ������ֵ��û�зֺŻ�ð�š�
		int len=1024;
		if(isbase64==true)//ת���ɴ��ֱ���󣬸�������ֵ�����ԷֺŸ�����
		{
			char curmy[1025];curmy[0]='\0';
			strcpy(curmy,my);my[0]='\0';
			int len=b64_decode(my,curmy);
			my[len]='\0';
			WCHAR* wchar2=0;
			// �������ԣ���Ϊbase64ʱ ����charsetΪutf8
			//wchar2=ConvertUtf8ToUnicode(my);//utf8��Unicode wchar2�з��ľ�������ֵ����Ҫ�����ʷ��ֶη�������
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
			CString Value=CString(my);
			vp->setValue (Value.GetBuffer());
			Value.ReleaseBuffer();
	
		}
		myVcard->addProperty (vp);//�����ʲ嵽vcard������
		delete vp;
	}
}

