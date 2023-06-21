/*!
* \file meeting_sign_interpretation_interface.h
* \brief Meeting Service Sign Interpretation Interface
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_SIGN_INTERPRETATION_INTERFACE_H_
#define _MEETING_SIGN_INTERPRETATION_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum SignInterpretationStatus
	\brief Status of sign interpretation.
	Here are more detailed structural descriptions.
*/
enum SignInterpretationStatus
{
	SignInterpretationStatus_Initial, ///<The initial status
	SignInterpretationStatus_Started, ///<sign interpretation stared.
	SignInterpretationStatus_Stopped,  ///<sign interpretation stopped.
};

/// \brief sign interpretation language interface.
///
class ISignInterpretationLanguageInfo
{
public:
	virtual ~ISignInterpretationLanguageInfo() {}
	virtual const wchar_t* GetSignLanguageID() = 0;
	virtual const wchar_t* GetSignLanguageName() = 0;
};

/// \brief sign interpreter interface.
///
class ISignInterpreter
{
public:
	virtual ~ISignInterpreter() {}
	virtual unsigned int GetUserID() = 0;
	virtual const wchar_t* GetSignLanguageID() = 0;
	virtual bool IsAvailable() = 0;
};

/// \brief Process after the sign interpreter receives the requirement from the host to allow to talk.
class IRequestSignInterpreterToTalkHandler
{
public:
	virtual ~IRequestSignInterpreterToTalkHandler() {};
	/// \brief Instance to ignore the requirement, return nothing and finally self-destroy.
	virtual SDKError Ignore() = 0;
	/// \brief Instance to accept the requirement, unmute the audio and finally self-destroy.
	virtual SDKError Accept() = 0;
	/// \brief Ignore the request to unmute the audio in the meeting and finally the instance self-destroys.
	virtual SDKError Cancel() = 0;
};

/// \brief Meeting sign interpretation callback event.
///
class IMeetingSignInterpretationControllerEvent
{
public:
	virtual ~IMeetingSignInterpretationControllerEvent() {}

	/// \brief Sign interpretation status change callback. This function is used to inform the user sign interpretation has been started or stopped, and all users in the meeting can get the event.
	/// \param status Specify current sign interpretation status.
	virtual void OnSignInterpretationStatusChanged(SignInterpretationStatus status) = 0;

	/// \brief Sign interpreter list changed callback. When an interpreter leave the meeting, preset interpreter joins the meeting, or the host adds or removes an interpreter, this will be triggered.
	virtual void OnSignInterpreterListChanged() = 0;

	/// \brief Available sign languages changed callback. When the available sign languages in a meeting change, all users in the meeting can get the event.
	/// \param pAvailableSignLanguageList Specify the available sign languages list. For more details, see \link ISignInterpretationLanguageInfo \endlink.
	virtual void OnAvailableSignLanguageListUpdated(IList<ISignInterpretationLanguageInfo*>* pAvailableSignLanguageList) = 0;

	/// \brief Interpreters role changed callback. when myself role changed(participant <-> interpreter), and only myself in meeting can get the event. 
	virtual void OnSignInterpreterRoleChanged() = 0;

	/// \brief Sign interpreter languages changed callback. when a sign interpreter's languages changed, and only the sign interpreter self can get the event.
	virtual void OnSignInterpreterLanguageChanged() = 0;

	/// \brief Callback event for the user talk privilege changed. When the interpreter role or host changed, host allows/disallows interpreter talk, this will be triggered. Only the sign interpreter can get the event.
	/// \param hasPrivilege Specify whether the user has talk privilege or not.
	virtual void OnTalkPrivilegeChanged(bool hasPrivilege) = 0;

	/// \brief Callback event of the requirement to unmute the audio.
	/// \param handler_ A pointer to the IRequestSignInterpreterToTalkHandler. For more details, see \link IRequestSignInterpreterToTalkHandler \endlink.
	virtual void OnRequestSignInterpreterToTalk(IRequestSignInterpreterToTalkHandler* handler) = 0;

	/// \brief Callback event for the host to disallow the sign interpreter to talk.
	/// this interface be marked as deprecated, then it will be instead by OnTalkPrivilegeChanged
	virtual void OnDisallowSignInterpreterToTalk() = 0;
};

/// \brief Meeting interpretation controller interface
///
class IMeetingSignInterpretationController
{
public:
	virtual ~IMeetingSignInterpretationController() {}

