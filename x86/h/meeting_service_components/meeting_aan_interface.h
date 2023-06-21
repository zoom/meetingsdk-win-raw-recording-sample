/*!
* \file meeting_aan_interface.h
* \brief show/hide AAN window.
* Valid for customUI mode.
*/
#ifndef _MEETING_AAN_INTERFACE_H_
#define _MEETING_AAN_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/// \brief Meeting AAN controller interface.
///
class IMeetingAANController
{
public:
	/// \brief Show AAN panel window.
	/// \param x: the horizontal coordinate value. 
	/// \param y: the coordinate coordinate value. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ShowAANPanel(unsigned int x, unsigned int y) = 0;

	/// \brief Hide AAN panel window.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError HideAANPanel() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif