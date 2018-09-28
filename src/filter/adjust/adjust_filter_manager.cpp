//
// Created by zhouhaibo on 2017/9/20.
//

#include "adjust_filter_manager.h"

#define LOG_TAG "AdjustFilterManager"

AdjustFilterManager::AdjustFilterManager() {
    mIsInitialized = false;
    mFboTextureID = 0;
    mFboBufferID = 0;
    mAdjustFilter = NULL;
}

AdjustFilterManager::~AdjustFilterManager() {
    if (mIsInitialized) {
        destroy();
    }
}

void AdjustFilterManager::init(int width, int height) {
    if (NULL == mAdjustFilter) {
        mAdjustFilter = new AdjustFilter();
        mAdjustFilter->init();
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

void AdjustFilterManager::setParams(int type, float intensity) {
    if (NULL != mAdjustFilter) {
        mAdjustFilter->setParam(type, intensity);
    }
}

GLuint AdjustFilterManager::process(GLuint textureId, int width, int height) {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, mFboBufferID);
    GLuint targetTexture = textureId;

    if (NULL != mAdjustFilter) {
        mAdjustFilter->process(targetTexture, width, height);
        targetTexture = mFboTextureID;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return targetTexture;
}

void AdjustFilterManager::destroy() {
    if (!mIsInitialized) {
        LOGE(LOG_TAG, "BeautifyInterFace is not Initialized");
        return;
    }

    if (NULL != mAdjustFilter) {
        mAdjustFilter->destroy();
        delete mAdjustFilter;
    }

    mIsInitialized = false;
}