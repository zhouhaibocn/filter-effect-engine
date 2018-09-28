//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_CALM_FILTER_H
#define FILTERENGINE_CALM_FILTER_H

#include "filter/base/multi_input_filter.h"

class CalmFilter : public MultiInputFilter {
public:
    CalmFilter();

    ~CalmFilter();

    void init(FilterConfig *filterConfig);
};

#endif //FILTERENGINE_CALM_FILTER_H
