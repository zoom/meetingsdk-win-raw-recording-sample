/*!
* \file meeting_immersive_interface.h
* \brief ZOOM Custom Immersive Interface
*
*/
#ifndef _MEETING_IMMERSIVE_INTERFACE_H_
#define _MEETING_IMMERSIVE_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum CustomImmersiveTemplateType
	\brief Type of immersive template.
	View more detailed structural descriptions.
*/
enum CustomImmersiveTemplateType
{
	CustomImmersiveTemplateType_Default,	///<The default template.
	CustomImmersiveTemplateType_CustomImage,///<A template using a custom image. This kind of template can only be used after CustomImmersiveTemplateType_MyVideo template is ready.
	CustomImmersiveTemplateType_MyVideo		///<The my video template.
};

/*! \struct SeatPlacementInfo
	\brief Information of seat placement in a template.
*/
struct SeatPlacementInfo
{
	unsigned int seat_id;	///<The seat ID.
	RECT position;			///<The seat position.
};

/*! \struct CustomImmersiveLayoutData
	\brief Layout data of immersive.
*/
struct CustomImmersiveLayoutData
{
	bool is_seat_free;		///<Whether this user is in seat.
	unsigned int seat_id;	///<The seat ID.
	unsigned int user_id;	///<The user ID.
	unsigned int z_order;	///<The seat z order. Higher numbers are displayed on top of lower ones.
	RECT position;			///<The seat position.
};

/// \brief Immersive template object interface.
///
class ICustomImmersiveTemplate
{
public:
	/// \brief Get the name of this template.
	/// \return If the function succeeds, the return value is the name of this template.
	virtual const wchar_t* getTemplateName() = 0;

	/// \brief Get the bitmap of the thumbnail.
	/// \return If the function succeeds, the return value is the bitmap of this thumbnail.
	virtual const void* getThumbnailBitmap() = 0;

	/// \brief Get the capacity of this template.
	/// \return If the function succeeds, the return value is the seat capacity of this template.
	virtual unsigned int getCapacity() = 0;

	/// \brief Determine if this template is ready. 
	/// \return TRUE indicates that this template is ready.
	virtual bool isTemplateReady() = 0;

	/// \brief Determine whether this template supports a free seat. 
	/// \return TRUE indicates that the user can be put to free seat in this template.
	virtual bool isSupportFreeSeat() = 0;

	/// \brief Get the size of this template.
	/// \return If the function succeeds, the return value is the size of this template.
	virtual SIZE getCanvasSize() = 0;

	/// \brief Get the list of template seats.
	/// \return The list of template seats. ZERO(0) indicates that there are no seats in the template.
	virtual IList<SeatPlacementInfo>* getSeatList() = 0;

	/// \brief Get the type of this template.
	/// \return If the function succeeds, the return value is the type of this template. For more details, see \link CustomImmersiveTemplateType \endlink enum.
	virtual CustomImmersiveTemplateType getType() = 0;

	virtual ~ICustomImmersiveTemplate() {}
};

/// \brief Immersive pre-layout helper interface to update immersive view layout at once. 
///
class ICustomImmersivePreLayoutHelper
{
public:
	/// \brief Add a user to the pre-layout with a seat ID.
	/// \param userID The user ID.
	/// \param seatID The seat ID.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS.
	///Otherwise, the function returns an error. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError addUser(unsigned int userID, unsigned int seatID) = 0;

	/// \brief Add a user to the pre-layout with a position.
	/// \param userID The user ID.
	/// \param pos The position.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS.
	///Otherwise, the function returns an error. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError addUser(unsigned int userID, RECT pos) = 0;

	/// \brief Remove a user from the pre-layout.
	/// \param userID The user ID.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS.
	///Otherwise, the function returns an error. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError removeUser(unsigned int userID) = 0;

	/// \brief Remove all users from the pre-layout.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS.
	///Otherwise, the function returns an error. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError removeAllUsers() = 0;

	/// \brief Get the pre-layout data.
	/// \return The pre-layout data. ZERO(0) indicates that there are no user in the pre-layout. For more details, see \link CustomImmersiveLayoutData \endlink.
	virtual IList<CustomImmersiveLayoutData>* getPreLayoutData() = 0;

	/// \brief Commit pre-layout data to immersive view. This only works just after the immersive view starts. 
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS and the user list will be cleaned up.
	///Otherwise, the function returns an error. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError commit() = 0;

	virtual ~ICustomImmersivePreLayoutHelper() {}
};

/// \brief Immersive controller object interface.
///
class ICustomImmersiveCtrlEvent
{
public:
	/// \brief Callback event that the immersive view was enabled/disabled.
	/// \param bOn The status of immersive status.
	virtual void onImmersiveStatusChanged(bool bOn) = 0;

	/// \brief Callback event that the selected immersive template changed.
	/// \param immersiveTemplate The new template. For more details, see \link ICustomImmersiveTemplate \endlink.
	virtual void onSelectedImmersiveTemplateChanged(ICustomImmersiveTemplate* immersiveTemplate) = 0;

	/// \brief Callback event that the immersive seat layout changed.
	/// \param seatList The new seat layout. For more details, see \link CustomImmersiveLayoutData \endlink.
	virtual void onImmersiveSeatLayoutUpdated(IList<CustomImmersiveLayoutData>* seatList) = 0;

	/// \brief Callback event for the immersive template download process.
	/// \param immersiveTemplate The new template. For more details, see \link ICustomImmersiveTemplate \endlink.
	/// \param progress The process.
	virtual void onTemplateDownloadProgress(ICustomImmersiveTemplate* immersiveTemplate, unsigned int progress) = 0;

