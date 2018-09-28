//
// Created by zhouhaibo on 2017/8/1.
//

#ifndef FILTERENGINE_PIC_DECODER_H
#define FILTERENGINE_PIC_DECODER_H

#include "common/common.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/time.h>
#include <libavutil/frame.h>
#include <libswscale/swscale.h>
}

int pic_decode(const char *filePath, int *width, int *height, unsigned char **rgbaBuf);

#endif //FILTERENGINE_PIC_DECODER_H
