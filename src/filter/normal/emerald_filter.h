//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_EMERALD_FILTER_H
#define FILTERENGINE_EMERALD_FILTER_H

#include "filter/base/multi_input_filter.h"

class EmeraldFilter : public MultiInputFilter {
public:
    EmeraldFilter();

    ~EmeraldFilter();

    void init(FilterConfig *filterConfig);
};


#endif //FILTERENGINE_EMERALD_FILTER_H
