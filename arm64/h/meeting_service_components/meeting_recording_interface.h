/*!
* \file meeting_recording_interface.h
* \brief Recording of Meeting Service Interface
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_Recording_INTERFACE_H_
#define _MEETING_Recording_INTERFACE_H_
#include "zoom_sdk_def.h"
#include <time.h>

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum RecordingStatus
    \brief Recording status.
    Here are more detailed structural descriptions.
*/
enum RecordingStatus
{
	Recording_Start,///Start recording on local computer or on cloud.
	Recording_Stop,///Stop recording on local computer or on cloud.
	Recording_DiskFull,///There is no space to store for both local and cloud recording.
	Recording_Pause,///Pause recording on local or on cloud.
	Recording_Connecting,///Connecting, only for cloud recording.
};

/*! \enum RequestLocalRecordingStatus
	\brief Request local recording privilege status.
	Here are more detailed structural descriptions.
*/
enum RequestLocalRecordingStatus
{
	RequestLocalRecording_Granted,///host grant the request.
	RequestLocalRecording_Denied,///host deny the request.
	RequestLocalRecording_Timeout,///the request local recording timeout.	
};

enum LocalRecordingRequestPrivilegeStatus
{
	LocalRecordingRequestPrivilege_None,
	LocalRecordingRequestPrivilege_AllowRequest,///allow participant to send privilege requests.
	LocalRecordingRequestPrivilege_AutoGrant,///host auto-allow all privilege requests.
	LocalRecordingRequestPrivilege_AutoDeny,///host auto-deny all privilege requests.
};

/// \brief Process after the host receives the requirement from the user to give the local recording privilege.
class IRequestLocalRecordingPrivilegeHandler
{
public:
	virtual ~IRequestLocalRecordingPrivilegeHandler() {};
	/// \brief Get the request ID.
	/// \return If the function succeeds, the return value is the request ID.
	virtual const wchar_t* GetRequestId() = 0;

	/// \brief Get the user ID who requested privilege.
	/// \return If the function succeeds, the return value is the user ID. Otherwise, this returns 0.
	virtual unsigned int GetRequesterId() = 0;

	/// \brief Get the user name who requested privileges.
	/// \return If the function succeeds, the return value is the user name.
	virtual const wchar_t* GetRequesterName() = 0;

	/// \brief Allows the user to start local recording and finally self-destroy.
	virtual SDKError GrantLocalRecordingPrivilege() = 0;

	/// \brief Denies the user permission to start local recording and finally self-destroy.
	virtual SDKError DenyLocalRecordingPrivilege() = 0;
};

class ICustomizedLocalRecordingLayoutHelper;
/// \brief Meeting recording callback event.
///
class IMeetingRecordingCtrlEvent
{
public:
	virtual ~IMeetingRecordingCtrlEvent() {}

	/// \brief Callback event of ending the conversion to MP4 format.
	/// \param bsuccess TRUE indicates to convert successfully. FALSE not.
	/// \param iResult This value is used to save the error code only when the convert fails.
	/// \param szPath If the conversion is successful, this value is used to save the path of the recording file. 
	/// \remarks In order to trigger this callback correctly, you need call IMeetingConfiguration.EnableLocalRecordingConvertProgressBarDialog(false) before you start a meeting.
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) = 0;

	/// \brief Callback event of the process of the conversion to MP4 format.
	/// \param iPercentage Percentage of conversion process. Range from ZERO(0) to ONE HUNDREAD(100).
	/// \remarks In order to trigger this callback correctly, you need call IMeetingConfiguration.EnableLocalRecordingConvertProgressBarDialog(false) before you start a meeting.
	virtual void onRecording2MP4Processing(int iPercentage) = 0;

	/// \brief Callback event that the status of my local recording changes.
	/// \param status Value of recording status. For more details, see \link RecordingStatus \endlink enum.
	virtual void onRecordingStatus(RecordingStatus status) = 0;

	/// \brief Callback event that the status of cloud recording changes.
	/// \param status Value of recording status. For more details, see \link RecordingStatus \endlink enum.
	virtual void onCloudRecordingStatus(RecordingStatus status) = 0;

	/// \brief Callback event that the recording authority changes.
	/// \param bCanRec TRUE indicates to enable to record.
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;

	/// \brief Callback event that the status of request local recording privilege.
	/// \param status Value of request local recording privilege status. For more details, see \link RequestLocalRecordingStatus \endlink enum.
	virtual void onLocalRecordingPrivilegeRequestStatus(RequestLocalRecordingStatus status) = 0;

	/// \brief Callback event that the local recording source changes in the custom user interface mode.
	/// \param layout_helper An object pointer to ICustomizedLocalRecordingLayoutHelper. For more details, see \link ICustomizedLocalRecordingLayoutHelper \endlink.
	///The layout_helper won't be released till the call ends. The user needs to complete the related layout before the call ends. 
	virtual void onCustomizedLocalRecordingSourceNotification(ICustomizedLocalRecordingLayoutHelper* layout_helper) = 0;

	/// \brief Callback event when a user requests local recording privilege.
	/// \param handler A pointer to the IRequestLocalRecordingPrivilegeHandler. For more details, see \link IRequestLocalRecordingPrivilegeHandler \endlink.
	virtual void onLocalRecordingPrivilegeRequested(IRequestLocalRecordingPrivilegeHandler* handler) = 0;
};

