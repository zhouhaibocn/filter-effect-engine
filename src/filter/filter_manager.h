//
// Created by zhouhaibo on 2017/9/15.
//

#ifndef FILTERENGINE_FILTER_MANAGER_H
#define FILTERENGINE_FILTER_MANAGER_H

#include "filter/base/multi_input_filter.h"
#include "filter/filter_factory.h"

class FilterManager {

private:
    bool mIsInitialized;
    GLuint mFboBufferID;
    GLuint mFboTextureID;

    FilterType mCurrentFilter;

    FilterConfig *mFilterConfig;

    MultiInputFilter *mMultiInputFilter;

public:
    FilterManager();

    ~FilterManager();

    void init(int width, int height);

    void setFilter(ConstString zipPath);

    GLuint process(GLuint textureId, int width, int height);

    void destroy();

    // for test
    void getResult(unsigned char * buffer);

};


#endif //FILTERENGINE_FILTER_MANAGER_H
