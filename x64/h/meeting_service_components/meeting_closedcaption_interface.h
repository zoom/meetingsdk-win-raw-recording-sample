/*!
* \file meeting_claosecaptioin_interface.h
* \brief Meeting Service Closed Caption Interface.
* \remarks Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_CLOSEDCAPTION_INTERFACE_H_
#define _MEETING_CLOSEDCAPTION_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/**
 * @brief Enumerations of the type for live transcription status.
 */
	typedef enum
{
	SDK_LiveTranscription_Status_Stop = 0,   //not start
	SDK_LiveTranscription_Status_Start = 1,  //start
	SDK_LiveTranscription_Status_User_Sub = 2,  //user sub
	SDK_LiveTranscription_Status_Connecting = 10,	 //connecting
}SDKLiveTranscriptionStatus;

/**
 * @brief Enumerations of the type for live transcription operation type.
 */
typedef enum
{
	SDK_LiveTranscription_OperationType_None = 0,
	SDK_LiveTranscription_OperationType_Add,
	SDK_LiveTranscription_OperationType_Update,
	SDK_LiveTranscription_OperationType_Delete,
	SDK_LiveTranscription_OperationType_Complete,
	SDK_LiveTranscription_OperationType_NotSupported,
	SDK_LiveTranscription_OperationType_NoTranslation,
}SDKLiveTranscriptionOperationType;

/// \brief live transcription language interface.
///
class ILiveTranscriptionLanguage
{
public:
	virtual int GetLTTLanguageID() = 0;
	virtual const wchar_t* GetLTTLanguageName() = 0;
	virtual ~ILiveTranscriptionLanguage() {};
};

/// \brief Closed Caption controller callback event.
///
class IClosedCaptionControllerEvent
{
public:
	virtual ~IClosedCaptionControllerEvent() {}

	/// \brief Callback event when the user is assigned to send Closed Caption messages.
	virtual void onAssignedToSendCC(bool bAssigned) = 0;

	/// \brief Callback event when the user receives Closed Caption messages.
	/// \If the meeting supports multi-language transcription and the host sets manual captions to true,
	/// \attendees must set the translation language id to -1 to receive closed captioned messages.
	/// \param ccMsg: an object pointer to the closed caption message content. 
	/// \param sender_id: the sender id of a closed caption message. 
	/// \param time: the time when a caption message was sent.
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, unsigned int sender_id, time_t time) = 0;

	/// \brief live transcription status changed callback.
	/// \param status: the live transcription status. For more details, see \link SDKLiveTranscriptionStatus \endlink.
	virtual void onLiveTranscriptionStatus(SDKLiveTranscriptionStatus status) = 0;

	/// \brief live transcription message received callback.
	/// \param ltMsg: an object pointer to the live transcription message content. 
	/// \param ltSpearkId: the speaker id of the live transcription message. 
	/// \param type: the live transcription operation type. For more details, see \link SDKLiveTranscriptionOperationType \endlink.
	virtual void onLiveTranscriptionMsgReceived(const wchar_t* ltMsg, unsigned int speaker_id, SDKLiveTranscriptionOperationType type) = 0;

	/// \brief The translation message error callback.
	/// \param speakingLanguage: an object of the spoken message language. 
	/// \param transcriptLanguageId: an object of the message language you want to translate.
	virtual void onLiveTranscriptionMsgError(ILiveTranscriptionLanguage* spokenLanguage, ILiveTranscriptionLanguage* transcriptLanguage) = 0;

	/// \brief only host can receive this callback.
	/// \param requester_id: the request user id, if param bAnonymous is true, the requester_id is 0, no meanings. 
	/// \param bAnonymous: specify the request whether user anonymous request.
	virtual void onRequestForLiveTranscriptReceived(unsigned int requester_id, bool bAnonymous) = 0;

	/// \brief request live transcription status changed callback.
	/// \param bEnabled Specify the request live transcription status is enable, true enable, false disabled.
	virtual void onRequestLiveTranscriptionStatusChange(bool bEnabled) = 0;

	/// \brief Sink the event of captions enabled status changed.
	/// \param bEnabled True means the host enables the captions, otherwise means the host disables the captions.
	virtual void onCaptionStatusChanged(bool bEnabled) = 0;
};

/// \brief Closed caption controller interface.
class IClosedCaptionController
{
public:
	/// Set the controller event of closed caption(CC).
	virtual SDKError SetEvent(IClosedCaptionControllerEvent* pEvent) = 0;

	/// Determine if the current meeting supports the CC feature.
	virtual bool IsMeetingSupportCC() = 0;

	/// Query if it is able to assign others to send CC.
	virtual bool CanAssignOthersToSendCC() = 0;

	/// Assign a user to send CC.
	/// Zero(0) means to assign the current user himself.
	virtual SDKError AssignCCPriviledge(unsigned int userid, bool bAssigned) = 0;

	/// Determine if the user can be assigned as a CC sender.
	virtual bool CanBeAssignedToSendCC(unsigned int userid) = 0;

	/// Query if the user can send CC.
	virtual bool CanSendClosedCaption() = 0;

	/// Send the CC message.
	virtual SDKError SendClosedCaption(const wchar_t* ccMsg) = 0;

	/// Determine if it is enabled to save CC.
	virtual bool IsSaveCCEnabled() = 0;