/// \brief Meeting recording controller interface.
///
class IMeetingRecordingController
{
public:
	/// \brief Set meeting recording callback event handler.
	/// \param pEvent A pointer to the IMeetingRecordingCtrlEvent that receives the recording event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingRecordingCtrlEvent* pEvent) = 0;

	/// \brief Determine if the user owns the authority to enable the local recording. 	
	/// \return If the host is enabled to handle local recording request, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError IsSupportRequestLocalRecordingPrivilege() = 0;

	/// \brief Send a request to enable the SDK to start local recording.
	/// \return If the function succeeds, the return value is SDKErr_Success and the SDK will send the request.
	///Otherwise it fails and the request will not be sent. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RequestLocalRecordingPrivilege() = 0;

	/// \brief Start recording.
	/// \param [out] startTimestamp The timestamps when start recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartRecording(time_t& startTimestamp) = 0;

	/// \brief Stop recording.
	/// \param [out] stopTimestamp The timestamps when stop recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopRecording(time_t& stopTimestamp) = 0;

	/// \brief Determine if the specified user is enabled to start recording.
	/// \param cloud_recording TRUE indicates to determine whether to enable the cloud recording. FALSE local recording. 
	/// \param userid Specifies the user ID.
	/// \return If the value of cloud_recording is set to TRUE and the cloud recording is enabled, the return value is SDKErr_Success.
	///If the value of cloud_recording is set to FALSE and the local recording is enabled, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanStartRecording(bool cloud_recording, unsigned int userid) = 0;

	/// \brief Determine if the current user own the authority to change the recording permission of the others.
	/// \return If the user own the authority, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanAllowDisAllowLocalRecording() = 0;

	/// \brief Start cloud recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartCloudRecording() = 0;

	/// \brief Stop cloud recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopCloudRecording() = 0;

	/// \brief Determine if the user owns the authority to enable the local recording. 
	/// \param userid Specifies the user ID.
	/// \return If the specified user is enabled to start local recording, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError IsSupportLocalRecording(unsigned int userid) = 0;

	/// \brief Give the specified user authority for local recording.
	/// \param userid Specifies the user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError AllowLocalRecording(unsigned int userid) = 0;

	/// \brief Abrogate the authority of the specified user for local recoding.
	/// \param userid Specifies the user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DisAllowLocalRecording(unsigned int userid) = 0;

	/// \brief Send a request to enable the SDK to call IMeetingRecordingCtrlEvent::onCustomizedLocalRecordingSourceNotification().
	/// \return If the function succeeds, the return value is SDKErr_Success, and you will receive the onCustomizedLocalRecordingSourcenNotification callback event.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for custom style user interface mode only when recording.
	virtual SDKError RequestCustomizedLocalRecordingSource() = 0;

	/// \brief Pause recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError PauseRecording() = 0;

	/// \brief Resume recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ResumeRecording() = 0;

	/// \brief Pause cloud recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError PauseCloudRecording() = 0;

	/// \brief Resume cloud recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ResumeCloudRecording() = 0;

	/// \brief Start rawdata recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartRawRecording() = 0;

	/// \brief Stop rawdata recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopRawRecording() = 0;

	/// \brief Get current cloud recording.
	/// \return If the function succeeds, the return value is recording status.
	///To get extended error information, see \link RecordingStatus \endlink enum.
	virtual RecordingStatus GetCloudRecordingStatus() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif