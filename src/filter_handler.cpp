//
// Created by zhouhaibo on 2017/9/12.
//

#include "filter_handler.h"

FilterHandler::FilterHandler() {
    mIsInitialized = false;
    mViewWidth = -1;
    mViewHeight = -1;
    mImgWidth = -1;
    mImgHeight = -1;
    mTextureID = 0;
    mIsEnableFilter = false;
    mBeautifyManager = NULL;
    mAdjustFilterManager = NULL;
    mFilterManager = NULL;
    mDefaultDrawer = NULL;
}

FilterHandler::~FilterHandler() {

}

int FilterHandler::init(ConstString fileName) {
    if (NULL != fileName) {
        mTextureID = loadTextureFromPngWithSize(fileName, &mImgWidth, &mImgHeight);
        if (mTextureID <= 0) {
            LOGE("loadTexture failed, textureId: %d", mTextureID);
        }
    }

    if (NULL == mBeautifyManager) {
        mBeautifyManager = new BeautifyManager();
        mBeautifyManager->init(mImgWidth, mImgHeight);
    }

    if (NULL == mAdjustFilterManager) {
        mAdjustFilterManager = new AdjustFilterManager();
        mAdjustFilterManager->init(mImgWidth, mImgHeight);
    }

    if (NULL == mFilterManager) {
        mFilterManager = new FilterManager();
        mFilterManager->init(mImgWidth, mImgHeight);
    }

    if (NULL == mDefaultDrawer) {
        mDefaultDrawer = new DefaultDrawer();
        mDefaultDrawer->init();
    }

    mIsInitialized = true;

    return 0;
}

int FilterHandler::setSize(int width, int height) {
    if (width > 0 && height > 0) {
        mViewWidth = width;
        mViewHeight = height;
    }

    return 0;
}

int FilterHandler::setFilter(ConstString filter_zip) {
    if (NULL != filter_zip) {
        mIsEnableFilter = true;
        if (NULL != mFilterManager) {
            mFilterManager->setFilter(filter_zip);
        }
    } else {
        mIsEnableFilter = false;
    }

    return 0;
}

int FilterHandler::setBeautifyParams(int type, float intensity) {
    if (NULL != mBeautifyManager) {
        mBeautifyManager->setParams(type, intensity);
    }

    return 0;
}

int FilterHandler::setAdjustParams(int type, float intensity) {
    if (NULL != mAdjustFilterManager) {
        mAdjustFilterManager->setParams(type, intensity);
    }

    return 0;
}

GLuint FilterHandler::process(GLuint textureId) {
    GLuint targetTextureId = mTextureID;

    if (NULL != mBeautifyManager && targetTextureId > 0) {
        targetTextureId = mBeautifyManager->process(targetTextureId, mImgWidth, mImgHeight);
    }

    if (NULL != mAdjustFilterManager && targetTextureId > 0) {
        targetTextureId = mAdjustFilterManager->process(targetTextureId, mImgWidth, mImgHeight);
    }

    if (NULL != mFilterManager && targetTextureId > 0 && mIsEnableFilter) {
        targetTextureId = mFilterManager->process(targetTextureId, mImgWidth, mImgHeight);
    }

    if (NULL != mDefaultDrawer && targetTextureId > 0) {
        mDefaultDrawer->process(targetTextureId, mViewWidth, mViewHeight);
    }

    return targetTextureId;
}

void FilterHandler::destroy() {
    if (NULL != mBeautifyManager) {
        mBeautifyManager->destroy();
        delete mBeautifyManager;
    }

    if (NULL != mAdjustFilterManager) {
        mAdjustFilterManager->destroy();
        delete mAdjustFilterManager;
    }

    if (NULL != mFilterManager) {
        mFilterManager->destroy();
        delete mFilterManager;
    }
}


void FilterHandler::getResult(unsigned char *data) {
    if (mFilterManager != NULL) {
        mFilterManager->getResult(data, mImgWidth, mImgHeight);
    }
}

void FilterHandler::getIameSize(int *width, int *height) {
    *width = mImgWidth;
    *height = mImgHeight;
}
