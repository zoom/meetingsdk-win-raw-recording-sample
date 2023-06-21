/*!
* \file meeting_reminder_ctrl_interface.h
* \brief Meeting Service Phone Interface.
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_REMINDER_CTRL_INTERFACE_H_
#define _MEETING_REMINDER_CTRL_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum MeetingReminderType
	\brief The type for disclaimer dialog.
	Here are more detailed structural descriptions.
*/
enum MeetingReminderType
{
	TYPE_LOGIN_REQUIRED,///Reminder type of login.
	TYPE_START_OR_JOIN_MEETING,///<Reminder type of start or join meeting.
	TYPE_RECORD_REMINDER,///<Reminder type of record reminder.
	TYPE_RECORD_DISCLAIMER,///<Reminder type of record disclaimer
	TYPE_LIVE_STREAM_DISCLAIMER,///<Reminder type of live stream disclaimer.
	TYPE_ARCHIVE_DISCLAIMER,///<Reminder type of archive disclaimer.
	TYPE_WEBINAR_AS_PANELIST_JOIN,///<Reminder type of join webinar as panelist.
};

/// \brief the interface of reminder dialog content.
class IMeetingReminderContent
{
public:
	virtual ~IMeetingReminderContent() {};
	/// \brief Get the type of the reminder.
	virtual MeetingReminderType  GetType() = 0;
	/// \brief Get the title of the reminder dialog content.
	virtual const wchar_t* GetTitle() = 0;
	/// \brief Get the detail content of the reminder dialog content.
	virtual const wchar_t* GetContent() = 0;
	/// \brief Determine whether block the user join or stay in the meeting
	/// \return True indicates block the user join or stay in the meeting. Otherwise False.
	virtual bool  IsBlocking() = 0;
};

/// \brief the interface to handle the reminder dialog.
class IMeetingReminderHandler
{
public:
	virtual ~IMeetingReminderHandler() {};
	/// \brief Ignore the reminder.
	virtual void  Ignore() = 0;
	/// \brief Accept the reminder.
	virtual void  Accept() = 0;
	/// \brief Decline the reminder.
	virtual void  Decline() = 0;
};

/// \brief Meeting reminder helper callback event.
class IMeetingReminderEvent
{
public:
	virtual ~IMeetingReminderEvent() {}

	/// \brief Callback event of the reminder dialog show.
	/// \param content The detail content in the reminder dialog. For more details, see \link IMeetingReminderContent \endlink enum.
	/// \param handle A pointer to the IMeetingReminderHandler. For more details, see \link IMeetingReminderHandler \endlink.
	virtual void onReminderNotify(IMeetingReminderContent* content, IMeetingReminderHandler* handle) = 0;
};
/// \brief Meeting reminder dialog interface.
///
class IMeetingReminderController
{
public:
	/// \brief Set meeting reminder controller callback event handler
	/// \param pEvent A pointer to the IMeetingReminderEvent that receives reminder callback event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingReminderEvent* pEvent) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif