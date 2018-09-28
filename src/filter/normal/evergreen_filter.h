//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_EVERGREEN_FILTER_H
#define FILTERENGINE_EVERGREEN_FILTER_H

#include "filter/base/multi_input_filter.h"

class EvergreenFilter : public MultiInputFilter {
public:
    EvergreenFilter();

    ~EvergreenFilter();

    void init(FilterConfig *filterConfig);
};

#endif //FILTERENGINE_EVERGREEN_FILTER_H
