//
// Created by zhouhaibo on 2017/9/19.
//

#include "beautify_filter.h"

static ConstString Beautify_Default_VSH = GLES_SHADER_STRING(
    attribute vec2 aPosition;
    attribute vec2 aTexCoord;
    varying vec2 textureCoordinate;

    void main() {
        gl_Position = vec4(aPosition, 0.0, 1.0);
        textureCoordinate = aTexCoord;
    }
);

//static ConstString Beautify_Default_FSH = GLES_SHADER_STRING_PRECISION_H(
//    varying vec2 textureCoordinate;
//    uniform sampler2D inputImageTexture;
//    uniform float brightness;
//    uniform float blur;
//    uniform float hue;
//    const float texelWidthOffset = 2.0f/540.0f;
//    const float texelHeightOffset = 2.0f/960.0f;
//    const vec3 W = vec3(0.299, 0.587, 0.114);
//    const mat3 saturateMatrix = mat3( 1.1102, -0.0598, -0.061,
//                                     -0.0774, 1.0826, -0.1186,
//                                     -0.0228, -0.0228, 1.1772);
//    vec2 blurCoordinates[24];
//    float hardLight(float color) {
//        if (color <= 0.5)
//            color = color * color * 2.0;
//        else
//            color = 1.0 - ((1.0 - color)*(1.0 - color) * 2.0);
//         return color;
//    }
//
//    void main() {
//        vec3 centralColor = texture2D(inputImageTexture, textureCoordinate).rgb;
//        vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);
//
//        blurCoordinates[0] = textureCoordinate.xy + singleStepOffset * vec2(0.0, -10.0);
//        blurCoordinates[1] = textureCoordinate.xy + singleStepOffset * vec2(0.0, 10.0);
//        blurCoordinates[2] = textureCoordinate.xy + singleStepOffset * vec2(-10.0, 0.0);
//        blurCoordinates[3] = textureCoordinate.xy + singleStepOffset * vec2(10.0, 0.0);
//        blurCoordinates[4] = textureCoordinate.xy + singleStepOffset * vec2(5.0, -8.0);
//        blurCoordinates[5] = textureCoordinate.xy + singleStepOffset * vec2(5.0, 8.0);
//        blurCoordinates[6] = textureCoordinate.xy + singleStepOffset * vec2(-5.0, 8.0);
//        blurCoordinates[7] = textureCoordinate.xy + singleStepOffset * vec2(-5.0, -8.0);
//        blurCoordinates[8] = textureCoordinate.xy + singleStepOffset * vec2(8.0, -5.0);
//        blurCoordinates[9] = textureCoordinate.xy + singleStepOffset * vec2(8.0, 5.0);
//        blurCoordinates[10] = textureCoordinate.xy + singleStepOffset * vec2(-8.0, 5.0);
//        blurCoordinates[11] = textureCoordinate.xy + singleStepOffset * vec2(-8.0, -5.0);
//        blurCoordinates[12] = textureCoordinate.xy + singleStepOffset * vec2(0.0, -6.0);
//        blurCoordinates[13] = textureCoordinate.xy + singleStepOffset * vec2(0.0, 6.0);
//        blurCoordinates[14] = textureCoordinate.xy + singleStepOffset * vec2(6.0, 0.0);
//        blurCoordinates[15] = textureCoordinate.xy + singleStepOffset * vec2(-6.0, 0.0);
//        blurCoordinates[16] = textureCoordinate.xy + singleStepOffset * vec2(-4.0, -4.0);
//        blurCoordinates[17] = textureCoordinate.xy + singleStepOffset * vec2(-4.0, 4.0);
//        blurCoordinates[18] = textureCoordinate.xy + singleStepOffset * vec2(4.0, -4.0);
//        blurCoordinates[19] = textureCoordinate.xy + singleStepOffset * vec2(4.0, 4.0);
//        blurCoordinates[20] = textureCoordinate.xy + singleStepOffset * vec2(-2.0, -2.0);
//        blurCoordinates[21] = textureCoordinate.xy + singleStepOffset * vec2(-2.0, 2.0);
//        blurCoordinates[22] = textureCoordinate.xy + singleStepOffset * vec2(2.0, -2.0);
//        blurCoordinates[23] = textureCoordinate.xy + singleStepOffset * vec2(2.0, 2.0);
//
//        float sampleColor = centralColor.g * 22.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[0]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[1]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[2]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[3]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[4]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[5]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[6]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[7]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[8]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[9]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[10]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[11]).g;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[12]).g * 2.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[13]).g * 2.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[14]).g * 2.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[15]).g * 2.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[16]).g * 2.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[17]).g * 2.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[18]).g * 2.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[19]).g * 2.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[20]).g * 3.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[21]).g * 3.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[22]).g * 3.0;
//        sampleColor += texture2D(inputImageTexture, blurCoordinates[23]).g * 3.0;
//
//        sampleColor = sampleColor / 62.0;
//
//        float highPass = centralColor.g - sampleColor + 0.5;
//        for (int i = 0; i < 5; i++) {
//            highPass = hardLight(highPass);
//        }
//
//        float lumance = dot(centralColor, W);
//
////        float alpha = pow(lumance, params.r);
//        float alpha = pow(lumance, blur);
//
//        vec3 smoothColor = centralColor + (centralColor - vec3(highPass)) * alpha * 0.1;
//
////        smoothColor.r = clamp(pow(smoothColor.r, params.g), 0.0, 1.0);
////        smoothColor.g = clamp(pow(smoothColor.g, params.g), 0.0, 1.0);
////        smoothColor.b = clamp(pow(smoothColor.b, params.g), 0.0, 1.0);
//        smoothColor.r = clamp(pow(smoothColor.r, blur + 0.33), 0.0, 1.0);
//        smoothColor.g = clamp(pow(smoothColor.g, blur + 0.33), 0.0, 1.0);
//        smoothColor.b = clamp(pow(smoothColor.b, blur + 0.33), 0.0, 1.0);
//
//        vec3 lvse = vec3(1.0) - (vec3(1.0) - smoothColor) * (vec3(1.0) - centralColor);
//        vec3 bianliang = max(smoothColor, centralColor);
//        vec3 rouguang = 2.0 * centralColor * smoothColor + centralColor * centralColor -
//                        2.0 * centralColor * centralColor * smoothColor;
//
//        gl_FragColor = vec4(mix(centralColor, lvse, alpha), 1.0);
//        gl_FragColor.rgb = mix(gl_FragColor.rgb, bianliang, alpha);
//        gl_FragColor.rgb = mix(gl_FragColor.rgb, rouguang, hue);
//
//        vec3 satcolor = gl_FragColor.rgb * saturateMatrix;
//        gl_FragColor.rgb = mix(gl_FragColor.rgb, satcolor, hue);
//
//        gl_FragColor.rgb = vec3(gl_FragColor.rgb + vec3(brightness));
//    }
//);


