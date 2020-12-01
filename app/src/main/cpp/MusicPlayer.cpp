//
// Created by tck on 2020/11/26.
//

#include "MusicPlayer.h"
#include <cstring>
#include <malloc.h>


MusicPlayer::MusicPlayer(JavaCallHelper *_helper) : helper(_helper) {

}

void MusicPlayer::setPlayerStatus(MyPlayerStatus *_pStatus) {
    this->playerStatus = _pStatus;
}

MusicPlayer::~MusicPlayer() {
    delete path;
    path = nullptr;
}

void MusicPlayer::setDataSource(const char *path_) {
    path = new char[strlen(path_) + 1];
    strcpy(path, path_);
}

void *decodeFFmpeg(void *data) {
    auto *player = (MusicPlayer *) data;
    player->decodeFFmpegThread();
    pthread_exit(&player->decodeThread);
    return nullptr;
}

void MusicPlayer::decodeFFmpegThread() {

    avformat_network_init();

    avFormatContext = avformat_alloc_context();
    if (avformat_open_input(&avFormatContext, path, nullptr, nullptr) != 0) {
        if (LOG_DEBUG) {
            LOGE("can not open url :%s", path);
            return;
        }
    }

    if (avformat_find_stream_info(avFormatContext, nullptr) < 0) {
        if (LOG_DEBUG) {
            LOGE("can not find streams from %s", path);
            return;
        }
    }

    for (int i = 0; i < avFormatContext->nb_streams; ++i) {
        if (avFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            if (audio == nullptr) {
                audio = new AudioChannel(this->playerStatus,
                                         avFormatContext->streams[i]->codecpar->sample_rate,helper);
                audio->streamIndex = i;
                audio->codecpar = avFormatContext->streams[i]->codecpar;
                break;
            }
        }
    }
    if (!audio) {
        if (LOG_DEBUG) {
            LOGE("audio = nullptr");
        }
        return;
    }

    AVCodec *avCodec = avcodec_find_decoder(audio->codecpar->codec_id);
    if (!avCodec) {
        if (LOG_DEBUG) {
            LOGE("can not find decoder");
        }
        return;
    }
    audio->avCodecContext = avcodec_alloc_context3(avCodec);
    if (!audio->avCodecContext) {
        if (LOG_DEBUG) {
            LOGE("can not alloc new decodecctx");
        }
        return;
    }

    if (avcodec_parameters_to_context(audio->avCodecContext, audio->codecpar) < 0) {
        if (LOG_DEBUG) {
            LOGE("can not fill decodecctx");
        }
        return;
    }

    if (avcodec_open2(audio->avCodecContext, avCodec, nullptr) != 0) {
        if (LOG_DEBUG) {
            LOGE("cant not open audio strames");
        }
        return;
    }

    helper->onCallJavaPrepared(THREAD_CHILD);

}

void MusicPlayer::prepare() {
    pthread_create(&decodeThread, nullptr, decodeFFmpeg, this);
}

void MusicPlayer::start() {

    if (audio == NULL) {
        if (LOG_DEBUG) {
            LOGE("audio = nullptr");
        }
        return;
    }
    audio->play();

    int count = 0;
    while (playerStatus != nullptr && !playerStatus->exit) {
        AVPacket *avPacket = av_packet_alloc();
        if (av_read_frame(avFormatContext, avPacket) == 0) {
            if (avPacket->stream_index == audio->streamIndex) {
                //解码操作
                count++;
//                if (LOG_DEBUG) {
//                    LOGE("解码第 %d 帧", count);
//                }
                audio->queue->putAvPacket(avPacket);
            } else {
                av_packet_free(&avPacket);
                av_free(avPacket);
            }
        } else {
            av_packet_free(&avPacket);
            av_free(avPacket);
            while (playerStatus != nullptr && !playerStatus->exit) {
                if (audio->queue->getQueueSize() > 0) {
                    continue;
                } else {
                    playerStatus->exit = true;
                    break;
                }
            }
        }
    }

    if (LOG_DEBUG) {
        LOGD("解码完成");
    }
}

void MusicPlayer::onResume() {
    if (audio != NULL) {
        audio->onResume();
    }
}

void MusicPlayer::onPause() {
    if (audio != NULL) {
        audio->onPause();
    }
}








