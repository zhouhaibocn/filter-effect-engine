//
// Created by zhouhaibo on 2017/9/27.
//

#include "picture_decoder.h"

int pic_decode(const char *filePath, int *width, int *height, unsigned char **rgbaBuf) {

    if (NULL == filePath) {
        return -1;
    }

    av_register_all();
    avcodec_register_all();

    AVFormatContext *pFormatCtx = NULL;
    AVCodecContext *videoCodecCtx = NULL;
    AVCodec *videoCodec = NULL;
    AVFrame *videoFrame = NULL;

    int videoStreamIndex = -1;

    pFormatCtx = avformat_alloc_context();
    if (pFormatCtx == NULL) {
        LOGE("Alloc avformat_context Error");
        return -1;
    }

    if (avformat_open_input(&pFormatCtx, filePath, NULL, NULL) != 0) {
        LOGE("avformat_open_input Error");
        return -1;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL ) < 0) {
        LOGE("avformat_find_stream_info Error");
        return -1;
    }

    videoStreamIndex = -1;
    for(int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }
    if(videoStreamIndex == -1) {
        LOGE("Input Video File Has No Video Streams");
        return -1;
    }

    videoCodec = avcodec_find_decoder(pFormatCtx->streams[videoStreamIndex]->codec->codec_id);
    if( videoCodec == NULL ) {
        LOGE("avcodec_find_decoder Error");
        return -1;
    }

    videoCodecCtx = avcodec_alloc_context3(videoCodec);
    if (avcodec_copy_context(videoCodecCtx, pFormatCtx->streams[videoStreamIndex]->codec) != 0) {
        LOGE("Couldn't copy codec context");
        return -1;
    }

    if(avcodec_open2(videoCodecCtx, videoCodec, NULL) < 0) {
        LOGE("avcodec_open2 Error");
        return -1;
    }

    AVPacket packet;
    av_init_packet(&packet);

    if (videoFrame == NULL) {
        videoFrame = av_frame_alloc();
    }

    int got_picture = 0;
    bool finished = false;
    int ret = 0;
    while(!finished) {
        ret = av_read_frame(pFormatCtx, &packet);
        if (ret < 0) {
            LOGE("av_read_frame return an error");
            if (ret != AVERROR_EOF) {
                LOGE("av_read_frame return an not AVERROR_EOF error");
            } else {
                LOGI("video EOF");
            }
            av_free_packet(&packet);
            break;
        }

        if (packet.stream_index == videoStreamIndex) {
            int len = avcodec_decode_video2(videoCodecCtx, videoFrame, &got_picture, &packet);
            if (len < 0) {
                LOGI("decode video error, skip packet");
            }
            if (got_picture) {
                finished = true;
            }
        }

        av_free_packet(&packet);
    }

    if (!finished) {
        return -1;
    }

    // 格式转换
    if (AV_PIX_FMT_RGBA != videoFrame->format) {
        LOGI("Pic Frame Pix Format is not RGBA(%d), Format: %d", AV_PIX_FMT_RGBA, videoFrame->format );
        LOGI("need convert pix format");
        SwsContext *pSwsCtx;
        pSwsCtx = sws_getContext(videoCodecCtx->width, videoCodecCtx->height,
                                 videoCodecCtx->pix_fmt, videoCodecCtx->width,
                                 videoCodecCtx->height, AV_PIX_FMT_RGBA, SWS_BICUBIC, NULL, NULL,
                                 NULL);

        if (NULL == pSwsCtx) {
            LOGE("sws_getContext Error");
        }
        AVPicture picture;
        avpicture_alloc(&picture,AV_PIX_FMT_RGBA, videoCodecCtx->width, videoCodecCtx->height);
        sws_scale(pSwsCtx, (const unsigned char* const*)videoFrame->data, videoFrame->linesize, 0, videoFrame->height,
                  picture.data, picture.linesize);
        LOGI("picture linesize : %d, frame linesize : %d", picture.linesize[0], videoFrame->linesize[0]);
        *width = videoCodecCtx->width;
        *height = videoCodecCtx->height;
        *rgbaBuf = (unsigned char *)malloc(sizeof(unsigned char) * 4 * videoCodecCtx->width * videoCodecCtx->height);
        memcpy(*rgbaBuf, picture.data[0], sizeof(unsigned char) * 4 * videoCodecCtx->width * videoCodecCtx->height);
        sws_freeContext(pSwsCtx);
    } else {
        *width = videoCodecCtx->width;
        *height = videoCodecCtx->height;
        *rgbaBuf = (unsigned char *)malloc(sizeof(unsigned char) * 4 * videoCodecCtx->width * videoCodecCtx->height);

        for(int i = 0; i < videoCodecCtx->height; i++) {
            memcpy(*rgbaBuf + i * videoCodecCtx->width * 4, videoFrame->data[0] + i * videoFrame->linesize[0], videoCodecCtx->width * 4);
        }
        //memcpy(*rgbaBuf, videoFrame->data[0], sizeof(unsigned char) * 4 * videoCodecCtx->width * videoCodecCtx->height);
    }

    if (NULL != videoFrame) {
        av_frame_free(&videoFrame);
        videoFrame = NULL;
    }

    if (NULL != videoCodecCtx) {
        avcodec_close(videoCodecCtx);
    }

    if (NULL != pFormatCtx) {
        avformat_close_input(&pFormatCtx);
        avformat_free_context(pFormatCtx);
        pFormatCtx = NULL;
    }

    return 0;
}