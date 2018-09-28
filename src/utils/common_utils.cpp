//
// Created by zhouhaibo on 2017/9/20.
//

#include "common_utils.h"

float caculateIntensity(float intensity, float minValue, float defaultValue, float maxValue) {
    float mIntensity;
    if (intensity <= 0.0) {
        mIntensity = minValue;
    } else if (intensity >= 1.0) {
        mIntensity = maxValue;
    } else if (intensity <= 0.5) {
        mIntensity = minValue + (defaultValue - minValue) * intensity * 2.0f;
    } else {
        mIntensity = maxValue + (defaultValue - maxValue) * (1.0f - intensity) * 2.0f;
    }

    return mIntensity;
}

size_t caculateBinDataLength(uint8_t * dataBuf, size_t dataLength) {
    size_t length = 0;
    if (dataLength >= 4) {
        size_t width = dataBuf[1] * 256 + dataBuf[0];
        size_t height = dataBuf[3] * 256 + dataBuf[2];
        length = width * height * 4;
    }
    return length;
}