	/// \brief Callback event for the immersive template download end.
	/// \param immersiveTemplate The new template. For more details, see \link ICustomImmersiveTemplate \endlink.
	/// \param bSuccess The download result.
	virtual void onTemplateDownloadEnded(ICustomImmersiveTemplate* immersiveTemplate, bool bSuccess) = 0;

	/// \brief Callback event that template thumbnails download end.
	/// \param bSuccess The download result.
	virtual void onTemplateThumbnailsDownloadEnded(bool bSuccess) = 0;

	virtual ~ICustomImmersiveCtrlEvent() {}
};

/// \brief Meeting immersive controller interface. For more details on this feature, see https://support.zoom.us/hc/en-us/articles/360060220511-Immersive-View
///
class ICustomImmersiveController
{
public:
	/// \brief Set immersive object callback event handler.
	/// \param pEvent A pointer to the ICustomImmersiveCtrlEvent that receives the immersive object events. For more details, see \link ICustomImmersiveCtrlEvent \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(ICustomImmersiveCtrlEvent* pEvent) = 0;

	/// \brief Determine if immersive is supported. 
	/// \param [out] bSupport True means support immersive. Otherwise, false. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError isSupportImmersive(bool& bSupport) = 0;

	/// \brief Determine if immersive view is active. 
	/// \param [out] bOn True means the immersive view is active. Otherwise, false. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError isImmersiveViewOn(bool& bOn) = 0;

	/// \brief Download the template thumbnails. See /link ICustomImmersiveCtrlEvent /endlink for updates on the download.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError downloadTemplateThumbnails() = 0;

	/// \brief Determine if the thumbnails are ready. 
	/// \param [out] bReady True means the immersive thumbnails is ready, false not. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError isTemplateThumbnailsReady(bool& bReady) = 0;

	/// \brief Get the list of templates.
	/// \return The list of templates. ZERO(0) indicates that there are no templates. For more details, see \link ICustomImmersiveTemplate \endlink.
	virtual IList<ICustomImmersiveTemplate*>* getTemplates() = 0;

	/// \brief Download complete template resource. 
	/// \param immersiveTemplate The template to be downloaded. For more details, see \link ICustomImmersiveTemplate \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError downloadTemplate(ICustomImmersiveTemplate* immersiveTemplate) = 0;

	/// \brief Determine if the immersive template can be started. 
	/// \param immersiveTemplate The selected template in immersive view. For more details, see \link ICustomImmersiveTemplate \endlink.
	/// \param [out] bCan True means the immersive can be started, false not. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError canStartImmersiveView(ICustomImmersiveTemplate* immersiveTemplate, bool& bCan) = 0;

	/// \brief Start immersive view. 
	/// \param immersiveTemplate The selected template in immersive view. For more details, see \link ICustomImmersiveTemplate \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	/// remarks For the host, it must be started after the immersive container is created.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError startImmersiveView(ICustomImmersiveTemplate* immersiveTemplate) = 0;

	/// \brief Change template in immersive view. 
	/// \param immersiveTemplate The selected template in immersive view. For more details, see \link ICustomImmersiveTemplate \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError changeTemplate(ICustomImmersiveTemplate* immersiveTemplate) = 0;

	/// \brief Exit immersive view. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError endImmersiveView() = 0;

	/// \brief Get the current template. 
	/// \return If the function succeeds, the return value is the current template. For more details, see \link ICustomImmersiveTemplate \endlink.
	virtual ICustomImmersiveTemplate* getCurrentTemplate() = 0;

	/// \brief Determine if the user can be shown in immersive view. 
	/// \param userID The user ID.
	/// \param [out] bCan True means the user can be shown in immersive view, false if they cannot. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError canUserShowInImmersiveView(unsigned int userID, bool& bCan) = 0;

	/// \brief Get the immersive pre-layout helper pointer. 
/// \return If the function succeeds, the return value is the immersive layout helper pointer. For more details, see \link ICustomImmersiveLayoutHelper \endlink.
	virtual ICustomImmersivePreLayoutHelper* getImmersivePreLayoutHelper() = 0;

	/// \brief Get the immersive seat layout data.
	/// \return The immersive seat layout data. ZERO(0) indicates that there are no users in the immersive view. For more details, see \link CustomImmersiveLayoutData \endlink.
	virtual IList<CustomImmersiveLayoutData>* getLayoutData() = 0;

	/// \brief Put the user in the seat. 
	/// \param userID The user ID.
	/// \param seatID The seat ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError assignUser(unsigned int userID, unsigned int seatID) = 0;

	/// \brief Put the user in the free seat. 
	/// \param userID The user ID.
	/// \param pos The position.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError putUserToFreeSeat(unsigned int userID, RECT pos) = 0;

	/// \brief Remove user from immersive view. 
	/// \param userID The user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError removeUser(unsigned int userID) = 0;

	/// \brief Determine if the user is in immersive view. 
	/// \param userID The user ID.
	/// \param [out] bIn True means the user is in immersive view, false means that they are not. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError isUserInImmersiveView(unsigned int userID, bool& bIn) = 0;

	/// \brief Add a template based on a custom image. 
	/// \param filePath The image file path.
	/// \param [out] immersiveTemplate The object of custom template. For more details, see \link ICustomImmersiveTemplate \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError addCustomImageTemplate(const wchar_t* filePath, ICustomImmersiveTemplate** immersiveTemplate) = 0;

	/// \brief Remove custom image template. 
	/// \param immersiveTemplate The custom image template that want to remove. For more details, see \link ICustomImmersiveTemplate \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise, failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError removeCustomImageTemplate(ICustomImmersiveTemplate* immersiveTemplate) = 0;


	virtual ~ICustomImmersiveController() {}
};



END_ZOOM_SDK_NAMESPACE
#endif