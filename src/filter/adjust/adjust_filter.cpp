//
// Created by zhouhaibo on 2017/9/20.
//

#include "adjust_filter.h"

static ConstString Adjust_Default_VSH = GLES_SHADER_STRING(
        attribute vec2 aPosition;
        attribute vec2 aTexCoord;
        varying vec2 textureCoordinate;

        void main() {
            gl_Position = vec4(aPosition, 0.0, 1.0);
            textureCoordinate = aTexCoord;
        }
);

/**
 * brightness: 亮度, 理论取值[-1.0, 1.0], 实际限制取值为[-0.4, 0.4], 默认0.0, PS: 输入范围为[0.0, 1.0], 默认输入为0.5
 * contrast: 对比度, 理论取值[0.0, 2.0], 实际限制取值为[0.5, 1.5], 默认1.0, PS: 输入范围为[0.0, 1.0], 默认输入为0.5
 * exposure: 曝光度, 取值[-1.0, 1.0], 默认0.0,  PS: 输入范围为[0.0, 1.0], 默认输入为0.5
 * hue: 色调, 取值[-5.0, 5.0], 默认0.0, PS: 输入范围为[0.0, 1.0], 默认输入为0.5
 * sharpen: 锐化, 取值[-0.5, 8.0], 默认1.0, PS: 输入范围为[0.0, 1.0], 默认输入为0.5
 * saturation: 饱和度, 取值[0.0, 10.0], 实际限制取值为[0.0, 2.0], 默认1.0, PS: 输入范围为[0.0, 1.0], 默认输入为0.5
 */
static ConstString Adjust_Default_FSH = GLES_SHADER_STRING_PRECISION_H(
        varying vec2 textureCoordinate;
        uniform sampler2D inputImageTexture;
        uniform float brightness;
        uniform float contrast;
        uniform float exposure;
        uniform float hue;
        uniform float sharpen;
        uniform float saturation;
        uniform float width;
        uniform float height;

        vec3 rgb2yiq(vec3 src) {
            return src * mat3(0.299,     0.587,     0.114,
                              0.595716, -0.274453, -0.321263,
                              0.211456, -0.522591,  0.31135);
        }

        vec3 yiq2rgb(vec3 src) {
            return src * mat3(1.0,  0.9563,  0.6210,
                              1.0, -0.2721, -0.6474,
                              1.0, -1.1070,  1.7046);
        }

        void main() {
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            // brightness
            textureColor = vec4((textureColor.rgb + vec3(brightness)), textureColor.w);

            // contrast
            textureColor = vec4(((textureColor.rgb - vec3(0.5)) * contrast + vec3(0.5)), textureColor.a);

            // exposure
            textureColor = vec4(textureColor.rgb * exp2(exposure), textureColor.a);

            // hue
            vec3 yiq = rgb2yiq(textureColor.rgb);
            float hueTmp = atan(yiq.z, yiq.y);
            float chroma = length(yiq.yz);
            hueTmp -= hue;
            yiq.yz = vec2(cos(hueTmp), sin(hueTmp)) * chroma;
            textureColor = vec4(yiq2rgb(yiq), textureColor.a);

            // sharpen
            vec4 tmp = textureColor;
            float blurSamplerScale = 1.0f;
            vec2 samplerSteps = vec2(1.0/width, 1.0/height);
            tmp += texture2D(inputImageTexture, textureCoordinate + blurSamplerScale * vec2(-samplerSteps.x, 0.0));
            tmp += texture2D(inputImageTexture, textureCoordinate + blurSamplerScale * vec2(samplerSteps.x, 0.0));
            tmp += texture2D(inputImageTexture, textureCoordinate + blurSamplerScale * vec2(0.0, -samplerSteps.y));
            tmp += texture2D(inputImageTexture, textureCoordinate + blurSamplerScale * vec2(0.0, samplerSteps.y));

            tmp += texture2D(inputImageTexture, textureCoordinate + blurSamplerScale * samplerSteps);
            tmp += texture2D(inputImageTexture, textureCoordinate - blurSamplerScale * samplerSteps);
            tmp += texture2D(inputImageTexture, textureCoordinate + blurSamplerScale * vec2(-samplerSteps.x, samplerSteps.y));
            tmp += texture2D(inputImageTexture, textureCoordinate + blurSamplerScale * vec2(samplerSteps.x, -samplerSteps.y));
            textureColor = mix(tmp / 9.0, textureColor, sharpen);

            // saturation
            float lum = (max(max(textureColor.r, textureColor.g),textureColor.b) + min(min(textureColor.r, textureColor.g), textureColor.b)) / 2.0;
            textureColor = vec4(mix(vec3(lum), textureColor.rgb, saturation), textureColor.a);

            gl_FragColor = textureColor;
        }
);



