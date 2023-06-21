#pragma once
#include "sdk_util.h"
#include "sdk_demo_app_common.h"

class ISDKInMeetingServiceCustomUIEvent
{
public:
	virtual void SetSDKMeetingService(ZOOM_SDK_NAMESPACE::IMeetingService* meeting_service_) = 0;
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0) = 0;
//	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) = 0;
//	virtual void onRecording2MP4Processing(int iPercentage) = 0;
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;
	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId) = 0;
	virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId) = 0;
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper) = 0;
	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) = 0;
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status) = 0;
	virtual void onCustomizedAnnotationObjDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* obj_) = 0;
	virtual void onSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_) = 0;
	virtual void onUserNamesChanged(ZOOM_SDK_NAMESPACE::IList<unsigned int>* pList) = 0;
	virtual void onWebinarNeedRegisterNotification(ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandler* handler_) = 0;
	//-------Add more interfaces here if you want the customized UI to handle it ---------------//
	/*
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status) = 0;

	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc) = 0;
	virtual void onHostChangeNotification(unsigned int userId) = 0;
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;
	virtual void onGetAudioAndVideoSettingFlags(const wchar_t* audioFlag, const wchar_t* videoFlag) = 0;

	//for ITestAudioDeviceHelperEvent and ITestVideoDeviceHelperEvent
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume) = 0;
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk)  = 0; 
	virtual void OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status, bool& bHandled)  = 0;
	virtual void OnSelectedAudioDeviceIsChanged()  = 0;

	virtual void OnNoVideoDeviceIsUseful()  = 0; 
	virtual void OnSelectedVideoDeviceIsChanged()  = 0;
	virtual void OnNoWindowToShowPreview() = 0;
	*/
};

