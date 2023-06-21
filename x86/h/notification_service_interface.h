/*!
* \file notification_service_interface.h
* \brief Notification Service Interface
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _NOTIFICATIONE_SERVICE_INTERFACE_H_
#define _NOTIFICATIONE_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \struct MeetingDeviceInfo
	\brief information of meeting device info.
	Here are more detailed structural descriptions..
*/
struct InMeetingDeviceInfo
{
	int nIndex;///<index
	const wchar_t* deviceName;///<device name
	const wchar_t* meetingTopic;///<meeting topic
	UINT64 meetingNumber;///<meeting number
	InMeetingDeviceInfo()
	{
		nIndex = -1;
		deviceName = NULL;
		meetingTopic = NULL;
		meetingNumber = 0;
	}
};

/// \brief Notification service helper callback event.
///
class INotificationServiceEvent
{
public:
	/// \brief Callback event that the device for users to attend the meeting has changed.
	/// \param pDeviceList A list of meeting info with active meetings.
	virtual void onMeetingDeviceListChanged(IList<InMeetingDeviceInfo>* pDeviceList) = 0;

	/// \brief Transfer meeting status changed callback.
	/// \param bSuccess The result of transfer meeting.
	virtual void onTransferMeetingStatus(bool bSuccess) = 0;
		
};

/// \brief Notification service control interface.
class IPresenceHelper;
class INotificationServiceHelper 
{
public:
	virtual ~INotificationServiceHelper () {}

	/// \brief Get the Presence helper.
	/// \return If the function succeeds, the return value is a pointer to IPresenceHelper. Otherwise the function fails and returns NULL.
	virtual IPresenceHelper* GetPresenceHelper() = 0;

	/// Set the controller event of notification service.
	virtual SDKError SetEvent(INotificationServiceEvent* pEvent) = 0;

	/// brief Determine whether the transfer meeting feature is enabled.
	virtual bool IsTransferMeetingEnabled() = 0;

	/// brief Determine whether the presence feature is enabled.
	virtual bool IsPresenceFeatureEnabled() = 0;

	/// \brief Try to transfer meeting to current device.
	/// \param nIndex Specifies the index of meeting list.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError TransferMeeting(int nIndex) = 0;

};
END_ZOOM_SDK_NAMESPACE
#endif