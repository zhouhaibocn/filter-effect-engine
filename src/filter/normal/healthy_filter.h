//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_HEALTHY_FILTER_H
#define FILTERENGINE_HEALTHY_FILTER_H

#include "filter/base/multi_input_filter.h"

class HealthyFilter : public MultiInputFilter {
private:
    GLint mWidthOffsetHandle;
    GLint mHeightOffsetHandle;

public:
    HealthyFilter();

    ~HealthyFilter();

    void init(FilterConfig *filterConfig);

    void process(GLuint textureId, int width, int height);
};


#endif //FILTERENGINE_HEALTHY_FILTER_H
