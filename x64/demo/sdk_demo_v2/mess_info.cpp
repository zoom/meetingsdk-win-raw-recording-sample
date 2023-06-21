#include "stdafx.h"
#include "mess_info.h"

CSDKMessInfo::CSDKMessInfo()
{
	m_pErrorDescription = NULL;
	m_pErrorMessInfo = NULL;
	Init();
}
CSDKMessInfo::~CSDKMessInfo()
{
	Cleanup();
	m_pErrorDescription = NULL;
	m_pErrorMessInfo = NULL;
}
bool CSDKMessInfo::Init()
{
	if (m_pErrorMessInfo == NULL)
	{
		m_pErrorMessInfo = new wchar_t[1024];
	}
	if (m_pErrorMessInfo)
	{
		return true;
	} 
	else
	{
		return false;
	}	
}
void CSDKMessInfo::Cleanup()
{
	if (m_pErrorMessInfo)
	{
		delete m_pErrorMessInfo;
		m_pErrorMessInfo = NULL;
	}
}
CSDKMessInfo& CSDKMessInfo::GetInst()
{
	static CSDKMessInfo s_inst;
	return s_inst;
}
const wchar_t* CSDKMessInfo::GetErrorDescription()
{
	const ZOOM_SDK_NAMESPACE::IZoomLastError* pZoomLastError = SDKInterfaceWrap::GetInst().GetLastError();
	if (pZoomLastError == NULL)
	{
		return nullptr;
	}

	m_pErrorDescription = pZoomLastError->GetErrorDescription();

	return m_pErrorDescription;	
}
int CSDKMessInfo::GetErrorCode()
{
	const ZOOM_SDK_NAMESPACE::IZoomLastError* pZoomLastError = SDKInterfaceWrap::GetInst().GetLastError();
	if (pZoomLastError == NULL)
	{
		return -1;
	}

	m_nErrorCode = pZoomLastError->GetErrorCode();

	return m_nErrorCode;	
}
const wchar_t* CSDKMessInfo::GetErrorType()
{
	const ZOOM_SDK_NAMESPACE::IZoomLastError* pZoomLastError = SDKInterfaceWrap::GetInst().GetLastError();
	if (pZoomLastError == NULL)
	{
		return nullptr;
	}

	ZOOM_SDK_NAMESPACE::LastErrorType errorType = pZoomLastError->GetErrorType();
	switch (errorType)
	{
	case ZOOM_SDK_NAMESPACE::LastErrorType_Auth:
	{
		m_sErrorType = _T("LastErrorType_Auth");
	}
	break;
	case ZOOM_SDK_NAMESPACE::LastErrorType_Login:
	{
		m_sErrorType = _T("LastErrorType_Login");
	}
	break;
	case ZOOM_SDK_NAMESPACE::LastErrorType_Meeting:
	{
		m_sErrorType = _T("LastErrorType_Meeting");
	}
	break;
	case ZOOM_SDK_NAMESPACE::LastErrorType_System:
	{
		m_sErrorType = _T("LastErrorType_System");
	}
	break;
	default:
		break;

	}

	return m_sErrorType.c_str();
}
wchar_t* CSDKMessInfo::GetErrorMessInfo()
{
	if (m_pErrorMessInfo == nullptr)
		return _T("");

	const ZOOM_SDK_NAMESPACE::IZoomLastError* pZoomLastError = SDKInterfaceWrap::GetInst().GetLastError();

	if (pZoomLastError)
	{
		swprintf_s(m_pErrorMessInfo,1024, L"Error Type: %s\nError Code: %d\nError Description: %s", GetErrorType(), GetErrorCode(), GetErrorDescription());
	}
	else
	{
		swprintf_s(m_pErrorMessInfo, 1024, L"There is an unknown error.");
	}
	return m_pErrorMessInfo;
}