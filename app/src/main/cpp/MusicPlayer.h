//
// Created by tck on 2020/11/26.
//

#ifndef MYMUSICPLAYER_MUSICPLAYER_H
#define MYMUSICPLAYER_MUSICPLAYER_H

#include <pthread.h>
#include "JavaCallHelper.h"
#include "AndroidLog.h"
#include "AudioChannel.h"

extern "C"
{
#include "libavformat/avformat.h"
}


class MusicPlayer {

public:
    MusicPlayer(JavaCallHelper *_helper);

    ~MusicPlayer();

private:
    char *path;
    JavaCallHelper *helper;
    AudioChannel *audio;
public:
    pthread_t decodeThread;
    AVFormatContext *avFormatContext;

private:


public:
    void setDataSource(const char *path);

    void prepare();

    void start();

    void decodeFFmpegThread();
};


#endif //MYMUSICPLAYER_MUSICPLAYER_H
