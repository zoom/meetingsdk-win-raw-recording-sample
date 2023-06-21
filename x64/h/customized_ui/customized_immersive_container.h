/*!
* \file customized_immersive_container.h
* \brief ZOOM Custom Immersive Container Interface.
*
*/
#ifndef _ZOOM_CUSTOMIZED_IMMERSIVE_CONTAINER_H_
#define _ZOOM_CUSTOMIZED_IMMERSIVE_CONTAINER_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/// \brief Callback event of custom immersive container. 
///
class ICustomizedImmersiveContainerEvent
{
public:
	/// \brief The SDK will pass the window messages to users via the callback. Here are the messages.
	///WM_MOUSEMOVE
	///WM_MOUSEENTER
	///WM_MOUSELEAVE
	///WM_LBUTTONDOWN
	///WM_LBUTTONUP
	///WM_RBUTTONUP
	///WM_LBUTTONDBLCLK
	///WM_KEYDOWN
	virtual void onWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	virtual	~ICustomizedImmersiveContainerEvent() {};
};


class ICustomizedImmersiveContainer
{
public:
	/// \brief Set immersive container callback event handler.
	/// \param pEvent A pointer to the ICustomizedImmersiveContainerEvent that receives video container callback event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(ICustomizedImmersiveContainerEvent* pEvent) = 0;

	/// \brief Resize the immersive container in the specified area and reset the parent window.
	/// \param rc Specify a new display area. The coordinate value of the structure is that of the parent window of immersive container.
	/// \param hParentWnd Specify a new parent window HWND.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RepositionContainer(RECT rc, HWND hParentWnd = nullptr) = 0;

	/// \brief Show the waiting area before start immersive.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// remarks It is only valid if called before start immersive view.
	virtual SDKError ShowWaitingArea() = 0;

	/// \brief Hide the waiting area before start immersive.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// remarks It is only valid if called before start immersive view.
	virtual SDKError HideWaitingArea() = 0;

	virtual ~ICustomizedImmersiveContainer() {}
};

END_ZOOM_SDK_NAMESPACE
#endif