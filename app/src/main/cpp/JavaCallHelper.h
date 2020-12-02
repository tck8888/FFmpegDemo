//
// Created by tck on 2020/11/26.
//

#ifndef MYMUSICPLAYER_JAVACALLHELPER_H
#define MYMUSICPLAYER_JAVACALLHELPER_H


#include <jni.h>
#include "AndroidLog.h"

//标记线程 因为子线程需要attach
#define THREAD_MAIN 1
#define THREAD_CHILD 2

class JavaCallHelper {

public:
    JavaCallHelper(JavaVM *_javaVM, JNIEnv *_env, jobject &_jobj);

    ~JavaCallHelper();

public:
    JavaVM *javaVM;
    JNIEnv *env;
    jobject jobj;
    jmethodID jmid_prepare;
    jmethodID jmid_onload;
    jmethodID jmid_audio_info;
    jmethodID jmid_error;
    jmethodID jmid_complete;

public:
    void onCallJavaPrepared(int thread);

    void onCallOnLoad(bool load, int thread);

    void onCallAudioTimeInfo(int curr, int total, int thread);

    void onCallOnError(int code, const char *msg, int thread = THREAD_CHILD);
    void onCallOnComplete(int thread = THREAD_CHILD);

};


#endif //MYMUSICPLAYER_JAVACALLHELPER_H
