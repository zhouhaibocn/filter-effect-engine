//
// Created by zhouhaibo on 2017/9/12.
//

#ifndef FILTERENGINE_FILTER_HANDLER_H
#define FILTERENGINE_FILTER_HANDLER_H

#include "beautify/beautify_manager.h"
#include "filter/adjust/adjust_filter_manager.h"
#include "filter/filter_manager.h"
#include "utils/default_drawer.h"

class FilterHandler {
private:
    bool mIsInitialized;
    GLuint mTextureID;
    int mViewWidth;
    int mViewHeight;

    int mImgWidth;
    int mImgHeight;

    bool mIsEnableFilter;

    BeautifyManager *mBeautifyManager;

    AdjustFilterManager *mAdjustFilterManager;

    FilterManager *mFilterManager;

    DefaultDrawer *mDefaultDrawer;

public:
    FilterHandler();

    ~FilterHandler();

    int init(ConstString fileName);

    int setBeautifyParams(int type, float intensity);

    int setFilter(const char *filter_zip);

    int setSize(int width, int height);

    int setAdjustParams(int type, float intensity);

    GLuint process(GLuint textureId);

    void getResult(unsigned char *data);

    void getIameSize(int *width, int *height);

    void destroy();
};


#endif //FILTERENGINE_FILTER_HANDLER_H
