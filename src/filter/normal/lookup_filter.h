//
// Created by zhouhaibo on 2017/9/12.
//

#ifndef FILTERENGINE_LOOKUP_FILTER_H
#define FILTERENGINE_LOOKUP_FILTER_H

#include "filter/base/multi_input_filter.h"

class LookupFilter : public  MultiInputFilter {

public:
    LookupFilter();

    ~LookupFilter();

    void init(FilterConfig *filterConfig);
};

#endif //FILTERENGINE_LOOKUP_FILTER_H