AdjustFilter::AdjustFilter() {
    mBrightnessIntensity = 0.0f;
    mContrastIntensity = 0.0f;
    mExposureIntensity = 0.0f;
    mHueIntensity = 0.0f;
    mSharpenIntensity = 0.0f;
    mSaturationIntensity = 0.0f;
    mProgramId = 0;
    mTextureCoords = -1;
    mVertexCoords = -1;
    mTextureHandle = -1;
    mBrightnessIntensityHandle = -1;
    mContrastIntensityHandle = -1;
    mExposureIntensityHandle = -1;
    mHueIntensityHandle = -1;
    mSharpenIntensityHandle = -1;
    mSaturationIntensityHandle = -1;

    mVertexShader = Adjust_Default_VSH;
    mFragmentShader = Adjust_Default_FSH;
}

AdjustFilter::~AdjustFilter() {

}

void AdjustFilter::init() {
    // 创建GL程序
    mProgramId = loadProgram(mVertexShader, mFragmentShader);
    if (mProgramId == 0) {
        LOGE("create gl program error");
    }

    // 顶点坐标
    mVertexCoords = glGetAttribLocation(mProgramId, "aPosition");
    checkGlError("glGetAttribLocation aPosition");
    if (mVertexCoords == -1) {
        LOGE("glGetAttribLocation aPosition error");
    }

    // 纹理坐标
    mTextureCoords = glGetAttribLocation(mProgramId, "aTexCoord");
    checkGlError("glGetAttribLocation aTexCoord");
    if (mTextureCoords == -1) {
        LOGE("glGetAttribLocation aTexCoord error");
    }

    // 纹理
    mTextureHandle = glGetUniformLocation(mProgramId, "inputImageTexture");
    checkGlError("glGetUniformLocation inputImageTexture");
    if (mTextureHandle == -1) {
        LOGE("glGetUniformLocation inputImageTexture error");
    }

    // 亮度
    mBrightnessIntensityHandle = glGetUniformLocation(mProgramId, "brightness");
    checkGlError("glGetUniformLocation brightness");
    if (mBrightnessIntensityHandle == -1) {
        LOGE("glGetUniformLocation mBrightnessIntensityHandle error");
    }

    // 对比度
    mContrastIntensityHandle = glGetUniformLocation(mProgramId, "contrast");
    checkGlError("glGetUniformLocation contrast");
    if (mContrastIntensityHandle == -1) {
        LOGE("glGetUniformLocation mContrastIntensityHandle error");
    }

    // 曝光
    mExposureIntensityHandle = glGetUniformLocation(mProgramId, "exposure");
    checkGlError("glGetUniformLocation exposure");
    if (mExposureIntensityHandle == -1) {
        LOGE("glGetUniformLocation mExposureIntensityHandle error");
    }

    // 色调
    mHueIntensityHandle = glGetUniformLocation(mProgramId, "hue");
    checkGlError("glGetUniformLocation hue");
    if (mHueIntensityHandle == -1) {
        LOGE("glGetUniformLocation mHueIntensityHandle error");
    }

    // 锐化
    mSharpenIntensityHandle = glGetUniformLocation(mProgramId, "sharpen");
    checkGlError("glGetUniformLocation sharpen");
    if (mSharpenIntensityHandle == -1) {
        LOGE("glGetUniformLocation mSharpenIntensityHandle error");
    }

    // 饱和度
    mSaturationIntensityHandle = glGetUniformLocation(mProgramId, "saturation");
    checkGlError("glGetUniformLocation saturation");
    if (mSaturationIntensityHandle == -1) {
        LOGE("glGetUniformLocation mSaturationIntensityHandle error");
    }

    mWidthHandle = glGetUniformLocation(mProgramId, "width");
    checkGlError("glGetUniformLocation width");
    if (mWidthHandle == -1) {
        LOGE("glGetUniformLocation mWidthHandle error");
    }

    mHeightHandle = glGetUniformLocation(mProgramId, "height");
    checkGlError("glGetUniformLocation height");
    if (mHeightHandle == -1) {
        LOGE("glGetUniformLocation mHeightHandle error");
    }

    // default value
    mBrightnessIntensity = 0.0f;
    mContrastIntensity = 1.0f;
    mExposureIntensity = 0.0f;
    mHueIntensity = 0.0f;
    mSharpenIntensity = 1.0f;
    mSaturationIntensity = 1.0f;
}

