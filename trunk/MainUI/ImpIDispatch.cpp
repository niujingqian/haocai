/********************************************************************
	file base:	ImpIDispatch
	author:		������
	purpose:	����ʵ���Զ����ӿڣ�ʵ�ֺ���ҳ����
*********************************************************************/

#include "stdafx.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include "ImpIDispatch.h"
#include "InterFaceName.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImpIDispatch::CImpIDispatch(void)
{
	m_cRef = 0;
	m_InterfaceToJs=new InterfaceToJS((IDispatch*)this);
}

CImpIDispatch::~CImpIDispatch(void)
{
	ASSERT(m_cRef==0);
}

STDMETHODIMP CImpIDispatch::QueryInterface(REFIID riid, void** ppv)
{
	*ppv = NULL;
	
	if(IID_IDispatch == riid)
	{
        *ppv = this;
	}
	
	if(NULL != *ppv)
    {
		((LPUNKNOWN)*ppv)->AddRef();
		return NOERROR;
	}
	
	return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) CImpIDispatch::AddRef(void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CImpIDispatch::Release(void)
{
	return --m_cRef;
}

STDMETHODIMP CImpIDispatch::GetTypeInfoCount(UINT* /*pctinfo*/)
{
	return E_NOTIMPL;
}

STDMETHODIMP CImpIDispatch::GetTypeInfo(
			/* [in] */ UINT /*iTInfo*/,
            /* [in] */ LCID /*lcid*/,
            /* [out] */ ITypeInfo** /*ppTInfo*/)
{
	return E_NOTIMPL;
}

STDMETHODIMP CImpIDispatch::GetIDsOfNames(
			/* [in] */ REFIID riid,
            /* [size_is][in] */ OLECHAR** rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID* rgDispId)
{
	HRESULT		hr		= NOERROR;
	UINT		i		= 0;
	CString		cszName	= rgszNames[i];
	for(i=0; i<cNames; ++i)
	{
		if(cszName == cszCB_IsOurCustomBrowser)
		{
			rgDispId[i] = DISPID_CB_IsOurCustomBrowser;
		}
		/**************************���Ի������**************************************/
		else if(cszName == csCPP_Close)
		{
			rgDispId[i] = DISPID_CB_Close;
		}
		else if (cszName == csCPP_MoveMianDlg)
		{
			rgDispId[i] = DISPID_CB_MoveMianDlg;
		}
		else if (cszName == csCPP_MinDlg)
		{
			rgDispId[i] = DISPID_CB_MinDlg;
		}
		/*******************************��ϵ��ģ�����*****************************/
		else if (cszName == csCPP_OnRequestContactData)
		{
			rgDispId[i] = DISPID_CB_RequestContactData;
		}
		else if (cszName == csCPP_OnRequestRfreshContactData)
		{
			rgDispId[i] = DISPID_CB_RequestRfreshContactData;
		}
		else if (cszName == csCPP_OnRequestAddContactData)
		{
			rgDispId[i] = DISPID_CB_RequestAddContactData;
		}
		else if (cszName == csCPP_OnRequestAddContactFile)
		{
			rgDispId[i] = DISPID_CB_RequestAddContactFile;
		}
		else if (cszName == csCPP_OnRequestDeletContactData)
		{
			rgDispId[i] = DISPID_CB_RequestDeleteContactData;
		}
		else if (cszName == csCPP_OnRequestBackUpContactData)
		{
			rgDispId[i] = DISPID_CB_RequestBackUpContactData;
		}
		else if (cszName == csCPP_OnRequestEditContactData)
		{
			rgDispId[i] = DISPID_CB_RequestEditContactData;
		}
		else if (cszName == csCPP_OnRequestAddGroupData)
		{
			rgDispId[i] = DISPID_CB_RequestAddGroupData;
		}
		else if (cszName == csCPP_OnRequestGroupData)
		{
			rgDispId[i] = DISPID_CB_RequestGroupData;
		}
		else if (cszName == csCPP_OnRequestDeleteGroupData)
		{
			rgDispId[i] = DISPID_CB_RequestDeleteGroupData;
		}
		else if (cszName == csCPP_OnRequestEditGroupData)
		{
			rgDispId[i] = DISPID_CB_RequestEditGroupData;
		}
		/******************************����ģ�����************************/
		else if (cszName == csCPP_OnRequestSmsData)
		{
			rgDispId[i] = DISPID_CB_RequestSmsData;
		}
		else if (cszName == csCPP_OnRequestDeleteSmsData)
		{
			rgDispId[i] = DISPID_CB_RequestDeleteSmsData;
		}
		else if (cszName == csCPP_OnRequestSendSms)
		{
			rgDispId[i] = DISPID_CB_RequestSendSms;
		}
		/****************************�ļ�����ģ�����**********************/
		else
		{
			// One or more are unknown so set the return code accordingly
			hr = ResultFromScode(DISP_E_UNKNOWNNAME);
			rgDispId[i] = DISPID_UNKNOWN;
		}
	}
	return hr;
}

void CImpIDispatch::DisProperty(WORD wFlag, VARIANT *varResul)
{
	if(wFlag & DISPATCH_PROPERTYGET)
	{
		if(varResul != NULL)
		{
			VariantInit(varResul);
			V_VT(varResul) = VT_BOOL;
			V_BOOL(varResul) = true;
		}
	}
}

STDMETHODIMP CImpIDispatch::Invoke(
			/* [in] */ DISPID dispIdMember,
			/* [in] */ REFIID /*riid*/,
			/* [in] */ LCID /*lcid*/,
			/* [in] */ WORD wFlags,
			/* [out][in] */ DISPPARAMS* pDispParams,
			/* [out] */ VARIANT* pVarResult,
			/* [out] */ EXCEPINFO* /*pExcepInfo*/,
			/* [out] */ UINT* puArgErr)
{	

	if(dispIdMember == DISPID_CB_IsOurCustomBrowser) 
	{
		DisProperty(wFlags, pVarResult);
		if(wFlags & DISPATCH_METHOD)
		{
			VariantInit(pVarResult);
			V_VT(pVarResult) = VT_BOOL;
			V_BOOL(pVarResult) = true;
		}
	}

	switch ((int)dispIdMember)
	{
		/***********************************���Ի������**********************************************/
	case (int)DISPID_CB_Close:
		{
			DisProperty(wFlags, pVarResult);	
			if(wFlags & DISPATCH_METHOD)
			{
				m_InterfaceToJs->CPP_Close();
			}
		}
		break;
	case (int)DISPID_CB_MoveMianDlg:
		{		
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				int	Xpoint	= pDispParams->rgvarg[1].intVal;
				int	Ypoint	= pDispParams->rgvarg[0].intVal;
				m_InterfaceToJs->CPP_MoveMianDlg(Xpoint , Ypoint);
			}
		}
		break;
	case (int)DISPID_CB_MinDlg:
		{
			DisProperty(wFlags,pVarResult);
			if (wFlags & DISPATCH_METHOD)
			{
				m_InterfaceToJs->CPP_MinDlg();
			}
		}
		break;
		/***********************************��ϵ�˲���**********************************************/
	case (int)DISPID_CB_RequestContactData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				m_InterfaceToJs->CPP_OnRequestContactData();
			}
		}
		break;
	case (int)DISPID_CB_RequestRfreshContactData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				m_InterfaceToJs->CPP_OnRequestRfreshContactData();
			}
		}
		break;
	case (int)DISPID_CB_RequestAddContactData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString	strContact	= pDispParams->rgvarg[0].bstrVal;
				m_InterfaceToJs->CPP_OnRequestAddContactData(strContact);
			}
		}
		break;
	case (int)DISPID_CB_RequestAddContactFile:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString	strFile	= pDispParams->rgvarg[0].bstrVal;
				m_InterfaceToJs->CPP_OnRequestAddContactFile(strFile);
			}
		}
		break;
	case (int)DISPID_CB_RequestDeleteContactData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString	ContactId	= pDispParams->rgvarg[0].bstrVal;
				m_InterfaceToJs->CPP_OnRequestDeleteContactData(ContactId);
			}
		}
		break;
	case (int)DISPID_CB_RequestBackUpContactData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString	ContactId	= pDispParams->rgvarg[0].bstrVal;
				m_InterfaceToJs->CPP_OnRequestBackUpContactData(ContactId);
			}
		}
		break;
	case (int)DISPID_CB_RequestGroupData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				m_InterfaceToJs->CPP_OnRequestGroupData();
			}
		}
		break;
	case (int)DISPID_CB_RequestEditContactData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString	ContactData	= pDispParams->rgvarg[0].bstrVal;
				m_InterfaceToJs->CPP_OnRequestEditContactData(ContactData);
			}
		}
		break;
	case (int)DISPID_CB_RequestAddGroupData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString StrAddGruop = pDispParams->rgvarg[0].bstrVal; 
				m_InterfaceToJs->CPP_OnRequestAddGroupData(StrAddGruop);
			}
		}
		break;
	case (int)DISPID_CB_RequestDeleteGroupData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString DelGruop = pDispParams->rgvarg[0].bstrVal;
				m_InterfaceToJs->CPP_OnRequestDeleteGroupData(DelGruop);
			}
		}
		break;
	case (int)DISPID_CB_RequestEditGroupData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString EditGruop = pDispParams->rgvarg[0].bstrVal;
				m_InterfaceToJs->CPP_OnRequestEditGroupData(EditGruop);
			}
		}
		break;
		/***********************************���Ų���**************************************************/
	case (int)DISPID_CB_RequestSmsData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				m_InterfaceToJs->CPP_OnRequestSmsData();
			}
		}
		break;
	case (int)DISPID_CB_RequestDeleteSmsData:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString	SmsId	= pDispParams->rgvarg[0].bstrVal;
				m_InterfaceToJs->CPP_OnRequestDeleteSmsData(SmsId);
			}
		}
		break;
	case (int)DISPID_CB_RequestSendSms:
		{
			DisProperty(wFlags, pVarResult);
			if(wFlags & DISPATCH_METHOD)
			{
				CString	SmsInfo	= pDispParams->rgvarg[0].bstrVal;
				m_InterfaceToJs->CPP_OnRequestSendSms(SmsInfo);
			}
		}
		break;
		/***********************************�ļ��������**********************************************/
	}
	return S_OK;
}