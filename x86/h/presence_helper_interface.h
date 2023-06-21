/*!
* \file presenece_helper_interface.h
* \brief Presence Helper Interface
* 
*/
#ifndef _PRESENCE_HELPER_INTERFACE_H_
#define _PRESENCE_HELPER_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

enum SDKPresenceStatus
{	
	SDKPresenceStatus_None,
	SDKPresenceStatus_Available,
	SDKPresenceStatus_UnAvailable,
	SDKPresenceStatus_InMeeting,
	SDKPresenceStatus_Busy,
	SDKPresenceStatus_DoNotDisturb,
	SDKPresenceStatus_Away,
	SDKPresenceStatus_PhoneCall,
	SDKPresenceStatus_Presenting,
	SDKPresenceStatus_Calendar,
	SDKPresenceStatus_OutOfOffice,
};

/// \brief Presence information interface.
///
class IContactInfo
{
public:
	/// \brief Get the contact's ID.
	/// \return The contact ID.
	virtual const wchar_t* GetContactId() = 0;

	/// \brief Get the contact's name.
	/// \return The contact name.
	virtual const wchar_t* GetContactName() = 0;

	/// \brief Get the contact's presence status.
	/// \return The return value is the contact presence such as SDKPresenceStatus_Available. 
	/// It's just the state when you get the contact detail information. 
	virtual SDKPresenceStatus GetPresenceStatus() = 0;
	
	/// \brief Get the contact's profile picture.
	/// \return The profile picture.
	virtual const wchar_t* GetProfilePicture() = 0;

	/// \brief Get the contact's personal note.
	/// \return The personal note.
	virtual const wchar_t* GetPersonalNote() = 0;

	/// \brief Get the contact's company name.
	/// \return The company name, such as "Acme Incorporated".
	virtual const wchar_t* GetCompanyName() = 0;

	/// \brief Get the contact's department.
	/// \return The contact's department, such as "Human resources".
	virtual const wchar_t* GetDepartment() = 0;

	/// \brief Get the contact's job title.
	/// \return The contact's job title,such as "Support engineer".
	virtual const wchar_t* GetJobTitle() = 0;

	/// \brief Get the contact's phone number.
	/// \return The phone number, such as "+1 000 000-0000".
	virtual const wchar_t* GetPhoneNumber() = 0;

	/// \brief Get the contact's email.
	/// \return The email address, such as "jillchill@example.com".
	virtual const wchar_t* GetEmail() = 0;

	virtual ~IContactInfo(){};
};

/// \brief Process after the user receives the invitation from other user to join meeting.
class IInvitationMeetingHandler
{
public:
	virtual ~IInvitationMeetingHandler() {};

	/// \brief Get the inviter's name.
	/// \return The return value is the inviter's name.
	virtual const wchar_t* GetSenderName() = 0;

	/// \brief Get the meeting invite number.
	/// \return The meeting invite number.
	virtual UINT64 GetMeetingNumber() = 0;

	/// \brief Determine whether this invitation is from a channel. 
	/// \return TRUE indicates that this invitation is from a channel.
	virtual bool IsChannelInvitation() = 0;

	/// \brief Get the channel name.
	/// \return The channel name.
	virtual const wchar_t* GetChannelName() = 0;

	/// \brief Get the channel member count.
	/// \return The number of channel members of this invitation.
	virtual UINT64 GetChannelMemberCount() = 0;

	/// \brief Set the display name in meeting. 
	/// \param screenName The display name in meeting.
	virtual SDKError SetScreenName(const wchar_t* screenName) = 0;

	/// \brief Instance to accept the invitation, join the meeting and finally self-destroy.	
	virtual SDKError Accept() = 0;

	/// \brief Instance to decline the invitation, decline and finally self-destroy.
	virtual SDKError Decline() = 0;

	/// \brief Instance timeout, and finally self-destruct.
	virtual SDKError TimeOut() = 0;
	
};

/// \brief Presence helper callback event.
///
class IPresenceHelperEvent
{
public:
	virtual ~IPresenceHelperEvent() {}

	/// \brief Request star contact ID list callback.
	/// \param pContactList Star contact result value.
	virtual void onRequestStarContact(IList<const wchar_t*>* pContactList) = 0;

	/// \brief Request contact detail information list callback.
	/// \param pContactList Contact detail information list.
	virtual void onRequestContactDetailInfo(IList<IContactInfo*>* pContactList) = 0;