	/// History of saving CC.
	virtual SDKError SaveCCHistory() = 0;

	/// Get the path of saving CC.
	virtual const wchar_t* GetClosedCaptionHistorySavedPath() = 0;

	/// Get the CC URL used by the third party service.
	virtual const wchar_t* GetClosedCaptionUrlFor3rdParty() = 0;

	/// brief Enable or disable manual captions for the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	/// Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableMeetingManualCaption(bool bEnable) = 0;

	/// Determine whether manually added closed captions is enabled for the meeting.
	virtual bool IsMeetingManualCaptionEnabled() = 0;

	/// \brief Determine whether the legal notice for Live transcript is available.
	/// \return True indicates the legal notice for Live transcript is available. Otherwise False.
	virtual bool IsLiveTranscriptLegalNoticeAvailable() = 0;

	/// brief Enable or disable to receive original and translated content.If enable this feature,you need start live transcription.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	/// Otherwise the function fails and returns an error. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableReceiveSpokenLanguageContent(bool bEnable) = 0;

	/// \brief Query if the user can disable captions.
	/// \return True means that the host can disable captions.
	virtual bool CanDisableCaptions() = 0;

	/// \brief Enable or disable captions.
	/// \param bEnable True means that captions are enabled; false means that captions are disabled.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableCaptions(bool bEnable) = 0;

	/// \brief Query if the captions enabled.
	/// \return True means that captions are enabled.
	virtual bool IsCaptionsEnabled() = 0;

	/// \brief Determine whether receive original and translated is available.
	/// \return True indicates receive original and translated is available. Otherwise False.
	virtual bool IsReceiveSpokenLanguageContentEnabled() = 0;

	/// Get the CC legal notices prompt.
	virtual const wchar_t* getLiveTranscriptLegalNoticesPrompt() = 0;

	/// Get the CC legal notices explained.
	virtual const wchar_t* getLiveTranscriptLegalNoticesExplained() = 0;

	/// brief Determine whether the live transcription feature is enabled.
	virtual bool IsLiveTranscriptionFeatureEnabled() = 0;

	/// brief Determine whether the multi-language transcription feature is enabled.
	virtual bool IsMultiLanguageTranscriptionEnabled() = 0;

	/// brief Determine whether the translated captions feature is enabled.
	virtual bool IsTextLiveTranslationEnabled() = 0;

	/// \brief Get the current live transcription status.
	//  \return type: the current live transcription status type. For more details, see \link SDKLiveTranscriptionStatus \endlink.
	virtual SDKLiveTranscriptionStatus GetLiveTranscriptionStatus() = 0;

	/// Query if the user can start live transcription.
	virtual bool CanStartLiveTranscription() = 0;

	/// \brief Start live transcription.
	/// \If the meeting allows multi-language transcription,all users can start live transcription.Otherwise only the host can start it
	/// \return If the function succeeds, the return value is SDKErr_Success.
	/// Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartLiveTranscription() = 0;

	/// \brief Stop live transcription.
	/// \If the meeting allows multi-language transcription,all user can stop live transcription.Otherwise only the host can stop it
	/// \return If the function succeeds, the return value is SDKErr_Success.
	/// Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopLiveTranscription() = 0;

	/// \brief Enable or disable the ability for attendees to request live transcriptions.
	/// \If the meeting allows multi-language transcription,the return value is SDKERR_WRONG_USAGE
	/// \return If the function succeeds, the return value is SDKErr_Success.
	/// Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableRequestLiveTranscription(bool bEnable) = 0;

	/// \brief Determine whether the request to start live transcription is enabled.If the return value is true, it is enabled, if false, disabled.
	/// \If the meeting allows multi-language transcription, the return value is false
	virtual bool IsRequestToStartLiveTranscriptionEnalbed() = 0;

	/// \brief Request the host to start live transcription.
	/// \If the meeting allows multi-language transcription,the return value is SDKERR_WRONG_USAGE
	/// \param bRequestAnonymous: True indicates the user anonymous request.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	/// Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RequestToStartLiveTranscription(bool bRequestAnonymous) = 0;

	/// \brief Get the list of all available speaking languages in meeting.
	/// \return If the function succeeds, the return value is the list of the available spoken languages in a meeting.
	///Otherwise failed, the return value is NULL.	
	virtual IList<ILiveTranscriptionLanguage*>* GetAvailableMeetingSpokenLanguages() = 0;

	/// \brief Set the spoken language of the current user.
	/// \param languageID: The spoken language id.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetMeetingSpokenLanguage(int languageID) = 0;

	/// Get the spoken language of the current user.
	virtual ILiveTranscriptionLanguage* GetMeetingSpokenLanguage() = 0;

	/// \brief Get the list of all available translation languages in a meeting.
	/// \return If the function succeeds, the return value is the list of all available translation languages in a meeting.
	///Otherwise failed, the return value is NULL.
	virtual IList<ILiveTranscriptionLanguage*>* GetAvailableTranslationLanguages() = 0;

	/// \brief Set the translation language of the current user.	
	/// \param languageID: The translation language id.
	/// If the language id is set to -1, live translation will be disabled.You can receive closed captions if the host sets manual captions to true for the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetTranslationLanguage(int languageID) = 0;

	/// Get the translation language of the current user.
	virtual ILiveTranscriptionLanguage* GetTranslationLanguage() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif