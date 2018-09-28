//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_SWEETS_FILTER_H
#define FILTERENGINE_SWEETS_FILTER_H

#include "filter/base/multi_input_filter.h"

class SweetsFilter : public MultiInputFilter {
private:
    GLint mWidthOffsetHandle;
    GLint mHeightOffsetHandle;

public:
    SweetsFilter();

    ~SweetsFilter();

    void init(FilterConfig *filterConfig);

    void process(GLuint textureId, int width, int height);
};
#endif //FILTERENGINE_SWEETS_FILTER_H
