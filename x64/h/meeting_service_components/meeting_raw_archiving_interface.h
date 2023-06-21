/*!
* \file meeting_aan_interface.h
* \brief show/hide AAN window.
* Valid for customUI mode.
*/
#ifndef _MEETING_RAW_ARCHIVING_INTERFACE_H_
#define _MEETING_RAW_ARCHIVING_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/// \brief Meeting AAN controller interface.
///
class IMeetingRawArchivingController
{
public:
	/// \brief start raw archiving,call this method can get rawdata receive previlege
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartRawArchiving() = 0;

	/// \brief stop raw archiving, call this method reclaim rawdata receive previlege
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopRawArchiving() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif