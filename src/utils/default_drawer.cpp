//
// Created by zhouhaibo on 2017/9/19.
//

#include "utils/default_drawer.h"

#define LOG_TAG "DefaultDrawer"

static ConstString Default_VSH = GLES_SHADER_STRING(
        attribute vec2 aPosition;
        attribute vec2 aTexCoord;
        varying vec2 textureCoordinate;

        void main() {
            gl_Position = vec4(aPosition, 0.0, 1.0);
            textureCoordinate = aTexCoord;
        }
);

static ConstString Default_FSH = GLES_SHADER_STRING_PRECISION_H(
        varying vec2 textureCoordinate;
        uniform sampler2D inputImageTexture;

        void main() {
            gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
        }
);

DefaultDrawer::DefaultDrawer() {
    mProgramId = 0;
    mTextureCoords = -1;
    mVertexCoords = -1;
    mTextureHandle = -1;

    mVertexShader = Default_VSH;
    mFragmentShader = Default_FSH;
}

DefaultDrawer::~DefaultDrawer() {

}

void DefaultDrawer::init() {
    // 创建GL程序
    mProgramId = loadProgram(mVertexShader, mFragmentShader);
    if (mProgramId == 0) {
        LOGE(LOG_TAG, "create gl program error");
    }

    // 顶点坐标
    mVertexCoords = glGetAttribLocation(mProgramId, "aPosition");
    checkGlError("glGetAttribLocation aPosition");

    // 纹理坐标
    mTextureCoords = glGetAttribLocation(mProgramId, "aTexCoord");
    checkGlError("glGetAttribLocation aTexCoord");

    // 纹理
    mTextureHandle = glGetUniformLocation(mProgramId, "inputImageTexture");
    checkGlError("glGetUniformLocation inputImageTexture");
}


void DefaultDrawer::process(GLuint textureId, int width, int height) {
    glViewport(0, 0, width, height);
    glUseProgram(mProgramId);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0);

    // 顶点数据
    glVertexAttribPointer(mVertexCoords, 2, GL_FLOAT, 0, 0, VERTICE_NO_ROTATION);
    checkGlError("glVertexAttribPointer aPosition");
    glEnableVertexAttribArray(mVertexCoords);
    checkGlError("glEnableVertexAttribArray mVertexCoords");

    // 纹理数据
    glVertexAttribPointer(mTextureCoords, 2, GL_FLOAT, 0, 0, TEXTURE_ROTATED_180);
    checkGlError("glVertexAttribPointer aTexCoord");
    glEnableVertexAttribArray(mTextureCoords);
    checkGlError("glEnableVertexAttribArray mTextureCoords");

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

void DefaultDrawer::destroy() {
    if (mProgramId != 0) {
        glDeleteProgram(mProgramId);
        checkGlError("glDeleteProgram mProgramId");
    }
}