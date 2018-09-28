//
// Created by zhouhaibo on 2017/9/21.
//

#ifndef FILTERENGINE_SAKURA_FILTER_H
#define FILTERENGINE_SAKURA_FILTER_H

#include "filter/base/multi_input_filter.h"

class SakuraFilter : public  MultiInputFilter {
private:
    GLint mWidthOffsetHandle;
    GLint mHeightOffsetHandle;

public:
    SakuraFilter();

    ~SakuraFilter();

    void init(FilterConfig *filterConfig);

    void process(GLuint textureId, int width, int height);
};

#endif //FILTERENGINEDEMO_SAKURA_FILTER_H
