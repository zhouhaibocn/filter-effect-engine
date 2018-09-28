//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_SKETCH_FILTER_H
#define FILTERENGINE_SKETCH_FILTER_H

#include "filter/base/multi_input_filter.h"

class SketchFilter : public MultiInputFilter {
private:
    GLint mWidthOffsetHandle;
    GLint mHeightOffsetHandle;

public:
    SketchFilter();

    ~SketchFilter();

    void init(FilterConfig *filterConfig);

    void process(GLuint textureId, int width, int height);
};

#endif //FILTERENGINE_SKETCH_FILTER_H