	/// \brief Contact presence changed callback.
	/// \param contactId The contact's ID.
	/// \param status contact presence status.	
	virtual void onContactPresenceChanged(const wchar_t* contactId, SDKPresenceStatus status) = 0;

	/// \brief Star contact list changed callback.
	/// \param pContactList The list of change contact's ID.
	/// \param bAdd Specifies whether the contact list is added.
	virtual void onStarContactListChanged(IList<const wchar_t*>* pContactList,bool bAdd) = 0;

	/// \brief Receive meeting invitation callback.
	/// \param handler A pointer to the IInvitationMeetingHandler. For more details, see \link IInvitationMeetingHandler \endlink.
	virtual void onReceiveInvitationToMeeting(IInvitationMeetingHandler* handler) = 0;

	/// \brief Callback for the meeting invitation canceled by the inviter.
	/// \param meetingNumber cancel meeting number.
	virtual void onMeetingInvitationCanceled(UINT64 meetingNumber) = 0;

	/// \brief Callback to accept a meeting invitation on another device.
	/// \param meetingNumber accept meeting number.
	virtual void onMeetingAcceptedByOtherDevice(UINT64 meetingNumber) = 0;

	/// \brief Callback to decline a meeting invitation on another device.
	/// \param meetingNumber accept meeting number.
	virtual void onMeetingDeclinedByOtherDevice(UINT64 meetingNumber) = 0;

	/// \brief Callback to decline a meeting invitation.
	/// \contactId The ID of the contact who declines the invitation.
	virtual void onMeetingInvitationDeclined(const wchar_t* contactId) = 0;

};

class IBatchRequestContactHelper
{
public:
	/// \brief Prepare to batch request for contact helper.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum
	/// \remarks If the function succeeds, all the added contact IDs are removed and the prepared list you added by calling \link AddContactToList \endlink is cleared.
	virtual SDKError CreateBatchRequestBegin() = 0;

	/// \brief Add the contact ID to a prepared list.
	/// \param contactId, the contact ID you want to request.
	/// \return true if the contact ID is added to the prepared list successfully.
	/// \remarks The max number of the prepared list is 20.
	/// \Remark CreateBatchRequestBegin() must be called before this function is called. Otherwise this returns false.
	virtual bool AddContactToList(const wchar_t* contactId) = 0;

	/// \brief Batch request contact detail information according to the prepare list.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum
	/// \Remarks Call CreateBatchRequestBegin() before calling this function. Otherwise, it returns SDKErr_WRONG_USAGE.
	virtual SDKError CommitContactDetailInfoRequest() = 0;

	/// \brief Batch subscribe contact presence status according to the prepare list.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum
	/// \Remarks Call CreateBatchRequestBegin() before calling this function. Otherwise, it returns SDKErr_WRONG_USAGE.
	/// The expiration time of the subscription is three hours.
	virtual SDKError CommitSubscribeContactPresence() = 0;

	/// \brief Batch unsubscribe contact presence status according to the prepare list.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum
	/// \Remarks Call CreateBatchRequestBegin() before calling this function. Otherwise, it returns SDKErr_WRONG_USAGE.
	virtual SDKError CommitUnSubscribeContactPresence() = 0;
};

/// \brief Presence Helper Interface.
///
class IPresenceHelper
{
public:	
	/// \brief Set the presence helper callback event handler.
	/// \param pEvent A pointer to receive presence helper event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IPresenceHelperEvent* pEvent) = 0;

	/// \brief Send a request to get the starred contact ids.
	/// \return If the function succeeds, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RequestStarContact() = 0;

	/// \brief Send a request to add the contact ID to the starred contact list.
	/// \param contactId The contact ID.
	/// \return If the function succeeds, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError AddStarContact(const wchar_t* contactId) = 0;

	/// \brief Send a request to remove the contact ID from starred contact list.
	/// \param contactId The contact ID.
	/// \return If the function succeeds, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError UnStarContact(const wchar_t* contactId) = 0;

	/// \brief Send an invitation to a contact to join a meeting.
	/// \param contactId The contact ID.
	/// \return If the function succeeds, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError InviteContact(const wchar_t* contactId) = 0;

	/// \brief Get the Batch request contact controller.
	/// \return If the function succeeds, the return value is a pointer to IBatchRequestContactHelper. Otherwise the function fails and returns NULL.
	virtual IBatchRequestContactHelper* GetBatchRequestContactHelper() = 0;

};
END_ZOOM_SDK_NAMESPACE
#endif
