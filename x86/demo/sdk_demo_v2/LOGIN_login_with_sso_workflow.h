#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "sdk_demo_app_common.h"
/////////////////////////
class CSDKLoginFlowUIEvent;
class CSDKLoginWithSSOFlow 
{
public:
	CSDKLoginWithSSOFlow();
	virtual ~CSDKLoginWithSSOFlow();

	const wchar_t* GetSSOUrl(std::wstring prefix_of_vanity_url);
	ZOOM_SDK_NAMESPACE::SDKError Login(const wchar_t* sso_uri_protocol);
	ZOOM_SDK_NAMESPACE::SDKError LogOut();
	void Cleanup(){}

protected:
	ZOOM_SDK_NAMESPACE::IAuthService* m_pAuthService;
};