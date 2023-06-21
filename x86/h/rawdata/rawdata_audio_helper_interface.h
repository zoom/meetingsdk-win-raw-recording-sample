#ifndef _RAWDATA_AUDIO_HELPER_INTERFACE_H_
#define _RAWDATA_AUDIO_HELPER_INTERFACE_H_
#include "zoom_sdk_def.h"

class AudioRawData;

BEGIN_ZOOM_SDK_NAMESPACE
class IZoomSDKAudioRawDataDelegate
{
public:
	~IZoomSDKAudioRawDataDelegate(){}
	virtual void onMixedAudioRawDataReceived(AudioRawData* data_) = 0;
	virtual void onOneWayAudioRawDataReceived(AudioRawData* data_, uint32_t node_id) = 0;
};

class IZoomSDKAudioRawDataSender
{
public:
	virtual ~IZoomSDKAudioRawDataSender() {}

	/// \brief Send audio raw data, channel number must be mono, and sampling bits must be 16.
	/// \param data, The address of audio data.
	/// \param data_length, The length of audio data, it must be even numbers.
	/// \param sample_rate, The sampling rate of audio data(8000/11025/32000/44100/48000/50000/50400/96000/192000/2822400).
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError send(char* data, unsigned int data_length, int sample_rate) = 0;
};

class IZoomSDKVirtualAudioMicEvent
{
public:
	virtual ~IZoomSDKVirtualAudioMicEvent() {}

	/// \brief Callback for virtual audio mic to do some initialization.
	/// \param pSender, You can send audio data based on this object, see \link IZoomSDKAudioRawDataSender \endlink.
	virtual void onMicInitialize(IZoomSDKAudioRawDataSender* pSender) = 0;

	/// \brief Callback for virtual audio mic can send raw data with 'pSender'.
	virtual void onMicStartSend() = 0;

	/// \brief Callback for virtual audio mic should stop send raw data.
	virtual void onMicStopSend() = 0;

	/// \brief Callback for virtual audio mic is uninitialized.
	virtual void onMicUninitialized() = 0;
};

class IZoomSDKAudioRawDataHelper
{
public:
	virtual ~IZoomSDKAudioRawDataHelper(){}
	virtual SDKError subscribe(IZoomSDKAudioRawDataDelegate* pDelegate) = 0;
	virtual SDKError unSubscribe() = 0;

	/// \brief Subscribe audio mic raw data with a callback.
	/// \param pSource, Callback sink object.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError setExternalAudioSource(IZoomSDKVirtualAudioMicEvent* pSource) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif