#pragma once
#include "stdafx.h"
#include "rawdata/rawdata_audio_helper_interface.h"


class ZoomSDKAudioRawDataDelegate : public ZOOM_SDK_NAMESPACE::IZoomSDKAudioRawDataDelegate
{
public:
    ZoomSDKAudioRawDataDelegate(){};
    virtual ~ZoomSDKAudioRawDataDelegate(){};
    virtual void onMixedAudioRawDataReceived(AudioRawData* data_) override;
    virtual void onOneWayAudioRawDataReceived(AudioRawData* data_, uint32_t node_id) override;
};
