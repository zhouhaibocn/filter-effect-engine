//
// Created by zhouhaibo on 2017/9/20.
//

#ifndef FILTERENGINE_MATHMATIC_H
#define FILTERENGINE_MATHMATIC_H

#include "common/common.h"

/**
 * 计算滤镜强度值, 线性变换
 * @param intensity 输入值[0.0, 1.0]
 * @param minValue 滤镜最小值
 * @param defaultValue 滤镜默认值, 无滤镜效果
 * @param maxValue 滤镜最大值
 * @return 当前滤镜设定值
 */
float caculateIntensity(float intensity, float minValue, float defaultValue, float maxValue);

/**
 * 计算Bin真实数据长度
 * @param dataBuf 数据指针
 * @param dataLength  数据长度
 * @return  返回真实数据长度
 */
size_t caculateBinDataLength(uint8_t * dataBuf, size_t dataLength);

#endif //FILTERENGINE_MATHMATIC_H
