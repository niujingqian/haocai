

CString cszCB_IsOurCustomBrowser	    = _T("CB_IsOurCustomBrowser");

//���� ���Ի��� �Ĳ���
CString csCPP_MoveMianDlg				= _T("CPP_MoveMainDlg");				//�ƶ����Ի���
CString csCPP_Close						= _T("CB_Close");						//�ر����Ի���
CString csCPP_MinDlg					= _T("CPP_Min");						//��С�����Ի���

//��ϵ��ģ�麯��
CString csCPP_OnRequestContactData      = _T("CPP_OnRequestContactData");		//������ϵ������
CString csCPP_OnRequestRfreshContactData= _T("CPP_OnRequestRfreshContactData"); //����ˢ����ϵ������
CString csCPP_OnRequestAddContactData   = _T("CPP_OnRequestAddContactData");	//�����ϵ������
CString csCPP_OnRequestAddContactFile   = _T("CPP_OnRequestAddContactFile");	//�����ϵ���ļ�
CString csCPP_OnRequestBackUpContactData= _T("CPP_OnRequestBackUpContactData"); //������ϵ��
CString csCPP_OnRequestDeletContactData = _T("CPP_OnRequestDeleteContactData");	//ɾ����ϵ��
CString csCPP_OnRequestEditContactData  = _T("CPP_OnRequestEditContactData");	//�༭��ϵ��

CString csCPP_OnRequestGroupData        = _T("CPP_OnRequestGroupData");			//�������
CString csCPP_OnRequestAddGroupData     = _T("CPP_OnRequestAddGroupData");		//��ӷ���
CString csCPP_OnRequestDeleteGroupData  = _T("CPP_OnRequestDeleteGroupData");	//ɾ������
CString csCPP_OnRequestEditGroupData    = _T("CPP_OnRequestEditGroupData");		//�༭����
//����ģ�麯��
CString csCPP_OnRequestSmsData      = _T("CPP_OnRequestSmsData");		//�����������
CString csCPP_OnRequestDeleteSmsData= _T("CPP_OnRequestDeleteSmsData");	//����ɾ������
CString csCPP_OnRequestSendSms      = _T("CPP_OnRequestSendSms");		//�����Ͷ���
//�ļ�����ģ�麯��

//�ӿڶ���
enum DISPID_CPP {
	DISPID_CB_IsOurCustomBrowser = 1,
	//�������Ի���Ĳ���
	DISPID_CB_Close,						//�رնԻ���
	DISPID_CB_MoveMianDlg,					//����ƶ����Ի���
	DISPID_CB_MinDlg,						//��С���Ի���
	//��ϵ��ģ��Ĳ���
	DISPID_CB_RequestContactData,			//������ϵ������
	DISPID_CB_RequestRfreshContactData,		//����ˢ����ϵ������
	DISPID_CB_RequestAddContactData,		//�����ϵ������
	DISPID_CB_RequestAddContactFile,        //�����ϵ���ļ�
	DISPID_CB_RequestDeleteContactData,     //ɾ����ϵ��
	DISPID_CB_RequestEditContactData,       //�༭��ϵ��
	DISPID_CB_RequestBackUpContactData,     //������ϵ��
	
	DISPID_CB_RequestGroupData,             //�������
	DISPID_CB_RequestAddGroupData,          //��ӷ���
	DISPID_CB_RequestDeleteGroupData,       //ɾ������
	DISPID_CB_RequestEditGroupData,         //�༭����
	//����ģ��Ĳ���
	DISPID_CB_RequestSmsData,				//�����������
	DISPID_CB_RequestAddSmsData,			//��Ӷ���
	DISPID_CB_RequestAddSmsFile,			//��Ӷ����ļ�
	DISPID_CB_RequestDeleteSmsData,			//ɾ������
	DISPID_CB_RequestEditSmsData,			//�༭����
	DISPID_CB_RequestSendSms,				//���Ͷ���
	DISPID_CB_RequestAcceptSms,				//���յ����µĶ���
	//�ļ�����ģ��Ĳ���
	DISPID_CB_RequestInstallApk,			//����װAPK
	DISPID_CB_RequestBatchInstallApk,		//����������װAPK
	DISPID_CB_RequestUninstallApk,			//����ж��APK
	DISPID_CB_RequestBatchUninstallApk,		//��������ж��APK
};