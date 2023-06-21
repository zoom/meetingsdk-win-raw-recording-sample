#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "sdk_demo_app_common.h"
class CSDKJoinMeetingForLoginUserFlowUIEvent
{
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0) = 0;
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) = 0;
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) = 0;
	virtual void onSuspendParticipantsActivities() = 0;
};
class CSDKJoinMeetingForLoginUserFlow:public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent
{
public:
	CSDKJoinMeetingForLoginUserFlow();
	virtual ~CSDKJoinMeetingForLoginUserFlow();
	bool IsMeetingServiceReady();
	ZOOM_SDK_NAMESPACE::SDKError JoinMeeting(ZOOM_SDK_NAMESPACE::JoinParam& paramJoinMeeting);
	void Cleanup() {}
	void SetUIEvent(CSDKJoinMeetingForLoginUserFlowUIEvent* event_);

	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type);
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param);
	virtual void onSuspendParticipantsActivities();

private:
	CSDKJoinMeetingForLoginUserFlowUIEvent* m_pJoinMeetingForLoginUserFlowUIEvent;
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
};