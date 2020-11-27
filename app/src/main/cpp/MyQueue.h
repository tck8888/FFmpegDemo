//
// Created by tck on 2020/11/27.
//

#ifndef MYMUSICPLAYER_MYQUEUE_H
#define MYMUSICPLAYER_MYQUEUE_H

#include "queue"
#include "pthread.h"
#include "AndroidLog.h"
#include "MyPlayerStatus.h"

extern "C"
{
#include "libavcodec/avcodec.h"
};


class MyQueue {

public:
    MyPlayerStatus *playerStatus = nullptr;
    pthread_mutex_t mutexPacket;
    pthread_cond_t condPacket;
    std::queue<AVPacket *> queuePacket;

public:
    MyQueue(MyPlayerStatus *_playerStatus);

    ~MyQueue();

public:
    int putAvPacket(AVPacket *packet);

    int getAvPacket(AVPacket *packet);

    int getQueueSize();
};


#endif //MYMUSICPLAYER_MYQUEUE_H
