
#include "../common/Include/DataDefine.h"

//������ͷ�ļ��ж�����һЩҪ�õĳ��������ݽṹ��
#include <string>//  �����ַ����Ĵ���
using namespace std;


//�Զ����һЩ����ֵ
#define SUCESS_BUT_SPACE_SHORT 3
#define CONVERT_OK  1 //ת���ɹ�
#define ALLO_FAIL -1 //�ڴ����ʧ��
#define FAILNEW_VCARDOBJECT -2  // ����VObjectʧ��
#define FILE_OPEN_FAILED -3
#define STRING_NULL	 -4	//���������ַ���Ϊ�մ�
#define NMU_IS_LESSTHANONE -5 //num��ֵС��1
#define NMU_ERROR -6 //num��ֵС�ڱȽṹ���е��ֶ����࣬��Ϊ����
#define FILE_FORMAT_ERROR -7


///**********************************************************************************************************************
//* ���������˵��һЩVCARD��ÿһ����Ŀ��ֵ��ENCODING����Ҫ���������紫������ж����ݵ������Ա�����
//* ���������У�7BIT��BASE64��QUOTED-PRINTABLE��8BIT��Ĭ��ֵ��7BIT��
//* ��ContactInfo�ṹ�е���Ŀ��homeaddressһ������ΪQUOTED-PRINTABLE��������һ�㶼����Ĭ��ֵ��
//* 0 ��ʾ7BIT��	1 BASE64��	2 QUOTED-PRINTABLE��	3	8BIT
//* ���ָ����ֵ�Ƿ�����7BIT���롣
//************************************************************************************************************************/
//class encodingcharset
//{
//public:
//	encodingcharset()
//	{
//		nameEn=phoneworkEn=emailEn=homeaddressEn=companyEn=birthdayEn=IDEn=typeEn=0;//Ĭ�ϸ�ֵȫΪ0
//	}
//	
//	int nameEn;
//	int phoneworkEn;  
//	int emailEn;        
//	int homeaddressEn;
//	int companyEn;
//	int birthdayEn; 
//	int IDEn;
//	int typeEn;
//private://���ұ����������á�
//	encodingcharset(int na,int ph,int em,int add,int comp,int bir,int id,int type)
//	{
//		nameEn=na;	phoneworkEn=ph;	emailEn=em;	homeaddressEn=add;
//		companyEn=comp;	birthdayEn=bir;	IDEn=id;	typeEn=type;
//	}
//};

/*********************************************************************************************************************
* ��ContactInfo��ʽ������ת����VCard2.1��ʽ
*
* @pbitem (in)Ϊ��ת��������	ContactInfo �ṹ��homeaddress�Ľṹ��: 
*  סլ�ʵݵ�ַ(��������);סլ��չ��ַ;סլ���ڽֵ�;��;ʡ����������;�ʱ�;���ҵ�������ֵ֮����Ӣ�ĵķֺŸ������ֶ��ж���
*  ���зֺţ������һ��ֵΪ�գ�ҲҪ�ӷֺţ�����˹��ҵ����������Ķ�Ϊ�յ�д����;;;;;;���ҵ���
* @myvcard21str (out) ���ڴ洢ת��������ݣ�myvcard21str��ʹ���߽��������ݽṹ�����������ô��ݸ�������
* @enchset (in)�д洢��ΪVCARD�и���Ŀ��ʹ�õı������ͣ����Ժ������˲��ʹ�ã�������ֻ������������
*
* @ret ���ת���ɹ�������CONVERT_OK�����򷵻���Ӧ�Ĵ������
*
* �������ĸ�ʽ���ԣ��������������飬�ʲ��ᱨ����email��ַд��akflajfasdf Ҳ���ᱨ��
* ���ĳһ��ֵ���зֺ�(';')������Զ�����'\'����Ϊ��VCARD��,�ֺ��Ƿָ���������Զ�������ת���ַ���
* ע�⣺ʹ��ʱ���pbitemĳһ���ֵΪ�գ���һ��Ҫ'\0'����char[0]λ���ϣ�pbitem.mobilenumber��ֵΪ��
* ����pbitem.mobilenumber[0]='\0';������������
***********************************************************************************************************************/
 

/**********************************************************************************************************************
* ��ϸע�������ConvertContactInfotoVcard21(.....);ֻ�ǽ�����������ɵ��ַ���д��ָ�����ļ�����ȥ��,
* @pbitem (in) ˵���ԣ� @path (in)Ҫд����ļ���Ŀ¼���ļ�����	@enchset(in) ˵����
* @ret ���ת���ɹ�������CONVERT_OK�����򷵻���Ӧ�Ĵ������
*
* ע�⣺�����д�ļ����Ǹ���ʽд����ԭ���ļ��е����ݶ������ǵ���
***********************************************************************************************************************/
int ConvertContactInfotoVcard21andWriteToFile(const sContactInfo& trPbItem, WCHAR* pwchPath);

