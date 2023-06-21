#ifndef _RAWDATA_SHARE_SOURCE_HELPER_INTERFACE_H_
#define _RAWDATA_SHARE_SOURCE_HELPER_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

class IZoomSDKShareSender
{
public:
	virtual ~IZoomSDKShareSender() {}
	virtual SDKError sendShareFrame(char* frameBuffer, int width, int height, int frameLength, FrameDataFormat format = FrameDataFormat_I420_FULL) = 0;
};

class IZoomSDKShareSource
{
public:
	virtual ~IZoomSDKShareSource() {}
	virtual void onStartSend(IZoomSDKShareSender* pSender) = 0;
	virtual void onStopSend() = 0;
};

class IZoomSDKShareSourceHelper
{
public:
	virtual ~IZoomSDKShareSourceHelper() {}
	virtual SDKError setExternalShareSource(IZoomSDKShareSource* pShareSource) = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif