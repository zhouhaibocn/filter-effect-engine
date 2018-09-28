//
// Created by zhouhaibo on 2017/9/21.
//

#ifndef FILTERENGINE_COOL_FILTER_H
#define FILTERENGINE_COOL_FILTER_H

#include "filter/base/multi_input_filter.h"

class CoolFilter : public MultiInputFilter {
public:
    CoolFilter();

    ~CoolFilter();

    void init(FilterConfig *filterConfig);
};


#endif //FILTERENGINE_COOL_FILTER_H
