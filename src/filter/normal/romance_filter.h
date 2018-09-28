//
// Created by zhouhaibo on 2017/9/21.
//

#ifndef FILTERENGINE_ROMANCE_FILTER_H
#define FILTERENGINE_ROMANCE_FILTER_H

#include "filter/base/multi_input_filter.h"

class RomanceFilter : public  MultiInputFilter {

public:
    RomanceFilter();

    ~RomanceFilter();

    void init(FilterConfig *filterConfig);
};

#endif //FILTERENGINE_ROMANCE_FILTER_H