class CSDKCustomUIWorkFlow : public ISDKInMeetingServiceMgrEvent
{
public:
	CSDKCustomUIWorkFlow();
	void Init(ISDKInMeetingServiceCustomUIEvent* pEvent_);
	virtual ~CSDKCustomUIWorkFlow();
	ZOOM_SDK_NAMESPACE::IMeetingService* GetSDKObj() { return m_pMeetingService; }
	
public:
	//more In Meeting features goes here
	ZOOM_SDK_NAMESPACE::IUserInfo* GetUserByUserID(unsigned int userid);
	bool IsMeetingServiceReady();
	void GetServiceControls();
	void Uninit();
	void InitMeetingService();
	bool IsVideoOn();
	bool IsAudioOn();
	unsigned __int64 GetMeetingID();
public:
	//IMeetingServiceEvent
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type){}
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) {}
	virtual void onSuspendParticipantsActivities() {}

	//IMeetingRemoteCtrlEvent
	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId);
	virtual void OnAcceptRemoteControlDisclaimer() {}

	//IMeetingParticipantsCtrlEvent
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);
	
	virtual void onHostChangeNotification(unsigned int userId) {}
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) {}
	virtual void onUserNamesChanged(ZOOM_SDK_NAMESPACE::IList<unsigned int>* pList);
	virtual void onCoHostChangeNotification(unsigned int userId, bool isCoHost){}
	virtual void onInvalidReclaimHostkey() {}
	virtual void onLocalRecordingStatusChanged(unsigned int user_id, ZOOM_SDK_NAMESPACE::RecordingStatus status) {}
	virtual void onAllowParticipantsRenameNotification(bool bAllow) {}
	virtual void onAllowParticipantsUnmuteSelfNotification(bool bAllow) {}
	virtual void onAllowParticipantsStartVideoNotification(bool bAllow) {}
	virtual void onAllowParticipantsShareWhiteBoardNotification(bool bAllow) {}
	virtual void onLocalVideoOrderUpdated(ZOOM_SDK_NAMESPACE::IList<unsigned int >* localOrderList) {}
	virtual void onAllHandsLowered() {}
	virtual void onRequestLocalRecordingPriviligeChanged(ZOOM_SDK_NAMESPACE::LocalRecordingRequestPrivilegeStatus status) {}

	//IMeetingRecordingCtrlEvent
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) {}
	virtual void onRecording2MP4Processing(int iPercentage) {}
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status) {}
	virtual void onRecordPriviligeChanged(bool bCanRec) {}
	virtual void onCloudRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status) {}
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper);
	virtual void onLocalRecordingPrivilegeRequestStatus(ZOOM_SDK_NAMESPACE::RequestLocalRecordingStatus status) {}
	virtual void onLocalRecordingPrivilegeRequested(ZOOM_SDK_NAMESPACE::IRequestLocalRecordingPrivilegeHandler* handler) {}

	//IMeetingVideoCtrlEvent
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status);
	virtual void onSpotlightedUserListChangeNotification(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstSpotlightedUserID) {}
	virtual void onHostRequestStartVideo(ZOOM_SDK_NAMESPACE::IRequestStartVideoHandler* handler_) {}
	virtual void onActiveSpeakerVideoUserChanged(unsigned int userid){}
	virtual void onActiveVideoUserChanged(unsigned int userid) {}
	virtual void onHostVideoOrderUpdated(ZOOM_SDK_NAMESPACE::IList<unsigned int >* orderList) {}
	virtual void onFollowHostVideoOrderChanged(bool bFollow) {}
	virtual void onUserVideoQualityChanged(ZOOM_SDK_NAMESPACE::VideoConnectionQuality quality, unsigned int userid) {}

	//IMeetingAudioCtrlEvent
	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL);
	virtual void onUserActiveAudioChange(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstActiveAudioUser) {}
	virtual void onHostRequestStartAudio(ZOOM_SDK_NAMESPACE::IRequestStartAudioHandler* handler_) {}

	//IMeetingChatCtrlEvent
	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc) {}
	virtual void onChatStautsChangedNotification(ZOOM_SDK_NAMESPACE::ChatStatus* status_) {} 
	virtual void onChatMsgDeleteNotification(const wchar_t* msgID, ZOOM_SDK_NAMESPACE::SDKChatMessageDeleteType deleteBy) {}
	virtual void onShareMeetingChatStatusChanged(bool isStart) {}

	
	//IMeetingShareCtrlEvent
	virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId);
	virtual void onLockShareStatus(bool bLocked) {}
	virtual void onShareContentNotification(ZOOM_SDK_NAMESPACE::ShareInfo& shareInfo) {}
	virtual void onMultiShareSwitchToSingleShareNeedConfirm(ZOOM_SDK_NAMESPACE::IShareSwitchMultiToSingleConfirmHandler* handler_) {}
	virtual void onShareSettingTypeChangedNotification(ZOOM_SDK_NAMESPACE::ShareSettingType type) {}

	//IMeetingUIControllerEvent
	virtual void onInviteBtnClicked(bool& bHandled) {}
	virtual void onStartShareBtnClicked() {}
	virtual void onEndMeetingBtnClicked() {}
	virtual void onParticipantListBtnClicked() {}
	virtual void onCustomLiveStreamMenuClicked() {}
	virtual void onZoomInviteDialogFailed() {}
	virtual void onCCBTNClicked() {}
	virtual void onAudioBtnClicked(ZOOM_SDK_NAMESPACE::AudioBtnClickedCallbackInfo info) {}
	virtual void onAudioMenuBtnClicked() {}
	virtual void onBreakoutRoomBtnClicked() {}

	//ITestAudioDeviceHelperEvent
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume)  {}
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk)  {}
	virtual void OnTestMicStatusChanged(ZOOM_SDK_NAMESPACE::SDK_TESTMIC_STATUS status, bool& bHandled)  {}
	virtual void OnSelectedAudioDeviceIsChanged()  {}

	//ITestVideoDeviceHelperEvent
	virtual void OnNoVideoDeviceIsUseful()  {}
	virtual void OnSelectedVideoDeviceIsChanged()  {}
	virtual void OnNoWindowToShowPreview() {}
	
	//IClosedCaptionControllerEvent
	virtual void onAssignedToSendCC(bool bAssigned) {}
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, unsigned int sender_id, time_t time) {}
	virtual void onLiveTranscriptionStatus(ZOOM_SDK_NAMESPACE::SDKLiveTranscriptionStatus status) {}
	virtual void onLiveTranscriptionMsgReceived(const wchar_t* ltMsg, unsigned int speaker_id, ZOOM_SDK_NAMESPACE::SDKLiveTranscriptionOperationType type) {}
	virtual void onLiveTranscriptionMsgError(ZOOM_SDK_NAMESPACE::ILiveTranscriptionLanguage* spokenLanguage, ZOOM_SDK_NAMESPACE::ILiveTranscriptionLanguage* transcriptLanguage) {}
	virtual void onRequestForLiveTranscriptReceived(unsigned int requester_id, bool bAnonymous) {}
	virtual void onRequestLiveTranscriptionStatusChange(bool bEnabled) {}
	virtual void onCaptionStatusChanged(bool bEnabled) {};

	//ICustomizedAnnotationControllerEvent
	virtual void onCustomizedAnnotationObjDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* obj_);
	virtual void onSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_);

	//IMeetingConfigurationEvent
	virtual void onInputMeetingPasswordAndScreenNameNotification(ZOOM_SDK_NAMESPACE::IMeetingPasswordAndScreenNameHandler* pHandler){}
	virtual void onWebinarNeedRegisterNotification(ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandler* handler_);
	virtual void onEndOtherMeetingToJoinMeetingNotification(ZOOM_SDK_NAMESPACE::IEndOtherMeetingToJoinMeetingHandler* handler_){}
	virtual void onFreeMeetingRemainTime(unsigned int leftTime) {}
	virtual void onFreeMeetingRemainTimeStopCountDown() {}
	virtual void onFreeMeetingNeedToUpgrade(FreeMeetingNeedUpgradeType type_, const wchar_t* gift_url) {}
	virtual void onFreeMeetingUpgradeToGiftFreeTrialStart() {}
	virtual void onFreeMeetingUpgradeToGiftFreeTrialStop() {}
	virtual void onFreeMeetingUpgradeToProMeeting() {}

private:
	ISDKInMeetingServiceCustomUIEvent* m_pCustomUIEvent;
	ZOOM_SDK_NAMESPACE::IMeetingService* m_pMeetingService;
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	std::wstring m_strCamera;
	bool m_bInited;
	ZOOM_SDK_NAMESPACE::IMeetingAudioController* m_pAudioCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingChatController* m_pChatCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* m_pUserCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingRecordingController* m_pRecCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingRemoteController* m_pRemoteCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingShareController* m_pShareCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingVideoController* m_pVideoCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingUIController* m_pMeetingUICtrl;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* m_pCustomAnnoCtrl;
	ZOOM_SDK_NAMESPACE::IMeetingConfiguration* m_pMeetingConfiguration;

	//ZOOM_SDK_NAMESPACE::ITestAudioDeviceHelper* m_pAudioDeviceHelper;
	//ZOOM_SDK_NAMESPACE::ITestVideoDeviceHelper* m_pVideoDeviceHelper;

	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* _anno_obj;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* _sending_sharing_anno_obj;
	
};