static ConstString Beautify_Simple_FSH = GLES_SHADER_STRING_PRECISION_H(
        varying vec2 textureCoordinate;
        uniform sampler2D inputImageTexture;
        uniform float brightness;
        uniform float blur;
        uniform float hue;
        uniform float width;
        uniform float height;
        const vec3 W = vec3(0.299, 0.587, 0.114);
        const mat3 saturateMatrix = mat3( 1.1102, -0.0598, -0.061,
                                          -0.0774, 1.0826, -0.1186,
                                          -0.0228, -0.0228, 1.1772);

        void main() {
            vec4 src = texture2D(inputImageTexture, textureCoordinate);

            vec4 tmp = src;
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
            gl_FragColor = mix(tmp / 9.0, src, blur);

            vec3 satcolor = gl_FragColor.rgb * saturateMatrix;
            gl_FragColor.rgb = mix(gl_FragColor.rgb, satcolor, hue);

            gl_FragColor.rgb = vec3(gl_FragColor.rgb + vec3(brightness));
        }
);



BeautifyFilter::BeautifyFilter() {
    mWhitenIntensity = 0.0f;
    mSmoothIntensity = 0.0f;
    mReddenIntensity = 0.0f;
    mProgramId = 0;
    mTextureCoords = -1;
    mVertexCoords = -1;
    mTextureHandle = -1;
    mWhitenIntensityHandle = -1;
    mSmoothIntensityHandle = -1;
    mReddenIntensityHandle = -1;

    mVertexShader = Beautify_Default_VSH;
    mFragmentShader = Beautify_Simple_FSH;
}

BeautifyFilter::~BeautifyFilter() {

}

void BeautifyFilter::init() {
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

    // 亮度-美白
    mWhitenIntensityHandle = glGetUniformLocation(mProgramId, "brightness");
    checkGlError("glGetUniformLocation brightness");
    if (mWhitenIntensityHandle == -1) {
        LOGE("glGetUniformLocation mWhitenIntensityHandle error");
    }

    // 模糊-磨皮
    mSmoothIntensityHandle = glGetUniformLocation(mProgramId, "blur");
    checkGlError("glGetUniformLocation blur");
    if (mSmoothIntensityHandle == -1) {
        LOGE("glGetUniformLocation mSmoothIntensityHandle error");
    }

    // 色调-红润
    mReddenIntensityHandle = glGetUniformLocation(mProgramId, "hue");
    checkGlError("glGetUniformLocation hue");
    if (mReddenIntensityHandle == -1) {
        LOGE("glGetUniformLocation mReddenIntensityHandle error");
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

    mWhitenIntensity = 0.0f;
    mSmoothIntensity = 0.0f;
    mReddenIntensity = 0.0f;
}

void BeautifyFilter::setParam(int type, float intensity) {
    switch (type) {
        case BEAUTIFY_WHITEN_INTENSITY:
            mWhitenIntensity = intensity * 0.15f;
            break;
        case BEAUTIFY_SMOOTH_INTENSITY:
            mSmoothIntensity = 1.0f - intensity * 1.5f;
            break;
        case BEAUTIFY_REDDEN_INTENSITY:
            mReddenIntensity = intensity * 0.6f;
            break;
        case BEAUTIFY_NONE:
        default:
            break;
    }
}

void BeautifyFilter::process(GLuint textureId, int width, int height) {
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

    // 美白
    glUniform1f(mWhitenIntensityHandle, mWhitenIntensity);

    // 磨皮
    glUniform1f(mSmoothIntensityHandle, mSmoothIntensity);

    // 红润
    glUniform1f(mReddenIntensityHandle, mReddenIntensity);

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

void BeautifyFilter::destroy() {
    if (mProgramId != 0) {
        glDeleteProgram(mProgramId);
        checkGlError("glDeleteProgram mProgramId");
    }
}