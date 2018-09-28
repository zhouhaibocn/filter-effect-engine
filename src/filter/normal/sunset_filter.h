//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_SUNSET_FILTER_H
#define FILTERENGINE_SUNSET_FILTER_H

#include "filter/base/multi_input_filter.h"

class SunsetFilter : public MultiInputFilter {
public:
    SunsetFilter();

    ~SunsetFilter();

    void init(FilterConfig *filterConfig);
};

#endif //FILTERENGINE_SUNSET_FILTER_H
