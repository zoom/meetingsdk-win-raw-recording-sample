/*!
* \file zoom_sdk_ext.h
* \brief  ZOOM SDK Embedded Browser Interface.
* 
*/

#ifndef _ZOOM_SDK_EXT_H_
#define _ZOOM_SDK_EXT_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
extern "C"
{
	class IUIHooker;
	class ICustomizedResourceHelper;

	/// \brief Retrieve user Hooker interface.
	/// \param ppUIHooker A pointer to the IUIHooker*. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppEmbeddedBrowser is not NULL
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError RetrieveUIHooker(IUIHooker** ppUIHooker);

	/// \brief Retrieve customized resource helper interface.
	/// \param ppCustomiezedResourceHelper A pointer to the ICustomizedResourceHelper*. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppCustomiezedResourceHelper is not NULL
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError RetrieveCustomizedResourceHelper(ICustomizedResourceHelper** ppCustomiezedResourceHelper);
}

END_ZOOM_SDK_NAMESPACE
#endif