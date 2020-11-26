//
// Created by tck on 2020/11/26.
//

#ifndef MYMUSICPLAYER_AUDIOCHANNEL_H
#define MYMUSICPLAYER_AUDIOCHANNEL_H

extern "C"
{
#include "libavformat/avformat.h"
}

class AudioChannel {


public:
    AVCodecParameters *codecpar;
    AVCodecContext *avCodecContext;
    int streamIndex;

};


#endif //MYMUSICPLAYER_AUDIOCHANNEL_H
