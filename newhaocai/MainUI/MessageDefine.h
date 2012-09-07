/***********************************************************************************
* ˵��      ��  ���ļ�������Ϣö�ٵĶ���                                           *
* ������    ��  ̷����                                                             *
* ��������  ��  2011-9-8                                                           *
***********************************************************************************/

#pragma once

//��Ϣ����
enum eMessage
{
	//ϵͳ��Ϣ
	MSG_SYSTEM,				           //ת��ϵͳ��Ϣ

	//����������Ϣ
	MSG_GET_PHONEINFO_OVER,           //��ȡ�ֻ���Ϣ���

	/****************����������Ϣ*****************************/  
	 
	MSG_CONTACT_INFO_TO_DATA_ENGINE,          //��ϵ�˵�����������Ϣ
	MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,     //��ϵ�˷��鵽����������Ϣ
	MSG_SMS_INFO_TO_DATA_ENGINE,              //���ŵ�����������Ϣ

	/****************��ϵ��ģ����Ϣ*****************************/
	MSG_CONTACT_REQUEST_CMD,                  //������ϵ��������������
	MSG_CONTACT_ADD_CMD,                      //�����ϵ������
	MSG_CONTACT_DELTE_CMD,                    //ɾ����ϵ������
	MSG_CONTACT_DELTE_ALL_CMD,                //ɾ��������ϵ��
	MSG_CONTACT_EDIT_CMD,                     //�༭��ϵ������
	MSG_CONTACT_BACKUP_CMD,                   //��ϵ�˱���

	MSG_CONTACTGROUP_REQUEST_CMD,             //��ϵ�˷�����Ϣ
	MSG_CONTACTGROUP_ADD_CMD,                 //�����ϵ�˷���
	MSG_CONTACTGROUP_DELETE_CMD,              //ɾ����ϵ�˷���
	MSG_CONTACTGROUP_DELETE_ALL_CMD,          //ɾ��������ϵ�˷���
	MSG_CONTACTGROUP_EDIT_CMD,                //�༭��ϵ�˷���

	/****************����ģ����Ϣ*****************************/
	MSG_SMS_REQUEST_CMD,                  //�������������������
	MSG_SMS_ADD_CMD,                      //��Ӷ�������
	MSG_SMS_DELTE_CMD,                    //ɾ����������
	MSG_SMS_DELTE_ALL_CMD,                //ɾ�����ж���
	MSG_SMS_EDIT_CMD,                     //�༭��������
	MSG_SMS_BACKUP_CMD,                   //���ű���
	MSG_SMS_SEND_CMD,					  //���Ͷ���

	/****************������Ϣ*****************************/
	
	MSG_START_CONNECT_PHONE_WIFI,              //ͨ������������WIFI
	MSG_UPDATE_USB_DEVICES_LIST,              //����USB�豸�б���Ϣ
	MSG_UPDATE_WIFI_DEVICES_LIST,             //����WIFI�豸�б���Ϣ
	MSG_UPDATE_DLG_STATUS_BY_WIFI,            //���¶Ի���״̬

	//��ҳ��Ϣ
	MSG_START_CONECT_PHONE,           //��ʼ�����ֻ���Ϣ
	MSG_UPDATE_DRIVE_INFO_LIST,       //����������Ϣ�б�
	MSG_GOTO_DEVICE_LIST,             //��ת���豸�б�
	MSG_GOTO_USB_TIPDLG,              //��ת��USB��ʾҳ��
	MSG_GOTO_USB_CONNECTDLG,          //��ת��USB����ҳ��
	MSG_GOTO_INSTALL_DRIVE_DLG,       //��ת��������װҳ��
	MSG_GOTO_TAB_DOWNLOAD,			//��ת�����ص�ҳ��
	MSG_GOTO_TAB_CONTACTS,			  //��ת����ϵ��ҳ��
	MSG_GOTO_TAB_SMS,				  //��ת������ҳ��
	MSG_GOTO_TAB_FILEMANAGE,		  //��ת���ļ��������	
	MSG_UPDATE_COUNTDATA_SUM,		  //��������ͳ������
	MSG_DISCONNECT_PHONE,			  //�ֻ�������Ϣ
	MSG_CONNECTED_PHONE,			  //�ֻ�������Ϣ
	MSG_UPDATE_LOGINED_STATE,			//��½״̬ˢ��
	MSG_DOWN_PHONE_BORAD_IMAGE,         //�����ֻ������Ϣ
	MSG_UPDATE_PHONE_BORAD_IMAGE,       //�����ֻ������Ϣ
	MSG_UPDATE_DOWNLOAD_COUNT,			//�����������ͳ����
	MSG_SHOW_DOWNLOAD_TIP,				//��ʾ������ʾ��Ϣ


	//��ϵ����Ϣ
	MSG_QUERY_INPUT_VALUE,				  //�༭�������������
	MSG_EDIT_KILLFFOUSE,				//�༭��ʧȥ������Ϣ
	MSG_CONTACT_GROUP_COMMIT,			//��ϵ�˷����ύ�¼�
	MSG_COMBOX_KIILFOUSE,				//ʧȥ�����¼�
	MSG_CONTACT_LBCLICK,				//��ϵ�˵����¼�
	MSG_EDIT_WHEEL,						//�༭������¼�
	MSG_UPDATE_CONTACT_GROUP,			//������ϵ��������
	MSG_UPDATE_SHOW_CONTACT_LIST,		//��ʾ��ϵ���б�
	MSG_EDIT_CLICKACTIVE,				// �༭��ͨ�������������

	//������Ϣ
	MSG_BEGIN_IMPORT_SMS,             //��ʼ�������
	MSG_EDIT_CHANGE,				  // �༭������ݷ����ı�ʱ����

	//�ļ�������Ϣ
	MSG_UPDATE_APP_LIST,					//ˢ�µ�ǰ�б���Ϣ
	MSG_UPNETDISK_DATA,                     //������������
	MSG_QUERY_APP,						//����Ӧ�ó�����Ϣ

	//������Ϣ
	MSG_OVER_PROGRESS,					//������������Ϣ���������ٽ������Ի���
	MSG_CLOSE_PROGRESS,					//�رս�����
	MSG_UPDATE_PROGRESS,				//���½�������Ϣ (ע�����ٷֱ���ʾ��Ҫ��ȫ��, ����Χ��ʾ��Ҫ��������)
	MSG_RESET_PROGRESS,					//���ý�����Ϣ
	MSG_STARTDOWN_INSTALL_PACK,         //��ʼ���ذ�װ����Ϣ
	MSG_DOWNING_INSTALL_PACK,            //��װ�����ؽ�������Ϣ
	MSG_CHECK_PACK_STATUS,                //��ⰲװ��״̬
	MSG_DOWNOVER_INSTALL_PACK ,            //���ذ�װ�����Ϣ
	MSG_STARTCHECK_INSTALL_PACK,          //��������°汾
	MSG_SHOW_TOOLTIP,					//��ʾ��ʾ��Ϣ
	MSG_LIST_MOUSE_MOVE,				//�б���껬���¼�
	MSG_GET_MOUSE_POINT,				//��ȡ��괰������
	

	MSG_CREATE_SHADE_FLOOR,            //���´����ɲ���Ϣ

	MSG_UPDATE_USB_LIST,              //����USB�����б�
	MSG_UPDATE_WIFI_LIST,              //����WIFI�����б�	
};

const	WORD	MRSSAGE_TYPE_COUNT	=	74;			//��Ϣ������
//ÿ������һ����ϢʱMRSSAGE_TYPE_COUNT������1����MRSSAGE_TYPE_COUNT������1��ʼ������0
