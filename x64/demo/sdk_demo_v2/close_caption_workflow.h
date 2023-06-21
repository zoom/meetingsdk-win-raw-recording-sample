#pragma once

#include "sdk_util.h"

class IClosedCaptionWorkflowEvent
{
public:
	virtual void onAssignedToSendCC(bool bAssigned) = 0;
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, unsigned int sender_id, time_t time) = 0;

};
class CCloseCaptionWorkflow:public ZOOM_SDK_NAMESPACE::IClosedCaptionControllerEvent
{
public:
	CCloseCaptionWorkflow();
	virtual ~CCloseCaptionWorkflow();
	void SetEvent(IClosedCaptionWorkflowEvent* _event);

public:
	void Init();
	bool CanIAssignOthersToSendCC();//Query if it is able to assign others to send CC
	ZOOM_SDK_NAMESPACE::SDKError AssignCCPriviledge(unsigned int userid, bool bAssigned);//assign someone to send cc.
	bool CanBeAssignedToSendCC(unsigned int userid);//Query whether someone is assigned to send cc or not.
	bool CanSendClosedCaption();//Query if current user can send Close Caption.
	ZOOM_SDK_NAMESPACE::SDKError SendClosedCaption(const wchar_t* ccMsg);//send cc.
	const wchar_t* GetClosedCaptionUrlFor3rdParty();
	ZOOM_SDK_NAMESPACE::SDKError SaveCCHistory();
	const wchar_t* GetClosedCaptionSavePath();


public:
	virtual void onAssignedToSendCC(bool bAssigned);
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, unsigned int sender_id, time_t time);
	virtual void onLiveTranscriptionStatus(ZOOM_SDK_NAMESPACE::SDKLiveTranscriptionStatus status) {};
	virtual void onLiveTranscriptionMsgReceived(const wchar_t* ltMsg, unsigned int speaker_id, ZOOM_SDK_NAMESPACE::SDKLiveTranscriptionOperationType type) {};
	virtual void onLiveTranscriptionMsgError(ZOOM_SDK_NAMESPACE::ILiveTranscriptionLanguage* spokenLanguage, ZOOM_SDK_NAMESPACE::ILiveTranscriptionLanguage* transcriptLanguage) {};
	virtual void onRequestForLiveTranscriptReceived(unsigned int requester_id, bool bAnonymous) {};
	virtual void onRequestLiveTranscriptionStatusChange(bool bEnabled) {}	
	virtual void onCaptionStatusChanged(bool bEnabled) {};
protected:
	ZOOM_SDK_NAMESPACE::IClosedCaptionController* m_close_caption_ctrl;

	IClosedCaptionWorkflowEvent* m_close_caption_workflow_event;
	bool m_bSupportCC;
};