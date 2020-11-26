//
// Created by tck on 2020/11/26.
//

#ifndef MYMUSICPLAYER_ANDROIDLOG_H
#define MYMUSICPLAYER_ANDROIDLOG_H

#include "android/log.h"

#define LOG_DEBUG true
#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"tck6666",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"tck6666",FORMAT,##__VA_ARGS__);

#endif //MYMUSICPLAYER_ANDROIDLOG_H
