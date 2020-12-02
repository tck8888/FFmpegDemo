#include <jni.h>
#include <string>
#include <android/native_window_jni.h>
#include <zconf.h>
#include "MusicPlayer.h"
#include "JavaCallHelper.h"
#include "MyPlayerStatus.h"

extern "C" {
#include "libavcodec/avcodec.h"
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavformat/avformat.h>
}

JavaVM *_JavaVM = nullptr;

extern "C" jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    _JavaVM = vm;
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_tck_player_MyMusicPlayer_setDataSource(JNIEnv *env, jobject thiz, jlong native_handle,
                                                jstring path_) {

    auto *player = reinterpret_cast<MusicPlayer *>(native_handle);
    if (player == NULL) {
        return;
    }
    const char *path = env->GetStringUTFChars(path_, nullptr);

    player->setDataSource(path);
    env->ReleaseStringUTFChars(path_, path);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_tck_player_MyMusicPlayer_nativePrepare(JNIEnv *env, jobject thiz, jlong native_handle) {
    auto *player = reinterpret_cast<MusicPlayer *>(native_handle);
    if (player == NULL) {
        return;
    }
    player->prepare();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_tck_player_MyMusicPlayer_nativeStart(JNIEnv *env, jobject thiz, jlong native_handle) {
    auto *player = reinterpret_cast<MusicPlayer *>(native_handle);
    if (player == NULL) {
        return;
    }
    player->start();
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_tck_player_MyMusicPlayer_nativeInit(JNIEnv *env, jobject thiz) {
    auto *player = new MusicPlayer(_JavaVM, env, thiz);
    player->setPlayerStatus(new MyPlayerStatus());
    return (jlong) player;
}extern "C"
JNIEXPORT void JNICALL
Java_com_tck_player_MyMusicPlayer_nativePause(JNIEnv *env, jobject thiz, jlong native_handle) {
    auto *player = reinterpret_cast<MusicPlayer *>(native_handle);
    player->onPause();
}extern "C"
JNIEXPORT void JNICALL
Java_com_tck_player_MyMusicPlayer_nativeResume(JNIEnv *env, jobject thiz, jlong native_handle) {
    auto *player = reinterpret_cast<MusicPlayer *>(native_handle);
    if (player == NULL) {
        return;
    }
    player->onResume();
}extern "C"
JNIEXPORT jlong JNICALL
Java_com_tck_player_MyMusicPlayer_nativeStop(JNIEnv *env, jobject thiz, jlong native_handle) {
    auto *player = reinterpret_cast<MusicPlayer *>(native_handle);
    if (player == NULL) {
        return 0;
    }
    player->release();

    delete player;
    player = NULL;
    return 0;
}