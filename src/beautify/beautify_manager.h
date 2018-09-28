//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_BEAUTIFY_MANAGER_H
#define FILTERENGINE_BEAUTIFY_MANAGER_H

#include "beautify_filter.h"

class BeautifyManager {
private:
    bool mIsInitialized;
    GLuint mFboBufferID;
    GLuint mFboTextureID;

    BeautifyFilter *mBeautifyFilter;

public:
    BeautifyManager();

    ~BeautifyManager();

    void init(int width, int height);

    void setParams(int type, float intensity);

    GLuint process(GLuint textureId, int width, int height);

    void destroy();
};


#endif //FILTERENGINE_BEAUTIFY_MANAGER_H
