//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_NOSTALGIA_FILTER_H
#define FILTERENGINE_NOSTALGIA_FILTER_H

#include "filter/base/multi_input_filter.h"

class NostalgiaFilter : public MultiInputFilter {
private:
    GLint mWidthOffsetHandle;
    GLint mHeightOffsetHandle;

public:
    NostalgiaFilter();

    ~NostalgiaFilter();

    void init(FilterConfig *filterConfig);

    void process(GLuint textureId, int width, int height);
};


#endif //FILTERENGINE_NOSTALGIA_FILTER_H
