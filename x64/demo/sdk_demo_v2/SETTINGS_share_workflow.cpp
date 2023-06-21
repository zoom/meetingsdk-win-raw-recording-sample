#include "stdafx.h"
#include "SETTINGS_share_workflow.h"

CSDKShareSettingsWorkFlow::CSDKShareSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pShareSettingContext = NULL;
	Init();
}

CSDKShareSettingsWorkFlow::~CSDKShareSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pShareSettingContext = NULL;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::Init()
{
	if (NULL == m_pSettingService)
	{
		m_pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
	}
	if (m_pSettingService)
	{
		m_pShareSettingContext = m_pSettingService->GetShareSettings();
	}
	if (NULL == m_pShareSettingContext)
	{
		return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::EnableTCPConnectionWhenSharing(bool bEnable)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->EnableTCPConnectionWhenSharing(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::EnableShowMyAppWindowWhenShare(bool bEnable)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->EnableShowMyAppWindowWhenShare(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::EnableRemoteControlAllApplications(bool bEnable)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->EnableRemoteControlAllApplications(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::EnableGreenBorderWhenShare(bool bEnable)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->EnableGreenBorderWhenShare(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::EnableLimitFPSWhenShare(bool bEnable)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->EnableLimitFPSWhenShare(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::EnableAccelerateGPUWhenShare(bool bEnable)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->EnableAccelerateGPUWhenShare(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

bool CSDKShareSettingsWorkFlow::IsAccelerateGPUWhenShareEnabled()
{
	if (m_pShareSettingContext)
	{
		bool bChecked(false);
		m_pShareSettingContext->IsAccelerateGPUWhenShareEnabled(bChecked);
		return bChecked;
	}
	return false;
}

bool CSDKShareSettingsWorkFlow::IsCurrentOSSupportAccelerateGPUWhenShare()
{
	if (m_pShareSettingContext)
	{
		bool bChecked = m_pShareSettingContext->IsCurrentOSSupportAccelerateGPUWhenShare();
		return bChecked;
	}
	return false;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::SetLimitFPSValueWhenShare(ZOOM_SDK_NAMESPACE::LimitFPSValue limitValue)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->SetLimitFPSValueWhenShare(limitValue);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::LimitFPSValue CSDKShareSettingsWorkFlow::GetLimitFPSValueWhenShare()
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::LimitFPSValue value = m_pShareSettingContext->GetLimitFPSValueWhenShare();
		return value;
	}
	return ZOOM_SDK_NAMESPACE::limitfps_Not_Enable;
}

bool CSDKShareSettingsWorkFlow::IsTCPConnectionWhenSharing()
{
	if (m_pShareSettingContext)
	{
		bool bChecked = m_pShareSettingContext->IsTCPConnectionWhenSharing();
		return bChecked;
	}
	return false;
}

bool CSDKShareSettingsWorkFlow::IsShowMyAppWindowWhenShareEnabled()
{
	if (m_pShareSettingContext)
	{
		bool bChecked = m_pShareSettingContext->IsShowMyAppWindowWhenShareEnabled();
		return bChecked;
	}
	return false;
}

bool CSDKShareSettingsWorkFlow::IsSupportShowMyAppWindowWhenShare()
{
	if (m_pShareSettingContext)
	{
		return m_pShareSettingContext->IsSupportShowMyAppWindowWhenShare();
	}
	return false;
}

bool CSDKShareSettingsWorkFlow::IsRemoteControlAllApplicationsEnabled()
{
	if (m_pShareSettingContext)
	{
		bool bChecked = m_pShareSettingContext->IsRemoteControlAllApplicationsEnabled();
		return bChecked;
	}
	return false;
}

bool CSDKShareSettingsWorkFlow::IsGreenBorderEnabledWhenShare()
{
	if (m_pShareSettingContext)
	{
		bool bChecked = m_pShareSettingContext->IsGreenBorderEnabledWhenShare();
		return bChecked;
	}
	return false;
}

bool CSDKShareSettingsWorkFlow::IsLimitFPSEnabledWhenShare()
{
	if (m_pShareSettingContext)
	{
		bool bChecked = m_pShareSettingContext->IsLimitFPSEnabledWhenShare();
		return bChecked;
	}
	return false;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::SetWindowSizeTypeWhenViewShare(ZOOM_SDK_NAMESPACE::WindowSizeType eType)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->SetWindowSizeTypeWhenViewShare(eType);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::WindowSizeType CSDKShareSettingsWorkFlow::GetWindowSizeTypeWhenViewShare()
{
	ZOOM_SDK_NAMESPACE::WindowSizeType eWindowSizeType = ZOOM_SDK_NAMESPACE::WindowSize_FullScreen;

	if (m_pShareSettingContext)
	{
		eWindowSizeType = m_pShareSettingContext->GetWindowSizeTypeWhenViewShare();
	}
	return eWindowSizeType;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::SetScreenCaptureMode(ZOOM_SDK_NAMESPACE::ScreenCaptureMode eMode)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->SetScreenCaptureMode(eMode);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::GetScreenCaptureMode(ZOOM_SDK_NAMESPACE::ScreenCaptureMode& capture_mode)
{
	ZOOM_SDK_NAMESPACE::ScreenCaptureMode eScreenCaptureMode = ZOOM_SDK_NAMESPACE::CaptureMode_end;

	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = m_pShareSettingContext->GetScreenCaptureMode(capture_mode);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::EnableAnnotateHardwareAcceleration(bool bEnable)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->EnableHardwareAcceleratedAnnotation(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

bool CSDKShareSettingsWorkFlow::IsAnnotateHardwareAccelerationEnabled()
{
	if (m_pShareSettingContext)
	{
		bool bChecked(false);
		m_pShareSettingContext->IsAnnotationHardwareAccelerated(bChecked);
		return bChecked;
	}
	return false;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKShareSettingsWorkFlow::EnableAccelerateGPUWhenVideoShare(bool bEnable)
{
	if (m_pShareSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pShareSettingContext->EnableHardwareAcceleratedVideoSharing(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

bool CSDKShareSettingsWorkFlow::IsAccelerateGPUWhenVideoShareEnabled()
{
	if (m_pShareSettingContext)
	{
		bool bChecked(false);
		m_pShareSettingContext->IsVideoSharingHardwareAccelerated(bChecked);
		return bChecked;
	}
	return false;
}


