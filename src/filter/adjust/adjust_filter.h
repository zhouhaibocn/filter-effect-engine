//
// Created by zhouhaibo on 2017/9/20.
//

#ifndef FILTERENGINE_ADJUST_FILTER_H
#define FILTERENGINE_ADJUST_FILTER_H

#include "common/filter_interface.h"
#include "utils/common_utils.h"

/** 基础调节滤镜参数类型 */
enum AdjustFilterParamsType {
    ADJUST_FILTER_NONE,
    ADJUST_FILTER_BRIGHTNESS_INTENSITY,
    ADJUST_FILTER_CONTRAST_INTENSITY,
    ADJUST_FILTER_EXPOSURE_INTENSITY,
    ADJUST_FILTER_HUE_INTENSITY,
    ADJUST_FILTER_SHARPEN_INTENSITY,
    ADJUST_FILTER_SATURATION_INTENSITY
};

class AdjustFilter : public FilterInterface {
private:
    float mBrightnessIntensity;
    float mContrastIntensity;
    float mExposureIntensity;
    float mHueIntensity;
    float mSharpenIntensity;
    float mSaturationIntensity;
    ConstString mVertexShader;
    ConstString mFragmentShader;
    GLuint mProgramId;
    GLint mVertexCoords;;
    GLint mTextureCoords;
    GLint mTextureHandle;
    GLint mBrightnessIntensityHandle;
    GLint mContrastIntensityHandle;
    GLint mExposureIntensityHandle;
    GLint mHueIntensityHandle;
    GLint mSharpenIntensityHandle;
    GLint mSaturationIntensityHandle;
    GLint mWidthHandle;
    GLint mHeightHandle;

public:
    AdjustFilter();

    ~AdjustFilter();

    void init();

    void setParam(int type, float intensity);

    void process(GLuint textureId, int width, int height);

    void destroy();

};


#endif //FILTERENGINE_ADJUST_FILTER_H
