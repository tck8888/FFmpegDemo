#include <jni.h>
#include <string>
#include <android/native_window_jni.h>
#include <zconf.h>

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
extern "C"
JNIEXPORT void JNICALL
Java_com_tck_player_MyPlayer_start(JNIEnv *env, jobject thiz, jstring path_, jobject surface) {

    ANativeWindow *aNativeWindow = ANativeWindow_fromSurface(env, surface);

    const char *path = env->GetStringUTFChars(path_, nullptr);

    avformat_network_init();
    AVFormatContext *avFormatContext = avformat_alloc_context();
    AVDictionary *avDictionary = nullptr;
    av_dict_set(&avDictionary, "timeout", "3000000", 0);

    int ret = avformat_open_input(&avFormatContext, path, nullptr, &avDictionary);
    if (ret) {
        return;
    }

    avformat_find_stream_info(avFormatContext, nullptr);

    //视频流
    int video_stream_index = -1;
    for (int i = 0; i < avFormatContext->nb_streams; ++i) {
        if (avFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            break;
        }
    }

    AVCodecParameters *avCodecParameters = avFormatContext->streams[video_stream_index]->codecpar;

    //解码器
    AVCodec *avCodec = avcodec_find_encoder(avCodecParameters->codec_id);
    //解码器上下文
    AVCodecContext *avCodecContext = avcodec_alloc_context3(avCodec);
    //解码器参数 copy到解码器上下文
    avcodec_parameters_to_context(avCodecContext, avCodecParameters);

    avcodec_open2(avCodecContext, avCodec, nullptr);

    //解码 yuv数据
    AVPacket *avPacket = av_packet_alloc();
    SwsContext *swsContext = sws_getContext(
            avCodecContext->width,
            avCodecContext->height,
            avCodecContext->pix_fmt,
            avCodecContext->width,
            avCodecContext->height,
            AV_PIX_FMT_RGBA,
            SWS_BILINEAR,
            nullptr,
            nullptr,
            nullptr
    );

    ANativeWindow_setBuffersGeometry(
            aNativeWindow,
            avCodecContext->width,
            avCodecContext->height,
            WINDOW_FORMAT_RGBA_8888
    );
    ANativeWindow_Buffer outBuffer;

    while (av_read_frame(avFormatContext, avPacket) >= 0) {
        avcodec_send_packet(avCodecContext, avPacket);
        AVFrame *avFrame = av_frame_alloc();
        ret = avcodec_receive_frame(avCodecContext, avFrame);
        if (ret == AVERROR(EAGAIN)) {
            continue;
        } else if (ret < 0) {
            break;
        }
        //接受容器
        uint8_t *dst_data[0];
        // 每一行 首地址
        int dst_lineSize[4];
        av_image_alloc(
                dst_data,
                dst_lineSize,
                avCodecContext->width,
                avCodecContext->height,
                AV_PIX_FMT_RGBA,
                1);

        sws_scale(
                swsContext,
                avFrame->data,
                avFrame->linesize,
                0,
                avFrame->height,
                dst_data,
                dst_lineSize);

        ANativeWindow_lock(
                aNativeWindow,
                &outBuffer,
                nullptr);

        //rgb_frame是有画面数据
        uint8_t *dst= (uint8_t *) outBuffer.bits;
        //拿到一行有多少个字节 RGBA
        int destStride=outBuffer.stride*4;
        uint8_t *src_data = dst_data[0];
        int src_linesize = dst_lineSize[0];
        uint8_t *firstWindown = static_cast<uint8_t *>(outBuffer.bits);

        for (int i = 0; i < outBuffer.height; ++i) {
            memcpy(firstWindown + i * destStride, src_data + i * src_linesize, destStride);
        }
        ANativeWindow_unlockAndPost(aNativeWindow);
        usleep(1000 * 16);
        av_frame_free(&avFrame);
    }
    ANativeWindow_release(aNativeWindow);
    avcodec_close(avCodecContext);
    avformat_free_context(avFormatContext);
    env->ReleaseStringUTFChars(path_, path);

}