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
    mVAOId = 0;

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

    // VAO
    glGenVertexArrays(1, &mVAOId);
    glBindVertexArray(mVAOId);

    GLuint vboId[2];
    glGenBuffers(2, vboId);

    glEnableVertexAttribArray(mVertexCoords);
    glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICE_NO_ROTATION), VERTICE_NO_ROTATION, GL_STATIC_DRAW);
    glVertexAttribPointer(mVertexCoords, 2, GL_FLOAT, 0, 2 * 4, NULL);

    glEnableVertexAttribArray(mTextureCoords);
    glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TEXTURE_ROTATED_180), TEXTURE_ROTATED_180, GL_STATIC_DRAW);
    glVertexAttribPointer(mTextureCoords, 2, GL_FLOAT, 0, 2 * 4, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(2, vboId);
}


void DefaultDrawer::process(GLuint textureId, int width, int height) {
    glViewport(0, 0, width, height);
    glUseProgram(mProgramId);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0);

    glBindVertexArray(mVAOId);

    // 渲染
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(mTextureHandle, 0);

    // draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawArrays");

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DefaultDrawer::destroy() {
    if (mProgramId != 0) {
        glDeleteProgram(mProgramId);
        checkGlError("glDeleteProgram mProgramId");
    }

    if (mVAOId != 0) {
        glDeleteVertexArrays(1, &mVAOId);
    }
}