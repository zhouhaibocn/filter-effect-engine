//
// Created by zhouhaibo on 2017/9/20.
//

#ifndef FILTERENGINE_ADJUST_FILTER_MANAGER_H
#define FILTERENGINE_ADJUST_FILTER_MANAGER_H

#include "adjust_filter.h"

class AdjustFilterManager {
private:
    bool mIsInitialized;
    GLuint mFboBufferID;
    GLuint mFboTextureID;

    AdjustFilter *mAdjustFilter;

public:
    AdjustFilterManager();

    ~AdjustFilterManager();

    void init(int width, int height);

    void setParams(int type, float intensity);

    GLuint process(GLuint textureId, int width, int height);

    void destroy();

};


#endif //FILTERENGINE_ADJUST_FILTER_MANAGER_H
