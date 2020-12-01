//
// Created by tck on 2020/11/26.
//

#ifndef MYMUSICPLAYER_AUDIOCHANNEL_H
#define MYMUSICPLAYER_AUDIOCHANNEL_H

#include "MyQueue.h"
#include "MyPlayerStatus.h"
#include "pthread.h"

extern "C"
{
#include "libavformat/avformat.h"
#include <libswresample/swresample.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
}

class AudioChannel {

public:
    AudioChannel(MyPlayerStatus *_playerStatus,int _sample_rate);

    ~AudioChannel();

public:
    int streamIndex=-1;
    AVCodecParameters *codecpar = nullptr;
    AVCodecContext *avCodecContext = nullptr;
    MyQueue *queue = nullptr;
    MyPlayerStatus *playerStatus = nullptr;
    uint8_t *buffer = nullptr;

    pthread_t thread_play;

    AVPacket *avPacket = nullptr;
    AVFrame *avFrame = nullptr;
    int ret = 0;
    int data_size = 0;
    int sample_rate = 0;

    // 引擎接口
    SLObjectItf engineObject = NULL;
    SLEngineItf engineEngine = NULL;

    //混音器
    SLObjectItf outputMixObject = NULL;
    SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;
    SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

    //pcm
    SLObjectItf pcmPlayerObject = NULL;
    SLPlayItf pcmPlayerPlay = NULL;

    //缓冲器队列接口
    SLAndroidSimpleBufferQueueItf pcmBufferQueue = NULL;

public:
    void play();

    int resampleAudio();

    void initOpenSLES();

    SLuint32 getCurrentSampleRateForOpensles(int sample_rate);
};


#endif //MYMUSICPLAYER_AUDIOCHANNEL_H
