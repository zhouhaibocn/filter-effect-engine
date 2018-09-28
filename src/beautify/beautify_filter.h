//
// Created by zhouhaibo on 2017/9/19.
//

#ifndef FILTERENGINE_BEAUTIFY_FILTER_H
#define FILTERENGINE_BEAUTIFY_FILTER_H

#include "common/filter_interface.h"

/** 美颜参数类型 */
enum BeautifyParamsType {
    BEAUTIFY_NONE,
    BEAUTIFY_WHITEN_INTENSITY,
    BEAUTIFY_SMOOTH_INTENSITY,
    BEAUTIFY_REDDEN_INTENSITY
};

class BeautifyFilter : public  FilterInterface {
private:
    float mWhitenIntensity;
    float mSmoothIntensity;
    float mReddenIntensity;
    ConstString mVertexShader;
    ConstString mFragmentShader;
    GLuint mProgramId;
    GLint mVertexCoords;;
    GLint mTextureCoords;
    GLint mTextureHandle;
    GLint mWhitenIntensityHandle;
    GLint mSmoothIntensityHandle;
    GLint mReddenIntensityHandle;
    GLint mWidthHandle;
    GLint mHeightHandle;

public:
    BeautifyFilter();

    ~BeautifyFilter();

    void init();

    void setParam(int type, float intensity);

    void process(GLuint textureId, int width, int height);

    void destroy();
};


#endif //FILTERENGINE_BEAUTIFY_FILTER_H
