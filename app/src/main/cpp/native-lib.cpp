#include <jni.h>
#include <string>
#include <android/native_window_jni.h>
#include <zconf.h>
#include "MusicPlayer.h"
#include "JavaCallHelper.h"

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

    const char *path = env->GetStringUTFChars(path_, nullptr);

    auto *player = reinterpret_cast<MusicPlayer *>(native_handle);
    player->setDataSource(path);
    env->ReleaseStringUTFChars(path_, path);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_tck_player_MyMusicPlayer_nativePrepare(JNIEnv *env, jobject thiz, jlong native_handle) {
    auto *player = reinterpret_cast<MusicPlayer *>(native_handle);
    player->prepare();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_tck_player_MyMusicPlayer_nativeStart(JNIEnv *env, jobject thiz, jlong native_handle) {
    auto *player = reinterpret_cast<MusicPlayer *>(native_handle);
    player->start();
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_tck_player_MyMusicPlayer_nativeInit(JNIEnv *env, jobject thiz) {
    auto *player = new MusicPlayer(new JavaCallHelper(_JavaVM, env, thiz));
    return (jlong) player;
}