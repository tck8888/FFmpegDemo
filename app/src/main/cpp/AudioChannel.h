//
// Created by tck on 2020/11/26.
//

#ifndef MYMUSICPLAYER_AUDIOCHANNEL_H
#define MYMUSICPLAYER_AUDIOCHANNEL_H

#include "MyQueue.h"
#include "MyPlayerStatus.h"

extern "C"
{
#include "libavformat/avformat.h"
}

class AudioChannel {

public:
    AudioChannel(MyPlayerStatus *_playerStatus);

    ~AudioChannel();

public:
    int streamIndex;
    AVCodecParameters *codecpar = nullptr;
    AVCodecContext *avCodecContext = nullptr;
    MyQueue *queue = nullptr;
    MyPlayerStatus *playerStatus = nullptr;

};


#endif //MYMUSICPLAYER_AUDIOCHANNEL_H
