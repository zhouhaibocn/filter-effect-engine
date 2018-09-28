//
// Created by zhouhaibo on 2017/9/20.
//

#include "multi_input_filter.h"

static ConstString MULTI_INPUT_Default_VSH = GLES_SHADER_STRING(
        attribute vec2 aPosition;
        attribute vec2 aTexCoord;
        varying vec2 textureCoordinate;

        void main() {
            gl_Position = vec4(aPosition, 0.0, 1.0);
            textureCoordinate = aTexCoord;
        }
);

static ConstString MULTI_INPUT_Default_FSH = GLES_SHADER_STRING_PRECISION_H(
        varying vec2 textureCoordinate;
        uniform sampler2D inputImageTexture;
        void main() {
            gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
        }
);

MultiInputFilter::MultiInputFilter() {
    mIsInitialized = false;
    mProgramId = 0;
    mTextureCoords = -1;
    mVertexCoords = -1;
    mTextureHandle = -1;

    mInputImageHandle = NULL;
    mInputTexture = NULL;

    mInputImageNum = 0;

    mVertexShader = MULTI_INPUT_Default_VSH;
    mFragmentShader = MULTI_INPUT_Default_FSH;

}

MultiInputFilter::~MultiInputFilter() {
    if (mIsInitialized) {
        destroy();
    }
}

void MultiInputFilter::init(FilterConfig *filterConfig) {
    if (NULL == filterConfig) {
        return;
    }

    mInputImageNum = filterConfig->num;

    if (mInputImageNum == 1) {
        mInputImageHandle = new GLint(-1);
        mInputTexture = new GLuint(0);
    } else if (mInputImageNum > 1) {
        mInputImageHandle = new GLint[mInputImageNum];
        mInputTexture = new GLuint[mInputImageNum];
    }

    for (int i = 0; i < filterConfig->num; i++) {
        switch (filterConfig->data[i].type) {
            case Type_Bin_Data:
                mInputTexture[i] = loadTextureFromBin(filterConfig->data[i].name);
                break;
            case Type_Png_Data:
                mInputTexture[i] = loadTextureFromPng(filterConfig->data[i].name);
                break;
            case Type_None:
                break;
        }
    }

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
        LOGE("glGetUniformLocation mTextureHandle error");
    }

    // inputImage
    for (int i = 0; i < mInputImageNum; i ++) {
        char str[30] = {0} ;
        sprintf(str, "inputImageTexture%d\0", i + 1);
        mInputImageHandle[i] = glGetUniformLocation(mProgramId, str);
        checkGlError("glGetUniformLocation inputImageTexture1");
        if (mInputImageHandle[i] == -1) {
            LOGE("glGetUniformLocation mInputImageHandle error");
        }
    }

    mIsInitialized = true;
}

void MultiInputFilter::process(GLuint textureId, int width, int height) {
    if (mIsInitialized) {
        internalPreProcess(textureId);
        internalDraw(width, height);
    }
}

void MultiInputFilter::internalPreProcess(GLuint textureId) {
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

    // 渲染
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(mTextureHandle, 0);

    //
    for (int i = 0; i < mInputImageNum; i ++) {
        glActiveTexture(GL_TEXTURE1 + i);
        glBindTexture(GL_TEXTURE_2D, mInputTexture[i]);
        glUniform1i(mInputImageHandle[i], i + 1);
    }

}

void MultiInputFilter::internalDraw(int width, int height) {
    // draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawArrays");

    // unbind
    glDisableVertexAttribArray(mVertexCoords);
    glDisableVertexAttribArray(mTextureCoords);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void MultiInputFilter::destroy() {
    for (int i = 0; i < mInputImageNum; i ++) {
        if (mInputTexture[i] > 0) {
            glDeleteTextures(1, &mInputTexture[i]);
        }
    }

    if (NULL != mInputImageHandle) {
        delete mInputImageHandle;
    }

    if (NULL != mInputTexture) {
        delete mInputTexture;
    }

    if (mProgramId != 0) {
        glDeleteProgram(mProgramId);
        checkGlError("glDeleteProgram mProgramId");
    }

    mInputImageNum = 0;
    mIsInitialized = false;
}
