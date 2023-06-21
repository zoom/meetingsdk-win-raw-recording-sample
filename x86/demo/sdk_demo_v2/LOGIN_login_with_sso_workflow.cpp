#include "stdafx.h"
#include "LOGIN_login_with_sso_workflow.h"

CSDKLoginWithSSOFlow::CSDKLoginWithSSOFlow()
{
	m_pAuthService = NULL;

}
CSDKLoginWithSSOFlow::~CSDKLoginWithSSOFlow()
{
	m_pAuthService = NULL;
}

const wchar_t* CSDKLoginWithSSOFlow::GetSSOUrl(std::wstring prefix_of_vanity_url)
{
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
	}
	if (m_pAuthService)
	{
		return m_pAuthService->GenerateSSOLoginWebURL(prefix_of_vanity_url.c_str());
	}
	return NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKLoginWithSSOFlow::Login(const wchar_t* sso_uri_protocol)
{
	if (NULL == m_pAuthService)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
	}
	if (m_pAuthService)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pAuthService->SSOLoginWithWebUriProtocol(sso_uri_protocol);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKLoginWithSSOFlow::LogOut()
{
	ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
	if (m_pAuthService == NULL)
	{
		m_pAuthService = SDKInterfaceWrap::GetInst().GetAuthService();
	}
	if (m_pAuthService)
	{
		err = m_pAuthService->LogOut();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}