	//Common (for all)
	/// \brief Set the interpretation controller callback event handler.
	/// \param event A pointer to the IMeetingInterpretationControllerEvent that receives the interpretation event. . 
	virtual void SetEvent(IMeetingSignInterpretationControllerEvent* event) = 0;

	/// \brief Determine if sign interpretation feature is enabled in the meeting.
	virtual bool IsSignInterpretationEnabled() = 0;

	/// \brief Get sign interpretation status of current meeting.
	/// \return If the function succeeds, the return value is the sign interpretation status of current meeting.  
	///Otherwise failed. For more details, see \link SignInterpretationStatus \endlink enum.
	virtual SignInterpretationStatus GetSignInterpretationStatus() = 0;

	/// \brief Determine if myself is interpreter.
	virtual bool IsSignInterpreter() = 0;

	/// \brief Get the sign interpretation language object of specified sign language ID.
	/// \param signLanguageId Specify the sign language ID for which you want to get the information. 
	/// \return If the function succeeds, the return value is a pointer to the IInterpretationLanguage, Otherwise failed, the return value is NULL.
	virtual ISignInterpretationLanguageInfo* GetSignInterpretationLanguageInfoByID(const wchar_t* signLanguageId) = 0;

	/// \brief Get the available sign interpretation language list.
	/// \return If the function succeeds, the return value is a pointer to the IList<ISignInterpretationLanguageInfo*>, Otherwise failed, the return value is NULL.
	/// For more details, see \link ISignInterpretationLanguageInfo \endlink.
	virtual IList<ISignInterpretationLanguageInfo*>* GetAvailableSignLanguageInfoList() = 0;

	//Admin (only for host) 
	/// \brief Get all supported sign interpretation language list.
	/// \return If the function succeeds, the return value is a pointer to the IList<ISignInterpretationLanguageInfo*>, Otherwise failed, the return value is NULL.
	/// \For more details, see \link ISignInterpretationLanguageInfo \endlink.
	virtual IList<ISignInterpretationLanguageInfo*>* GetAllSupportedSignLanguageInfoList() = 0;

	/// \brief Get the sign interpreters list.
	/// \return If the function succeeds, the return value is a pointer to the IList<ISignInterpreter*>, Otherwise failed, the return value is NULL.
	virtual IList<ISignInterpreter*>* GetSignInterpreterList() = 0;

	/// \brief Add someone as a sign interpreter.
	/// \param userID Specify the user.
	/// \param signLanguageId Specify the sign language.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError AddSignInterpreter(unsigned int userID, const wchar_t* signLanguageId) = 0;

	/// \brief Remove someone from the list of sign interpreters.
	/// \param userID Specify the user.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RemoveSignInterpreter(unsigned int userID) = 0;

	/// \brief Modify the language of a sign interpreter.
	/// \param userID Specify the interpreter.
	/// \param signLanguageId Specify the new sign language.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ModifySignInterpreterLanguage(unsigned int userID, const wchar_t* signLanguageId) = 0;

	/// \brief Determine if I can start the sign interpretation in the meeting.
	/// \return If it can start the sign interpretation, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanStartSignInterpretation() = 0;

	/// \brief Start sign interpretation.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartSignInterpretation() = 0;

	/// \brief Stop sign interpretation.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopSignInterpretation() = 0;

	/// \brief Host allow sign language interpreter to talk.
	/// \param userID Specify the sign language interpreter.
	/// \param allowToTalk true indicates to allow to talk. Otherwise, false.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RequestSignLanuageInterpreterToTalk(unsigned int userID, bool allowToTalk) = 0;

	/// \brief Determine if the sign language interpreter be allowed to talk.
	/// \param [out] canTalk indicates if allow to talk.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanSignLanuageInterpreterTalk(unsigned int userID, bool& canTalk) = 0;

	//Interpreter (only for interpreter)
	/// \brief Get sign language id if myself is a sign interpreter.
	/// \return If the function succeeds, the return value is the current assigned sign language id. Otherwise returns an empty string of length ZERO(0)
	virtual const wchar_t* GetSignInterpreterAssignedLanID() = 0;

	//Listener (for non interpreter)
	/// \brief Join a sign language channel if myself is not a sign interpreter.
	/// \param signLanguageId Specify the sign language channel ID.
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for Zoom style user interface mode. 
	virtual SDKError JoinSignLanguageChannel(const wchar_t* signLanguageId) = 0;

	/// \brief Off sign language if myself is not a sign interpreter..
	/// \return If the function succeeds, the return value is SDKErr_Success. Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for Zoom style user interface mode. 
	virtual SDKError LeaveSignLanguageChannel() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif