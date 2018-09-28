//
// Created by zhouhaibo on 2017/9/11.
//

#include "beautify_manager.h"

BeautifyManager::BeautifyManager() {
    mIsInitialized = false;
    mFboTextureID = 0;
    mFboBufferID = 0;
    mBeautifyFilter = NULL;
}

BeautifyManager::~BeautifyManager() {
    if (mIsInitialized) {
        destroy();
    }
}

void BeautifyManager::init(int width, int height) {
    if (NULL == mBeautifyFilter) {
        mBeautifyFilter = new BeautifyFilter();
        mBeautifyFilter->init();
    }

    if (mFboTextureID == 0) {
        glGenTextures(1, &mFboTextureID);
    }

    if (mFboBufferID == 0) {
        glGenFramebuffers(1, &mFboBufferID);
    }

    bindFrameBuffer(mFboTextureID, mFboBufferID, width, height);

    mIsInitialized = true;
}

void BeautifyManager::setParams(int type, float intensity) {
    if (NULL != mBeautifyFilter) {
        mBeautifyFilter->setParam(type, intensity);
    }
}

GLuint BeautifyManager::process(GLuint textureId, int width, int height) {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, mFboBufferID);
    GLuint targetTexture = textureId;

    if (NULL != mBeautifyFilter) {
        mBeautifyFilter->process(targetTexture, width, height);
        targetTexture = mFboTextureID;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return targetTexture;
}

void BeautifyManager::destroy() {
    if (!mIsInitialized) {
        LOGE("BeautifyInterFace is not Initialized");
        return;
    }

    if (NULL != mBeautifyFilter) {
        mBeautifyFilter->destroy();
        delete mBeautifyFilter;
    }

    mIsInitialized = false;
}