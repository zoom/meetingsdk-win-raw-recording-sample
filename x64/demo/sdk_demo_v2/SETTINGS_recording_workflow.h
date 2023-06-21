#pragma once
#include "sdk_util.h"
#include "stdafx.h"
#include "setting_service_interface.h"

class CSDKRecordingSettingsWorkFlow
{
public:
	CSDKRecordingSettingsWorkFlow();
	virtual ~CSDKRecordingSettingsWorkFlow();
	ZOOM_SDK_NAMESPACE::SDKError Init();
	void Cleanup(){}
	ZOOM_SDK_NAMESPACE::SDKError SetRecordingPath(const wchar_t* szPath);
	const wchar_t* GetRecordingPath();
	
	const wchar_t* GetRecordingManagementURL();
	ZOOM_SDK_NAMESPACE::SDKError CanGetRecordingManagementURL(bool& bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableSelectRecordFileLocationAfterMeeting(bool bEnable);
	bool IsSelectRecordFileLocationAfterMeetingEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnableMultiAudioStreamRecord(bool bEnable);
	bool IsMultiAudioStreamRecordEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnableAddTimestampWatermark(bool bEnable);
	bool IsAddTimestampWatermarkEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnableOptimizeFor3rdPartyVideoEditor(bool bEnable);
	bool IsOptimizeFor3rdPartyVideoEditorEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnableShowVideoThumbnailWhenShare(bool bEnable);
	bool IsShowVideoThumbnailWhenShareEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnablePlaceVideoNextToShareInRecord(bool bEnable);
	bool IsPlaceVideoNextToShareInRecordEnabled();
	
private:
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IRecordingSettingContext* m_pRecordingSettingContext;
};