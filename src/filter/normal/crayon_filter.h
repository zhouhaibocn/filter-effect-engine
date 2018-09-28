//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_CRAYON_FILTER_H
#define FILTERENGINE_CRAYON_FILTER_H

#include "filter/base/multi_input_filter.h"

class CrayonFilter : public MultiInputFilter {
private:
    GLint mWidthOffsetHandle;
    GLint mHeightOffsetHandle;

public:
    CrayonFilter();

    ~CrayonFilter();

    void init(FilterConfig *filterConfig);

    void process(GLuint textureId, int width, int height);
};

#endif //FILTERENGINE_CRAYON_FILTER_H