void AdjustFilter::setParam(int type, float intensity) {
    switch (type) {
        case ADJUST_FILTER_BRIGHTNESS_INTENSITY:
            mBrightnessIntensity = (intensity * 2.0f - 1.0f) * 0.4f;;
            break;
        case ADJUST_FILTER_CONTRAST_INTENSITY:
            mContrastIntensity = intensity + 0.5f;;
            break;
        case ADJUST_FILTER_EXPOSURE_INTENSITY:
            mExposureIntensity = (intensity - 0.5f) * 2.0f;
            break;
        case ADJUST_FILTER_HUE_INTENSITY:
            mHueIntensity = (intensity - 0.5f) * 10.0f;
            break;
        case ADJUST_FILTER_SHARPEN_INTENSITY:
            mSharpenIntensity = caculateIntensity(intensity, -0.5f, 1.0f, 8.0f);
            break;
        case ADJUST_FILTER_SATURATION_INTENSITY:
            mSaturationIntensity = caculateIntensity(intensity, 0.8f, 1.0f, 1.2f);
            break;
        case ADJUST_FILTER_NONE:
        default:
            break;
    }
}

void AdjustFilter::process(GLuint textureId, int width, int height) {
    glUseProgram(mProgramId);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0);

    // 顶点数据
    glVertexAttribPointer(mVertexCoords, 2, GL_FLOAT, 0, 0, VERTICE_NO_ROTATION);
    checkGlError("glVertexAttribPointer aPosition");
    glEnableVertexAttribArray(mVertexCoords);
    checkGlError("glEnableVertexAttribArray mVertexCoords");

    // 纹理数据
    glVertexAttribPointer(mTextureCoords, 2, GL_FLOAT, 0, 0, TEXTURE_NO_ROTATION);
    checkGlError("glVertexAttribPointer aTexCoord");
    glEnableVertexAttribArray(mTextureCoords);
    checkGlError("glEnableVertexAttribArray mTextureCoords");

    // 亮度
    glUniform1f(mBrightnessIntensityHandle, mBrightnessIntensity);

    // 对比度
    glUniform1f(mContrastIntensityHandle, mContrastIntensity);

    // 曝光
    glUniform1f(mExposureIntensityHandle, mExposureIntensity);

    // 色调
    glUniform1f(mHueIntensityHandle, mHueIntensity);

    // 锐化
    glUniform1f(mSharpenIntensityHandle, mSharpenIntensity);

    // 饱和度
    glUniform1f(mSaturationIntensityHandle, mSaturationIntensity);

    glUniform1f(mWidthHandle, width);
    glUniform1f(mHeightHandle, height);

    // 渲染
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(mTextureHandle, 0);

    // draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawArrays");

    // unbind
    glDisableVertexAttribArray(mVertexCoords);
    glDisableVertexAttribArray(mTextureCoords);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void AdjustFilter::destroy() {
    if (mProgramId != 0) {
        glDeleteProgram(mProgramId);
        checkGlError("glDeleteProgram mProgramId");
    }
}