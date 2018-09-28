//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_WARM_FILTER_H
#define FILTERENGINE_WARM_FILTER_H

#include "filter/base/multi_input_filter.h"

class WarmFilter : public MultiInputFilter {
public:
    WarmFilter();

    ~WarmFilter();

    void init(FilterConfig *filterConfig);
};

#endif //FILTERENGINE_WARM_FILTER_H
