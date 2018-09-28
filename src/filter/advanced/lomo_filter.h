//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_LOMO_FILTER_H
#define FILTERENGINE_LOMO_FILTER_H

#include "filter/base/multi_input_filter.h"

class LomoFilter : public MultiInputFilter {
public:
    LomoFilter();

    ~LomoFilter();

    void init(FilterConfig *filterConfig);

};

#endif //FILTERENGINE_LOMO_FILTER_H
