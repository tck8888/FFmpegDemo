//
// Created by tck on 2020/11/26.
//

#ifndef MYMUSICPLAYER_MUSICPLAYER_H
#define MYMUSICPLAYER_MUSICPLAYER_H

#include <pthread.h>
#include "JavaCallHelper.h"
#include "AndroidLog.h"
#include "AudioChannel.h"
#include "MyPlayerStatus.h"

extern "C"
{
#include "libavformat/avformat.h"
#include <libavutil/time.h>
}


class MusicPlayer {

public:
    MusicPlayer(JavaVM *_javaVM, JNIEnv *_env, jobject &_jobj);

    ~MusicPlayer();

public:
    char *path = NULL;
    JavaCallHelper *helper = NULL;
    AudioChannel *audio = NULL;
    MyPlayerStatus *playerStatus = NULL;
public:
    pthread_t decodeThread;
    pthread_mutex_t init_mutex;
    pthread_mutex_t seek_mutex;
    AVFormatContext *avFormatContext = NULL;
    bool exit = false;
    int duration = 0;
private:


public:
    void setDataSource(const char *path);

    void prepare();

    void start();

    void onResume();

    void onPause();

    void release();

    void decodeFFmpegThread();

    void seek(int64_t seconds);
};


#endif //MYMUSICPLAYER_MUSICPLAYER_H
