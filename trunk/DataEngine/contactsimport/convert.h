
 
#include "contact_define.h"
  


//������ͷ�ļ��ж�����һЩҪ�õĳ��������ݽṹ��
#include <vector>
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
//* ��TrPbItem�ṹ�е���Ŀ��homeaddressһ������ΪQUOTED-PRINTABLE��������һ�㶼����Ĭ��ֵ��
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
* ��TrPbItem��ʽ������ת����VCard2.1��ʽ
*
* @pbitem (in)Ϊ��ת��������	TrPbItem �ṹ��homeaddress�Ľṹ��: 
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
* ��ϸע�������ConvertTrPbItemtoVcard21(.....);ֻ�ǽ�����������ɵ��ַ���д��ָ�����ļ�����ȥ��,
* @pbitem (in) ˵���ԣ� @path (in)Ҫд����ļ���Ŀ¼���ļ�����	@enchset(in) ˵����
* @ret ���ת���ɹ�������CONVERT_OK�����򷵻���Ӧ�Ĵ������
*
* ע�⣺�����д�ļ����Ǹ���ʽд����ԭ���ļ��е����ݶ������ǵ���
***********************************************************************************************************************/
int ConvertTrPbItemtoVcard21andWriteToFile(const TrPbItem& trPbItem, WCHAR* pwchPath);

/**********************************************************************************************************************
* ���������һ��pbitem����Ϣд�뵽һ���ļ�����ȥ��
* @pbitem (in) TrPbItem���飻 @path (in)Ҫд����ļ���Ŀ¼���ļ�����	@enchset (in)˵���� @num (in)��ʾpbitem�����ά����
* @ret ���ת���ɹ�������CONVERT_OK�����򷵻���Ӧ�Ĵ������

* ������ʹ���������������һ����ϵ��д��һ���ļ���ȥ����������ļ��ļ����Ը��á�һ���ļ���д�����ϵ�˵Ļ���Щ������ܻ᲻ʶ��
***********************************************************************************************************************/
int ConvertTrPbItemtoVcard21andWriteToOneFile(const vector< TrPbItem> &pbContactsMgr, WCHAR* path);

/**********************************************************************************************************************
* ��һ������vcard2.1��ʽ���ַ����е����ݶ���TrPbItem�ṹ��
* @myvcard21str (in)����vcard2.1��ʽ���ַ���	@pbitem (out)����ʢ��ת����Ľ���������û��Լ����������ݽṹ��
*
* ת���ɹ������ط���CONVERT_OK�����򷵻���Ӧ�Ĵ������
***********************************************************************************************************************/
int ConvertVcard21toTrPbItem(const wstring & myvcard21str, TrPbItem* pTrPbItem);

/**********************************************************************************************************************
* ���ļ��ж����ݲ������е�������ȡ��TrPbItem�ṹ��
***********************************************************************************************************************/
int ConvertVcard21toTrPbItemandReadFromFile(const WCHAR* path,vector< TrPbItem> &m_PbContactsMgr,int n);

/**********************************************************************************************************************
* �뺯��ConvertVcard21toTrPbItem(..)�Ĺ������ƣ�ֻ�Ǵ��ļ��ж����ݣ����������ַ���
***********************************************************************************************************************/
int ConvertVcard21toTrPbItemandReadFromFile(const WCHAR* path, TrPbItem* pTrPbItem);

/**********************************************************************************************************************
* ���Եõ�һ��vcard2.1��vcard3.0�ļ����ж��ٸ�vcard���󣨼���ϵ�ˣ�����һ���ļ��д洢�˼�����ϵ��
* @path (in)�ļ���·�����ļ���
* @ret �����ļ��к��ж��ٸ���ϵ�˵���Ϣ������д��󷵻�0��ֵ��
***********************************************************************************************************************/
int GetVcardObjectNum(const WCHAR* path);


/**********************************************************************************************************************
* ���漸�������Ĺ��ܼ�ʵ��������ļ����������ƣ���ο����漸����Ӧ������˵��
***********************************************************************************************************************/
int ConvertTrPbItemtoVcard30(const TrPbItem& pbitem,wstring& myvcard30str);

int ConvertTrPbItemtoVcard30andWriteToFile(const TrPbItem& pbitem,WCHAR* path);

int ConvertTrPbItemtoVcard30andWriteToOneFile(const TrPbItem pbitem[],WCHAR* path,int num);

int ConvertVcard30toTrPbItem(const wstring & myvcard30str,TrPbItem& pbitem);

int ConvertVcard30toTrPbItemandReadFromFile(const WCHAR* path,TrPbItem& pbitem);

int ConvertVcard30toTrPbItemandReadFromFile(const WCHAR* path,TrPbItem pbitem[],int n);

/**********************************************************************************************************************
* ����ṹ���ں���ConvertCSVtoTrPbItem(...)��ʹ�ã�����ָ������������CSV�ļ��е�˳�򡣲�ͬ��csv�ļ����������ŷŵ�˳����ܲ�ͬ
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
* ��һЩTrPbItem�ṹ������ת����CSV��ʽ��
* @pbitem[] (in)Ϊpbitem�����飬ʢ�Ž�Ҫת�������ݡ�	@CSVstr (out)�û����������ݽṹ�����ڽ��������@num (in)Ϊpbitem����ĳ���
*
* ת���ɹ������ط���CONVERT_OK�����򷵻���Ӧ�Ĵ������
*
***********************************************************************************************************************/
int ConvertTrPbItemtoCSV(const vector< TrPbItem*>* pVectorContacts, wstring& CSVstr);


/**********************************************************************************************************************
* ������CSV�ṹ�����ݴ洢��TrPbItem�ṹ�С�
* @CSVstr����CSV�ṹ�����ݵ��ַ���.ע������ַ�����ֱ�Ӱ������ݼ��ɣ����ð���˵�����õ�ͷ����csv�ļ��ĵ�һ�����ݡ�	
* @pbitem������ʢ��ת��������ݣ��û�������@order����˵������������CSV�ṹ�е�����˳��
*
***********************************************************************************************************************/
int ConvertCSVtoTrPbItem(char* pchLineText, TrPbItem* pTrPbItem);
