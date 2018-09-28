//
// Created by zhouhaibo on 2017/9/21.
//

#ifndef FILTERENGINE_LATTE_FILTER_H
#define FILTERENGINE_LATTE_FILTER_H

#include "filter/base/multi_input_filter.h"

class LatteFilter : public  MultiInputFilter {

public:
    LatteFilter();

    ~LatteFilter();

    void init(FilterConfig *filterConfig);
};

#endif //FILTERENGINE_LATTE_FILTER_H
