//
// Created by zhouhaibo on 2017/7/24.
//

#ifndef FILTERENGINE_GL_UTILS_H
#define FILTERENGINE_GL_UTILS_H

#include "common/common.h"
#include "decoder/picture_decoder.h"

#define GLES_CHECK_ERROR_FLAG  true

static const float VERTICE_NO_ROTATION[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f,  1.0f,
        1.0f,  1.0f,
};

static const float TEXTURE_NO_ROTATION[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
};

static const float TEXTURE_ROTATED_90[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
};

static const float TEXTURE_ROTATED_180[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
};

static const float TEXTURE_ROTATED_270[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
};


bool checkGlError(const char* op);

GLuint loadShader(GLenum shaderType, ConstString pSource);

GLuint loadProgram(ConstString pVertexSource, ConstString pFragmentSource);

void bindFrameBuffer(GLuint textureId, GLuint frameBuffer, int width, int height);

void bindFrameBufferWithDepth(GLuint textureId, GLuint frameBuffer, int width, int height);

void bindFrameBufferWithMSAA(GLuint frameBuffer, int width, int height);

GLuint loadTexture(int width, int height, unsigned char *rgbaBuf);

GLuint loadTextureFromBin(ConstString binName);

GLuint loadTextureFromPng(ConstString pngName);

GLuint loadTextureFromPngWithSize(ConstString pngName, int *imgWidth, int *imgHeight);

#endif //FILTERENGINE_GL_UTILS_H
