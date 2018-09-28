//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_SIERRA_FILTER_H
#define FILTERENGINE_SIERRA_FILTER_H

#include "filter/base/multi_input_filter.h"

class SierraFilter : public MultiInputFilter {
public:
    SierraFilter();

    ~SierraFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_SIERRA_FILTER_H
