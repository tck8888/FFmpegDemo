//
// Created by tck on 2020/11/26.
//

#ifndef MYMUSICPLAYER_AUDIOCHANNEL_H
#define MYMUSICPLAYER_AUDIOCHANNEL_H

#include "MyQueue.h"
#include "MyPlayerStatus.h"
#include "JavaCallHelper.h"

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
    AudioChannel(
            MyPlayerStatus *_playerStatus,
            int _sample_rate,
            JavaCallHelper *_javaCallHelper);

    ~AudioChannel();

public:
    int streamIndex = -1;
    AVCodecParameters *codecpar = NULL;
    AVCodecContext *avCodecContext = NULL;
    MyQueue *queue = NULL;
    MyPlayerStatus *playerStatus = NULL;
    uint8_t *buffer = NULL;

    pthread_t thread_play;

    AVPacket *avPacket = NULL;
    AVFrame *avFrame = NULL;
    int ret = 0;
    int data_size = 0;
    int sample_rate = 0;

    int64_t duration = 0;
    AVRational time_base;
    double clock;//总的播放时长
    double now_time;//当前frame时间
    double last_time; //上一次调用时间

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


    JavaCallHelper *javaCallHelper = NULL;

public:
    void play();

    int resampleAudio();

    void initOpenSLES();

    void onResume();

    void onPause();

    void onStop();

    void release();

    SLuint32 getCurrentSampleRateForOpensles(int sample_rate);
};


#endif //MYMUSICPLAYER_AUDIOCHANNEL_H
