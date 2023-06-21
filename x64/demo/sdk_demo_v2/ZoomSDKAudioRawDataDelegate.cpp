#include "stdafx.h"
#include "ZoomSDKAudioRawDataDelegate.h"

#include <iostream>
#include <zoom_sdk_raw_data_def.h>


void ZoomSDKAudioRawDataDelegate::onMixedAudioRawDataReceived(AudioRawData* data_)
{
}

void ZoomSDKAudioRawDataDelegate::onOneWayAudioRawDataReceived(AudioRawData* data_, uint32_t node_id)
{
    cout << "Received " << data_->GetBufferLen() << "b from "<< "Node " << node_id << endl;
}
