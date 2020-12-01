//
// Created by tck on 2020/11/26.
//

#include "JavaCallHelper.h"

JavaCallHelper::JavaCallHelper(JavaVM *_javaVM, JNIEnv *_env, jobject &_jobj) : javaVM(_javaVM),
                                                                                env(_env) {
    jobj = env->NewGlobalRef(_jobj);
    jclass jclazz = env->GetObjectClass(jobj);
    jmid_prepare = env->GetMethodID(jclazz, "onCallJavaPrepared", "()V");
    jmid_onload = env->GetMethodID(jclazz, "onCallLoad", "(Z)V");
    jmid_audio_info = env->GetMethodID(jclazz, "onCallAudioTimeInfo", "(II)V");

}

JavaCallHelper::~JavaCallHelper() {
    env->DeleteGlobalRef(jobj);
    jobj = nullptr;
}

void JavaCallHelper::onCallJavaPrepared(int thread) {
    if (thread == THREAD_CHILD) {
        JNIEnv *jniEnv;
        if (javaVM->AttachCurrentThread(&jniEnv, NULL) != JNI_OK) {
            if (LOG_DEBUG) {
                LOGE("get child thread jnienv worng");
            }
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_prepare);
        javaVM->DetachCurrentThread();
    } else {
        env->CallVoidMethod(jobj, jmid_prepare);
    }
}

void JavaCallHelper::onCallOnLoad(bool load, int thread) {
    if (thread == THREAD_CHILD) {
        JNIEnv *jniEnv;
        if (javaVM->AttachCurrentThread(&jniEnv, NULL) != JNI_OK) {
            if (LOG_DEBUG) {
                LOGE("get child thread jnienv worng");
            }
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_onload, load);
        javaVM->DetachCurrentThread();
    } else {
        env->CallVoidMethod(jobj, jmid_onload, load);
    }
}

void JavaCallHelper::onCallAudioTimeInfo(int curr, int total, int thread) {
    if (thread == THREAD_CHILD) {
        JNIEnv *jniEnv;
        if (javaVM->AttachCurrentThread(&jniEnv, NULL) != JNI_OK) {
            if (LOG_DEBUG) {
                LOGE("get child thread jnienv worng");
            }
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_audio_info, curr, total);
        javaVM->DetachCurrentThread();
    } else {
        env->CallVoidMethod(jobj, jmid_audio_info, curr, total);
    }
}

