/***********************************************************************************
* ˵��      ��  ��ϵ��ת������                                                     *
* ������    ��  ̷����                                                             *
* ��������  ��  2012-2-24                                                          *
***********************************************************************************/

//�Զ����һЩ����ֵ
#define TRANS_OK                 1  //ת���ɹ�
#define ALLO_FAIL                 -1  //�ڴ����ʧ��
#define FAILNEW_VCARDOBJECT       -2  // ����VObjectʧ��
#define STRING_NULL	              -4  //���������ַ���Ϊ�մ�
#define NMU_IS_LESSTHANONE        -5  //num��ֵС��1
#define NMU_ERROR                 -6  //num��ֵС�ڱȽṹ���е��ֶ����࣬��Ϊ����
#define FILE_FORMAT_ERROR         -7  //��ʽ������



//��Vcard211�ַ���ת��Ϊ��ϵ����Ϣ
int TransVcard211ToContactInfo(CString& VcardStr,sContactInfo& Info);

//����ϵ����Ϣת��ΪVcard211�ַ���
int TransContactInfoToVard211(sContactInfo& Info,CString& VcardStr);

//��Vcard30�ַ���ת��Ϊ��ϵ����Ϣ
int TransVcard30ToContactInfo(CString& VcardStr,sContactInfo& Info);

//����ϵ����Ϣת��ΪVcard30
int TransContactInfoToVcard30(sContactInfo& Info,CString& VcardStr);

//��CSV��ʽת��Ϊ��ϵ����Ϣ
int TransCSVToContactInfo(CString& CSVStr,sContactInfo& Info);

//����ϵ����Ϣת��ΪCSV��ʽ�ַ���
int TransContactInfoToCSV(sContactInfo& Info,CString& CSVStr);

//���ַ���ת��ΪVCARD
//int TransStrToVcardObject(CString& VcardStr,VObject* pVcard);

