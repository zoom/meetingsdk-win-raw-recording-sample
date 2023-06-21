#pragma once
#include "sdk_util.h"
#include "stdafx.h"
#include "setting_service_interface.h"

class CSDKShareSettingsWorkFlow
{
public:
	CSDKShareSettingsWorkFlow();
	virtual ~CSDKShareSettingsWorkFlow();
	ZOOM_SDK_NAMESPACE::SDKError Init();
	void Cleanup() {}
	ZOOM_SDK_NAMESPACE::SDKError EnableTCPConnectionWhenSharing(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableShowMyAppWindowWhenShare(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableRemoteControlAllApplications(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableGreenBorderWhenShare(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableLimitFPSWhenShare(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableAccelerateGPUWhenShare(bool bEnable);
	bool IsTCPConnectionWhenSharing();
	bool IsShowMyAppWindowWhenShareEnabled();
	bool IsSupportShowMyAppWindowWhenShare();
	bool IsRemoteControlAllApplicationsEnabled();
	bool IsGreenBorderEnabledWhenShare();
	bool IsLimitFPSEnabledWhenShare();
	bool IsAccelerateGPUWhenShareEnabled();
	bool IsCurrentOSSupportAccelerateGPUWhenShare();
	ZOOM_SDK_NAMESPACE::SDKError SetWindowSizeTypeWhenViewShare(ZOOM_SDK_NAMESPACE::WindowSizeType eType);
	ZOOM_SDK_NAMESPACE::WindowSizeType GetWindowSizeTypeWhenViewShare();
	ZOOM_SDK_NAMESPACE::SDKError SetLimitFPSValueWhenShare(ZOOM_SDK_NAMESPACE::LimitFPSValue limitValue);
	ZOOM_SDK_NAMESPACE::LimitFPSValue GetLimitFPSValueWhenShare();
	ZOOM_SDK_NAMESPACE::SDKError SetScreenCaptureMode(ZOOM_SDK_NAMESPACE::ScreenCaptureMode eMode);
	ZOOM_SDK_NAMESPACE::SDKError GetScreenCaptureMode(ZOOM_SDK_NAMESPACE::ScreenCaptureMode& capture_mode);
	ZOOM_SDK_NAMESPACE::SDKError EnableAnnotateHardwareAcceleration(bool bEnable);
	bool IsAnnotateHardwareAccelerationEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnableAccelerateGPUWhenVideoShare(bool bEnable);
	bool IsAccelerateGPUWhenVideoShareEnabled();

private:
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IShareSettingContext* m_pShareSettingContext;
};