/**********************************************************************************************************************
* ���������һ��pbitem����Ϣд�뵽һ���ļ�����ȥ��
* @pbitem (in) ContactInfo���飻 @path (in)Ҫд����ļ���Ŀ¼���ļ�����	@enchset (in)˵���� @num (in)��ʾpbitem�����ά����
* @ret ���ת���ɹ�������CONVERT_OK�����򷵻���Ӧ�Ĵ������

* ������ʹ���������������һ����ϵ��д��һ���ļ���ȥ����������ļ��ļ����Ը��á�һ���ļ���д�����ϵ�˵Ļ���Щ������ܻ᲻ʶ��
***********************************************************************************************************************/
int ConvertContactInfotoVcard21andWriteToOneFile(const vector< sContactInfo> &pbContactsMgr, WCHAR* path);

/**********************************************************************************************************************
* ��һ������vcard2.1��ʽ���ַ����е����ݶ���ContactInfo�ṹ��
* @myvcard21str (in)����vcard2.1��ʽ���ַ���	@pbitem (out)����ʢ��ת����Ľ���������û��Լ����������ݽṹ��
*
* ת���ɹ������ط���CONVERT_OK�����򷵻���Ӧ�Ĵ������
***********************************************************************************************************************/
int ConvertVcard21toContactInfo(const wstring & myvcard21str, sContactInfo* pContactInfo);


int ConverTrpbItemToVcard21Str(const sContactInfo& trPbItem, wstring & myvcard21str, bool bIsWriteVersion);


/**********************************************************************************************************************
* ���ļ��ж����ݲ������е�������ȡ��ContactInfo�ṹ��
***********************************************************************************************************************/
int ConvertVcard21toContactInfoandReadFromFile(const WCHAR* path,vector< sContactInfo> &m_PbContactsMgr,int n);

/**********************************************************************************************************************
* �뺯��ConvertVcard21toContactInfo(..)�Ĺ������ƣ�ֻ�Ǵ��ļ��ж����ݣ����������ַ���
***********************************************************************************************************************/
int ConvertVcard21toContactInfoandReadFromFile(const WCHAR* path, sContactInfo* pContactInfo);

/**********************************************************************************************************************
* ���Եõ�һ��vcard2.1��vcard3.0�ļ����ж��ٸ�vcard���󣨼���ϵ�ˣ�����һ���ļ��д洢�˼�����ϵ��
* @path (in)�ļ���·�����ļ���
* @ret �����ļ��к��ж��ٸ���ϵ�˵���Ϣ������д��󷵻�0��ֵ��
***********************************************************************************************************************/
int GetVcardObjectNum(const WCHAR* path);


/**********************************************************************************************************************
* ���漸�������Ĺ��ܼ�ʵ��������ļ����������ƣ���ο����漸����Ӧ������˵��
***********************************************************************************************************************/
int ConvertContactInfotoVcard30(const sContactInfo& pbitem,wstring& myvcard30str);

int ConvertContactInfotoVcard30andWriteToFile(const sContactInfo& pbitem,WCHAR* path);

int ConvertContactInfotoVcard30andWriteToOneFile(const sContactInfo pbitem[],WCHAR* path,int num);

int ConvertVcard30toContactInfo(const wstring & myvcard30str,sContactInfo& pbitem);

int ConvertVcard30toContactInfoandReadFromFile(const WCHAR* path,sContactInfo& pbitem);

int ConvertVcard30toContactInfoandReadFromFile(const WCHAR* path,sContactInfo pbitem[],int n);

/**********************************************************************************************************************
* ����ṹ���ں���ConvertCSVtoContactInfo(...)��ʹ�ã�����ָ������������CSV�ļ��е�˳�򡣲�ͬ��csv�ļ����������ŷŵ�˳����ܲ�ͬ
* ��������������ݽṹ������ָ������ֵ���ڵ�˳��
* �Ǵ�1��ʼ�������Ǵ�0��ʼ��������һ���������ַ����е�λ����1��������0��
***********************************************************************************************************************/
struct orderofpropincsv
{
	int name;	int mobilenumber;	int mobilehome;	int mobilework;		int phonenumber;	int phonehome;	
	int phonework;	int email;		int PostOfficeAddress; int ExtendedAddress;int Street;int Locality;
	int Region;int Postalcode;int Country;		int company;		int birthday;
	int fax;		int departments;	int duties;
};

/**********************************************************************************************************************
* ��һЩContactInfo�ṹ������ת����CSV��ʽ��
* @pbitem[] (in)Ϊpbitem�����飬ʢ�Ž�Ҫת�������ݡ�	@CSVstr (out)�û����������ݽṹ�����ڽ��������@num (in)Ϊpbitem����ĳ���
*
* ת���ɹ������ط���CONVERT_OK�����򷵻���Ӧ�Ĵ������
*
***********************************************************************************************************************/
int ConvertContactInfotoCSV(const vector< ContactInfo*>* pVectorContacts, wstring& CSVstr);


/**********************************************************************************************************************
* ������CSV�ṹ�����ݴ洢��ContactInfo�ṹ�С�
* @CSVstr����CSV�ṹ�����ݵ��ַ���.ע������ַ�����ֱ�Ӱ������ݼ��ɣ����ð���˵�����õ�ͷ����csv�ļ��ĵ�һ�����ݡ�	
* @pbitem������ʢ��ת��������ݣ��û�������@order����˵������������CSV�ṹ�е�����˳��
*
***********************************************************************************************************************/
int ConvertCSVtoContactInfo(char* pchLineText, ContactInfo* pContactInfo);

int ConvertVcard211toContactInfo(CString cStrTmp, ContactInfo* pContactInfo);
