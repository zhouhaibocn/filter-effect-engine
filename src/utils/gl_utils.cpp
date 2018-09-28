//
// Created by zhouhaibo on 2017/9/27.
//

#include "gl_utils.h"

#define LOG_TAG "GlUtils"

bool checkGlError(const char* op) {
    if (GLES_CHECK_ERROR_FLAG) {
        GLint error;
        for (error = glGetError(); error; error = glGetError()) {
            LOGE(LOG_TAG, "after %s() glError (0x%x)\n", op, error);
            return true;
        }
    }
    return false;
}

GLuint loadShader(GLenum shaderType, ConstString pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE(LOG_TAG, "Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
            } else {
                LOGI(LOG_TAG, "Guessing at GL_INFO_LOG_LENGTH size\n");
                char* buf = (char*) malloc(0x1000);
                if (buf) {
                    glGetShaderInfoLog(shader, 0x1000, NULL, buf);
                    LOGE(LOG_TAG, "Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

GLuint loadProgram(ConstString pVertexSource, ConstString pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }
    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }
    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE(LOG_TAG, "Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}


void bindFrameBuffer(GLuint textureId, GLuint frameBuffer, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,textureId, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void bindFrameBufferWithDepth(GLuint textureId, GLuint frameBuffer, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLuint depthBuffer = 0;
    glGenRenderbuffers(1, &depthBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void bindFrameBufferWithMSAA(GLuint frameBuffer, int width, int height) {
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA8, width, height);
    checkGlError("glRenderbufferStorageMultisample");
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);
    checkGlError("glFramebufferRenderbuffer");

    GLuint depthBuffer = 0;
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT16, width, height);
    checkGlError("glRenderbufferStorageMultisample");
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    checkGlError("glFramebufferRenderbuffer");

    // Test the framebuffer for completeness.
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOGE(LOG_TAG, "failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
}


GLuint loadTexture(int width, int height, unsigned char *rgbaBuf){
    GLuint textureHandle;
    glGenTextures(1, &textureHandle);

    if (textureHandle != 0){
        glBindTexture(GL_TEXTURE_2D, textureHandle);

        // Set filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaBuf);

    }

    return textureHandle;
}

GLuint loadTextureFromBin(ConstString binName) {
    if (NULL == binName) {
        return 0;
    }
    FILE *fp = NULL;
    fp = fopen(binName, "rb");
    if (NULL == fp) {
        LOGE(LOG_TAG, "open bin file failed, bin file name: %s", binName);
        return 0;
    }
    // 先读取头信息
    uint8_t head[4] = {0};
    size_t  headSize = fread(head, 1, sizeof(head), fp);
    if (headSize != sizeof(head)) {
        LOGE(LOG_TAG, "read bin head failed, read head size: %d", headSize);
        fclose(fp);
        return 0;
    }
    // 小端格式
    size_t width = head[1] * 256 + head[0];
    size_t height = head[3] * 256 + head[2];
    size_t length = width * height * 4;

    uint8_t *rgbaBuf = new uint8_t[length];

    size_t rgbaSize = fread(rgbaBuf, 1, length, fp);
    if (rgbaSize != length) {
        LOGE(LOG_TAG, "read bin data failed, read data size: %d", rgbaSize);
        fclose(fp);
        return 0;
    }

    GLuint target = loadTexture(width, height, rgbaBuf);
    if (NULL != rgbaBuf) {
        delete rgbaBuf;
    }

    return target;
}

GLuint loadTextureFromPng(ConstString pngName) {
    if (NULL == pngName) {
        return 0;
    }

    GLuint target = 0;
    int width = 0;
    int height = 0;
    unsigned char *rgbaBuf = NULL;
    if (!pic_decode(pngName, &width, &height, &rgbaBuf)) {
        target = loadTexture(width, height, rgbaBuf);
        if (NULL != rgbaBuf) {
            free(rgbaBuf);
            rgbaBuf = NULL;
        }
    } else {
        LOGE(LOG_TAG, "decode png file failed");
    }

    return target;
}

GLuint loadTextureFromPngWithSize(ConstString pngName, int *imgWidth, int *imgHeight) {
    if (NULL == pngName) {
        return 0;
    }

    GLuint target = 0;
    int width = 0;
    int height = 0;
    unsigned char *rgbaBuf = NULL;
    if (!pic_decode(pngName, &width, &height, &rgbaBuf)) {
        target = loadTexture(width, height, rgbaBuf);
        if (width > 0 && height > 0) {
            *imgWidth = width;
            *imgHeight = height;
        }
        if (NULL != rgbaBuf) {
            free(rgbaBuf);
            rgbaBuf = NULL;
        }
    } else {
        LOGE(LOG_TAG, "decode png file failed");
    }

    return target;
}